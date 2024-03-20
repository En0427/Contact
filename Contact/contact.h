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
	struct PeopleInfo *data; //�����ϵ����Ϣ
	int size; //��¼��ǰ�м����˵���Ϣ
	int capacity; //��ǰͨѶ¼�������
};

//��������
//��ʼ��ͨѶ¼����
void InitContact(struct Contact* ps);
//����һ����ϵ�˵�ͨѶ¼
void AddContact(struct Contact* ps);
//��ӡͨѶ¼�е���Ϣ
void ShowContact(const struct Contact* ps);
//ɾ��ָ������ϵ��
void DelContact(struct Contact* ps);
//������ϵ��
void SearchContact(const struct Contact* ps);
//�޸���ϵ����Ϣ
void ModifyContact(struct Contact* ps);
//������ϵ����Ϣ
void SortContact(struct Contact* ps);
//�ͷ�ͨѶ¼�ڴ�
void FreeContact(struct Contact* ps);
//����ͨѶ¼��Ϣ
void SaveContact(struct Contact* ps);
//���ļ��б������Ϣ���ص�ͨѶ¼��
void LoadContact(struct Contact* ps);