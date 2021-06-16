#pragma once
#include "parameter.h"

class Genius
{
protected:
	vector <CxImage*> Image;//精灵图片
	CxImage *ImageTemp;//
	UINT ImageNum;//图片数
	UINT Width;//宽
	UINT Height;//高
	UINT IntervalTime;//播放间隔时间
	UINT ImageIndex;//当前播放图片索引
	UINT RotateAngle;//旋转角度
	DWORD LastTime;//上次显示的时间
	bool isFlash;//是否为动画
public:
	UINT GetWidth(){
		return Width;
	}
	UINT GetHeight(){
		return Height;
	}
	void Create(UINT width, UINT height, bool isflash,UINT interval = 0);//创建
	bool AddImage(UINT image);//增加图片
	void Draw(HDC goalDC, int x, int y);//绘制
	void DrawHasAngle(HDC goalDC, int x, int y, float Angle = 0);//带角度绘制
	Genius();
	~Genius();
};

//管道精灵
class Pipe{
protected:
	Genius pipe[2];
public:
	void Create(UINT pipe_up, UINT pipe_down){
		pipe[0].Create(PIPE_WIDTH, PIPE_HIGHT, false);
		pipe[1].Create(PIPE_WIDTH, PIPE_HIGHT, false);
		pipe[0].AddImage(pipe_up);
		pipe[1].AddImage(pipe_down);
	}
	void Draw(int x, int y, HDC goalDC){
		pipe[0].Draw(goalDC, x, y - PIPE_HIGHT);
		pipe[1].Draw(goalDC, x, y + PIPE_SPACE);
	}
};
