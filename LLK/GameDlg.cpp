// GameDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg.h"
#include "afxdialogex.h"
#include "GameControl.h"
#include "GameLogic.h"
#include "resource.h"
#include "global.h"
// CGameDlg 对话框

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;

	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	//初始化游戏更新区域
	m_rtGameRect.top = m_ptGameTop.y;
	m_rtGameRect.left = m_ptGameTop.x;
	m_rtGameRect.right = m_rtGameRect.left + m_sizeElem.cx * MAX_COL;
	m_rtGameRect.bottom = m_rtGameRect.top + m_sizeElem.cy * MAX_ROW;

	m_bFirstPoint = true;

	m_bPause = true;
}

CGameDlg::~CGameDlg()
{
}

void CGameDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_GAME_TIME, m_GamePrograss);
}

BEGIN_MESSAGE_MAP(CGameDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_START, &CGameDlg::OnClickedBtnStart)
	ON_WM_LBUTTONUP()
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BTN_PAUSE, &CGameDlg::OnClickedBtnPause)
	ON_BN_CLICKED(IDC_BTN_HELP, &CGameDlg::OnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BTN_PROMPT, &CGameDlg::OnClickedBtnPrompt)
//	ON_BN_CLICKED(IDC_BTN_RESET, &CGameDlg::OnClickedBtnReset)
ON_BN_CLICKED(IDC_BTN_RESET, &CGameDlg::OnClickedBtnReset)
END_MESSAGE_MAP()

// CGameDlg 消息处理程序
void CGameDlg::InitBackground() 
{
	CClientDC dc(this);	//获得当前对话框的视频内容

	//调用API
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

	//创建与视频内存兼容的内存DC
	m_dcBG.CreateCompatibleDC(&dc);
	//将位图资源选进DC
	m_dcBG.SelectObject(hBmpBG);

	//初始化内存DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	//将位图选进DC
	m_dcMem.SelectObject(&bmpMem);
	//绘制背景到内存DC中
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
}

//初始化对话框
BOOL CGameDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	InitBackground();

	InitElement();

	m_flag = m_pGameC->GetGameFlag();
	return TRUE;
}


void CGameDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
					   // TODO: 在此处添加消息处理程序代码
					   // 不为绘图消息调用 CDialogEx::OnPaint()
	dc.BitBlt(0,0,800,600,&m_dcMem,0,0,SRCCOPY);
}

//初始化数据
void CGameDlg::InitElement()
{
	CClientDC dc(this);	//获得当前对话框的视频内存

	//调用API，加载BMP图片资源
	HANDLE bmpElement = ::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	m_dcElement.CreateCompatibleDC(&dc);
	//将位图选进DC
	m_dcElement.SelectObject(bmpElement);


	//调用API，加载BMP图片资源
	HANDLE bmpMask = ::LoadImage(NULL, _T("theme\\picture\\fruit_mask.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//创建与视频内存兼容的内存DC
	m_dcMask.CreateCompatibleDC(&dc);
	//将位图选进DC
	m_dcMask.SelectObject(bmpMask);

	HANDLE bmpPause =::LoadImage(NULL,_T("theme\\picture\\pause.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	m_dcPause.CreateCompatibleDC(&dc);
	m_dcPause.SelectObject(bmpPause);
	m_dcCache.CreateCompatibleDC(&dc);
	CBitmap bmpCache;
	bmpCache.CreateCompatibleBitmap(&dc, 640, 400);
	m_dcCache.SelectObject(bmpCache);
	m_dcCache.BitBlt(0, 0, 640, 400, &m_dcPause, 0, 0, SRCCOPY);
}

//更新地图
void CGameDlg::UpdateMap()
{
	//计算图片的顶点坐标与图片大小
	int nTop = m_ptGameTop.y;
	int nLeft = m_ptGameTop.x;
	int nElemW = m_sizeElem.cx;
	int nElemH = m_sizeElem.cy;



	m_dcMem.BitBlt(m_rtGameRect.left, m_rtGameRect.top,
		m_rtGameRect.Width(), m_rtGameRect.Height(), &m_dcBG,
		m_rtGameRect.left, m_rtGameRect.top, SRCCOPY);


	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			/*m_dcMem.BitBlt(nLeft + j*nElenW, nTop + i*nElenH, nElenW, nElenH,
			&m_dcElement, 0, m_anMap[i][j] * nElenH, SRCCOPY);*/
			int nInfo = m_gameControl.GetElement(i,j);
			if (nInfo == BLANK) continue;
			//将背景与编码相或，边保留，图像区域为1
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH,
				&m_dcMask, 0, nInfo * nElemH, SRCPAINT);
			//将背景与元素图片相与，边保留，图像区域为元素图片
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH,
				&m_dcElement, 0, nInfo * nElemH, SRCAND);

		}
	}
}

//按钮响应函数
void CGameDlg::OnClickedBtnStart()
{


	//初始化游戏地图
	m_gameControl.StartGame();
	//更新界面
	UpdateMap();
	

	//游戏标识设为true
	m_bPlaying = true;
	//禁止按钮点击
	this->GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);

	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(SW_SHOW);

	if (m_flag.csTitle == _T("欢乐连连看—基本模式 by 温皓"))
	{
		this->SetWindowTextW(m_flag.csTitle);
		//初始化进度条
		m_GamePrograss.SetRange(0, 60 * 5);	//初始范围
		m_GamePrograss.SetStep(-1);		//初始步数值
		m_GamePrograss.SetPos(60 * 5);	//设置初始值
										//启动定时器
		this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
		//绘制当前秒数
		DrawGameTime();
		//更新窗口
	}
	if (m_flag.csTitle == _T("欢乐连连看—休闲模式 by 温皓"))
	{
		this->SetWindowTextW(m_flag.csTitle);
		//初始化进度条
		m_GamePrograss.SetRange(0, 60 * 5);	//初始范围
		m_GamePrograss.SetStep(-1);		//初始步数值
		m_GamePrograss.SetPos(60 * 5);	//设置初始值
										//启动定时器
		//this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
		//绘制当前秒数
		DrawGameTime();
		//更新窗口
	}
	if (m_flag.csTitle == _T("欢乐连连看—关卡模式 by 温皓"))
	{
		this->SetWindowTextW(m_flag.csTitle);
		//初始化进度条
		m_GamePrograss.SetRange(0, 60 * 5);	//初始范围
		m_GamePrograss.SetStep(-1);		//初始步数值
		m_GamePrograss.SetPos(60 * 5);	//设置初始值
										//启动定时器
		this->SetTimer(PLAY_TIMER_ID, 500, NULL);
		//绘制当前秒数
		DrawGameTime();
	}
	//更新窗口
	InvalidateRect(m_rtGameRect, FALSE);
}

//鼠标消息相应函数
void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	//判断点击位置的坐标是否在游戏的上面或者左边
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	//计算鼠标点击的位置的行号与列号
	int nRow = (point.y - m_ptGameTop.y) / m_sizeElem.cy;
	int nCol = (point.x - m_ptGameTop.x) / m_sizeElem.cx;
	if (nRow > MAX_ROW-1 || nCol > MAX_COL-1)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}

	if (m_bFirstPoint)
	{
		DrawTipFrame(nRow, nCol);
		/*m_ptSelFirst.col = nCol;
		m_ptSelFirst.row = nRow;*/
		m_gameControl.SetFirstPoint(nRow, nCol);
	}
	else
	{
		DrawTipFrame(nRow, nCol);
		/*m_ptSelSec.col = nCol;
		m_ptSelSec.row = nRow;*/
		m_gameControl.SetSecPoint(nRow, nCol);

		//活动路径
		VerTex avPath[4];
		int Vernum = 0;
		//判断是否是相同图片
		if (m_gameControl.Link(avPath,Vernum))
		{
			//画提示线
			DrawTipLine(avPath, Vernum);
		
		//更新地图
			UpdateMap();
			Sleep(200);
			InvalidateRect(m_rtGameRect, FALSE);	//在更新游戏地图时，声明游戏地图无效，能最低限度的减少屏幕闪烁
		}
		int bGameStatus = m_GamePrograss.GetPos();

		CString strTitle;
		this->GetWindowTextW(strTitle);
		//判断胜负 
		if (m_gameControl.IsWin() && bGameStatus > 0 && m_bPlaying)
		{
			m_bPlaying = false;
			KillTimer(PLAY_TIMER_ID);
			MessageBox(_T("YOU WIN!!!!"), strTitle);
			this->GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
		}
		if (bGameStatus == 0)
		{
			MessageBox(_T("傻盖儿"), strTitle);
			this->GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
		}
	}
	m_bFirstPoint = !m_bFirstPoint;
	
}

void CGameDlg :: DrawTipFrame(int nRow,int nCol)
{
	CClientDC dc(this);
	CBrush brush(RGB(233, 43, 43));
	CRect rtTipFrame;
	rtTipFrame.left = m_ptGameTop.x + nCol*m_sizeElem.cx;
	rtTipFrame.top = m_ptGameTop.y + nRow*m_sizeElem.cy;
	rtTipFrame.right = rtTipFrame.left + m_sizeElem.cx;
	rtTipFrame.bottom = rtTipFrame.top + m_sizeElem.cy;
	dc.FrameRect(rtTipFrame, &brush);

}

//判断选择的图片是否是同一种图片
//bool CGameDlg::IsLink()
//{
//	/*if (m_gameControl.GetElement[m_ptSelFirst.row][m_ptSelFirst.col] == m_gameControl.GetElement[m_ptSelSec.row][m_ptSelSec.col])
//	{
//		return true;
//	}*/
//	return false;
//}

//绘制连接线
void CGameDlg::DrawTipLine(VerTex avPath[4],int nVernum)
{
	//获取DC
	CClientDC dc(this);

	//设置画笔
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//将画笔选入DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	//绘制连接线
	dc.MoveTo(m_ptGameTop.x + avPath[0].col*m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + avPath[0].row*m_sizeElem.cy + m_sizeElem.cy / 2);
	dc.LineTo(m_ptGameTop.x + avPath[1].col*m_sizeElem.cx + m_sizeElem.cx / 2,
		m_ptGameTop.y + avPath[1].row*m_sizeElem.cy + m_sizeElem.cy / 2);

	for (int i = 1; i < nVernum; i++)
	{
		dc.LineTo(m_ptGameTop.x + avPath[i].col*m_sizeElem.cx + m_sizeElem.cx / 2,
			m_ptGameTop.y + avPath[i].row*m_sizeElem.cy + m_sizeElem.cy / 2);
	}

	dc.SelectObject(pOldPen);

}

void CGameDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: 在此添加消息处理程序代码和/或调用默认值
	DrawGameTime();
	if (nIDEvent == PLAY_TIMER_ID&&m_bPlaying)
	{
		//游戏时间减1s
		m_GamePrograss.StepIt();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CGameDlg::DrawGameTime()
{
	//创建字体
	CFont timeFont;
	timeFont.CreatePointFont(200, _T("Consolas"));
	CFont * oldFont;
	oldFont = m_dcMem.SelectObject(&timeFont);
	m_dcMem.SetTextColor(RGB(215, 202, 153));
	m_dcMem.SetBkColor(RGB(0,255,255,255));
	int time = m_GamePrograss.GetPos();
	CString strTime;
	strTime.Format(_T("%d s"), time);
	CRect rect;
	GetClientRect(&rect);
	CSize size;
	size = m_dcMem.GetTextExtent(strTime, strTime.GetLength());
	int x = ((rect.Width() - size.cx) / 2) + 280;
	int y = ((rect.Height() - size.cy) / 2) + 240;
	m_dcMem.TextOutW(x, y, strTime);

	m_dcMem.SelectObject(&timeFont);
	Invalidate(FALSE);
}

//暂停
void CGameDlg::OnClickedBtnPause()
{
	// TODO: 在此添加控件通知处理程序代码
	CClientDC dc(this);

	if (m_bPause)
	{
		KillTimer(PLAY_TIMER_ID);
		m_dcMem.BitBlt(50, 50, 640, 400, &m_dcCache, 0, 0, SRCCOPY);
		InvalidateRect(m_rtGameRect, FALSE);
		this->GetDlgItem(IDC_BTN_PAUSE)->SetWindowTextW(_T("继续游戏"));
	}
	else {
		this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
		UpdateMap();
		InvalidateRect(m_rtGameRect, FALSE);
		this->GetDlgItem(IDC_BTN_PAUSE)->SetWindowTextW(_T("暂停游戏"));
	}
	m_bPause = !m_bPause;
}

//帮助
void CGameDlg::OnClickedBtnHelp()
{
	// TODO: 在此添加控件通知处理程序代码
	CString strTitle;
	this->GetWindowTextW(strTitle);
	KillTimer(PLAY_TIMER_ID);
	if (MessageBox(_T("立即充值，成为会员，即可享有帮助功能"), strTitle, MB_OKCANCEL)== IDOK)
	{
		MessageBox(_T("我的博客：http://blog.csdn.net/www_indows"), strTitle);
		this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
		UpdateMap();
		InvalidateRect(m_rtGameRect, FALSE);
	}
	else
	{
		MessageBox(_T("不充钱你怎么变强？"), strTitle, MB_OKCANCEL);
		this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
		UpdateMap();
		InvalidateRect(m_rtGameRect, FALSE);
	}
}

//提示
void CGameDlg::OnClickedBtnPrompt()
{
	// TODO: 在此添加控件通知处理程序代码
	VerTex avPath[MAX_VERTEX_NUM];
	int nVexNum = 0;
	if (m_gameControl.Help(avPath, nVexNum))
	{
		m_ptSelFirst = avPath[0];	//起点
		m_ptSelSec = avPath[nVexNum - 1];	//终点
		DrawTipFrame(m_ptSelFirst.row, m_ptSelFirst.col);
		DrawTipFrame(m_ptSelSec.row, m_ptSelSec.col);
		DrawTipLine(avPath, nVexNum);
		UpdateMap();
		Sleep(200);
		InvalidateRect(m_rtGameRect, FALSE);
	}
	
}

void CGameDlg::OnClickedBtnReset()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox(_T("测试"));
	m_gameControl.ResetMap();
	UpdateMap();
	InvalidateRect(m_rtGameRect, FALSE);
}

void CGameDlg::SetGameModel(CGameControl* pGameC)
{
	m_pGameC = pGameC;
}



