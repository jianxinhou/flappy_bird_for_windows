#include "GameAudio.h"


GameAudio::GameAudio()
{

}

void GameAudio::Create(HWND hWnd){
	HRESULT result;
	result = DirectSoundCreate(NULL, &pDS, NULL);
	if (result != DS_OK){
		MessageBox(hWnd, "错误！", "声音设备初始化失败！", MB_OK);
	}
	result = pDS->SetCooperativeLevel(hWnd, DSSCL_NORMAL);
	if (result != DS_OK){
		MessageBox(hWnd, "错误！", "声音设备初始化失败！", MB_OK);
	}
}

GameAudio::~GameAudio()
{
}

void GameAudio::AddAudio(LPTSTR audiopath){
	WAVEFORMATEX swfmt;
	MMCKINFO chRiff;
	MMCKINFO ckInfo;
	MMRESULT mmresult;
	HRESULT result;
	HMMIO hmmio;
	DWORD size;
	DSBUFFERDESC desc;
	hmmio = mmioOpen(audiopath, NULL, MMIO_ALLOCBUF | MMIO_READ);
	if (hmmio == NULL){
		MessageBox(NULL, "文件不存在","错误！", MB_OK);
	}
	chRiff.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	mmresult = mmioDescend(hmmio, &chRiff, NULL, MMIO_FINDRIFF);
	if (mmresult != MMSYSERR_NOERROR){
		MessageBox(NULL, "文件格式错误", "错误！", MB_OK);
	}
	ckInfo.ckid = mmioFOURCC('f', 'm', 't', ' ');
	mmresult = mmioDescend(hmmio, &ckInfo, &chRiff, MMIO_FINDCHUNK);
	if (mmresult != MMSYSERR_NOERROR){
		MessageBox(NULL, "文件格式错误", "错误！", MB_OK);
	}
	if (mmioRead(hmmio, (HPSTR)&swfmt, sizeof(swfmt)) == -1){
		MessageBox(NULL, "错误！", "读取格式失败", MB_OK);
	}
	mmresult = mmioAscend(hmmio, &ckInfo, 0);
	ckInfo.ckid = mmioFOURCC('d', 'a', 't', 'a');
	mmresult= mmioDescend(hmmio, &ckInfo, &chRiff, MMIO_FINDCHUNK);
	if (mmresult != MMSYSERR_NOERROR){
		MessageBox(NULL, "错误！", "文件格式错误", MB_OK);
	}
	size = ckInfo.cksize;
	LPDIRECTSOUNDBUFFER pBUFFER;
	memset(&desc, 0, sizeof(desc));
	desc.dwSize = sizeof(desc);
	desc.dwBufferBytes = size;
	desc.lpwfxFormat = &swfmt;
	desc.dwFlags = DSBCAPS_STATIC | DSBCAPS_CTRLPAN | DSBCAPS_CTRLVOLUME | DSBCAPS_GLOBALFOCUS;
	result = pDS->CreateSoundBuffer(&desc, &pBUFFER, NULL);
	if (result != DS_OK){
		MessageBox(NULL, "错误！", "建立缓冲区失败", MB_OK);
	}
	pBuffer.push_back(pBUFFER);
	LPVOID pAudio;
	DWORD size2;
	pBuffer[pBuffer.size()-1]->Lock(0, size, &pAudio, &size2, NULL, NULL, NULL);
	mmioRead(hmmio, (HPSTR)pAudio, size2);
	pBuffer[pBuffer.size()-1]->Unlock(pAudio, size2, NULL, NULL);
	mmioClose(hmmio, 0);
	pBuffer[pBuffer.size() - 1]->SetVolume(200);
}

void GameAudio::Play(UINT Temp){
	pBuffer[Temp]->Play(0, 0, 0);
}


void GameAudio::Close(){

}