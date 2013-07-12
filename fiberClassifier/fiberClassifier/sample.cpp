#include "stdafx.h"
#include "sample.h"


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
	images[0].display("image1");
	images[1].display("image2");
	images[2].display("image3");
}

void Sample::images_align()
{
	images[1].display;
}

void points_for_aling(int event, int x, int y, int flags)
{
	int coordenates = 0;
	switch ( event ) {
	  case CV_EVENT_LBUTTONDOWN:
		points[coordenates].x = x;
		points[coordenates].y = y;
		coordenates ++;
		if (coordenates == 3)break;
    }
};