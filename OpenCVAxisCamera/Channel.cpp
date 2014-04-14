#include "Channel.h"
static const int depth = 8;

Mat pyramid[depth];
Mat OriginalImage;
Mat FilteredFeatures[depth];
Channel::Channel()
{


}
Channel::Channel(Mat I)
{
	MakePyramid(I);

}
void Channel::MakePyramid(Mat I){

	pyramid[0] = I;
	for (int x = 1; x <= depth; x++){
		pyrDown(pyramid[x - 1], pyramid[x], Size(pyramid[x - 1].cols / 2, pyramid[x - 1].rows / 2));

	}
}// will make an spatial pyramid of indicated depth using buildPyramid or somthing like it

Mat Channel::getImage(){

	return pyramid[0];

}

void Channel::setImage(Mat I){

	MakePyramid(I);


}

Mat* Channel::getPyramid(){

	return pyramid;
}
Mat* Filter(Mat seed){
	//filter2D();
	return FilteredFeatures;
}

Channel::~Channel()
{
	delete[] pyramid;
	delete[] FilteredFeatures;
}

