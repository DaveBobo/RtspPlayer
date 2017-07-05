
// SmartPlayerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "SmartPlayer.h"
#include "SmartPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSmartPlayerDlg类中静态变量初始化
CSmartPlayerDlg* CSmartPlayerDlg::DlgInstance = NULL;


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};


CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}


void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_LBUTTONDOWN()
END_MESSAGE_MAP()


// CSmartPlayerDlg 对话框
CSmartPlayerDlg::CSmartPlayerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CSmartPlayerDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CSmartPlayerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CSmartPlayerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_TIMER()
	ON_WM_GETMINMAXINFO()
	ON_WM_QUERYDRAGICON()
	ON_MESSAGE(WM_RTSP, OnMessageFromRtsp)
	ON_BN_CLICKED(IDC_BUTTON_PLAY, &CSmartPlayerDlg::OnBnClickedButtonPlay)
	ON_BN_CLICKED(IDC_BUTTON_PAUSE, &CSmartPlayerDlg::OnBnClickedButtonPause)
	ON_BN_CLICKED(IDC_BUTTON_PLAYSTOP, &CSmartPlayerDlg::OnBnClickedButtonPlayStop)
	ON_BN_CLICKED(IDC_BUTTON_EXIT, &CSmartPlayerDlg::OnBnClickedButtonExit)
END_MESSAGE_MAP()


// CSmartPlayerDlg 消息处理程序

// 创建本对话框唯一入口
CSmartPlayerDlg* CSmartPlayerDlg::getInstance()
{
	if(DlgInstance)
	{
		delete[] DlgInstance;
		DlgInstance = NULL;
	}

	DlgInstance = new CSmartPlayerDlg;
	return DlgInstance;
}

// 析构函数
CSmartPlayerDlg::~CSmartPlayerDlg()
{
	;
}

void CSmartPlayerDlg::InitPROCESS_INFORMATION(PROCESS_INFORMATION& pi)
{
	pi.dwProcessId = 0;
	pi.dwThreadId = 0;
	pi.hProcess = NULL;
	pi.hThread = NULL;
}

BOOL CSmartPlayerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作

	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

////////////////////////////////////////////////////////////////////////////////////////////////////
/////初始化窗口
////////////////////////////////////////////////////////////////////////////////////////////////////
	// 初次使用,创建DATA文件夹,以及playwndbackground.bmp文件
	if(!PathIsDirectory(FOLDERPATH))		
	{
		if(!CreateDirectory(FOLDERPATH, NULL))
		{
			CString strMsg = "";
			strMsg.Format   ("创建路径\"%s\"失败！", FOLDERPATH);
			OnBnClickedButtonExit();
			return TRUE;
		}
	}

	GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(true);
	GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_PLAYSTOP)->EnableWindow(false);
	GetDlgItem(IDC_BUTTON_SMARTCTRL)->EnableWindow(false);

	m_cur_status		= NOTHING;

	InitPROCESS_INFORMATION(*m_process_info);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CSmartPlayerDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CSmartPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 当用户拖动最小化窗口时系统调用此函数取得光标
// 显示。
HCURSOR CSmartPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LRESULT CSmartPlayerDlg::OnMessageFromRtsp(WPARAM wParam, LPARAM lParam)
{
	int which = wParam;

	CBitmap bitmap;  // CBitmap对象，用于加载位图   
	HBITMAP hBmp;    // 保存CBitmap加载的位图的句柄   

	switch(which)
	{
	case WPARAM_START:	// RtspPlayer开始运行
		// 将ScreenWidth 和 ScreenHeight 告之
		PostThreadMessage(m_process_info->dwThreadId, WM_PLAYER, m_screen_width, m_screen_height);
		
		break;
	case WPARAM_CLOSE:	// 结束播放
		/*MessageBox("我接收到了RTSP发来的WPARAM_CLOSE", "提示");*/
		// 界面按键控制
		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_PLAYSTOP)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_SMARTCTRL)->EnableWindow(false);

		bitmap.LoadBitmap(IDB_PLAYWND);  // 将位图IDB_BITMAP1加载到bitmap   
		hBmp = (HBITMAP)bitmap.GetSafeHandle();  // 获取bitmap加载位图的句柄   
		((CStatic*)GetDlgItem(IDC_PLAYWND))->SetBitmap(hBmp);    // 设置图片控件m_jzmPicture的位图图片为IDB_BITMAP1   

		// 检查并关闭RtspPlayer
		while(m_process_info->hProcess != NULL)
		{
			DWORD dwResult;
			GetExitCodeThread(m_process_info->hProcess, &dwResult);
			if(dwResult == STILL_ACTIVE)	//如果说明还在运行，再关一次
			{
				PostThreadMessage(m_process_info->dwThreadId, WM_PLAYER, WPARAM_STOP, 0);
				Sleep(500);
			}
			else
				InitPROCESS_INFORMATION(*m_process_info);
		}
		
		m_cur_status = NOTHING;
		MessageBox("播放结束", "提示");
		// PostThreadMessage(m_process_info.dwThreadId, WM_PLAYER, WPARAM_STOP, 0);
		break;
	case WPARAM_RECT:	// 保留
		MessageBox("长宽接收到位!", "提示");
		break;
	case WPARAM_PLAYING:
		// 界面按键控制
		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_PLAYSTOP)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_SMARTCTRL)->EnableWindow(true);
		
		m_cur_status = PLAYING;
		break;
	case WPARAM_PAUSE:
		switch(m_cur_status)
		{
		case PAUSE:
			GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowTextA("暂停");
			m_cur_status = PLAYING;
			break;
		case PLAYING:
			GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowTextA("播放");
			m_cur_status = PAUSE;
			break;
		default:
			break;
		}

		break;
	case WPARAM_STOP:	// 保留
		/*MessageBox("我接收到了WPARAM_STOP", "提示");*/
		// 界面按键控制
		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_PLAYSTOP)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_SMARTCTRL)->EnableWindow(false);
		InitPROCESS_INFORMATION(*m_process_info);
		m_cur_status = NOTHING;
		break;
	default:
		break;
	}

	// MessageBox("我接收到了WM_CONTROL", "提示");
	return 0;
}

// <播放>按键响应函数
void CSmartPlayerDlg::OnBnClickedButtonPlay()
{
	if(WAITING == m_cur_status)
	{
		MessageBox("正在连接移动机器人,请稍候", "提示");
		return;
	}

// 通过URL输入对话框获得用户输入的URL地址
	int			ret;
	CString		sUrl;
	CInputURLDlg* InputURLDlg = new CInputURLDlg();
	ret = InputURLDlg->DoModal();		// 弹出输入URL的对话框,并获取返回值
	if(IDOK == ret)						// 点击OK则获取输入的URL,否则直接返回
		sUrl = InputURLDlg->GetURL();
	else
		return;

	delete InputURLDlg;
	InputURLDlg = NULL;


	CRect			DisplayRect;

	GetDlgItem(IDC_PLAYWND)->GetWindowRect(&DisplayRect);
	ScreenToClient(DisplayRect);
	m_screen_width  = DisplayRect.right  - DisplayRect.left - 10;
	m_screen_height = DisplayRect.bottom - DisplayRect.top - 10;



	HWND hWnd = GetDlgItem(IDC_PLAYWND)->GetSafeHwnd();
	if(hWnd != NULL)
	{
		char CommandLine[128] = {0};

		sprintf(CommandLine, "SDL_WINDOWID=%d", hWnd);    // 主窗口句柄

		STARTUPINFO si={sizeof(si)};
		BOOL b = CreateProcess(RTSPPLAYERPATH, CommandLine, NULL, NULL, FALSE, NULL, NULL, NULL, &si, m_process_info);
		if(!b)
		{
			MessageBox("远程视频接收失败!", "提示");
			return;
		}
	}

	m_cur_status = WAITING;

}

// <暂停>按键响应函数
void CSmartPlayerDlg::OnBnClickedButtonPause()
{
	if((NOTHING == m_cur_status) || (WAITING == m_cur_status))
		return;

	PostThreadMessage(m_process_info->dwThreadId, WM_PLAYER, WPARAM_PAUSE, 0);

}

// <停止>按键响应函数
void CSmartPlayerDlg::OnBnClickedButtonPlayStop()
{
	if((NOTHING == m_cur_status) || (WAITING == m_cur_status))
		return;

	PostThreadMessage(m_process_info->dwThreadId, WM_PLAYER, WPARAM_STOP, 0);
	
}

// <退出>按键响应函数
void CSmartPlayerDlg::OnBnClickedButtonExit()
{
	PostThreadMessage(m_process_info->dwThreadId, WM_PLAYER, WPARAM_STOP, 0);

	SendMessage(WM_CLOSE);
}


