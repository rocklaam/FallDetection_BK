//#include "opencv2/objdetect.hpp"
//#include "opencv2/highgui.hpp"
//#include "opencv2/imgproc.hpp"
//#include "opencv2/video/tracking.hpp"
//#include <opencv2/core/core.hpp>
//#include <opencv2/imgcodecs.hpp>
//#include <opencv2/highgui/highgui.hpp>
//
//#include <iostream>
//#include <string>
//
//using namespace cv;
//using namespace std;
//
//Mat detectHumanInImage(Mat image);
//CascadeClassifier human_cascade;
//
//
//int main(int argc, char** argv)
//{
//	/** Global variables */
//	String human_cascade_name = "C:/opencv/sources/data/haarcascades_cuda/_haarcascadeUpperbody.xml";
//	String window_name = "Capture - Face detection";
//	VideoCapture capture("E:/BachKhoaUni/DoAn/ThesisProject_2018/FallDetection_BK/Private/Office/a.avi");
//	//VideoCapture capture(0);
//
//	// 	//-- 1. Load the cascades
//	if (!human_cascade.load(human_cascade_name)){ printf("--(!)Error loading human cascade\n"); return -1; };
//
//	//-- 2. Read the video stream
//	if (!capture.isOpened()) { printf("--(!)Error opening video capture\n"); return -1; }
//
//	string imageName("E:/BachKhoaUni/DoAn/ThesisProject_2018/FallDetection_BK/Private/HumanDetechData/persons/person_001.jpg"); // by default
//	if (argc > 1)
//	{
//		imageName = argv[1];
//	}
//
//	Mat image;
//	image = imread("E:/BachKhoaUni/DoAn/ThesisProject_2018/FallDetection_BK/Private/HumanDetechData/persons/person_001.jpg", IMREAD_COLOR); // Read the file
//
//	if (image.empty())                      // Check for invalid input
//	{
//		cout << "Could not open or find the image" << std::endl;
//		return -1;
//	}
//	image = detectHumanInImage(image);
//	//namedWindow(window_name, WINDOW_AUTOSIZE); // Create a window for display.
//	imshow(window_name, image);                // Show our image inside it.
//
//	waitKey(0); // Wait for a keystroke in the window
//	return 0;
//}
//
//Mat detectHumanInImage(Mat image){
//	vector<Rect> humans;
//	Mat gray_image;
//	cvtColor(image, gray_image, COLOR_BGR2GRAY);
//	equalizeHist(gray_image, gray_image);
//	cout << "ntlam" << endl;
//	human_cascade.detectMultiScale(gray_image, humans, 1.04, 4, 0 | 1, Size(30, 80), Size(80, 200));
//	cout << humans.size() << endl;
//	for (size_t i = 0; i < humans.size(); i++)
//	{
//		//rectangle(image, humans[i].tl(), humans[i].br(), Scalar(255, 0, 255), 2, 8, 0);
//		rectangle(image, humans[i], Scalar(255, 0, 255), 2, 8, 0);
//	}
//	cout << "done" << endl;
//	//-- Show what you got
//	return image;
//}