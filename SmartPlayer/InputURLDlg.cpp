/*********************************************************** 
		�ļ���:		InputURLDlg.cpp

		�༭����:	Microsoft Visual Studio 2010

		����:		UESTC-PRMI

		����ʱ��:	2014-10-18

		�޸���:		
		
		�޸�ʱ��:

		��Ҫ����:	InputURLDLG.hʵ���ļ�
***********************************************************/ 

#include "stdafx.h"
#include "InputURLDlg.h"
#include "afxdialogex.h"
#include "StaticData.h"

// CInputURLDlg �Ի���

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

	// ����URLĬ����ʾ�ı�,���ļ��ж�ȡ��һ����ȷ����ı���
	CFile URLFile;
	if(!(URLFile.Open(URLFILE, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeRead | CFile::typeBinary)))
	{
		MessageBox("��ȡURL�ļ�����", "��ʾ");
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

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

// CInputURLDlg ��Ϣ�������

// ������URLʱ������м򵥵��б��Ƿ���������
bool CInputURLDlg::JudgeURL(CString URL)
{
	// ����1��	URL.IsEmpty():URLΪ��,������
	// ����2��	һ�������,��ַ��ʽΪ:rtsp://xxx.xxx.xxx.xxx...,����22���ַ�
	// ����3��	ȡURLǰ7���ַ�,�����ִ�Сд�ıȽ��Ƿ�Ϊ"rtsp://",��ͬ������(��).
	if(URL.IsEmpty() || (URL.GetLength() < 22) || ((URL.Left(7)).CompareNoCase("rtsp://")))
		return false;
	else
	{
		URL = URL.Right(URL.GetLength() - 7);	// �õ���ȥ"rtsp://"ʣ�µ��ַ���
		int Pos = URL.FindOneOf(":/");
		if(-1 == Pos)		// ʣ�ಿ�ֲ��� ':' �� '/',��õ�ַ����
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

// �ж�һ��IP��ַ�Ƿ�Ϸ�, �Ϸ�:����true,���򷵻�false
bool CInputURLDlg::JudgeIP(CString IPAddress)
{
	int IP[] = {0, 0, 0, 0};
	int count = 0;
	int StrLenth = IPAddress.GetLength();
 
	// һ�������,IP��ַ��ʽΪxxx.xxx.xxx.xxx,��15���ַ�,�ʳ������Ϊ15
	if(StrLenth > 15)
		return false;
	
	// �����ʽ�ж�
	for(int i = 0; i < StrLenth; ++i)
	{	// ��������IP��ַ,�������ֻ��ߵ��,����û������,����'.'����.����,��ֱ�ӷ���false
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
	
	// �����Ķ�����,�ж�ȡֵ��Χ�Ƿ���ȷ
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	GetDlgItem(IDC_EDIT_URL)->GetWindowTextA(m_url);
	if(!JudgeURL(m_url))
	{
		MessageBox("URL��ַ����", "����");
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CDialogEx::OnCancel();
}
