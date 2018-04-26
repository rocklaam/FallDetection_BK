
// FallDetection_GUIDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"


// CFallDetection_GUIDlg dialog
class CFallDetection_GUIDlg : public CDialogEx
{
// Construction
public:
	CFallDetection_GUIDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_FALLDETECTION_GUI_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnIpnFieldchangedIpaddress1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
protected:
	CIPAddressCtrl AddressID_;
	CButton btnCheck_;
	CIPAddressCtrl ipAddress_;
public:
	afx_msg void OnBnClickedButtonCheck();
};
