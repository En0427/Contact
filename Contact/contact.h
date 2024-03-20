#define _CRT_SECURE_NO_WARNINGS 1
//#define MAX 1000
#define DEFAULT_SZ 3
#define NAME_MAX 20
#define SEX_MAX 5
#define TELE_MAX 12
#define ADDR_MAX 30

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

enum Option
{
	EXIT,
	ADD,
	DEL,
	SEARCH,
	MODIFY,
	SHOW,
	SORT
};

struct PeopleInfo
{
	char name[NAME_MAX];
	int age;
	char sex[SEX_MAX];
	char tele[TELE_MAX];
	char addr[ADDR_MAX];
};

struct Contact
{
	struct PeopleInfo *data; //存放联系人信息
	int size; //记录当前有几个人的信息
	int capacity; //当前通讯录最大容量
};

//声明函数
//初始化通讯录函数
void InitContact(struct Contact* ps);
//增加一个联系人到通讯录
void AddContact(struct Contact* ps);
//打印通讯录中的信息
void ShowContact(const struct Contact* ps);
//删除指定的联系人
void DelContact(struct Contact* ps);
//查找联系人
void SearchContact(const struct Contact* ps);
//修改联系人信息
void ModifyContact(struct Contact* ps);
//排序联系人信息
void SortContact(struct Contact* ps);
//释放通讯录内存
void FreeContact(struct Contact* ps);
//保存通讯录信息
void SaveContact(struct Contact* ps);
//把文件中保存的信息加载到通讯录中
void LoadContact(struct Contact* ps);