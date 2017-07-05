/*********************************************************** 
		文件名:		InputURLDlg.h	头文件

		编辑工具:	Microsoft Visual Studio 2010

		作者:		UESTC-PRMI

		创建时间:	2014-10-18

		修改者:		
		
		修改时间:

		主要内容:	1、	接收用户url地址输入
					2、	将接收到的url地址写入DATA文件夹下url.pref文件
					3、	判断输入url地址的正确性
***********************************************************/ 

#pragma once
#include "stdafx.h"
#include "resource.h"

// CInputURLDlg 对话框

class CInputURLDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CInputURLDlg)

public:
	CInputURLDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CInputURLDlg();

// 对话框数据
	enum { IDD = IDD_INPUTURL_DIALOG };

private:
	CString m_url;	// 唯一的私有成员变量。用于保存输入url地址

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	virtual BOOL OnInitDialog();

	DECLARE_MESSAGE_MAP()

private:
	bool JudgeURL(CString URL);						// URL地址正确，则返回TRUE；否则返回FALSE
	bool JudgeIP(CString IPAddress);				// 判断输入url地址中ip地址是否有误，在JudgeURL()中被调用
public:
	CString GetURL();

	// <确定>、<取消>按键响应函数
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
