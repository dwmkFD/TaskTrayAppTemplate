#pragma once
#include "CTrayWindow.hpp"

class CTrayWindowEx : public CTrayWindow
{
	DECLARE_DYNAMIC( CTrayWindowEx )

public:
	CTrayWindowEx();
	virtual ~CTrayWindowEx();

private:
	HICON m_hIcon_main;

protected:
	void DoLButtonClick();
	void DoRButtonClick();
	void DoLButtonDoubleClick();
	void DoBalloonUserClick();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnAppExit();
	afx_msg void OnAppAbout();
	afx_msg int OnCreate( LPCREATESTRUCT lpCreateStruct );
	afx_msg void OnDestroy();

	BOOL m_DlgEnable;
};

