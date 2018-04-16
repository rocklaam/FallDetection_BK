 //#include "opencv2/objdetect.hpp"
 //#include "opencv2/highgui.hpp"
 //#include "opencv2/imgproc.hpp"
 //#include "opencv2/video/tracking.hpp"
 //#include <opencv2/core/core.hpp>
 //#include <opencv2/imgcodecs.hpp>
 //#include <opencv2/highgui/highgui.hpp>

 //#include <iostream>
 //#include <stdio.h>

 //using namespace std;
 //using namespace cv;

 ///** Function Headers */
 //Mat detectAndDisplay(Mat frame);
 //Mat detectHumanInImage(Mat image);

 ///** Global variables */
 //String human_cascade_name = "E:/BachKhoaUni/DoAn/ThesisProject_2018/FallDetection_BK/Private/HumanDetechData/persons_test/output/cascade.xml";
 ////sString human_cascade_name = "C:/opencv/sources/data/haarcascades/haarcascade_upperbody.xml";
 //CascadeClassifier human_cascade;
 //String window_name = "Capture - Face detection";

 ///** @function main */
 //int main(void)
 //{
 //	namedWindow(window_name, WINDOW_AUTOSIZE);
 //	VideoCapture capture("E:/BachKhoaUni/DoAn/ThesisProject_2018/FallDetection_BK/Private/Office/a.avi");
 //	//VideoCapture capture(0);

 //	//-- 1. Load the cascades
 //	if (!human_cascade.load(human_cascade_name)){ printf("--(!)Error loading human cascade\n"); return -1; };

 //	//-- 2. Read the video stream
 //	if (!capture.isOpened()) { printf("--(!)Error opening video capture\n"); return -1; }

 //	// while (1)
 //	// {
 //	// 	Mat frame;
 //	// 	capture.read(frame);
 //	// 	if (frame.empty())
 //	// 	{
 //	// 		printf(" --(!) No captured frame -- Break!");
 //	// 		break;
 //	// 	}

 //	// 	//-- 3. Apply the classifier to the frame
 //	// 	frame = detectAndDisplay(frame);
 //	// 	imshow(window_name, frame);

 //	// 	// int c = waitKey(10);
 //	// 	if (waitKey(10) == 27) { break; } // escape
 //	// }
 //	Mat frame;
 //	frame = imread("E:/BachKhoaUni/DoAn/ThesisProject_2018/FallDetection_BK/Private/HumanDetechData/persons/person_001.jpg", IMREAD_COLOR);
 //	cout << frame.empty() << endl;
 //	frame = detectHumanInImage(frame);
 //	imshow(window_name, frame);
 //	getchar();
 //	return 0;
 //}

 ///** @function detectAndDisplay */
 //Mat detectAndDisplay(Mat frame)
 //{
 //	vector<Rect> humans;
 //	Mat frame_gray;

 //	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
 //	equalizeHist(frame_gray, frame_gray);

 //	//-- Detect faces
 //	printf("processing 1\n");
 //	human_cascade.detectMultiScale(frame_gray, humans, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT, Size(), Size(20, 80));
 //	//cout << humans.size() << endl;
 //	for (size_t i = 0; i < humans.size(); i++)
 //	{
 //		//rectangle(frame, center, Size(humans[i].width / 2, humans[i].height / 2), 0, 0, 360, Scalar(255, 0, 255), 4, 8, 0);
 //		//if (humans.size() > 0)
 //		//{ 
 //		rectangle(frame, humans[i].tl(), humans[i].br(), Scalar(255, 0, 255), 2, 8, 0);
 //		//}

 //		// Mat faceROI = frame_gray(humans[i]);
 //		// std::vector<Rect> eyes;

 //		// //-- In each face, detect eyes
 //		// eyes_cascade.detectMultiScale(faceROI, eyes, 1.1, 2, 0 | CASCADE_SCALE_IMAGE, Size(30, 30));

 //		// for (size_t j = 0; j < eyes.size(); j++)
 //		// {
 //		// 	Point eye_center(faces[i].x + eyes[j].x + eyes[j].width / 2, faces[i].y + eyes[j].y + eyes[j].height / 2);
 //		// 	int radius = cvRound((eyes[j].width + eyes[j].height)*0.25);
 //		// 	circle(frame, eye_center, radius, Scalar(255, 0, 0), 4, 8, 0);
 //		// }
 //	}
 //	//-- Show what you got
 //	return frame;
 //}

 //Mat detectHumanInImage(Mat image){
 //	vector<Rect> humans;
 //	Mat gray_image;
 //	cvtColor(image, gray_image, COLOR_BGR2GRAY);
 //	equalizeHist(gray_image, gray_image);
 //	cout << "ntlam" << endl;
 //	//human_cascade.detectMultiScale(gray_image, humans, 1.1, 3, CV_HAAR_FIND_BIGGEST_OBJECT, Size(20, 80));
 //	//for (size_t i = 0; i < humans.size(); i++)
 //	//{
 //	//rectangle(image, humans[i].tl(), humans[i].br(), Scalar(255, 0, 255), 2, 8, 0);
 //	//}
 //	//-- Show what you got
 //	return image;
 //}