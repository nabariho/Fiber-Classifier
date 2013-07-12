#pragma once

#include <opencv2\highgui\highgui.hpp>
#include <opencv2\core\core.hpp>
#include <opencv2\imgproc\imgproc.hpp>
#include <iostream>

using namespace std;
using namespace cv;


class Image
{
  String path;
  Mat opencv_mat;
  
  public:
	Image();
    Image(String file_path);
	Image(const Image& image);
	~Image();
	//display image in a opencv window
	void display(string windows_name);
	//egdes detection in image by canny method
	void canny_edge_detector(Image* dest);
	//fiber detection by threshold
	void automatic_threshold_detector(Image* dest);

	void operator=(Image img); 
};

