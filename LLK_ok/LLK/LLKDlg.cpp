
// LLKDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "LLK.h"
#include "LLKDlg.h"
#include "GameDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// �Ի�������
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CLLKDlg �Ի���



CLLKDlg::CLLKDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_LLK_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CLLKDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CLLKDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BTN_BASIC, &CLLKDlg::OnClickedBtnBasic)
	ON_BN_CLICKED(IDC_BTN_RELAX, &CLLKDlg::OnClickedBtnRelax)
	ON_BN_CLICKED(IDC_BTN_LEVEL, &CLLKDlg::OnClickedBtnLevel)
	ON_BN_CLICKED(IDC_BTN_RANK, &CLLKDlg::OnClickedBtnRank)
	ON_BN_CLICKED(IDC_BTN_HELP, &CLLKDlg::OnClickedBtnHelp)
	ON_BN_CLICKED(IDC_BTN_SET, &CLLKDlg::OnClickedBtnSet)
END_MESSAGE_MAP()


// CLLKDlg ��Ϣ�������

BOOL CLLKDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ  ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	InitBackground();

	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CLLKDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ  ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CLLKDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		//����CPaintDC����
		CPaintDC dc(this);

		dc.BitBlt(0,0,800,600,&m_dcMem,0,0,SRCCOPY);
		CDialogEx::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CLLKDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CLLKDlg::InitBackground() {
	//����λͼ
	CBitmap bmpMain;
	bmpMain.LoadBitmapW(IDB_MAIN_BG);

	//��������DC
	CClientDC dc(this);
	m_dcMem.CreateCompatibleDC(&dc);

	//��λͼѡ��DC
	m_dcMem.SelectObject(bmpMain);

}

void CLLKDlg::OnBnClickedButton1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CLLKDlg::OnBnClickedButton3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}


void CLLKDlg::OnClickedBtnBasic()
{
	
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_HIDE);	//����������
	CGameControl *basicGC=new CGameControl;
	FLAG basicFlag;
	basicFlag.bProp = false;
	basicFlag.bTimer = true;
	basicFlag.csTitle = _T("����������������ģʽ by ���");
	basicGC->SetGameFlag(basicFlag);
	CGameDlg dlg;
	dlg.SetGameModel(basicGC);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void CLLKDlg::OnClickedBtnRelax()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	this->ShowWindow(SW_HIDE);
	CGameControl *relaxGC = new CGameControl;
	FLAG relaxFlag;
	relaxFlag.bProp = true;
	relaxFlag.bTimer = true;
	relaxFlag.csTitle = _T("����������������ģʽ by ���");
	relaxGC->SetGameFlag(relaxFlag);
	CGameDlg dlg;
	dlg.SetGameModel(relaxGC);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void CLLKDlg::OnClickedBtnLevel()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������

	this->ShowWindow(SW_HIDE);
	CGameControl *levelGC = new CGameControl;
	FLAG levelFlag;
	levelFlag.bProp = true;
	levelFlag.bTimer = true;
	levelFlag.csTitle = _T("�������������ؿ�ģʽ by ���");
	levelGC->SetGameFlag(levelFlag);
	CGameDlg dlg;
	dlg.SetGameModel(levelGC);
	dlg.DoModal();
	this->ShowWindow(SW_SHOW);
}


void CLLKDlg::OnClickedBtnRank()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("��ʱû�������棬����û������~"));
}


void CLLKDlg::OnClickedBtnHelp()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	CString strTitle;
	this->GetWindowTextW(strTitle);
	if (MessageBox(_T("������ֵ����Ϊ��Ա���������а�������"), strTitle, MB_OKCANCEL) == IDOK)
	{
		MessageBox(_T("�ҵĲ��ͣ�http://blog.csdn.net/www_indows"), strTitle);
	}
	else
	{
		MessageBox(_T("����Ǯ����ô��ǿ��"), strTitle, MB_OKCANCEL);
	}
}


void CLLKDlg::OnClickedBtnSet()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	MessageBox(_T("��ʱû�����ã��������ϵ�ң����ͣ�http://blog.csdn.net/www_indows"));
}
