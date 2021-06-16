#include "Game.h"


Game::Game()
{
	LogoDataInit();
	
}


Game::~Game()
{
	DeleteDC(bufferDC);
	DeleteObject(font);
	DeleteObject(bufferBtMap);
}

//进程初始化
void Game::InitDC(HDC goalDC,HWND hwnd){
	audio.Create(hwnd);
	font = CreateFont
		(
		28,0,    //高度20, 宽取0表示由系统选择最佳值
		0, 0,    //文本倾斜，与字体倾斜都为0
		FW_HEAVY,    //粗体
		0, 0, 0,        //非斜体，无下划线，无中划线
		GB2312_CHARSET,    //字符集
		OUT_DEFAULT_PRECIS,
		CLIP_DEFAULT_PRECIS,
		DEFAULT_QUALITY,        //一系列的默认值
		DEFAULT_PITCH | FF_DONTCARE,
		"微软雅黑"    //字体名称
		);
	logotime = GetTickCount()+1500;//logo时间
	afterflag = false;				
	GameState = 0;//游戏状态
	bufferDC = CreateCompatibleDC(goalDC);//缓冲区buffer
	bufferBtMap = CreateCompatibleBitmap(goalDC, BKGROUND_WIDTH, BKGROUND_HEIGHT);
	SelectObject(bufferDC, bufferBtMap);//
	title.Create(178, 48, false);//
	title.AddImage(IDB_TITLE);//窗口左上角图标
	begin.Create(LOGO_BUTTON_WIDTH, LOGO_BUTTON_HEIGHT, false);//
	begin.AddImage(IDB_BEGIN);//
	gamelogo.Create(BKGROUND_WIDTH, BKGROUND_HEIGHT, false);
	gamelogo.AddImage(IDB_LOGO);
	explain.Create(EXPLAIN_WIDTH, EXPLAIN_HEIGHT, false);
	explain.AddImage(IDB_EXPLAIN);
	ready.Create(READY_WIDTH, READY_HEIGHT, false);
	ready.AddImage(IDB_READY);
	num[0].Create(FONT_WIDTH, FONT_HEIGHT, false);
	num[0].AddImage(IDB_0);
	num[1].Create(FONT_WIDTH, FONT_HEIGHT, false);
	num[1].AddImage(IDB_1);
	num[2].Create(FONT_WIDTH, FONT_HEIGHT, false);
	num[2].AddImage(IDB_2);
	num[3].Create(FONT_WIDTH, FONT_HEIGHT, false);
	num[3].AddImage(IDB_3);
	num[4].Create(FONT_WIDTH, FONT_HEIGHT, false);
	num[4].AddImage(IDB_4);
	num[5].Create(FONT_WIDTH, FONT_HEIGHT, false);
	num[5].AddImage(IDB_5);
	num[6].Create(FONT_WIDTH, FONT_HEIGHT, false);
	num[6].AddImage(IDB_6);
	num[7].Create(FONT_WIDTH, FONT_HEIGHT, false);
	num[7].AddImage(IDB_7);
	num[8].Create(FONT_WIDTH, FONT_HEIGHT, false);
	num[8].AddImage(IDB_8);	
	num[9].Create(FONT_WIDTH, FONT_HEIGHT, false);
	num[9].AddImage(IDB_9);
	over.Create(204, 54, false);
	over.AddImage(IDB_OVER);
	score.Create(126, 238, false);
	score.AddImage(IDB_SCORE);
	bird[0].Create(BIRD_WIDTH, BIRD_HIGHT, true, 100);
	bird[1].Create(BIRD_WIDTH, BIRD_HIGHT, true, 100);
	bird[2].Create(BIRD_WIDTH, BIRD_HIGHT, true, 100);
	bird[0].AddImage(IDB_BIRD_R_MID);
	bird[0].AddImage(IDB_BIRD_R_UP);
	bird[0].AddImage(IDB_BIRD_R_MID);
	bird[0].AddImage(IDB_BIRD_R_DOWN);
	bird[1].AddImage(IDB_BIRD_Y_MID);
	bird[1].AddImage(IDB_BIRD_Y_UP);
	bird[1].AddImage(IDB_BIRD_Y_MID);
	bird[1].AddImage(IDB_BIRD_Y_DOWN);
	bird[2].AddImage(IDB_BIRD_B_MID);
	bird[2].AddImage(IDB_BIRD_B_UP);
	bird[2].AddImage(IDB_BIRD_B_MID);
	bird[2].AddImage(IDB_BIRD_B_DOWN);
	pipes.Create(IDB_PIPEUP_G, IDB_PIPEDOWN_G);
	ground.Create(GROUND_WIDTH, GROUND_HIGHT, false);
	bkground[0].Create(BKGROUND_WIDTH, BKGROUND_HEIGHT, false);
	bkground[1].Create(BKGROUND_WIDTH, BKGROUND_HEIGHT, false);
	ground.AddImage(IDB_GROUND);
	bkground[0].AddImage(IDB_DAY);
	bkground[1].AddImage(IDB_NIGHT);
	Medal[0].Create(44, 44, false);
	Medal[0].AddImage(IDB_GOLD);
	Medal[1].Create(44, 44, false);
	Medal[1].AddImage(IDB_METAL);
	Medal[2].Create(44, 44, false);
	Medal[2].AddImage(IDB_TONG);
	Medal[3].Create(44, 44, false);
	Medal[3].AddImage(IDB_WHITE);
	SetTextColor(bufferDC, RGB(255, 255, 255));
	SetBkMode(bufferDC, TRANSPARENT);
	SelectObject(bufferDC, font);
	Record.resize(4, 0);
	audio.AddAudio("Resource\\wing.wav");
	audio.AddAudio("Resource\\hit.wav");
	audio.AddAudio("Resource\\point.wav");
	audio.AddAudio("Resource\\die.wav");
	audio.AddAudio("Resource\\woo.wav");
	ifstream record("record\\record.txt");
	char Temp[10];
	int temp = 0;
	if (record.is_open()){//打开得分记录
		for (int i = 0; i < 3; i++){
			if (!record.eof()){
				record >> Temp;
				sscanf(Temp, "%d", &temp);
				Record[i] = temp;
			}
			else{
				Record[i] = 0;
			}
		}
		record.close();
	}
}
void Game::BeforeDataInit(){
	bird[BirdState].Create(BIRD_WIDTH, BIRD_HIGHT, true ,100);
	audio.Play(ID_WOO);
	isScore[0] = 0;
	isScore[1] = 0;
	GameScore = 0;
	sprintf(ScoreTemp, "%d", GameScore);
	Score = ScoreTemp;
	DayState = rand() % 2;
	BirdState = rand() % 3;
	pbird.SetPos(BEFORE_BIRD_INIT_POSX, BEFORE_BIRD_INIT_POSY);
	pbird.SetA(0, GRAVITY);
	pbird.SetV(0, BEFORE_BIRD_VY);
	pground.SetPos(0, GROUND_POS_Y);
	pground.SetV(-PIPE_V, 0);
}
void Game::DuringDataInit(){
	//GameState = 1;
	pbird.SetV(0, BIRD_FLY_V);
	birdangle = -30;
	IsPass[0] = false;
	IsPass[1] = false;
	ppipes[0].SetPos(PIPE_INITPOS, rand() % (GROUND_POS_Y - (PIPE_SPACE + 2 * PIPE_HEAD_HIGHT)) + PIPE_HEAD_HIGHT);
	ppipes[1].SetPos(PIPE_INITPOS + PIPE_CREATEPOS / 2 + PIPE_WIDTH / 2, rand() % (GROUND_POS_Y - (PIPE_SPACE + 2 * PIPE_HEAD_HIGHT)) + PIPE_HEAD_HIGHT);
	ppipes[0].SetA(0, 0);
	ppipes[1].SetA(0, 0);
	ppipes[0].SetV(-PIPE_V, 0);
	ppipes[1].SetV(-PIPE_V, 0);
}

void Game::AfterDataInit(){
	birdangle = 90;
	pbird.SetV(0, 0);
	pbird.SetA(0, 1.5);
	bird[BirdState].Create(BIRD_WIDTH, BIRD_HIGHT, false);
	pover.SetPos(42, 512);
	pover.SetV(0, -15);
	pscore.SetPos(25, 582);
	pscore.SetV(0, -15);
	afterflag = false;
	int i = 0;
	for (; i < 3; i++){
		if (GameScore >= Record[i]){
			Record.insert(Record.begin() + i, 1, GameScore);
			medal = i;
			break;
		}
	}
	if (i == 3){
		medal = 3;
		Record[3] = GameScore;
	}
	sprintf(RecordTemp, "%d", Record[0]);
	char Temp[10];
	audio.Play(ID_DIE);
	ofstream record("record\\record.txt");
	for (int j = 0; j < 3; j++){
		sprintf(Temp, "%d", Record[j]);
		record << Temp<<endl;
	}
}

void Game::LogoDataInit(){
	DayState = 0;
	BirdState = 1;
	pbird.SetPos(LOGO_BIRD_INIT_POSX, LOGO_BIRD_INIT_POSY);
	pbird.SetV(0, LOGO_BIRD_VY);
	pground.SetPos(0, GROUND_POS_Y);
	pground.SetV(-PIPE_V, 0);
	pground.SetA(0, 0);
	bird[BirdState].Create(BIRD_WIDTH, BIRD_HIGHT, false);
}

void Game::GameProcess(HDC goalDC){
	switch (GameState){
	case 0:
		GameLogo();
		break;
	case 1:
		BeforeGame();
		break;
	case 2:
		DuringGame();
		break;
	case 3:
		AfterGame();
		break;
	}
	BitBlt(goalDC, 0, 0, BKGROUND_WIDTH, BKGROUND_HEIGHT, bufferDC, 0, 0, SRCCOPY);
}
 
void Game::GameLogo(){
	//如果当前时间小于目标时间则
	if (GetTickCount() < logotime){
		gamelogo.Draw(bufferDC, 0, 0);
	}else{
		if (pbird.Pos.y <LOGO_BIRD_UP_EDGE){
			pbird.SetPos(LOGO_BIRD_INIT_POSX, LOGO_BIRD_UP_EDGE);
			pbird.SetV(0, LOGO_BIRD_VY);
		}
		if (pbird.Pos.y >LOGO_BIRD_DOWN_EDGE){
			pbird.SetPos(LOGO_BIRD_INIT_POSX, LOGO_BIRD_DOWN_EDGE);
			pbird.SetV(0, -LOGO_BIRD_VY);
		}
		if (pground.Pos.x < -GROUND_WIDTH){
			pground.SetPos(0, GROUND_POS_Y);
		}
		bkground[DayState].Draw(bufferDC, 0, 0);
		pground.UniformMove();
		pbird.UniformMove();
		bird[BirdState].Draw(bufferDC, pbird.Pos.x, pbird.Pos.y);
		ground.Draw(bufferDC, pground.Pos.x, pground.Pos.y);
		ground.Draw(bufferDC, pground.Pos.x+GROUND_WIDTH, pground.Pos.y);
		title.Draw(bufferDC, 55, 90);
		begin.Draw(bufferDC, LOGO_BUTTON_X, LOGO_BUTTON_Y);
	}
}

void Game::BeforeGame(){
	pground.UniformMove();
	pbird.UniformMove();
	if (pbird.Pos.y < BEFORE_BIRD_UP_EDGE){
		pbird.SetPos(BEFORE_BIRD_INIT_POSX, BEFORE_BIRD_UP_EDGE);
		pbird.SetV(0, BEFORE_BIRD_VY);
	}
	if (pbird.Pos.y > BEFORE_BIRD_DOWN_EDGE){
		pbird.SetPos(BEFORE_BIRD_INIT_POSX, BEFORE_BIRD_DOWN_EDGE);
		pbird.SetV(0, -BEFORE_BIRD_VY);
	}
	if (pground.Pos.x < -GROUND_WIDTH){
		pground.SetPos(0, GROUND_POS_Y);
	}
	bkground[DayState].Draw(bufferDC, 0, 0);
	ready.Draw(bufferDC, 46, 120);
	explain.Draw(bufferDC, 95, 190);
	ground.Draw(bufferDC, pground.Pos.x, pground.Pos.y);
	ground.Draw(bufferDC, pground.Pos.x + GROUND_WIDTH, pground.Pos.y);
	bird[BirdState].Draw(bufferDC, pbird.Pos.x, pbird.Pos.y);
	num[0].Draw(bufferDC, 132, 70);
}

void Game::DuringGame(){
	pbird.ShiftMove();
	ppipes[0].UniformMove();
	ppipes[1].UniformMove();
	pground.UniformMove();

	birdangle = pbird.V.y < 0 ? pbird.V.y*2 : pbird.V.y*3;
	if (!IsPass[0]){
		if ((pbird.Pos.x + 39 > ppipes[0].Pos.x&&pbird.Pos.y+15<ppipes[0].Pos.y) || 
			(pbird.Pos.x + 39 > ppipes[0].Pos.x&&pbird.Pos.y + 32 > ppipes[0].Pos.y + PIPE_SPACE)){
			audio.Play(ID_HIT);
			GameState = 3;
			AfterDataInit();
		}
	}
	if (!IsPass[1]){
		if ((pbird.Pos.x + 39 > ppipes[1].Pos.x&&pbird.Pos.y + 15<ppipes[1].Pos.y) ||
			(pbird.Pos.x + 39 > ppipes[1].Pos.x&&pbird.Pos.y + 32 > ppipes[1].Pos.y + PIPE_SPACE)){
			audio.Play(ID_HIT);
			GameState = 3;
			AfterDataInit();
		}
	}
	if (pbird.Pos.x+16 > ppipes[0].Pos.x + PIPE_WIDTH){
		IsPass[0] = true;
		isScore[0]++;
		if (isScore[0] == 1){
			GameScore++;
			audio.Play(ID_POINT);
			sprintf(ScoreTemp, "%d", GameScore);
			Score = ScoreTemp;
		}
	}
	if (pbird.Pos.x+16 > ppipes[1].Pos.x + PIPE_WIDTH){
		IsPass[1] = true;
		isScore[1]++;
		if (isScore[1] == 1){
			GameScore++;
			audio.Play(ID_POINT);
			sprintf(ScoreTemp, "%d", GameScore);
			Score = ScoreTemp;
		}
	}

	if (pbird.Pos.y+32 > GROUND_POS_Y){
		GameState = 3;
		pbird.Pos.y = GROUND_POS_Y - 35;
		audio.Play(ID_HIT);
		AfterDataInit();
	}
	if (ppipes[0].Pos.x < -PIPE_WIDTH){
		ppipes[0].Pos.x = PIPE_CREATEPOS;
		ppipes[0].SetPos(PIPE_CREATEPOS, rand() % (GROUND_POS_Y - (PIPE_SPACE + 2 * PIPE_HEAD_HIGHT)) + PIPE_HEAD_HIGHT);
		IsPass[0] = false;
		isScore[0] = 0;
	}
	if (ppipes[1].Pos.x < -PIPE_WIDTH){
		ppipes[1].Pos.x = PIPE_CREATEPOS;
		ppipes[1].SetPos(PIPE_CREATEPOS, rand() % (GROUND_POS_Y - (PIPE_SPACE + 2 * PIPE_HEAD_HIGHT)) + PIPE_HEAD_HIGHT);
		IsPass[1] = false;
		isScore[1] = 0;
	}
	if (pground.Pos.x < -GROUND_WIDTH){
		pground.SetPos(0, GROUND_POS_Y);
	}
	if (pbird.V.y > 30){
		pbird.V.y = 30;
	}

	bkground[DayState].Draw(bufferDC, 0, 0);
	pipes.Draw(ppipes[0].Pos.x, ppipes[0].Pos.y, bufferDC);
	pipes.Draw(ppipes[1].Pos.x, ppipes[1].Pos.y, bufferDC);
	ground.Draw(bufferDC, pground.Pos.x, pground.Pos.y);
	ground.Draw(bufferDC, pground.Pos.x + GROUND_WIDTH, pground.Pos.y);
	bird[BirdState].DrawHasAngle(bufferDC, pbird.Pos.x, pbird.Pos.y, birdangle);
	for (int i = 0; i < Score.size(); i++){
		num[Score[i] - '0'].Draw(bufferDC, (BKGROUND_WIDTH - Score.size()*FONT_WIDTH)/2+i*FONT_WIDTH, 70);
	}
}

void Game::AfterGame(){
	if (pbird.Pos.y < GROUND_POS_Y - 40){
		pbird.ShiftMove();
		if (pbird.Pos.y + 32 > GROUND_POS_Y){
			pbird.Pos.y = GROUND_POS_Y - 35;
		}
	}
	else{
		if (pover.Pos.y>80){
			pover.UniformMove();
			pscore.UniformMove();
		}
		else{
			afterflag = true;
		}
	}
	bkground[DayState].Draw(bufferDC, 0, 0);
	pipes.Draw(ppipes[0].Pos.x, ppipes[0].Pos.y, bufferDC);
	pipes.Draw(ppipes[1].Pos.x, ppipes[1].Pos.y, bufferDC);
	ground.Draw(bufferDC, pground.Pos.x, pground.Pos.y);
	ground.Draw(bufferDC, pground.Pos.x + GROUND_WIDTH, pground.Pos.y);
	bird[BirdState].DrawHasAngle(bufferDC, pbird.Pos.x, pbird.Pos.y, birdangle);
	over.Draw(bufferDC, pover.Pos.x, pover.Pos.y);
	score.Draw(bufferDC, pscore.Pos.x, pscore.Pos.y);
	if (afterflag){
		Medal[medal].Draw(bufferDC, 56, 192);
		begin.Draw(bufferDC, 86, 290);
		TextOut(bufferDC, 208, 227, RecordTemp, strlen(RecordTemp));
		TextOut(bufferDC, 208, 177, _T(ScoreTemp), Score.size());
	}
}