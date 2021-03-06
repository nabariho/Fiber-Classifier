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
  int threshold_value;
  public:

	Image();
    Image(String file_path, int threshold);
	~Image();
	Image(const Image& image);
	void operator=(Image img); 

	//calculate inverse
	void inverse(Image* dest);

	//display image in a opencv window
	void display();
	void display_off();

	string get_path();
	void set_path(string path);

	//egdes detection in image by canny method
	void canny_edge_detector(Image* dest);
	
	//fiber detection by threshold
	void automatic_threshold_detector(Image* dest);	
	void threshold_detector(Image* dest, int threshold_type);

	//contours detections
	void get_contours(Image* dest);
	
	//get the white fibers in image
	Image get_white();
    //get the black fibers in image
	Image get_black();

	//copy image.opencv_mat to Mat  <-- Es realmente necesaria esta funci�n?
	Mat image_mat();
	void set_threshold_value(int threshold);
	//update opencv_mat with new math
	void update_image(Mat new_mat);



};

