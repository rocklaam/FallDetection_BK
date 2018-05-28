// FallDetectDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FallDetection_GUI.h"
#include "FallDetectDlg.h"
#include "afxdialogex.h"

// Properties
Mat FallDetectDlg::_frame;
Mat FallDetectDlg::_mhi;
Mat FallDetectDlg::_bin;
char* FallDetectDlg::notiURL = "http://falldetection-datn.herokuapp.com/api/sendfcmnotification/";

// FallDetectDlg dialog

IMPLEMENT_DYNAMIC(FallDetectDlg, CDialogEx)

FallDetectDlg::FallDetectDlg(char* imgURL, char* idCam, int minHumanShape, CWnd* pParent /*=NULL*/)
: CDialogEx(FallDetectDlg::IDD, pParent)
{
	_imgURL = imgURL;
	string notiURLBuf = notiURL;
	notiURLBuf += idCam;
	_notiURL = _strdup(notiURLBuf.c_str());
	_isPaused = false;
	_minHumanShape = minHumanShape;
}

FallDetectDlg::~FallDetectDlg()
{
}

void FallDetectDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RESULT, pcResult_);
}


BEGIN_MESSAGE_MAP(FallDetectDlg, CDialogEx)
	ON_BN_CLICKED(IDCANCEL, &FallDetectDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_START_DETECT, &FallDetectDlg::OnBnClickedButtonStartDetect)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE_DETECT, &FallDetectDlg::OnBnClickedButtonPauseDetect)
END_MESSAGE_MAP()


// FallDetectDlg message handlers

BOOL FallDetectDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	cv::destroyWindow(_NAME_BLURRED);
	cv::namedWindow(_NAME_BLURRED);
	HWND hWND0 = (HWND)cvGetWindowHandle(_NAME_BLURRED);
	HWND hParent0 = ::GetParent(hWND0);
	::SetParent(hWND0, GetDlgItem(IDC_PC_BLURRED)->m_hWnd);
	::ShowWindow(hParent0, SW_HIDE);

	cv::destroyWindow(_NAME_MHI);
	cv::namedWindow(_NAME_MHI);
	hWND0 = (HWND)cvGetWindowHandle(_NAME_MHI);
	hParent0 = ::GetParent(hWND0);
	::SetParent(hWND0, GetDlgItem(IDC_PC_MHI)->m_hWnd);
	::ShowWindow(hParent0, SW_HIDE);

	cv::destroyWindow(_NAME_BIN);
	cv::namedWindow(_NAME_BIN);
	hWND0 = (HWND)cvGetWindowHandle(_NAME_BIN);
	hParent0 = ::GetParent(hWND0);
	::SetParent(hWND0, GetDlgItem(IDC_PC_BIN)->m_hWnd);
	::ShowWindow(hParent0, SW_HIDE);

	return TRUE;
}

void FallDetectDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	_isPaused = true;
	CDialogEx::OnCancel();
}

void FallDetectDlg::OnBnClickedButtonStartDetect()
{
	// TODO: Add your control notification handler code here
	_isPaused = false;
	while (!_isPaused)
	{
		if (!CurlUtils::curlImg(_imgURL, _frame))
		{
			continue;
		}
		cv::resize(_frame, _frame, cv::Size(FRAME_WIDTH, FRAME_HEIGHT));
		//FallDetect::fallDetect(_frame, _mhi, _bin, _notiURL);
		if (FallDetect::fallDetect2(_frame, _mhi, _bin))
		{
			cBitmap_.LoadBitmap(IDB_BITMAP_DANGER);
			pcResult_.SetBitmap((HBITMAP)cBitmap_.Detach());
			UpdateData(true);
		}
		else
		{
			cBitmap_.LoadBitmap(IDB_BITMAP_SAFE);
			pcResult_.SetBitmap((HBITMAP)cBitmap_.Detach());
			UpdateData(true);
		}
		imshow(_NAME_BLURRED, _frame);
		imshow(_NAME_MHI, _mhi);
		imshow(_NAME_BIN, _bin);
		if (waitKey(30) >= 0)
		{
			break;
		}
	}
}

void FallDetectDlg::OnBnClickedButtonPauseDetect()
{
	// TODO: Add your control notification handler code here
	_isPaused = true;
}
