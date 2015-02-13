#include "StdAfx.h"
#include "QUIApp.h"

QUIApp::QUIApp( LPCWSTR szUIHtml )
{
    m_frame.SetUIPath(szUIHtml);
}

QUIApp::~QUIApp(void)
{
}

BOOL QUIApp::InitRun()
{
    if (!m_frame.Create(NULL))
        return FALSE;

    SetMainWnd(&m_frame);
    return TRUE;
}
