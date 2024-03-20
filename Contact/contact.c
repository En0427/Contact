#define _CRT_SECURE_NO_WARNINGS 1

#include "contact.h"

//������ϵ��λ�ã��ҵ��������������±ꣻ�Ҳ�������-1
static int FindByName(const struct Contact* ps, char name[NAME_MAX])
{
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		if (strcmp(ps->data[i].name, name) == 0)
		{
			return i;
		}
	}
	return -1; //�Ҳ��������
}

void CheckCapacity(struct Contact* ps)
{
	//��⵱ǰͨѶ¼������
	//1.������ˣ������ӿռ�
	//2.���û���������в���
	if (ps->size == ps->capacity)
	{
		struct PeopleInfo* ptr = realloc(ps->data, (ps->capacity + 2) * sizeof(struct PeopleInfo));
		if (ptr != NULL)
		{
			ps->data = ptr;
			ps->capacity += 2;
		}
	}
}

void InitContact(struct Contact* ps)
{
	//memset(ps->data, 0, sizeof(ps->data));
	ps->data = (struct PeopleInfo*) malloc(3 * sizeof(struct PeopleInfo));
	if (ps->data == NULL)
	{
		return;
	}
	ps->size = 0; //���ó�ʼͨѶ¼Ϊ0��Ԫ��
	ps->capacity = DEFAULT_SZ;
	//���ļ��б������Ϣ���ص�ͨѶ¼��
	LoadContact(ps);
}

void LoadContact(struct Contact* ps)
{
	struct PeopleInfo tmp = { 0 };
	FILE* pfRead = fopen("contact.dat", "rb");
	if (pfRead == NULL)
	{
		printf("LoadContact::%s\n", strerror(errno));
		return;
	}
	//��ȡ�ļ�����ŵ�ͨѶ¼
	while (fread(&tmp, sizeof(struct PeopleInfo), 1, pfRead))
	{
		CheckCapacity(ps);
		ps->data[ps->size] = tmp;
		ps->size++;
	}
}

void AddContact(struct Contact* ps)
{
	//��⵱ǰͨѶ¼������
	CheckCapacity(ps);
	printf("����������:>");
	scanf("%s", &ps->data[ps->size].name);
	printf("����������:>");
	scanf("%d", &ps->data[ps->size].age);
	printf("�������Ա�:>");
	scanf("%s", &ps->data[ps->size].sex);
	printf("������绰:>");
	scanf("%s", &ps->data[ps->size].tele);
	printf("�������ַ:>");
	scanf("%s", &ps->data[ps->size].addr);
	ps->size++;
	printf("��ӳɹ�\n");
	/*if (ps->size == MAX)
	{
		printf("����ͨѶ¼����\n");
	}
	else
	{
		printf("����������:>");
		scanf("%s", &ps->data[ps->size].name);
		printf("����������:>");
		scanf("%d", &ps->data[ps->size].age);
		printf("�������Ա�:>");
		scanf("%s", &ps->data[ps->size].sex);
		printf("������绰:>");
		scanf("%s", &ps->data[ps->size].tele);
		printf("�������ַ:>");
		scanf("%s", &ps->data[ps->size].addr);
		ps->size++;
		printf("��ӳɹ�\n");
	}*/
}

void ShowContact(const struct Contact* ps)
{
	if (ps->size == 0)
	{
		printf("ͨѶ¼Ϊ��\n");
	}
	else
	{
		int i = 0;
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-20s\n", "name", "age", "gender", "tele", "address");
		for (i = 0; i < ps->size; i++)
		{
			printf("%-20s\t%-4d\t%-5s\t%-12s\t%-20s\n",
				ps->data[i].name,
				ps->data[i].age,
				ps->data[i].sex,
				ps->data[i].tele,
				ps->data[i].addr);
		}
	}
}

void DelContact(struct Contact* ps)
{
	char name[NAME_MAX];
	printf("������Ҫɾ������ϵ��:>");
	scanf("%s", &name);
	//1.����Ҫɾ���˵�λ��
	int pos = FindByName(ps, name);
	//2.ɾ��
	if (pos == -1)
	{
		printf("��ϵ�˲�����\n");
	}
	else
	{
		int j = 0;
		for (j = pos; j < ps->size - 1; j++)
		{
			ps->data[j] = ps->data[j + 1];
		}
		ps->size--;
		printf("ɾ���ɹ�\n");
	}
}

void SearchContact(const struct Contact* ps)
{
	int pos = 0;
	char name[NAME_MAX];
	printf("������Ҫ�����˵���ϵ��:>");
	scanf("%s", &name);
	pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("��ϵ�˲�����\n");
	}
	else
	{
		printf("%-20s\t%-4s\t%-5s\t%-12s\t%-20s\n", "name", "age", "gender", "tele", "address");
		printf("%-20s\t%-4d\t%-5s\t%-12s\t%-20s\n",
			ps->data[pos].name,
			ps->data[pos].age,
			ps->data[pos].sex,
			ps->data[pos].tele,
			ps->data[pos].addr);
	}
}

void ModifyContact(struct Contact* ps)
{
	int pos = 0;
	char name[NAME_MAX];
	printf("������Ҫ�޸ĵ���ϵ��:>");
	scanf("%s", &name);
	pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("��ϵ�˲�����\n");
	}
	else
	{
		printf("����������:>");
		scanf("%s", &ps->data[pos].name);
		printf("����������:>");
		scanf("%d", &ps->data[pos].age);
		printf("�������Ա�:>");
		scanf("%s", &ps->data[pos].sex);
		printf("������绰:>");
		scanf("%s", &ps->data[pos].tele);
		printf("�������ַ:>");
		scanf("%s", &ps->data[pos].addr);
		printf("�޸ĳɹ�\n");
	}
}

int sort_by_name(const void* e1, const void* e2)
{
	return strcmp(((struct PeopleInfo*)e1)->name, ((struct PeopleInfo*)e2)->name);
}

void SortContact(struct Contact* ps)
{
	qsort(ps->data, ps->size, sizeof(struct PeopleInfo), sort_by_name);
}

void FreeContact(struct Contact* ps)
{
	free(ps->data);
	ps->data = NULL;
}

void SaveContact(struct Contact* ps)
{
	FILE* pfWrite = fopen("contact.dat", "wb");
	if (pfWrite == NULL)
	{
		printf("SaveContact::%s\n", strerror(errno));
		return;
	}
	int i = 0;
	for (i = 0; i < ps->size; i++)
	{
		fwrite(&(ps->data[i]), sizeof(struct PeopleInfo), 1, pfWrite);
	}
	fclose(pfWrite);
	pfWrite = NULL;
}