#include "pch.h"
#include "TaskTrayAppTemplateDlg.hpp"
#include "CTrayWindowEx.hpp"
#include "Resource.h"

IMPLEMENT_DYNAMIC( CTrayWindowEx, CTrayWindow )


CTrayWindowEx::CTrayWindowEx()
{
	m_hIcon_main = nullptr;
	m_DlgEnable = FALSE;
}

CTrayWindowEx::~CTrayWindowEx()
{
}


BEGIN_MESSAGE_MAP( CTrayWindowEx, CTrayWindow )
	ON_COMMAND( ID_APP_EXIT, &CTrayWindowEx::OnAppExit )
	ON_COMMAND( ID_APP_ABOUT, &CTrayWindowEx::OnAppAbout )
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()



// CTrayWindowEx メッセージ ハンドラー

void CTrayWindowEx::DoLButtonClick()
{
	POINT pt;
	GetCursorPos( &pt );

	CMenu menu;
//	menu.LoadMenu( IDM_TRAY_L );

	CMenu *pPopup = menu.GetSubMenu( 0 );

	SetForegroundWindow();
	pPopup->TrackPopupMenu( TPM_RIGHTBUTTON, pt.x, pt.y, this );
	PostMessage( WM_NULL );
}

void CTrayWindowEx::DoRButtonClick()
{
	POINT pt;
	GetCursorPos( &pt );

	CMenu menu;
//	menu.LoadMenu( IDM_TRAY_R );

	CMenu *pPopup = menu.GetSubMenu( 0 );

	SetForegroundWindow();
	pPopup->TrackPopupMenu( TPM_RIGHTBUTTON, pt.x, pt.y, this );
	PostMessage( WM_NULL );
}

void CTrayWindowEx::DoLButtonDoubleClick()
{
}

void CTrayWindowEx::DoBalloonUserClick()
{
}

void CTrayWindowEx::OnAppExit()
{
	PostMessage( WM_CLOSE );
}

void CTrayWindowEx::OnAppAbout()
{
	CAboutDlg dlg;
	dlg.DoModal();
}

int CTrayWindowEx::OnCreate( LPCREATESTRUCT lpCreateStruct )
{
	if ( -1 == CTrayWindow::OnCreate( lpCreateStruct ) )
		return ( -1 );

	m_hIcon_main = AfxGetApp()->LoadIcon( IDR_MAINFRAME );
	NotifyIcon( NIM_ADD, m_hIcon_main, _T( "TaskTrayAppTemplate" ) );

	return ( 0 );
}


void CTrayWindowEx::OnDestroy()
{
	CTrayWindow::OnDestroy();

	NotifyIcon( NIM_DELETE, NULL, _T( "TaskTrayAppTemplate" ) );
}

