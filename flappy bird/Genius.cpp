#include "Genius.h"


Genius::Genius(){
	Width = 0;
	Height = 0;
	IntervalTime = 0;
	isFlash = false;
	ImageNum = 0;
	ImageTemp = new CxImage;
	ImageIndex = 0;
	RotateAngle = 0;
	LastTime = GetTickCount();
}

void Genius::Create(UINT width, UINT height, bool isflash, UINT interval){
	Width = width;
	Height = height;
	isFlash = isflash;
	IntervalTime = interval;
}

bool Genius::AddImage(UINT image){//���ͼƬ
	HRSRC resource = FindResource(NULL,MAKEINTRESOURCE(image),"PNG");
	if (resource != NULL){
		Image.push_back(NULL);
		Image[ImageNum] = new CxImage;
		Image[ImageNum]->LoadResource(resource, CXIMAGE_FORMAT_PNG);
		ImageNum++;
		return true;
	}
	return false;
}


void Genius::Draw(HDC goalDC, int x, int y){	//���ƾ���
	if (isFlash){
		Image[ImageIndex%ImageNum]->Draw(goalDC, x, y, Width, Height);
		if (GetTickCount() > LastTime){
			LastTime = GetTickCount() + IntervalTime;
			ImageIndex++;
		}
	}
	else{
		Image[0]->Draw(goalDC, x, y);
	}
}

void Genius::DrawHasAngle(HDC goalDC, int x, int y, float Angle){//���ǶȻ���
	if (isFlash){
		Image[ImageIndex%ImageNum]->Rotate(Angle, ImageTemp);
		ImageTemp->Draw(goalDC, x, y);
		if (GetTickCount() > LastTime){
			LastTime = GetTickCount() + IntervalTime;
			ImageIndex++;
		}
	}
	else{
		Image[0]->Rotate(Angle, ImageTemp);
		ImageTemp->Draw(goalDC, x, y);
	}
}

Genius::~Genius(){
	for (int i = 0; i < Image.size(); i++){
		delete Image[i];
	}
	delete ImageTemp;
}
