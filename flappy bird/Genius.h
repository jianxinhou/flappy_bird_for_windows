#pragma once
#include "parameter.h"

class Genius
{
protected:
	vector <CxImage*> Image;//����ͼƬ
	CxImage *ImageTemp;//
	UINT ImageNum;//ͼƬ��
	UINT Width;//��
	UINT Height;//��
	UINT IntervalTime;//���ż��ʱ��
	UINT ImageIndex;//��ǰ����ͼƬ����
	UINT RotateAngle;//��ת�Ƕ�
	DWORD LastTime;//�ϴ���ʾ��ʱ��
	bool isFlash;//�Ƿ�Ϊ����
public:
	UINT GetWidth(){
		return Width;
	}
	UINT GetHeight(){
		return Height;
	}
	void Create(UINT width, UINT height, bool isflash,UINT interval = 0);//����
	bool AddImage(UINT image);//����ͼƬ
	void Draw(HDC goalDC, int x, int y);//����
	void DrawHasAngle(HDC goalDC, int x, int y, float Angle = 0);//���ǶȻ���
	Genius();
	~Genius();
};

//�ܵ�����
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
