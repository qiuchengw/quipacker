// QUITest.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "QUITest.h"
#include "QUITestx.h"
#include "AppHelper.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE G_hInst;								// current instance
HWND    G_hMainDlg = NULL;

// Forward declarations of functions included in this code module:
BOOL				InitInstance(HINSTANCE, int);
INT_PTR CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);

int APIENTRY _tWinMain(HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPTSTR    lpCmdLine,
    int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
    MSG msg;

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    // Main message loop:
    while (GetMessage(&msg, NULL, 0, 0))
    {
        if(!IsDialogMessage(G_hMainDlg, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
    G_hMainDlg = CreateDialog(hInstance, MAKEINTRESOURCE(IDD_DLG_MAIN), NULL, WndProc );
    ShowWindow(G_hMainDlg, SW_SHOW);
    G_hInst = hInstance; // Store instance handle in our global variable

    qcwbase::CenterWindowInWindow(G_hMainDlg, GetDesktopWindow());

    return TRUE;
}

BOOL OnCommand(HWND hDlg, UINT nCmdCode)
{
    // Parse the menu selections:
    switch (nCmdCode)
    {
    case IDOK:
    case IDCANCEL:
        return TRUE;
    case IDC_BTN_PREVIEW:
        {
            wchar_t szMainUI[MAX_PATH] = {0};
            wchar_t szUIDir[MAX_PATH] = {0};
            GetDlgItemText(hDlg, IDC_EDIT_UIDIR, szUIDir, MAX_PATH);
            GetDlgItemText(hDlg, IDC_EDIT_MAINHTML, szMainUI, MAX_PATH);

            QUITest::GetInstance()->TestUI(szUIDir, szMainUI);

            return TRUE;
        }
    }
    return FALSE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
INT_PTR CALLBACK WndProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    int wmId, wmEvent;
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_KEYDOWN:
        if (wParam == VK_ESCAPE)
            return TRUE;
        break;

    case WM_COMMAND:
        wmId    = LOWORD(wParam);
        wmEvent = HIWORD(wParam);
        if (wmId == IDOK || wmId == IDCANCEL)
        {
            DestroyWindow(hDlg);
            return (INT_PTR)TRUE;
        }
        else
        {
            OnCommand(hDlg, wmId);
        }
        return 1;

    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    }
    return 0;
}
