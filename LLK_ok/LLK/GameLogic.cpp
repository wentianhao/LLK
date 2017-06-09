// GameLogic.cpp : 实现文件
//

#include "stdafx.h"
#include "LLK.h"
#include "GameLogic.h"
#include "afxdialogex.h"

CGameLogic::CGameLogic()
{
	m_VerTexNum = 0;
}

CGameLogic::~CGameLogic()
{
}

void CGameLogic::InitMap(int anMap[][MAX_COL])
{
	//初始化游戏地图
	int anTemp[10][16] = { {0,0,0,0,0,0,0,0,0,0,1,1,1,1,1,1},
						   {1,1,1,1,2,2,2,2,2,2,2,2,2,2,3,3},
						   {3,3,3,3,3,3,3,3,4,4,4,4,4,4,4,4},
						   {4.4,5,5,5,5,5,5,5,5,5,5,6,6,6,6 },
						   {6,6,6,6,6,6,7,7,7,7,7,7,7,7,7,7},
		                   {8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9},
						   {9,9,9,9,10,10,10,10,10,10,10,10,10,10,11,11},
						   {11,11,11,11,11,11,11,11,12,12,12,12,12,12,12,12},
						   {12,12,13,13,13,13,13,13,13,13,13,13,14,14,14,14},
						   {14,14,14,14,14,14,15,15,15,15,15,15,15,15,15,15}};

	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			anMap[i][j] = anTemp[i][j];
		}
	}

	int nRepeatNum = MAX_ROW*MAX_COL / PicNum;	//重复数
	int nCount = 0;
	for (int i = 0; i < nRepeatNum; i++)
	{
		//重复数
		for (int j = 0; j < nRepeatNum; j++)
		{
			anMap[nCount / MAX_COL][nCount%MAX_COL] = i;
			nCount++;
		}
	}

	//设置种子
	srand((int)time(NULL));

	//随机任意交换两个数字
	int nVertexNum = MAX_COL*MAX_ROW;
	for (int i = 0; i < nVertexNum; i++)
	{
		//随机得到两个坐标
		int Index1 = rand() % nVertexNum;
		int Index2 = rand() % nVertexNum;

		//交换两个数值
		int nTemp = anMap[Index1 / MAX_COL][Index1%MAX_COL];
		anMap[Index1 / MAX_COL][Index1%MAX_COL] = anMap[Index2 / MAX_COL][Index2%MAX_COL];
		anMap[Index2 / MAX_COL][Index2%MAX_COL] = nTemp;
	}
}

bool CGameLogic::isLink(int anMap[][MAX_COL], VerTex v1, VerTex v2)
{
	
	/*if (anMap[nRow1][nCol1] == anMap[nRow2][nCol2])
	{
		return true;
	}*/

	//一条直线连通
	int nRow1 = v1.row;
	int nCol1 = v1.col;
	int nRow2 = v2.row;
	int nCol2 = v2.col;
	AddVerTex(v1);
	if (nRow1 == nRow2)
	{
		if (LinkInRow(anMap, v1, v2) == true)
		{
			AddVerTex(v2);
			return true;
		}
	}else if (nCol1 == nCol2)
	{
		if (LinkInCol(anMap, v1, v2) == true)
		{
			AddVerTex(v2);
			return true;
		}	
	}

	//两条直线连通
	 if (OneCornerLink(anMap, v1, v2) == true)
	{
		AddVerTex(v2);
		return true;
	}
		
	//三条直线连通
	 if (TwoCornerLink(anMap, v1, v2) == true)
	{
		AddVerTex(v2);
		return true;
	}
		
	DeleteVerTex();
	return false;
}

void CGameLogic::Clear(int anMap[][MAX_COL], VerTex v1, VerTex v2)
{
	anMap[v1.row][v1.col] = BLANK;
	anMap[v2.row][v2.col] = BLANK;
}

bool CGameLogic::LinkInRow(int anMap[][MAX_COL], VerTex v1, VerTex v2)
{
	int nCol1 = v1.col;
	int nCol2 = v2.col;
	int nRow = v1.row;

	if (nCol1 > nCol2)
	{
		int nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;
	}

	for (int i = nCol1 + 1; i <= nCol2; i++)
	{
		if (i == nCol2)
		{
			return true;
		}
		if (anMap[nRow][i] != BLANK)
		{
			break;
		}
	}
	return false;
}

bool CGameLogic::LinkInCol(int anMap[][MAX_COL], VerTex v1, VerTex v2)
{
	int nCol = v1.col;
	int nRow1 = v1.row;
	int nRow2 = v2.row;

	if (nRow1 > nRow2)
	{
		int nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;
	}

	//直通
	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2)
			return true;
		if (anMap[i][nCol] != BLANK)
			break;
	}
	return false;
}


bool CGameLogic::LineX(int anMap[][MAX_COL],int nRow,int nCol1,int nCol2)
{
	if (nCol1 > nCol2)
	{
		int nTemp = nCol1;
		nCol1 = nCol2;
		nCol2 = nTemp;
	}

	for (int i = nCol1 + 1; i <= nCol2; i++)
	{
		if (i == nCol2)
		{
			return true;
		}
		if (anMap[nRow][i] != BLANK)
		{
			break;
		}
	}
	return false;
}

bool CGameLogic::LineY(int anMap[][MAX_COL], int nCol, int nRow1, int nRow2)
{
	if (nRow1 > nRow2)
	{
		int nTemp = nRow1;
		nRow1 = nRow2;
		nRow2 = nTemp;
	}

	//直通
	for (int i = nRow1 + 1; i <= nRow2; i++)
	{
		if (i == nRow2)
			return true;
		if (anMap[i][nCol] != BLANK)
			break;
	}
	return false;
}

bool CGameLogic::OneCornerLink(int anMap[][MAX_COL], VerTex v1, VerTex v2)
{
	if (anMap[v1.row][v2.col] == BLANK)
	{
		if (LineY(anMap, v2.col, v1.row, v2.row) && (LineX(anMap, v1.row, v1.col, v2.col)))
		{
			VerTex v = { v1.row,v2.col,BLANK };
			AddVerTex(v);
			return true;
		}
		
	}

	if (anMap[v2.row][v1.col] == BLANK)
	{
		if (LineY(anMap, v1.col, v1.row, v2.row) && LineX(anMap, v2.row, v1.col, v2.col))
		{
			VerTex v = { v2.row,v1.col,BLANK };
			AddVerTex(v);
			return true;
		}

	}
	return false;
}

bool CGameLogic::TwoCornerLink(int anMap[][MAX_COL], VerTex v1, VerTex v2)
{

	for (int col = 0; col < MAX_COL; col++)
	{
		//找到一条与Y轴平行的连通线段
		if (anMap[v1.row][col] == BLANK && anMap[v2.row][col] == BLANK)
		{
			if (LineY(anMap, col, v1.row, v2.row))
			{
				if (LineX(anMap, v1.row, v1.col, col) && LineX(anMap, v2.row, v2.col, col))
				{
					VerTex x1 = { v1.row,col,BLANK };
					VerTex x2 = { v2.row,col,BLANK };
					AddVerTex(x1);
					AddVerTex(x2);
					return true;
				}
			}
		}
	}
	for (int row = 0; row < MAX_ROW; row++)
	{
		//找到一条与X轴平行的连通线段
		if (anMap[row][v1.col] == BLANK&&anMap[row][v2.col] == BLANK)
		{
			if (LineX(anMap, row, v1.col, v2.col))
			{
				if (LineY(anMap, v1.col, row, v1.row) && LineY(anMap, v2.col, row, v2.row))
				{
					VerTex x1 = { row,v1.col,BLANK };
					VerTex x2 = { row,v2.col,BLANK };
					AddVerTex(x1);
					AddVerTex(x2);
					return true;
				}
			}
		}

	}
	return false;
}

int CGameLogic::GetVexPath(VerTex avPath[MAX_VERTEX_NUM])
{
	for (int i = 0; i < m_VerTexNum; i++)
	{
		avPath[i] = m_avPath[i];
	}
	return m_VerTexNum;
}

void CGameLogic::AddVerTex(VerTex v)
{
	m_avPath[m_VerTexNum] = v;
	m_VerTexNum++;
}

void CGameLogic::DeleteVerTex()
{
	m_VerTexNum--;
}

bool CGameLogic::isBank(int anMap[][MAX_COL])
{
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			if (anMap[i][j] != BLANK)
				return false;
		}
	}
	return true;
}

bool CGameLogic::SearchValidPath(int anMap[][MAX_COL])
{
	for (int i = 0; i < MAX_ROW; i++)
	{
		for (int j = 0; j < MAX_COL; j++)
		{
			int nInfo1 = anMap[i][j];	//第一个点
			int nInfo2;	//第二个点
			for (int m = i; m < MAX_ROW; m++)
			{
				int n;
				for (n = j+1; n < MAX_COL; n++)
				{
					nInfo2 = anMap[m][n];
					if (nInfo1 == nInfo2 && nInfo1 != BLANK && nInfo2 != BLANK)
					{
						VerTex v1 = { i,j,nInfo1 };
						AddVerTex(v1);
						VerTex v2 = { m,n,nInfo2 };
						if (isLink(anMap, v1, v2))
						{
							return true;
						}
						DeleteVerTex();
					}
				}
				
			}
		}
	}
	return false;
}

void CGameLogic::ResetMap(int anMap[][MAX_COL])
{
	
	//设置种子
	srand((int)time(NULL));

	//随机任意交换两个数字
	int nVertexNum = MAX_COL*MAX_ROW;
	for (int i = 0; i < nVertexNum; i++)
	{
		//随机得到两个坐标
		int Index1 = rand() % nVertexNum;
		int Index2 = rand() % nVertexNum;

		//交换两个数值
		int nTemp = anMap[Index1 / MAX_COL][Index1%MAX_COL];
		anMap[Index1 / MAX_COL][Index1%MAX_COL] = anMap[Index2 / MAX_COL][Index2%MAX_COL];
		anMap[Index2 / MAX_COL][Index2%MAX_COL] = nTemp;
	}
}
