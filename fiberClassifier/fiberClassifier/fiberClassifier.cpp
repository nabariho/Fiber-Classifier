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

Mat getContours(string File1, int cannyThreshold){
	Mat src,blurMat,canny_output;
	src = imread( File1);

	/// Convert image to gray and blur it
	cvtColor( src, blurMat, CV_BGR2GRAY );
	blur( blurMat, blurMat, Size(3,3) );

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	Canny( blurMat, canny_output, cannyThreshold, cannyThreshold*2, 3 );
	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	Mat drawing = Mat::zeros(blurMat.size(), CV_8UC3 );

	for( int i = 0; i< contours.size(); i++ )
     {
		drawContours( drawing, contours, i, 255, CV_FILLED, 8, hierarchy, 0, Point() );
     }
	return drawing;
}

Mat getContourFromBinary(Mat canny_output)
{

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	findContours(canny_output, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0) );
	Mat drawing = Mat::zeros(canny_output.size(), CV_8UC3 );

	for( int i = 0; i< contours.size(); i++ )
     {
		drawContours( drawing, contours, i, 255, CV_FILLED, 8, hierarchy, 0, Point() );
     }
	return drawing;
}


int _tmain(int argc, _TCHAR* argv[])
{

    String file1 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/4_3_1.tif";
	String file2 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/4_50_1.tif";
	String file3 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/10_3_1.tif";


	Sample my_sample(file1,file2,file3,BLACK_THRESHOLD_IMAGE1,BLACK_THRESHOLD_IMAGE2,BLACK_THRESHOLD_IMAGE3);
	my_sample.align(); //Queda pendiente tratar el alineamiento
	Mat channels[3],channel;
	
	Image blackImage1, blackImage2,blackImage3;

	blackImage1 = my_sample.images[0].get_black();
	blackImage2 = my_sample.images[1].get_black();
	blackImage3 = my_sample.images[2].get_black();


	Mat invBlackImage1, invBlackImage2, invBlackImage3;
	Mat type1, type2, type3;

	bitwise_not(blackImage1.image_mat(),invBlackImage1);
	bitwise_not(blackImage2.image_mat(),invBlackImage2);
	bitwise_not(blackImage3.image_mat(),invBlackImage3);



	//Fibras tipo 1 (1, 1, 0)
	bitwise_and(invBlackImage1,invBlackImage2,type1);
	bitwise_and(blackImage3.image_mat(),type1,type1);

	namedWindow( "Tipo1",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "Tipo1", type1);

	//Fibras tipo 2 (1, 0, 1)
	bitwise_and(invBlackImage1, blackImage2.image_mat(), type2);
	bitwise_and(type2, invBlackImage3, type2);

	namedWindow( "Tipo2",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "Tipo2", type2);

	//Fibras tipo 3 (0, 1, 1)
	bitwise_and(blackImage1.image_mat(), invBlackImage2, type3);
	bitwise_and(type3,invBlackImage3,type3);

	namedWindow( "Tipo3",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "Tipo3", type3);


	channels[0] = type1;
	channels[1] = type2;
	channels[2] = type3;
	merge(channels, 3, channel);
	namedWindow( "combined",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "combined", channel);

  /// Show in a window
	Mat contourOriginal1 = getContours(file1, CANNY_THRESHOLD_IMAGE1);
	Mat contourOriginal2 = getContours(file2, CANNY_THRESHOLD_IMAGE2);
	Mat contourOriginal3 = getContours(file3, CANNY_THRESHOLD_IMAGE3);

	Mat contourType1, contourType2, contourType3;

	namedWindow( "Contornos",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "Contornos", contourOriginal);

	contourType1 = getContourFromBinary(type1);
	namedWindow( "Contornos Tipo1",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "Contornos Tipo1", contourType1);

	contourType2 = getContourFromBinary(type2);
	namedWindow( "Contornos Tipo2",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "Contornos Tipo2", contourType2);

	contourType3 = getContourFromBinary(type3);
	namedWindow( "Contornos Tipo3",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "Contornos Tipo3", contourType3);





    waitKey();
    return 0;

}


