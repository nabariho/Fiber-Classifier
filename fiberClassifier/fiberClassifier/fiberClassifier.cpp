// fiberClassifier.cpp: define el punto de entrada de la aplicación de consola.
//
#include "stdafx.h"
#include "sample.h"
#include "image.h"

////////
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;
using namespace std;



int _tmain(int argc, _TCHAR* argv[])
{
	String file1 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/pruebas_alineacion/flor-1.jpg";
	String file2 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/pruebas_alineacion/flor-1-rotada.jpg";
	String file3 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/pruebas_alineacion/flor-1-despl.jpg";

    //String file1 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/4_3_1.png";
	//String file2 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/4_50_1.png";
	//String file3 = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/10_3_1.png";

	Sample my_sample(file1,file2,file3);
	my_sample.align();
	my_sample.display();

	//Image src(file), treshold,contours, negras, blancas;

	//negras = src.get_black();
	//blancas = src.get_white();
	//src.display("fuente");
	//negras.display("negras");
	//blancas.display("blancas");
	waitKey(0);
	return 0;

}


