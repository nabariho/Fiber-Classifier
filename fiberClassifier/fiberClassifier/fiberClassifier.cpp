// fiberClassifier.cpp: define el punto de entrada de la aplicación de consola.
//
#include "stdafx.h"
#include "sample.h"
#include "image.h"


int _tmain(int argc, _TCHAR* argv[])
{
	String file = "C:/Users/nabar/Documents/GitHub/Fiber-Classifier/fiberClassifier/images/fibras_1.png";
	//Image my_image(file);
	//my_image.display("image1");
	Sample my_sample(file,file,file);
	my_sample.display();
	waitKey(0);
	return 0;
}
