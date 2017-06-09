#pragma once
#include "global.h"
#include "GameControl.h"
#include "afxcmn.h"
#include "LLKDlg.h"
// CGameDlg �Ի���

class CGameDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CGameDlg)

public:
	CGameDlg(CWnd* pParent = NULL);   // ��׼���캯��
	virtual ~CGameDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAME_DIALOG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��
	

	DECLARE_MESSAGE_MAP()

public:

	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();

protected :
	CDC m_dcMem;		//�ڴ�DC
	CDC m_dcElement;	//Ԫ���ڴ�DC
	CDC m_dcMask;		//�����ڴ�DC
	CDC m_dcBG;			//����DC

	CDC m_dcPause;		//��ͣDC
	CDC m_dcCache;		//����DC
	//int m_anMap[4][4];		//��ʼ����ͼΪ4*4

	CPoint m_ptGameTop;		//��Ϸ��ʼ�㣨��Ϸ��һ��ͼƬ�Ķ��㣬��������ڴ��ڿͻ�����
	CSize m_sizeElem;		//Ԫ��ͼƬ�Ĵ�С
	CRect m_rtGameRect;		//��Ϸ�����С

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
