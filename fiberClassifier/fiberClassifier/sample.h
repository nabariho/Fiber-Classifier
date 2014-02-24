#pragma once
#include "image.h"


class Sample
{
public:
	Image images[3];
	Sample(void);
	//It initializes the images' vector with the images passed as parameters
	Sample(String path_a, String path_b, String path_c);
	~Sample(void);

	void display(void);
	//It align the three images using warpAffine
	void align();
};

