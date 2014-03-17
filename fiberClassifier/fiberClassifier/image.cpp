#include "stdafx.h"
#include "image.h"
#include "Utils.h"



Image::Image()
{
  path = "";
  opencv_mat = NULL;
}
//constructor by  path
Image::Image(String file_path, int threshold)
{
  try{
	path = file_path;
	opencv_mat = imread(path);
	threshold_value = threshold;
	//We always work with gray images
	cvtColor(opencv_mat,opencv_mat,CV_BGR2GRAY);
	//reduce noise
	blur(opencv_mat,opencv_mat,Size(3,3));
	equalizeHist(opencv_mat,opencv_mat);

  }catch(const char* msg){
	  cerr << "File can't be open" << endl;
  }
}

Image::Image(const Image& image)
{
	path = image.path;
	image.opencv_mat.copyTo(opencv_mat);
	threshold_value = image.threshold_value;
}

Image::~Image(void)
{
  path = "";
  opencv_mat = NULL;

}

void Image::set_threshold_value(int threshold){
	threshold_value = threshold;
}
string Image::get_path(){
	return path;
}
void Image::set_path(string new_path){
	path = new_path;
}

void Image::display()
{
	if(opencv_mat.data)
	{
	  namedWindow( path,CV_WINDOW_NORMAL);// Create a window for display.
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

void Image::threshold_detector(Image* dest, int threshold_type){
	Mat aux;
	dest ->opencv_mat.create(opencv_mat.size(),opencv_mat.type());
	equalizeHist(opencv_mat,aux);
	//threshold( src_gray, dst, threshold_value, max_BINARY_value,threshold_type );
	threshold(aux, dest->opencv_mat, threshold_value,MAX_BINARY_VALUE,threshold_type);
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
	     drawContours(dest->opencv_mat, contours, i, 255, 2, 8, hierarchy, 0, Point());
		 
	  }
     }
	dest->set_path("contornos");
}
 
void Image::operator= (Image img)
{
	path = img.path;
	img.opencv_mat.copyTo(opencv_mat);
	threshold_value = img.threshold_value;
}

Image Image::get_black(){
	Image black;
	black.set_path("negras");
	threshold_detector(&black, BINARY_THRESHOLD);
	return black;
}
Image Image::get_white(){
    Image white, black,all;
	Mat aux;
	white.set_path("blancas");
	black.set_path("negras");
	all.set_path("all");

	//threshold_detector(&black,BINARY_THRESHOLD,BLACK_THRESHOLD);
	//threshold_detector(&all, BINARY_THRESHOLD,WHITE_THRESHOLD);
	////bitwise_or(all.image_mat(),black.image_mat(),aux);
	//absdiff(all.image_mat(),black.image_mat(),aux);
	//bitwise_not(aux,aux);
	////equalizeHist(aux,aux);
	//white.update_image(aux);

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