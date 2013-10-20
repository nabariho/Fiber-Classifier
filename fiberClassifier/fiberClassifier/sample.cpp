#include "stdafx.h"
#include "Utils.h"
#include "sample.h"
#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>
//aling helpers

#include <vector>
#include <fstream>
#include <list>
#include <sstream>
#include <iomanip>
#include <iostream>

using namespace std;
using namespace cv;


//aling variables
int i_orig = 0;
vector <Point2f> puntosOrig(3);
int i_modif = 0;
vector <Point2f> puntosModif(3);
Mat img1, img2;
string window_name_1, window_name_2;

//private functions

void my_mouse_callback( int event, int x, int y, int flags, void* param )
{

	if (i_orig > 2){
        return;
	}
    switch ( event ) {
    case CV_EVENT_LBUTTONDOWN:
        puntosOrig[i_orig].x = x;
        puntosOrig[i_orig].y = y;
        circle(img1, puntosOrig[i_orig], 3, Scalar(255, 255, 255), 1, 8, 0);
	    imshow(window_name_1, img1);
	    cout << "Click en: " << puntosOrig[i_orig] << endl;
        i_orig++;
	break;
    }
}

void my_mouse_callback2( int event, int x, int y, int flags, void* param )
{

	    if (i_modif > 2){
			return;
		}

    switch ( event ) {
    case CV_EVENT_LBUTTONDOWN:
			cout << "nombre de la ventana 2: " << window_name_2 << endl;

        puntosModif[i_modif].x = x;
        puntosModif[i_modif].y = y;
        cv::circle(img2, puntosModif[i_modif], 3, cv::Scalar(255, 255, 255), 1, 8, 0);
	    cv::imshow(window_name_2, img2);
	    cv::waitKey(10);
	
	cout << "Click en: " << puntosModif[i_modif] << endl;

        i_modif++;

	break;
    }
}




//Public functions

Sample::Sample(void)
{
}

Sample::Sample(String path_a, String path_b, String path_c)
{
	
	images[0] = Image(path_a);
	images[1] = Image(path_b);
	images[2] = Image(path_c);
}

Sample::~Sample(void)
{
}

void Sample::display()
{
	images[0].display();
	images[1].display();
	images[2].display();
}



void Sample::align()
{
	images[0].display();
	images[1].display();
	//images[2].display("Imagen_Original_3");

	images[0].image_mat().copyTo(img1);
	images[1].image_mat().copyTo(img2);
	


	window_name_1 = images[0].get_path();
	setMouseCallback(images[0].get_path(), my_mouse_callback);

	window_name_2 = images[1].get_path();
    setMouseCallback(images[1].get_path(), my_mouse_callback2); 
    waitKey(0);

    // calcula la matriz de transformacion
    Mat matrizTransf;
    matrizTransf = getAffineTransform(puntosModif,puntosOrig); 
    // aplica la transformacion calculada
    Mat nueva;
    warpAffine(images[1].image_mat(), nueva, matrizTransf, img1.size());
	//actualizamos la primera imagen alineada
	images[1].update_image(nueva);

	
	images[1].display_off();
	i_orig = 0;
	i_modif= 0;
	images[2].display();
	images[2].image_mat().copyTo(img2);
	

	window_name_2 = images[2].get_path();
    setMouseCallback(images[2].get_path(), my_mouse_callback2); 
	waitKey(0);
	
	matrizTransf = getAffineTransform(puntosModif,puntosOrig);
	warpAffine(images[2].image_mat(), nueva, matrizTransf, img2.size());
	images[2].update_image(nueva);
    
}

