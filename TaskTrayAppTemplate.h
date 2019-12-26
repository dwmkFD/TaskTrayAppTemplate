
// TaskTrayAppTemplate.h : PROJECT_NAME アプリケーションのメイン ヘッダー ファイルです
//

#pragma once

#ifndef __AFXWIN_H__
	#error "PCH に対してこのファイルをインクルードする前に 'pch.h' をインクルードしてください"
#endif

#include "resource.h"		// メイン シンボル

#include "TaskTrayAppTemplateDlg.hpp"


// CTaskTrayAppTemplateApp:
// このクラスの実装については、TaskTrayAppTemplate.cpp を参照してください
//

class CTaskTrayAppTemplateApp : public CWinApp
{
public:
	CTaskTrayAppTemplateApp();

// オーバーライド
public:
	virtual BOOL InitInstance();

	void initMainDlgWindow()
	{
		// メインのダイアログを生成する
		m_dlg.Create( IDD_TASKTRAYAPPTEMPLATE_DIALOG );
		m_dlg.ShowWindow( SW_HIDE );
	}
private:
	CTaskTrayAppTemplateDlg m_dlg;

// 実装

	DECLARE_MESSAGE_MAP()
};

extern CTaskTrayAppTemplateApp theApp;
