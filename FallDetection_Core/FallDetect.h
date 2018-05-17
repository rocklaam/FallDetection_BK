#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>

#include "CurlUtils.h"
#include "MHIProcess.h"

#ifndef FALLDETECT
#define FALLDETECT

class FallDetect
{
public:
	static void fallDetect(Mat& resizedFrame, Mat& mhi, Mat& binaryImg, char* notiURL, int minHumanRect = 3000);
private:
	// variables
	static float _a_b0;									// params of ellipse to calculate d0 and dA_B
	static float _angle0;
	static float _stageTime0;							// the starting time for each stage, to calculate dT
	static float _humanArea;							// param to recog the last area of human after fall
	static float _a_b1, _angle1, _timeStamp;
	static int _stage;									// stage of algorithm
	static Mat _contourImg;
	static Mat _element;								// morphology element
	static Point2f _center0;							// point to regconize to last center of body after fall
	static Point2f _center1;
	// MOG2 Background subtractor
	static Ptr< BackgroundSubtractor> _pMOG2;
	static Scalar _color;								// color
	static RotatedRect _rotatedRect;					// rectangle to determine elipse

	static bool _calElipseParams(RotatedRect &rotatedRect, vector<Point> contour, float &angle, float &a_b);
};

#endif