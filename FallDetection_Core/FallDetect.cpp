#include "FallDetect.h"

// variables
float FallDetect::_a_b0 = 0;
float FallDetect::_angle0 = 0;
float FallDetect::_stageTime0;
float FallDetect::_humanArea = 0;
float FallDetect::_a_b1;
float FallDetect::_angle1;
float FallDetect::_timeStamp;
int FallDetect::_stage = STAGE_CMOTION;
Mat FallDetect::_element(16, 16, CV_8U, cv::Scalar(1));
Point2f FallDetect::_center0(0, 0);
Point2f FallDetect::_center1(0, 0);
Ptr< BackgroundSubtractor> FallDetect::_pMOG2 = cv::createBackgroundSubtractorMOG2(300, 32, true);
Scalar FallDetect::_color(0, 255, 0);
RotatedRect FallDetect::_rotatedRect;
Mat FallDetect::_contourImg;

bool FallDetect::_calElipseParams(RotatedRect &rotatedRect, vector<Point> contour, float &angle, float &a_b)
{
	try
	{
		rotatedRect = fitEllipse((Mat)contour);
		// Calculate angle
		angle = rotatedRect.angle;
		if (angle > 90)
		{
			angle = angle - 180;
		}
		a_b = rotatedRect.size.height / rotatedRect.size.width;
		return true;
	}
	catch (Exception e)
	{
		return false;
	}
}

void FallDetect::fallDetect(Mat& resizedFrame, Mat& mhi, Mat& binaryImg, char* notiURL, int minHumanRect)
{
	// Blur
	blur(resizedFrame, resizedFrame, Size(4, 4));

	// Background subtraction
	_pMOG2->apply(resizedFrame, binaryImg, -1);
	// Calculate MHI
	float sumHist = 0;
	MHIProcess::updateMHI(resizedFrame, mhi, 30, sumHist);

	// Process for foreground image- Delete 1 point
	morphologyEx(binaryImg, binaryImg, CV_MOP_CLOSE, _element);
	// Shadow Delete Shadow
	threshold(binaryImg, binaryImg, 128, 255, CV_THRESH_BINARY);

	// Find contour- Retrieve the external contours, all pixels of each contours
	vector< vector< Point> > contours;
	_contourImg = binaryImg.clone();
	findContours(_contourImg, contours, CV_RETR_EXTERNAL, CV_CHAIN_APPROX_NONE);

	// Detect fall based on contours
	if (contours.size() > 0)
	{
		// Detect human by area of contour
		int theLargestId = 0;
		int theLargestRect = 0;
		for (int i = 0; i < contours.size(); i++)
		{
			int a = boundingRect(contours[i]).area();
			if (a > theLargestRect && contours[i].size() > 5)
			{
				theLargestId = i;
				theLargestRect = a;
			}
		}
		if (theLargestRect > AREA_MAX || theLargestRect <= minHumanRect)
		{
			theLargestRect = 0;
		}
		if (theLargestRect > 0 /*|| stage == STAGE_DY*/)	// Found a human in frame
		{
			switch (_stage)
			{
			case STAGE_CMOTION:
				// Drawing bouding rect
				rectangle(resizedFrame, boundingRect(contours[theLargestId]), _color, 4);
				// Calculate cMotion= sumHist / (contourArea(contours[theLargestId]))
				if (sumHist / (contourArea(contours[theLargestId])) > THRESHOLD_CMOTION){
					if (!_calElipseParams(_rotatedRect, contours[theLargestId], _angle0, _a_b0))
					{
						return;
					}
					_stageTime0 = (float)clock() / CLOCKS_PER_SEC;
					_stage = STAGE_D0;
				}
				break;
			case STAGE_D0:
				if (_calElipseParams(_rotatedRect, contours[theLargestId], _angle1, _a_b1))
				{
					ellipse(resizedFrame, _rotatedRect, _color, 4); // Drawing bouding rect
					if (abs(_angle1 - _angle0) > THRESHOLD_D0 || abs(_a_b0 - _a_b1) > THRESHOLD_DA_B)
					{
						//center0 = rotatedRect.center;
						_stageTime0 = (float)clock() / CLOCKS_PER_SEC;
						_humanArea = contourArea(contours[theLargestId]);
						_stage = STAGE_DY;
						return;
					}
				}
				_timeStamp = (float)clock() / CLOCKS_PER_SEC;
				// Calculate dT=t1-t0
				if (_timeStamp - _stageTime0 > DURATION_D0)
				{
					// Wrong alarm, back to cMotion stage
					_stage = STAGE_CMOTION;
				}
				break;
			case STAGE_DY:
				if (_calElipseParams(_rotatedRect, contours[theLargestId], _angle1, _a_b1))
				{
					_center1 = _rotatedRect.center;
				}
				rectangle(resizedFrame, boundingRect(contours[theLargestId]), Scalar(0, 0, 255), 4);
				if (sumHist / _humanArea < THRESHOLD_CMOTION_DY && abs(_center1.x - _center0.x) < THRESHOLD_DX && abs(_center1.y - _center0.y) < THRESHOLD_DY)
				{
					// Send notification
					char data[] = "";
					struct curl_slist *hs = NULL;
					bool result = CurlUtils::curlURLWithData(notiURL, hs, data, false);

					_stage = STAGE_CMOTION;

					break;
				}
				_center0 = _center1;
				_timeStamp = (float)clock() / CLOCKS_PER_SEC;
				// Calculate dT=t1-t0
				if (_timeStamp - _stageTime0 > DURATION_DY)
				{
					// Wrong alarm, back to cMotion stage
					_stage = STAGE_CMOTION;
				}
				break;
			default:
				_stage = STAGE_CMOTION;
			}
		}
	}
}