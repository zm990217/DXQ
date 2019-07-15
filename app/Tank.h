#pragma once

#ifndef __AFXWIN_H__
    #error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"      

class CTankApp : public CWinApp
{
public:
    CTankApp();

public:
    virtual BOOL InitInstance();
    virtual int ExitInstance();


public:
    afx_msg void OnAppAbout();
    DECLARE_MESSAGE_MAP()

private:
    
    ULONG_PTR m_tokenGdiplus;
    Gdiplus::GdiplusStartupInput input;
    Gdiplus::GdiplusStartupOutput output;

};

extern CTankApp theApp;