#include "Orienation_Channel.h"


Orienation_Channel::Orienation_Channel()
{
}
Orienation_Channel::Orienation_Channel(Mat I){

}
void Orienation_Channel::Initialize(Mat I){
	OriginalImage = I;
	Mat pyr1[depth];
	
	MakePyramid(I, pyr1);
	// garbor uses first argument/8 to get the degrees, second argument is the scale and the final is the sigma
	int scale = .25;
	int sigma = 2;
	filter = CvGabor(0, .25, 2);
	Make_FeatureMap(pyr1, FeatureMaps0, F0);
	filter = CvGabor(2, .25, 2);
	Make_FeatureMap(pyr1, FeatureMaps45, F45);
	filter = CvGabor(4, .25, 2);
	Make_FeatureMap(pyr1, FeatureMaps90, F90);
	filter = CvGabor(6, .25, 2);
	Make_FeatureMap(pyr1, FeatureMaps135, F135);
	
	delete[] pyr1;


}
Mat* Orienation_Channel::MakePyramid(Mat I, Mat* dst){
	I.copyTo(dst[0]);
	for (int x = 1; x <= depth; x++){
		pyrDown(dst[x - 1], dst[x], Size(dst[x - 1].cols / 2, dst[x - 1].rows / 2));

	}
	return dst;
}
void Orienation_Channel::Make_FeatureMap(Mat *p1, Mat *fMap, Features x){
	for (int i = 0; i < depth; i++){
		IplImage ipl_img = p1->operator IplImage();
		IplImage *filtered = new IplImage();
		filter.conv_img(&ipl_img, filtered, 2);
		Mat cvmat(filtered);
		fMap[i] = cvmat;
	}
	x = Features(fMap, depth);
}
void Orienation_Channel::setImage(Mat I){
	Initialize(I);
}
Mat* Orienation_Channel::getImage(){
	return &OriginalImage;
}

Orienation_Channel::~Orienation_Channel()
{
}
