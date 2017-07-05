/*********************************************************** 
		文件名:		SmartPlayerDlg.h

		编辑工具:	Microsoft Visual Studio 2010

		作者:		UESTC-PRMI

		创建时间:	2014-10-18

		修改者:		
		
		修改时间:

		主要内容:	1、	负责对SmartControl和RtspPlayer两个进程
						的发起，管理，和结束。
					2、	负责请求接收视频数据，暂停播放视频，停
						止播放视频等功能。
					3、	负责对接收到的视频数据的显示。
***********************************************************/ 

#pragma once
#include "stdafx.h"
#include <stdio.h>
#include <Tlhelp32.h>

#include "StaticData.h"
#include "InputURLDlg.h"

// CSmartPlayerDlg 对话框
class CSmartPlayerDlg : public CDialogEx
{
// 构造
public:
	CSmartPlayerDlg(CWnd* pParent = NULL);	// 标准构造函数
	virtual ~CSmartPlayerDlg();
	static CSmartPlayerDlg* DlgInstance;
public:
// 对话框数据
	enum { IDD = IDD_SMARTPLAYER_DIALOG };

// 多进程同步使用
	PROCESS_INFORMATION*	m_process_info;		// 保存RtspPlayer进程信息

	// 将RTSPPlayer进程信息传出去(已弃用）
	void setProcessInfo(PROCESS_INFORMATION* ProcessInfo) {	m_process_info = ProcessInfo;	};

	LONG			m_screen_width;
	LONG			m_screen_height;	// 视频显示区域的rect,宽,高

	PlayerStatus	m_cur_status;		// 当前播放状态

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持

// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	static CSmartPlayerDlg* getInstance();

	LRESULT OnMessageFromRtsp(WPARAM wParam, LPARAM lParam);	// 多进程通讯,相应来自控制模块的消息

// 按键响应函数
	afx_msg void OnBnClickedButtonPlay();			// 播放
	afx_msg void OnBnClickedButtonPause();			// 暂停
	afx_msg void OnBnClickedButtonPlayStop();		// 停止
	afx_msg void OnBnClickedButtonExit();			// 退出

private:
	void InitPROCESS_INFORMATION(PROCESS_INFORMATION& pi);	// 初始化PROCESS_INFORMATION结构体
};