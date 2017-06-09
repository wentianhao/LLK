#include "stdafx.h"
#include "GameControl.h"
#include "GameLogic.h"


CGameControl::CGameControl()
{

}


CGameControl::~CGameControl()
{
}

void CGameControl::StartGame()
{
	CGameLogic gameLogic;
	gameLogic.InitMap(m_anMap);
}

int CGameControl::GetElement(int nRow, int nCol)
{
	return m_anMap[nRow][nCol];
}

void CGameControl::SetFirstPoint(int nRow, int nCol)
{
	m_ptSelFirst.row = nRow;
	m_ptSelFirst.col = nCol;
}

void CGameControl::SetSecPoint(int nRow, int nCol)
{
	m_ptSelSec.row = nRow;
	m_ptSelSec.col = nCol;
}

bool CGameControl::Link(VerTex avPath[4],int &nVexnum)
{
	CGameLogic gameLogic;
	//判断是否同一张图片
	if ((m_ptSelFirst.row == m_ptSelSec.row) && (m_ptSelFirst.col == m_ptSelSec.col))
	{
		return false;
	}
	//判断图片是否相同
	if (m_anMap[m_ptSelFirst.row][m_ptSelFirst.col] != m_anMap[m_ptSelSec.row][m_ptSelSec.col])
	{
		return false;
	}
	
	if (gameLogic.isLink(m_anMap, m_ptSelFirst, m_ptSelSec) == true)
	{
		//消子
		gameLogic.Clear(m_anMap, m_ptSelFirst, m_ptSelSec);
		nVexnum = gameLogic.GetVexPath(avPath);
		return true;
	}
	return false;
}

bool CGameControl::IsWin()
{
	CGameLogic gameLogic;
	return gameLogic.isBank(m_anMap);
}

bool CGameControl::Help(VerTex avPath[MAX_VERTEX_NUM], int &nVernum)
{
	CGameLogic gameLogic;
	//判断是否为空
	if (gameLogic.isBank(m_anMap))
		return false;
	//如果不为空，则查找一个有效的提示路径
	if (gameLogic.SearchValidPath(m_anMap))
	{
		//返回路径顶点
		nVernum = gameLogic.GetVexPath(avPath);
		return true;
	}
	return false;
}

void CGameControl::SetGameFlag(FLAG flag)
{
	m_flag = flag;
}

FLAG CGameControl::GetGameFlag()
{
	return m_flag;
}

void CGameControl::ResetMap()
{
	CGameLogic gameLogic;
	gameLogic.ResetMap(m_anMap);
}
