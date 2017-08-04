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

#define SCR_ROW 25             /*��Ļ����*/
#define SCR_COL 80             /*��Ļ����*/

DWORD rec;
/**
*��Ļ������Ϣ�������ṹ
*/
typedef struct layer_node {
	char LayerNo;            /**< �������ڲ���*/
	SMALL_RECT rcArea;       /**< ����������������*/
	CHAR_INFO *pContent;     /**< �������������ַ���Ԫԭ��Ϣ�洢������*/
	char *pScrAtt;           /**< �������������ַ���Ԫԭ����ֵ�洢������*/
	struct layer_node *next; /**< ָ����һ����ָ��*/
} LAYER_NODE;

/**
*��ǩ���ṹ
*/
typedef struct labe1_bundle {
	char **ppLabel;        /**< ��ǩ�ַ��������׵�ַ*/
	COORD *pLoc;           /**< ��ǩ��λ�����׵�ַ*/
	int num;               /**< ��ǩ����*/
} LABEL_BUNDLE;

/**
*�����ṹ
*/
typedef struct hot_area {
	SMALL_RECT *pArea;     /**< ������λ�����׵�ַ*/
	char *pSort;           /**< �������(�������ı���ѡ���)�����׵�ַ*/
	char *pTag;            /**< ������������׵�ַ*/
	int num;               /**< ��������*/
} HOT_AREA;

LAYER_NODE *gp_top_layer = NULL;               /*����������Ϣ����ͷ*/


char *gp_sys_name = "¥�̲�ѯϵͳ";    /*ϵͳ����*/

char *ga_main_menu[] = { "�ļ�(F)",             /*ϵͳ���˵���*/
"����ά��(M)",
"���ݲ�ѯ(Q)",
"����ͳ��(S)",
"����(H)"
};

char *ga_sub_menu[] = {/*ϵͳ�Ӳ˵���*/
					   /*�ļ�*/
	"[S] ���ݱ���",
	"[B] ���ݱ���",
	"[R] ���ݻָ�",
	"[X] �˳�    ",
	/*����ά��*/
	"[D] �������",
	"[P] ɾ������",
	"[C] �޸�����",
	/*���ݲ�ѯ*/
	"[D] ��������ѯ",
	"[P] �����Ͳ�ѯ",
	"[C] ���۸��ѯ",
	/*����ͳ��*/
	"[E] ȫ��¥��",
	"[H] ȫ������",
	/*����*/
	"[T] ��������",
	"",
	"[A] ����... "
};

int pass = 1;
int ga_sub_menu_count[] = { 4, 3, 3, 2, 3 };  /*�����˵������Ӳ˵��ĸ���*/
int gi_sel_menu = 1;                        /*��ѡ�е����˵����,��ʼΪ1*/
int gi_sel_sub_menu = 0;                    /*��ѡ�е��Ӳ˵����,��ʼΪ0,��ʾδѡ��*/

CHAR_INFO *gp_buff_menubar_info = NULL;     /*��Ų˵�����Ļ���ַ���Ϣ�Ļ�����*/
CHAR_INFO *gp_buff_stateBar_info = NULL;    /*���״̬����Ļ���ַ���Ϣ�Ļ�����*/

char *gp_scr_att = NULL;    /*�����Ļ���ַ���Ԫ����ֵ�Ļ�����*/

HANDLE gh_std_out;          /*��׼����豸���*/
HANDLE gh_std_in;           /*��׼�����豸���*/

							/*������Ϣ�����ṹ*/
typedef struct house_node {
	char estate_id[10];          /*¥�̱��*/
	char build_id[10];          /*¥�����*/
	char house_id[10];         /*���ݱ��*/
	char type[20];             /*����*/
	int area;                  /*���*/
	float shared_rate;         /*��̯��*/
	int one_price;              /*��λ����۸�*/
	struct house_node*next;    /*ָ����һ�����ݽ��*/
}HOUSE_NODE;

/*¥����Ϣ�����ṹ*/
typedef struct build_node {
	char estate_id[10];          /*¥�̱��*/
	char build_id[10];          /*¥�����*/
	int unit;              /*¥��������Ԫ��*/
	int floor;                 /*¥��*/
	struct house_node*hnext;   /*ָ����һ�����ݽ��*/
	struct build_node*next;     /*ָ����һ��¥�����*/
}BUILD_NODE;

/*¥����Ϣ�����ṹ*/
typedef struct estate_node {
	char estate_id[10];                   /*¥�̱��*/
	char name[20];                      /*¥������*/
	char city[10];                      /*����*/
	char address[30];                   /*¥�̵�ַ*/
	char developer[20];                 /*������*/
	char management_company[20];        /*��ҵ��˾*/
	struct build_node*bnext;             /*ָ����һ��¥�����*/
	struct estate_node*next;              /*ָ����һ��¥�̽��*/
}ESTATE_NODE;

ESTATE_NODE* hd;/*ָ�������ͷ��ָ��*/
char * gp_estate_info_filename = "estate.dat";/*���¥������Ϣ���ļ�*/
char * gp_build_info_filename = "build.dat";/*���¥����Ϣ���ļ�*/
char * gp_house_info_filename = "house.dat";/*��ŷ�����Ϣ���ļ�*/

BOOL LoadData(void);
void InitInterface(void);                 /*ϵͳ�����ʼ��*/
void ClearScreen(void);                         /*����*/
void ShowMenu(void);                            /*��ʾ�˵���*/
void PopMenu(int num);                          /*��ʾ�����˵�*/
void PopUp(SMALL_RECT *, WORD, LABEL_BUNDLE *, HOT_AREA *);  /*����������Ļ��Ϣά��*/
void PopOff(void);                              /*�رն��㵯������*/
void DrawBox(SMALL_RECT *parea);                /*���Ʊ߿�*/
void LocSubMenu(int num, SMALL_RECT *parea);    /*���˵������˵���λ*/
void ShowState(void);                           /*��ʾ״̬��*/
void TagMainMenu(int num);                      /*��Ǳ�ѡ�е����˵���*/
void TagSubMenu(int num);                       /*��Ǳ�ѡ�е��Ӳ˵���*/
int DealInput(HOT_AREA *phot_area, int *pihot_num);  /*����̨���봦��*/
void SetHotPoint(HOT_AREA *phot_area, int hot_num);     /*��������*/
void RunSys(ESTATE_NODE **phead);                 /*ϵͳ����ģ���ѡ�������*/
void CloseSys(ESTATE_NODE *hd);                  /*�˳�ϵͳ*/


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

BOOL ExeFunction(int main_menu_num, int sub_menu_num);  /*����ģ��ĵ���*/

BOOL SaveData(void);		/*���ݱ���*/
BOOL BackupData(void);		/*���ݱ���*/
BOOL RestoreData(void);		/*���ݻָ�*/
BOOL ExitSys(void);			/*�˳�*/
BOOL AddData(void);			/*�������*/
BOOL DeleteData(void);		/*ɾ������*/
BOOL ModifyData(void);		/*�޸�����*/
BOOL Search(void);			/*����*/
BOOL ShowAllEstate(void);	/*չʾȫ��¥������*/
BOOL ShowAllHouse(void);	/*չʾȫ����������*/
BOOL StatCity(void);		/*��������ѯ*/
BOOL StatType(void);		/*�����Ͳ�ѯ*/
BOOL StatPrice(void);		/*���۸��ѯ*/
BOOL HelpTopic(void);		/*��������*/
BOOL About(void);			/*����*/
void Administrator(void);	/*����Ա*/

#endif /**< TYPE_H_INCLUDED*/