#include "pch.h"
#include "CTrayWindow.hpp"

IMPLEMENT_DYNAMIC( CTrayWindow, CWnd )

CTrayWindow::CTrayWindow()
{
	m_hIcon_current = NULL;
	m_bFireDoubleClick = false;
}

CTrayWindow::~CTrayWindow()
{
}


BEGIN_MESSAGE_MAP( CTrayWindow, CWnd )
	ON_MESSAGE( WM_TASKTRAYEX, &CTrayWindow::OnTrayNotify )
	ON_MESSAGE( NIN_BALLOONUSERCLICK, &CTrayWindow::OnBalloonUserClick )
	ON_WM_TIMER()
	ON_WM_LBUTTONUP()
	ON_WM_RBUTTONUP()
	ON_WM_LBUTTONDBLCLK()
END_MESSAGE_MAP()


BOOL CTrayWindow::Create()
{
	return CreateEx( WS_EX_TOOLWINDOW,
		AfxRegisterWndClass( 0 ),
		_T( "TrayWindow" ),
		WS_OVERLAPPED,
		0, 0, 0, 0,
		nullptr, nullptr );
}

void CTrayWindow::PostNcDestroy()
{
	// TODO: ここに特定なコードを追加するか、もしくは基本クラスを呼び出してください。

	CWnd::PostNcDestroy();

	delete this;
}

BOOL CTrayWindow::NotifyIcon( DWORD dwMessage, HICON hIcon, LPCTSTR pszTip )
{
	ASSERT( NIM_ADD == dwMessage
		|| NIM_DELETE == dwMessage
		|| NIM_MODIFY == dwMessage );

	NOTIFYICONDATA nid;
	ZeroMemory( &nid, sizeof( NOTIFYICONDATA ) );
	nid.cbSize = sizeof( NOTIFYICONDATA );
	nid.hWnd = GetSafeHwnd();
	nid.uID = m_iconID;	// この関数は、アイコンを1つだけサポートする。
	// タスクトレイのアイコンID
	// 1つのプロセスで複数のアイコンをタスクトレイに表示する場合には、それぞれ異なるIDを指定する。
	// このIDはプロセスごとに独立しているので、他のプロセスが同じIDを指定していたとしても、それらが衝突することはない。
	nid.uCallbackMessage = WM_TASKTRAYEX;
	nid.uFlags = NIF_MESSAGE;

	if ( ( nullptr != hIcon )
		 && ( m_hIcon_current != hIcon )
		 )
	{	// アイコン変更
		nid.uFlags |= NIF_ICON;
		nid.hIcon = hIcon;
		m_hIcon_current = hIcon;
	}

	if ( nullptr != pszTip )
	{	// ツールチップ表示
		nid.uFlags |= NIF_TIP;
		_tcsncpy_s( nid.szTip, sizeof( nid.szTip ), pszTip, _TRUNCATE );
	}

	return ( Shell_NotifyIcon( dwMessage, &nid ) );
}

BOOL CTrayWindow::NotifyIcon( DWORD dwMessage, HICON hIcon, UINT nStringResource )
{
	// 表示メッセージを、ストリングリソースのリソースＩＤで指定する関数
	CString msg;
	VERIFY( msg.LoadString( nStringResource ) );
	return NotifyIcon( dwMessage, hIcon, msg );
}

LRESULT CTrayWindow::OnTrayNotify(UINT wParam, LONG lParam)
{
	UINT uiIconID = (UINT)wParam;
	UINT uiMouseMsg = (UINT)lParam;

	if ( m_iconID != uiIconID )
	{
		return ( 0 );
	}

	switch ( uiMouseMsg )
	{
	case WM_LBUTTONDOWN:
		m_bFireDoubleClick = FALSE;
		SetTimer( ID_CLICKTIMER, GetDoubleClickTime(), NULL );
		break;

	case WM_LBUTTONUP:
		if ( m_bFireDoubleClick )
		{
			PostMessage( WM_LBUTTONDBLCLK );
		}
		break;

	case WM_LBUTTONDBLCLK:
		m_bFireDoubleClick = TRUE;
		KillTimer( ID_CLICKTIMER );
		break;

	case WM_RBUTTONUP:
		PostMessage( WM_RBUTTONUP );
		break;
		
	case NIN_BALLOONUSERCLICK:
		PostMessage( NIN_BALLOONUSERCLICK );
		break;
	}

	return 0;
}


LRESULT CTrayWindow::OnBalloonUserClick( UINT wParam, LONG lParam )
{
	DoBalloonUserClick();
	return ( 0 );
}


void CTrayWindow::OnTimer( UINT_PTR nIDEvent )
{
	if ( ID_CLICKTIMER == nIDEvent )
	{
		KillTimer( nIDEvent );
		PostMessage( WM_LBUTTONUP );
	}
}


void CTrayWindow::OnLButtonUp( UINT nFlags, CPoint point )
{
	DoLButtonClick();
}


void CTrayWindow::OnRButtonUp( UINT nFlags, CPoint point )
{
	DoRButtonClick();
}


void CTrayWindow::OnLButtonDblClk( UINT nFlags, CPoint point )
{
	DoLButtonDoubleClick();
}
