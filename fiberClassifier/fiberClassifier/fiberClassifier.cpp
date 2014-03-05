// fiberClassifier.cpp: define el punto de entrada de la aplicación de consola.
//
//#include "stdafx.h"
//#include "sample.h"
//#include "image.h"
//#include "Utils.h"
//////////
//#include "opencv2/highgui/highgui.hpp"
//#include "opencv2/imgproc/imgproc.hpp"
//#include <iostream>
//#include <stdio.h>
//#include <stdlib.h>
//
//using namespace cv;
//using namespace std;
//
//
//
//int _tmain(int argc, _TCHAR* argv[])
//{
//	/*String file1 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/pruebas_alineacion/flor-1.jpg";
//	String file2 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/pruebas_alineacion/flor-1-rotada.jpg";
//	String file3 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/pruebas_alineacion/flor-1-despl.jpg";*/
//
//    String file1 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/4_3_1.tif";
//	String file2 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/4_50_1.tif";
//	String file3 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/10_3_1.tif";
//
//
//	Sample my_sample(file1,file2,file3,BLACK_THRESHOLD_IMAGE1,BLACK_THRESHOLD_IMAGE2,BLACK_THRESHOLD_IMAGE3);
//	my_sample.align(); //Queda pendiente tratar el alineamiento
//	Mat channels[3],channel;
//	
//
//
//
//
//	//black1.display();
//	//black2.display();
//	//white1.display();
//
//
//	//////Proceso para obtener las fibras de tipo 1 (Negra-Negra-Blanca)
//	//my_sample.images[0].display();
//	//my_sample.images[1].display();
//	//my_sample.images[2].display();
//	Image blackImage1, blackImage2,blackImage3;
//
//	blackImage1 = my_sample.images[0].get_black();
//	blackImage2 = my_sample.images[1].get_black();
//	blackImage3 = my_sample.images[2].get_black();
//
//	//namedWindow( "Tipo2",CV_WINDOW_NORMAL);// Create a window for display.
//	//imshow( "Tipo2", blackImage1.image_mat());
//
//	Mat invBlackImage1, invBlackImage2, invBlackImage3;
//	Mat type1, type2, type3;
//
//	bitwise_not(blackImage1.image_mat(),invBlackImage1);
//	bitwise_not(blackImage2.image_mat(),invBlackImage2);
//	bitwise_not(blackImage3.image_mat(),invBlackImage3);
//
//
//
//	//Fibras tipo 1 (1, 1, 0)
//	bitwise_and(invBlackImage1,invBlackImage2,type1);
//	bitwise_and(blackImage3.image_mat(),type1,type1);
//
//	namedWindow( "Tipo1",CV_WINDOW_NORMAL);// Create a window for display.
//	imshow( "Tipo1", type1);
//
//	//Fibras tipo 2 (1, 0, 1)
//	bitwise_and(invBlackImage1, blackImage2.image_mat(), type2);
//	bitwise_and(type2, invBlackImage3, type2);
//
//	namedWindow( "Tipo2",CV_WINDOW_NORMAL);// Create a window for display.
//	imshow( "Tipo2", type2);
//
//	//Fibras tipo 3 (0, 1, 1)
//	bitwise_and(blackImage1.image_mat(), invBlackImage2, type3);
//	bitwise_and(type3,invBlackImage3,type3);
//
//	namedWindow( "Tipo3",CV_WINDOW_NORMAL);// Create a window for display.
//	imshow( "Tipo3", type3);
//
//
//	channels[0] = type1;
//	channels[1] = type2;
//	channels[2] = type3;
//	merge(channels, 3, channel);
//	namedWindow( "combined",CV_WINDOW_NORMAL);// Create a window for display.
//	imshow( "combined", channel);
//    waitKey();
//    return 0;
//
//}

#include "stdafx.h"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <stdlib.h>
#include <stdio.h>

using namespace cv;

/// Global variables

int threshold_value = 0;
int threshold_type = 3;;
int const max_value = 255;
int const max_type = 4;
int const max_BINARY_value = 255;

Mat src, src_gray, dst;
char* window_name = "Threshold Demo";

char* trackbar_type = "Type: \n 0: Binary \n 1: Binary Inverted \n 2: Truncate \n 3: To Zero \n 4: To Zero Inverted";
char* trackbar_value = "Value";

/// Function headers
void Threshold_Demo( int, void* );

**
 * @function main
 */
int main( int argc, char** argv )
{

	String file1 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/4_3_1.tif";
	String file2 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/4_50_1.tif";
	String file3 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/10_3_1.tif";
  /// Load an image
  src = imread( file3, 1 );

  /// Convert the image to Gray
  cvtColor( src, src_gray, CV_RGB2GRAY );
  equalizeHist(src_gray,src_gray);
  /// Create a window to display results
  namedWindow( window_name, CV_WINDOW_AUTOSIZE );

  /// Create Trackbar to choose type of Threshold
  createTrackbar( trackbar_type,
                  window_name, &threshold_type,
                  max_type, Threshold_Demo );

  createTrackbar( trackbar_value,
                  window_name, &threshold_value,
                  max_value, Threshold_Demo );

  /// Call the function to initialize
  Threshold_Demo( 0, 0 );

  /// Wait until user finishes program
  while(true)
  {
    int c;
    c = waitKey( 20 );
    if( (char)c == 27 )
      { break; }
   }

}


**
 * @function Threshold_Demo
 */
void Threshold_Demo( int, void* )
{
  /* 0: Binary
     1: Binary Inverted
     2: Threshold Truncated
     3: Threshold to Zero
     4: Threshold to Zero Inverted
   */

  threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );

  imshow( window_name, dst );
}

