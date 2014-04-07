
#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>



using namespace cv;
using namespace std;

Mat src, src_gray;
Mat dst, detected_edges, inv;

int edgeThresh = 1;
int lowThreshold;
int const max_lowThreshold = 500;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";



Mat getContourFromBinary(Mat canny_output)
{

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	Canny( canny_output, canny_output, 100, 100*3, 3 );

	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3 );

	for( int i = 0; i< contours.size(); i++ )
     {
			drawContours( drawing, contours, i, 255, 0, 8, hierarchy, 0, Point() );
     }
	return drawing;
}

/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
void CannyThreshold(int, void*)
{
  /// Reduce noise with a kernel 3x3
  blur( src_gray, detected_edges, Size(3,3) );
  equalizeHist(detected_edges,detected_edges);

  /// Canny detector
  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);
  src.copyTo( dst, detected_edges);
  src.copyTo(inv, detected_edges);
  blur(inv,inv, Size(3,3));
  bitwise_not(inv,inv);
  imshow( window_name, dst );
  imshow("inverse",inv);

  Mat channels[3];
  channels[0] = inv;
  channels[1] = inv;
  channels[2] = inv;

  Mat channel;
  merge(channels,channel);





  //Mat invContours;
  //invContours.create( src.size(), src.type() );

  //invContours = getContourFromBinary(inv);
  //threshold(invContours, invContours, 0, 255, CV_THRESH_BINARY);

  //namedWindow("contours", CV_WINDOW_NORMAL);
  //imshow ("contours", invContours);
 }

/** @function main */
int main( int argc, char** argv )
{
  /// Load source image and convert it to gray
  String file1 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/4_3_1.tif";
  String file2 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/4_50_1.tif";
  String file3 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/10_3_1.tif";
  src = imread(file3);

  if( !src.data )
  { return -1; }

  /// Create a matrix of the same type and size as src (for dst)
  dst.create( src.size(), src.type() );
  inv.create( src.size(), src.type() );

  /// Convert the image to grayscale
  cvtColor( src, src_gray, CV_BGR2GRAY );

  /// Create a window
  namedWindow( window_name, CV_WINDOW_NORMAL );
  namedWindow("inverse", CV_WINDOW_NORMAL);
  namedWindow("eq", CV_WINDOW_NORMAL);

  /// Create a Trackbar for user to enter threshold
  createTrackbar( "Min Threshold:", window_name, &lowThreshold, max_lowThreshold, CannyThreshold );

  /// Show the image
  CannyThreshold(0, 0);

  /// Wait until user exit program by pressing a key
  waitKey(0);

  return 0;

}



