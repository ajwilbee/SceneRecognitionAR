#include "Color_Channel.h"


Color_Channel::Color_Channel()
{
}

Color_Channel::Color_Channel(Mat I){
	setImage(I);
	CreateColorPlanes();
	Mat pyr1[depth];
	Mat pyr2[depth];
	//RG first 

	MakePyramid(ColorPlanes[0], pyr1);
	MakePyramid(ColorPlanes[1], pyr2);
	Make_FeatureMap(pyr1, pyr2, FeatureMapsRG);
	MakePyramid(ColorPlanes[2], pyr1);
	MakePyramid(ColorPlanes[3], pyr2);
	Make_FeatureMap(pyr1, pyr2, FeatureMapsBY);
	MakePyramid(ColorPlanes[4], pyr1);
	Make_FeatureMap(pyr1, pyr1, FeatureMapsI);

	delete[] pyr1;
	delete[] pyr2;
}
// 2-5,2-6,3-6,3-7,4-7,4-8 layer combinations, -1 to get 0 indexing
//takes in as an argument the class variable for the feature map that it is to fill, fmap
void Color_Channel::Make_FeatureMap(Mat *p1, Mat *p2, Mat *fMap){
	
	Mat interpolated;
	for (int i = 0; i < 6; i++){
		Interpolate(p2[i], interpolated);
		fMap[i] = abs(p1[i] - interpolated);
	}

	 interpolated.deallocate();

}
void Color_Channel::CreateColorPlanes(){
	Mat colors[3];
	split(OriginalImage, colors);
	ColorPlanes[0] = colors[0] - (colors[1] + colors[2])/2;
	ColorPlanes[1] = colors[1] - (colors[0] + colors[2])/2;
	ColorPlanes[2] = colors[2] - (colors[1] + colors[0])/2;
	ColorPlanes[3] = colors[0] + colors[1] - 2 * (abs(colors[0] - colors[1])+ colors[2]);
	ColorPlanes[4] = (colors[0] + colors[1] + colors[2])/3;
	delete[] colors;
}
Mat* Color_Channel::MakePyramid(Mat I, Mat* dst){
	dst[0] = I;
	for (int x = 1; x <= depth; x++){
		pyrDown(dst[x - 1], dst[x], Size(dst[x - 1].cols / 2, dst[x - 1].rows / 2));

	}
	return dst;
}
Mat Color_Channel::getImage(){
	return OriginalImage;
}
Mat Color_Channel::Interpolate(Mat src, Mat dst){
	pyrUp(src, dst);
	return dst;
}
void Color_Channel::setImage(Mat I){
	OriginalImage = I;
}


Color_Channel::~Color_Channel()
{
	OriginalImage.deallocate();
	delete[] ColorPlanes;
	delete[] FeatureMapsRG;
	delete[] FeatureMapsBY;
	delete[] FeatureMapsI;
}
