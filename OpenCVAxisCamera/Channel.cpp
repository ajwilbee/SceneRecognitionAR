#include "Channel.h"
static const int depth = 8;


Mat OriginalImage;
Mat FilteredFeatures[depth];
Channel::Channel()
{


}
Channel::Channel(Mat I)
{
	setImage(I);
}
Mat* Channel::MakePyramid(Mat I){
	Mat pyramid[depth];
	pyramid[0] = I;
	for (int x = 1; x <= depth; x++){
		pyrDown(pyramid[x - 1], pyramid[x], Size(pyramid[x - 1].cols / 2, pyramid[x - 1].rows / 2));

	}
	return pyramid;
}// will make an spatial pyramid of indicated depth using buildPyramid or somthing like it

Mat Channel::getImage(){

	return OriginalImage;

}

void Channel::setImage(Mat I){

	OriginalImage = I;


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
	delete[] FilteredFeatures;
}

