
// SmartPlayer.h : PROJECT_NAME Ӧ�ó������ͷ�ļ�
//

#pragma once

#ifndef __AFXWIN_H__
	#error "�ڰ������ļ�֮ǰ������stdafx.h�������� PCH �ļ�"
#endif

#include "resource.h"		// ������


// CSmartPlayerApp:
// �йش����ʵ�֣������ SmartPlayer.cpp
//

class CSmartPlayerApp : public CWinApp
{
public:
	CSmartPlayerApp();

// ��д
public:
	virtual BOOL InitInstance();

// ʵ��

	DECLARE_MESSAGE_MAP()
};

extern CSmartPlayerApp theApp;