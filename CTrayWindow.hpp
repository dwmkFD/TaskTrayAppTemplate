#pragma once
#include <afxwin.h>

static constexpr unsigned long WM_TASKTRAYEX = WM_APP + 1;
static constexpr unsigned long WM_BLNUSERCLK = WM_TASKTRAYEX + 1;
static constexpr unsigned long ID_CLICKTIMER = 4;

class CTrayWindow : public CWnd
{
	DECLARE_DYNAMIC( CTrayWindow )

public:
	CTrayWindow();
	virtual ~CTrayWindow();
	BOOL Create();
	void PostNcDestroy();
	BOOL NotifyIcon( DWORD dwMessage, HICON hIcon, LPCTSTR pszTip );
	BOOL NotifyIcon( DWORD dwMessage, HICON hIcon, UINT nStringResource );
	LRESULT OnTrayNotify( UINT wParam, LONG lParam );
	LRESULT OnBalloonUserClick( UINT wParam, LONG lParam );

	HICON m_hIcon_current;
	BOOL m_bFireDoubleClick;

	static constexpr unsigned int m_iconID = 1;
protected:
	DECLARE_MESSAGE_MAP()
	virtual void DoLButtonClick(){}
	virtual void DoRButtonClick(){}
	virtual void DoLButtonDoubleClick(){}
	virtual void DoBalloonUserClick(){}

public:
	afx_msg void OnTimer( UINT_PTR nIDEvent );
	afx_msg void OnLButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnRButtonUp( UINT nFlags, CPoint point );
	afx_msg void OnLButtonDblClk( UINT nFlags, CPoint point );
};

