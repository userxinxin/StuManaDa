#include <stdio.h>
#include <stdlib.h>
#include "linklist.h"

//初始化节点
NODE* initNode(int id,char name[],int score)
{
	NODE* pTemp = (NODE*)malloc(sizeof(NODE));
	if (NULL == pTemp)
	{
		printf("新建信息格失败，请再试一次呢\n");
		return NULL;
	}
	int i = 0;
	pTemp->data.id = id;
	while (i < (int)(sizeof(pTemp->data.name)) - 1 && name[i] != '\0' && name[i] != '\n')
	{
		pTemp->data.name[i] = name[i];
		i++;
	}
	pTemp->data.name[i] = '\0';
	//namelen是加上终止符的长度
	pTemp->data.namelen = i + 1;
	pTemp->data.score = score;
	pTemp->next = NULL;
	return pTemp;
}

//初始化链表,给链表分配内存
LL* initLL()
{
	LL* pTemp = (LL*)malloc(sizeof(LL));
	if (NULL == pTemp)
	{
		printf("链表初始化失败\n");
		return NULL;
	}
	pTemp->pEnd = pTemp->pHead = NULL;
	pTemp->length = 0;
	return pTemp;
}

//将指针移动到指定位置
NODE* movePointer(LL* pList, int id)
{
	if (NULL == pList || 0 == pList->length)
	{
		printf("数据库为空，无法操作\n");
		return NULL;
	}
	NODE* pTemp = pList->pHead;
	int idx = findNode(pList, id);
	//int judge = 0;
	for (int i = 1; i < idx; i++)
	{
		pTemp = pTemp->next;
	}
	return pTemp;
}

//空链表添加数据
int appendList(LL* pList, int id,char name[],int score)
{
	NODE* pTemp = initNode(id,name,score);
	if (NULL == pTemp)
	{
		return 0;
	}
	//链表没有数据
	if (NULL == pList->pHead)
	{
		pList->pHead = pList->pEnd = pTemp;
	}
	pList->length++;
	pTemp = NULL;
	return 1;
}

//头插或者中间插
int insertNode(LL* pList, int id, char name[], int score)
{
	if (NULL == pList)
	{
		printf("数据库初始化失败\n");
		return 0;
	}
	//空表直接用上面的函数
	else if (NULL == pList->pHead)
	{
		if (1 == appendList(pList, id, name, score))
			return 1;
		else
			return 0;
	}
	//findnode找到了就返回位置而不是下标
	//没找到返回的-1
	if (findNode(pList, id) > 0)
	{
		printf("数据库中已经有这个id了，添加失败~\n");
		return 0;
	}
	NODE* pTemp = initNode(id, name, score);
	if (NULL == pTemp)
	{
		return 0;
	}


	//用头节点赋值给前驱节点
	NODE* pPre = pList->pHead;
	//pre,predecessor,前任，前辈，前驱
	//若表中只有一个数据，就不能进入循环，ppre就是head
	while (NULL != pPre->next)
	{
		if (pPre->next->data.id > id)
		//跳出时ppre是要插入的数据的上一个节点
			break;
		pPre = pPre->next;
	}
	//假如插入数据的id大于所有节点的id，那么ppre就会变成end，插入就要插到end后面
	//ok
	if (pPre == pList->pHead)
	{
		//插入到链表头部之前
		if (pTemp->data.id < pPre->data.id)
		{
			pTemp->next = pList->pHead;
			pList->pHead = pTemp;
		}
		//头部之后
		else
		{
			pTemp->next = pList->pHead->next;
			pList->pHead->next = pTemp;
			//pList->pHead = pTemp;
		}
		pList->length++;
		return 1;
	}
	if(pPre == pList->pEnd)
		//当它来到end了，end就要变成ptemp
	{
		//pList->pEnd->next = NULL;
		//插入到链表尾部
	/*	if (pTemp->data.id > pPre->data.id)
		{*/
			pList->pEnd->next = pTemp;
			pList->pEnd = pTemp;
			//pTemp->next = pList->pHead;
			//pList->pHead = pTemp;
		//}
	/*	else
		{
			pList->pEnd->next = pTemp;
			pList->pEnd = pTemp;
		}
		return 1;*/
		/*pList->pEnd->next = pTemp;
		pList->pEnd = pTemp;*/
		pList->length++;
		return 1;
	}
	//如果一次循环也没有执行

	//后面的ppre都是在要插入的数据之前
	pTemp->next = pPre->next;
	pPre->next = pTemp;
	//pPre->next = pTemp;
	pPre = NULL;
	pList->length++;
	pTemp = NULL;
	return 1;
}

//节点删除,头尾中间
int delNode(LL* pList, int id)
{
	if (NULL == pList || 0 == pList->length)
	{
		printf("数据库是空的，无法删除数据\n");
		return 0;
	}
	if (-1 == findNode(pList, id))
	{
		printf("该学生不存在\n\n");
		return 0;
	}
	if (0 == findNode(pList, id))
	{
		return 0;
	}
	int idx = findNode(pList, id);
	//idx获取到要删除的节点的位置
	int judge = 0;
	NODE* pTemp = pList->pHead;
	NODE* pPre = pTemp;
	//ppre是前驱
	for (int i = 1; i < pList->length; i++)
	{
		if (pTemp->data.id == id)
			break;
		pPre = pTemp;
		pTemp = pTemp->next;
	}
	if (pTemp->data.id == id)
	{
		printf("该学生的信息：\n");
		printfNode(pTemp);
		printf("您确定要删除吗？是请按1，否请按2\n");
		scanf_s("%d", &judge);
		if (1 == judge)
		{
			//ptemp是要删除的节点
			//ppre在删除节点前一个位置
			pPre->next = pTemp->next;
			pList->length--;
			free(pTemp);
			return 1;
		}
		else if (2 == judge)
		{
			printf("删除已取消~\n");
			return 0;
		}
		else
		{
			printf("无效选项，删除失败~\n");
			return 0;
		}
	}
	else
	{
		printf("没有找到该学生\n");
		return 0;
	}
}

//改
int modiNode(LL* pList, int id)
{
	if (NULL == pList || 0 == pList->length)
	{
		printf("数据库是空的，无法修改值\n");
		return 0;
	}
	if (-1 == findNode(pList, id))
	{
		printf("该学生不存在\n\n");
		return 0;
	}
	if (0 == findNode(pList, id))
	{
		return 0;
	}
	// 移动到要修改的位置
	NODE* pTemp = pList->pHead;
	int idx = findNode(pList, id);
	int judge = 0;
	for (int i = 1; i < idx; i++)
	{
		pTemp = pTemp->next;
	}
	printf("该学生的原信息：\n");
	printfNode(pTemp);
	printf("您想改变该学生的哪一栏信息?\n");
	printf("若是id请按1，姓名请按2，分数请按3\n");
	//若是输入失败了
	if (scanf_s("%d", &judge) != 1)
	{
		// 清空输入缓冲
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
		//返回输入数据错误后结束函数
		printf("输入无效\n");
		return 0;
	}
	if (1 == judge)
	{
		int newId = 0;
		printf("请输入新id:");
		if (scanf_s("%d", &newId) == 1)
		//scanf返回值是成功读取的项数，如果成功读取了一个整数，返回值是1
		{
			int find = findNode(pList, newId);
			if (find > 0)
			{
				printf("数据库中已经有这个id了\n");
				return 0;
			}
			
			pTemp->data.id = newId;
		}
		else
		{
			int ch;
			while ((ch = getchar()) != '\n' && ch != EOF);
			//这里也是要吸走垃圾，防止影响后面的输入
			printf("输入无效，修改失败\n");
			return 0;
		}
	}
	else if (2 == judge)
	{
		// 吸走其余垃圾字符（换行等）
		int ch;
		while ((ch = getchar()) != '\n' && ch != EOF);
		// 读取新姓名（使用 fgets 更安全）
		char newname[20];
		printf("请输入新姓名：");
		if (fgets(newname, sizeof(newname), stdin) == NULL)
			//stdin是从键盘输入，一般就这样写，这比scanf更安全
		{
			printf("读取姓名失败\n");
			return 0;
		}
		// 去除末尾换行符
		int len = 0;
		while (len < (int)(sizeof(newname)) - 1 && newname[len] != '\0' && newname[len] != '\n')
		{
			len++;
		}
		// 复制到节点的 name 数组并设置结束符及长度
		for (int i = 0; i < len; i++)
		{
			pTemp->data.name[i] = newname[i];
		}
		pTemp->data.name[len] = '\0';
		pTemp->data.namelen = len;
	}
	else if (3 == judge)
	{
		int newScore = 0;
		printf("请输入新分数:");
		if (scanf_s("%d", &newScore) == 1)
		{
			pTemp->data.score = newScore;
		}
		else
		{
			int ch;
			//吸走垃圾
			while ((ch = getchar()) != '\n' && ch != EOF);
			printf("输入无效，修改失败\n");
			return 0;
		}
	}
	else
	{
		printf("无效选项，修改失败~\n");
		return 0;
	}
	return 1;
}

//查,不能用二分，因为链表不支持随机访问，也不能指针偏移
//在增、改和查的地方用到了
//若找到了，就返回该数据的位置，>0
int findNode(LL* pList, int id)
{
	if (NULL == pList || 0 == pList->length)
	{
		printf("数据库是空的，无法查找\n");
		return 0;
	}
	int i = 0;
	NODE* pTemp = pList->pHead;
	while (NULL != pTemp)
	{
		i++;
		if (pTemp->data.id == id)
		{
			//返回学生的位置,是用户看到的位置，不是下标
			//如果找到的这个id是在第一位，那么他返回的值就是1
			return i;
		}
		pTemp = pTemp->next;
	}
	//printf("数据库中没有这个学生~\n");
	return -1;
}

//链表的死亡
//这里是只释放了表中的数据，表的内存还保留
void delLL(LL** pList)
{
	if (NULL == *pList)
	{
		printf("数据库不存在，无法释放\n");
		return;
	}
	if (0 == (*pList)->length)
	{
		free(*pList);
		*pList = NULL;
		return;
	}
	NODE* pTemp = (*pList)->pHead;
	while (NULL != (*pList)->pHead)
	{
		pTemp = (*pList)->pHead;
		(*pList)->pHead = (*pList)->pHead->next;
		free(pTemp);
		pTemp = NULL;
	}
	(*pList)->pEnd = NULL;
	(*pList)->length = 0;

}

//输出节点的学生信息
void printfNode(NODE* pTemp)
{
	printf("id：%d\n", pTemp->data.id);
	printf("姓名：");
	for (int i = 0; i < pTemp->data.namelen; i++)
	{
		putchar(pTemp->data.name[i]);
	}
	printf("\n分数：%d\n", pTemp->data.score);
	return;
}

//遍历链表
void printfLL(LL* pList)
{
	if (NULL == pList || 0 == pList->length)
	{
		printf("数据库是空的，无法查看\n\n");
		return;
	}
	NODE* pTemp = pList->pHead;
	printf("**********\n\n");
	while (NULL != pTemp)
	{
		/*printf("*****\n");*/
		printfNode(pTemp);
		printf("\n");
		pTemp = pTemp->next;
	}
	printf("**********\n");
	printf("表中共有%d个学生数据\n", pList->length);
	printf("\n");
}

