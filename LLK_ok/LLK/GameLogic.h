#pragma once
#include "global.h"

class CGameLogic {
public:
	CGameLogic();
	~CGameLogic();

public:
	void InitMap(int anMap[][MAX_COL]);
	bool isLink(int anMap[][MAX_COL],VerTex v1,VerTex v2);
	void Clear(int anMap[][MAX_COL], VerTex v1, VerTex v2);
	void AddVerTex(VerTex v);
	void DeleteVerTex();
	int GetVexPath(VerTex avPath[4]);
	bool isBank(int anMap[][MAX_COL]);
	bool SearchValidPath(int anMap[][MAX_COL]);
	void ResetMap(int anMap[][MAX_COL]);

	VerTex m_avPath[MAX_VERTEX_NUM];
	int m_VerTexNum;

protected:
	bool LinkInRow(int anMap[][MAX_COL], VerTex v1, VerTex v2);
	bool LinkInCol(int anMap[][MAX_COL], VerTex v1, VerTex v2);
	bool LineX(int anMap[][MAX_COL], int nRow, int nCol1, int nCol2);
	bool LineY(int anMap[][MAX_COL], int nRow, int nCol1, int nCol2);
	bool OneCornerLink(int anMap[][MAX_COL], VerTex v1, VerTex v2);
	bool TwoCornerLink(int anMap[][MAX_COL], VerTex V1, VerTex v2);
	
};