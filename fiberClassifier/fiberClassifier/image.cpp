#include "stdafx.h"
#include "image.h"



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


Image::~Image(void)
{
  path = "";
  opencv_mat = NULL;

}


void Image::display(string windows_name)
{
	if(opencv_mat.data)
	{
	  namedWindow( windows_name, CV_WINDOW_AUTOSIZE );// Create a window for display.
	  imshow( windows_name, opencv_mat);
	}
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