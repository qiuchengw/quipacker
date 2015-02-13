#include "StdAfx.h"
#include "QUITestx.h"
#include "file/FileEnumerator.h"
#include "crypt/CXUnzip.h"
#include "BaseType.h"
#include "AppHelper.h"
#include "QUIApp.h"
#include "ui/QConfig.h"

QConfig theConfig;
extern HINSTANCE G_hInst;								// current instance
extern HWND    G_hMainDlg;

QUITest::QUITest(void)
{
}

void xMessageBox(LPCTSTR lpszText, UINT nType  = MB_OK )
{
    ::MessageBox(G_hMainDlg, lpszText, L"XXX", nType);
}

#ifndef _DEBUG      // release mode 
#include "crypt/rijndael.h"
#include "crypt/QDataEnDe.h"

bool QUITest::PackUIZip(LPCWSTR szDir, LPCWSTR szDest)
{
    FileList lstFiles;
    QFileFinder(szDir, L"*.*", TRUE).GetFileList(lstFiles);
    if (lstFiles.size() < 0)
    {
        xMessageBox(L"No files found!\n");
        return false;
    }

    QString sDir(szDir);
    // get the password
    QBuffer qBuf;
    if (!qBuf.FileRead(sDir + L"CODE"))
    {
        xMessageBox(L"No CODE file!\n");
        return false;
    }
    QDataEnDe cEnDe;
    if (!cEnDe.SetCodeData(qBuf))
    {
        xMessageBox(L"Failed Init DataEnDe");
        return false;
    }

    CXZip zip;
    if (!zip.Create( szDest ))
    {
        xMessageBox(L"Create Zip Failed!");
        return false;
    }
    // Code File;
    zip.AddFile(L"Code",qBuf.GetBuffer(0),qBuf.GetBufferLen());

    // pack
    QString sFile;
    int nDirLen = sDir.GetLength();
    for (FileListItr i = lstFiles.begin(); i != lstFiles.end(); ++i)
    {
        //fX.Read(buf,3); // 丢弃文件的编码信息,要求所有的文本文件必须为UTF-8格式
        if (qBuf.FileRead((*i).c_str()))
        {
            sFile = *i;
            sFile = sFile.Mid(nDirLen);
            cEnDe.EncryptData(qBuf);
            zip.AddFile(sFile, qBuf.GetBuffer(0), qBuf.GetBufferLen());
        }
    }
    // 把CODE重写
//     qBuf.FileRead(sDir + L"CODE");
//     zip.AddFile(sDir + L"CODE", qBuf.GetBuffer(0), qBuf.GetBufferLen());
    return true;
}

#else

bool QUITest::PackUIZip(LPCWSTR szDir, LPCWSTR szDest)
{
    FileList lstFiles;
    QFileFinder(szDir, L"*.*", TRUE).GetFileList(lstFiles);
    if (lstFiles.size() < 0)
    {
        xMessageBox(L"No files found!");
        return false;
    }

    QString sDir(szDir);
    // get the password
    QBuffer qBuf;
    if (!qBuf.FileRead(sDir + L"CODE"))
    {
        xMessageBox(L"No CODE file!\n");
        return false;
    }

    CXZip zip;
    if (!zip.Create( szDest ))
    {
        xMessageBox(L"Create Zip Failed!");
        return false;
    }
    // Code File;
    zip.AddFile(L"Code",qBuf.GetBuffer(0),qBuf.GetBufferLen());

    // pack
    QString sFile;
    int nDirLen = sDir.GetLength();
    for (FileListItr i = lstFiles.begin(); i != lstFiles.end(); ++i)
    {
        //fX.Read(buf,3); // 丢弃文件的编码信息,要求所有的文本文件必须为UTF-8格式
        if (qBuf.FileRead((*i).c_str()))
        {
            sFile = *i;
            sFile = sFile.Mid(nDirLen);
            zip.AddFile(sFile, qBuf.GetBuffer(0), qBuf.GetBufferLen());
        }
    }
    return true;
}

#endif

BOOL QUITest::TestUI( LPCWSTR szUIDir, LPCWSTR szMainUI )
{
    m_sZip = qcwbase::GetModulePath() + L"UI.zip";
    DeleteFile(m_sZip);

    BOOL bRet = FALSE;
    if (PackUIZip(szUIDir, m_sZip))
    {
        m_sMainUI = szMainUI;
        HANDLE h = (HANDLE)_beginthreadex(NULL,0, &QUITest::thread_ui, this, 0, NULL);
        if (h > 0)
        {
            CloseHandle(h);
            bRet = TRUE;
        }
    }
    return bRet;
}

unsigned __stdcall QUITest::thread_ui( void* pparam )
{
    QUITest *pThis = reinterpret_cast<QUITest*>(pparam);
    ASSERT(NULL != pThis);

    ::OleInitialize(NULL);

    QUIApp theApp(pThis->m_sMainUI);
    theApp.Init(NULL, G_hInst);
    theApp.Run(G_hInst);
    theApp.Term();

    ::CoUninitialize();

    return 0;
}
