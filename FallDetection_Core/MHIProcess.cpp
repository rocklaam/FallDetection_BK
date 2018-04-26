#include "MHIProcess.h"

//Properties
vector<Mat> MHIProcess::buf = vector<Mat>(2);
int MHIProcess::_last = 0;
Mat MHIProcess::_mhi = Mat();

//Methods
void MHIProcess::updateMHI(const Mat& img, Mat& dst, int diff_threshold, double& sumHist){
	double timestamp = (double)clock() / CLOCKS_PER_SEC; // get current time in seconds
	Size size = img.size();
	int idx1 = _last;
	Rect comp_rect;
	// allocate images at the beginning or reallocate them if the frame size is changed
	if (_mhi.size() != size)
	{
		_mhi = Mat::zeros(size, CV_32F);
		buf[0] = Mat::zeros(size, CV_8U);
		buf[1] = Mat::zeros(size, CV_8U);
	}

	cvtColor(img, buf[_last], COLOR_BGR2GRAY); // convert frame to grayscale

	int idx2 = (_last + 1) % 2; // index of (_last - (N-1))th frame
	_last = idx2;

	Mat silh = buf[idx2];
	absdiff(buf[idx1], buf[idx2], silh); // get difference between frames

	threshold(silh, silh, diff_threshold, 1, THRESH_BINARY); // and threshold it
	updateMotionHistory(silh, _mhi, timestamp, MHI_DURATION); // update MHI
	_mhi.convertTo(dst, CV_8U, 255. / MHI_DURATION, (MHI_DURATION - timestamp)*255. / MHI_DURATION);// convert MHI to 8u image

	// calculate sumHist
	for (int i = 0; i < dst.rows; i++){
		for (int j = 0; j < dst.cols; j++){
			sumHist += dst.at<uchar>(i, j);
		}
	}
}