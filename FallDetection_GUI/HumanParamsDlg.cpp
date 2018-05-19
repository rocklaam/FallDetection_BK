// HumanParamsDlg.cpp : implementation file
//

#include "stdafx.h"
#include "HumanParamsDlg.h"
#include "afxdialogex.h"

// HumanParamsDlg dialog

IMPLEMENT_DYNAMIC(HumanParamsDlg, CDialogEx)

HumanParamsDlg::HumanParamsDlg(char* imgURL, char* idCam, CWnd* pParent /*=NULL*/)
: CDialogEx(HumanParamsDlg::IDD, pParent)
{
	_isCalculated = false;
	_imgURL = imgURL;
	_idCam = idCam;
}

HumanParamsDlg::~HumanParamsDlg()
{
}

void HumanParamsDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_PC_HUMAN_PARAMS, pcHumanShape_);
}


BEGIN_MESSAGE_MAP(HumanParamsDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &HumanParamsDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &HumanParamsDlg::OnBnClickedCancel)
	ON_STN_ENABLE(IDC_PC_HUMAN_PARAMS, &HumanParamsDlg::OnStnEnablePcHumanParams)
	ON_BN_CLICKED(IDC_START, &HumanParamsDlg::OnBnClickedStart)
END_MESSAGE_MAP()


// HumanParamsDlg message handlers
BOOL HumanParamsDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	cv::destroyWindow(_nameWindow);
	cv::namedWindow(_nameWindow);
	HWND hWND0 = (HWND)cvGetWindowHandle(_nameWindow);
	HWND hParent0 = ::GetParent(hWND0);
	::SetParent(hWND0, GetDlgItem(IDC_PC_HUMAN_PARAMS)->m_hWnd);
	::ShowWindow(hParent0, SW_HIDE);
	return TRUE;
}

void HumanParamsDlg::OnBnClickedOk()
{
	// TODO: Add your control notification handler code here
	if (_humanArea == 0)
	{
		MessageBox(_T("Please calculate the body shape!"), _T("Error"), MB_ICONWARNING);
		return;
	}
	_isCalculated = true;
	ShowWindow(SW_HIDE);
	FallDetectDlg fallDetectDlg(_imgURL, _idCam, _humanArea);
	INT_PTR nResponse = fallDetectDlg.DoModal();
	if (nResponse == IDCANCEL)
	{
		ShowWindow(SW_NORMAL);
	}
}


void HumanParamsDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	_isCalculated = true;
	CDialogEx::OnCancel();
}


void HumanParamsDlg::OnStnEnablePcHumanParams()
{
	// TODO: Add your control notification handler code here
}


void HumanParamsDlg::OnBnClickedStart()
{
	// TODO: Add your control notification handler code here
	_isCalculated = false;
	Mat frame;
	Detector detector;
	while (!_isCalculated)
	{
		if (!CurlUtils::curlImg(this->_imgURL, frame))
		{
			continue;
		}
		cv::resize(frame, frame, cv::Size(FRAME_WIDTH, FRAME_HEIGHT));
		detector.calculateHuman(frame, _humanArea);
		imshow(_nameWindow, frame);
		if (waitKey(30) >= 0)
		{
			break;
		}
	}
}
