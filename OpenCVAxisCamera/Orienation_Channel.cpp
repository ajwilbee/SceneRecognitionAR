#include "Orienation_Channel.h"


Orienation_Channel::Orienation_Channel()
{
	createSobels();
}
Orienation_Channel::Orienation_Channel(Mat I){
	createSobels();
	OriginalImage = I;
	Initialize(I);
}
void Orienation_Channel::Initialize(Mat I){
	OriginalImage = I;
	Mat pyr1[depth];
	
	MakePyramid(I, pyr1);
	// garbor uses first argument/8 to get the degrees, second argument is the scale and the final is the sigma
	int scale = .25;
	int sigma = 2;
	Mat im;
	Mat out;
	

	for (int i = 0; i < depth; i++){
		im = pyr1[i];
		out = FeatureMaps0[i];
		filter2D(im, out, im.depth(), horz);
	}
	for (int i = 0; i < depth; i++){
		im = pyr1[i];
		filter2D(im, FeatureMaps45[i], im.depth(), d45);
	}
	for (int i = 0; i < depth; i++){
		im = pyr1[i];
		filter2D(im, FeatureMaps90[i], im.depth(), vert);
	}
	for (int i = 0; i < depth; i++){
		im = pyr1[i];
		filter2D(im, FeatureMaps135[i], im.depth(), d135);
	}
	//Make_FeatureMap(pyr1, FeatureMaps0, &horz,&F0);
	//Make_FeatureMap(pyr1, FeatureMaps45, &d45, &F45);
	//Make_FeatureMap(pyr1, FeatureMaps90, &vert, &F90);
	//Make_FeatureMap(pyr1, FeatureMaps135, &d135, &F135);
	
	//delete[] pyr1;


}
void Orienation_Channel::MakePyramid(Mat I, Mat* dst){
	I.copyTo(dst[0]);
	for (int x = 1; x < depth; x++){
		pyrDown(dst[x - 1], dst[x], Size(dst[x - 1].cols / 2, dst[x - 1].rows / 2));

	}
}
void Orienation_Channel::Make_FeatureMap(Mat p1[], Mat fMap[], Mat *Filter, OrientationFeature *x){
	Mat cvmat;
	Mat Ftr = *Filter;
	Mat im;
	
	x = &OrientationFeature(fMap);
	cvmat.release();
}
void Orienation_Channel::setImage(Mat I){
	Initialize(I);
}
Mat* Orienation_Channel::getImage(){
	return &OriginalImage;
}

void Orienation_Channel::createSobels(){

	horz.at<double>(0, 0) = 1;
	horz.at<double>(0, 1) = 2;
	horz.at<double>(0, 2) = 1;
	horz.at<double>(1, 0) = 0;
	horz.at<double>(1, 1) = 0;
	horz.at<double>(1, 2) = 0;
	horz.at<double>(2, 0) = -1;
	horz.at<double>(2, 1) = -2;
	horz.at<double>(2, 2) = -1;

	vert.at<double>(0, 0) = 1;
	vert.at<double>(0, 1) = 0;
	vert.at<double>(0, 2) = -1;
	vert.at<double>(1, 0) = 2;
	vert.at<double>(1, 1) = 0;
	vert.at<double>(1, 2) = -2;
	vert.at<double>(2, 0) = 1;
	vert.at<double>(2, 1) = 0;
	vert.at<double>(2, 2) = -1;


	d135.at<double>(0, 0) = 2;
	d135.at<double>(0, 1) = 1;
	d135.at<double>(0, 2) = 0;
	d135.at<double>(1, 0) = 1;
	d135.at<double>(1, 1) = 0;
	d135.at<double>(1, 2) = -1;
	d135.at<double>(2, 0) = 0;
	d135.at<double>(2, 1) = -1;
	d135.at<double>(2, 2) = -2;

	d45.at<double>(0, 0) = 0;
	d45.at<double>(0, 1) = -1;
	d45.at<double>(0, 2) = -2;
	d45.at<double>(1, 0) = 1;
	d45.at<double>(1, 1) = 0;
	d45.at<double>(1, 2) = -1;
	d45.at<double>(2, 0) = 2;
	d45.at<double>(2, 1) = 1;
	d45.at<double>(2, 2) = 0;

	//d45.at<double>(0, 0) = 1;
	//d45.at<double>(0, 1) = 1;
	//d45.at<double>(0, 2) = 1;
	//d45.at<double>(1, 0) = 1;
	//d45.at<double>(1, 1) = 1;
	//d45.at<double>(1, 2) = 1;
	//d45.at<double>(2, 0) = 1;
	//d45.at<double>(2, 1) = 1;
	//d45.at<double>(2, 2) = 1;
}


Orienation_Channel::~Orienation_Channel()
{
	//delete &F0;
	//delete &F90;
	//delete &F45;
	//delete &F135;
}
