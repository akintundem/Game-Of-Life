#include <iostream>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp> //for resizing
#include <vector>
#include <sstream>
#include <string>

#define MAX_SIZE 1024

int main(int argc, char** argv)
{
	assert(argc == 4);
	
	//-----------------------
	// Convert Command Line
	//-----------------------
			
	int ny = atoi(argv[1]);
	int nx = atoi(argv[2]);
    int maxiter = atoi(argv[3]);
	
    assert(ny <= MAX_SIZE);
    assert(nx <= MAX_SIZE);
    
    //---------------------------------
    // Generate the initial image
    //---------------------------------
    srand(clock());
    cv::Mat population(ny, nx, CV_8UC1);
    for (unsigned int iy = 0; iy < ny; iy++)
    {
        for (unsigned int ix = 0; ix < nx; ix++)
        {
            //seed a 1/2 density of alive (just arbitrary really)
            int state = rand()%2;
            if (state == 0) population.at<uchar>(iy,ix) = 255; //dead
            else population.at<uchar>(iy,ix) = 0;   //alive
        }
    }
    
    cv::Mat newpopulation = population.clone();
    cv::namedWindow("Population", cv::WINDOW_AUTOSIZE );
    cv::Mat image_for_viewing(MAX_SIZE,MAX_SIZE,CV_8UC1);
    
    for (int iter = 0; iter < maxiter; iter++)
    {
        //something new here - we will resize our image up to MAX_SIZE x MAX_SIZE so its not really tiny on the screen
        cv::resize(population,image_for_viewing,image_for_viewing.size(),cv::INTER_LINEAR); //resize image to MAX_SIZE x MAX_SIZE
        cv::imshow("Population", image_for_viewing);
        cv::waitKey(10);	//wait 10 seconds before closing image (or a keypress to close)
        
        for (int iy = 0; iy < ny; iy++)
        {
            for (int ix = 0; ix < nx; ix++)
            {
                int occupied_neighbours = 0;

                for (int jy = iy - 1; jy <= iy + 1; jy++)
                {
                    for (int jx = ix - 1; jx <= ix + 1; jx++)
                    {
                        if (jx == ix && jy == iy) continue;
                        
                        int row = jy;
                        if (row == ny) row = 0;
                        if (row == -1) row = ny-1;
                        
                        int col = jx;
                        if (col == nx) col = 0;
                        if (col == -1) col = nx - 1;
                        
                        if (population.at<uchar>(row,col) == 0) occupied_neighbours++;
                    }
                }
            
                if (population.at<uchar>(iy,ix) == 0)   //alive
                {
                    if (occupied_neighbours <= 1 || occupied_neighbours >= 4) newpopulation.at<uchar>(iy,ix) = 255; //dies
                    if (occupied_neighbours == 2 || occupied_neighbours == 3) newpopulation.at<uchar>(iy,ix) = 0; //same as population
                }
                else if (population.at<uchar>(iy,ix) == 255) //dead
                {
                    if (occupied_neighbours == 3)
                    {
                        newpopulation.at<uchar>(iy,ix) = 0; //reproduction
                    }
                }
            }
        }
        population = newpopulation.clone();
    }
}
