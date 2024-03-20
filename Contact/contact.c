#define _CRT_SECURE_NO_WARNINGS 1

#include "contact.h"

//查找联系人位置，找到返回名字所在下标；找不到返回-1
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
	return -1; //找不到的情况
}

void CheckCapacity(struct Contact* ps)
{
	//检测当前通讯录的容量
	//1.如果满了，就增加空间
	//2.如果没满，不进行操作
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
	ps->size = 0; //设置初始通讯录为0个元素
	ps->capacity = DEFAULT_SZ;
	//把文件中保存的信息加载到通讯录中
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
	//读取文件，存放到通讯录
	while (fread(&tmp, sizeof(struct PeopleInfo), 1, pfRead))
	{
		CheckCapacity(ps);
		ps->data[ps->size] = tmp;
		ps->size++;
	}
}

void AddContact(struct Contact* ps)
{
	//检测当前通讯录的容量
	CheckCapacity(ps);
	printf("请输入名字:>");
	scanf("%s", &ps->data[ps->size].name);
	printf("请输入年龄:>");
	scanf("%d", &ps->data[ps->size].age);
	printf("请输入性别:>");
	scanf("%s", &ps->data[ps->size].sex);
	printf("请输入电话:>");
	scanf("%s", &ps->data[ps->size].tele);
	printf("请输入地址:>");
	scanf("%s", &ps->data[ps->size].addr);
	ps->size++;
	printf("添加成功\n");
	/*if (ps->size == MAX)
	{
		printf("错误，通讯录已满\n");
	}
	else
	{
		printf("请输入名字:>");
		scanf("%s", &ps->data[ps->size].name);
		printf("请输入年龄:>");
		scanf("%d", &ps->data[ps->size].age);
		printf("请输入性别:>");
		scanf("%s", &ps->data[ps->size].sex);
		printf("请输入电话:>");
		scanf("%s", &ps->data[ps->size].tele);
		printf("请输入地址:>");
		scanf("%s", &ps->data[ps->size].addr);
		ps->size++;
		printf("添加成功\n");
	}*/
}

void ShowContact(const struct Contact* ps)
{
	if (ps->size == 0)
	{
		printf("通讯录为空\n");
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
	printf("请输入要删除的联系人:>");
	scanf("%s", &name);
	//1.查找要删除人的位置
	int pos = FindByName(ps, name);
	//2.删除
	if (pos == -1)
	{
		printf("联系人不存在\n");
	}
	else
	{
		int j = 0;
		for (j = pos; j < ps->size - 1; j++)
		{
			ps->data[j] = ps->data[j + 1];
		}
		ps->size--;
		printf("删除成功\n");
	}
}

void SearchContact(const struct Contact* ps)
{
	int pos = 0;
	char name[NAME_MAX];
	printf("请输入要查找人的联系人:>");
	scanf("%s", &name);
	pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("联系人不存在\n");
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
	printf("请输入要修改的联系人:>");
	scanf("%s", &name);
	pos = FindByName(ps, name);
	if (pos == -1)
	{
		printf("联系人不存在\n");
	}
	else
	{
		printf("请输入名字:>");
		scanf("%s", &ps->data[pos].name);
		printf("请输入年龄:>");
		scanf("%d", &ps->data[pos].age);
		printf("请输入性别:>");
		scanf("%s", &ps->data[pos].sex);
		printf("请输入电话:>");
		scanf("%s", &ps->data[pos].tele);
		printf("请输入地址:>");
		scanf("%s", &ps->data[pos].addr);
		printf("修改成功\n");
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