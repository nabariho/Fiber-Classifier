#include "stdafx.h"
#include "image.h"
#include "Utils.h"



Image::Image()
{
  path = "";
  opencv_mat = NULL;
}
//constructor by  path
Image::Image(String file_path)
{
  try{
	path = file_path;
	opencv_mat = imread(path);
	//We always work with gray images
	cvtColor(opencv_mat,opencv_mat,CV_BGR2GRAY);
	//reduce noise
	blur(opencv_mat,opencv_mat,Size(3,3));
  }catch(const char* msg){
	  cerr << "File can't be open" << endl;
  }
}

Image::Image(const Image& image)
{
	path = image.path;
	image.opencv_mat.copyTo(opencv_mat);
}

Image::~Image(void)
{
  path = "";
  opencv_mat = NULL;

}


string Image::get_path(){
	return path;
}

void Image::display()
{
	if(opencv_mat.data)
	{
		namedWindow( path,NULL);// Create a window for display.
	  imshow( path, opencv_mat);
	}
}

void Image::display_off(){
	destroyWindow(path);
}

void Image::canny_edge_detector(Image* dest)
{
  if(opencv_mat.data)
  {
    dest ->opencv_mat.create(opencv_mat.size(),opencv_mat.type());
    Canny(opencv_mat,dest->opencv_mat,10,10);
  }
}

void Image::automatic_threshold_detector(Image* dest)
{
	if(opencv_mat.data)
	{
	  dest ->opencv_mat.create(opencv_mat.size(),opencv_mat.type());
	  adaptiveThreshold(opencv_mat, dest->opencv_mat,255,CV_ADAPTIVE_THRESH_MEAN_C,CV_THRESH_BINARY,3,5 );
	}

}

void Image::threshold_detector(Image* dest, int threshold_type,int threshold_value){
	dest ->opencv_mat.create(opencv_mat.size(),opencv_mat.type());
	threshold(opencv_mat, dest->opencv_mat,threshold_value,MAX_BINARY_VALUE,threshold_type);
}

void Image::get_contours(Image* dest){
	
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	RNG rng(12345);
	Mat image_copy;
	opencv_mat.copyTo(image_copy);

	findContours(image_copy, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_SIMPLE, Point(0, 0));

	/// Draw contours
	dest->opencv_mat = Mat::zeros(opencv_mat.size(), CV_8UC3);
	for( int i = 0; i< contours.size(); i++ )
     {
	  if (contourArea(contours[i]) > 100){
		 Scalar color = Scalar(rng.uniform(0, 255), rng.uniform(0,255), rng.uniform(0,255));
	     drawContours(dest->opencv_mat, contours, i, color, 2, 8, hierarchy, 0, Point());
		 
	  }
	  //dest->display("yo que se");
	  //waitKey(0);
     }
}
 
void Image::operator= (Image img)
{
	path = img.path;
	img.opencv_mat.copyTo(opencv_mat);
}

Image Image::get_black(){
	Image black;
	threshold_detector(&black, BINARY_THRESHOLD,BLACK_THRESHOLD);
	return black;

}
Image Image::get_white(){
    Image white, inv;
	//bitwise_not(opencv_mat,inv.opencv_mat);
	threshold_detector(&white, INV_BINARY_THRESHOLD,WHITE_THRESHOLD);
	return white;
}

void Image::inverse(Image* dest){
	bitwise_not(opencv_mat, dest->opencv_mat);
}

Mat Image::image_mat(){
	return opencv_mat;
}

void Image::update_image(Mat new_mat){
	new_mat.copyTo(opencv_mat);
}