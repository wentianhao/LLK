// GameDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "GameDlg.h"
#include "afxdialogex.h"
#include "GameControl.h"
#include "GameLogic.h"
#include "resource.h"
#include "global.h"
// CGameDlg �Ի���

IMPLEMENT_DYNAMIC(CGameDlg, CDialogEx)

CGameDlg::CGameDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_GAME_DIALOG, pParent)
{
	m_ptGameTop.x = 50;
	m_ptGameTop.y = 50;

	m_sizeElem.cx = 40;
	m_sizeElem.cy = 40;

	//��ʼ����Ϸ��������
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

// CGameDlg ��Ϣ�������
void CGameDlg::InitBackground() 
{
	CClientDC dc(this);	//��õ�ǰ�Ի������Ƶ����

	//����API
	HANDLE hBmpBG = ::LoadImage(NULL, _T("theme\\picture\\fruit_bg.bmp"),IMAGE_BITMAP,0,0,LR_LOADFROMFILE);

	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcBG.CreateCompatibleDC(&dc);
	//��λͼ��Դѡ��DC
	m_dcBG.SelectObject(hBmpBG);

	//��ʼ���ڴ�DC
	m_dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpMem;
	bmpMem.CreateCompatibleBitmap(&dc, 800, 600);
	//��λͼѡ��DC
	m_dcMem.SelectObject(&bmpMem);
	//���Ʊ������ڴ�DC��
	m_dcMem.BitBlt(0, 0, 800, 600, &m_dcBG, 0, 0, SRCCOPY);
}

//��ʼ���Ի���
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
					   // TODO: �ڴ˴������Ϣ����������
					   // ��Ϊ��ͼ��Ϣ���� CDialogEx::OnPaint()
	dc.BitBlt(0,0,800,600,&m_dcMem,0,0,SRCCOPY);
}

//��ʼ������
void CGameDlg::InitElement()
{
	CClientDC dc(this);	//��õ�ǰ�Ի������Ƶ�ڴ�

	//����API������BMPͼƬ��Դ
	HANDLE bmpElement = ::LoadImage(NULL, _T("theme\\picture\\fruit_element.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcElement.CreateCompatibleDC(&dc);
	//��λͼѡ��DC
	m_dcElement.SelectObject(bmpElement);


	//����API������BMPͼƬ��Դ
	HANDLE bmpMask = ::LoadImage(NULL, _T("theme\\picture\\fruit_mask.bmp"),
		IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	//��������Ƶ�ڴ���ݵ��ڴ�DC
	m_dcMask.CreateCompatibleDC(&dc);
	//��λͼѡ��DC
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

//���µ�ͼ
void CGameDlg::UpdateMap()
{
	//����ͼƬ�Ķ���������ͼƬ��С
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
			//�������������򣬱߱�����ͼ������Ϊ1
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH,
				&m_dcMask, 0, nInfo * nElemH, SRCPAINT);
			//��������Ԫ��ͼƬ���룬�߱�����ͼ������ΪԪ��ͼƬ
			m_dcMem.BitBlt(nLeft + j*nElemW, nTop + i*nElemH, nElemW, nElemH,
				&m_dcElement, 0, nInfo * nElemH, SRCAND);

		}
	}
}

//��ť��Ӧ����
void CGameDlg::OnClickedBtnStart()
{


	//��ʼ����Ϸ��ͼ
	m_gameControl.StartGame();
	//���½���
	UpdateMap();
	

	//��Ϸ��ʶ��Ϊtrue
	m_bPlaying = true;
	//��ֹ��ť���
	this->GetDlgItem(IDC_BTN_START)->EnableWindow(FALSE);

	this->GetDlgItem(IDC_GAME_TIME)->ShowWindow(SW_SHOW);

	if (m_flag.csTitle == _T("����������������ģʽ by ���"))
	{
		this->SetWindowTextW(m_flag.csTitle);
		//��ʼ��������
		m_GamePrograss.SetRange(0, 60 * 5);	//��ʼ��Χ
		m_GamePrograss.SetStep(-1);		//��ʼ����ֵ
		m_GamePrograss.SetPos(60 * 5);	//���ó�ʼֵ
										//������ʱ��
		this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
		//���Ƶ�ǰ����
		DrawGameTime();
		//���´���
	}
	if (m_flag.csTitle == _T("����������������ģʽ by ���"))
	{
		this->SetWindowTextW(m_flag.csTitle);
		//��ʼ��������
		m_GamePrograss.SetRange(0, 60 * 5);	//��ʼ��Χ
		m_GamePrograss.SetStep(-1);		//��ʼ����ֵ
		m_GamePrograss.SetPos(60 * 5);	//���ó�ʼֵ
										//������ʱ��
		//this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
		//���Ƶ�ǰ����
		DrawGameTime();
		//���´���
	}
	if (m_flag.csTitle == _T("�������������ؿ�ģʽ by ���"))
	{
		this->SetWindowTextW(m_flag.csTitle);
		//��ʼ��������
		m_GamePrograss.SetRange(0, 60 * 5);	//��ʼ��Χ
		m_GamePrograss.SetStep(-1);		//��ʼ����ֵ
		m_GamePrograss.SetPos(60 * 5);	//���ó�ʼֵ
										//������ʱ��
		this->SetTimer(PLAY_TIMER_ID, 500, NULL);
		//���Ƶ�ǰ����
		DrawGameTime();
	}
	//���´���
	InvalidateRect(m_rtGameRect, FALSE);
}

//�����Ϣ��Ӧ����
void CGameDlg::OnLButtonUp(UINT nFlags, CPoint point)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	//�жϵ��λ�õ������Ƿ�����Ϸ������������
	if (point.x < m_ptGameTop.x || point.y < m_ptGameTop.y)
	{
		return CDialogEx::OnLButtonUp(nFlags, point);
	}
	//�����������λ�õ��к����к�
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

		//�·��
		VerTex avPath[4];
		int Vernum = 0;
		//�ж��Ƿ�����ͬͼƬ
		if (m_gameControl.Link(avPath,Vernum))
		{
			//����ʾ��
			DrawTipLine(avPath, Vernum);
		
		//���µ�ͼ
			UpdateMap();
			Sleep(200);
			InvalidateRect(m_rtGameRect, FALSE);	//�ڸ�����Ϸ��ͼʱ��������Ϸ��ͼ��Ч��������޶ȵļ�����Ļ��˸
		}
		int bGameStatus = m_GamePrograss.GetPos();

		CString strTitle;
		this->GetWindowTextW(strTitle);
		//�ж�ʤ�� 
		if (m_gameControl.IsWin() && bGameStatus > 0 && m_bPlaying)
		{
			m_bPlaying = false;
			KillTimer(PLAY_TIMER_ID);
			MessageBox(_T("YOU WIN!!!!"), strTitle);
			this->GetDlgItem(IDC_BTN_START)->EnableWindow(TRUE);
		}
		if (bGameStatus == 0)
		{
			MessageBox(_T("ɵ�Ƕ�"), strTitle);
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

//�ж�ѡ���ͼƬ�Ƿ���ͬһ��ͼƬ
//bool CGameDlg::IsLink()
//{
//	/*if (m_gameControl.GetElement[m_ptSelFirst.row][m_ptSelFirst.col] == m_gameControl.GetElement[m_ptSelSec.row][m_ptSelSec.col])
//	{
//		return true;
//	}*/
//	return false;
//}

//����������
void CGameDlg::DrawTipLine(VerTex avPath[4],int nVernum)
{
	//��ȡDC
	CClientDC dc(this);

	//���û���
	CPen penLine(PS_SOLID, 2, RGB(0, 255, 0));

	//������ѡ��DC
	CPen* pOldPen = dc.SelectObject(&penLine);

	//����������
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
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	DrawGameTime();
	if (nIDEvent == PLAY_TIMER_ID&&m_bPlaying)
	{
		//��Ϸʱ���1s
		m_GamePrograss.StepIt();
	}

	CDialogEx::OnTimer(nIDEvent);
}

void CGameDlg::DrawGameTime()
{
	//��������
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

//��ͣ
void CGameDlg::OnClickedBtnPause()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CClientDC dc(this);

	if (m_bPause)
	{
		KillTimer(PLAY_TIMER_ID);
		m_dcMem.BitBlt(50, 50, 640, 400, &m_dcCache, 0, 0, SRCCOPY);
		InvalidateRect(m_rtGameRect, FALSE);
		this->GetDlgItem(IDC_BTN_PAUSE)->SetWindowTextW(_T("������Ϸ"));
	}
	else {
		this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
		UpdateMap();
		InvalidateRect(m_rtGameRect, FALSE);
		this->GetDlgItem(IDC_BTN_PAUSE)->SetWindowTextW(_T("��ͣ��Ϸ"));
	}
	m_bPause = !m_bPause;
}

//����
void CGameDlg::OnClickedBtnHelp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strTitle;
	this->GetWindowTextW(strTitle);
	KillTimer(PLAY_TIMER_ID);
	if (MessageBox(_T("������ֵ����Ϊ��Ա���������а�������"), strTitle, MB_OKCANCEL)== IDOK)
	{
		MessageBox(_T("�ҵĲ��ͣ�http://blog.csdn.net/www_indows"), strTitle);
		this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
		UpdateMap();
		InvalidateRect(m_rtGameRect, FALSE);
	}
	else
	{
		MessageBox(_T("����Ǯ����ô��ǿ��"), strTitle, MB_OKCANCEL);
		this->SetTimer(PLAY_TIMER_ID, 1000, NULL);
		UpdateMap();
		InvalidateRect(m_rtGameRect, FALSE);
	}
}

//��ʾ
void CGameDlg::OnClickedBtnPrompt()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	VerTex avPath[MAX_VERTEX_NUM];
	int nVexNum = 0;
	if (m_gameControl.Help(avPath, nVexNum))
	{
		m_ptSelFirst = avPath[0];	//���
		m_ptSelSec = avPath[nVexNum - 1];	//�յ�
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
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("����"));
	m_gameControl.ResetMap();
	UpdateMap();
	InvalidateRect(m_rtGameRect, FALSE);
}

void CGameDlg::SetGameModel(CGameControl* pGameC)
{
	m_pGameC = pGameC;
}



