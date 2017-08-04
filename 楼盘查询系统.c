#include"estate.h"
int main(void)
{
	COORD size = { SCR_COL, SCR_ROW };              /*窗口缓冲区大小*/

	gh_std_out = GetStdHandle(STD_OUTPUT_HANDLE); /* 获取标准输出设备句柄*/
	gh_std_in = GetStdHandle(STD_INPUT_HANDLE);   /* 获取标准输入设备句柄*/

	SetConsoleTitle(gp_sys_name);                 /*设置窗口标题*/
	SetConsoleScreenBufferSize(gh_std_out, size); /*设置窗口缓冲区大小80*25*/

	if (!LoadData())
		return 1;                  /*数据加载*/
	InitInterface();          /*界面初始化*/
	RunSys(&hd);             /*系统功能模块的选择及运行*/
	CloseSys(hd);            /*退出系统*/

	return 0;
}




BOOL HelpTopic(void)
{
	printf("--------------------------------------------------------------------------------");
	printf("该系统提供了以下功能\n");
	printf("1.文件备份、保存、恢复功能\n");
	printf("2.增减&删改数据功能\n");
	printf("3.按城区、户型、价格查询房屋数据功能\n");
	printf("4.统计全部楼盘、房屋数据功能\n");
	printf("--------------------------------------------------------------------------------");
	printf("\n\n\n");
	printf("\t\t\t\t\t\t按任意键继续...");
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
	char *pCh[] = { "作者的话                          关于" };
	int iHot = 1;

	pos.X = strlen(pCh[0]) + 6;
	pos.Y = 7;
	rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
	rcPop.Right = rcPop.Left + pos.X - 7;
	rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
	rcPop.Bottom = rcPop.Top + pos.Y - 8;
	att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
		printf("系统名：楼盘查询系统\n");
		printf("发布时间：2017/8/4\n");
		printf("适用平台：windows操作系统\n");
		printf("--------------------------------------------------------------------------------");
		printf("发布人：CS1610宁嘉\n");
		printf("邮箱：hust_ningjia@hust.edu.cn\n");
		printf("网址：https://github.com/hust-nj/Searching-Real-Estate-System");
		printf("\n                                      -----欢迎Fork me\n");
		break;
	case 1:
		printf("这是我做的第一个系统，虽然花了比较多的时间，\n功能也不是很完善，但是做出来后还是很开心!\n");
		break;
	}
	printf("\n\n\n");
	printf("\t\t\t\t\t\t按任意键继续...");
	getch();
	InitInterface();
	return 1;
}

/**
* 函数名称：Adminstrator
* 函数功能：获取管理员权限
* 输入参数：无
* 输出参数：pass
* 返回值：无
* 函数说明：
*/
void Administrator(void)
{
	char account[21];
	char password[21];
	int deal1 = 1;
	while (pass && deal1)
	{
		int i = 0;		// i代表光标当前的位置
		char c;
		printf("请输入管理员账号：");
		while ((c = getch()) != '\r')
		{
			if (isprint(c) && i < 20)	//如果是打印字符时
			{
				account[i] = c;
				putchar(c);
				i++;
			}
			else if (c == '\b' && i > 0)	//如果是退格字符时
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
		printf("请输入管理员密码：");
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
			printf("登陆成功！\n");
			printf("按任意键继续以下操作...");
			getchar();
			pass = 0;
			InitInterface();
		}
		else
		{
			printf("登陆失败！请重新输入账号和密码或返回\n");

			LABEL_BUNDLE labels;
			HOT_AREA areas;

			SMALL_RECT rcPop;
			COORD pos;
			WORD att;
			char *pCh[] = { "继续输入                          返回" };
			int iHot = 1;

			pos.X = strlen(pCh[0]) + 6;
			pos.Y = 7;
			rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
			rcPop.Right = rcPop.Left + pos.X - 7;
			rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
			rcPop.Bottom = rcPop.Top + pos.Y - 8;
			att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
* 函数名称: LoadData
* 函数功能: 将数据文件载入到内存缓冲区和十字链表中.
* 输入参数: 无
* 输出参数: 无
* 返 回 值: BOOL类型，返回TRUE则成功加载，返回FALSE则失败
* 函数说明：
*/
BOOL LoadData(void)
{
	int Re;
	Re = CreatList(&hd);
	if (Re<3)
	{  /*数据加载提示信息*/
		printf("\n系统基础数据不完整!\n");
		printf("\n按任意键继续...\n");
		getch();
		return FALSE;
	}

	return TRUE;
}

/**
* 函数名称: InitInterface
* 函数功能: 初始化界面.
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void InitInterface()
{
	WORD att = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY
		| BACKGROUND_GREEN;  /*黄色前景和绿色背景*/

	SetConsoleTextAttribute(gh_std_out, att);  /*设置控制台屏幕缓冲区字符属性*/

	ClearScreen();  /* 清屏*/

					/*创建弹出窗口信息堆栈，将初始化后的屏幕窗口当作第一层弹出窗口*/
	gp_scr_att = (char *)calloc(SCR_COL * SCR_ROW, sizeof(char));/*屏幕字符属性*/
	gp_top_layer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
	gp_top_layer->LayerNo = 0;      /*弹出窗口的层号为0*/
	gp_top_layer->rcArea.Left = 0;  /*弹出窗口的区域为整个屏幕窗口*/
	gp_top_layer->rcArea.Top = 0;
	gp_top_layer->rcArea.Right = SCR_COL - 1;
	gp_top_layer->rcArea.Bottom = SCR_ROW - 1;
	gp_top_layer->pContent = NULL;
	gp_top_layer->pScrAtt = gp_scr_att;
	gp_top_layer->next = NULL;

	ShowMenu();     /*显示菜单栏*/
	ShowState();    /*显示状态栏*/

	return;
}

/**
* 函数名称: ClearScreen
* 函数功能: 清除屏幕信息.
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void ClearScreen(void)
{
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	COORD home = { 0, 0 };
	unsigned long size;

	GetConsoleScreenBufferInfo(gh_std_out, &bInfo);/*取屏幕缓冲区信息*/
	size = bInfo.dwSize.X * bInfo.dwSize.Y; /*计算屏幕缓冲区字符单元数*/

											/*将屏幕缓冲区所有单元的字符属性设置为当前屏幕缓冲区字符属性*/
	FillConsoleOutputAttribute(gh_std_out, bInfo.wAttributes, size, home, &rec);

	/*将屏幕缓冲区所有单元填充为空格字符*/
	FillConsoleOutputCharacter(gh_std_out, ' ', size, home, &rec);

	return;
}

/**
* 函数名称: ShowMenu
* 函数功能: 在屏幕上显示主菜单, 并设置热区, 在主菜单第一项上置选中标记.
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*
* 调用说明:
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
	for (i = 0; i < 5; i++) /*在窗口第一行第一列处输出主菜单项*/
	{
		printf("  %s  ", ga_main_menu[i]);
	}

	GetConsoleCursorInfo(gh_std_out, &lpCur);
	lpCur.bVisible = FALSE;
	SetConsoleCursorInfo(gh_std_out, &lpCur);  /*隐藏光标*/

											   /*申请动态存储区作为存放菜单条屏幕区字符信息的缓冲区*/
	gp_buff_menubar_info = (CHAR_INFO *)malloc(size.X * size.Y * sizeof(CHAR_INFO));
	SMALL_RECT rcMenu = { 0, 0, size.X - 1, 0 };

	/*将窗口第一行的内容读入到存放菜单条屏幕区字符信息的缓冲区中*/
	ReadConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

	/*将这一行中英文字母置为红色，其他字符单元置为白底黑字*/
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

	/*修改后的菜单条字符信息回写到窗口的第一行*/
	WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);
	COORD endPos = { 0, 1 };
	SetConsoleCursorPosition(gh_std_out, endPos);  /*将光标位置设置在第2行第1列*/

												   /*将菜单项置为热区，热区编号为菜单项号，热区类型为0(按钮型)*/
	i = 0;
	do
	{
		PosB = PosA + strlen(ga_main_menu[i]);  /*定位第i+1号菜单项的起止位置*/
		for (j = PosA; j<PosB; j++)
		{
			gp_scr_att[j] |= (i + 1) << 2; /*设置菜单项所在字符单元的属性值*/
		}
		PosA = PosB + 4;
		i++;
	} while (i<5);

	TagMainMenu(gi_sel_menu);  /*在选中主菜单项上做标记，gi_sel_menu初值为1*/

	return;
}

/**
* 函数名称: ShowState
* 函数功能: 显示状态条.
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*
* 调用说明: 状态条字符属性为白底黑字, 初始状态无状态信息.
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
* 函数名称: TagMainMenu
* 函数功能: 在指定主菜单项上置选中标志.
* 输入参数: num 选中的主菜单项号
* 输出参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void TagMainMenu(int num)
{
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	COORD size;
	COORD pos = { 0, 0 };
	int PosA = 2, PosB;
	char ch;
	int i;

	if (num == 0) /*num为0时，将会去除主菜单项选中标记*/
	{
		PosA = 0;
		PosB = 0;
	}
	else  /*否则，定位选中主菜单项的起止位置: PosA为起始位置, PosB为截止位置*/
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

	/*去除选中菜单项前面的菜单项选中标记*/
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

	/*在选中菜单项上做标记，黑底白字*/
	for (i = PosA; i<PosB; i++)
	{
		(gp_buff_menubar_info + i)->Attributes = FOREGROUND_BLUE | FOREGROUND_GREEN
			| FOREGROUND_RED;
	}

	/*去除选中菜单项后面的菜单项选中标记*/
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

	/*将做好标记的菜单条信息写到窗口第一行*/
	SMALL_RECT rcMenu = { 0, 0, size.X - 1, 0 };
	WriteConsoleOutput(gh_std_out, gp_buff_menubar_info, size, pos, &rcMenu);

	return;
}

/**
* 函数名称: CloseSys
* 函数功能: 关闭系统.
* 输入参数: hd 主链头指针
* 输出参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void CloseSys(ESTATE_NODE *hd)
{
	ESTATE_NODE *pPremNode1 = hd, *pPremNode2;
	BUILD_NODE *pBuilNode1, *pBuilNode2;
	HOUSE_NODE *pHouseNode1, *pHouseNode2;

	while (pPremNode1 != NULL) /*释放十字交叉链表的动态存储区*/
	{
		pPremNode2 = pPremNode1->next;
		pBuilNode1 = pPremNode1->bnext;
		while (pBuilNode1 != NULL) /*释放楼栋基本信息支链的动态存储区*/
		{
			pBuilNode2 = pBuilNode1->next;
			pHouseNode1 = pBuilNode1->hnext;
			while (pHouseNode1 != NULL) /*释放房屋信息支链的动态存储区*/
			{
				pHouseNode2 = pHouseNode1->next;
				free(pHouseNode1);
				pHouseNode1 = pHouseNode2;
			}
			free(pBuilNode1);
			pBuilNode1 = pBuilNode2;
		}
		free(pPremNode1);  /*释放主链结点的动态存储区*/
		pPremNode1 = pPremNode2;
	}

	ClearScreen();        /*清屏*/

						  /*释放存放菜单条、状态条、性别代码和学生类别代码等信息动态存储区*/
	free(gp_buff_menubar_info);
	free(gp_buff_stateBar_info);

	/*关闭标准输入和输出设备句柄*/
	CloseHandle(gh_std_out);
	CloseHandle(gh_std_in);

	/*将窗口标题栏置为运行结束*/
	SetConsoleTitle("运行结束");

	return;
}


/**
* 函数名称: RunSys
* 函数功能: 运行系统, 在系统主界面下运行用户所选择的功能模块.
* 输入参数: 无
* 输出参数: phead 主链头指针的地址
* 返 回 值: 无
*
* 调用说明:
*/
void RunSys(ESTATE_NODE **phead)
{
	INPUT_RECORD inRec;
	DWORD res;
	COORD pos = { 0, 0 };
	BOOL bRet = TRUE;
	int i, loc, num;
	int cNo, cAtt;      /*cNo:字符单元层号, cAtt:字符单元属性*/
	char vkc, asc;      /*vkc:虚拟键代码, asc:字符的ASCII码值*/

	while (bRet)
	{
		/*从控制台输入缓冲区中读一条记录*/
		ReadConsoleInput(gh_std_in, &inRec, 1, &res);

		if (inRec.EventType == MOUSE_EVENT) /*如果记录由鼠标事件产生*/
		{
			pos = inRec.Event.MouseEvent.dwMousePosition;  /*获取鼠标坐标位置*/
			cNo = gp_scr_att[pos.Y * SCR_COL + pos.X] & 3; /*取该位置的层号*/
			cAtt = gp_scr_att[pos.Y * SCR_COL + pos.X] >> 2;/*取该字符单元属性*/
			if (cNo == 0) /*层号为0，表明该位置未被弹出子菜单覆盖*/
			{
				/* cAtt > 0 表明该位置处于热区(主菜单项字符单元)
				* cAtt != gi_sel_menu 表明该位置的主菜单项未被选中
				* gp_top_layer->LayerNo > 0 表明当前有子菜单弹出
				*/
				if (cAtt > 0 && cAtt != gi_sel_menu && gp_top_layer->LayerNo > 0)
				{
					PopOff();            /*关闭弹出的子菜单*/
					gi_sel_sub_menu = 0; /*将选中子菜单项的项号置为0*/
					PopMenu(cAtt);       /*弹出鼠标所在主菜单项对应的子菜单*/
				}
			}
			else if (cAtt > 0) /*鼠标所在位置为弹出子菜单的菜单项字符单元*/
			{
				TagSubMenu(cAtt); /*在该子菜单项上做选中标记*/
			}

			if (inRec.Event.MouseEvent.dwButtonState
				== FROM_LEFT_1ST_BUTTON_PRESSED) /*如果按下鼠标左边第一键*/
			{
				if (cNo == 0) /*层号为0，表明该位置未被弹出子菜单覆盖*/
				{
					if (cAtt > 0) /*如果该位置处于热区(主菜单项字符单元)*/
					{
						PopMenu(cAtt);   /*弹出鼠标所在主菜单项对应的子菜单*/
					}
					/*如果该位置不属于主菜单项字符单元，且有子菜单弹出*/
					else if (gp_top_layer->LayerNo > 0)
					{
						PopOff();            /*关闭弹出的子菜单*/
						gi_sel_sub_menu = 0; /*将选中子菜单项的项号置为0*/
					}
				}
				else /*层号不为0，表明该位置被弹出子菜单覆盖*/
				{
					if (cAtt > 0) /*如果该位置处于热区(子菜单项字符单元)*/
					{
						PopOff(); /*关闭弹出的子菜单*/
						gi_sel_sub_menu = 0; /*将选中子菜单项的项号置为0*/

											 /*执行对应功能函数:gi_sel_menu主菜单项号,cAtt子菜单项号*/
						bRet = ExeFunction(gi_sel_menu, cAtt);
					}
				}
			}
			else if (inRec.Event.MouseEvent.dwButtonState
				== RIGHTMOST_BUTTON_PRESSED) /*如果按下鼠标右键*/
			{
				if (cNo == 0) /*层号为0，表明该位置未被弹出子菜单覆盖*/
				{
					PopOff();            /*关闭弹出的子菜单*/
					gi_sel_sub_menu = 0; /*将选中子菜单项的项号置为0*/
				}
			}
		}
		else if (inRec.EventType == KEY_EVENT  /*如果记录由按键产生*/
			&& inRec.Event.KeyEvent.bKeyDown) /*且键被按下*/
		{
			vkc = inRec.Event.KeyEvent.wVirtualKeyCode; /*获取按键的虚拟键码*/
			asc = inRec.Event.KeyEvent.uChar.AsciiChar; /*获取按键的ASC码*/

														/*系统快捷键的处理*/
			if (vkc == 112) /*如果按下F1键*/
			{
				if (gp_top_layer->LayerNo != 0) /*如果当前有子菜单弹出*/
				{
					PopOff();            /*关闭弹出的子菜单*/
					gi_sel_sub_menu = 0; /*将选中子菜单项的项号置为0*/
				}
				bRet = ExeFunction(5, 1);  /*运行帮助主题功能函数*/
			}
			else if (inRec.Event.KeyEvent.dwControlKeyState
				& (LEFT_ALT_PRESSED | RIGHT_ALT_PRESSED))
			{ /*如果按下左或右Alt键*/
				switch (vkc)  /*判断组合键Alt+字母*/
				{
				case 88:  /*Alt+X 退出*/
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
			else if (asc == 0) /*其他控制键的处理*/
			{
				if (gp_top_layer->LayerNo == 0) /*如果未弹出子菜单*/
				{
					switch (vkc) /*处理方向键(左、右、下)，不响应其他控制键*/
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
				else  /*已弹出子菜单时*/
				{
					for (loc = 0, i = 1; i<gi_sel_menu; i++)
					{
						loc += ga_sub_menu_count[i - 1];
					}  /*计算该子菜单中的第一项在子菜单字符串数组中的位置(下标)*/
					switch (vkc) /*方向键(左、右、上、下)的处理*/
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
			else if ((asc - vkc == 0) || (asc - vkc == 32)) {  /*按下普通键*/
				if (gp_top_layer->LayerNo == 0)  /*如果未弹出子菜单*/
				{
					switch (vkc)
					{
					case 70: /*f或F*/
						PopMenu(1);
						break;
					case 77: /*m或M*/
						PopMenu(2);
						break;
					case 81: /*q或Q*/
						PopMenu(3);
						break;
					case 83: /*s或S*/
						PopMenu(4);
						break;
					case 72: /*h或H*/
						PopMenu(5);
						break;
					case 13: /*回车*/
						PopMenu(gi_sel_menu);
						TagSubMenu(1);
						break;
					}
				}
				else /*已弹出子菜单时的键盘输入处理*/
				{
					if (vkc == 27) /*如果按下ESC键*/
					{
						PopOff();
						gi_sel_sub_menu = 0;
					}
					else if (vkc == 13) /*如果按下回车键*/
					{
						num = gi_sel_sub_menu;
						PopOff();
						gi_sel_sub_menu = 0;
						bRet = ExeFunction(gi_sel_menu, num);
					}
					else /*其他普通键的处理*/
					{
						/*计算该子菜单中的第一项在子菜单字符串数组中的位置(下标)*/
						for (loc = 0, i = 1; i<gi_sel_menu; i++)
						{
							loc += ga_sub_menu_count[i - 1];
						}

						/*依次与当前子菜单中每一项的代表字符进行比较*/
						for (i = loc; i<loc + ga_sub_menu_count[gi_sel_menu - 1]; i++)
						{
							if (strlen(ga_sub_menu[i])>0 && vkc == ga_sub_menu[i][1])
							{ /*如果匹配成功*/
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
* 函数名称: PopMenu
* 函数功能: 弹出指定主菜单项对应的子菜单.
* 输入参数: num 指定的主菜单项号
* 输出参数: 无
* 返 回 值: 无
*
* 调用说明:
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

	if (num != gi_sel_menu)       /*如果指定主菜单不是已选中菜单*/
	{
		if (gp_top_layer->LayerNo != 0) /*如果此前已有子菜单弹出*/
		{
			PopOff();
			gi_sel_sub_menu = 0;
		}
	}
	else if (gp_top_layer->LayerNo != 0) /*若已弹出该子菜单，则返回*/
	{
		return;
	}

	gi_sel_menu = num;    /*将选中主菜单项置为指定的主菜单项*/
	TagMainMenu(gi_sel_menu); /*在选中的主菜单项上做标记*/
	LocSubMenu(gi_sel_menu, &rcPop); /*计算弹出子菜单的区域位置, 存放在rcPop中*/

									 /*计算该子菜单中的第一项在子菜单字符串数组中的位置(下标)*/
	for (i = 1; i<gi_sel_menu; i++)
	{
		loc += ga_sub_menu_count[i - 1];
	}
	/*将该组子菜单项项名存入标签束结构变量*/
	labels.ppLabel = ga_sub_menu + loc;   /*标签束第一个标签字符串的地址*/
	labels.num = ga_sub_menu_count[gi_sel_menu - 1]; /*标签束中标签字符串的个数*/
	COORD* aLoc = (COORD*)calloc(sizeof(COORD), labels.num);/*定义一个坐标数组，存放每个标签字符串输出位置的坐标*/
	for (i = 0; i<labels.num; i++) /*确定标签字符串的输出位置，存放在坐标数组中*/
	{
		aLoc[i].X = rcPop.Left + 2;
		aLoc[i].Y = rcPop.Top + i + 1;
	}
	labels.pLoc = aLoc; /*使标签束结构变量labels的成员pLoc指向坐标数组的首元素*/
						/*设置热区信息*/
	areas.num = labels.num;       /*热区的个数，等于标签的个数，即子菜单的项数*/
	SMALL_RECT *aArea = (SMALL_RECT*)calloc(sizeof(SMALL_RECT), areas.num);                    /*定义数组存放所有热区位置*/
	char *aSort = (char*)calloc(sizeof(char), areas.num);                      /*定义数组存放所有热区对应类别*/
	char *aTag = (char*)calloc(sizeof(char), areas.num);                         /*定义数组存放每个热区的编号*/
	for (i = 0; i<areas.num; i++)
	{
		aArea[i].Left = rcPop.Left + 2;  /*热区定位*/
		aArea[i].Top = rcPop.Top + i + 1;
		aArea[i].Right = rcPop.Right - 2;
		aArea[i].Bottom = aArea[i].Top;
		aSort[i] = 0;       /*热区类别都为0(按钮型)*/
		aTag[i] = i + 1;           /*热区按顺序编号*/
	}
	areas.pArea = aArea;/*使热区结构变量areas的成员pArea指向热区位置数组首元素*/
	areas.pSort = aSort;/*使热区结构变量areas的成员pSort指向热区类别数组首元素*/
	areas.pTag = aTag;   /*使热区结构变量areas的成员pTag指向热区编号数组首元素*/

	att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
	PopUp(&rcPop, att, &labels, &areas);
	DrawBox(&rcPop);  /*给弹出窗口画边框*/
	pos.X = rcPop.Left + 2;
	for (pos.Y = rcPop.Top + 1; pos.Y<rcPop.Bottom; pos.Y++)
	{ /*此循环用来在空串子菜项位置画线形成分隔，并取消此菜单项的热区属性*/
		pCh = ga_sub_menu[loc + pos.Y - rcPop.Top - 1];
		if (strlen(pCh) == 0) /*串长为0，表明为空串*/
		{   /*首先画横线*/
			FillConsoleOutputCharacter(gh_std_out, '-', rcPop.Right - rcPop.Left - 3, pos, &rec);
			for (j = rcPop.Left + 2; j<rcPop.Right - 1; j++)
			{   /*取消该区域字符单元的热区属性*/
				gp_scr_att[pos.Y*SCR_COL + j] &= 3; /*按位与的结果保留了低两位*/
			}
		}

	}
	/*将子菜单项的功能键设为白底红字*/
	pos.X = rcPop.Left + 3;
	att = FOREGROUND_RED | BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;
	for (pos.Y = rcPop.Top + 1; pos.Y<rcPop.Bottom; pos.Y++)
	{
		if (strlen(ga_sub_menu[loc + pos.Y - rcPop.Top - 1]) == 0)
		{
			continue;  /*跳过空串*/
		}
		FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &rec);
	}
	return;
}

/**
* 函数名称: PopUp
* 函数功能: 在指定区域输出弹出窗口信息, 同时设置热区, 将弹出窗口位置信息入栈.
* 输入参数: pRc 弹出窗口位置数据存放的地址
*           att 弹出窗口区域字符属性
*           pLabel 弹出窗口中标签束信息存放的地址
pHotArea 弹出窗口中热区信息存放的地址
* 输出参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void PopUp(SMALL_RECT *pRc, WORD att, LABEL_BUNDLE *pLabel, HOT_AREA *pHotArea)
{
	LAYER_NODE *nextLayer;
	COORD size;
	COORD pos = { 0, 0 };
	char *pCh;
	int i, j, row;

	/*弹出窗口所在位置字符单元信息入栈*/
	size.X = pRc->Right - pRc->Left + 1;    /*弹出窗口的宽度*/
	size.Y = pRc->Bottom - pRc->Top + 1;    /*弹出窗口的高度*/
											/*申请存放弹出窗口相关信息的动态存储区*/
	nextLayer = (LAYER_NODE *)malloc(sizeof(LAYER_NODE));
	nextLayer->next = gp_top_layer;
	nextLayer->LayerNo = gp_top_layer->LayerNo + 1;
	nextLayer->rcArea = *pRc;
	nextLayer->pContent = (CHAR_INFO *)malloc(size.X*size.Y * sizeof(CHAR_INFO));
	nextLayer->pScrAtt = (char *)malloc(size.X*size.Y * sizeof(char));
	pCh = nextLayer->pScrAtt;
	/*将弹出窗口覆盖区域的字符信息保存，用于在关闭弹出窗口时恢复原样*/
	ReadConsoleOutput(gh_std_out, nextLayer->pContent, size, pos, pRc);
	for (i = pRc->Top; i <= pRc->Bottom; i++)
	{   /*此二重循环将所覆盖字符单元的原先属性值存入动态存储区，便于以后恢复*/
		for (j = pRc->Left; j <= pRc->Right; j++)
		{
			*pCh = gp_scr_att[i*SCR_COL + j];
			pCh++;
		}
	}
	gp_top_layer = nextLayer;  /*完成弹出窗口相关信息入栈操作*/
							   /*设置弹出窗口区域字符的新属性*/
	pos.X = pRc->Left;
	pos.Y = pRc->Top;
	for (i = pRc->Top; i <= pRc->Bottom; i++)
	{
		FillConsoleOutputAttribute(gh_std_out, att, size.X, pos, &rec);
		pos.Y++;
	}
	/*将标签束中的标签字符串在设定的位置输出*/
	for (i = 0; i<pLabel->num; i++)
	{
		pCh = pLabel->ppLabel[i];
		if (strlen(pCh) != 0)
		{
			WriteConsoleOutputCharacter(gh_std_out, pCh, strlen(pCh),
				pLabel->pLoc[i], &rec);
		}
	}
	/*设置弹出窗口区域字符单元的新属性*/
	for (i = pRc->Top; i <= pRc->Bottom; i++)
	{   /*此二重循环设置字符单元的层号*/
		for (j = pRc->Left; j <= pRc->Right; j++)
		{
			gp_scr_att[i*SCR_COL + j] = gp_top_layer->LayerNo;
		}
	}

	for (i = 0; i<pHotArea->num; i++)
	{   /*此二重循环设置所有热区中字符单元的热区类型和热区编号*/
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
* 函数名称: PopOff
* 函数功能: 关闭顶层弹出窗口, 恢复覆盖区域原外观和字符单元原属性.
* 输入参数: 无
* 输出参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void PopOff(void)
{
	LAYER_NODE *nextLayer;
	COORD size;
	COORD pos = { 0, 0 };
	char *pCh;
	int i, j;

	if ((gp_top_layer->next == NULL) || (gp_top_layer->pContent == NULL))
	{   /*栈底存放的主界面屏幕信息，不用关闭*/
		return;
	}
	nextLayer = gp_top_layer->next;
	/*恢复弹出窗口区域原外观*/
	size.X = gp_top_layer->rcArea.Right - gp_top_layer->rcArea.Left + 1;
	size.Y = gp_top_layer->rcArea.Bottom - gp_top_layer->rcArea.Top + 1;
	WriteConsoleOutput(gh_std_out, gp_top_layer->pContent, size, pos, &(gp_top_layer->rcArea));
	/*恢复字符单元原属性*/
	pCh = gp_top_layer->pScrAtt;
	for (i = gp_top_layer->rcArea.Top; i <= gp_top_layer->rcArea.Bottom; i++)
	{
		for (j = gp_top_layer->rcArea.Left; j <= gp_top_layer->rcArea.Right; j++)
		{
			gp_scr_att[i*SCR_COL + j] = *pCh;
			pCh++;
		}
	}
	free(gp_top_layer->pContent);    /*释放动态存储区*/
	free(gp_top_layer->pScrAtt);
	free(gp_top_layer);
	gp_top_layer = nextLayer;
	gi_sel_sub_menu = 0;
	return;
}

/**
* 函数名称: DrawBox
* 函数功能: 在指定区域画边框.
* 输入参数: pRc 存放区域位置信息的地址
* 输出参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void DrawBox(SMALL_RECT *pRc)
{
	char chBox[] = { '+','-','|' };  /*画框用的字符*/
	COORD pos = { pRc->Left, pRc->Top };  /*定位在区域的左上角*/

	WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &rec);/*画边框左上角*/
	for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
	{   /*此循环画上边框横线*/
		WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &rec);
	}
	pos.X = pRc->Right;
	WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &rec);/*画边框右上角*/
	for (pos.Y = pRc->Top + 1; pos.Y < pRc->Bottom; pos.Y++)
	{   /*此循环画边框左边线和右边线*/
		pos.X = pRc->Left;
		WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &rec);
		pos.X = pRc->Right;
		WriteConsoleOutputCharacter(gh_std_out, &chBox[2], 1, pos, &rec);
	}
	pos.X = pRc->Left;
	pos.Y = pRc->Bottom;
	WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &rec);/*画边框左下角*/
	for (pos.X = pRc->Left + 1; pos.X < pRc->Right; pos.X++)
	{   /*画下边框横线*/
		WriteConsoleOutputCharacter(gh_std_out, &chBox[1], 1, pos, &rec);
	}
	pos.X = pRc->Right;
	WriteConsoleOutputCharacter(gh_std_out, &chBox[0], 1, pos, &rec);/*画边框右下角*/
	return;
}


/**
* 函数名称: TagSubMenu
* 函数功能: 在指定子菜单项上做选中标记.
* 输入参数: num 选中的子菜单项号
* 输出参数: 无
* 返 回 值: 无
*
* 调用说明:
*/
void TagSubMenu(int num)
{
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;
	int width;

	LocSubMenu(gi_sel_menu, &rcPop);  /*计算弹出子菜单的区域位置, 存放在rcPop中*/
	if ((num<1) || (num == gi_sel_sub_menu) || (num>rcPop.Bottom - rcPop.Top - 1))
	{   /*如果子菜单项号越界，或该项子菜单已被选中，则返回*/
		return;
	}

	pos.X = rcPop.Left + 2;
	width = rcPop.Right - rcPop.Left - 3;
	if (gi_sel_sub_menu != 0) /*首先取消原选中子菜单项上的标记*/
	{
		pos.Y = rcPop.Top + gi_sel_sub_menu;
		att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
		FillConsoleOutputAttribute(gh_std_out, att, width, pos, &rec);
		pos.X += 1;
		att |= FOREGROUND_RED;/*白底红字*/
		FillConsoleOutputAttribute(gh_std_out, att, 1, pos, &rec);
	}
	/*在制定子菜单项上做选中标记*/
	pos.X = rcPop.Left + 2;
	pos.Y = rcPop.Top + num;
	att = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*黑底白字*/
	FillConsoleOutputAttribute(gh_std_out, att, width, pos, &rec);
	gi_sel_sub_menu = num;  /*修改选中子菜单项号*/
	return;
}

/**
* 函数名称: LocSubMenu
* 函数功能: 计算弹出子菜单区域左上角和右下角的位置.
* 输入参数: num 选中的主菜单项号
* 输出参数: rc 存放区域位置信息的地址
* 返 回 值: 无
*
* 调用说明:
*/
void LocSubMenu(int num, SMALL_RECT *rc)
{
	int i, len, loc = 0;

	rc->Top = 1; /*区域的上边定在第2行，行号为1*/
	rc->Left = 1;
	for (i = 1; i<num; i++)
	{   /*计算区域左边界位置, 同时计算第一个子菜单项在子菜单字符串数组中的位置*/
		rc->Left += strlen(ga_main_menu[i - 1]) + 4;
		loc += ga_sub_menu_count[i - 1];
	}
	rc->Right = strlen(ga_sub_menu[loc]);/*暂时存放第一个子菜单项字符串长度*/
	for (i = 1; i<ga_sub_menu_count[num - 1]; i++)
	{   /*查找最长子菜单字符串，将其长度存放在rc->Right*/
		len = strlen(ga_sub_menu[loc + i]);
		if (rc->Right < len)
		{
			rc->Right = len;
		}
	}
	rc->Right += rc->Left + 3;  /*计算区域的右边界*/
	rc->Bottom = rc->Top + ga_sub_menu_count[num - 1] + 1;/*计算区域下边的行号*/
	if (rc->Right >= SCR_COL)  /*右边界越界的处理*/
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
	int cNo, cTag, cSort;/*cNo:层号, cTag:热区编号, cSort: 热区类型*/
	char vkc, asc;       /*vkc:虚拟键代码, asc:字符的ASCII码值*/

	SetHotPoint(pHotArea, *piHot);
	while (TRUE)
	{    /*循环*/
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
				{  /*方向键(左、上、右、下)的处理*/
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
			{  /*ESC键*/
				iRet = 27;
				break;
			}
			else if (vkc == 13 || vkc == 32)
			{  /*回车键或空格表示按下当前按钮*/
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

	att1 = FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED;  /*黑底白字*/
	att2 = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
	for (i = 0; i<pHotArea->num; i++)
	{  /*将按钮类热区置为白底黑字*/
		pos.X = pHotArea->pArea[i].Left;
		pos.Y = pHotArea->pArea[i].Top;
		width = pHotArea->pArea[i].Right - pHotArea->pArea[i].Left + 1;
		if (pHotArea->pSort[i] == 0)
		{  /*热区是按钮类*/
			FillConsoleOutputAttribute(gh_std_out, att2, width, pos, &rec);
		}
	}

	pos.X = pHotArea->pArea[iHot - 1].Left;
	pos.Y = pHotArea->pArea[iHot - 1].Top;
	width = pHotArea->pArea[iHot - 1].Right - pHotArea->pArea[iHot - 1].Left + 1;
	if (pHotArea->pSort[iHot - 1] == 0)
	{  /*被激活热区是按钮类*/
		FillConsoleOutputAttribute(gh_std_out, att1, width, pos, &rec);
	}
	else if (pHotArea->pSort[iHot - 1] == 1)
	{  /*被激活热区是文本框类*/
		SetConsoleCursorPosition(gh_std_out, pos);
		GetConsoleCursorInfo(gh_std_out, &lpCur);
		lpCur.bVisible = TRUE;
		SetConsoleCursorInfo(gh_std_out, &lpCur);
	}
}

/**
* 函数名称: ExeFunction
* 函数功能: 执行由主菜单号和子菜单号确定的功能函数.
* 输入参数: m 主菜单项号
*           s 子菜单项号
* 输出参数: 无
* 返 回 值: BOOL类型, TRUE 或 FALSE
*
* 调用说明: 仅在执行函数ExitSys时, 才可能返回FALSE, 其他情况下总是返回TRUE
*/
BOOL ExeFunction(int m, int s)
{
	InitInterface();
	BOOL bRet = TRUE;
	/*函数指针数组，用来存放所有功能函数的入口地址*/
	BOOL(**pFunction)(void);
	pFunction = (BOOL(**)(void))calloc(sizeof(BOOL(*)(void)),
		ga_sub_menu_count[0] + ga_sub_menu_count[1] + ga_sub_menu_count[2] + ga_sub_menu_count[3] + ga_sub_menu_count[4]);
	int i, loc;

	/*将功能函数入口地址存入与功能函数所在主菜单号和子菜单号对应下标的数组元素*/
	/*文件*/
	pFunction[0] = SaveData;
	pFunction[1] = BackupData;
	pFunction[2] = RestoreData;
	pFunction[3] = ExitSys;
	/*数据维护*/
	pFunction[4] = AddData;
	pFunction[5] = DeleteData;
	pFunction[6] = ModifyData;
	/*数据查询*/
	pFunction[7] = StatCity;
	pFunction[8] = StatType;
	pFunction[9] = StatPrice;
	/*数据统计*/
	pFunction[10] = ShowAllEstate;
	pFunction[11] = ShowAllHouse;
	/*帮助*/
	pFunction[12] = HelpTopic;
	pFunction[13] = NULL;
	pFunction[14] = About;

	for (i = 1, loc = 0; i<m; i++)  /*根据主菜单号和子菜单号计算对应下标*/
	{
		loc += ga_sub_menu_count[i - 1];
	}
	loc += s - 1;

	if (pFunction[loc] != NULL)
	{
		bRet = (*pFunction[loc])();  /*用函数指针调用所指向的功能函数*/
	}

	return bRet;
}

/**
*函数名称：SaveData
*函数功能：保存数据
*输入参数：无
*输出参数：无
*返回值：BOOL类型，始终返回TRUE
*函数说明：
*/
BOOL SaveData(void)
{
	FILE *fp_estate, *fp_build, *fp_house;
	ESTATE_NODE * pestate;
	BUILD_NODE * pbuild;
	HOUSE_NODE * phouse;

	/*储存楼盘信息*/
	if ((fp_estate = fopen(gp_estate_info_filename, "wb")) == NULL)
	{
		fputs("打开楼盘数据文件出错！", stderr);
		exit(EXIT_FAILURE);
	}
	pestate = hd;
	while (pestate)
	{
		fwrite(pestate, sizeof(ESTATE_NODE), 1, fp_estate);
		pestate = pestate->next;
	}

	/*储存楼栋信息*/
	if ((fp_build = fopen(gp_build_info_filename, "wb")) == NULL)
	{
		fputs("打开楼栋数据文件出错！", stderr);
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

	/*储存房屋信息*/
	if ((fp_house = fopen(gp_house_info_filename, "wb")) == NULL)
	{
		fputs("打开房屋数据文件出错！", stderr);
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
	printf("储存成功！\n");
	printf("--------------------------------------------------------------------------------");
	printf("按任意键继续...");
	getch();
	InitInterface();
	return TRUE;
}

/**
*函数名称：BackupData
*函数功能：备份数据，将数据另存为新文件
*输入参数：无
*输出参数：无
*返回值：BOOL类型，始终返回TRUE
*/
BOOL BackupData(void)
{
	int flag, deal1 = 1;
	FILE * newfp, *oldfp;//申请新旧两个文件指针
	char filename[255];
	ESTATE_NODE* pestate = (ESTATE_NODE*)malloc(sizeof(ESTATE_NODE));
	BUILD_NODE* pbuild = (BUILD_NODE*)malloc(sizeof(BUILD_NODE));
	HOUSE_NODE* phouse = (HOUSE_NODE*)malloc(sizeof(HOUSE_NODE));
	LABEL_BUNDLE labels;
	HOT_AREA areas;
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;

	printf("选择你要备份的信息数据项：\n");
	char *pCh[] = { "1、备份楼盘数据","2、备份楼栋数据", "3、备份房屋数据" };

	int iHot = 3;
	pos.X = strlen(pCh[0]) + 10;
	pos.Y = 12;
	rcPop.Left = (SCR_COL - pos.X) / 2;
	rcPop.Right = rcPop.Left + pos.X - 1;
	rcPop.Top = (25 - pos.Y) / 2;
	rcPop.Bottom = rcPop.Top + pos.Y - 1;

	att = BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
		/*精确查询*/
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
		printf("输入你要存储的路径和文件名，例如：C:\\Users\\***\\Desktop\\**.dat\n");
		printf("文件路径&文件名： ");
		scanf("%s", filename);
		while (getchar() != '\n');
		printf("--------------------------------------------------------------------------------");
		if ((newfp = fopen(filename, "wb")) == NULL)//打开新文件
		{
			fputs("文件路径或文件名无效！请重新输入！", stderr);
		}
		else
		{
			switch (flag)
			{
			case 1:
			{
				if ((oldfp = fopen(gp_estate_info_filename, "rb")) == NULL)
				{
					fputs("打开楼盘信息文件错误！", stderr);
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
					fputs("打开楼栋信息文件错误！", stderr);
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
					fputs("打开房屋信息文件错误！", stderr);
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
			printf("备份成功！\n");
			printf("按任意键继续...");
			getch();
			InitInterface();
			return TRUE;
		}


		char *pCh[] = { "继续输入                          返回" };
		iHot = 1;

		pos.X = strlen(pCh[0]) + 6;
		pos.Y = 7;
		rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
		rcPop.Right = rcPop.Left + pos.X - 7;
		rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
		rcPop.Bottom = rcPop.Top + pos.Y - 8;
		att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
*函数名称：RestoreData
*函数功能：将备份的数据重新加载，恢复数据
*输入参数：无
*输出参数：无
*返回值：BOOL类型，始终返回TRUE
*/
BOOL RestoreData(void)
{
	int flag, deal1 = 1;
	FILE * newfp, *oldfp;//申请新旧两个文件指针
	char filename[255];
	ESTATE_NODE* pestate = (ESTATE_NODE*)malloc(sizeof(ESTATE_NODE));
	BUILD_NODE* pbuild = (BUILD_NODE*)malloc(sizeof(BUILD_NODE));
	HOUSE_NODE* phouse = (HOUSE_NODE*)malloc(sizeof(HOUSE_NODE));
	LABEL_BUNDLE labels;
	HOT_AREA areas;
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;

	printf("选择你要还原的信息数据项：\n");
	char *pCh[] = { "1、还原楼盘数据","2、还原楼栋数据", "3、还原房屋数据" };

	int iHot = 3;
	pos.X = strlen(pCh[0]) + 10;
	pos.Y = 12;
	rcPop.Left = (SCR_COL - pos.X) / 2;
	rcPop.Right = rcPop.Left + pos.X - 1;
	rcPop.Top = (25 - pos.Y) / 2;
	rcPop.Bottom = rcPop.Top + pos.Y - 1;

	att = BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
		/*精确查询*/
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
		printf("输入你要还原的路径和文件名，例如：C:\\Users\\***\\Desktop\\**.dat\n");
		printf("文件路径&文件名： ");
		scanf("%s", filename);
		while (getchar() != '\n');
		printf("--------------------------------------------------------------------------------");
		if ((newfp = fopen(filename, "rb")) == NULL)//打开新文件
		{
			fputs("未找到该文件，请确认文件路劲和文件名并重新输入！", stderr);
		}
		else
		{
			switch (flag)
			{
			case 1:
			{
				if ((oldfp = fopen(gp_estate_info_filename, "wb")) == NULL)
				{
					fputs("打开楼盘信息文件错误！", stderr);
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
					fputs("打开楼栋信息文件错误！", stderr);
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
					fputs("打开房屋信息文件错误！", stderr);
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
			printf("还原成功！\n");
			printf("按任意键继续...");
			getch();
			InitInterface();
			return TRUE;
		}


		char *pCh[] = { "继续输入                          返回" };
		iHot = 1;

		pos.X = strlen(pCh[0]) + 6;
		pos.Y = 7;
		rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
		rcPop.Right = rcPop.Left + pos.X - 7;
		rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
		rcPop.Bottom = rcPop.Top + pos.Y - 8;
		att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
*函数名称：ExitSys
*函数功能：退出系统
*输入参数：无
*输出参数：无
*返回值：BOOL类型，根据用户选择返回TRUE或FALSE
*/
BOOL ExitSys(void)
{
	LABEL_BUNDLE labels;
	HOT_AREA areas;
	BOOL bRet = TRUE;
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;
	char *pCh[] = { "确认退出系统吗？", "确定    取消" };
	int iHot = 1;

	pos.X = strlen(pCh[0]) + 6;
	pos.Y = 7;
	rcPop.Left = (SCR_COL - pos.X) / 2;
	rcPop.Right = rcPop.Left + pos.X - 1;
	rcPop.Top = (SCR_ROW - pos.Y) / 2;
	rcPop.Bottom = rcPop.Top + pos.Y - 1;

	att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
*函数名称：Creatlist
*函数功能：从文件中读取基础数据，并存放到所创建的十字链表中
*输入参数：主链头指针地址phead
*返回值：int型数据，0表示空链，1表示加载楼盘信息，2表示加载楼盘和楼栋信息，3表示加载楼盘，楼栋和房屋信息
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
		printf("楼盘信息数据文件打开失败!\n");
		return num;
	}
	printf("楼盘信息数据文件打开成功!\n");

	/*从数据文件中读取楼盘信息数据，存入以后进先出方式建立的主链中*/
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
		printf("楼盘信息数据文件加载失败!\n");
		return num;
	}
	printf("楼盘信息数据文件加载成功!\n");
	*phead = hd;
	num++;
	if ((pFile = fopen(gp_build_info_filename, "rb")) == NULL)
	{
		printf("楼栋信息数据文件打开失败!\n");
		return num;
	}
	printf("楼栋信息数据文件打开成功!\n");
	num++;

	/*从数据文件中读取楼栋信息数据存入主链对应结点的学生基本信息支链中*/
	pBuildNode = (BUILD_NODE*)malloc(sizeof(BUILD_NODE));
	fread(pBuildNode, sizeof(BUILD_NODE), 1, pFile);
	while (!feof(pFile))
	{
		pBuildNode->hnext = NULL;

		/*在主链上查找楼栋对应的楼盘主链结点*/
		pEstateNode = hd;
		while (pEstateNode != NULL&&strcmp(pEstateNode->estate_id, pBuildNode->estate_id) != 0)
		{
			pEstateNode = pEstateNode->next;
		}

		/*如果找到，则将结点以后进先出方式插入楼栋信息支链*/
		if (pEstateNode != NULL)
		{
			pBuildNode->next = pEstateNode->bnext;
			pEstateNode->bnext = pBuildNode;
		}
		else  /*如果未找到，则释放所创建结点的内存空间*/
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
		printf("房屋信息数据文件打开失败!\n");
		return num;
	}
	printf("房屋信息数据文件打开成功!\n");
	num++;
	/*从数据文件中读取房屋信息数据存入楼栋信息对应结点的房屋信息支链中*/
	pHouseNode = (HOUSE_NODE*)malloc(sizeof(HOUSE_NODE));
	fread(pHouseNode, sizeof(HOUSE_NODE), 1, pFile);
	while (!feof(pFile))
	{
		/*在楼栋支链上查找该房屋所在楼栋对应的结点*/
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
		if (find)  /*如果找到则将结点以后进先出方式插入房屋信息支链中*/
		{
			pHouseNode->next = pBuildNode->hnext;
			pBuildNode->hnext = pHouseNode;
		}
		else    /*如果未找到，则释放所创建结点的内存空间*/
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
*函数名称：SeekEstateNode
*函数功能：根据楼盘编号查询对应结点
*输入参数：主链头指针head,楼盘编号

*函数说明：
*返回值：对应的楼盘结点，未找到返回空指针
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
*函数名称：SeekBuildNode
*函数功能：根据楼盘编号,楼栋编号查询对应结点
*输入参数：主链头指针head，楼盘编号，楼栋编号
*输出参数：无
*返回值：对应的楼栋结点，未找到返回空指针
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
*函数名称：SeekHouseNode
*函数功能：根据楼盘编号,楼栋编号，房屋编号查询对应结点
*输入参数：主链头指针head，楼盘编号，楼栋编号，房屋编号
*输出参数：无
*返回值：对应的房屋结点，未找到返回空指针
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
*函数名称：DelHouseNode
*函数功能：在十字链表中删除指定的房屋信息结点
*输入参数：hd主链头指针，楼盘编号，楼栋编号，房屋编号
*输出参数：无
*返回值：BOOL型数据，TRUE表示删除成功，FALSE表示删除失败
*函数说明：
*/
BOOL DelHouseNode(ESTATE_NODE*head, char* estateid, char* buildid, char* houseid)
{
	BUILD_NODE* pbuild;
	HOUSE_NODE* p, *pbefore;
	pbuild = SeekBuildNode(head, estateid, buildid);//定位到对应楼栋结点
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
		//找到且为p所定位
		if (p == pbuild->hnext)  //如果被删结点是头指针
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
*函数名称：DelBuildNode
*函数功能：在十字链表中删除指定的楼栋信息结点
*输入参数：主链头指针，楼盘编号，楼栋编号
*输出参数：无
*函数说明：
*返回值：BOOL型数据，TRUE表示删除成功，FALSE表示删除失败
*/
BOOL DelBuildNode(ESTATE_NODE*head, char* estateid, char* buildid)
{
	ESTATE_NODE* pestate;
	BUILD_NODE* p, *pbefore;
	pestate = SeekEstateNode(head, estateid);//定位到对应楼盘结点
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
		//找到且为p所定位
		if (p == pestate->bnext)  //如果被删结点是头指针
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
*函数名称：DelEstatelNode
*函数功能：在十字链表中删除指定的楼盘信息结点
*输入参数：指向主链头指针的指针，楼盘编号
*函数说明：
*返回值：BOOL型数据，TRUE表示删除成功，FALSE表示删除失败
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
	//找到且为p所定位
	if (p == *phead)  //如果被删结点是头指针
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
* 函数名称：AddData
* 函数功能：向内存数据中增添新的数据项
* 输入参数：无
* 输出参数：无
* 返回值：无
* 函数说明：
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
		char *pCh[] = { "1、添加楼盘数据","2、添加楼栋数据", "3、添加房屋数据" };
		int iHot = 3;
		int find;

		pos.X = strlen(pCh[0]) + 10;
		pos.Y = 12;
		rcPop.Left = (SCR_COL - pos.X) / 2;
		rcPop.Right = rcPop.Left + pos.X - 1;
		rcPop.Top = (25 - pos.Y) / 2;
		rcPop.Bottom = rcPop.Top + pos.Y - 1;

		att = BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
			/*精确查询*/
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
			case 1:/*添加楼盘数据*/
			{
				newestate = (ESTATE_NODE*)malloc(sizeof(ESTATE_NODE));
				printf("--------------------------------------------------------------------------------");
				find = 1;
				while (find)
				{
					printf("\t输入楼盘编号（不超过9位数）\t");
					scanf("%9s", newestate->estate_id);
					while (getchar() != '\n');		/*如果输入超过限制，通过该语句刷新输入缓冲区*/
					estate = hd;
					while (estate != NULL&&strcmp(estate->estate_id, newestate->estate_id) != 0)
						estate = estate->next;
					if (estate != NULL)
					{
						find = 1;
						printf("\t对不起，您输入的楼盘编号已存在，请重新输入!\n");
					}
					else
						find = 0;
					printf("--------------------------------------------------------------------------------");
				}
				printf("\t输入楼盘名称\t\t\t");
				scanf("%19s", newestate->name);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t输入城区\t\t\t");
				scanf("%9s", newestate->city);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t输入楼盘地址\t\t\t");
				scanf("%29s", newestate->address);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t输入开发商\t\t\t");
				scanf("%19s", newestate->developer);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t输入物业公司\t\t\t");
				scanf("%19s", newestate->management_company);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				newestate->bnext = NULL;
				newestate->next = hd;
				hd = newestate;
				printf("\t\t\t\t\t\t\t插入成功");
				break;
			}
			case 2:/*添加楼栋数据*/
			{
				newbuild = (BUILD_NODE*)malloc(sizeof(BUILD_NODE));
				find = 1;
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入对应楼盘编号\t");
				scanf("%9s", newbuild->estate_id);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入楼栋编号\t\t");
				scanf("%9s", newbuild->build_id);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入单元数\t\t");
				scanf("%d", &newbuild->unit);
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入楼层\t\t");
				scanf("%d", &newbuild->floor);
				printf("--------------------------------------------------------------------------------");
				newbuild->hnext = NULL;
				newbuild->next = NULL;
				ESTATE_NODE *pestate = SeekEstateNode(hd, newbuild->estate_id);
				if (pestate == NULL)
				{
					free(newbuild);
					printf("\t\t\t输入有误，该楼栋所对应的楼盘不存在，插入失败\n");
				}
				else
				{
					newbuild->next = pestate->bnext;
					pestate->bnext = newbuild;
					printf("\t\t\t\t\t\t\t插入成功\n");
				}
				break;
			}
			case 3:/*添加房屋数据*/
			{
				newhouse = (HOUSE_NODE*)malloc(sizeof(HOUSE_NODE));
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入楼盘编号\t\t");
				scanf("%9s", newhouse->estate_id);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入楼栋编号\t\t");
				scanf("%9s", newhouse->build_id);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入房屋编号\t\t");
				scanf("%9s", newhouse->house_id);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入户型\t\t");
				scanf("%19s", newhouse->type);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入面积(m*m)\t\t");
				scanf("%d", &newhouse->area);
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入公摊率\t\t");
				scanf("%f", &newhouse->shared_rate);
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入单位面积价格（元/(m*m)）\t");
				scanf("%d", &newhouse->one_price);
				printf("--------------------------------------------------------------------------------");
				newhouse->next = NULL;
				BUILD_NODE* pbuild = SeekBuildNode(hd, newhouse->estate_id, newhouse->build_id);
				if (pbuild == NULL)
				{
					free(newhouse);
					printf("\t\t\t输入有误，该房屋所对应的楼栋不存在，插入失败\n");
				}
				else
				{
					newhouse->next = pbuild->hnext;
					pbuild->hnext = newhouse;
					printf("\t\t\t\t\t\t插入成功\n");
				}
				break;
			}
			default:
			{
				printf("--------------------------------------------------------------------------------");
				printf("\t\t\t\t输入功能编号有误\n");
			}
			}
			LABEL_BUNDLE labels;
			HOT_AREA areas;

			SMALL_RECT rcPop;
			COORD pos;
			WORD att;
			char *pCh[] = { "继续插入                          返回" };
			int iHot = 1;

			pos.X = strlen(pCh[0]) + 6;
			pos.Y = 7;
			rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
			rcPop.Right = rcPop.Left + pos.X - 7;
			rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
			rcPop.Bottom = rcPop.Top + pos.Y - 8;
			att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
* 函数名称：DeletData
* 函数功能：删除楼盘、楼栋或房屋结点数据
* 输入参数：无
* 输出参数：无
* 返回值：BOOL类型，始终返回TRUE
* 函数说明：
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
		char *pCh[] = { "1、删除楼盘数据","2、删除楼栋数据", "3、删除房屋数据" };
		int iHot = 3;

		pos.X = strlen(pCh[0]) + 10;
		pos.Y = 12;
		rcPop.Left = (SCR_COL - pos.X) / 2;
		rcPop.Right = rcPop.Left + pos.X - 1;
		rcPop.Top = (25 - pos.Y) / 2;
		rcPop.Bottom = rcPop.Top + pos.Y - 1;

		att = BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
			/*精确查询*/
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
			case 1:/*删除楼盘数据*/
			{
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入您想要删除的楼盘编号\t\t");
				scanf("%9s", estateid);
				while (getchar() != '\n');
				if (DelEstateNode(&hd, estateid))
				{
					printf("--------------------------------------------------------------------------------");
					printf("\t\t\t\t\t已删除对应楼盘\n");
				}
				else
				{
					printf("--------------------------------------------------------------------------------");
					printf("\t\t\t\t\t未找到对应的楼盘\n");
				}
				break;
			}
			case 2:/*删除楼栋数据*/
			{
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入楼盘编号\t\t");
				scanf("%9s", estateid);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入楼栋编号\t\t");
				scanf("%9s", buildid);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				if (DelBuildNode(hd, estateid, buildid))
				{
					printf("\t\t\t\t\t已删除对应楼栋\n");
				}
				else
				{
					printf("\t\t\t\t\t未找到对应的楼栋\n");
				}
				break;
			}
			case 3:/*删除房屋数据*/
			{
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入楼盘编号\t\t");
				scanf("%9s", estateid);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入楼栋编号\t\t");
				scanf("%9s", buildid);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入房屋编号\t\t");
				scanf("%9s", houseid);
				while (getchar() != '\n');
				printf("--------------------------------------------------------------------------------");
				if (DelHouseNode(hd, estateid, buildid, houseid))
					printf("\t\t\t\t\t已删除对应房屋\n");
				else
					printf("\t\t\t\t\t未找到对应的房屋\n");
				break;
			}
			default:
			{
				printf("--------------------------------------------------------------------------------");
				printf("\t\t\t\t输入功能编号有误\n");
			}
			}
			LABEL_BUNDLE labels;
			HOT_AREA areas;

			SMALL_RECT rcPop;
			COORD pos;
			WORD att;
			char *pCh[] = { "继续删除                          返回" };
			int iHot = 1;

			pos.X = strlen(pCh[0]) + 6;
			pos.Y = 7;
			rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
			rcPop.Right = rcPop.Left + pos.X - 7;
			rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
			rcPop.Bottom = rcPop.Top + pos.Y - 8;
			att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
*函数名称：ModifyData
*函数功能：修改楼盘、楼栋、房屋数据
*输入参数：无
*输出参数：无
*函数说明：
*返回值：BOOL类型，始终返回TRUE
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
		char *pCh[] = { "1、修改楼盘数据","2、修改楼栋数据", "3、修改房屋数据" };
		int iHot = 3;

		pos.X = strlen(pCh[0]) + 10;
		pos.Y = 12;
		rcPop.Left = (SCR_COL - pos.X) / 2;
		rcPop.Right = rcPop.Left + pos.X - 1;
		rcPop.Top = (25 - pos.Y) / 2;
		rcPop.Bottom = rcPop.Top + pos.Y - 1;

		att = BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
			/*精确查询*/
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
			case 1:/*修改楼盘数据*/
			{
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入楼盘编号\t\t");
				scanf("%9s", estateid);
				while (getchar() != '\n');
				printf("\n");
				printf("--------------------------------------------------------------------------------");
				newestate = SeekEstateNode(hd, estateid);/*查找对应楼盘*/
				if (newestate == NULL)
					printf("未找到对应的数据\n");
				else
					ModifyEstate(newestate);
				break;
			}
			case 2:/*修改楼栋数据*/
			{
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入楼盘编号\t\t");
				scanf("%9s", estateid);
				while (getchar() != '\n');
				printf("\n");
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入楼栋编号\t\t");
				scanf("%9s", buildid);
				while (getchar() != '\n');
				printf("\n");
				printf("--------------------------------------------------------------------------------");
				newbuild = SeekBuildNode(hd, estateid, buildid);/*查找对应楼栋*/
				if (newbuild == NULL)
					printf("\t\t\t\t未找到对应的数据\n");
				else
					ModifyBuild(newbuild);
				break;
			}
			case 3:/*修改房屋数据*/
			{
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入楼盘编号\t\t");
				scanf("%9s", estateid);
				while (getchar() != '\n');
				printf("\n");
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入楼栋编号\t\t");
				scanf("%9s", buildid);
				while (getchar() != '\n');
				printf("\n");
				printf("--------------------------------------------------------------------------------");
				printf("\t\t输入房屋编号\t\t");
				scanf("%9s", houseid);
				while (getchar() != '\n');
				printf("\n");
				printf("--------------------------------------------------------------------------------");
				newhouse = SeekHouseNode(hd, estateid, buildid, houseid);/*查找对应房屋*/
				if (newhouse == NULL)
					printf("\t\t\t\t未找到对应的数据\n");
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
			char *pCh[] = { "继续修改                          返回" };
			int iHot = 1;

			pos.X = strlen(pCh[0]) + 6;
			pos.Y = 7;
			rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
			rcPop.Right = rcPop.Left + pos.X - 7;
			rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
			rcPop.Bottom = rcPop.Top + pos.Y - 8;
			att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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


/*修改楼盘数据函数*/
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
	char *pCh[] = { "1、修改楼盘编号","2、修改楼盘名称", "3、修改楼盘地址","4、修改开发商","5、修改物业公司" };
	int iHot = 5;

	pos.X = strlen(pCh[0]) + 10;
	pos.Y = 12;
	rcPop.Left = (SCR_COL - pos.X) / 2;
	rcPop.Right = rcPop.Left + pos.X - 1;
	rcPop.Top = (25 - pos.Y) / 2;
	rcPop.Bottom = rcPop.Top + pos.Y + 5;

	att = BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
		/*精确查询*/
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
		printf("\t\t输入楼盘编号\t\t");
		scanf("%9s", pestate->estate_id);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t修改完成");
		pbuild = pestate->bnext;
		while (pbuild)/*将该楼盘对应的楼栋与房屋信息一起修改*/
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
		printf("\t\t输入楼盘名称\t\t");
		scanf("%19s", pestate->name);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t修改完成");
		break;
	}
	case 3:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t输入楼盘地址\t\t");
		scanf("%29s", pestate->address);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t修改完成");
		break;
	}
	case 4:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t输入开发商\t\t");
		scanf("%19s", pestate->developer);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t修改完成");
		break;
	}
	case 5:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t输入物业公司\t\t");
		scanf("%19s", pestate->management_company);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t修改完成");
		break;
	}
	}

}

/*修改楼栋数据函数*/
void ModifyBuild(BUILD_NODE* pbuild)
{
	int deal1;
	HOUSE_NODE* phouse;
	LABEL_BUNDLE labels;
	HOT_AREA areas;
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;
	char *pCh[] = { "1、修改楼栋编号","2、修改单元", "3、修改楼层" };
	int iHot = 3;

	pos.X = strlen(pCh[0]) + 10;
	pos.Y = 12;
	rcPop.Left = (SCR_COL - pos.X) / 2;
	rcPop.Right = rcPop.Left + pos.X - 1;
	rcPop.Top = (25 - pos.Y) / 2;
	rcPop.Bottom = rcPop.Top + pos.Y - 1;

	att = BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
		/*精确查询*/
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
		printf("\t\t输入楼栋编号\t\t");
		scanf("%9s", pbuild->build_id);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t修改完成");
		phouse = pbuild->hnext;
		while (phouse)/*修改该楼栋对应的房屋信息*/
		{
			strcpy(phouse->build_id, pbuild->build_id);
			phouse = phouse->next;
		}
		break;
	}
	case 2:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t输入单元\t\t");
		scanf("%d", &pbuild->unit);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t修改完成");
		break;
	}
	case 3:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t输入楼层\t\t");
		scanf("%d", &pbuild->floor);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t修改完成");
		break;
	}
	}
}

/**
*函数名称：SortEstateByNum
*函数功能：利用选择排序法将楼盘数据按编号从小到大排序
*输入参数：主链头指针
*输出参数：无
*返回值：无
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

/*修改房屋数据函数*/
void ModifyHouse(HOUSE_NODE* phouse)
{
	int deal1;
	LABEL_BUNDLE labels;
	HOT_AREA areas;
	SMALL_RECT rcPop;
	COORD pos;
	WORD att;
	char *pCh[] = { "1、修改房屋编号","2、修改户型", "3、修改面积","4、修改公摊率","5、修改价格" };
	int iHot = 5;

	pos.X = strlen(pCh[0]) + 10;
	pos.Y = 12;
	rcPop.Left = (SCR_COL - pos.X) / 2;
	rcPop.Right = rcPop.Left + pos.X - 1;
	rcPop.Top = (25 - pos.Y) / 2;
	rcPop.Bottom = rcPop.Top + pos.Y + 5;

	att = BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
		/*精确查询*/
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
		printf("\t\t输入房屋编号\t\t");
		scanf("%9s", phouse->house_id);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t修改完成");
		break;
	}
	case 2:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t输入户型\t\t");
		scanf("%19s", phouse->type);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t修改完成");
		break;
	}
	case 3:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t输入面积\t\t");
		scanf("%d", &phouse->area);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t修改完成");
		break;
	}
	case 4:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t输入公摊率\t\t");
		scanf("%f", &phouse->shared_rate);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t修改完成");
		break;
	}
	case 5:
	{
		printf("--------------------------------------------------------------------------------");
		printf("\t\t输入价格\t\t");
		scanf("%d", &phouse->one_price);
		while (getchar() != '\n');
		printf("\n");
		printf("--------------------------------------------------------------------------------");
		printf("\t\t\t\t修改完成");
		break;
	}
	}
}

/**
*函数名称：ShowAllEstate
*函数功能：以分页的形式展示楼盘
*输入参数：无
*输出参数：无
*返回值：BOOL类型，始终返回TRUE
*/
BOOL ShowAllEstate(void)
{
	SortEstateByNum(hd);
	InitInterface();
	int num = 0, i = 0, page = 0;//page用来标志页数
	int choice;//若choice==1，则表示继续；choice==0，则结束
	int k;//每次用k来限制输出不超过5个
	int flag;//若flag==0，表示到首页；flag==1，表示到中间；flag==2，表示到尾页
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
	if (i == 1)//只有一页
	{
		pestate = p[page];
		printf("--------------------------------------------------------------------------------");
		printf("楼盘编号|    楼盘名称    |所在城区|    楼盘地址    |   开发商   |   物业公司   |");
		printf("--------------------------------------------------------------------------------");
		while (pestate)
		{
			printf("%8s|%16s|%8s|%16s|%12s|%14s|", pestate->estate_id, pestate->name,
				pestate->city, pestate->address, pestate->developer, pestate->management_company);
			printf("--------------------------------------------------------------------------------");
			pestate = pestate->next;
		}
		printf("按任意键继续...");
		getch();
		InitInterface();
	}
	else//有多页的时候
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
				printf("楼盘编号|    楼盘名称    |所在城区|    楼盘地址    |   开发商   |   物业公司   |");
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
				printf("                                                          第%d页\n", page + 1);
				printf("                                                           共%d页\n", i);
				LABEL_BUNDLE labels;
				HOT_AREA areas;

				SMALL_RECT rcPop;
				COORD pos;
				WORD att;
				char *pCh[] = { "下一页                          结  束" };
				int iHot = 1;

				pos.X = strlen(pCh[0]) + 6;
				pos.Y = 7;
				rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
				rcPop.Right = rcPop.Left + pos.X - 7;
				rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
				rcPop.Bottom = rcPop.Top + pos.Y - 8;

				att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
				printf("楼盘编号|    楼盘名称    |所在城区|    楼盘地址    |   开发商   |   物业公司   |");
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
				printf("                                                          第%d页\n", page + 1);
				printf("                                                           共%d页\n", i);
				LABEL_BUNDLE labels;
				HOT_AREA areas;

				SMALL_RECT rcPop;
				COORD pos;
				WORD att;
				char *pCh[] = { "上一页                          下一页" };
				int iHot = 1;

				pos.X = strlen(pCh[0]) + 6;
				pos.Y = 7;
				rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
				rcPop.Right = rcPop.Left + pos.X - 7;
				rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
				rcPop.Bottom = rcPop.Top + pos.Y - 8;

				att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
				printf("楼盘编号|    楼盘名称    |所在城区|    楼盘地址    |   开发商   |   物业公司   |");
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
				printf("                                                          第%d页\n", page + 1);
				printf("                                                           共%d页\n", i);
				LABEL_BUNDLE labels;
				HOT_AREA areas;

				SMALL_RECT rcPop;
				COORD pos;
				WORD att;
				char *pCh[] = { "上一页                          结  束" };
				int iHot = 1;

				pos.X = strlen(pCh[0]) + 6;
				pos.Y = 7;
				rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
				rcPop.Right = rcPop.Left + pos.X - 7;
				rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
				rcPop.Bottom = rcPop.Top + pos.Y - 8;

				att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
*函数名称：ShowHouseList
*函数功能：以分页的形式展示房屋信息
*输入参数：HOUSE_NODE类型头指针
*输出参数：无
*返回值：BOOL类型，返回FALSE则表明HOUSE_NODE为空指针，否则表示正常输出
*/
BOOL ShowHouseList(HOUSE_NODE* househd)
{
	InitInterface();
	if (househd == NULL)
	{
		printf("未查询到相应的数据项！\n");
		printf("按任意键继续...");
		getch();
		InitInterface();
		return FALSE;
	}
	else
	{
		int num = 0, i = 0, page = 0;//page用来标志页数
		int choice;//若choice==1，则表示继续；choice==0，则结束
		int k;//每次用k来限制输出不超过5个
		int flag;//若flag==0，表示到首页；flag==1，表示到中间；flag==2，表示到尾页
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
		if (i == 1)//只有一页
		{
			phouse = p[page];
			printf("--------------------------------------------------------------------------------");
			printf("楼盘编号|楼栋编号|房屋编号|    户型    |房屋面积(平方米)|公摊率|价格(元/平方米)|");
			printf("--------------------------------------------------------------------------------");
			while (phouse)
			{
				printf("%8s|%8s|%8s|%12s|%16d|%6.2f|%15d|", phouse->estate_id, phouse->build_id,
					phouse->house_id, phouse->type, phouse->area, phouse->shared_rate,phouse->one_price);
				printf("--------------------------------------------------------------------------------");
				phouse = phouse->next;
			}
			printf("按任意键继续...");
			getch();
			InitInterface();
		}
		else//有多页的时候
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
					printf("楼盘编号|楼栋编号|房屋编号|    户型    |房屋面积(平方米)|公摊率|价格(元/平方米)|");
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
					printf("                                                          第%d页\n", page + 1);
					printf("                                                           共%d页\n", i);
					LABEL_BUNDLE labels;
					HOT_AREA areas;

					SMALL_RECT rcPop;
					COORD pos;
					WORD att;
					char *pCh[] = { "下一页                          结  束" };
					int iHot = 1;

					pos.X = strlen(pCh[0]) + 6;
					pos.Y = 7;
					rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
					rcPop.Right = rcPop.Left + pos.X - 7;
					rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
					rcPop.Bottom = rcPop.Top + pos.Y - 8;

					att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
					printf("楼盘编号|楼栋编号|房屋编号|    户型    |房屋面积(平方米)|公摊率|价格(元/平方米)|");
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
					printf("                                                          第%d页\n", page + 1);
					printf("                                                           共%d页\n", i);
					LABEL_BUNDLE labels;
					HOT_AREA areas;

					SMALL_RECT rcPop;
					COORD pos;
					WORD att;
					char *pCh[] = { "上一页                          下一页" };
					int iHot = 1;

					pos.X = strlen(pCh[0]) + 6;
					pos.Y = 7;
					rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
					rcPop.Right = rcPop.Left + pos.X - 7;
					rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
					rcPop.Bottom = rcPop.Top + pos.Y - 8;

					att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
					printf("楼盘编号|楼栋编号|房屋编号|    户型    |房屋面积(平方米)|公摊率|价格(元/平方米)|");
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
					printf("                                                          第%d页\n", page + 1);
					printf("                                                           共%d页\n", i);
					LABEL_BUNDLE labels;
					HOT_AREA areas;

					SMALL_RECT rcPop;
					COORD pos;
					WORD att;
					char *pCh[] = { "上一页                          结  束" };
					int iHot = 1;

					pos.X = strlen(pCh[0]) + 6;
					pos.Y = 7;
					rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
					rcPop.Right = rcPop.Left + pos.X - 7;
					rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
					rcPop.Bottom = rcPop.Top + pos.Y - 8;

					att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
*函数名称：ShowAllHouse
*函数功能：以分页的形式展示所有的房屋数据
*输入参数：无
*输出参数：无
*返回值：BOOL类型，始终返回TRUE
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
	char *pCh[] = { "按默认编号输出                         按价格高低输出" };
	int iHot = 1;

	pos.X = strlen(pCh[0]) + 6;
	pos.Y = 7;
	rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
	rcPop.Right = rcPop.Left + pos.X - 7;
	rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
	rcPop.Bottom = rcPop.Top + pos.Y - 8;

	att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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

/*排序楼房通过id*/
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

/*通过价格排序房屋数据函数*/
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
*函数名称：StatCity
*函数功能：按城区查询房屋信息
*输入参数：无
*输出参数：无
*返回值：BOOL类型，始终返回TRUE
*/
BOOL StatCity(void)
{
	InitInterface();
	printf("请输入你想查询的城区："); 
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
	char *pCh[] = { "按默认编号输出                         按价格高低输出" };
	int iHot = 1;

	pos.X = strlen(pCh[0]) + 6;
	pos.Y = 7;
	rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
	rcPop.Right = rcPop.Left + pos.X - 7;
	rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
	rcPop.Bottom = rcPop.Top + pos.Y - 8;

	att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
*函数名称：StatType
*函数功能：按户型查询房屋信息
*输入参数：无
*输出参数：无
*返回值：BOOL类型，始终返回TRUE
*/
BOOL StatType(void)
{
	InitInterface();
	printf("请输入你想查询的户型：");
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
	char *pCh[] = { "按默认编号输出                         按价格高低输出" };
	int iHot = 1;

	pos.X = strlen(pCh[0]) + 6;
	pos.Y = 7;
	rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
	rcPop.Right = rcPop.Left + pos.X - 7;
	rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
	rcPop.Bottom = rcPop.Top + pos.Y - 8;

	att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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
*函数名称：StatPrice
*函数功能：按户型查询房屋信息
*输入参数：无
*输出参数：无
*返回值：BOOL类型，始终返回TRUE
*/
BOOL StatPrice(void)
{
	InitInterface();
	printf("输入你想查询的房屋价格的上下限：\n");
	int min, max;
	printf("上限为：");
	scanf("%d", &max);
	printf("下限为：");
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
	char *pCh[] = { "按默认编号输出                         按价格高低输出" };
	int iHot = 1;

	pos.X = strlen(pCh[0]) + 6;
	pos.Y = 7;
	rcPop.Left = (SCR_COL - pos.X) / 2 + 3;
	rcPop.Right = rcPop.Left + pos.X - 7;
	rcPop.Top = (SCR_ROW - pos.Y) / 2 + 11;
	rcPop.Bottom = rcPop.Top + pos.Y - 8;

	att = BACKGROUND_BLUE | BACKGROUND_GREEN | BACKGROUND_RED;  /*白底黑字*/
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

