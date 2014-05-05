#include "Color_Channel.h"


Color_Channel::Color_Channel()
{
}

Color_Channel::Color_Channel(Mat I){
	Initialize(I);
}

void Color_Channel::Initialize(Mat I){
	I.copyTo(OriginalImage);
	CreateColorPlanes();
	Mat pyr1[depth];
	Mat pyr2[depth];
	//RG first 
	//BY
	//I
	
	//ColorPlanes[0].copyTo(pyr1[0]);
	//for (int x = 1; x < depth; x++){
	//	pyrDown(pyr1[x - 1], pyr1[x], Size(pyr1[x - 1].cols / 2, pyr1[x - 1].rows / 2));

	//}
	MakePyramid(ColorPlanes[0], pyr1);
	MakePyramid(ColorPlanes[1], pyr2);
	Mat interpolated;
	for (int i = 0; i < 6; i++){
		Interpolate(pyr2[i], interpolated);
		FeatureMapsRG[i] = abs(pyr1[i] - interpolated);
	}
	RG = ColorFeature(FeatureMapsRG);
	MakePyramid(ColorPlanes[2], pyr1);
	MakePyramid(ColorPlanes[3], pyr2);
	for (int i = 0; i < 6; i++){
		Interpolate(pyr2[i], interpolated);
		FeatureMapsBY[i] = abs(pyr1[i] - interpolated);
	}
	BY = ColorFeature(FeatureMapsBY);
	MakePyramid(ColorPlanes[4], pyr1);
	for (int i = 0; i < 6; i++){
		Interpolate(pyr2[i], interpolated);
		FeatureMapsI[i] = abs(pyr1[i] - interpolated);
	}
	Intensity = ColorFeature(FeatureMapsI);
	for (int i = 0; i < depth; i++){
		 pyr1[i].release();
		 pyr2[i].release();

	}
}

// 2-5,2-6,3-6,3-7,4-7,4-8 layer combinations, -1 to get 0 indexing
//takes in as an argument the class variable for the feature map that it is to fill, fmap
void Color_Channel::Make_FeatureMap(Mat *p1, Mat *p2, Mat *fMap, ColorFeature *x){
	
	Mat interpolated;
	for (int i = 0; i < 6; i++){
		Interpolate(p2[i], interpolated);
		fMap[i] = abs(p1[i] - interpolated);
	}
	x = &ColorFeature(fMap); 
	//interpolated.release();
}
void Color_Channel::CreateColorPlanes(){
	Mat colors[3];
	//allocate seperatly?
	split(OriginalImage, colors);
	ColorPlanes[0] = colors[0] - (colors[1] + colors[2])/2;
	ColorPlanes[1] = colors[1] - (colors[0] + colors[2])/2;
	ColorPlanes[2] = colors[2] - (colors[1] + colors[0])/2;
	ColorPlanes[3] = colors[0] + colors[1] - 2 * (abs(colors[0] - colors[1])+ colors[2]);
	ColorPlanes[4] = (colors[0] + colors[1] + colors[2])/3;
	//dealocate seperatly?
	//delete colors;
}
void Color_Channel::MakePyramid(Mat I, Mat* dst){
	I.copyTo(dst[0]);
	for (int x = 1; x < depth; x++){
		pyrDown(dst[x - 1], dst[x], Size(dst[x - 1].cols / 2, dst[x - 1].rows / 2));

	}
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
	Initialize(I);
}


Color_Channel::~Color_Channel()
{

	// killing the original image here will ruin everything
	//OriginalImage.deallocate();
//dealocate seperatly?
///	delete[] ColorPlanes;
//	delete[] FeatureMapsRG;
//	delete[] FeatureMapsBY;
//	delete[] FeatureMapsI;

//	delete &RG;
//	delete &BY;
//	delete &Intensity;
}
