#include <opencv2/objdetect.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>

#include <iostream>
#include <iomanip>

using namespace cv;
using namespace std;

#ifndef DETECTOR
#define DETECTOR

class Detector
{
public:
	Detector::Detector() : m(Default), hog(), hog_d(Size(48, 96), Size(16, 16), Size(8, 8), Size(8, 8), 9)
	{
		hog.setSVMDetector(HOGDescriptor::getDefaultPeopleDetector());
		hog_d.setSVMDetector(HOGDescriptor::getDaimlerPeopleDetector());
	};
	void adjustRect(Rect & r) const;
	vector<Rect> detect(InputArray bluredImg);
	void calculateHuman(Mat & bluredImg, int & area);

private:
	enum Mode { Default, Daimler } m;
	HOGDescriptor hog, hog_d;
};

#endif