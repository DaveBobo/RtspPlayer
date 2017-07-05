/*********************************************************** 
		�ļ���:		SmartPlayerDlg.h

		�༭����:	Microsoft Visual Studio 2010

		����:		UESTC-PRMI

		����ʱ��:	2014-10-18

		�޸���:		
		
		�޸�ʱ��:

		��Ҫ����:	1��	�����SmartControl��RtspPlayer��������
						�ķ��𣬹����ͽ�����
					2��	�������������Ƶ���ݣ���ͣ������Ƶ��ͣ
						ֹ������Ƶ�ȹ��ܡ�
					3��	����Խ��յ�����Ƶ���ݵ���ʾ��
***********************************************************/ 

#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <Tlhelp32.h>

#include "StaticData.h"
#include "InputURLDlg.h"

// CSmartPlayerDlg �Ի���
class CSmartPlayerDlg : public CDialogEx
{
// ����
public:
	CSmartPlayerDlg(CWnd* pParent = NULL);	// ��׼���캯��
	virtual ~CSmartPlayerDlg();
	static CSmartPlayerDlg* DlgInstance;
public:
// �Ի�������
	enum { IDD = IDD_SMARTPLAYER_DIALOG };

// �����ͬ��ʹ��
	PROCESS_INFORMATION*	m_process_info;		// ����RtspPlayer������Ϣ

	// ��RTSPPlayer������Ϣ����ȥ(�����ã�
	void setProcessInfo(PROCESS_INFORMATION* ProcessInfo) {	m_process_info = ProcessInfo;	};

	LONG			m_screen_width;
	LONG			m_screen_height;	// ��Ƶ��ʾ�����rect,��,��

	PlayerStatus	m_cur_status;		// ��ǰ����״̬

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV ֧��

// ʵ��
protected:
	HICON m_hIcon;

	// ���ɵ���Ϣӳ�亯��
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	static CSmartPlayerDlg* getInstance();

	LRESULT OnMessageFromRtsp(WPARAM wParam, LPARAM lParam);	// �����ͨѶ,��Ӧ���Կ���ģ�����Ϣ

// ������Ӧ����
	afx_msg void OnBnClickedButtonPlay();			// ����
	afx_msg void OnBnClickedButtonPause();			// ��ͣ
	afx_msg void OnBnClickedButtonPlayStop();		// ֹͣ
	afx_msg void OnBnClickedButtonExit();			// �˳�

private:
	void InitPROCESS_INFORMATION(PROCESS_INFORMATION& pi);	// ��ʼ��PROCESS_INFORMATION�ṹ��
};