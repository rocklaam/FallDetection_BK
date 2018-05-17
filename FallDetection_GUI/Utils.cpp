#include "stdafx.h"
#include "Utils.h"

void Utils::displayCVImage(Mat img, char* windowName, HWND dialog, int pictureControlID)
{
	//destroyWindow(windowName);
	//namedWindow(windowName);
	HWND hWND = (HWND)cvGetWindowHandle(windowName);
	HWND parent = GetParent(hWND);
	::SetParent(hWND, GetDlgItem(dialog, pictureControlID));
	//ShowWindow(parent, SW_HIDE);
	imshow(windowName, img);
}