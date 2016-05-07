/*
 * road.cpp
 *
 *  Created on: 24-Feb-2016
 *      Author: designer
 */




#include <sstream>
#include <string>
#include <iostream>
#include <math.h>
#include <unistd.h>
#include <sys/time.h>
//#include "opencv\highgui.h"
//#include "opencv\cv.h"

#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;
using namespace std;

int main(int argc, const char** argv){

	Mat dst = imread("im7.jpg", CV_LOAD_IMAGE_UNCHANGED); //read the image data in the file "MyPic.JPG" and store it in 'img'

	     if (dst.empty()) //check whether the image is loaded or not
	     {
	          cout << "Error : Image cannot be loaded..!!" << endl;
	          //system("pause"); //wait for a key press
	          return -1;
	     }

	     Size size(600,600);
	     Mat img_1;
	     resize(dst,img_1,size);

	     cv::Size s = img_1.size();
	     int rows = s.height;
	     int cols = s.width;
	     printf("%d \t%d \t%d\t%d", rows,cols,s.height,s.width);

	     cv::Rect myROI(0,img_1.cols/4,img_1.cols-1,img_1.rows - img_1.cols/4);

	     cv::Mat img = img_1(myROI);
	     Mat gray,gray_test;
	     blur( img, gray,Size(3,3));
	     cvtColor(img, gray, CV_RGB2GRAY);

	     /**/
	     cvtColor(img_1, gray_test, CV_RGB2GRAY);


	     Mat contours,cont_test;
	     Canny(gray,contours,140,350,3);
	     /**/
	     Canny(gray_test,cont_test,140,350,3);
	     Mat contoursInv,c_test;
	     threshold(contours,contoursInv,128,255,THRESH_BINARY_INV);
	     /**/
	     threshold(cont_test,c_test,128,255,THRESH_BINARY_INV);
	     int x_1=0;
	     int y_1=0;
	     int x_2=0;
	     int y_2=0;
	     vector<Vec4i> lines;
	         HoughLinesP( contours, lines, 1, CV_PI/180, 150, 30, 10 );
	         //sort (lines.begin(),lines.end());
	         size_t l=lines.size();
	         x_1=lines[0][0];
	         y_1=lines[0][1];
	         x_2=lines[l-1][2];
	         y_2=lines[l-1][3];
//
	         for( size_t i = 0; i < lines.size(); i++ )
	         {
	             line( img, Point(lines[i][0], lines[i][1]),
	                 Point(lines[i][2], lines[i][3]), Scalar(0,0,255), 2, 8 );
	         }

	        // line( img, x_1,y_1,x_2,y_2, Scalar(0,0,255), 2, 8 );

	         vector<Vec4i> lines_1;
	         	         HoughLinesP( cont_test, lines_1, 1, CV_PI/180, 150, 30, 10 );
	         	         for( size_t i = 0; i < lines_1.size(); i++ )
	         	         {
	         	             line( img_1, Point(lines_1[i][0], lines_1[i][1]),
	         	             Point(lines_1[i][2], lines_1[i][3]), Scalar(0,255,0), 3, 8 );
	         	         }

	     namedWindow("Gray", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	     imshow("Gray", img); //display the image which is stored in the 'img' in the "MyWindow" window

	     namedWindow("Canny", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	      imshow("Canny", img_1);

	      namedWindow("Contours", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	      	      imshow("Contours", contoursInv);

	      	    namedWindow("Gray", CV_WINDOW_AUTOSIZE); //create a window with the name "MyWindow"
	      	    	      	      imshow("gray_Scale", gray);


	     waitKey(0); //wait infinite time for a keypress

	     destroyWindow("MyWindow"); //destroy the window with the name, "MyWindow"

	     return 0;

	return 0;
}
