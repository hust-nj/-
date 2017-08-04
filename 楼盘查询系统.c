#include"estate.h"
int main(void)
{
	COORD size = { SCR_COL, SCR_ROW };              /*���ڻ�������С*/

	gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE); /* ��ȡ��׼����豸���*/
	gh_std_in = GetStdHandle(STD_INPUT_HANDLE);   /* ��ȡ��׼�����豸���*/

	SetConsoleTitle(gp_sys_name);                 /*���ô��ڱ���*/
	SetConsoleScreenBufferSize(gh_std_out, size); /*���ô��ڻ�������С80*25*/

	if (!LoadData())
		return 1;                  /*���ݼ���*/
	InitInterface();          /*�����ʼ��*/
	RunSys(&hd);             /*ϵͳ����ģ���ѡ������*/
	CloseSys(hd);            /*�˳�ϵͳ*/

	return 0;
}




BOOL HelpTopic(void)
{
	printf("--------------------------------------------------------------------------------");
	printf("��ϵͳ�ṩ�����¹���\n");
	printf("1.�ļ����ݡ����桢�ָ�����\n");
	printf("2.����&ɾ�����ݹ���\n");
	printf("3.�����������͡��۸��ѯ�������ݹ���\n");
	printf("4.ͳ��ȫ��¥�̡��������ݹ���\n");
	printf("--------------------------------------------------------------------------------");
	printf("\n\n\n");
	printf("\t\t\t\t\t\t�����������...");
	getch();
	InitInterface();
	return 1;
}

BOOL About(void)
{
	InitInterface();
	int deal1;
	LABEL_BUNDLE labels;
	HOT_AREA areas;

	SMALL_RECT rcPop;
	COORD pos;
	WORD att;
	char *pCh[] = { "���ߵĻ�                          ����" };
	int iHot = 1;

	pos.X = strlen(pCh[0]) + 6;
	pos.Y = 7;
	rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
	rcPop.Right = rcPop.Left + pos.X - 7;
	rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
	rcPop.Bottom = rcPop.Top + pos.Y - 8;
	att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
	labels.num = 1;
	labels.ppLabel = pCh;
	COORD aLoc[] = { { rcPop.Left, rcPop.Top },
	{ rcPop.Left + 5, rcPop.Top + 5 } };
	labels.pLoc = aLoc;

	areas.num = 2;
	SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
		rcPop.Left + 7, rcPop.Top },
		{ rcPop.Left + 34, rcPop.Top ,
		rcPop.Left + 37, rcPop.Top } };
	char aSort[] = { 0, 0 };
	char aTag[] = { 1, 2 };
	areas.pArea = aArea;
	areas.pSort = aSort;
	areas.pTag = aTag;
	PopUp(&rcPop, att, &labels, &areas);

	pos.X = rcPop.Left + 1;
	pos.Y = rcPop.Top + 4;

	if (DealInput(&areas, &iHot) == 13 && iHot == 1)
	{
		deal1 = 1;
	}
	else
	{
		deal1 = 0;
	}
	PopOff();
	InitInterface();

	switch (deal1)
	{
	case 0:
		printf("ϵͳ����¥�̲�ѯϵͳ\n");
		printf("����ʱ�䣺2017/8/4\n");
		printf("����ƽ̨��windows����ϵͳ\n");
		printf("--------------------------------------------------------------------------------");
		printf("�����ˣ�CS1610����\n");
		printf("���䣺hust_ningjia@hust.edu.cn\n");
		printf("��ַ��https://github.com/hust-nj/Searching-Real-Estate-System");
		printf("\n                                      -----��ӭFork me\n");
		break;
	case 1:
		printf("���������ĵ�һ��ϵͳ����Ȼ���˱Ƚ϶��ʱ�䣬\n����Ҳ���Ǻ����ƣ��������������Ǻܿ���!\n");
		break;
	}
	printf("\n\n\n");
	printf("\t\t\t\t\t\t�����������...");
	getch();
	InitInterface();
	return 1;
}

/**
* �������ƣ�Adminstrator
* �������ܣ���ȡ����ԱȨ��
* �����������
* ���������pass
* ����ֵ����
* ����˵����
*/
void Administrator(void)
{
	char account[21];
	char password[21];
	int deal1 = 1;
	while (pass && deal1)
	{
		int i = 0;		// i�����굱ǰ��λ��
		char c;
		printf("���������Ա�˺ţ�");
		while ((c = getch()) != '\r')
		{
			if (isprint(c) && i < 20)	//����Ǵ�ӡ�ַ�ʱ
			{
				account[i] = c;
				putchar(c);
				i++;
			}
			else if (c == '\b' && i > 0)	//������˸��ַ�ʱ
			{
				i--;
				putchar('\b');
				putchar(' ');
				putchar('\b');
			}
		}
		putchar('\n');
		account[i] = '\0';
		i = 0;
		printf("���������Ա���룺");
		while ((c = getch()) != '\r')
		{
			if (isprint(c) && i < 20)
			{
				password[i] = c;
				putchar('*');
				i++;
			}
			else if (c == '\b' && i > 0)
			{
				i--;
				putchar('\b');
				putchar(' ');
				putchar('\b');
			}
		}
		putchar('\n');
		password[i] = '\0';

		if (!strcmp(account, "123456789ab") && !strcmp(password, "123456"))
		{
			printf("��½�ɹ���\n");
			printf("��������������²���...");
			getchar();
			pass = 0;
			InitInterface();
		}
		else
		{
			printf("��½ʧ�ܣ������������˺ź�����򷵻�\n");

			LABEL_BUNDLE labels;
			HOT_AREA areas;

			SMALL_RECT rcPop;
			COORD pos;
			WORD att;
			char *pCh[] = { "��������                          ����" };
			int iHot = 1;

			pos.X = strlen(pCh[0]) + 6;
			pos.Y = 7;
			rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
			rcPop.Right = rcPop.Left + pos.X - 7;
			rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
			rcPop.Bottom = rcPop.Top + pos.Y - 8;
			att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
			labels.num = 1;
			labels.ppLabel = pCh;
			COORD aLoc[] = { { rcPop.Left, rcPop.Top },
			{ rcPop.Left + 5, rcPop.Top + 5 } };
			labels.pLoc = aLoc;

			areas.num = 2;
			SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
				rcPop.Left + 7, rcPop.Top },
				{ rcPop.Left + 34, rcPop.Top ,
				rcPop.Left + 37, rcPop.Top } };
			char aSort[] = { 0, 0 };
			char aTag[] = { 1, 2 };
			areas.pArea = aArea;
			areas.pSort = aSort;
			areas.pTag = aTag;
			PopUp(&rcPop, att, &labels, &areas);

			pos.X = rcPop.Left + 1;
			pos.Y = rcPop.Top + 4;

			if (DealInput(&areas, &iHot) == 13 && iHot == 1)
			{
				deal1 = 1;
			}
			else
			{
				deal1 = 0;
			}
			PopOff();
			InitInterface();
		}
	}
}


/**
* ��������: LoadData
* ��������: �������ļ����뵽�ڴ滺������ʮ��������.
* �������: ��
* �������: ��
* �� �� ֵ: BOOL���ͣ�����TRUE��ɹ����أ�����FALSE��ʧ��
* ����˵����
*/
BOOL LoadData(void)
{
	int Re;
	Re = CreatList(&hd);
	if (Re<3)
	{  /*���ݼ�����ʾ��Ϣ*/
		printf("\nϵͳ�������ݲ�����!\n");
		printf("\n�����������...\n");
		getch();
		return FALSE;
	}

	return TRUE;
}

/**
* ��������: InitInterface
* ��������: ��ʼ������.
* �������: ��
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void InitInterface()
{
	WORD att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
		| BACKGROUND_GREEN;  /*��ɫǰ������ɫ����*/

	SetConsoleTextAttribute(gh_std_out, att);  /*���ÿ���̨��Ļ�������ַ�����*/

	ClearScreen();  /* ����*/

					/*��������������Ϣ��ջ������ʼ�������Ļ���ڵ�����һ�㵯������*/
	gp_scr_att = (char *)calloc(SCR_COL * SCR_ROW, sizeof(char));/*��Ļ�ַ�����*/
	gp_top_layer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
	gp_top_layer->LayerNo = 0;      /*�������ڵĲ��Ϊ0*/
	gp_top_layer->rcArea.Left = 0;  /*�������ڵ�����Ϊ������Ļ����*/
	gp_top_layer->rcArea.Top = 0;
	gp_top_layer->rcArea.Right = SCR_COL - 1;
	gp_top_layer->rcArea.Bottom = SCR_ROW - 1;
	gp_top_layer->pContent = NULL;
	gp_top_layer->pScrAtt = gp_scr_att;
	gp_top_layer->next = NULL;

	ShowMenu();     /*��ʾ�˵���*/
	ShowState();    /*��ʾ״̬��*/

	return;
}

/**
* ��������: ClearScreen
* ��������: �����Ļ��Ϣ.
* �������: ��
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void ClearScreen(void)
{
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	COORD home = { 0, 0 };
	unsigned long size;

	GetConsoleScreenBufferInfo(gh_std_out, &bInfo);/*ȡ��Ļ��������Ϣ*/
	size = bInfo.dwSize.X * bInfo.dwSize.Y; /*������Ļ�������ַ���Ԫ��*/

											/*����Ļ���������е�Ԫ���ַ���������Ϊ��ǰ��Ļ�������ַ�����*/
	FillConsoleOutputAttribute(gh_std_out, bInfo.wAttributes, size, home, &rec);

	/*����Ļ���������е�Ԫ���Ϊ�ո��ַ�*/
	FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &rec);

	return;
}

/**
* ��������: ShowMenu
* ��������: ����Ļ����ʾ���˵�, ����������, �����˵���һ������ѡ�б��.
* �������: ��
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void ShowMenu()
{
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	CONSOLE_CURSOR_INFO lpCur;
	COORD size;
	COORD pos = { 0, 0 };
	int i, j;
	int PosA = 2, PosB;
	char ch;

	GetConsoleScreenBufferInfo(gh_std_out, &bInfo);
	size.X = bInfo.dwSize.X;
	size.Y = 1;
	SetConsoleCursorPosition(gh_std_out, pos);
	for (i = 0; i < 5; i++) /*�ڴ��ڵ�һ�е�һ�д�������˵���*/
	{
		printf("  %s  ", ga_main_menu[i]);
	}

	GetConsoleCursorInfo(gh_std_out, &lpCur);
	lpCur.bVisible = FALSE;
	SetConsoleCursorInfo(gh_std_out, &lpCur);  /*���ع��*/

											   /*���붯̬�洢����Ϊ��Ų˵�����Ļ���ַ���Ϣ�Ļ�����*/
	gp_buff_menubar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
	SMALL_RECT rcMenu = { 0, 0, size.X - 1, 0 };

	/*�����ڵ�һ�е����ݶ��뵽��Ų˵�����Ļ���ַ���Ϣ�Ļ�������*/
	ReadConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

	/*����һ����Ӣ����ĸ��Ϊ��ɫ�������ַ���Ԫ��Ϊ�׵׺���*/
	for (i = 0; i<size.X; i++)
	{
		(gp_buff_menubar_info + i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
			| BACKGROUND_RED;
		ch = (char)((gp_buff_menubar_info + i)->Char.AsciiChar);
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		{
			(gp_buff_menubar_info + i)->Attributes |= FOREGROUND_RED;
		}
	}

	/*�޸ĺ�Ĳ˵����ַ���Ϣ��д�����ڵĵ�һ��*/
	WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);
	COORD endPos = { 0, 1 };
	SetConsoleCursorPosition(gh_std_out, endPos);  /*�����λ�������ڵ�2�е�1��*/

												   /*���˵�����Ϊ�������������Ϊ�˵���ţ���������Ϊ0(��ť��)*/
	i = 0;
	do
	{
		PosB = PosA + strlen(ga_main_menu[i]);  /*��λ��i+1�Ų˵������ֹλ��*/
		for (j = PosA; j<PosB; j++)
		{
			gp_scr_att[j] |= (i + 1) << 2; /*���ò˵��������ַ���Ԫ������ֵ*/
		}
		PosA = PosB + 4;
		i++;
	} while (i<5);

	TagMainMenu(gi_sel_menu);  /*��ѡ�����˵���������ǣ�gi_sel_menu��ֵΪ1*/

	return;
}

/**
* ��������: ShowState
* ��������: ��ʾ״̬��.
* �������: ��
* �������: ��
* �� �� ֵ: ��
*
* ����˵��: ״̬���ַ�����Ϊ�׵׺���, ��ʼ״̬��״̬��Ϣ.
*/
void ShowState()
{
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	COORD size;
	COORD pos = { 0, 0 };
	int i;

	GetConsoleScreenBufferInfo(gh_std_out, &bInfo);
	size.X = bInfo.dwSize.X;
	size.Y = 1;
	SMALL_RECT rcMenu = { 0, bInfo.dwSize.Y - 1, size.X - 1, bInfo.dwSize.Y - 1 };

	if (gp_buff_stateBar_info == NULL)
	{
		gp_buff_stateBar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
		ReadConsoleOutput(gh_std_out, gp_buff_stateBar_info, size, pos, &rcMenu);
	}

	for (i = 0; i<size.X; i++)
	{
		(gp_buff_stateBar_info + i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
			| BACKGROUND_RED;
		/*
		ch = (char)((gp_buff_stateBar_info+i)->Char.AsciiChar);
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		{
		(gp_buff_stateBar_info+i)->Attributes |= FOREGROUND_RED;
		}
		*/
	}

	WriteConsoleOutput(gh_std_out, gp_buff_stateBar_info, size, pos, &rcMenu);

	return;
}

/**
* ��������: TagMainMenu
* ��������: ��ָ�����˵�������ѡ�б�־.
* �������: num ѡ�е����˵����
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void TagMainMenu(int num)
{
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	COORD size;
	COORD pos = { 0, 0 };
	int PosA = 2, PosB;
	char ch;
	int i;

	if (num == 0) /*numΪ0ʱ������ȥ�����˵���ѡ�б��*/
	{
		PosA = 0;
		PosB = 0;
	}
	else  /*���򣬶�λѡ�����˵������ֹλ��: PosAΪ��ʼλ��, PosBΪ��ֹλ��*/
	{
		for (i = 1; i<num; i++)
		{
			PosA += strlen(ga_main_menu[i - 1]) + 4;
		}
		PosB = PosA + strlen(ga_main_menu[num - 1]);
	}

	GetConsoleScreenBufferInfo(gh_std_out, &bInfo);
	size.X = bInfo.dwSize.X;
	size.Y = 1;

	/*ȥ��ѡ�в˵���ǰ��Ĳ˵���ѡ�б��*/
	for (i = 0; i<PosA; i++)
	{
		(gp_buff_menubar_info + i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
			| BACKGROUND_RED;
		ch = (gp_buff_menubar_info + i)->Char.AsciiChar;
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		{
			(gp_buff_menubar_info + i)->Attributes |= FOREGROUND_RED;
		}
	}

	/*��ѡ�в˵���������ǣ��ڵװ���*/
	for (i = PosA; i<PosB; i++)
	{
		(gp_buff_menubar_info + i)->Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN
			| FOREGROUND_RED;
	}

	/*ȥ��ѡ�в˵������Ĳ˵���ѡ�б��*/
	for (i = PosB; i<bInfo.dwSize.X; i++)
	{
		(gp_buff_menubar_info + i)->Attributes = BACKGROUND_BLUE | BACKGROUND_GREEN
			| BACKGROUND_RED;
		ch = (char)((gp_buff_menubar_info + i)->Char.AsciiChar);
		if ((ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'))
		{
			(gp_buff_menubar_info + i)->Attributes |= FOREGROUND_RED;
		}
	}

	/*�����ñ�ǵĲ˵�����Ϣд�����ڵ�һ��*/
	SMALL_RECT rcMenu = { 0, 0, size.X - 1, 0 };
	WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

	return;
}

/**
* ��������: CloseSys
* ��������: �ر�ϵͳ.
* �������: hd ����ͷָ��
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void CloseSys(ESTATE_NODE *hd)
{
	ESTATE_NODE *pPremNode1 = hd, *pPremNode2;
	BUILD_NODE *pBuilNode1, *pBuilNode2;
	HOUSE_NODE *pHouseNode1, *pHouseNode2;

	while (pPremNode1 != NULL) /*�ͷ�ʮ�ֽ�������Ķ�̬�洢��*/
	{
		pPremNode2 = pPremNode1->next;
		pBuilNode1 = pPremNode1->bnext;
		while (pBuilNode1 != NULL) /*�ͷ�¥��������Ϣ֧���Ķ�̬�洢��*/
		{
			pBuilNode2 = pBuilNode1->next;
			pHouseNode1 = pBuilNode1->hnext;
			while (pHouseNode1 != NULL) /*�ͷŷ�����Ϣ֧���Ķ�̬�洢��*/
			{
				pHouseNode2 = pHouseNode1->next;
				free(pHouseNode1);
				pHouseNode1 = pHouseNode2;
			}
			free(pBuilNode1);
			pBuilNode1 = pBuilNode2;
		}
		free(pPremNode1);  /*�ͷ��������Ķ�̬�洢��*/
		pPremNode1 = pPremNode2;
	}

	ClearScreen();        /*����*/

						  /*�ͷŴ�Ų˵�����״̬�����Ա�����ѧ�����������Ϣ��̬�洢��*/
	free(gp_buff_menubar_info);
	free(gp_buff_stateBar_info);

	/*�رձ�׼���������豸���*/
	CloseHandle(gh_std_out);
	CloseHandle(gh_std_in);

	/*�����ڱ�������Ϊ���н���*/
	SetConsoleTitle("���н���");

	return;
}


/**
* ��������: RunSys
* ��������: ����ϵͳ, ��ϵͳ�������������û���ѡ��Ĺ���ģ��.
* �������: ��
* �������: phead ����ͷָ��ĵ�ַ
* �� �� ֵ: ��
*
* ����˵��:
*/
void RunSys(ESTATE_NODE **phead)
{
	INPUT_RECORD inRec;
	DWORD res;
	COORD pos = { 0, 0 };
	BOOL bRet = TRUE;
	int i, loc, num;
	int cNo, cAtt;      /*cNo:�ַ���Ԫ���, cAtt:�ַ���Ԫ����*/
	char vkc, asc;      /*vkc:���������, asc:�ַ���ASCII��ֵ*/

	while (bRet)
	{
		/*�ӿ���̨���뻺�����ж�һ����¼*/
		ReadConsoleInput(gh_std_in, &inRec, 1, &res);

		if (inRec.EventType == MOUSE_EVENT) /*�����¼������¼�����*/
		{
			pos = inRec.Event.MouseEvent.dwMousePosition;  /*��ȡ�������λ��*/
			cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3; /*ȡ��λ�õĲ��*/
			cAtt = gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2;/*ȡ���ַ���Ԫ����*/
			if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
			{
				/* cAtt > 0 ������λ�ô�������(���˵����ַ���Ԫ)
				* cAtt != gi_sel_menu ������λ�õ����˵���δ��ѡ��
				* gp_top_layer->LayerNo > 0 ������ǰ���Ӳ˵�����
				*/
				if (cAtt > 0 && cAtt != gi_sel_menu && gp_top_layer->LayerNo > 0)
				{
					PopOff();            /*�رյ������Ӳ˵�*/
					gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
					PopMenu(cAtt);       /*��������������˵����Ӧ���Ӳ˵�*/
				}
			}
			else if (cAtt > 0) /*�������λ��Ϊ�����Ӳ˵��Ĳ˵����ַ���Ԫ*/
			{
				TagSubMenu(cAtt); /*�ڸ��Ӳ˵�������ѡ�б��*/
			}

			if (inRec.Event.MouseEvent.dwButtonState
				== FROM_LEFT_1ST_BUTTON_PRESSED) /*������������ߵ�һ��*/
			{
				if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
				{
					if (cAtt > 0) /*�����λ�ô�������(���˵����ַ���Ԫ)*/
					{
						PopMenu(cAtt);   /*��������������˵����Ӧ���Ӳ˵�*/
					}
					/*�����λ�ò��������˵����ַ���Ԫ�������Ӳ˵�����*/
					else if (gp_top_layer->LayerNo > 0)
					{
						PopOff();            /*�رյ������Ӳ˵�*/
						gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
					}
				}
				else /*��Ų�Ϊ0��������λ�ñ������Ӳ˵�����*/
				{
					if (cAtt > 0) /*�����λ�ô�������(�Ӳ˵����ַ���Ԫ)*/
					{
						PopOff(); /*�رյ������Ӳ˵�*/
						gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/

											 /*ִ�ж�Ӧ���ܺ���:gi_sel_menu���˵����,cAtt�Ӳ˵����*/
						bRet = ExeFunction(gi_sel_menu, cAtt);
					}
				}
			}
			else if (inRec.Event.MouseEvent.dwButtonState
				== RIGHTMOST_BUTTON_PRESSED) /*�����������Ҽ�*/
			{
				if (cNo == 0) /*���Ϊ0��������λ��δ�������Ӳ˵�����*/
				{
					PopOff();            /*�رյ������Ӳ˵�*/
					gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
				}
			}
		}
		else if (inRec.EventType == KEY_EVENT  /*�����¼�ɰ�������*/
			&& inRec.Event.KeyEvent.bKeyDown) /*�Ҽ�������*/
		{
			vkc = inRec.Event.KeyEvent.wVirtualKeyCode; /*��ȡ�������������*/
			asc = inRec.Event.KeyEvent.uChar.AsciiChar; /*��ȡ������ASC��*/

														/*ϵͳ��ݼ��Ĵ���*/
			if (vkc == 112) /*�������F1��*/
			{
				if (gp_top_layer->LayerNo != 0) /*�����ǰ���Ӳ˵�����*/
				{
					PopOff();            /*�رյ������Ӳ˵�*/
					gi_sel_sub_menu = 0; /*��ѡ���Ӳ˵���������Ϊ0*/
				}
				bRet = ExeFunction(5, 1);  /*���а������⹦�ܺ���*/
			}
			else if (inRec.Event.KeyEvent.dwControlKeyState
				& (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))
			{ /*������������Alt��*/
				switch (vkc)  /*�ж���ϼ�Alt+��ĸ*/
				{
				case 88:  /*Alt+X �˳�*/
					if (gp_top_layer->LayerNo != 0)
					{
						PopOff();
						gi_sel_sub_menu = 0;
					}
					bRet = ExeFunction(1, 4);
					break;
				case 70:  /*Alt+F*/
					PopMenu(1);
					break;
				case 77: /*Alt+M*/
					PopMenu(2);
					break;
				case 81: /*Alt+Q*/
					PopMenu(3);
					break;
				case 83: /*Alt+S*/
					PopMenu(4);
					break;
				case 72: /*Alt+H*/
					PopMenu(5);
					break;
				}
			}
			else if (asc == 0) /*�������Ƽ��Ĵ���*/
			{
				if (gp_top_layer->LayerNo == 0) /*���δ�����Ӳ˵�*/
				{
					switch (vkc) /*�������(���ҡ���)������Ӧ�������Ƽ�*/
					{
					case 37:
						gi_sel_menu--;
						if (gi_sel_menu == 0)
						{
							gi_sel_menu = 5;
						}
						TagMainMenu(gi_sel_menu);
						break;
					case 39:
						gi_sel_menu++;
						if (gi_sel_menu == 6)
						{
							gi_sel_menu = 1;
						}
						TagMainMenu(gi_sel_menu);
						break;
					case 40:
						PopMenu(gi_sel_menu);
						TagSubMenu(1);
						break;
					}
				}
				else  /*�ѵ����Ӳ˵�ʱ*/
				{
					for (loc = 0, i = 1; i<gi_sel_menu; i++)
					{
						loc += ga_sub_menu_count[i - 1];
					}  /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
					switch (vkc) /*�����(���ҡ��ϡ���)�Ĵ���*/
					{
					case 37:
						gi_sel_menu--;
						if (gi_sel_menu < 1)
						{
							gi_sel_menu = 5;
						}
						TagMainMenu(gi_sel_menu);
						PopOff();
						PopMenu(gi_sel_menu);
						TagSubMenu(1);
						break;
					case 38:
						num = gi_sel_sub_menu - 1;
						if (num < 1)
						{
							num = ga_sub_menu_count[gi_sel_menu - 1];
						}
						if (strlen(ga_sub_menu[loc + num - 1]) == 0)
						{
							num--;
						}
						TagSubMenu(num);
						break;
					case 39:
						gi_sel_menu++;
						if (gi_sel_menu > 5)
						{
							gi_sel_menu = 1;
						}
						TagMainMenu(gi_sel_menu);
						PopOff();
						PopMenu(gi_sel_menu);
						TagSubMenu(1);
						break;
					case 40:
						num = gi_sel_sub_menu + 1;
						if (num > ga_sub_menu_count[gi_sel_menu - 1])
						{
							num = 1;
						}
						if (strlen(ga_sub_menu[loc + num - 1]) == 0)
						{
							num++;
						}
						TagSubMenu(num);
						break;
					}
				}
			}
			else if ((asc - vkc == 0) || (asc - vkc == 32)) {  /*������ͨ��*/
				if (gp_top_layer->LayerNo == 0)  /*���δ�����Ӳ˵�*/
				{
					switch (vkc)
					{
					case 70: /*f��F*/
						PopMenu(1);
						break;
					case 77: /*m��M*/
						PopMenu(2);
						break;
					case 81: /*q��Q*/
						PopMenu(3);
						break;
					case 83: /*s��S*/
						PopMenu(4);
						break;
					case 72: /*h��H*/
						PopMenu(5);
						break;
					case 13: /*�س�*/
						PopMenu(gi_sel_menu);
						TagSubMenu(1);
						break;
					}
				}
				else /*�ѵ����Ӳ˵�ʱ�ļ������봦��*/
				{
					if (vkc == 27) /*�������ESC��*/
					{
						PopOff();
						gi_sel_sub_menu = 0;
					}
					else if (vkc == 13) /*������»س���*/
					{
						num = gi_sel_sub_menu;
						PopOff();
						gi_sel_sub_menu = 0;
						bRet = ExeFunction(gi_sel_menu, num);
					}
					else /*������ͨ���Ĵ���*/
					{
						/*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
						for (loc = 0, i = 1; i<gi_sel_menu; i++)
						{
							loc += ga_sub_menu_count[i - 1];
						}

						/*�����뵱ǰ�Ӳ˵���ÿһ��Ĵ����ַ����бȽ�*/
						for (i = loc; i<loc + ga_sub_menu_count[gi_sel_menu - 1]; i++)
						{
							if (strlen(ga_sub_menu[i])>0 && vkc == ga_sub_menu[i][1])
							{ /*���ƥ��ɹ�*/
								PopOff();
								gi_sel_sub_menu = 0;
								bRet = ExeFunction(gi_sel_menu, i - loc + 1);
							}
						}
					}
				}
			}
		}
	}
}


/**
* ��������: PopMenu
* ��������: ����ָ�����˵����Ӧ���Ӳ˵�.
* �������: num ָ�������˵����
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void PopMenu(int num)
{
	LABEL_BUNDLE labels;
	HOT_AREA areas;
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;
	char *pCh;
	int i, j, loc = 0;

	if (num != gi_sel_menu)       /*���ָ�����˵�������ѡ�в˵�*/
	{
		if (gp_top_layer->LayerNo != 0) /*�����ǰ�����Ӳ˵�����*/
		{
			PopOff();
			gi_sel_sub_menu = 0;
		}
	}
	else if (gp_top_layer->LayerNo != 0) /*���ѵ������Ӳ˵����򷵻�*/
	{
		return;
	}

	gi_sel_menu = num;    /*��ѡ�����˵�����Ϊָ�������˵���*/
	TagMainMenu(gi_sel_menu); /*��ѡ�е����˵����������*/
	LocSubMenu(gi_sel_menu, &rcPop); /*���㵯���Ӳ˵�������λ��, �����rcPop��*/

									 /*������Ӳ˵��еĵ�һ�����Ӳ˵��ַ��������е�λ��(�±�)*/
	for (i = 1; i<gi_sel_menu; i++)
	{
		loc += ga_sub_menu_count[i - 1];
	}
	/*�������Ӳ˵������������ǩ���ṹ����*/
	labels.ppLabel = ga_sub_menu + loc;   /*��ǩ����һ����ǩ�ַ����ĵ�ַ*/
	labels.num = ga_sub_menu_count[gi_sel_menu - 1]; /*��ǩ���б�ǩ�ַ����ĸ���*/
	COORD* aLoc = (COORD*)calloc(sizeof(COORD), labels.num);/*����һ���������飬���ÿ����ǩ�ַ������λ�õ�����*/
	for (i = 0; i<labels.num; i++) /*ȷ����ǩ�ַ��������λ�ã����������������*/
	{
		aLoc[i].X = rcPop.Left + 2;
		aLoc[i].Y = rcPop.Top + i + 1;
	}
	labels.pLoc = aLoc; /*ʹ��ǩ���ṹ����labels�ĳ�ԱpLocָ�������������Ԫ��*/
						/*����������Ϣ*/
	areas.num = labels.num;       /*�����ĸ��������ڱ�ǩ�ĸ��������Ӳ˵�������*/
	SMALL_RECT *aArea = (SMALL_RECT*)calloc(sizeof(SMALL_RECT), areas.num);                    /*������������������λ��*/
	char *aSort = (char*)calloc(sizeof(char), areas.num);                      /*��������������������Ӧ���*/
	char *aTag = (char*)calloc(sizeof(char), areas.num);                         /*����������ÿ�������ı��*/
	for (i = 0; i<areas.num; i++)
	{
		aArea[i].Left = rcPop.Left + 2;  /*������λ*/
		aArea[i].Top = rcPop.Top + i + 1;
		aArea[i].Right = rcPop.Right - 2;
		aArea[i].Bottom = aArea[i].Top;
		aSort[i] = 0;       /*�������Ϊ0(��ť��)*/
		aTag[i] = i + 1;           /*������˳����*/
	}
	areas.pArea = aArea;/*ʹ�����ṹ����areas�ĳ�ԱpAreaָ������λ��������Ԫ��*/
	areas.pSort = aSort;/*ʹ�����ṹ����areas�ĳ�ԱpSortָ���������������Ԫ��*/
	areas.pTag = aTag;   /*ʹ�����ṹ����areas�ĳ�ԱpTagָ���������������Ԫ��*/

	att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
	PopUp(&rcPop, att, &labels, &areas);
	DrawBox(&rcPop);  /*���������ڻ��߿�*/
	pos.X = rcPop.Left + 2;
	for (pos.Y = rcPop.Top + 1; pos.Y<rcPop.Bottom; pos.Y++)
	{ /*��ѭ�������ڿմ��Ӳ���λ�û����γɷָ�����ȡ���˲˵������������*/
		pCh = ga_sub_menu[loc + pos.Y - rcPop.Top - 1];
		if (strlen(pCh) == 0) /*����Ϊ0������Ϊ�մ�*/
		{   /*���Ȼ�����*/
			FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right - rcPop.Left - 3, pos, &rec);
			for (j = rcPop.Left + 2; j<rcPop.Right - 1; j++)
			{   /*ȡ���������ַ���Ԫ����������*/
				gp_scr_att[pos.Y*SCR_COL + j] &= 3; /*��λ��Ľ�������˵���λ*/
			}
		}

	}
	/*���Ӳ˵���Ĺ��ܼ���Ϊ�׵׺���*/
	pos.X = rcPop.Left + 3;
	att = FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
	for (pos.Y = rcPop.Top + 1; pos.Y<rcPop.Bottom; pos.Y++)
	{
		if (strlen(ga_sub_menu[loc + pos.Y - rcPop.Top - 1]) == 0)
		{
			continue;  /*�����մ�*/
		}
		FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &rec);
	}
	return;
}

/**
* ��������: PopUp
* ��������: ��ָ�������������������Ϣ, ͬʱ��������, ����������λ����Ϣ��ջ.
* �������: pRc ��������λ�����ݴ�ŵĵ�ַ
*           att �������������ַ�����
*           pLabel ���������б�ǩ����Ϣ��ŵĵ�ַ
pHotArea ����������������Ϣ��ŵĵ�ַ
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void PopUp(SMALL_RECT *pRc, WORD att, LABEL_BUNDLE *pLabel, HOT_AREA *pHotArea)
{
	LAYER_NODE *nextLayer;
	COORD size;
	COORD pos = { 0, 0 };
	char *pCh;
	int i, j, row;

	/*������������λ���ַ���Ԫ��Ϣ��ջ*/
	size.X = pRc->Right - pRc->Left + 1;    /*�������ڵĿ��*/
	size.Y = pRc->Bottom - pRc->Top + 1;    /*�������ڵĸ߶�*/
											/*�����ŵ������������Ϣ�Ķ�̬�洢��*/
	nextLayer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
	nextLayer->next = gp_top_layer;
	nextLayer->LayerNo = gp_top_layer->LayerNo + 1;
	nextLayer->rcArea = *pRc;
	nextLayer->pContent = (CHAR_INFO *)malloc(size.X*size.Y * sizeof(CHAR_INFO));
	nextLayer->pScrAtt = (char *)malloc(size.X*size.Y * sizeof(char));
	pCh = nextLayer->pScrAtt;
	/*���������ڸ���������ַ���Ϣ���棬�����ڹرյ�������ʱ�ָ�ԭ��*/
	ReadConsoleOutput(gh_std_out, nextLayer->pContent, size, pos, pRc);
	for (i = pRc->Top; i <= pRc->Bottom; i++)
	{   /*�˶���ѭ�����������ַ���Ԫ��ԭ������ֵ���붯̬�洢���������Ժ�ָ�*/
		for (j = pRc->Left; j <= pRc->Right; j++)
		{
			*pCh = gp_scr_att[i*SCR_COL + j];
			pCh++;
		}
	}
	gp_top_layer = nextLayer;  /*��ɵ������������Ϣ��ջ����*/
							   /*���õ������������ַ���������*/
	pos.X = pRc->Left;
	pos.Y = pRc->Top;
	for (i = pRc->Top; i <= pRc->Bottom; i++)
	{
		FillConsoleOutputAttribute(gh_std_out, att, size.X, pos, &rec);
		pos.Y++;
	}
	/*����ǩ���еı�ǩ�ַ������趨��λ�����*/
	for (i = 0; i<pLabel->num; i++)
	{
		pCh = pLabel->ppLabel[i];
		if (strlen(pCh) != 0)
		{
			WriteConsoleOutputCharacter(gh_std_out, pCh, strlen(pCh),
				pLabel->pLoc[i], &rec);
		}
	}
	/*���õ������������ַ���Ԫ��������*/
	for (i = pRc->Top; i <= pRc->Bottom; i++)
	{   /*�˶���ѭ�������ַ���Ԫ�Ĳ��*/
		for (j = pRc->Left; j <= pRc->Right; j++)
		{
			gp_scr_att[i*SCR_COL + j] = gp_top_layer->LayerNo;
		}
	}

	for (i = 0; i<pHotArea->num; i++)
	{   /*�˶���ѭ�����������������ַ���Ԫ���������ͺ��������*/
		row = pHotArea->pArea[i].Top;
		for (j = pHotArea->pArea[i].Left; j <= pHotArea->pArea[i].Right; j++)
		{
			gp_scr_att[row*SCR_COL + j] |= (pHotArea->pSort[i] << 6)
				| (pHotArea->pTag[i] << 2);
		}
	}
	return;
}

/**
* ��������: PopOff
* ��������: �رն��㵯������, �ָ���������ԭ��ۺ��ַ���Ԫԭ����.
* �������: ��
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void PopOff(void)
{
	LAYER_NODE *nextLayer;
	COORD size;
	COORD pos = { 0, 0 };
	char *pCh;
	int i, j;

	if ((gp_top_layer->next == NULL) || (gp_top_layer->pContent == NULL))
	{   /*ջ�״�ŵ���������Ļ��Ϣ�����ùر�*/
		return;
	}
	nextLayer = gp_top_layer->next;
	/*�ָ�������������ԭ���*/
	size.X = gp_top_layer->rcArea.Right - gp_top_layer->rcArea.Left + 1;
	size.Y = gp_top_layer->rcArea.Bottom - gp_top_layer->rcArea.Top + 1;
	WriteConsoleOutput(gh_std_out, gp_top_layer->pContent, size, pos, &(gp_top_layer->rcArea));
	/*�ָ��ַ���Ԫԭ����*/
	pCh = gp_top_layer->pScrAtt;
	for (i = gp_top_layer->rcArea.Top; i <= gp_top_layer->rcArea.Bottom; i++)
	{
		for (j = gp_top_layer->rcArea.Left; j <= gp_top_layer->rcArea.Right; j++)
		{
			gp_scr_att[i*SCR_COL + j] = *pCh;
			pCh++;
		}
	}
	free(gp_top_layer->pContent);    /*�ͷŶ�̬�洢��*/
	free(gp_top_layer->pScrAtt);
	free(gp_top_layer);
	gp_top_layer = nextLayer;
	gi_sel_sub_menu = 0;
	return;
}

/**
* ��������: DrawBox
* ��������: ��ָ�����򻭱߿�.
* �������: pRc �������λ����Ϣ�ĵ�ַ
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void DrawBox(SMALL_RECT *pRc)
{
	char chBox[] = { '+','-','|' };  /*�����õ��ַ�*/
	COORD pos = { pRc->Left, pRc->Top };  /*��λ����������Ͻ�*/

	WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &rec);/*���߿����Ͻ�*/
	for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
	{   /*��ѭ�����ϱ߿����*/
		WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &rec);
	}
	pos.X = pRc->Right;
	WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &rec);/*���߿����Ͻ�*/
	for (pos.Y = pRc->Top + 1; pos.Y < pRc->Bottom; pos.Y++)
	{   /*��ѭ�����߿�����ߺ��ұ���*/
		pos.X = pRc->Left;
		WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &rec);
		pos.X = pRc->Right;
		WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &rec);
	}
	pos.X = pRc->Left;
	pos.Y = pRc->Bottom;
	WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &rec);/*���߿����½�*/
	for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
	{   /*���±߿����*/
		WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &rec);
	}
	pos.X = pRc->Right;
	WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &rec);/*���߿����½�*/
	return;
}


/**
* ��������: TagSubMenu
* ��������: ��ָ���Ӳ˵�������ѡ�б��.
* �������: num ѡ�е��Ӳ˵����
* �������: ��
* �� �� ֵ: ��
*
* ����˵��:
*/
void TagSubMenu(int num)
{
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;
	int width;

	LocSubMenu(gi_sel_menu, &rcPop);  /*���㵯���Ӳ˵�������λ��, �����rcPop��*/
	if ((num<1) || (num == gi_sel_sub_menu) || (num>rcPop.Bottom - rcPop.Top - 1))
	{   /*����Ӳ˵����Խ�磬������Ӳ˵��ѱ�ѡ�У��򷵻�*/
		return;
	}

	pos.X = rcPop.Left + 2;
	width = rcPop.Right - rcPop.Left - 3;
	if (gi_sel_sub_menu != 0) /*����ȡ��ԭѡ���Ӳ˵����ϵı��*/
	{
		pos.Y = rcPop.Top + gi_sel_sub_menu;
		att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
		FillConsoleOutputAttribute(gh_std_out, att, width, pos, &rec);
		pos.X += 1;
		att |= FOREGROUND_RED;/*�׵׺���*/
		FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &rec);
	}
	/*���ƶ��Ӳ˵�������ѡ�б��*/
	pos.X = rcPop.Left + 2;
	pos.Y = rcPop.Top + num;
	att = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*�ڵװ���*/
	FillConsoleOutputAttribute(gh_std_out, att, width, pos, &rec);
	gi_sel_sub_menu = num;  /*�޸�ѡ���Ӳ˵����*/
	return;
}

/**
* ��������: LocSubMenu
* ��������: ���㵯���Ӳ˵��������ϽǺ����½ǵ�λ��.
* �������: num ѡ�е����˵����
* �������: rc �������λ����Ϣ�ĵ�ַ
* �� �� ֵ: ��
*
* ����˵��:
*/
void LocSubMenu(int num, SMALL_RECT *rc)
{
	int i, len, loc = 0;

	rc->Top = 1; /*������ϱ߶��ڵ�2�У��к�Ϊ1*/
	rc->Left = 1;
	for (i = 1; i<num; i++)
	{   /*����������߽�λ��, ͬʱ�����һ���Ӳ˵������Ӳ˵��ַ��������е�λ��*/
		rc->Left += strlen(ga_main_menu[i - 1]) + 4;
		loc += ga_sub_menu_count[i - 1];
	}
	rc->Right = strlen(ga_sub_menu[loc]);/*��ʱ��ŵ�һ���Ӳ˵����ַ�������*/
	for (i = 1; i<ga_sub_menu_count[num - 1]; i++)
	{   /*������Ӳ˵��ַ��������䳤�ȴ����rc->Right*/
		len = strlen(ga_sub_menu[loc + i]);
		if (rc->Right < len)
		{
			rc->Right = len;
		}
	}
	rc->Right += rc->Left + 3;  /*����������ұ߽�*/
	rc->Bottom = rc->Top + ga_sub_menu_count[num - 1] + 1;/*���������±ߵ��к�*/
	if (rc->Right >= SCR_COL)  /*�ұ߽�Խ��Ĵ���*/
	{
		len = rc->Right - SCR_COL + 1;
		rc->Left -= len;
		rc->Right = SCR_COL - 1;
	}
	return;
}


int DealInput(HOT_AREA *pHotArea, int *piHot)
{
	INPUT_RECORD inRec;
	DWORD res;
	COORD pos = { 0, 0 };
	int num, arrow, iRet = 0;
	int cNo, cTag, cSort;/*cNo:���, cTag:�������, cSort: ��������*/
	char vkc, asc;       /*vkc:���������, asc:�ַ���ASCII��ֵ*/

	SetHotPoint(pHotArea, *piHot);
	while (TRUE)
	{    /*ѭ��*/
		ReadConsoleInput(gh_std_in, &inRec, 1, &res);
		if ((inRec.EventType == MOUSE_EVENT) &&
			(inRec.Event.MouseEvent.dwButtonState
				== FROM_LEFT_1ST_BUTTON_PRESSED))
		{
			pos = inRec.Event.MouseEvent.dwMousePosition;
			cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3;
			cTag = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2) & 15;
			cSort = (gp_scr_att[pos.Y * SCR_COL + pos.X] >> 6) & 3;

			if ((cNo == gp_top_layer->LayerNo) && cTag > 0)
			{
				*piHot = cTag;
				SetHotPoint(pHotArea, *piHot);
				if (cSort == 0)
				{
					iRet = 13;
					break;
				}
			}
		}
		else if (inRec.EventType == KEY_EVENT && inRec.Event.KeyEvent.bKeyDown)
		{
			vkc = inRec.Event.KeyEvent.wVirtualKeyCode;
			asc = inRec.Event.KeyEvent.uChar.AsciiChar;;
			if (asc == 0)
			{
				arrow = 0;
				switch (vkc)
				{  /*�����(���ϡ��ҡ���)�Ĵ���*/
				case 37: arrow = 1; break;
				case 38: arrow = 2; break;
				case 39: arrow = 3; break;
				case 40: arrow = 4; break;
				}
				if (arrow > 0)
				{
					num = *piHot;
					while (TRUE)
					{
						if (arrow < 3)
						{
							num--;
						}
						else
						{
							num++;
						}
						if ((num < 1) || (num > pHotArea->num) ||
							((arrow % 2) && (pHotArea->pArea[num - 1].Top
								== pHotArea->pArea[*piHot - 1].Top)) || ((!(arrow % 2))
									&& (pHotArea->pArea[num - 1].Top
										!= pHotArea->pArea[*piHot - 1].Top)))
						{
							break;
						}
					}
					if (num > 0 && num <= pHotArea->num)
					{
						*piHot = num;
						SetHotPoint(pHotArea, *piHot);
					}
				}
			}
			else if (vkc == 27)
			{  /*ESC��*/
				iRet = 27;
				break;
			}
			else if (vkc == 13 || vkc == 32)
			{  /*�س�����ո��ʾ���µ�ǰ��ť*/
				iRet = 13;
				break;
			}
		}
	}
	return iRet;
}

void SetHotPoint(HOT_AREA *pHotArea, int iHot)
{
	CONSOLE_CURSOR_INFO lpCur;
	COORD pos = { 0, 0 };
	WORD att1, att2;
	int i, width;

	att1 = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*�ڵװ���*/
	att2 = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
	for (i = 0; i<pHotArea->num; i++)
	{  /*����ť��������Ϊ�׵׺���*/
		pos.X = pHotArea->pArea[i].Left;
		pos.Y = pHotArea->pArea[i].Top;
		width = pHotArea->pArea[i].Right - pHotArea->pArea[i].Left + 1;
		if (pHotArea->pSort[i] == 0)
		{  /*�����ǰ�ť��*/
			FillConsoleOutputAttribute(gh_std_out, att2, width, pos, &rec);
		}
	}

	pos.X = pHotArea->pArea[iHot - 1].Left;
	pos.Y = pHotArea->pArea[iHot - 1].Top;
	width = pHotArea->pArea[iHot - 1].Right - pHotArea->pArea[iHot - 1].Left + 1;
	if (pHotArea->pSort[iHot - 1] == 0)
	{  /*�����������ǰ�ť��*/
		FillConsoleOutputAttribute(gh_std_out, att1, width, pos, &rec);
	}
	else if (pHotArea->pSort[iHot - 1] == 1)
	{  /*�������������ı�����*/
		SetConsoleCursorPosition(gh_std_out, pos);
		GetConsoleCursorInfo(gh_std_out, &lpCur);
		lpCur.bVisible = TRUE;
		SetConsoleCursorInfo(gh_std_out, &lpCur);
	}
}

/**
* ��������: ExeFunction
* ��������: ִ�������˵��ź��Ӳ˵���ȷ���Ĺ��ܺ���.
* �������: m ���˵����
*           s �Ӳ˵����
* �������: ��
* �� �� ֵ: BOOL����, TRUE �� FALSE
*
* ����˵��: ����ִ�к���ExitSysʱ, �ſ��ܷ���FALSE, ������������Ƿ���TRUE
*/
BOOL ExeFunction(int m, int s)
{
	InitInterface();
	BOOL bRet = TRUE;
	/*����ָ�����飬����������й��ܺ�������ڵ�ַ*/
	BOOL(**pFunction)(void);
	pFunction = (BOOL(**)(void))calloc(sizeof(BOOL(*)(void)),
		ga_sub_menu_count[0] + ga_sub_menu_count[1] + ga_sub_menu_count[2] + ga_sub_menu_count[3] + ga_sub_menu_count[4]);
	int i, loc;

	/*�����ܺ�����ڵ�ַ�����빦�ܺ����������˵��ź��Ӳ˵��Ŷ�Ӧ�±������Ԫ��*/
	/*�ļ�*/
	pFunction[0] = SaveData;
	pFunction[1] = BackupData;
	pFunction[2] = RestoreData;
	pFunction[3] = ExitSys;
	/*����ά��*/
	pFunction[4] = AddData;
	pFunction[5] = DeleteData;
	pFunction[6] = ModifyData;
	/*���ݲ�ѯ*/
	pFunction[7] = StatCity;
	pFunction[8] = StatType;
	pFunction[9] = StatPrice;
	/*����ͳ��*/
	pFunction[10] = ShowAllEstate;
	pFunction[11] = ShowAllHouse;
	/*����*/
	pFunction[12] = HelpTopic;
	pFunction[13] = NULL;
	pFunction[14] = About;

	for (i = 1, loc = 0; i<m; i++)  /*�������˵��ź��Ӳ˵��ż����Ӧ�±�*/
	{
		loc += ga_sub_menu_count[i - 1];
	}
	loc += s - 1;

	if (pFunction[loc] != NULL)
	{
		bRet = (*pFunction[loc])();  /*�ú���ָ�������ָ��Ĺ��ܺ���*/
	}

	return bRet;
}

/**
*�������ƣ�SaveData
*�������ܣ���������
*�����������
*�����������
*����ֵ��BOOL���ͣ�ʼ�շ���TRUE
*����˵����
*/
BOOL SaveData(void)
{
	FILE *fp_estate, *fp_build, *fp_house;
	ESTATE_NODE * pestate;
	BUILD_NODE * pbuild;
	HOUSE_NODE * phouse;

	/*����¥����Ϣ*/
	if ((fp_estate = fopen(gp_estate_info_filename, "wb")) == NULL)
	{
		fputs("��¥�������ļ�����", stderr);
		exit(EXIT_FAILURE);
	}
	pestate = hd;
	while (pestate)
	{
		fwrite(pestate, sizeof(ESTATE_NODE), 1, fp_estate);
		pestate = pestate->next;
	}

	/*����¥����Ϣ*/
	if ((fp_build = fopen(gp_build_info_filename, "wb")) == NULL)
	{
		fputs("��¥�������ļ�����", stderr);
		exit(EXIT_FAILURE);
	}
	pestate = hd;
	while (pestate)
	{
		pbuild = pestate->bnext;
		while (pbuild)
		{
			fwrite(pbuild, sizeof(BUILD_NODE), 1, fp_build);
			pbuild = pbuild->next;
		}
		pestate = pestate->next;
	}

	/*���淿����Ϣ*/
	if ((fp_house = fopen(gp_house_info_filename, "wb")) == NULL)
	{
		fputs("�򿪷��������ļ�����", stderr);
		exit(EXIT_FAILURE);
	}
	pestate = hd;
	while (pestate)
	{
		pbuild = pestate->bnext;
		while (pbuild)
		{
			phouse = pbuild->hnext;
			while (phouse)
			{
				fwrite(phouse, sizeof(HOUSE_NODE), 1, fp_house);
				phouse = phouse->next;
			}
			pbuild = pbuild->next;
		}
		pestate = pestate->next;
	}

	fclose(fp_estate);
	fclose(fp_build);
	fclose(fp_house);
	printf("����ɹ���\n");
	printf("--------------------------------------------------------------------------------");
	printf("�����������...");
	getch();
	InitInterface();
	return TRUE;
}

/**
*�������ƣ�BackupData
*�������ܣ��������ݣ����������Ϊ���ļ�
*�����������
*�����������
*����ֵ��BOOL���ͣ�ʼ�շ���TRUE
*/
BOOL BackupData(void)
{
	int flag, deal1 = 1;
	FILE * newfp, *oldfp;//�����¾������ļ�ָ��
	char filename[255];
	ESTATE_NODE* pestate = (ESTATE_NODE*)malloc(sizeof(ESTATE_NODE));
	BUILD_NODE* pbuild = (BUILD_NODE*)malloc(sizeof(BUILD_NODE));
	HOUSE_NODE* phouse = (HOUSE_NODE*)malloc(sizeof(HOUSE_NODE));
	LABEL_BUNDLE labels;
	HOT_AREA areas;
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;

	printf("ѡ����Ҫ���ݵ���Ϣ�����\n");
	char *pCh[] = { "1������¥������","2������¥������", "3�����ݷ�������" };

	int iHot = 3;
	pos.X = strlen(pCh[0]) + 10;
	pos.Y = 12;
	rcPop.Left = (SCR_COL - pos.X) / 2;
	rcPop.Right = rcPop.Left + pos.X - 1;
	rcPop.Top = (25 - pos.Y) / 2;
	rcPop.Bottom = rcPop.Top + pos.Y - 1;

	att = BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
	labels.num = 3;
	labels.ppLabel = pCh;
	COORD aLoc[] = { { rcPop.Left + 3, rcPop.Top + 2 },
	{ rcPop.Left + 3, rcPop.Top + 5 },
	{ rcPop.Left + 3, rcPop.Top + 8 }
	};
	labels.pLoc = aLoc;

	areas.num = 3;
	SMALL_RECT aArea[] =
	{
		{
			rcPop.Left + 3, rcPop.Top + 2,
			rcPop.Left + 17, rcPop.Top + 2
		},
		{
			rcPop.Left + 3, rcPop.Top + 5,
			rcPop.Left + 17, rcPop.Top + 5
		},
		{
			rcPop.Left + 3, rcPop.Top + 8,
			rcPop.Left + 17, rcPop.Top + 8
		}
	};
	char aSort[] = { 0,0,0 };
	char aTag[] = { 1,2,3 };
	areas.pArea = aArea;
	areas.pSort = aSort;
	areas.pTag = aTag;
	PopUp(&rcPop, att, &labels, &areas);
	if (DealInput(&areas, &iHot) == 13 && iHot == 1)
	{
		/*��ȷ��ѯ*/
		PopOff();
		flag = 1;
	}
	else
	{
		if (iHot == 2)
		{
			PopOff();
			flag = 2;
		}
		else
		{
			PopOff();
			flag = 3;
		}
	}

	while (deal1)
	{
		printf("--------------------------------------------------------------------------------");
		printf("������Ҫ�洢��·�����ļ��������磺C:\\Users\\***\\Desktop\\**.dat\n");
		printf("�ļ�·��&�ļ����� ");
		scanf("%s", filename);
		while (getchar() != '\n');
		printf("--------------------------------------------------------------------------------");
		if ((newfp = fopen(filename, "wb")) == NULL)//�����ļ�
		{
			fputs("�ļ�·�����ļ�����Ч�����������룡", stderr);
		}
		else
		{
			switch (flag)
			{
			case 1:
			{
				if ((oldfp = fopen(gp_estate_info_filename, "rb")) == NULL)
				{
					fputs("��¥����Ϣ�ļ�����", stderr);
					exit(EXIT_FAILURE);
				}
				fread(pestate, sizeof(ESTATE_NODE), 1, oldfp);
				while (!feof(oldfp))
				{
					fwrite(pestate, sizeof(ESTATE_NODE), 1, newfp);
					fread(pestate, sizeof(ESTATE_NODE), 1, oldfp);
				}
				fclose(oldfp);
				fclose(newfp);
				break;
			}
			case 2:
			{
				if ((oldfp = fopen(gp_build_info_filename, "rb")) == NULL)
				{
					fputs("��¥����Ϣ�ļ�����", stderr);
					exit(EXIT_FAILURE);
				}
				fread(pbuild, sizeof(BUILD_NODE), 1, oldfp);
				while (!feof(oldfp))
				{
					fwrite(pbuild, sizeof(BUILD_NODE), 1, newfp);
					fread(pbuild, sizeof(BUILD_NODE), 1, oldfp);
				}
				fclose(oldfp);
				fclose(newfp);
				break;
			}
			case 3:
			{
				if ((oldfp = fopen(gp_house_info_filename, "rb")) == NULL)
				{
					fputs("�򿪷�����Ϣ�ļ�����", stderr);
					exit(EXIT_FAILURE);
				}
				fread(phouse, sizeof(HOUSE_NODE), 1, oldfp);
				while (!feof(oldfp))
				{
					fwrite(phouse, sizeof(HOUSE_NODE), 1, newfp);
					fread(phouse, sizeof(HOUSE_NODE), 1, oldfp);
				}
				fclose(oldfp);
				fclose(newfp);
				break;
			}
			}
			printf("���ݳɹ���\n");
			printf("�����������...");
			getch();
			InitInterface();
			return TRUE;
		}


		char *pCh[] = { "��������                          ����" };
		iHot = 1;

		pos.X = strlen(pCh[0]) + 6;
		pos.Y = 7;
		rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
		rcPop.Right = rcPop.Left + pos.X - 7;
		rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
		rcPop.Bottom = rcPop.Top + pos.Y - 8;
		att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
		labels.num = 1;
		labels.ppLabel = pCh;
		COORD aLoc[] = { { rcPop.Left, rcPop.Top },
		{ rcPop.Left + 5, rcPop.Top + 5 } };
		labels.pLoc = aLoc;

		areas.num = 2;
		SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
			rcPop.Left + 7, rcPop.Top },
			{ rcPop.Left + 34, rcPop.Top ,
			rcPop.Left + 37, rcPop.Top } };
		char aSort[] = { 0, 0 };
		char aTag[] = { 1, 2 };
		areas.pArea = aArea;
		areas.pSort = aSort;
		areas.pTag = aTag;
		PopUp(&rcPop, att, &labels, &areas);

		pos.X = rcPop.Left + 1;
		pos.Y = rcPop.Top + 4;

		if (DealInput(&areas, &iHot) == 13 && iHot == 1)
		{
			deal1 = 1;
		}
		else
		{
			deal1 = 0;
		}
		PopOff();
		InitInterface();
	}
	return TRUE;
}

/**
*�������ƣ�RestoreData
*�������ܣ������ݵ��������¼��أ��ָ�����
*�����������
*�����������
*����ֵ��BOOL���ͣ�ʼ�շ���TRUE
*/
BOOL RestoreData(void)
{
	int flag, deal1 = 1;
	FILE * newfp, *oldfp;//�����¾������ļ�ָ��
	char filename[255];
	ESTATE_NODE* pestate = (ESTATE_NODE*)malloc(sizeof(ESTATE_NODE));
	BUILD_NODE* pbuild = (BUILD_NODE*)malloc(sizeof(BUILD_NODE));
	HOUSE_NODE* phouse = (HOUSE_NODE*)malloc(sizeof(HOUSE_NODE));
	LABEL_BUNDLE labels;
	HOT_AREA areas;
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;

	printf("ѡ����Ҫ��ԭ����Ϣ�����\n");
	char *pCh[] = { "1����ԭ¥������","2����ԭ¥������", "3����ԭ��������" };

	int iHot = 3;
	pos.X = strlen(pCh[0]) + 10;
	pos.Y = 12;
	rcPop.Left = (SCR_COL - pos.X) / 2;
	rcPop.Right = rcPop.Left + pos.X - 1;
	rcPop.Top = (25 - pos.Y) / 2;
	rcPop.Bottom = rcPop.Top + pos.Y - 1;

	att = BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
	labels.num = 3;
	labels.ppLabel = pCh;
	COORD aLoc[] = { { rcPop.Left + 3, rcPop.Top + 2 },
	{ rcPop.Left + 3, rcPop.Top + 5 },
	{ rcPop.Left + 3, rcPop.Top + 8 }
	};
	labels.pLoc = aLoc;

	areas.num = 3;
	SMALL_RECT aArea[] =
	{
		{
			rcPop.Left + 3, rcPop.Top + 2,
			rcPop.Left + 17, rcPop.Top + 2
		},
		{
			rcPop.Left + 3, rcPop.Top + 5,
			rcPop.Left + 17, rcPop.Top + 5
		},
		{
			rcPop.Left + 3, rcPop.Top + 8,
			rcPop.Left + 17, rcPop.Top + 8
		}
	};
	char aSort[] = { 0,0,0 };
	char aTag[] = { 1,2,3 };
	areas.pArea = aArea;
	areas.pSort = aSort;
	areas.pTag = aTag;
	PopUp(&rcPop, att, &labels, &areas);
	if (DealInput(&areas, &iHot) == 13 && iHot == 1)
	{
		/*��ȷ��ѯ*/
		PopOff();
		flag = 1;
	}
	else
	{
		if (iHot == 2)
		{
			PopOff();
			flag = 2;
		}
		else
		{
			PopOff();
			flag = 3;
		}
	}

	while (deal1)
	{
		printf("--------------------------------------------------------------------------------");
		printf("������Ҫ��ԭ��·�����ļ��������磺C:\\Users\\***\\Desktop\\**.dat\n");
		printf("�ļ�·��&�ļ����� ");
		scanf("%s", filename);
		while (getchar() != '\n');
		printf("--------------------------------------------------------------------------------");
		if ((newfp = fopen(filename, "rb")) == NULL)//�����ļ�
		{
			fputs("δ�ҵ����ļ�����ȷ���ļ�·�����ļ������������룡", stderr);
		}
		else
		{
			switch (flag)
			{
			case 1:
			{
				if ((oldfp = fopen(gp_estate_info_filename, "wb")) == NULL)
				{
					fputs("��¥����Ϣ�ļ�����", stderr);
					exit(EXIT_FAILURE);
				}
				fread(pestate, sizeof(ESTATE_NODE), 1, newfp);
				while (!feof(newfp))
				{
					fwrite(pestate, sizeof(ESTATE_NODE), 1, oldfp);
					fread(pestate, sizeof(ESTATE_NODE), 1, newfp);
				}
				fclose(oldfp);
				fclose(newfp);
				break;
			}
			case 2:
			{
				if ((oldfp = fopen(gp_build_info_filename, "wb")) == NULL)
				{
					fputs("��¥����Ϣ�ļ�����", stderr);
					exit(EXIT_FAILURE);
				}
				fread(pbuild, sizeof(BUILD_NODE), 1, newfp);
				while (!feof(newfp))
				{
					fwrite(pbuild, sizeof(BUILD_NODE), 1, oldfp);
					fread(pbuild, sizeof(BUILD_NODE), 1, newfp);
				}
				fclose(oldfp);
				fclose(newfp);
				break;
			}
			case 3:
			{
				if ((oldfp = fopen(gp_house_info_filename, "wb")) == NULL)
				{
					fputs("�򿪷�����Ϣ�ļ�����", stderr);
					exit(EXIT_FAILURE);
				}
				fread(phouse, sizeof(HOUSE_NODE), 1, newfp);
				while (!feof(oldfp))
				{
					fwrite(phouse, sizeof(HOUSE_NODE), 1, oldfp);
					fread(phouse, sizeof(HOUSE_NODE), 1, newfp);
				}
				fclose(oldfp);
				fclose(newfp);
				break;
			}
			}
			printf("��ԭ�ɹ���\n");
			printf("�����������...");
			getch();
			InitInterface();
			return TRUE;
		}


		char *pCh[] = { "��������                          ����" };
		iHot = 1;

		pos.X = strlen(pCh[0]) + 6;
		pos.Y = 7;
		rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
		rcPop.Right = rcPop.Left + pos.X - 7;
		rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
		rcPop.Bottom = rcPop.Top + pos.Y - 8;
		att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
		labels.num = 1;
		labels.ppLabel = pCh;
		COORD aLoc[] = { { rcPop.Left, rcPop.Top },
		{ rcPop.Left + 5, rcPop.Top + 5 } };
		labels.pLoc = aLoc;

		areas.num = 2;
		SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
			rcPop.Left + 7, rcPop.Top },
			{ rcPop.Left + 34, rcPop.Top ,
			rcPop.Left + 37, rcPop.Top } };
		char aSort[] = { 0, 0 };
		char aTag[] = { 1, 2 };
		areas.pArea = aArea;
		areas.pSort = aSort;
		areas.pTag = aTag;
		PopUp(&rcPop, att, &labels, &areas);

		pos.X = rcPop.Left + 1;
		pos.Y = rcPop.Top + 4;

		if (DealInput(&areas, &iHot) == 13 && iHot == 1)
		{
			deal1 = 1;
		}
		else
		{
			deal1 = 0;
		}
		PopOff();
		InitInterface();
	}
	return TRUE;
}

/**
*�������ƣ�ExitSys
*�������ܣ��˳�ϵͳ
*�����������
*�����������
*����ֵ��BOOL���ͣ������û�ѡ�񷵻�TRUE��FALSE
*/
BOOL ExitSys(void)
{
	LABEL_BUNDLE labels;
	HOT_AREA areas;
	BOOL bRet = TRUE;
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;
	char *pCh[] = { "ȷ���˳�ϵͳ��", "ȷ��    ȡ��" };
	int iHot = 1;

	pos.X = strlen(pCh[0]) + 6;
	pos.Y = 7;
	rcPop.Left = (SCR_COL - pos.X) / 2;
	rcPop.Right = rcPop.Left + pos.X - 1;
	rcPop.Top = (SCR_ROW - pos.Y) / 2;
	rcPop.Bottom = rcPop.Top + pos.Y - 1;

	att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
	labels.num = 2;
	labels.ppLabel = pCh;
	COORD aLoc[] = { { rcPop.Left + 3, rcPop.Top + 2 },
	{ rcPop.Left + 5, rcPop.Top + 5 } };
	labels.pLoc = aLoc;

	areas.num = 2;
	SMALL_RECT aArea[] = { { rcPop.Left + 5, rcPop.Top + 5,
		rcPop.Left + 8, rcPop.Top + 5 },
		{ rcPop.Left + 13, rcPop.Top + 5,
		rcPop.Left + 16, rcPop.Top + 5 } };
	char aSort[] = { 0, 0 };
	char aTag[] = { 1, 2 };
	areas.pArea = aArea;
	areas.pSort = aSort;
	areas.pTag = aTag;
	PopUp(&rcPop, att, &labels, &areas);

	pos.X = rcPop.Left + 1;
	pos.Y = rcPop.Top + 4;
	FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right - rcPop.Left - 1, pos, &rec);

	if (DealInput(&areas, &iHot) == 13 && iHot == 1)
	{
		bRet = FALSE;
	}
	else
	{
		bRet = TRUE;
	}
	PopOff();

	return bRet;
}


/**
*�������ƣ�Creatlist
*�������ܣ����ļ��ж�ȡ�������ݣ�����ŵ���������ʮ��������
*�������������ͷָ���ַphead
*����ֵ��int�����ݣ�0��ʾ������1��ʾ����¥����Ϣ��2��ʾ����¥�̺�¥����Ϣ��3��ʾ����¥�̣�¥���ͷ�����Ϣ
*/
int CreatList(ESTATE_NODE**phead)
{
	ESTATE_NODE*hd = NULL, *pEstateNode;
	BUILD_NODE*pBuildNode;
	HOUSE_NODE*pHouseNode;
	FILE*pFile;
	int find;
	int num = 0;
	if ((pFile = fopen(gp_estate_info_filename, "rb")) == NULL)
	{
		printf("¥����Ϣ�����ļ���ʧ��!\n");
		return num;
	}
	printf("¥����Ϣ�����ļ��򿪳ɹ�!\n");

	/*�������ļ��ж�ȡ¥����Ϣ���ݣ������Ժ���ȳ���ʽ������������*/
	pEstateNode = (ESTATE_NODE*)malloc(sizeof(ESTATE_NODE));
	fread(pEstateNode, sizeof(ESTATE_NODE), 1, pFile);
	while (!feof(pFile))
	{
		pEstateNode->bnext = NULL;
		pEstateNode->next = hd;
		hd = pEstateNode;
		pEstateNode = (ESTATE_NODE*)malloc(sizeof(ESTATE_NODE));
		fread(pEstateNode, sizeof(ESTATE_NODE), 1, pFile);
	}
	free(pEstateNode);
	fclose(pFile);
	if (hd == NULL)
	{
		printf("¥����Ϣ�����ļ�����ʧ��!\n");
		return num;
	}
	printf("¥����Ϣ�����ļ����سɹ�!\n");
	*phead = hd;
	num++;
	if ((pFile = fopen(gp_build_info_filename, "rb")) == NULL)
	{
		printf("¥����Ϣ�����ļ���ʧ��!\n");
		return num;
	}
	printf("¥����Ϣ�����ļ��򿪳ɹ�!\n");
	num++;

	/*�������ļ��ж�ȡ¥����Ϣ���ݴ���������Ӧ����ѧ��������Ϣ֧����*/
	pBuildNode = (BUILD_NODE*)malloc(sizeof(BUILD_NODE));
	fread(pBuildNode, sizeof(BUILD_NODE), 1, pFile);
	while (!feof(pFile))
	{
		pBuildNode->hnext = NULL;

		/*�������ϲ���¥����Ӧ��¥���������*/
		pEstateNode = hd;
		while (pEstateNode != NULL&&strcmp(pEstateNode->estate_id, pBuildNode->estate_id) != 0)
		{
			pEstateNode = pEstateNode->next;
		}

		/*����ҵ����򽫽���Ժ���ȳ���ʽ����¥����Ϣ֧��*/
		if (pEstateNode != NULL)
		{
			pBuildNode->next = pEstateNode->bnext;
			pEstateNode->bnext = pBuildNode;
		}
		else  /*���δ�ҵ������ͷ������������ڴ�ռ�*/
		{
			free(pBuildNode);
		}
		pBuildNode = (BUILD_NODE*)malloc(sizeof(BUILD_NODE));
		fread(pBuildNode, sizeof(BUILD_NODE), 1, pFile);
	}
	free(pBuildNode);
	fclose(pFile);
	if ((pFile = fopen(gp_house_info_filename, "rb")) == NULL)
	{
		printf("������Ϣ�����ļ���ʧ��!\n");
		return num;
	}
	printf("������Ϣ�����ļ��򿪳ɹ�!\n");
	num++;
	/*�������ļ��ж�ȡ������Ϣ���ݴ���¥����Ϣ��Ӧ���ķ�����Ϣ֧����*/
	pHouseNode = (HOUSE_NODE*)malloc(sizeof(HOUSE_NODE));
	fread(pHouseNode, sizeof(HOUSE_NODE), 1, pFile);
	while (!feof(pFile))
	{
		/*��¥��֧���ϲ��Ҹ÷�������¥����Ӧ�Ľ��*/
		pEstateNode = hd;
		find = 0;
		while (pEstateNode != NULL&&find == 0)
		{
			if (strcmp(pEstateNode->estate_id, pHouseNode->estate_id) == 0)
			{
				pBuildNode = pEstateNode->bnext;
				while (pBuildNode != NULL&&find == 0)
				{
					if (strcmp(pBuildNode->build_id, pHouseNode->build_id) == 0)
					{
						find = 1;
						break;
					}
					pBuildNode = pBuildNode->next;
				}
			}
			pEstateNode = pEstateNode->next;
		}
		if (find)  /*����ҵ��򽫽���Ժ���ȳ���ʽ���뷿����Ϣ֧����*/
		{
			pHouseNode->next = pBuildNode->hnext;
			pBuildNode->hnext = pHouseNode;
		}
		else    /*���δ�ҵ������ͷ������������ڴ�ռ�*/
		{
			free(pHouseNode);
		}
		pHouseNode = (HOUSE_NODE*)malloc(sizeof(HOUSE_NODE));
		fread(pHouseNode, sizeof(HOUSE_NODE), 1, pFile);
	}
	free(pHouseNode);
	fclose(pFile);
	return num;
}



/**
*�������ƣ�SeekEstateNode
*�������ܣ�����¥�̱�Ų�ѯ��Ӧ���
*�������������ͷָ��head,¥�̱��

*����˵����
*����ֵ����Ӧ��¥�̽�㣬δ�ҵ����ؿ�ָ��
*/
ESTATE_NODE* SeekEstateNode(ESTATE_NODE*head, char* estateid)
{
	ESTATE_NODE* pestate;
	pestate = head;
	while (pestate != NULL)
	{
		if (strcmp(pestate->estate_id, estateid) == 0)
		{
			return pestate;
		}
		pestate = pestate->next;
	}
	return NULL;
}


/**
*�������ƣ�SeekBuildNode
*�������ܣ�����¥�̱��,¥����Ų�ѯ��Ӧ���
*�������������ͷָ��head��¥�̱�ţ�¥�����
*�����������
*����ֵ����Ӧ��¥����㣬δ�ҵ����ؿ�ָ��
*/
BUILD_NODE* SeekBuildNode(ESTATE_NODE*head, char* estateid, char* buildid)
{
	BUILD_NODE* pbuild;
	ESTATE_NODE* pestate = SeekEstateNode(head, estateid);
	if (pestate == NULL)
	{
		return NULL;
	}
	pbuild = pestate->bnext;
	while (pbuild != NULL)
	{
		if (strcmp(pbuild->build_id, buildid) == 0)
		{
			return pbuild;
		}
		pbuild = pbuild->next;
	}
	return NULL;
}



/**
*�������ƣ�SeekHouseNode
*�������ܣ�����¥�̱��,¥����ţ����ݱ�Ų�ѯ��Ӧ���
*�������������ͷָ��head��¥�̱�ţ�¥����ţ����ݱ��
*�����������
*����ֵ����Ӧ�ķ��ݽ�㣬δ�ҵ����ؿ�ָ��
*/
HOUSE_NODE* SeekHouseNode(ESTATE_NODE*head, char* estateid, char* buildid, char* houseid)
{
	HOUSE_NODE* phouse;
	BUILD_NODE* pbuild = SeekBuildNode(head, estateid, buildid);
	if (pbuild == NULL)
	{
		return NULL;
	}
	phouse = pbuild->hnext;
	while (phouse != NULL)
	{
		if (strcmp(phouse->house_id, houseid) == 0)
		{
			return phouse;
		}
		phouse = phouse->next;
	}
	return NULL;
}




/**
*�������ƣ�DelHouseNode
*�������ܣ���ʮ��������ɾ��ָ���ķ�����Ϣ���
*���������hd����ͷָ�룬¥�̱�ţ�¥����ţ����ݱ��
*�����������
*����ֵ��BOOL�����ݣ�TRUE��ʾɾ���ɹ���FALSE��ʾɾ��ʧ��
*����˵����
*/
BOOL DelHouseNode(ESTATE_NODE*head, char* estateid, char* buildid, char* houseid)
{
	BUILD_NODE* pbuild;
	HOUSE_NODE* p, *pbefore;
	pbuild = SeekBuildNode(head, estateid, buildid);//��λ����Ӧ¥�����
	if (!pbuild)
		return FALSE;
	else
	{
		p = pbefore = pbuild->hnext;
		while (p != NULL && strcmp(p->house_id, houseid))
		{
			pbefore = p;
			p = p->next;
		}
		if (!p)
			return FALSE;
		//�ҵ���Ϊp����λ
		if (p == pbuild->hnext)  //�����ɾ�����ͷָ��
		{
			pbuild->hnext = p->next;
		}
		else
		{
			pbefore->next = p->next;
		}
		free(p);
		return TRUE;
	}
}


/**
*�������ƣ�DelBuildNode
*�������ܣ���ʮ��������ɾ��ָ����¥����Ϣ���
*�������������ͷָ�룬¥�̱�ţ�¥�����
*�����������
*����˵����
*����ֵ��BOOL�����ݣ�TRUE��ʾɾ���ɹ���FALSE��ʾɾ��ʧ��
*/
BOOL DelBuildNode(ESTATE_NODE*head, char* estateid, char* buildid)
{
	ESTATE_NODE* pestate;
	BUILD_NODE* p, *pbefore;
	pestate = SeekEstateNode(head, estateid);//��λ����Ӧ¥�̽��
	if (!pestate)
		return FALSE;
	else
	{
		p = pbefore = pestate->bnext;
		while (p != NULL && strcmp(p->build_id, buildid))
		{
			pbefore = p;
			p = p->next;
		}
		if (!p)
			return FALSE;
		//�ҵ���Ϊp����λ
		if (p == pestate->bnext)  //�����ɾ�����ͷָ��
		{
			pestate->bnext = p->next;
		}
		else
		{
			pbefore->next = p->next;
		}
		HOUSE_NODE* phouse = p->hnext;
		while (phouse)
		{
			HOUSE_NODE* temp = phouse;
			phouse = phouse->next;
			free(temp);
		}
		free(p);
		return TRUE;
	}
}

/**
*�������ƣ�DelEstatelNode
*�������ܣ���ʮ��������ɾ��ָ����¥����Ϣ���
*���������ָ������ͷָ���ָ�룬¥�̱��
*����˵����
*����ֵ��BOOL�����ݣ�TRUE��ʾɾ���ɹ���FALSE��ʾɾ��ʧ��
*/
BOOL DelEstateNode(ESTATE_NODE** phead, char* estateid)
{
	ESTATE_NODE* pbefore = *phead;
	ESTATE_NODE* p = *phead;
	while (p != NULL && strcmp(p->estate_id, estateid))
	{
		pbefore = p;
		p = p->next;
	}
	if (!p)
		return FALSE;
	//�ҵ���Ϊp����λ
	if (p == *phead)  //�����ɾ�����ͷָ��
	{
		*phead = p->next;
	}
	else
	{
		pbefore->next = p->next;
	}
	BUILD_NODE* pbuild = p->bnext;
	while (pbuild)
	{
		HOUSE_NODE* phouse = pbuild->hnext;
		while (phouse)
		{
			HOUSE_NODE *temp = phouse;
			phouse = phouse->next;
			free(temp);
		}
		BUILD_NODE* temp = pbuild;
		pbuild = pbuild->next;
		free(temp);
	}
	free(p);
	return TRUE;
}

/**
* �������ƣ�AddData
* �������ܣ����ڴ������������µ�������
* �����������
* �����������
* ����ֵ����
* ����˵����
*/

BOOL AddData(void)
{
	Administrator();
	if (pass == 0)
	{
		int deal1 = 1;
		int deal2;
		ESTATE_NODE* estate;
		ESTATE_NODE* newestate;
		BUILD_NODE* newbuild;
		HOUSE_NODE* newhouse;
		LABEL_BUNDLE labels;
		HOT_AREA areas;
		SMALL_RECT rcPop;
		COORD pos;
		WORD att;
		char *pCh[] = { "1�����¥������","2�����¥������", "3����ӷ�������" };
		int iHot = 3;
		int find;

		pos.X = strlen(pCh[0]) + 10;
		pos.Y = 12;
		rcPop.Left = (SCR_COL - pos.X) / 2;
		rcPop.Right = rcPop.Left + pos.X - 1;
		rcPop.Top = (25 - pos.Y) / 2;
		rcPop.Bottom = rcPop.Top + pos.Y - 1;

		att = BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
		labels.num = 3;
		labels.ppLabel = pCh;
		COORD aLoc[] = { { rcPop.Left + 3, rcPop.Top + 2 },
		{ rcPop.Left + 3, rcPop.Top + 5 },
		{ rcPop.Left + 3, rcPop.Top + 8 }
		};
		labels.pLoc = aLoc;

		areas.num = 3;
		SMALL_RECT aArea[] =
		{
			{
				rcPop.Left + 3, rcPop.Top + 2,
				rcPop.Left + 17, rcPop.Top + 2
			},
			{
				rcPop.Left + 3, rcPop.Top + 5,
				rcPop.Left + 17, rcPop.Top + 5
			},
			{
				rcPop.Left + 3, rcPop.Top + 8,
				rcPop.Left + 17, rcPop.Top + 8
			}
		};
		char aSort[] = { 0,0,0 };
		char aTag[] = { 1,2,3 };
		areas.pArea = aArea;
		areas.pSort = aSort;
		areas.pTag = aTag;
		PopUp(&rcPop, att, &labels, &areas);
		if (DealInput(&areas, &iHot) == 13 && iHot == 1)
		{
			/*��ȷ��ѯ*/
			PopOff();
			deal2 = 1;
		}
		else
		{
			if (iHot == 2)
			{
				PopOff();
				deal2 = 2;
			}
			else
			{
				PopOff();
				deal2 = 3;
			}
		}

		while (deal1 != 0)
		{
			switch (deal2) {
			case 1:/*���¥������*/
			{
				newestate = (ESTATE_NODE*)malloc(sizeof(ESTATE_NODE));
				printf("--------------------------------------------------------------------------------");
				find = 1;
				while (find)
				{
					printf("\t����¥�̱�ţ�������9λ����\t");
					scanf("%9s", newestate->estate_id);
					while (getchar() != '\n');		/*������볬�����ƣ�ͨ�������ˢ�����뻺����*/
					estate = hd;
					while (estate != NULL&&strcmp(estate->estate_id, newestate->estate_id) != 0)
						estate = estate->next;
					if (estate != NULL)
					{
						find = 1;
						printf("\t�Բ����������¥�̱���Ѵ��ڣ�����������!\n");
					}
					else
						find = 0;
					printf("--------------------------------------------------------------------------------");
				}
				printf("\t����¥������\t\t\t");
				scanf("%19s", newestate->name);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t�������\t\t\t");
				scanf("%9s", newestate->city);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t����¥�̵�ַ\t\t\t");
				scanf("%29s", newestate->address);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t���뿪����\t\t\t");
				scanf("%19s", newestate->developer);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t������ҵ��˾\t\t\t");
				scanf("%19s", newestate->management_company);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				newestate->bnext = NULL;
				newestate->next = hd;
				hd = newestate;
				printf("\t\t\t\t\t\t\t����ɹ�");
				break;
			}
			case 2:/*���¥������*/
			{
				newbuild = (BUILD_NODE*)malloc(sizeof(BUILD_NODE));
				find = 1;
				printf("--------------------------------------------------------------------------------");
				printf("\t\t�����Ӧ¥�̱��\t");
				scanf("%9s", newbuild->estate_id);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t����¥�����\t\t");
				scanf("%9s", newbuild->build_id);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t���뵥Ԫ��\t\t");
				scanf("%d", &newbuild->unit);
				printf("--------------------------------------------------------------------------------");
				printf("\t\t����¥��\t\t");
				scanf("%d", &newbuild->floor);
				printf("--------------------------------------------------------------------------------");
				newbuild->hnext = NULL;
				newbuild->next = NULL;
				ESTATE_NODE *pestate = SeekEstateNode(hd, newbuild->estate_id);
				if (pestate == NULL)
				{
					free(newbuild);
					printf("\t\t\t�������󣬸�¥������Ӧ��¥�̲����ڣ�����ʧ��\n");
				}
				else
				{
					newbuild->next = pestate->bnext;
					pestate->bnext = newbuild;
					printf("\t\t\t\t\t\t\t����ɹ�\n");
				}
				break;
			}
			case 3:/*��ӷ�������*/
			{
				newhouse = (HOUSE_NODE*)malloc(sizeof(HOUSE_NODE));
				printf("--------------------------------------------------------------------------------");
				printf("\t\t����¥�̱��\t\t");
				scanf("%9s", newhouse->estate_id);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t����¥�����\t\t");
				scanf("%9s", newhouse->build_id);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t���뷿�ݱ��\t\t");
				scanf("%9s", newhouse->house_id);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t���뻧��\t\t");
				scanf("%19s", newhouse->type);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t�������(m*m)\t\t");
				scanf("%d", &newhouse->area);
				printf("--------------------------------------------------------------------------------");
				printf("\t\t���빫̯��\t\t");
				scanf("%f", &newhouse->shared_rate);
				printf("--------------------------------------------------------------------------------");
				printf("\t\t���뵥λ����۸�Ԫ/(m*m)��\t");
				scanf("%d", &newhouse->one_price);
				printf("--------------------------------------------------------------------------------");
				newhouse->next = NULL;
				BUILD_NODE* pbuild = SeekBuildNode(hd, newhouse->estate_id, newhouse->build_id);
				if (pbuild == NULL)
				{
					free(newhouse);
					printf("\t\t\t�������󣬸÷�������Ӧ��¥�������ڣ�����ʧ��\n");
				}
				else
				{
					newhouse->next = pbuild->hnext;
					pbuild->hnext = newhouse;
					printf("\t\t\t\t\t\t����ɹ�\n");
				}
				break;
			}
			default:
			{
				printf("--------------------------------------------------------------------------------");
				printf("\t\t\t\t���빦�ܱ������\n");
			}
			}
			LABEL_BUNDLE labels;
			HOT_AREA areas;

			SMALL_RECT rcPop;
			COORD pos;
			WORD att;
			char *pCh[] = { "��������                          ����" };
			int iHot = 1;

			pos.X = strlen(pCh[0]) + 6;
			pos.Y = 7;
			rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
			rcPop.Right = rcPop.Left + pos.X - 7;
			rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
			rcPop.Bottom = rcPop.Top + pos.Y - 8;
			att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
			labels.num = 1;
			labels.ppLabel = pCh;
			COORD aLoc[] = { { rcPop.Left, rcPop.Top },
			{ rcPop.Left + 5, rcPop.Top + 5 } };
			labels.pLoc = aLoc;

			areas.num = 2;
			SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
				rcPop.Left + 7, rcPop.Top },
				{ rcPop.Left + 34, rcPop.Top ,
				rcPop.Left + 37, rcPop.Top } };
			char aSort[] = { 0, 0 };
			char aTag[] = { 1, 2 };
			areas.pArea = aArea;
			areas.pSort = aSort;
			areas.pTag = aTag;
			PopUp(&rcPop, att, &labels, &areas);

			pos.X = rcPop.Left + 1;
			pos.Y = rcPop.Top + 4;

			if (DealInput(&areas, &iHot) == 13 && iHot == 1)
			{
				deal1 = 1;
			}
			else
			{
				deal1 = 0;
			}
			PopOff();
			InitInterface();
		}
	}
	return TRUE;
}


/**
* �������ƣ�DeletData
* �������ܣ�ɾ��¥�̡�¥�����ݽ������
* �����������
* �����������
* ����ֵ��BOOL���ͣ�ʼ�շ���TRUE
* ����˵����
*/
BOOL DeleteData(void)
{
	Administrator();
	if (pass == 0)
	{
		int deal3 = 1;
		int deal2;
		char estateid[10];
		char buildid[10];
		char houseid[10];
		LABEL_BUNDLE labels;
		HOT_AREA areas;
		SMALL_RECT rcPop;
		COORD pos;
		WORD att;
		char *pCh[] = { "1��ɾ��¥������","2��ɾ��¥������", "3��ɾ����������" };
		int iHot = 3;

		pos.X = strlen(pCh[0]) + 10;
		pos.Y = 12;
		rcPop.Left = (SCR_COL - pos.X) / 2;
		rcPop.Right = rcPop.Left + pos.X - 1;
		rcPop.Top = (25 - pos.Y) / 2;
		rcPop.Bottom = rcPop.Top + pos.Y - 1;

		att = BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
		labels.num = 3;
		labels.ppLabel = pCh;
		COORD aLoc[] = { { rcPop.Left + 3, rcPop.Top + 2 },
		{ rcPop.Left + 3, rcPop.Top + 5 },
		{ rcPop.Left + 3, rcPop.Top + 8 }
		};
		labels.pLoc = aLoc;

		areas.num = 3;
		SMALL_RECT aArea[] =
		{
			{
				rcPop.Left + 3, rcPop.Top + 2,
				rcPop.Left + 17, rcPop.Top + 2
			},
			{
				rcPop.Left + 3, rcPop.Top + 5,
				rcPop.Left + 17, rcPop.Top + 5
			},
			{
				rcPop.Left + 3, rcPop.Top + 8,
				rcPop.Left + 17, rcPop.Top + 8
			}
		};
		char aSort[] = { 0,0,0 };
		char aTag[] = { 1,2,3 };
		areas.pArea = aArea;
		areas.pSort = aSort;
		areas.pTag = aTag;
		PopUp(&rcPop, att, &labels, &areas);
		if (DealInput(&areas, &iHot) == 13 && iHot == 1)
		{
			/*��ȷ��ѯ*/
			PopOff();
			deal2 = 1;
		}
		else
		{
			if (iHot == 2)
			{
				PopOff();
				deal2 = 2;
			}
			else
			{
				PopOff();
				deal2 = 3;
			}
		}

		while (deal3 != 0)
		{
			switch (deal2) {
			case 1:/*ɾ��¥������*/
			{
				printf("--------------------------------------------------------------------------------");
				printf("\t\t��������Ҫɾ����¥�̱��\t\t");
				scanf("%9s", estateid);
				while (getchar() != '\n');
				if (DelEstateNode(&hd, estateid))
				{
					printf("--------------------------------------------------------------------------------");
					printf("\t\t\t\t\t��ɾ����Ӧ¥��\n");
				}
				else
				{
					printf("--------------------------------------------------------------------------------");
					printf("\t\t\t\t\tδ�ҵ���Ӧ��¥��\n");
				}
				break;
			}
			case 2:/*ɾ��¥������*/
			{
				printf("--------------------------------------------------------------------------------");
				printf("\t\t����¥�̱��\t\t");
				scanf("%9s", estateid);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t����¥�����\t\t");
				scanf("%9s", buildid);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				if (DelBuildNode(hd, estateid, buildid))
				{
					printf("\t\t\t\t\t��ɾ����Ӧ¥��\n");
				}
				else
				{
					printf("\t\t\t\t\tδ�ҵ���Ӧ��¥��\n");
				}
				break;
			}
			case 3:/*ɾ����������*/
			{
				printf("--------------------------------------------------------------------------------");
				printf("\t\t����¥�̱��\t\t");
				scanf("%9s", estateid);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t����¥�����\t\t");
				scanf("%9s", buildid);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t���뷿�ݱ��\t\t");
				scanf("%9s", houseid);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				if (DelHouseNode(hd, estateid, buildid, houseid))
					printf("\t\t\t\t\t��ɾ����Ӧ����\n");
				else
					printf("\t\t\t\t\tδ�ҵ���Ӧ�ķ���\n");
				break;
			}
			default:
			{
				printf("--------------------------------------------------------------------------------");
				printf("\t\t\t\t���빦�ܱ������\n");
			}
			}
			LABEL_BUNDLE labels;
			HOT_AREA areas;

			SMALL_RECT rcPop;
			COORD pos;
			WORD att;
			char *pCh[] = { "����ɾ��                          ����" };
			int iHot = 1;

			pos.X = strlen(pCh[0]) + 6;
			pos.Y = 7;
			rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
			rcPop.Right = rcPop.Left + pos.X - 7;
			rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
			rcPop.Bottom = rcPop.Top + pos.Y - 8;
			att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
			labels.num = 1;
			labels.ppLabel = pCh;
			COORD aLoc[] = { { rcPop.Left, rcPop.Top },
			{ rcPop.Left + 5, rcPop.Top + 5 } };
			labels.pLoc = aLoc;

			areas.num = 2;
			SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
				rcPop.Left + 7, rcPop.Top },
				{ rcPop.Left + 34, rcPop.Top ,
				rcPop.Left + 37, rcPop.Top } };
			char aSort[] = { 0, 0 };
			char aTag[] = { 1, 2 };
			areas.pArea = aArea;
			areas.pSort = aSort;
			areas.pTag = aTag;
			PopUp(&rcPop, att, &labels, &areas);

			pos.X = rcPop.Left + 1;
			pos.Y = rcPop.Top + 4;

			if (DealInput(&areas, &iHot) == 13 && iHot == 1)
			{
				deal3 = 1;
			}
			else
			{
				deal3 = 0;
			}
			PopOff();
			InitInterface();
		}
	}
	return TRUE;
}

/**
*�������ƣ�ModifyData
*�������ܣ��޸�¥�̡�¥������������
*�����������
*�����������
*����˵����
*����ֵ��BOOL���ͣ�ʼ�շ���TRUE
*/
BOOL ModifyData(void)
{
	Administrator();
	if (pass == 0)
	{
		int deal2;
		ESTATE_NODE* newestate;
		BUILD_NODE* newbuild;
		HOUSE_NODE* newhouse;
		char estateid[10];
		char buildid[10];
		char houseid[10];
		int deal3 = 1;
		LABEL_BUNDLE labels;
		HOT_AREA areas;
		SMALL_RECT rcPop;
		COORD pos;
		WORD att;
		char *pCh[] = { "1���޸�¥������","2���޸�¥������", "3���޸ķ�������" };
		int iHot = 3;

		pos.X = strlen(pCh[0]) + 10;
		pos.Y = 12;
		rcPop.Left = (SCR_COL - pos.X) / 2;
		rcPop.Right = rcPop.Left + pos.X - 1;
		rcPop.Top = (25 - pos.Y) / 2;
		rcPop.Bottom = rcPop.Top + pos.Y - 1;

		att = BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
		labels.num = 3;
		labels.ppLabel = pCh;
		COORD aLoc[] = { { rcPop.Left + 3, rcPop.Top + 2 },
		{ rcPop.Left + 3, rcPop.Top + 5 },
		{ rcPop.Left + 3, rcPop.Top + 8 }
		};
		labels.pLoc = aLoc;

		areas.num = 3;
		SMALL_RECT aArea[] =
		{
			{
				rcPop.Left + 3, rcPop.Top + 2,
				rcPop.Left + 17, rcPop.Top + 2
			},
			{
				rcPop.Left + 3, rcPop.Top + 5,
				rcPop.Left + 17, rcPop.Top + 5
			},
			{
				rcPop.Left + 3, rcPop.Top + 8,
				rcPop.Left + 17, rcPop.Top + 8
			}
		};
		char aSort[] = { 0,0,0 };
		char aTag[] = { 1,2,3 };
		areas.pArea = aArea;
		areas.pSort = aSort;
		areas.pTag = aTag;
		PopUp(&rcPop, att, &labels, &areas);
		if (DealInput(&areas, &iHot) == 13 && iHot == 1)
		{
			/*��ȷ��ѯ*/
			PopOff();
			deal2 = 1;
		}
		else
		{
			if (iHot == 2)
			{
				PopOff();
				deal2 = 2;
			}
			else
			{
				PopOff();
				deal2 = 3;
			}
		}
		while (deal3 != 0)
		{
			switch (deal2) {
			case 1:/*�޸�¥������*/
			{
				printf("--------------------------------------------------------------------------------");
				printf("\t\t����¥�̱��\t\t");
				scanf("%9s", estateid);
				while (getchar() != '\n');
				printf("\n");
				printf("--------------------------------------------------------------------------------");
				newestate = SeekEstateNode(hd, estateid);/*���Ҷ�Ӧ¥��*/
				if (newestate == NULL)
					printf("δ�ҵ���Ӧ������\n");
				else
					ModifyEstate(newestate);
				break;
			}
			case 2:/*�޸�¥������*/
			{
				printf("--------------------------------------------------------------------------------");
				printf("\t\t����¥�̱��\t\t");
				scanf("%9s", estateid);
				while (getchar() != '\n');
				printf("\n");
				printf("--------------------------------------------------------------------------------");
				printf("\t\t����¥�����\t\t");
				scanf("%9s", buildid);
				while (getchar() != '\n');
				printf("\n");
				printf("--------------------------------------------------------------------------------");
				newbuild = SeekBuildNode(hd, estateid, buildid);/*���Ҷ�Ӧ¥��*/
				if (newbuild == NULL)
					printf("\t\t\t\tδ�ҵ���Ӧ������\n");
				else
					ModifyBuild(newbuild);
				break;
			}
			case 3:/*�޸ķ�������*/
			{
				printf("--------------------------------------------------------------------------------");
				printf("\t\t����¥�̱��\t\t");
				scanf("%9s", estateid);
				while (getchar() != '\n');
				printf("\n");
				printf("--------------------------------------------------------------------------------");
				printf("\t\t����¥�����\t\t");
				scanf("%9s", buildid);
				while (getchar() != '\n');
				printf("\n");
				printf("--------------------------------------------------------------------------------");
				printf("\t\t���뷿�ݱ��\t\t");
				scanf("%9s", houseid);
				while (getchar() != '\n');
				printf("\n");
				printf("--------------------------------------------------------------------------------");
				newhouse = SeekHouseNode(hd, estateid, buildid, houseid);/*���Ҷ�Ӧ����*/
				if (newhouse == NULL)
					printf("\t\t\t\tδ�ҵ���Ӧ������\n");
				else
					ModifyHouse(newhouse);
				break;
			}
			}
			LABEL_BUNDLE labels;
			HOT_AREA areas;

			SMALL_RECT rcPop;
			COORD pos;
			WORD att;
			char *pCh[] = { "�����޸�                          ����" };
			int iHot = 1;

			pos.X = strlen(pCh[0]) + 6;
			pos.Y = 7;
			rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
			rcPop.Right = rcPop.Left + pos.X - 7;
			rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
			rcPop.Bottom = rcPop.Top + pos.Y - 8;
			att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
			labels.num = 1;
			labels.ppLabel = pCh;
			COORD aLoc[] = { { rcPop.Left, rcPop.Top },
			{ rcPop.Left + 5, rcPop.Top + 5 } };
			labels.pLoc = aLoc;

			areas.num = 2;
			SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
				rcPop.Left + 7, rcPop.Top },
				{ rcPop.Left + 34, rcPop.Top ,
				rcPop.Left + 37, rcPop.Top } };
			char aSort[] = { 0, 0 };
			char aTag[] = { 1, 2 };
			areas.pArea = aArea;
			areas.pSort = aSort;
			areas.pTag = aTag;
			PopUp(&rcPop, att, &labels, &areas);

			pos.X = rcPop.Left + 1;
			pos.Y = rcPop.Top + 4;

			if (DealInput(&areas, &iHot) == 13 && iHot == 1)
			{
				deal3 = 1;
			}
			else
			{
				deal3 = 0;
			}
			PopOff();
			InitInterface();
		}
	}
	return TRUE;
}


/*�޸�¥�����ݺ���*/
void ModifyEstate(ESTATE_NODE* pestate)
{
	int deal1;
	BUILD_NODE* pbuild;
	HOUSE_NODE* phouse;
	LABEL_BUNDLE labels;
	HOT_AREA areas;
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;
	char *pCh[] = { "1���޸�¥�̱��","2���޸�¥������", "3���޸�¥�̵�ַ","4���޸Ŀ�����","5���޸���ҵ��˾" };
	int iHot = 5;

	pos.X = strlen(pCh[0]) + 10;
	pos.Y = 12;
	rcPop.Left = (SCR_COL - pos.X) / 2;
	rcPop.Right = rcPop.Left + pos.X - 1;
	rcPop.Top = (25 - pos.Y) / 2;
	rcPop.Bottom = rcPop.Top + pos.Y + 5;

	att = BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
	labels.num = 5;
	labels.ppLabel = pCh;
	COORD aLoc[] = { { rcPop.Left + 3, rcPop.Top + 2 },
	{ rcPop.Left + 3, rcPop.Top + 5 },
	{ rcPop.Left + 3, rcPop.Top + 8 },
	{ rcPop.Left + 3, rcPop.Top + 11 },
	{ rcPop.Left + 3, rcPop.Top + 14 }
	};
	labels.pLoc = aLoc;

	areas.num = 5;
	SMALL_RECT aArea[] =
	{
		{
			rcPop.Left + 3, rcPop.Top + 2,
			rcPop.Left + 17, rcPop.Top + 2
		},
		{
			rcPop.Left + 3, rcPop.Top + 5,
			rcPop.Left + 17, rcPop.Top + 5
		},
		{
			rcPop.Left + 3, rcPop.Top + 8,
			rcPop.Left + 17, rcPop.Top + 8
		},
		{
			rcPop.Left + 3, rcPop.Top + 11,
			rcPop.Left + 17, rcPop.Top + 11
		},
		{
			rcPop.Left + 3, rcPop.Top + 14,
			rcPop.Left + 17, rcPop.Top + 14
		}
	};
	char aSort[] = { 0,0,0,0,0 };
	char aTag[] = { 1,2,3,4,5 };
	areas.pArea = aArea;
	areas.pSort = aSort;
	areas.pTag = aTag;
	PopUp(&rcPop, att, &labels, &areas);
	if (DealInput(&areas, &iHot) == 13 && iHot == 1)
	{
		/*��ȷ��ѯ*/
		PopOff();
		deal1 = 1;
	}
	else
	{
		if (iHot == 2)
		{
			PopOff();
			deal1 = 2;
		}
		else
		{
			if (iHot == 3)
			{
				PopOff();
				deal1 = 3;
			}
			else
			{
				if (iHot == 4)
				{
					PopOff();
					deal1 = 4;
				}
				else
				{
					PopOff();
					deal1 = 5;
				}
			}
		}
	}
	switch (deal1) {
	case 1:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t����¥�̱��\t\t");
		scanf("%9s", pestate->estate_id);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t�޸����");
		pbuild = pestate->bnext;
		while (pbuild)/*����¥�̶�Ӧ��¥���뷿����Ϣһ���޸�*/
		{
			strcpy(pbuild->estate_id, pestate->estate_id);
			phouse = pbuild->hnext;
			while (phouse)
			{
				strcpy(phouse->estate_id, pestate->estate_id);
				phouse = phouse->next;
			}
			pbuild = pbuild->next;
		}
		break;
	}
	case 2:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t����¥������\t\t");
		scanf("%19s", pestate->name);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t�޸����");
		break;
	}
	case 3:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t����¥�̵�ַ\t\t");
		scanf("%29s", pestate->address);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t�޸����");
		break;
	}
	case 4:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t���뿪����\t\t");
		scanf("%19s", pestate->developer);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t�޸����");
		break;
	}
	case 5:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t������ҵ��˾\t\t");
		scanf("%19s", pestate->management_company);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t�޸����");
		break;
	}
	}

}

/*�޸�¥�����ݺ���*/
void ModifyBuild(BUILD_NODE* pbuild)
{
	int deal1;
	HOUSE_NODE* phouse;
	LABEL_BUNDLE labels;
	HOT_AREA areas;
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;
	char *pCh[] = { "1���޸�¥�����","2���޸ĵ�Ԫ", "3���޸�¥��" };
	int iHot = 3;

	pos.X = strlen(pCh[0]) + 10;
	pos.Y = 12;
	rcPop.Left = (SCR_COL - pos.X) / 2;
	rcPop.Right = rcPop.Left + pos.X - 1;
	rcPop.Top = (25 - pos.Y) / 2;
	rcPop.Bottom = rcPop.Top + pos.Y - 1;

	att = BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
	labels.num = 3;
	labels.ppLabel = pCh;
	COORD aLoc[] = { { rcPop.Left + 3, rcPop.Top + 2 },
	{ rcPop.Left + 3, rcPop.Top + 5 },
	{ rcPop.Left + 3, rcPop.Top + 8 }
	};
	labels.pLoc = aLoc;

	areas.num = 3;
	SMALL_RECT aArea[] =
	{
		{
			rcPop.Left + 3, rcPop.Top + 2,
			rcPop.Left + 17, rcPop.Top + 2
		},
		{
			rcPop.Left + 3, rcPop.Top + 5,
			rcPop.Left + 17, rcPop.Top + 5
		},
		{
			rcPop.Left + 3, rcPop.Top + 8,
			rcPop.Left + 17, rcPop.Top + 8
		}
	};
	char aSort[] = { 0,0,0 };
	char aTag[] = { 1,2,3 };
	areas.pArea = aArea;
	areas.pSort = aSort;
	areas.pTag = aTag;
	PopUp(&rcPop, att, &labels, &areas);
	if (DealInput(&areas, &iHot) == 13 && iHot == 1)
	{
		/*��ȷ��ѯ*/
		PopOff();
		deal1 = 1;
	}
	else
	{
		if (iHot == 2)
		{
			PopOff();
			deal1 = 2;
		}
		else
		{
			PopOff();
			deal1 = 3;
		}
	}
	switch (deal1) {
	case 1:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t����¥�����\t\t");
		scanf("%9s", pbuild->build_id);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t�޸����");
		phouse = pbuild->hnext;
		while (phouse)/*�޸ĸ�¥����Ӧ�ķ�����Ϣ*/
		{
			strcpy(phouse->build_id, pbuild->build_id);
			phouse = phouse->next;
		}
		break;
	}
	case 2:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t���뵥Ԫ\t\t");
		scanf("%d", &pbuild->unit);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t�޸����");
		break;
	}
	case 3:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t����¥��\t\t");
		scanf("%d", &pbuild->floor);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t�޸����");
		break;
	}
	}
}

/**
*�������ƣ�SortEstateByNum
*�������ܣ�����ѡ�����򷨽�¥�����ݰ���Ŵ�С��������
*�������������ͷָ��
*�����������
*����ֵ����
*/
void SortEstateByNum(ESTATE_NODE *head)
{
	ESTATE_NODE *flag, *pestate, *p;
	ESTATE_NODE* temp = malloc(sizeof(ESTATE_NODE));
	int iflag, ip;
	for (pestate = head; pestate != NULL; pestate = pestate->next)
	{
		flag = pestate;
		for (p = pestate; p != NULL; p = p->next)
		{
			iflag = atoi(flag->estate_id);
			ip = atoi(p->estate_id);
			if (iflag > ip)
				flag = p;
		}
		*temp = *flag;
		*flag = *pestate;
		*pestate = *temp;
		temp->next = flag->next;
		flag->next = pestate->next;
		pestate->next = temp->next;
	}
	free(temp);
}

/*�޸ķ������ݺ���*/
void ModifyHouse(HOUSE_NODE* phouse)
{
	int deal1;
	LABEL_BUNDLE labels;
	HOT_AREA areas;
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;
	char *pCh[] = { "1���޸ķ��ݱ��","2���޸Ļ���", "3���޸����","4���޸Ĺ�̯��","5���޸ļ۸�" };
	int iHot = 5;

	pos.X = strlen(pCh[0]) + 10;
	pos.Y = 12;
	rcPop.Left = (SCR_COL - pos.X) / 2;
	rcPop.Right = rcPop.Left + pos.X - 1;
	rcPop.Top = (25 - pos.Y) / 2;
	rcPop.Bottom = rcPop.Top + pos.Y + 5;

	att = BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
	labels.num = 5;
	labels.ppLabel = pCh;
	COORD aLoc[] = { { rcPop.Left + 3, rcPop.Top + 2 },
	{ rcPop.Left + 3, rcPop.Top + 5 },
	{ rcPop.Left + 3, rcPop.Top + 8 },
	{ rcPop.Left + 3, rcPop.Top + 11 },
	{ rcPop.Left + 3, rcPop.Top + 14 }
	};
	labels.pLoc = aLoc;

	areas.num = 5;
	SMALL_RECT aArea[] =
	{
		{
			rcPop.Left + 3, rcPop.Top + 2,
			rcPop.Left + 17, rcPop.Top + 2
		},
		{
			rcPop.Left + 3, rcPop.Top + 5,
			rcPop.Left + 17, rcPop.Top + 5
		},
		{
			rcPop.Left + 3, rcPop.Top + 8,
			rcPop.Left + 17, rcPop.Top + 8
		},
		{
			rcPop.Left + 3, rcPop.Top + 11,
			rcPop.Left + 17, rcPop.Top + 11
		},
		{
			rcPop.Left + 3, rcPop.Top + 14,
			rcPop.Left + 17, rcPop.Top + 14
		}
	};
	char aSort[] = { 0,0,0,0,0 };
	char aTag[] = { 1,2,3,4,5 };
	areas.pArea = aArea;
	areas.pSort = aSort;
	areas.pTag = aTag;
	PopUp(&rcPop, att, &labels, &areas);
	if (DealInput(&areas, &iHot) == 13 && iHot == 1)
	{
		/*��ȷ��ѯ*/
		PopOff();
		deal1 = 1;
	}
	else
	{
		if (iHot == 2)
		{
			PopOff();
			deal1 = 2;
		}
		else
		{
			if (iHot == 3)
			{
				PopOff();
				deal1 = 3;
			}
			else
			{
				if (iHot == 4)
				{
					PopOff();
					deal1 = 4;
				}
				else
				{
					PopOff();
					deal1 = 5;
				}
			}
		}
	}
	switch (deal1) {
	case 1:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t���뷿�ݱ��\t\t");
		scanf("%9s", phouse->house_id);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t�޸����");
		break;
	}
	case 2:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t���뻧��\t\t");
		scanf("%19s", phouse->type);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t�޸����");
		break;
	}
	case 3:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t�������\t\t");
		scanf("%d", &phouse->area);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t�޸����");
		break;
	}
	case 4:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t���빫̯��\t\t");
		scanf("%f", &phouse->shared_rate);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t�޸����");
		break;
	}
	case 5:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t����۸�\t\t");
		scanf("%d", &phouse->one_price);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t�޸����");
		break;
	}
	}
}

/**
*�������ƣ�ShowAllEstate
*�������ܣ��Է�ҳ����ʽչʾ¥��
*�����������
*�����������
*����ֵ��BOOL���ͣ�ʼ�շ���TRUE
*/
BOOL ShowAllEstate(void)
{
	SortEstateByNum(hd);
	InitInterface();
	int num = 0, i = 0, page = 0;//page������־ҳ��
	int choice;//��choice==1�����ʾ������choice==0�������
	int k;//ÿ����k���������������5��
	int flag;//��flag==0����ʾ����ҳ��flag==1����ʾ���м䣻flag==2����ʾ��βҳ
	ESTATE_NODE* pestate;
	ESTATE_NODE* p[10000];
	pestate = hd;
	while (pestate)
	{
		num++;
		if (num % 5 == 1)
		{
			p[i] = pestate;
			i++;
		}
		pestate = pestate->next;
	}
	if (i == 1)//ֻ��һҳ
	{
		pestate = p[page];
		printf("--------------------------------------------------------------------------------");
		printf("¥�̱��|    ¥������    |���ڳ���|    ¥�̵�ַ    |   ������   |   ��ҵ��˾   |");
		printf("--------------------------------------------------------------------------------");
		while (pestate)
		{
			printf("%8s|%16s|%8s|%16s|%12s|%14s|", pestate->estate_id, pestate->name,
				pestate->city, pestate->address, pestate->developer, pestate->management_company);
			printf("--------------------------------------------------------------------------------");
			pestate = pestate->next;
		}
		printf("�����������...");
		getch();
		InitInterface();
	}
	else//�ж�ҳ��ʱ��
	{
		do
		{
			if (page == 0)
				flag = 0;
			else if (page < i - 1)
				flag = 1;
			else
				flag = 2;
			switch (flag)
			{
			case 0:
			{
				k = 0;
				pestate = p[page];
				printf("--------------------------------------------------------------------------------");
				printf("¥�̱��|    ¥������    |���ڳ���|    ¥�̵�ַ    |   ������   |   ��ҵ��˾   |");
				printf("--------------------------------------------------------------------------------");
				while (k < 5 && pestate)
				{
					k++;
					printf("%8s|%16s|%8s|%16s|%12s|%14s|", pestate->estate_id, pestate->name,
						pestate->city, pestate->address, pestate->developer, pestate->management_company);
					printf("--------------------------------------------------------------------------------");
					pestate = pestate->next;
				}
				printf("\n");
				printf("                                                          ��%dҳ\n", page + 1);
				printf("                                                           ��%dҳ\n", i);
				LABEL_BUNDLE labels;
				HOT_AREA areas;

				SMALL_RECT rcPop;
				COORD pos;
				WORD att;
				char *pCh[] = { "��һҳ                          ��  ��" };
				int iHot = 1;

				pos.X = strlen(pCh[0]) + 6;
				pos.Y = 7;
				rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
				rcPop.Right = rcPop.Left + pos.X - 7;
				rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
				rcPop.Bottom = rcPop.Top + pos.Y - 8;

				att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
				labels.num = 1;
				labels.ppLabel = pCh;
				COORD aLoc[] = { { rcPop.Left, rcPop.Top },
				{ rcPop.Left + 5, rcPop.Top + 5 } };
				labels.pLoc = aLoc;

				areas.num = 2;
				SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
					rcPop.Left + 5, rcPop.Top },
					{ rcPop.Left + 32, rcPop.Top ,
					rcPop.Left + 37, rcPop.Top } };
				char aSort[] = { 0, 0 };
				char aTag[] = { 1, 2 };
				areas.pArea = aArea;
				areas.pSort = aSort;
				areas.pTag = aTag;
				PopUp(&rcPop, att, &labels, &areas);

				pos.X = rcPop.Left + 1;
				pos.Y = rcPop.Top + 4;

				if (DealInput(&areas, &iHot) == 13 && iHot == 1)
				{
					choice = 1;
					page++;
				}
				else
				{
					choice = 0;
				}
				PopOff();
				InitInterface();
				break;
			}
			case 1:
			{
				k = 0;
				pestate = p[page];
				printf("--------------------------------------------------------------------------------");
				printf("¥�̱��|    ¥������    |���ڳ���|    ¥�̵�ַ    |   ������   |   ��ҵ��˾   |");
				printf("--------------------------------------------------------------------------------");
				while (k < 5 && pestate)
				{
					k++;
					printf("%8s|%16s|%8s|%16s|%12s|%14s|", pestate->estate_id, pestate->name,
						pestate->city, pestate->address, pestate->developer, pestate->management_company);
					printf("--------------------------------------------------------------------------------");
					pestate = pestate->next;
				}
				printf("\n");
				printf("                                                          ��%dҳ\n", page + 1);
				printf("                                                           ��%dҳ\n", i);
				LABEL_BUNDLE labels;
				HOT_AREA areas;

				SMALL_RECT rcPop;
				COORD pos;
				WORD att;
				char *pCh[] = { "��һҳ                          ��һҳ" };
				int iHot = 1;

				pos.X = strlen(pCh[0]) + 6;
				pos.Y = 7;
				rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
				rcPop.Right = rcPop.Left + pos.X - 7;
				rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
				rcPop.Bottom = rcPop.Top + pos.Y - 8;

				att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
				labels.num = 1;
				labels.ppLabel = pCh;
				COORD aLoc[] = { { rcPop.Left, rcPop.Top },
				{ rcPop.Left + 5, rcPop.Top + 5 } };
				labels.pLoc = aLoc;

				areas.num = 2;
				SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
					rcPop.Left + 5, rcPop.Top },
					{ rcPop.Left + 32, rcPop.Top ,
					rcPop.Left + 37, rcPop.Top } };
				char aSort[] = { 0, 0 };
				char aTag[] = { 1, 2 };
				areas.pArea = aArea;
				areas.pSort = aSort;
				areas.pTag = aTag;
				PopUp(&rcPop, att, &labels, &areas);

				pos.X = rcPop.Left + 1;
				pos.Y = rcPop.Top + 4;

				if (DealInput(&areas, &iHot) == 13 && iHot == 1)
				{
					page--;
					choice = 1;
				}
				else
				{
					page++;
					choice = 1;
				}
				PopOff();
				InitInterface();
				break;
			}
			case 2:
			{
				k = 0;
				pestate = p[page];
				printf("--------------------------------------------------------------------------------");
				printf("¥�̱��|    ¥������    |���ڳ���|    ¥�̵�ַ    |   ������   |   ��ҵ��˾   |");
				printf("--------------------------------------------------------------------------------");
				while (k < 5 && pestate)
				{
					k++;
					printf("%8s|%16s|%8s|%16s|%12s|%14s|", pestate->estate_id, pestate->name,
						pestate->city, pestate->address, pestate->developer, pestate->management_company);
					printf("--------------------------------------------------------------------------------");
					pestate = pestate->next;
				}
				printf("\n");
				printf("                                                          ��%dҳ\n", page + 1);
				printf("                                                           ��%dҳ\n", i);
				LABEL_BUNDLE labels;
				HOT_AREA areas;

				SMALL_RECT rcPop;
				COORD pos;
				WORD att;
				char *pCh[] = { "��һҳ                          ��  ��" };
				int iHot = 1;

				pos.X = strlen(pCh[0]) + 6;
				pos.Y = 7;
				rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
				rcPop.Right = rcPop.Left + pos.X - 7;
				rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
				rcPop.Bottom = rcPop.Top + pos.Y - 8;

				att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
				labels.num = 1;
				labels.ppLabel = pCh;
				COORD aLoc[] = { { rcPop.Left, rcPop.Top },
				{ rcPop.Left + 5, rcPop.Top + 5 } };
				labels.pLoc = aLoc;

				areas.num = 2;
				SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
					rcPop.Left + 5, rcPop.Top },
					{ rcPop.Left + 32, rcPop.Top ,
					rcPop.Left + 37, rcPop.Top } };
				char aSort[] = { 0, 0 };
				char aTag[] = { 1, 2 };
				areas.pArea = aArea;
				areas.pSort = aSort;
				areas.pTag = aTag;
				PopUp(&rcPop, att, &labels, &areas);

				pos.X = rcPop.Left + 1;
				pos.Y = rcPop.Top + 4;

				if (DealInput(&areas, &iHot) == 13 && iHot == 1)
				{
					choice = 1;
					page--;
				}
				else
					choice = 0;
				PopOff();
				InitInterface();
				break;
			}
			}
		} while (choice);
	}
	return TRUE;
}

/**
*�������ƣ�ShowHouseList
*�������ܣ��Է�ҳ����ʽչʾ������Ϣ
*���������HOUSE_NODE����ͷָ��
*�����������
*����ֵ��BOOL���ͣ�����FALSE�����HOUSE_NODEΪ��ָ�룬�����ʾ�������
*/
BOOL ShowHouseList(HOUSE_NODE* househd)
{
	InitInterface();
	if (househd == NULL)
	{
		printf("δ��ѯ����Ӧ�������\n");
		printf("�����������...");
		getch();
		InitInterface();
		return FALSE;
	}
	else
	{
		int num = 0, i = 0, page = 0;//page������־ҳ��
		int choice;//��choice==1�����ʾ������choice==0�������
		int k;//ÿ����k���������������5��
		int flag;//��flag==0����ʾ����ҳ��flag==1����ʾ���м䣻flag==2����ʾ��βҳ
		HOUSE_NODE* phouse;
		HOUSE_NODE* p[300000];
		phouse = househd;
		while (phouse)
		{
			num++;
			if (num % 5 == 1)
			{
				p[i] = phouse;
				i++;
			}
			phouse = phouse->next;
		}
		if (i == 1)//ֻ��һҳ
		{
			phouse = p[page];
			printf("--------------------------------------------------------------------------------");
			printf("¥�̱��|¥�����|���ݱ��|    ����    |�������(ƽ����)|��̯��|�۸�(Ԫ/ƽ����)|");
			printf("--------------------------------------------------------------------------------");
			while (phouse)
			{
				printf("%8s|%8s|%8s|%12s|%16d|%6.2f|%15d|", phouse->estate_id, phouse->build_id,
					phouse->house_id, phouse->type, phouse->area, phouse->shared_rate,phouse->one_price);
				printf("--------------------------------------------------------------------------------");
				phouse = phouse->next;
			}
			printf("�����������...");
			getch();
			InitInterface();
		}
		else//�ж�ҳ��ʱ��
		{
			do
			{
				if (page == 0)
					flag = 0;
				else if (page < i - 1)
					flag = 1;
				else
					flag = 2;
				switch (flag)
				{
				case 0:
				{
					k = 0;
					phouse = p[page];
					printf("--------------------------------------------------------------------------------");
					printf("¥�̱��|¥�����|���ݱ��|    ����    |�������(ƽ����)|��̯��|�۸�(Ԫ/ƽ����)|");
					printf("--------------------------------------------------------------------------------");
					while (phouse && k<5)
					{
						k++;
						printf("%8s|%8s|%8s|%12s|%16d|%6.2f|%15d|", phouse->estate_id, phouse->build_id,
							phouse->house_id, phouse->type, phouse->area, phouse->shared_rate, phouse->one_price);
						printf("--------------------------------------------------------------------------------");
						phouse = phouse->next;
					}
					printf("\n");
					printf("                                                          ��%dҳ\n", page + 1);
					printf("                                                           ��%dҳ\n", i);
					LABEL_BUNDLE labels;
					HOT_AREA areas;

					SMALL_RECT rcPop;
					COORD pos;
					WORD att;
					char *pCh[] = { "��һҳ                          ��  ��" };
					int iHot = 1;

					pos.X = strlen(pCh[0]) + 6;
					pos.Y = 7;
					rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
					rcPop.Right = rcPop.Left + pos.X - 7;
					rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
					rcPop.Bottom = rcPop.Top + pos.Y - 8;

					att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
					labels.num = 1;
					labels.ppLabel = pCh;
					COORD aLoc[] = { { rcPop.Left, rcPop.Top },
					{ rcPop.Left + 5, rcPop.Top + 5 } };
					labels.pLoc = aLoc;

					areas.num = 2;
					SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
						rcPop.Left + 5, rcPop.Top },
						{ rcPop.Left + 32, rcPop.Top ,
						rcPop.Left + 37, rcPop.Top } };
					char aSort[] = { 0, 0 };
					char aTag[] = { 1, 2 };
					areas.pArea = aArea;
					areas.pSort = aSort;
					areas.pTag = aTag;
					PopUp(&rcPop, att, &labels, &areas);

					pos.X = rcPop.Left + 1;
					pos.Y = rcPop.Top + 4;

					if (DealInput(&areas, &iHot) == 13 && iHot == 1)
					{
						choice = 1;
						page++;
					}
					else
					{
						choice = 0;
					}
					PopOff();
					InitInterface();
					break;
				}
				case 1:
				{
					k = 0;
					phouse = p[page];
					printf("--------------------------------------------------------------------------------");
					printf("¥�̱��|¥�����|���ݱ��|    ����    |�������(ƽ����)|��̯��|�۸�(Ԫ/ƽ����)|");
					printf("--------------------------------------------------------------------------------");
					while (phouse && k<5)
					{
						k++;
						printf("%8s|%8s|%8s|%12s|%16d|%6.2f|%15d|", phouse->estate_id, phouse->build_id,
							phouse->house_id, phouse->type, phouse->area, phouse->shared_rate, phouse->one_price);
						printf("--------------------------------------------------------------------------------");
						phouse = phouse->next;
					}
					printf("\n");
					printf("                                                          ��%dҳ\n", page + 1);
					printf("                                                           ��%dҳ\n", i);
					LABEL_BUNDLE labels;
					HOT_AREA areas;

					SMALL_RECT rcPop;
					COORD pos;
					WORD att;
					char *pCh[] = { "��һҳ                          ��һҳ" };
					int iHot = 1;

					pos.X = strlen(pCh[0]) + 6;
					pos.Y = 7;
					rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
					rcPop.Right = rcPop.Left + pos.X - 7;
					rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
					rcPop.Bottom = rcPop.Top + pos.Y - 8;

					att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
					labels.num = 1;
					labels.ppLabel = pCh;
					COORD aLoc[] = { { rcPop.Left, rcPop.Top },
					{ rcPop.Left + 5, rcPop.Top + 5 } };
					labels.pLoc = aLoc;

					areas.num = 2;
					SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
						rcPop.Left + 5, rcPop.Top },
						{ rcPop.Left + 32, rcPop.Top ,
						rcPop.Left + 37, rcPop.Top } };
					char aSort[] = { 0, 0 };
					char aTag[] = { 1, 2 };
					areas.pArea = aArea;
					areas.pSort = aSort;
					areas.pTag = aTag;
					PopUp(&rcPop, att, &labels, &areas);

					pos.X = rcPop.Left + 1;
					pos.Y = rcPop.Top + 4;

					if (DealInput(&areas, &iHot) == 13 && iHot == 1)
					{
						page--;
						choice = 1;
					}
					else
					{
						page++;
						choice = 1;
					}
					PopOff();
					InitInterface();
					break;
				}
				case 2:
				{
					k = 0;
					phouse = p[page];
					printf("--------------------------------------------------------------------------------");
					printf("¥�̱��|¥�����|���ݱ��|    ����    |�������(ƽ����)|��̯��|�۸�(Ԫ/ƽ����)|");
					printf("--------------------------------------------------------------------------------");
					while (phouse && k<5)
					{
						k++;
						printf("%8s|%8s|%8s|%12s|%16d|%6.2f|%15d|", phouse->estate_id, phouse->build_id,
							phouse->house_id, phouse->type, phouse->area, phouse->shared_rate, phouse->one_price);
						printf("--------------------------------------------------------------------------------");
						phouse = phouse->next;
					}
					printf("\n");
					printf("                                                          ��%dҳ\n", page + 1);
					printf("                                                           ��%dҳ\n", i);
					LABEL_BUNDLE labels;
					HOT_AREA areas;

					SMALL_RECT rcPop;
					COORD pos;
					WORD att;
					char *pCh[] = { "��һҳ                          ��  ��" };
					int iHot = 1;

					pos.X = strlen(pCh[0]) + 6;
					pos.Y = 7;
					rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
					rcPop.Right = rcPop.Left + pos.X - 7;
					rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
					rcPop.Bottom = rcPop.Top + pos.Y - 8;

					att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
					labels.num = 1;
					labels.ppLabel = pCh;
					COORD aLoc[] = { { rcPop.Left, rcPop.Top },
					{ rcPop.Left + 5, rcPop.Top + 5 } };
					labels.pLoc = aLoc;

					areas.num = 2;
					SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
						rcPop.Left + 5, rcPop.Top },
						{ rcPop.Left + 32, rcPop.Top ,
						rcPop.Left + 37, rcPop.Top } };
					char aSort[] = { 0, 0 };
					char aTag[] = { 1, 2 };
					areas.pArea = aArea;
					areas.pSort = aSort;
					areas.pTag = aTag;
					PopUp(&rcPop, att, &labels, &areas);

					pos.X = rcPop.Left + 1;
					pos.Y = rcPop.Top + 4;

					if (DealInput(&areas, &iHot) == 13 && iHot == 1)
					{
						choice = 1;
						page--;
					}
					else
						choice = 0;
					PopOff();
					InitInterface();
					break;
				}
				}
			} while (choice);
		}
		return TRUE;
	}
}

/**
*�������ƣ�ShowAllHouse
*�������ܣ��Է�ҳ����ʽչʾ���еķ�������
*�����������
*�����������
*����ֵ��BOOL���ͣ�ʼ�շ���TRUE
*/
BOOL ShowAllHouse(void)
{
	InitInterface();
	HOUSE_NODE* houhd = NULL;
	HOUSE_NODE* temp = NULL;
	ESTATE_NODE* pestate;
	BUILD_NODE* pbuild;
	HOUSE_NODE* phouse;
	for(pestate=hd;pestate;pestate=pestate->next)
		for(pbuild=pestate->bnext;pbuild;pbuild=pbuild->next)
			for (phouse = pbuild->hnext; phouse; phouse = phouse->next)
			{
				temp = (HOUSE_NODE *)malloc(sizeof(HOUSE_NODE));
				*temp = *phouse;
				temp->next = houhd;
				houhd = temp;
			}

	int choice;
	LABEL_BUNDLE labels;
	HOT_AREA areas;
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;
	char *pCh[] = { "��Ĭ�ϱ�����                         ���۸�ߵ����" };
	int iHot = 1;

	pos.X = strlen(pCh[0]) + 6;
	pos.Y = 7;
	rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
	rcPop.Right = rcPop.Left + pos.X - 7;
	rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
	rcPop.Bottom = rcPop.Top + pos.Y - 8;

	att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
	labels.num = 1;
	labels.ppLabel = pCh;
	COORD aLoc[] = { { rcPop.Left, rcPop.Top },
	{ rcPop.Left + 5, rcPop.Top + 5 } };
	labels.pLoc = aLoc;

	areas.num = 2;
	SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
		rcPop.Left + 13, rcPop.Top },
		{ rcPop.Left + 39, rcPop.Top ,
		rcPop.Left + 52, rcPop.Top } };
	char aSort[] = { 0, 0 };
	char aTag[] = { 1, 2 };
	areas.pArea = aArea;
	areas.pSort = aSort;
	areas.pTag = aTag;
	PopUp(&rcPop, att, &labels, &areas);

	pos.X = rcPop.Left + 1;
	pos.Y = rcPop.Top + 4;

	if (DealInput(&areas, &iHot) == 13 && iHot == 1)
	{
		choice = 1;
	}
	else
	{
		choice = 2;
	}
	PopOff();
	
	switch (choice)
	{
	case 1:
		SortHouseByNum(houhd);
		break;
	case 2:
		SortHouseByPrice(houhd);
		break;
	}
	ShowHouseList(houhd);
	while (houhd)
	{
		HOUSE_NODE* temp = houhd;
		houhd = houhd->next;
		free(temp);
	}
	return TRUE;
}

/*����¥��ͨ��id*/
void SortHouseByNum(HOUSE_NODE* head)
{
	HOUSE_NODE *flag, *phouse, *p;
	HOUSE_NODE* temp = malloc(sizeof(HOUSE_NODE));
	int deal;
	for (phouse = head; phouse != NULL; phouse = phouse->next)
	{
		flag = phouse;
		for (p = phouse; p != NULL; p = p->next)
		{
			if (atoi(p->estate_id) > atoi(phouse->estate_id))
				deal = 0;
			else if (atoi(p->estate_id) < atoi(phouse->estate_id))
				deal = 1;
			else
			{
				if (atoi(p->build_id) > atoi(phouse->build_id))
					deal = 0;
				else if (atoi(p->build_id) < atoi(phouse->build_id))
					deal = 1;
				else
				{
					if (atoi(p->house_id) > atoi(phouse->house_id))
						deal = 0;
					else if (atoi(p->house_id) < atoi(phouse->house_id))
						deal = 1;
					else deal = 0;
				}
			}
			if (deal)
				flag = p;
		}
		*temp = *flag;
		*flag = *phouse;
		*phouse = *temp;
		temp->next = flag->next;
		flag->next = phouse->next;
		phouse->next = temp->next;
	}
	free(temp);

}

/*ͨ���۸����������ݺ���*/
void SortHouseByPrice(HOUSE_NODE* head)
{
	HOUSE_NODE *flag, *phouse, *p;
	HOUSE_NODE* temp = malloc(sizeof(HOUSE_NODE));
	int iflag, ip;
	for (phouse = head; phouse != NULL; phouse = phouse->next)
	{
		flag = phouse;
		for (p = phouse; p != NULL; p = p->next)
		{
			iflag = flag->one_price;
			ip = p->one_price;
			if (iflag > ip)
				flag = p;
		}
		*temp = *flag;
		*flag = *phouse;
		*phouse = *temp;
		temp->next = flag->next;
		flag->next = phouse->next;
		phouse->next = temp->next;
	}
	free(temp);
}

/**
*�������ƣ�StatCity
*�������ܣ���������ѯ������Ϣ
*�����������
*�����������
*����ֵ��BOOL���ͣ�ʼ�շ���TRUE
*/
BOOL StatCity(void)
{
	InitInterface();
	printf("�����������ѯ�ĳ�����"); 
	char s[10];
	scanf("%9s", s);
	while (getchar() != '\n');
	HOUSE_NODE* houhd = NULL;
	HOUSE_NODE* temp = NULL;
	ESTATE_NODE* pestate;
	BUILD_NODE* pbuild;
	HOUSE_NODE* phouse;
	for (pestate = hd; pestate; pestate = pestate->next)
		if (strcmp(pestate->city, s) == 0)
		{
			for (pbuild = pestate->bnext; pbuild; pbuild = pbuild->next)
				for (phouse = pbuild->hnext; phouse; phouse = phouse->next)
				{
					temp = (HOUSE_NODE *)malloc(sizeof(HOUSE_NODE));
					*temp = *phouse;
					temp->next = houhd;
					houhd = temp;
				}
		}
	int choice;
	LABEL_BUNDLE labels;
	HOT_AREA areas;
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;
	char *pCh[] = { "��Ĭ�ϱ�����                         ���۸�ߵ����" };
	int iHot = 1;

	pos.X = strlen(pCh[0]) + 6;
	pos.Y = 7;
	rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
	rcPop.Right = rcPop.Left + pos.X - 7;
	rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
	rcPop.Bottom = rcPop.Top + pos.Y - 8;

	att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
	labels.num = 1;
	labels.ppLabel = pCh;
	COORD aLoc[] = { { rcPop.Left, rcPop.Top },
	{ rcPop.Left + 5, rcPop.Top + 5 } };
	labels.pLoc = aLoc;

	areas.num = 2;
	SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
		rcPop.Left + 13, rcPop.Top },
		{ rcPop.Left + 39, rcPop.Top ,
		rcPop.Left + 52, rcPop.Top } };
	char aSort[] = { 0, 0 };
	char aTag[] = { 1, 2 };
	areas.pArea = aArea;
	areas.pSort = aSort;
	areas.pTag = aTag;
	PopUp(&rcPop, att, &labels, &areas);

	pos.X = rcPop.Left + 1;
	pos.Y = rcPop.Top + 4;

	if (DealInput(&areas, &iHot) == 13 && iHot == 1)
	{
		choice = 1;
	}
	else
	{
		choice = 2;
	}
	PopOff();
	InitInterface();

	switch (choice)
	{
	case 1:
		SortHouseByNum(houhd);
		break;
	case 2:
		SortHouseByPrice(houhd);
		break;
	}
	ShowHouseList(houhd);
	while (houhd)
	{
		HOUSE_NODE* temp = houhd;
		houhd = houhd->next;
		free(temp);
	}
	return TRUE;
}

/**
*�������ƣ�StatType
*�������ܣ������Ͳ�ѯ������Ϣ
*�����������
*�����������
*����ֵ��BOOL���ͣ�ʼ�շ���TRUE
*/
BOOL StatType(void)
{
	InitInterface();
	printf("�����������ѯ�Ļ��ͣ�");
	char s[20];
	scanf("%19s", s);
	while (getchar() != '\n');
	HOUSE_NODE* houhd = NULL;
	HOUSE_NODE* temp = NULL;
	ESTATE_NODE* pestate;
	BUILD_NODE* pbuild;
	HOUSE_NODE* phouse;
	for (pestate = hd; pestate; pestate = pestate->next)
		for (pbuild = pestate->bnext; pbuild; pbuild = pbuild->next)
			for (phouse = pbuild->hnext; phouse; phouse = phouse->next)
			{
				if (strcmp(phouse->type, s) == 0)
				{
					temp = (HOUSE_NODE *)malloc(sizeof(HOUSE_NODE));
					*temp = *phouse;
					temp->next = houhd;
					houhd = temp;
				}
			}
	int choice;
	LABEL_BUNDLE labels;
	HOT_AREA areas;
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;
	char *pCh[] = { "��Ĭ�ϱ�����                         ���۸�ߵ����" };
	int iHot = 1;

	pos.X = strlen(pCh[0]) + 6;
	pos.Y = 7;
	rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
	rcPop.Right = rcPop.Left + pos.X - 7;
	rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
	rcPop.Bottom = rcPop.Top + pos.Y - 8;

	att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
	labels.num = 1;
	labels.ppLabel = pCh;
	COORD aLoc[] = { { rcPop.Left, rcPop.Top },
	{ rcPop.Left + 5, rcPop.Top + 5 } };
	labels.pLoc = aLoc;

	areas.num = 2;
	SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
		rcPop.Left + 13, rcPop.Top },
		{ rcPop.Left + 39, rcPop.Top ,
		rcPop.Left + 52, rcPop.Top } };
	char aSort[] = { 0, 0 };
	char aTag[] = { 1, 2 };
	areas.pArea = aArea;
	areas.pSort = aSort;
	areas.pTag = aTag;
	PopUp(&rcPop, att, &labels, &areas);

	pos.X = rcPop.Left + 1;
	pos.Y = rcPop.Top + 4;

	if (DealInput(&areas, &iHot) == 13 && iHot == 1)
	{
		choice = 1;
	}
	else
	{
		choice = 2;
	}
	PopOff();
	InitInterface();

	switch (choice)
	{
	case 1:
		SortHouseByNum(houhd);
		break;
	case 2:
		SortHouseByPrice(houhd);
		break;
	}
	ShowHouseList(houhd);
	while (houhd)
	{
		HOUSE_NODE* temp = houhd;
		houhd = houhd->next;
		free(temp);
	}
	return TRUE;
}

/**
*�������ƣ�StatPrice
*�������ܣ������Ͳ�ѯ������Ϣ
*�����������
*�����������
*����ֵ��BOOL���ͣ�ʼ�շ���TRUE
*/
BOOL StatPrice(void)
{
	InitInterface();
	printf("���������ѯ�ķ��ݼ۸�������ޣ�\n");
	int min, max;
	printf("����Ϊ��");
	scanf("%d", &max);
	printf("����Ϊ��");
	scanf("%d", &min);

	HOUSE_NODE* houhd = NULL;
	HOUSE_NODE* temp = NULL;
	ESTATE_NODE* pestate;
	BUILD_NODE* pbuild;
	HOUSE_NODE* phouse;
	for (pestate = hd; pestate; pestate = pestate->next)
		for (pbuild = pestate->bnext; pbuild; pbuild = pbuild->next)
			for (phouse = pbuild->hnext; phouse; phouse = phouse->next)
			{
				if (phouse->one_price>=min && phouse->one_price<=max)
				{
					temp = (HOUSE_NODE *)malloc(sizeof(HOUSE_NODE));
					*temp = *phouse;
					temp->next = houhd;
					houhd = temp;
				}
			}
	int choice;
	LABEL_BUNDLE labels;
	HOT_AREA areas;
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;
	char *pCh[] = { "��Ĭ�ϱ�����                         ���۸�ߵ����" };
	int iHot = 1;

	pos.X = strlen(pCh[0]) + 6;
	pos.Y = 7;
	rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
	rcPop.Right = rcPop.Left + pos.X - 7;
	rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
	rcPop.Bottom = rcPop.Top + pos.Y - 8;

	att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*�׵׺���*/
	labels.num = 1;
	labels.ppLabel = pCh;
	COORD aLoc[] = { { rcPop.Left, rcPop.Top },
	{ rcPop.Left + 5, rcPop.Top + 5 } };
	labels.pLoc = aLoc;

	areas.num = 2;
	SMALL_RECT aArea[] = { { rcPop.Left , rcPop.Top ,
		rcPop.Left + 13, rcPop.Top },
		{ rcPop.Left + 39, rcPop.Top ,
		rcPop.Left + 52, rcPop.Top } };
	char aSort[] = { 0, 0 };
	char aTag[] = { 1, 2 };
	areas.pArea = aArea;
	areas.pSort = aSort;
	areas.pTag = aTag;
	PopUp(&rcPop, att, &labels, &areas);

	pos.X = rcPop.Left + 1;
	pos.Y = rcPop.Top + 4;

	if (DealInput(&areas, &iHot) == 13 && iHot == 1)
	{
		choice = 1;
	}
	else
	{
		choice = 2;
	}
	PopOff();
	InitInterface();

	switch (choice)
	{
	case 1:
		SortHouseByNum(houhd);
		break;
	case 2:
		SortHouseByPrice(houhd);
		break;
	}
	ShowHouseList(houhd);
	while (houhd)
	{
		HOUSE_NODE* temp = houhd;
		houhd = houhd->next;
		free(temp);
	}
	return TRUE;
}

