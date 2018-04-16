//#include <time.h>   //  for  clock()   and   CLOCKS_PER_SEC
//#include <stdio.h>
//#include<iostream>
//#include <ctype.h>
//#include <opencv2\opencv.hpp>
//#include<opencv2\highgui\highgui.hpp>
//#include<opencv2\imgproc\imgproc.hpp>
//#include<opencv2\core\core.hpp>
//#include "opencv2/optflow.hpp"
//
//using namespace cv;
//using namespace cv::motempl;
//using namespace std;
//
//
///*MHI Simple------>*/
//int main(int argc, char** argv)
//{
//	Mat frame, frame2, dst;
//
//	//double timestamp = (double)clock() / CLOCKS_PER_SEC; // I found this in the Opencv/samples  motempl.cpp
//	double duration = 1; //same as above , found this value in the opencv/samples/motempl.cpp
//	//double timestamp = clock();
//	//cv::VideoCapture cap = cv::VideoCapture("http://192.168.0.103:8888/videostream.cgi?&loginuse=admin&loginpas=admin");
//	//cv::VideoCapture cap;
//	//cap.open("http://192.168.0.103:8888/videostream.cgi?&loginuse=admin&loginpas=admin");
//	//VideoCapture cap("E:/BachKhoaUni/DoAn/ThesisProject_2018/FallDetection_BK/Private/Office/a.avi");
//	VideoCapture cap(0);
//	cout << 255. / 7; // Device with float result
//	while (1)
//	{
//		double timestamp = (double)clock() / CLOCKS_PER_SEC; // I found this in the Opencv/samples  motempl.cpp
//		cout << timestamp << endl;
//		cap.read(frame);
//		if (frame.empty()){
//			break;
//		}
//		cvtColor(frame, frame, CV_BGR2GRAY);
//		cap.read(dst);
//		cvtColor(dst, dst, CV_BGR2GRAY);
//		absdiff(frame, dst, frame2); // Compare Difference directly
//		imshow("absolute frame difference", frame2);
//		threshold(frame2, frame2, 30, 255, THRESH_BINARY);
//		//Mat tst(frameHeight, frameWidth CV_32FC1);
//		//Mat.at（int y， int x）
//
//		Mat tst(frame2.rows, frame2.cols, CV_32FC1);
//
//		imshow("threshold_MHI", frame2);
//		updateMotionHistory(frame2, tst, timestamp, duration);
//		imshow("MHI updated", tst);
//		/*
//		void updateMotionHistory(InputArray silhouette,
//		InputOutputArray mhi,    //single-channel, 32-bit floating-point
//		double timestamp,
//		double duration)
//		*/
//
//		waitKey(30);
//	}
//	return 0;
//}