
// SmartPlayer.cpp : ����Ӧ�ó��������Ϊ��
//

#include "stdafx.h"
#include "SmartPlayer.h"
#include "SmartPlayerDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CSmartPlayerApp

BEGIN_MESSAGE_MAP(CSmartPlayerApp, CWinApp)
	ON_COMMAND(ID_HELP, &CWinApp::OnHelp)
END_MESSAGE_MAP()


// CSmartPlayerApp ����

CSmartPlayerApp::CSmartPlayerApp()
{
	// ֧����������������
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: �ڴ˴���ӹ�����룬
	// ��������Ҫ�ĳ�ʼ�������� InitInstance ��
}


// Ψһ��һ�� CSmartPlayerApp ����

CSmartPlayerApp theApp;


// CSmartPlayerApp ��ʼ��

BOOL CSmartPlayerApp::InitInstance()
{
	// ���һ�������� Windows XP �ϵ�Ӧ�ó����嵥ָ��Ҫ
	// ʹ�� ComCtl32.dll �汾 6 ����߰汾�����ÿ��ӻ���ʽ��
	//����Ҫ InitCommonControlsEx()�����򣬽��޷��������ڡ�
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// ��������Ϊ��������Ҫ��Ӧ�ó�����ʹ�õ�
	// �����ؼ��ࡣ
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// ���� shell ���������Է��Ի������
	// �κ� shell ����ͼ�ؼ��� shell �б���ͼ�ؼ���
	CShellManager *pShellManager = new CShellManager;

	// ��׼��ʼ��
	// ���δʹ����Щ���ܲ�ϣ����С
	// ���տ�ִ���ļ��Ĵ�С����Ӧ�Ƴ�����
	// ����Ҫ���ض���ʼ������
	// �������ڴ洢���õ�ע�����
	// TODO: Ӧ�ʵ��޸ĸ��ַ�����
	// �����޸�Ϊ��˾����֯��
	SetRegistryKey(_T("UESTC-PRMI"));
	// �жϱ������Ƿ��Ѿ�����,������,��ر�
	HWND SmartPlayer = ::FindWindowA(NULL, PLAYER_NAME);
	if(SmartPlayer)
	{
		int nRes = AfxMessageBox("���ѿ���SmartPlayer,�Ƿ�ر�?", MB_YESNO | MB_ICONQUESTION);
		if(nRes == IDYES)
		{
			// �ȹر�SmartControl,�����´򿪴��ڶ���Ϣ��������
			HWND SmartControl = ::FindWindowA(NULL, CONTROL_NAME);
			if(SmartControl)
				::SendMessageA(SmartControl, WM_CLOSE, 0, 0);
			Sleep(10);

			::SendMessageA(SmartPlayer, WM_CLOSE, 0, 0);
		}
		else
		{
			//��ʾ����
			::ShowWindow(SmartPlayer, SW_NORMAL);

			//ǰ����ʾ
			::SetForegroundWindow(SmartPlayer);

			//�����ö�
			// ::SetWindowPos(SmartPlayer, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			
			HWND SmartControl = ::FindWindowA(NULL, CONTROL_NAME);
			if(SmartControl)
			{
				::ShowWindow(SmartControl, SW_NORMAL);
				::SetForegroundWindow(SmartControl);
				// ::SetWindowPos(SmartControl, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			}

			return FALSE;
		}
	}

	PROCESS_INFORMATION RtspProcess;
	CSmartPlayerDlg* dlg = CSmartPlayerDlg::getInstance();
	m_pMainWnd = dlg;
	// 
	dlg->setProcessInfo(&RtspProcess);
	dlg->DoModal();

	// DWORD dwResult;
	// ��鲢�ر�RtspPlayer
	if(RtspProcess.hProcess != NULL)
	{
		::PostThreadMessageA(RtspProcess.dwThreadId, WM_PLAYER, WPARAM_STOP, 0);
		CloseHandle(RtspProcess.hProcess);
		RtspProcess.hProcess = NULL;
		//if(GetExitCodeThread(RtspProcess.hProcess, &dwResult))
		//{
		//	if(dwResult == STILL_ACTIVE)	//���˵���������У��ٹ�һ��
		//	{
		//		::PostThreadMessageA(RtspProcess.dwThreadId, WM_PLAYER, WPARAM_STOP, 0);
		//		Sleep(1000);
		//	}
		//	else
		//	{
		//		CloseHandle(RtspProcess.hProcess);
		//		RtspProcess.hProcess = NULL;
		//	}
		//}
		//else
		//{
		//	switch(GetLastError())
		//	{
		//		;
		//	}

		//	::PostThreadMessageA(RtspProcess.dwThreadId, WM_PLAYER, WPARAM_STOP, 0);
		//	CloseHandle(RtspProcess.hProcess);
		//	RtspProcess.hProcess = NULL;
		//}
	}
	// ��鲢�ر�SmartPlayer
	HWND SmartControl = ::FindWindowA(NULL, CONTROL_NAME);
	while(SmartControl != NULL)
	{
		SmartControl = ::FindWindowA(NULL, CONTROL_NAME);
		if(SmartControl)
		{
			::SendMessageA(SmartControl, WM_PLAYER, WPARAM_CLOSE, 0);
			Sleep(1000);
		}

	}


	// ɾ�����洴���� shell ��������
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// ���ڶԻ����ѹرգ����Խ����� FALSE �Ա��˳�Ӧ�ó���
	//  ����������Ӧ�ó������Ϣ�á�
	return FALSE;
}

