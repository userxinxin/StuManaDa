#include <stdio.h>
#include <stdlib.h>
//#include <>
#include "linklist.h"
//我们还缺什么，数据库，可以用write的方式写到txt里
// 
//这个程序完成后再赋值一份，改成双向链表
int main(void)
{
	//FILE* pFile = NULL;
	LL *pList = initLL();
	int number = 0;
	//用写入模式打开文件
	//fopen_s(&pFile, "database.txt", "w+");
	//创建链表
	printf("欢迎来到学生信息管理数据库！\n");
	while (1) 
	{
		input:
		printf("查看表中信息请按1，操作数据请按2，退出请按3\n");
		scanf_s("%d", &number);
		if (1 == number)
		{
			printfLL(pList);
		}
		else if (2 == number)
		{
			int innumber = 0;
			ininput:
			printf("增加数据请按1，删除数据请按2，修改数据请按3，查找数据请按4\n");
			printf("请输入数字：");
			scanf_s("%d", &innumber);
			if (1 == innumber)
			{
				int id = 0, score = 0;
				int i = 0;
				char name[20] = { '\0' };
				printf("请输入新增学生的信息\n");
				reid:
				printf("id：");
				scanf_s("%d", &id);
				if (id <= 0)
				{
					printf("id不能为0或负数，请重新输入\n");
					goto reid;
				}
				//吸走垃圾字符
				while ((getchar()) != '\n');
				printf("姓名:");
				int a = 0;
				for (i = 0; i < 19; i++)
				{
					scanf_s("%c", &name[i], 1);
					if ('\n' == name[i])
					{
						a++;
						break;
					}
				}
				name[i] = '\0';
				rescore:
				printf("分数：");
				scanf_s("%d", &score);
				if(score < 0 || score > 750)
				{
					printf("分数必须在0到750之间，请重新输入\n\n");
					goto rescore;
				}
				//输入之后应该按id重新将表的内容排序
				if (1 == insertNode(pList, id, name, score))
					printf("添加成功~\n");
				printf("\n");
			}
			else if (2 == innumber)
			{
				int id = 0;
				printf("请输入想删除的学生信息的id：");
				scanf_s("%d", &id);
				if (1 == delNode(pList, id))
					printf("删除成功~\n\n");
				//printf("\n");
			}
			else if (3 == innumber)
			{
				int id = 0;
				printf("请输入想修改的学生id：");
				scanf_s("%d", &id);
				if (1 == modiNode(pList, id))
					printf("修改成功~\n\n");
				else
					printf("修改失败~\n\n");
			}
			else if (4 == innumber)
			{
				int id = 0; 
				int find = 0;
				printf("请输入想查找的学生id：");
				scanf_s("%d", &id);
				find = findNode(pList, id);
				if (find > 0)
				{
					printfNode(movePointer(pList, id));
					printf("该学生存在于在表中第%d个位置\n", find);
				
				}
				else if (-1 == find)
					printf("表中没有该学生\n");
				printf("\n");
			}
			else
			{
				printf("输入的数据有误，请重试\n");
				goto ininput;
			}
		}
		else if (3 == number)
			break;
		else
		{
			printf("输入的数据有误，请重试\n");
			goto input;
		}
		//fwrite(pList, sizeof(), 1, pFile);
		//fwrite的参数1是要写入的内容，参数2是内容长度，参数四是文件指针
	}

	//fclose(pFile);
	delLL(&pList);
	//delLL(pList);

	free(pList);

	return 0;
}