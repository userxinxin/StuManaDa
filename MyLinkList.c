#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

//5.22
//查找信息失败，而且namelen总是19
//插入信息是成功的，插入函数里面包含了查找函数

int main(void)
{
	LL *pList = initLL();
	int number = 0;
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
				printf("id：");
				scanf_s("%d", &id);
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
				printf("分数：");
				scanf_s("%d", &score);
				//输入之后应该按id重新将表的内容排序
				if (1 == insertNode(pList, id, name, score))
					printf("添加成功~\n");
				//findNode(pList, id);
				printf("\n");
				//printf("%d\n", pList->pHead->data.namelen);
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
				printf("输入的数据有误，再输一下嘞\n");
				goto ininput;
			}
		}
		else if (3 == number)
			break;
		else
		{
			printf("输入的数据有误，再输一下嘞\n");
			goto input;
		}
	}

	//如果把数据存储，最后就不用释放了，而是更新
	//如果在程序中没有释放指针，下一次运行程序会被上一次未释放的内存影响吗
	delLL(&pList);
	//delLL(pList);

	free(pList);

	return 0;
}
//怎么才能把新记录提交到github嘞