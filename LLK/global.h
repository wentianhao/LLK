#pragma once  //防止头文件重复编译

//定义顶点结构体
typedef struct tagVerTex {
	int row;	  //行
	int col;	 //列
	int info;	//信息类
}VerTex;

typedef struct tagFlag {
	bool bTimer;	//计时进度条
	bool bProp;	   //提示
	CString csTitle;	//对话框标题栏文字
}FLAG;	//true表示显示，false表示不显示

#define BLANK -1
#define MAX_ROW 10 
#define MAX_COL 16
#define PicNum 16
#define PLAY_TIMER_ID 1
#define MAX_VERTEX_NUM 160