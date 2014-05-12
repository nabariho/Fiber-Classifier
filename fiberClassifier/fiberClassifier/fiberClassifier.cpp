// fiberClassifier.cpp: define el punto de entrada de la aplicación de consola.
//
#include "stdafx.h"
#include "sample.h"
#include "image.h"
#include "Utils.h"
////////
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;

#include "stdafx.h"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "Utils.h"



using namespace cv;
using namespace std;



int edgeThresh = 1;
int lowThreshold = 0;
int const max_lowThreshold = 100;
int ratio = 3;
int kernel_size = 3;
char* window_name = "Edge Map";


Mat getContourFromBinary(Mat canny_input)
{

	Mat src,blurMat,canny_output;

	/// Convert image to gray and blur it

	vector<vector<Point>> contours;
	vector<Vec4i> hierarchy;

	//Canny( canny_input, canny_output, 0, 0*3, 3 );

	findContours(canny_input, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_KCOS, Point(0, 0) );
	Mat drawing = Mat::zeros(canny_input.size(), CV_8UC3 );
	vector<Point> approxShape;
	vector<Moments> ContArea(contours.size());

    for( int i = 0; i < contours.size(); i++ )
    {  
        ContArea[i] = moments(contours[i], false);
    }

	   /// Find the convex hull object for each contour
   vector<vector<Point> >hull( contours.size() );
   for( int i = 0; i < contours.size(); i++ )
    {  
		  convexHull( Mat(contours[i]), hull[i], false ); 
   }

	RNG rng(12345);
	for( int i = 0; i< contours.size(); i++ )
     {
		Scalar color = Scalar(255, 255, 255);
		drawContours(drawing, contours, i, color, CV_FILLED);   // fill BLUE
		//drawContours( drawing, hull, i, color, CV_FILLED, 8, vector<Vec4i>(), 0, Point() );
     }
	return drawing;
}
/**
 * @function CannyThreshold
 * @brief Trackbar callback - Canny thresholds input with a ratio 1:3
 */
Mat CannyThreshold(string file, int, void*)
{
 
 Mat src,src_gray;
 src = imread(file);

 Mat dst, detected_edges, inv;
 dst.create( src.size(), src.type() );
 inv.create( src.size(), src.type() );

  /// Canny detector

	cvtColor( src, src_gray, CV_BGR2GRAY );

	blur( src_gray, detected_edges, Size(3,3) );
	//equalizeHist(detected_edges,detected_edges);

  Canny( detected_edges, detected_edges, lowThreshold, lowThreshold*ratio, kernel_size );

  /// Using Canny's output as a mask, we display our result
  dst = Scalar::all(0);
  src.copyTo( dst, detected_edges);
  //src.copyTo(inv, detected_edges);
  //blur(inv,inv, Size(3,3));
  //bitwise_not(inv,inv);
  return detected_edges;
 }

Mat Threshold( Mat src, int threshold_value, void* )
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */
	Mat dst, detected_edges, inv;
	Mat src_gray;
 //   src = imread(file);
	//cvtColor( src, src_gray, CV_RGB2GRAY );
 //   equalizeHist(src_gray,src_gray);
    dst.create( src.size(), src.type() );

	threshold( src, dst, threshold_value, 255,INV_BINARY_THRESHOLD);

	return dst;
}




int _tmain(int argc, _TCHAR* argv[])
{

    String file1 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/4_3_1.tif";
	String file2 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/4_50_1.tif";
	String file3 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/10_3_1.tif";

	  /// Create a matrix of the same type and size as src (for dst)




	Sample my_sample(file1,file2,file3,BLACK_THRESHOLD_IMAGE1,BLACK_THRESHOLD_IMAGE2,BLACK_THRESHOLD_IMAGE3);
	my_sample.align(); //Queda pendiente tratar el alineamiento
	Mat channels[3];
	
	Mat blackImage1, blackImage2,blackImage3, inv1, inv2, inv3, contour1, contour2, contour3;
	blackImage1 = Threshold(my_sample.images[0].image_mat(), BLACK_THRESHOLD_IMAGE1, 0);
	blackImage2 = Threshold(my_sample.images[1].image_mat(), BLACK_THRESHOLD_IMAGE2, 0);
	blackImage3 = Threshold(my_sample.images[2].image_mat(), BLACK_THRESHOLD_IMAGE3, 0);

	namedWindow( "negras1",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "negras1", blackImage1);
	namedWindow( "negras2",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "negras2", blackImage2);
	namedWindow( "negras3",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "negras3", blackImage3);


	contour1 = getContourFromBinary(blackImage1);
	contour2 = getContourFromBinary(blackImage2);
	contour3 = getContourFromBinary(blackImage3);

	namedWindow( "contour1",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "contour1", contour1);
	namedWindow("contour2",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "contour2", contour2);
	namedWindow( "contour3",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "contour3", contour3);

	bitwise_not(contour1, inv1);
	bitwise_not(contour2, inv2);
	bitwise_not(contour3, inv3);

	namedWindow( "inv1",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "inv1", inv1);
	namedWindow("inv2",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "inv2", inv2);
	namedWindow( "inv3",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "inv3", inv3);


	
	Mat type1, type2, type3;



	//Fibras tipo 1 (1, 1, 0)
	bitwise_and(contour1,contour2,type1);
	bitwise_and(inv3,type1,type1);

	namedWindow( "Tipo1",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "Tipo1", type1);

	//Fibras tipo 2 (1, 0, 1)
	bitwise_and(contour1, inv2, type2);
	bitwise_and(type2, contour3, type2);

	namedWindow( "Tipo2",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "Tipo2", type2);

	//Fibras tipo 3 (0, 1, 1)
	bitwise_and(inv1, contour2, type3);
	bitwise_and(type3,contour3,type3);

	namedWindow( "Tipo3",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "Tipo3", type3);





    // Create Matrices (make sure there is an image in input!)
    Mat input;
    Mat channel1[3],channel2[3],channel3[3];
	Mat channel_merge[3];
	Mat combined;

    // The actual splitting.
	split(type1, channel1);
	channel_merge[0] = channel1[0];
	split(type2, channel2);
	channel_merge[1] = channel2[0];
	split(type3, channel3);
	channel_merge[2] = channel3[0];
	merge(channel_merge,3,combined);

	//bitwise_and(type1,type2,channel);
	//bitwise_and(type3,channel,channel);
	namedWindow( "combined",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "combined", combined);

    waitKey();
    return 0;

}


