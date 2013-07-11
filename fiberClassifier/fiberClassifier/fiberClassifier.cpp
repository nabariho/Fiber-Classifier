// fiberClassifier.cpp: define el punto de entrada de la aplicación de consola.
//
#include "stdafx.h"
#include "image.h"


int _tmain(int argc, _TCHAR* argv[])
{
	String file = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/fibras_1.png";
	Image image(file);
	Image image_threshold;
	image.automatic_threshold_detector(&image_threshold);
	image.display("ventana1");
	image_threshold.display("ventana2");
	waitKey(0);
	return 0;
}
