#include <graphics.h>
#include <iostream>

char boardData[3][3] =
{ {'-','-','-'},
{'-','-','-'},
{'-','-','-'},
};
//��ǰ��������
char currentPiece = 'o';

//���ָ����������Ƿ��ʤ
bool checkWin(char c)
{
	if (boardData[0][0] == c && boardData[0][1] == c && boardData[0][2] == c)
		return true;
	if (boardData[1][0] == c && boardData[1][1] == c && boardData[1][2] == c)
		return true;
	if (boardData[2][0] == c && boardData[2][1] == c && boardData[2][2] == c)
		return true;
	if (boardData[0][0] == c && boardData[1][0] == c && boardData[2][0] == c)
		return true;
	if (boardData[0][1] == c && boardData[1][1] == c && boardData[2][1] == c)
		return true;
	if (boardData[0][2] == c && boardData[1][2] == c && boardData[2][2] == c)
		return true;
	if (boardData[0][0] == c && boardData[1][1] == c && boardData[2][2] == c)
		return true;
	if (boardData[0][2] == c && boardData[1][1] == c && boardData[2][0] == c)
		return true;
	return false;
}

//����Ƿ����ƽ��
bool checkDraw()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (boardData[i][j] == '-')
				return false;
		}
	}
	return true;
}

//��������
void drawBoard()
{
	line(0, 200, 600, 200);
	line(0, 400, 600, 400);
	line(200, 0, 200, 600);
	line(400, 0, 400, 600);
}

//��������
void drawPiece()
{
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (boardData[i][j])     //switch case����break;Ĭ��ִ�к������
			{
			case 'o':
				circle(i * 200 + 100, j * 200 + 100, 100);
				break;
			case 'x':
				line(i * 200, j * 200, (i + 1) * 200, (j + 1) * 200);
				line(i * 200, (j + 1) * 200, (i + 1) * 200, j * 200);
				break;
			case '-':
				break;
			}
		}
	}
}

//������ʾ��Ϣ
void drawTipText()
{
	static TCHAR str[64];
	_stprintf_s(str, _T("��ǰ�������ͣ�%c"), currentPiece);
	settextcolor(RGB(255, 175, 45));
	outtextxy(0, 0, str);
}

int main()
{
	initgraph(600, 600);
	bool running = true;
	ExMessage msg;
	BeginBatchDraw();
	DWORD start_time = GetTickCount();
	while (running)
	{
		while (peekmessage(&msg))
		{
			if (msg.message == WM_LBUTTONDOWN)
			{
				int x = msg.x;
				int y = msg.y;
				int index_x = x / 200;
				int index_y = y / 200;
				//��������
				if (boardData[index_x][index_y] == '-')
				{
					boardData[index_x][index_y] = currentPiece;
					//�л���������
					if (currentPiece == 'o')				
						currentPiece = 'x';
					else					
						currentPiece = 'o';
				}
			}
		}
		cleardevice();
		drawBoard();
		drawPiece();
		drawTipText();
		FlushBatchDraw();
		if (checkWin('x')) 
		{
			MessageBox(GetHWnd(), _T("x��һ�ʤ"), _T("��Ϸ����"),MB_OK);
			running = false;
		}
		else if (checkWin('o'))
		{
			MessageBox(GetHWnd(), _T("o��һ�ʤ"), _T("��Ϸ����"), MB_OK);
			running = false;
		}
		else if(checkDraw())
		{
			MessageBox(GetHWnd(), _T("ƽ��"), _T("��Ϸ����"), MB_OK);
			running = false;
		}
		DWORD end_time = GetTickCount();
		DWORD delta_time = end_time - start_time;
		if (delta_time < 1000 / 60)
		{
			Sleep(1000 / 60 - delta_time);
		}
	}
	EndBatchDraw();
	return 0;
}