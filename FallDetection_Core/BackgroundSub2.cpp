//#include "curl/curl.h" // has to go before opencv headers
////#include"stdafx.h"
//#include<vector>
//#include<iostream>
//#include<opencv2/optflow.hpp>
//#include<opencv2/opencv.hpp>
//#include<opencv2/core/core.hpp>
//#include<opencv2/imgproc/imgproc.hpp>
//#include<opencv2/highgui/highgui.hpp>
//
//using namespace std;
//using namespace cv;
//using namespace cv::motempl;
//
////curl writefunction to be passed as a parameter
//// we can't ever expect to get the whole image in one piece,
//// every router / hub is entitled to fragment it into parts
//// (like 1-8k at a time),
//// so insert the part at the end of our stream.
//size_t write_data(char *ptr, size_t size, size_t nmemb, void *userdata)
//{
//	vector<uchar> *stream = (vector<uchar>*)userdata;
//	size_t count = size * nmemb;
//	stream->insert(stream->end(), ptr, ptr + count);
//	return count;
//}
//
//// various tracking parameters (in seconds)
//const double MHI_DURATION = 0.5;
//const double MAX_TIME_DELTA = 0.5;
//const double MIN_TIME_DELTA = 0.05;
//
//// ring image buffer
//vector<Mat> buf;
//int last = 0;
//
//// temporary images
//Mat mhi, orient, mask, segmask, zplane;
//vector<Rect> regions = vector<Rect>();
//
////function to retrieve the image as cv::Mat data type
//Mat curlImg(const char *img_url, int timeout = 10)
//{
//	vector<uchar> stream;
//	CURL *curl = curl_easy_init();
//	curl_easy_setopt(curl, CURLOPT_URL, img_url); //the img url
//	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data); // pass the writefunction
//	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &stream); // pass the stream ptr to the writefunction
//	curl_easy_setopt(curl, CURLOPT_TIMEOUT, timeout); // timeout if curl_easy hangs, 
//	struct curl_slist *hs = NULL;
//	hs = curl_slist_append(hs, "Content-Type: image/jpeg");
//	curl_easy_setopt(curl, CURLOPT_HTTPHEADER, hs);
//	CURLcode res = curl_easy_perform(curl); // start curl
//	curl_easy_cleanup(curl); // cleanup
//	return imdecode(stream, -1); // 'keep-as-is'
//}
//
//static void  update_mhi(const Mat& img, Mat& dst, int diff_threshold, double& sumHist)
//{
//	double timestamp = (double)clock() / CLOCKS_PER_SEC; // get current time in seconds
//	//cout << timestamp << endl;
//	Size size = img.size();
//	int i, idx1 = last;
//	Rect comp_rect;
//
//	// allocate images at the beginning or
//	// reallocate them if the frame size is changed
//	if (mhi.size() != size)
//	{
//		mhi = Mat::zeros(size, CV_32F);
//		zplane = Mat::zeros(size, CV_8U);
//
//		buf[0] = Mat::zeros(size, CV_8U);
//		buf[1] = Mat::zeros(size, CV_8U);
//	}
//
//	//cvtColor(img, buf[last], COLOR_BGR2GRAY); // convert frame to grayscale
//	buf[last] = img;
//
//	int idx2 = (last + 1) % 2; // index of (last - (N-1))th frame
//	last = idx2;
//
//	Mat silh = buf[idx2];
//	absdiff(buf[idx1], buf[idx2], silh); // get difference between frames
//
//	threshold(silh, silh, diff_threshold, 1, THRESH_BINARY); // and threshold it
//	updateMotionHistory(silh, mhi, timestamp, MHI_DURATION); // update MHI
//	// Calculata sumHist
//	for (int i = 0; i < mhi.rows; i++){
//		for (int j = 0; j < mhi.cols; j++){
//			sumHist += mhi.at<float>(i, j);
//		}
//	}
//	float check = mhi.at<float>(3, 3);
//	// convert MHI to blue 8u image
//	mhi.convertTo(mask, CV_8U, 255. / MHI_DURATION, (MHI_DURATION - timestamp)*255. / MHI_DURATION);
//	Mat planes[] = { mask, zplane, zplane };
//	merge(planes, 3, dst);
//}
//
//int main(int argc, char *argv[])
//{
//	cv::Mat mhi;
//	cv::Mat frame;
//	cv::Mat fg;
//	cv::Mat blurred;
//	cv::Mat thresholded;
//	cv::Mat thresholded2;
//	cv::Mat result;
//	cv::Mat bgmodel;
//	cv::namedWindow("Frame");
//	cv::namedWindow("Background Model");
//	cv::namedWindow("MHI image");
//	//cv::VideoCapture cap(0);
//	buf.resize(2);
//	Ptr<BackgroundSubtractorMOG2> bgs = createBackgroundSubtractorMOG2(60, 15, true);
//	bool isFall = false;
//	std::vector<std::vector<cv::Point>> contours;
//	VideoCapture cap("E:/BachKhoaUni/DoAn/ThesisProject_2018/FallDetection_BK/Private/Office/video (5).avi");
//	//VideoCapture cap(0);
//	if (!cap.isOpened()){
//	return -1;
//	}
//	while (!isFall)
//	{
//		//frame = curlImg("http://192.168.0.222:8888/snapshot.cgi?loginuse=admin&loginpas=admin");
//		cap >> frame;
//		if (frame.empty()){
//		break;
//		}
//		double sumHist = 0;
//		cv::blur(frame, blurred, cv::Size(10, 10));
//		cvtColor(blurred, blurred, COLOR_BGR2GRAY);
//		update_mhi(blurred, mhi, 30, sumHist);
//		//equalizeHist(blurred, blurred);
//		bgs->apply(blurred, fg, -1);
//		bgs->getBackgroundImage(bgmodel);
//
//		cv::threshold(fg, thresholded, 70.0f, 255, CV_THRESH_BINARY);
//		cv::threshold(fg, thresholded2, 70.0f, 255, CV_THRESH_BINARY);
//
//		cv::Mat element50(50, 50, CV_8U, cv::Scalar(1));
//		cv::morphologyEx(thresholded, thresholded, cv::MORPH_CLOSE, element50);
//		cv::morphologyEx(thresholded2, thresholded2, cv::MORPH_CLOSE, element50);
//
//		cv::findContours(thresholded, contours, RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
//		cv::cvtColor(thresholded2, result, CV_GRAY2RGB);
//
//		int cmin = 50;
//		int cmax = 10000;
//
//		//std::vector<std::vector<cv::Point>>::iterator itc = contours.begin();
//
//		//while (itc != contours.end()) {
//
//		//	/*if (itc->size() < cmin || itc->size() > cmax){
//		//		itc = contours.erase(itc);
//		//		}*/
//		//	//else{
//		//	cout << sumHist / contourArea(*itc) << endl;
//		//	if (sumHist / contourArea(*itc) >= 0.9 && sumHist / contourArea(*itc) <= 1){
//		//		cout << "Fall detected!";
//		//		isFall = true;
//		//	}
//		//	std::vector<cv::Point> pts = *itc;
//		//	cv::Mat pointsMatrix = cv::Mat(pts);
//		//	cv::Scalar color(0, 255, 0);
//		//	cv::Rect r0 = cv::boundingRect(pointsMatrix);
//		//	cv::rectangle(result, r0, color, 2);
//
//		//	++itc;
//		//	//}
//		//}
//		if (contours.size() > 0){
//			double theLargestArea = contourArea(contours[0]);
//			int theLargestIndex = 0;
//			Rect bounding_Rect;
//			for (int i = 1; i < contours.size(); i++){
//				double a = contourArea(contours[i]);
//				if (a > theLargestArea && a >= 900){
//					theLargestArea = a;
//					theLargestIndex = i;
//				}
//			}
//			bounding_Rect = boundingRect(contours[theLargestIndex]);
//			rectangle(result, bounding_Rect, Scalar(0, 255, 0));
//			double firstFigure;
//			if (theLargestArea == 0){
//				firstFigure = 0;
//			}
//			else
//			{
//				firstFigure = sumHist / (theLargestArea * 255);
//				//firstFigure = theLargestArea;
//			}
//			cout << firstFigure << endl;
//		}
//
//
//		cv::imshow("Frame", result);
//		cv::imshow("Background Model", bgmodel);
//		cv::imshow("MHI image", mhi);
//		if (cv::waitKey(30) >= 0) break;
//	}
//	//waitKey(0);
//	return 0;
//}