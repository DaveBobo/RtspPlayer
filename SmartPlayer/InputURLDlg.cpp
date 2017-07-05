/*********************************************************** 
		文件名:		InputURLDlg.cpp

		编辑工具:	Microsoft Visual Studio 2010

		作者:		UESTC-PRMI

		创建时间:	2014-10-18

		修改者:		
		
		修改时间:

		主要内容:	InputURLDLG.h实现文件
***********************************************************/ 

#include "stdafx.h"
#include "InputURLDlg.h"
#include "afxdialogex.h"
#include "StaticData.h"

// CInputURLDlg 对话框

IMPLEMENT_DYNAMIC(CInputURLDlg, CDialogEx)

CInputURLDlg::CInputURLDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CInputURLDlg::IDD, pParent)
{

}

CInputURLDlg::~CInputURLDlg()
{
}

void CInputURLDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CInputURLDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CInputURLDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CInputURLDlg::OnBnClickedCancel)
END_MESSAGE_MAP()

BOOL CInputURLDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 定义URL默认显示文本,从文件中读取上一次正确输入的备份
	CFile URLFile;
	if(!(URLFile.Open(URLFILE, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeRead | CFile::typeBinary)))
	{
		MessageBox("读取URL文件错误", "提示");
		m_url = "rtsp://";
	}
	else
	{
		int FileLength = URLFile.GetLength();
		if(0 == URLFile.Read(m_url.GetBuffer(FileLength), FileLength))
			m_url = "rtsp://";
		m_url.ReleaseBuffer();
	}

	GetDlgItem(IDC_EDIT_URL)->SetWindowTextA(m_url);
	GetDlgItem(IDC_EDIT_URL)->SetFocus();
	((CEdit*)GetDlgItem(IDC_EDIT_URL))->SetSel(0,-1,TRUE);

	URLFile.Close();

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// CInputURLDlg 消息处理程序

// 在输入URL时对其进行简单的判别是否输入有误
bool CInputURLDlg::JudgeURL(CString URL)
{
	// 条件1、	URL.IsEmpty():URL为空,返回真
	// 条件2、	一般情况下,地址形式为:rtsp://xxx.xxx.xxx.xxx...,至少22个字符
	// 条件3、	取URL前7个字符,不区分大小写的比较是否为"rtsp://",相同返回零(假).
	if(URL.IsEmpty() || (URL.GetLength() < 22) || ((URL.Left(7)).CompareNoCase("rtsp://")))
		return false;
	else
	{
		URL = URL.Right(URL.GetLength() - 7);	// 得到除去"rtsp://"剩下的字符串
		int Pos = URL.FindOneOf(":/");
		if(-1 == Pos)		// 剩余部分不含 ':' 或 '/',则该地址错误
			return false;
		else
		{
			CString IPAddress = URL.Left(Pos);
			if(!JudgeIP(IPAddress))
				return false;
			else
				return true;
		}
	}
}

// 判断一个IP地址是否合法, 合法:返回true,否则返回false
bool CInputURLDlg::JudgeIP(CString IPAddress)
{
	int IP[] = {0, 0, 0, 0};
	int count = 0;
	int StrLenth = IPAddress.GetLength();
 
	// 一般情况下,IP地址格式为xxx.xxx.xxx.xxx,共15个字符,故长度最大为15
	if(StrLenth > 15)
		return false;
	
	// 规则格式判断
	for(int i = 0; i < StrLenth; ++i)
	{	// 遍历整个IP地址,都是数字或者点号,而且没有连点,并对'.'计数.不是,则直接返回false
		if((IPAddress.GetAt(i) >= '0') && (IPAddress.GetAt(i) <= '9'))
			continue;
		else if((IPAddress.GetAt(i) == '.') && (IPAddress.GetAt(i + 1) != '.'))
		{
			if(0 == i)
				return false;
			else
				++count;
		}
		else
			return false;
	}
	int flag = sscanf(IPAddress.GetBuffer(StrLenth), "%d.%d.%d.%d", IP + 0, IP + 1, IP + 2, IP + 3);
	IPAddress.ReleaseBuffer();

	if(count != 3 || flag != 4)	
		return false;
	
	// 遍历四段数字,判断取值范围是否正确
	for(int i = 0; i < 4; ++i)
		if((IP[i] > 255) || (IP[i] < 0))
			return false;
	return true;
}

CString CInputURLDlg::GetURL()
{
	return m_url;
}

void CInputURLDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_EDIT_URL)->GetWindowTextA(m_url);
	if(!JudgeURL(m_url))
	{
		MessageBox("URL地址错误！", "错误");
		GetDlgItem(IDC_EDIT_URL)->SetWindowTextA("rtsp://");
		return;
	}
	else
	{
		CFile URLFile;
		if(!(URLFile.Open(URLFILE, CFile::modeCreate | CFile::modeWrite | CFile::typeBinary)))
			return CDialogEx::OnOK();

		URLFile.Write(m_url, m_url.GetLength());

		URLFile.Close();
	}
	CDialogEx::OnOK();
}


void CInputURLDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnCancel();
}
