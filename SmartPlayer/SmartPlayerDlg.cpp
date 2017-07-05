
// SmartPlayerDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "SmartPlayer.h"
#include "SmartPlayerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CSmartPlayerDlg���о�̬������ʼ��
CSmartPlayerDlg* CSmartPlayerDlg::DlgInstance = NULL;


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���
class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
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


// CSmartPlayerDlg �Ի���
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


// CSmartPlayerDlg ��Ϣ�������

// �������Ի���Ψһ���
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

// ��������
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

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
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

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���

	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

////////////////////////////////////////////////////////////////////////////////////////////////////
/////��ʼ������
////////////////////////////////////////////////////////////////////////////////////////////////////
	// ����ʹ��,����DATA�ļ���,�Լ�playwndbackground.bmp�ļ�
	if(!PathIsDirectory(FOLDERPATH))		
	{
		if(!CreateDirectory(FOLDERPATH, NULL))
		{
			CString strMsg = "";
			strMsg.Format   ("����·��\"%s\"ʧ�ܣ�", FOLDERPATH);
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
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

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CSmartPlayerDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
// ��ʾ��
HCURSOR CSmartPlayerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


LRESULT CSmartPlayerDlg::OnMessageFromRtsp(WPARAM wParam, LPARAM lParam)
{
	int which = wParam;

	CBitmap bitmap;  // CBitmap�������ڼ���λͼ   
	HBITMAP hBmp;    // ����CBitmap���ص�λͼ�ľ��   

	switch(which)
	{
	case WPARAM_START:	// RtspPlayer��ʼ����
		// ��ScreenWidth �� ScreenHeight ��֮
		PostThreadMessage(m_process_info->dwThreadId, WM_PLAYER, m_screen_width, m_screen_height);
		
		break;
	case WPARAM_CLOSE:	// ��������
		/*MessageBox("�ҽ��յ���RTSP������WPARAM_CLOSE", "��ʾ");*/
		// ���水������
		GetDlgItem(IDC_BUTTON_PLAY)->EnableWindow(true);
		GetDlgItem(IDC_BUTTON_PAUSE)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_PLAYSTOP)->EnableWindow(false);
		GetDlgItem(IDC_BUTTON_SMARTCTRL)->EnableWindow(false);

		bitmap.LoadBitmap(IDB_PLAYWND);  // ��λͼIDB_BITMAP1���ص�bitmap   
		hBmp = (HBITMAP)bitmap.GetSafeHandle();  // ��ȡbitmap����λͼ�ľ��   
		((CStatic*)GetDlgItem(IDC_PLAYWND))->SetBitmap(hBmp);    // ����ͼƬ�ؼ�m_jzmPicture��λͼͼƬΪIDB_BITMAP1   

		// ��鲢�ر�RtspPlayer
		while(m_process_info->hProcess != NULL)
		{
			DWORD dwResult;
			GetExitCodeThread(m_process_info->hProcess, &dwResult);
			if(dwResult == STILL_ACTIVE)	//���˵���������У��ٹ�һ��
			{
				PostThreadMessage(m_process_info->dwThreadId, WM_PLAYER, WPARAM_STOP, 0);
				Sleep(500);
			}
			else
				InitPROCESS_INFORMATION(*m_process_info);
		}
		
		m_cur_status = NOTHING;
		MessageBox("���Ž���", "��ʾ");
		// PostThreadMessage(m_process_info.dwThreadId, WM_PLAYER, WPARAM_STOP, 0);
		break;
	case WPARAM_RECT:	// ����
		MessageBox("������յ�λ!", "��ʾ");
		break;
	case WPARAM_PLAYING:
		// ���水������
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
			GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowTextA("��ͣ");
			m_cur_status = PLAYING;
			break;
		case PLAYING:
			GetDlgItem(IDC_BUTTON_PAUSE)->SetWindowTextA("����");
			m_cur_status = PAUSE;
			break;
		default:
			break;
		}

		break;
	case WPARAM_STOP:	// ����
		/*MessageBox("�ҽ��յ���WPARAM_STOP", "��ʾ");*/
		// ���水������
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

	// MessageBox("�ҽ��յ���WM_CONTROL", "��ʾ");
	return 0;
}

// <����>������Ӧ����
void CSmartPlayerDlg::OnBnClickedButtonPlay()
{
	if(WAITING == m_cur_status)
	{
		MessageBox("���������ƶ�������,���Ժ�", "��ʾ");
		return;
	}

// ͨ��URL����Ի������û������URL��ַ
	int			ret;
	CString		sUrl;
	CInputURLDlg* InputURLDlg = new CInputURLDlg();
	ret = InputURLDlg->DoModal();		// ��������URL�ĶԻ���,����ȡ����ֵ
	if(IDOK == ret)						// ���OK���ȡ�����URL,����ֱ�ӷ���
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

		sprintf(CommandLine, "SDL_WINDOWID=%d", hWnd);    // �����ھ��

		STARTUPINFO si={sizeof(si)};
		BOOL b = CreateProcess(RTSPPLAYERPATH, CommandLine, NULL, NULL, FALSE, NULL, NULL, NULL, &si, m_process_info);
		if(!b)
		{
			MessageBox("Զ����Ƶ����ʧ��!", "��ʾ");
			return;
		}
	}

	m_cur_status = WAITING;

}

// <��ͣ>������Ӧ����
void CSmartPlayerDlg::OnBnClickedButtonPause()
{
	if((NOTHING == m_cur_status) || (WAITING == m_cur_status))
		return;

	PostThreadMessage(m_process_info->dwThreadId, WM_PLAYER, WPARAM_PAUSE, 0);

}

// <ֹͣ>������Ӧ����
void CSmartPlayerDlg::OnBnClickedButtonPlayStop()
{
	if((NOTHING == m_cur_status) || (WAITING == m_cur_status))
		return;

	PostThreadMessage(m_process_info->dwThreadId, WM_PLAYER, WPARAM_STOP, 0);
	
}

// <�˳�>������Ӧ����
void CSmartPlayerDlg::OnBnClickedButtonExit()
{
	PostThreadMessage(m_process_info->dwThreadId, WM_PLAYER, WPARAM_STOP, 0);

	SendMessage(WM_CLOSE);
}


