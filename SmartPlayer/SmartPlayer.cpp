
// SmartPlayer.cpp : 定义应用程序的类行为。
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


// CSmartPlayerApp 构造

CSmartPlayerApp::CSmartPlayerApp()
{
	// 支持重新启动管理器
	m_dwRestartManagerSupportFlags = AFX_RESTART_MANAGER_SUPPORT_RESTART;

	// TODO: 在此处添加构造代码，
	// 将所有重要的初始化放置在 InitInstance 中
}


// 唯一的一个 CSmartPlayerApp 对象

CSmartPlayerApp theApp;


// CSmartPlayerApp 初始化

BOOL CSmartPlayerApp::InitInstance()
{
	// 如果一个运行在 Windows XP 上的应用程序清单指定要
	// 使用 ComCtl32.dll 版本 6 或更高版本来启用可视化方式，
	//则需要 InitCommonControlsEx()。否则，将无法创建窗口。
	INITCOMMONCONTROLSEX InitCtrls;
	InitCtrls.dwSize = sizeof(InitCtrls);
	// 将它设置为包括所有要在应用程序中使用的
	// 公共控件类。
	InitCtrls.dwICC = ICC_WIN95_CLASSES;
	InitCommonControlsEx(&InitCtrls);

	CWinApp::InitInstance();


	AfxEnableControlContainer();

	// 创建 shell 管理器，以防对话框包含
	// 任何 shell 树视图控件或 shell 列表视图控件。
	CShellManager *pShellManager = new CShellManager;

	// 标准初始化
	// 如果未使用这些功能并希望减小
	// 最终可执行文件的大小，则应移除下列
	// 不需要的特定初始化例程
	// 更改用于存储设置的注册表项
	// TODO: 应适当修改该字符串，
	// 例如修改为公司或组织名
	SetRegistryKey(_T("UESTC-PRMI"));
	// 判断本窗口是否已经存在,若存在,则关闭
	HWND SmartPlayer = ::FindWindowA(NULL, PLAYER_NAME);
	if(SmartPlayer)
	{
		int nRes = AfxMessageBox("您已开启SmartPlayer,是否关闭?", MB_YESNO | MB_ICONQUESTION);
		if(nRes == IDYES)
		{
			// 先关闭SmartControl,避免新打开窗口对消息进行误判
			HWND SmartControl = ::FindWindowA(NULL, CONTROL_NAME);
			if(SmartControl)
				::SendMessageA(SmartControl, WM_CLOSE, 0, 0);
			Sleep(10);

			::SendMessageA(SmartPlayer, WM_CLOSE, 0, 0);
		}
		else
		{
			//显示窗口
			::ShowWindow(SmartPlayer, SW_NORMAL);

			//前端显示
			::SetForegroundWindow(SmartPlayer);

			//窗口置顶
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
	// 检查并关闭RtspPlayer
	if(RtspProcess.hProcess != NULL)
	{
		::PostThreadMessageA(RtspProcess.dwThreadId, WM_PLAYER, WPARAM_STOP, 0);
		CloseHandle(RtspProcess.hProcess);
		RtspProcess.hProcess = NULL;
		//if(GetExitCodeThread(RtspProcess.hProcess, &dwResult))
		//{
		//	if(dwResult == STILL_ACTIVE)	//如果说明还在运行，再关一次
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
	// 检查并关闭SmartPlayer
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


	// 删除上面创建的 shell 管理器。
	if (pShellManager != NULL)
	{
		delete pShellManager;
	}

	// 由于对话框已关闭，所以将返回 FALSE 以便退出应用程序，
	//  而不是启动应用程序的消息泵。
	return FALSE;
}

