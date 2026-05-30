#pragma once

#include <stdio.h>
#include <stdlib.h>

//#ifndef MY_LINKLIST_H
//	#define MY_LINKLIST_H
//另一种保护头文件的写法，二选一


//定义链表的节点结构


//定义学生信息结构
//学生有编号，姓名，总分三个信息
typedef struct Student
{
	int id;
	char name[20];
	int namelen;
	int score;
}STUDENT;

typedef struct Node
{
	STUDENT data;
	struct Node* next;
}NODE;

//定义链表的结构
typedef struct LinkList
{
	NODE* pHead;
	NODE* pEnd;
	int length;
}LL;



//声明函数
NODE* initNode(int id, char name[], int score);

LL* initLL();

NODE* movePointer(LL* pList, int id);

void appendList(LL* pList, int id, char name[], int score);

int insertNode(LL* pList, int id, char name[], int score);

int delNode(LL* pList, int idx);

int modiNode(LL* pList, int idx);

int findNode(LL* pList, int id);

void delLL(LL** pList);

void printfNode(NODE* pTemp);

void printfLL(LL* pList);




//#endif // !MY_LINKLIST_H


