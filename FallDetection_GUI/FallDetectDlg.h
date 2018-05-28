#include "Config.h"
#include "CurlUtils.h"
#include "FallDetect.h"

#pragma once


// FallDetectDlg dialog

class FallDetectDlg : public CDialogEx
{
	DECLARE_DYNAMIC(FallDetectDlg)
private:
	char* _imgURL;
	char* _notiURL;
	bool _isPaused;
	int _minHumanShape;
	static Mat _frame, _mhi, _bin;
	const char* _NAME_BIN = "Bin Img";
	const char* _NAME_BLURRED = "Blurred Img";
	const char* _NAME_MHI = "MHI Img";
public:
	FallDetectDlg(char* imgURL, char* idCam, int minHumanShape, CWnd* pParent = NULL);   // standard constructor
	virtual ~FallDetectDlg();

	static char* notiURL;

	// Dialog Data
	enum { IDD = IDD_FALL_DETECT };
protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedCancel();
	afx_msg void OnBnClickedButtonStartDetect();
	afx_msg void OnBnClickedButtonPauseDetect();
protected:
	CStatic pcResult_;
	CBitmap cBitmap_;
};
