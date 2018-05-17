// FallDetection_GUIDlg.cpp : implementation file
//

#include "stdafx.h"
#include "FallDetection_GUI.h"
#include "FallDetection_GUIDlg.h"
#include "afxdialogex.h"
#include "HumanParamsDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CAboutDlg dialog used for App About

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

	// Dialog Data
	enum { IDD = IDD_ABOUTBOX };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	// Implementation
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CFallDetection_GUIDlg dialog



CFallDetection_GUIDlg::CFallDetection_GUIDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CFallDetection_GUIDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CFallDetection_GUIDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_BUTTON_CHECK, btnCheck_);
	DDX_Control(pDX, IDC_IPADDRESS, ipAddress_);
	DDX_Control(pDX, IDC_EDT_PORT, port_);
	DDX_Control(pDX, IDC_EDT_USER, userName_);
	DDX_Control(pDX, IDC_EDT_PASS, pass_);
	DDX_Control(pDX, IDC_EDT_ID, idCamera_);
}

BEGIN_MESSAGE_MAP(CFallDetection_GUIDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDCANCEL, &CFallDetection_GUIDlg::OnBnClickedCancel)
	ON_BN_CLICKED(IDC_BUTTON_CHECK, &CFallDetection_GUIDlg::OnBnClickedButtonCheck)
END_MESSAGE_MAP()


// CFallDetection_GUIDlg message handlers

BOOL CFallDetection_GUIDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Add "About..." menu item to system menu.

	// IDM_ABOUTBOX must be in the system command range.

	// Init the default value for ip address
	ipAddress_.SetAddress(192, 168, 0, 222);
	UpdateData(true);

	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CFallDetection_GUIDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CFallDetection_GUIDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CFallDetection_GUIDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CFallDetection_GUIDlg::OnBnClickedCancel()
{
	// TODO: Add your control notification handler code here
	CDialogEx::OnCancel();
}


void CFallDetection_GUIDlg::OnBnClickedButtonCheck()
{
	// TODO: Add your control notification handler code here
	UpdateData(true);
	CString ipAddress = _T("");
	CString pass = _T("");
	CString port = _T("");
	CString userName = _T("");

	ipAddress_.GetWindowText(ipAddress);
	port_.GetWindowText(port);
	userName_.GetWindowText(userName);
	pass_.GetWindowText(pass);

	Mat buf;
	CString urlImg = _T("http://") + ipAddress + ":" + port
		+ "/snapshot.cgi?loginuse=" + userName + "&loginpas=" + pass;
	CT2A urlImgChar(urlImg);

	if (CurlUtils::curlImg(urlImgChar, buf))
	{
		MessageBox(_T("Successful!"));
		CString idCamera = _T("");
		idCamera_.GetWindowText(idCamera);
		CT2A idCamChar(idCamera);
		ShowWindow(SW_HIDE);
		HumanParamsDlg humanParamsDlg(urlImgChar, idCamChar);
		INT_PTR nResponse = humanParamsDlg.DoModal();
		if (nResponse == IDCANCEL)
		{
			ShowWindow(SW_NORMAL);
		}
	}
	else
	{
		MessageBox(_T("Error! Try Again"));
	}
}
