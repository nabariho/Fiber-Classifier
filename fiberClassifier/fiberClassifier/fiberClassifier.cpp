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

	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;

	//Canny( canny_input, canny_output, 0, 0*3, 3 );

	findContours(canny_input, contours, hierarchy, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_TC89_KCOS, Point(0, 0) );
	Mat drawing = Mat::zeros(canny_input.size(), CV_8UC3 );
	vector<Point> approxShape;
	for( int i = 0; i< contours.size(); i++ )
     {
		 drawContours(drawing, contours, i, Scalar(255, 255, 255), CV_FILLED);   // fill BLUE

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



int _tmain(int argc, _TCHAR* argv[])
{

    String file1 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/4_3_1.tif";
	String file2 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/4_50_1.tif";
	String file3 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/10_3_1.tif";

	  /// Create a matrix of the same type and size as src (for dst)




	Sample my_sample(file1,file2,file3,BLACK_THRESHOLD_IMAGE1,BLACK_THRESHOLD_IMAGE2,BLACK_THRESHOLD_IMAGE3);
	//my_sample.align(); //Queda pendiente tratar el alineamiento
	Mat channels[3],channel;
	
	Mat blackImage1, blackImage2,blackImage3, inv1, inv2, inv3, contour1, contour2, contour3;
	
	lowThreshold = 25;
	blackImage1 = CannyThreshold(file1, 0, 0);
	lowThreshold = 25;
	blackImage2 = CannyThreshold(file2, 0, 0);
	lowThreshold = 50;
	blackImage3 = CannyThreshold(file3, 0, 0);

	namedWindow( "negras1",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "negras1", blackImage1);
	namedWindow( "negras2",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "negras2", blackImage2);
	namedWindow( "negras3",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "negras3", blackImage3);

	bitwise_not(blackImage1, inv1);
	bitwise_not(blackImage2, inv2);
	bitwise_not(blackImage3, inv3);
	

	namedWindow( "inv1",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "inv1", inv1);
	namedWindow("inv2",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "inv2", inv2);
	namedWindow( "inv3",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "inv3", inv3);

	contour1 = getContourFromBinary(blackImage1);
	contour2 = getContourFromBinary(blackImage2);
	contour3 = getContourFromBinary(blackImage3);

		
	namedWindow( "contour1",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "contour1", contour1);
	namedWindow("contour2",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "contour2", contour2);
	namedWindow( "contour3",CV_WINDOW_NORMAL);// Create a window for display.
	imshow( "contour3", contour3);


	//threshold( blackImage1, blackImage1, 80, MAX_BINARY_VALUE,BINARY_THRESHOLD );
	//threshold( blackImage2, blackImage2, 80, MAX_BINARY_VALUE,BINARY_THRESHOLD );
	//threshold( blackImage3, blackImage3, 80, MAX_BINARY_VALUE,BINARY_THRESHOLD );



	//Mat invBlackImage1, invBlackImage2, invBlackImage3;
	//Mat type1, type2, type3;

	//bitwise_not(blackImage1,invBlackImage1);
	//bitwise_not(blackImage2,invBlackImage2);
	//bitwise_not(blackImage3,invBlackImage3);

	//namedWindow( "Negras1",CV_WINDOW_NORMAL);// Create a window for display.
	//imshow( "Negras1", blackImage1);	
	//namedWindow( "Negras2",CV_WINDOW_NORMAL);// Create a window for display.
	//imshow( "Negras2", blackImage2);	
	//namedWindow( "Negras3",CV_WINDOW_NORMAL);// Create a window for display.
	//imshow( "Negras3", blackImage3);	



	////Fibras tipo 1 (1, 1, 0)
	//bitwise_and(invBlackImage1,invBlackImage2,type1);
	//bitwise_and(blackImage3,type1,type1);

	//namedWindow( "Tipo1",CV_WINDOW_NORMAL);// Create a window for display.
	//imshow( "Tipo1", type1);

	////Fibras tipo 2 (1, 0, 1)
	//bitwise_and(invBlackImage1, blackImage2, type2);
	//bitwise_and(type2, invBlackImage3, type2);

	//namedWindow( "Tipo2",CV_WINDOW_NORMAL);// Create a window for display.
	//imshow( "Tipo2", type2);

	////Fibras tipo 3 (0, 1, 1)
	//bitwise_and(blackImage1, invBlackImage2, type3);
	//bitwise_and(type3,invBlackImage3,type3);

	//namedWindow( "Tipo3",CV_WINDOW_NORMAL);// Create a window for display.
	//imshow( "Tipo3", type3);

	//Mat contornos1, contornos2, contornos3;

	//contornos1 = getContourFromBinary(type1);
	//contornos2 = getContourFromBinary(type2);
	//contornos3 = getContourFromBinary(type3);

	//namedWindow( "contornos1",CV_WINDOW_NORMAL);// Create a window for display.
	//imshow( "contornos1", contornos1);	
	//namedWindow( "contornos2",CV_WINDOW_NORMAL);// Create a window for display.
	//imshow( "contornos2", contornos2);	
	//namedWindow( "contornos3",CV_WINDOW_NORMAL);// Create a window for display.
	//imshow( "contornos3", contornos3);	

	//channels[0] = contornos1;
	//channels[1] = contornos2;
	//channels[2] = contornos3;
	//merge(channels, 3, channel);
	//namedWindow( "combined",CV_WINDOW_NORMAL);// Create a window for display.
	//imshow( "combined", channel);

    waitKey();
    return 0;

}


