#pragma once
#include "global.h"

class CGameControl
{
public:
	CGameControl();
	~CGameControl();

	void StartGame();
	int GetElement(int nRow, int nCol);
	void SetFirstPoint(int nRow, int nCol);
	void SetSecPoint(int nRow, int nCol);
	bool Link(VerTex avPath[4], int &nVexnum);
	bool IsWin();
	bool Help(VerTex avPath[MAX_VERTEX_NUM], int &nVernum);
	void SetGameFlag(FLAG flag);
	void ResetMap();
	FLAG GetGameFlag();


private:
	int m_anMap[MAX_ROW][MAX_COL];	//≥ı ºªØµÿÕº
	VerTex m_ptSelFirst;
	VerTex m_ptSelSec;
	FLAG m_flag;
	
};

