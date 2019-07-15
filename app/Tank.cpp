#include "stdafx.h"
#include "afxwinappex.h"
#include "afxdialogex.h"
#include "Tank.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CTankApp
BEGIN_MESSAGE_MAP(CTankApp, CWinApp)
	ON_COMMAND(ID_APP_ABOUT, &CTankApp::OnAppAbout)
END_MESSAGE_MAP()

// CTankApp 
CTankApp::CTankApp()
{
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;
#ifdef _MANAGED
	System::Windows::Forms::Application::SetUnhandledExceptionMode(System::Windows::Forms::UnhandledExceptionMode::ThrowException);
#endif

	SetAppID(_T("Tank.AppID.NoVersion"));
}

CTankApp theApp;

BOOL CTankApp::InitInstance()
{
    CWinApp::InitInstance();

    Status s = GdiplusStartup(&m_tokenGdiplus, &input, &output);

    CMainFrame *pFrame = new CMainFrame;
    if (!pFrame) {
        return FALSE;
    }

    m_pMainWnd = pFrame;
    pFrame->ShowWindow(SW_SHOW);
    pFrame->UpdateWindow();
    return TRUE;
}

int CTankApp::ExitInstance()
{
	AfxOleTerm(FALSE);
	return CWinApp::ExitInstance();
}

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    

protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()

void CTankApp::OnAppAbout()
{
	CAboutDlg aboutDlg;
	aboutDlg.DoModal();
}