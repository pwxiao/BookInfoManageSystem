#include <iostream>
#include <string>
#include <stdio.h>
#include "cJSON.h"
#include <fstream>
#include <Windows.h>
#include <sstream>
#define FILE_NAME "cjosn.json"

using namespace std;

typedef struct books
{
	int id;
	string bookname;
	string aucther;
	string press;
	string publishTime;
	string price;
} book;

void addBook();
void query();
void deleteBook();
void updateFile(char *cjValue);
void changeBookInfo();
void showBookStruct(book bok);
void Toast(string str);
void showMenu();
const char *readFile(const char *fileName);
int queryAll();

int main()
{
	showMenu();	
	int input=1;
	while (input!=0)
	{
		printf("请输入对应哪个操作的编号：");
		scanf_s("%d", &input);
		switch (input)
		{
		case 0:
		    system("cls");
			printf("已退出系统!!");
			system("exit");
			break;
		case 2:
			query();
			break;
		case 1:
			addBook();
			break;
		case 3:
			changeBookInfo();
			break;
		case 4:
			deleteBook();
			break;
		case 5:
			queryAll();
			break;
		default:
			printf("你输错了\n");
		}
	}
	//system("pause");
	return 0;
}

void Toast(string str)
{
	printf("%s", str);
}

void showMenu()
{
	SetConsoleOutputCP(65001);
	printf("==========================================\n");
    printf("\n");
	printf("      欢迎进入图书管理系统    \n");
	printf("\t1.录入图书\n");
	printf("\t2.查询图书\n");
	printf("\t3.修改图书\n");
	printf("\t4.删除图书\n");
	printf("\t5.浏览全部\n");
	printf("\t0.退出\n");
	printf("\n");
	printf("\n");
	printf("===========================================\n");
}

const char *readFile(const char *fileName)
{
	std::ifstream file(fileName);
	char *content;
	content = (char *)malloc(sizeof(char) * 40960);
	if (content)
	{
		char buff[1024];
		int pt = 0;
		while (file.getline(buff, 1024))
		{
			for (int i = 0; i < 1024; i++)
			{
				char tmp = buff[i];
				if (tmp == '\0')
				{
					content[pt] = '\n';
					pt++;
					break;
				}
				content[pt] = tmp;
				pt++;
			}
		}
		content[pt] = '\0';
		char *result = (char *)malloc(sizeof(char) * (++pt));
		if (!result)
			return NULL;
		for (int i = 0; i < pt; i++)
		{
			result[i] = content[i];
		}
		return result;
	}
	return NULL;
}

int queryAll()
{
	cJSON *root = cJSON_Parse(readFile("cjosn.json"));
	if (root == NULL)
		return 0;

	cJSON *item;
	int i;
	item = cJSON_GetObjectItem(root, "data");
	if (item)
	{

		int ArraySize = cJSON_GetArraySize(item);
		printf("编号\t书名\t作者\t出版社\t发行日期\t价格\n");
		for (i = 0; i < ArraySize; i++)
		{

			cJSON *array_item = cJSON_GetArrayItem(item, i);
			if (array_item == NULL)
				continue;

			cJSON *obj = cJSON_GetObjectItem(array_item, "id");
			if (obj)
			{
				printf("%d\t", obj->valueint);
			}
			obj = cJSON_GetObjectItem(array_item, "bookname");
			if (obj)
			{
				printf("%s\t", obj->valuestring);
			}
			obj = cJSON_GetObjectItem(array_item, "aucther");
			if (obj)
			{
				printf("%s\t", obj->valuestring);
			}
			obj = cJSON_GetObjectItem(array_item, "press");
			if (obj)
			{
				printf("%s\t", obj->valuestring);
			}
			obj = cJSON_GetObjectItem(array_item, "publishTime");
			if (obj)
			{
				printf("%s\t", obj->valuestring);
			}
			obj = cJSON_GetObjectItem(array_item, "price");
			if (obj)
			{
				printf("%s\t", obj->valuestring);
			}
			printf("\n");
		}
	}

	cJSON_Delete(root);
	return 0;
}

void query()
{
	printf("请输入要查询的书的编号：");
	int in;
	cin >> in;
	cJSON *root = cJSON_Parse(readFile("cjosn.json"));
	cJSON *item;
	int i;
	item = cJSON_GetObjectItem(root, "data");
	if (item)
	{

		int ArraySize = cJSON_GetArraySize(item);
		for (i = 0; i < ArraySize; i++)
		{

			cJSON *array_item = cJSON_GetArrayItem(item, i);
			if (array_item == NULL)
				continue;
			cJSON *obj = cJSON_GetObjectItem(array_item, "id");
			int num = obj->valueint;
			if (num == in)
			{
				obj = cJSON_GetObjectItem(array_item, "bookname");
				if (obj)
				{
					printf("书名： %s\n", obj->valuestring);
				}
				obj = cJSON_GetObjectItem(array_item, "aucther");
				if (obj)
				{
					printf("作者： %s\n", obj->valuestring);
				}
				obj = cJSON_GetObjectItem(array_item, "press");
				if (obj)
				{
					printf("出版社：%s\n", obj->valuestring);
				}
				obj = cJSON_GetObjectItem(array_item, "publishTime");
				if (obj)
				{
					printf("出版日期： %s\n", obj->valuestring);
				}
				obj = cJSON_GetObjectItem(array_item, "price");
				if (obj)
				{
					printf("价格： %s\n", obj->valuestring);
				}
			}

			printf("\n");
		}
	}
	cJSON_Delete(root);
}

void addBook()
{
	struct books book;
	printf("\n请输入新图书信息的编号:");
	cin >> book.id;
	printf("\n请输入新图书信息的书名为:");
	cin >> book.bookname;
	printf("\n请输入新图书信息的作者名为:");
	cin >> book.aucther;
	printf("\n请输入新图书信息的出版社为:");
	cin >> book.press;
	printf("\n请输入新图书信息的出版时间为:");
	cin >> book.publishTime;
	printf("\n请输入新图书信息的价格为:");
	cin >> book.price;

	cJSON *root = cJSON_Parse(readFile("cjosn.json"));
	cJSON *body, *list;

	cJSON *rot = cJSON_GetObjectItem(root, "data");

	cJSON_AddItemToArray(rot, list = cJSON_CreateObject());

	cJSON_AddNumberToObject(list, "id", book.id);
	cJSON_AddStringToObject(list, "bookname", book.bookname.c_str());
	cJSON_AddStringToObject(list, "aucther", book.aucther.c_str());
	cJSON_AddStringToObject(list, "press", book.press.c_str());
	cJSON_AddStringToObject(list, "publishTime", book.publishTime.c_str());
	cJSON_AddStringToObject(list, "price", book.price.c_str());
	char *s = cJSON_Print(root);
	updateFile(s);
	printf("添加成功\n");
}

void deleteBook()
{
	printf("请输入要删除的书的编号：");
	int in;
	cin >> in;
	cJSON *root = cJSON_Parse(readFile("cjosn.json"));
	cJSON *item;
	int i;
	item = cJSON_GetObjectItem(root, "data");
	if (item)
	{

		int ArraySize = cJSON_GetArraySize(item);
		for (i = 0; i < ArraySize; i++)
		{

			cJSON *array_item = cJSON_GetArrayItem(item, i);
			if (array_item == NULL)
				continue;
			cJSON *obj = cJSON_GetObjectItem(array_item, "id");
			int num = obj->valueint;
			if (num == in)
				cJSON_DeleteItemFromArray(item, i);

		}
	}
	char *pstr = cJSON_Print(root);
	updateFile(pstr);
	printf("已删除！\n");
	cJSON_Delete(root);
}

void changeBookInfo()
{
	struct books book;
	printf("请输入要修改的书的编号：");
	int in;
	cin >> in;
	cJSON *root = cJSON_Parse(readFile("cjosn.json"));
	cJSON *item;
	int i;
	int index;
	item = cJSON_GetObjectItem(root, "data");
	if (item)
	{

		int ArraySize = cJSON_GetArraySize(item);
		for (i = 0; i < ArraySize; i++)
		{

			cJSON *array_item = cJSON_GetArrayItem(item, i);
			if (array_item == NULL)
				continue;
			cJSON *obj = cJSON_GetObjectItem(array_item, "id");
			int num = obj->valueint;
			if (num == in)
			{
				printf("\n请输入新图书信息的书名为:");
				cin >> book.bookname;
				cJSON_ReplaceItemInObject(array_item, "bookname", cJSON_CreateString(book.bookname.c_str()));
				printf("\n请输入新图书信息的作者名为:");
				cin >> book.aucther;
				cJSON_ReplaceItemInObject(array_item, "aucther", cJSON_CreateString(book.aucther.c_str()));
				printf("\n请输入新图书信息的出版社为:");
				cin >> book.press;
				cJSON_ReplaceItemInObject(array_item, "press", cJSON_CreateString(book.press.c_str()));
				printf("\n请输入新图书信息的出版时间为:");
				cin >> book.publishTime;
				cJSON_ReplaceItemInObject(array_item, "publishTime", cJSON_CreateString(book.publishTime.c_str()));
				printf("\n请输入新图书信息的价格为:");
				cin >> book.price;
				cJSON_ReplaceItemInObject(array_item, "price", cJSON_CreateString(book.price.c_str()));
				break;
			}
			printf("\n");
		}
	}

	char *pstr = cJSON_Print(root);
	updateFile(pstr);
	printf("\n已修改！\n");
	cJSON_Delete(root);
}

void updateFile(char *cjValue)
{
	// 打开文件
	FILE *file = fopen(FILE_NAME, "w");
	int ret = fwrite(cjValue, sizeof(char), strlen(cjValue), file);
	if (ret == 0)
	{
		printf("写入文件失败！");
	}

	fclose(file);
	free(cjValue);
}

void showBookStruct(book bok)
{
	cout << bok.id << endl;
	cout << bok.bookname << endl;
	cout << bok.aucther << endl;
	cout << bok.press << endl;
	cout << bok.publishTime << endl;
	cout << bok.price << endl;
}
