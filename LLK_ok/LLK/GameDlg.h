#pragma once
#include "global.h"
#include "GameControl.h"
#include "afxcmn.h"
#include "LLKDlg.h"
// CGameDlg 对话框

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CGameDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	

	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

protected :
	CDC m_dcMem;		//内存DC
	CDC m_dcElement;	//元素内存DC
	CDC m_dcMask;		//掩码内存DC
	CDC m_dcBG;			//背景DC

	CDC m_dcPause;		//暂停DC
	CDC m_dcCache;		//缓存DC
	//int m_anMap[4][4];		//初始化地图为4*4

	CPoint m_ptGameTop;		//游戏起始点（游戏第一张图片的顶点，坐标相对于窗口客户区）
	CSize m_sizeElem;		//元素图片的大小
	CRect m_rtGameRect;		//游戏区域大小

	CGameControl m_gameControl;
	CLLKDlg m_llkDlg;
	CGameControl *m_pGameC;

	FLAG m_flag;

	bool m_bFirstPoint;
	bool m_bPlaying;
	bool m_bPause;

	VerTex m_ptSelFirst;
	VerTex m_ptSelSec;
	
	

	void InitBackground();
	void InitElement();
	void UpdateMap();
	void DrawTipFrame(int nRow, int nCol);
	bool IsLink();
	void DrawTipLine(VerTex avPath[4], int nVernum);
	void DrawGameTime();


public:
	afx_msg void OnClickedBtnStart();
	afx_msg void OnLButtonUp(UINT nFlags, CPoint point);

	afx_msg void OnTimer(UINT_PTR nIDEvent);
	afx_msg void OnClickedBtnPause();
	afx_msg void OnClickedBtnHelp();
	afx_msg void OnClickedBtnPrompt();


	CProgressCtrl m_GamePrograss;

	void SetGameModel(CGameControl* pGameC);

//	afx_msg void OnClickedBtnReset();
	afx_msg void OnClickedBtnReset();
};
