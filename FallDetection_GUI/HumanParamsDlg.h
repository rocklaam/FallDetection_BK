#include "FallDetection_GUI.h"
#include "FallDetectDlg.h"

#include "Detector.h"

#pragma once

// HumanParamsDlg dialog

class HumanParamsDlg : public CDialogEx
{
	DECLARE_DYNAMIC(HumanParamsDlg)

private:
	bool _isCalculated;
	int _humanArea;
	char* _idCam;
	char* _imgURL;
	static Mat _frame;
	const char* _nameWindow = "Calculating Human Params";
public:
	HumanParamsDlg(char* imgURL, char* idCam, CWnd* pParent = NULL);   // standard constructor
	virtual ~HumanParamsDlg();

	// Dialog Data
	enum { IDD = IDD_HUMAN_SHAPE };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	CStatic pcHumanShape_;
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnStnEnablePcHumanParams();
	afx_msg void OnBnClickedStart();
};
