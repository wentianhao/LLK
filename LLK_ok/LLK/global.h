#pragma once  //��ֹͷ�ļ��ظ�����

//���嶥��ṹ��
typedef struct tagVerTex {
	int row;	  //��
	int col;	 //��
	int info;	//��Ϣ��
}VerTex;

typedef struct tagFlag {
	bool bTimer;	//��ʱ������
	bool bProp;	   //��ʾ
	CString csTitle;	//�Ի������������
}FLAG;	//true��ʾ��ʾ��false��ʾ����ʾ

#define BLANK -1
#define MAX_ROW 10 
#define MAX_COL 16
#define PicNum 16
#define PLAY_TIMER_ID 1
#define MAX_VERTEX_NUM 160