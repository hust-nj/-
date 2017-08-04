#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <wincon.h>
#include <conio.h>
#include <string.h>
#include <io.h>
#include <fcntl.h>
#include <sys\stat.h>
#include <ctype.h>
#include <time.h>

#ifndef TYPE_H_INCLUDED
#define TYPE_H_INCLUDED

#define SCR_ROW 25             /*屏幕行数*/
#define SCR_COL 80             /*屏幕列数*/

DWORD rec;
/**
*屏幕窗口信息链结点结点结构
*/
typedef struct layer_node {
	char LayerNo;            /**< 弹出窗口层数*/
	SMALL_RECT rcArea;       /**< 弹出窗口区域坐标*/
	CHAR_INFO *pContent;     /**< 弹出窗口区域字符单元原信息存储缓冲区*/
	char *pScrAtt;           /**< 弹出窗口区域字符单元原属性值存储缓冲区*/
	struct layer_node *next; /**< 指向下一结点的指针*/
} LAYER_NODE;

/**
*标签束结构
*/
typedef struct labe1_bundle {
	char **ppLabel;        /**< 标签字符串数组首地址*/
	COORD *pLoc;           /**< 标签定位数组首地址*/
	int num;               /**< 标签个数*/
} LABEL_BUNDLE;

/**
*热区结构
*/
typedef struct hot_area {
	SMALL_RECT *pArea;     /**< 热区定位数组首地址*/
	char *pSort;           /**< 热区类别(按键、文本框、选项框)数组首地址*/
	char *pTag;            /**< 热区序号数组首地址*/
	int num;               /**< 热区个数*/
} HOT_AREA;

LAYER_NODE *gp_top_layer = NULL;               /*弹出窗口信息链链头*/


char *gp_sys_name = "楼盘查询系统";    /*系统名称*/

char *ga_main_menu[] = { "文件(F)",             /*系统主菜单名*/
"数据维护(M)",
"数据查询(Q)",
"数据统计(S)",
"帮助(H)"
};

char *ga_sub_menu[] = {/*系统子菜单名*/
					   /*文件*/
	"[S] 数据保存",
	"[B] 数据备份",
	"[R] 数据恢复",
	"[X] 退出    ",
	/*数据维护*/
	"[D] 添加数据",
	"[P] 删除数据",
	"[C] 修改数据",
	/*数据查询*/
	"[D] 按城区查询",
	"[P] 按户型查询",
	"[C] 按价格查询",
	/*数据统计*/
	"[E] 全部楼盘",
	"[H] 全部房屋",
	/*帮助*/
	"[T] 帮助主题",
	"",
	"[A] 关于... "
};

int pass = 1;
int ga_sub_menu_count[] = { 4, 3, 3, 2, 3 };  /*各主菜单项下子菜单的个数*/
int gi_sel_menu = 1;                        /*被选中的主菜单项号,初始为1*/
int gi_sel_sub_menu = 0;                    /*被选中的子菜单项号,初始为0,表示未选中*/

CHAR_INFO *gp_buff_menubar_info = NULL;     /*存放菜单条屏幕区字符信息的缓冲区*/
CHAR_INFO *gp_buff_stateBar_info = NULL;    /*存放状态条屏幕区字符信息的缓冲区*/

char *gp_scr_att = NULL;    /*存放屏幕上字符单元属性值的缓冲区*/

HANDLE gh_std_out;          /*标准输出设备句柄*/
HANDLE gh_std_in;           /*标准输入设备句柄*/

							/*房屋信息链结点结构*/
typedef struct house_node {
	char estate_id[10];          /*楼盘编号*/
	char build_id[10];          /*楼栋编号*/
	char house_id[10];         /*房屋编号*/
	char type[20];             /*户型*/
	int area;                  /*面积*/
	float shared_rate;         /*公摊率*/
	int one_price;              /*单位面积价格*/
	struct house_node*next;    /*指向下一个房屋结点*/
}HOUSE_NODE;

/*楼栋信息链结点结构*/
typedef struct build_node {
	char estate_id[10];          /*楼盘编号*/
	char build_id[10];          /*楼栋编号*/
	int unit;              /*楼栋所含单元数*/
	int floor;                 /*楼层*/
	struct house_node*hnext;   /*指向下一个房屋结点*/
	struct build_node*next;     /*指向下一个楼栋结点*/
}BUILD_NODE;

/*楼盘信息链结点结构*/
typedef struct estate_node {
	char estate_id[10];                   /*楼盘编号*/
	char name[20];                      /*楼盘名称*/
	char city[10];                      /*城区*/
	char address[30];                   /*楼盘地址*/
	char developer[20];                 /*开发商*/
	char management_company[20];        /*物业公司*/
	struct build_node*bnext;             /*指向下一个楼栋结点*/
	struct estate_node*next;              /*指向下一个楼盘结点*/
}ESTATE_NODE;

ESTATE_NODE* hd;/*指向链表表头的指针*/
char * gp_estate_info_filename = "estate.dat";/*存放楼盘西信息的文件*/
char * gp_build_info_filename = "build.dat";/*存放楼栋信息的文件*/
char * gp_house_info_filename = "house.dat";/*存放房屋信息的文件*/

BOOL LoadData(void);
void InitInterface(void);                 /*系统界面初始化*/
void ClearScreen(void);                         /*清屏*/
void ShowMenu(void);                            /*显示菜单栏*/
void PopMenu(int num);                          /*显示下拉菜单*/
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);  /*弹出窗口屏幕信息维护*/
void PopOff(void);                              /*关闭顶层弹出窗口*/
void DrawBox(SMALL_RECT *parea);                /*绘制边框*/
void LocSubMenu(int num, SMALL_RECT *parea);    /*主菜单下拉菜单定位*/
void ShowState(void);                           /*显示状态栏*/
void TagMainMenu(int num);                      /*标记被选中的主菜单项*/
void TagSubMenu(int num);                       /*标记被选中的子菜单项*/
int DealInput(HOT_AREA *phot_area, int *pihot_num);  /*控制台输入处理*/
void SetHotPoint(HOT_AREA *phot_area, int hot_num);     /*设置热区*/
void RunSys(ESTATE_NODE **phead);                 /*系统功能模块的选择和运行*/
void CloseSys(ESTATE_NODE *hd);                  /*退出系统*/


int CreatList(ESTATE_NODE**phead);
ESTATE_NODE* SeekEstateNode(ESTATE_NODE*head, char* estateid);
BUILD_NODE* SeekBuildNode(ESTATE_NODE*head, char* estateid, char* buildid);
HOUSE_NODE* SeekHouseNode(ESTATE_NODE*head, char* estateid, char* buildid, char* houseid);
BOOL DelHouseNode(ESTATE_NODE*hd, char* estateid, char* buildid, char* houseid);
BOOL DelBuildNode(ESTATE_NODE*hd, char* estateid, char* buildid);
BOOL DelEstateNode(ESTATE_NODE** phead, char* estateid);
void ModifyEstate(ESTATE_NODE*);
void ModifyHouse(HOUSE_NODE*);
void ModifyBuild(BUILD_NODE*);
BOOL ShowHouseList(HOUSE_NODE*);
void SortEstateByNum(ESTATE_NODE*);
void SortHouseByNum(HOUSE_NODE*);
void SortHouseByPrice(HOUSE_NODE*);

BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*功能模块的调用*/

BOOL SaveData(void);		/*数据保存*/
BOOL BackupData(void);		/*数据备份*/
BOOL RestoreData(void);		/*数据恢复*/
BOOL ExitSys(void);			/*退出*/
BOOL AddData(void);			/*添加数据*/
BOOL DeleteData(void);		/*删除数据*/
BOOL ModifyData(void);		/*修改数据*/
BOOL Search(void);			/*检索*/
BOOL ShowAllEstate(void);	/*展示全部楼盘数据*/
BOOL ShowAllHouse(void);	/*展示全部房屋数据*/
BOOL StatCity(void);		/*按城区查询*/
BOOL StatType(void);		/*按户型查询*/
BOOL StatPrice(void);		/*按价格查询*/
BOOL HelpTopic(void);		/*帮助主题*/
BOOL About(void);			/*关于*/
void Administrator(void);	/*管理员*/

#endif /**< TYPE_H_INCLUDED*/