/*********************************************************** 
		�ļ���:		InputURLDlg.h	ͷ�ļ�

		�༭����:	Microsoft Visual Studio 2010

		����:		UESTC-PRMI

		����ʱ��:	2014-10-18

		�޸���:		
		
		�޸�ʱ��:

		��Ҫ����:	1��	�����û�url��ַ����
					2��	�����յ���url��ַд��DATA�ļ�����url.pref�ļ�
					3��	�ж�����url��ַ����ȷ��
***********************************************************/ 

#pragma once
#include "stdafx.h"
#include "resource.h"

// CInputURLDlg �Ի���

class CInputURLDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInputURLDlg)

public:
	CInputURLDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CInputURLDlg();

// �Ի�������
	enum { IDD = IDD_INPUTURL_DIALOG };

private:
	CString m_url;	// Ψһ��˽�г�Ա���������ڱ�������url��ַ

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	bool JudgeURL(CString URL);						// URL��ַ��ȷ���򷵻�TRUE�����򷵻�FALSE
	bool JudgeIP(CString IPAddress);				// �ж�����url��ַ��ip��ַ�Ƿ�������JudgeURL()�б�����
public:
	CString GetURL();

	// <ȷ��>��<ȡ��>������Ӧ����
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
