// 初始化表  InitList(L);
// DestroyList(L)
//ClearList(L)
// ListEmpty(L)
//初始条件是线性表L已存在；操作结果是若L为空表则返回TRUE,否则返回FALSE

// ListLength(L)
// GetElem(L,i,e) 1<=i<=ListLength(L)
//LocateElem(L,e)
//PriorElem(L,cur_e,pre_e)
//NextElem(L,cur_e,next_e)
//ListInsert(L,i,e)
//ListDelete(L,i,e)
//ListTraverse(L,visit())

/*********************************
 * 
 * 写一个函数来返回某一个元素的前一个元素的地址值会很方便  不存在则返回最后一个节点的位置
 * PtrToLNode GetAdress(List L, int e);
 * 
 * *************************************/

/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -3
#define INFEASTABLE -1
#define OVERFLOW -2
#define NOTFOUND -4

typedef int status;
typedef int ElemType; //数据元素类型定义

/*------- 节点定义 -------*/
typedef struct node
{
    ElemType data;
    struct node *next;
} LNode;

typedef LNode *PtrToLNode; // PtrToLNode 用来(PtrToLNode)malloc(sizeof(LNode));

// 由此定义线性表
typedef PtrToLNode List; //  List用来代表一个表  （带头节点） List L = (List)malloc(sizeof(LNode))  头节点的数据域用来存长度;

/*-------------函数声明-----------------*/
status InitList(List *L);                        // 初始化表
status DestroyList(List *L);                     // 摧毁表
status ClearList(List L);                        // 清空表
status ListEmpty(List L);                        // 表是否为空
status ListLength(List L);                       // 返回线性表长度
status GetElem(List L, int i, int *e);           // 用e返回第i位置的值
int LocateElem(List L, int *e);                  // 返回e所在的位序
status PriorElem(List L, int cur_e, int *pre_e); // 用pre_e 带回 cur_e 的前驱
status NextElem(List L, int cur_e, int *next_e); // 用next_e带回 cur_e 的后继

int main(void)
{
    List L = NULL;
    int op = 1;
    status sta = OK;
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitList       7. LocateElem\n");
        printf("    	  2. DestroyList    8. PriorElem\n");
        printf("    	  3. ClearList       9. NextElem \n");
        printf("    	  4. ListEmpty     10. ListInsert\n");
        printf("    	  5. ListLength     11. ListDelete\n");
        printf("    	  6. GetElem       12. ListTrabverse\n");
        printf("    	  0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~12]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            sta = InitList(&L);
            if (sta == OK)
                printf("线性表创建成功！\n");
            else if (sta == OVERFLOW)
                printf("线性表创建失败！\n");
            else if (sta == ERROR)
                printf("线性表已经创建\n");
            getchar();
            getchar();
            break;
        case 2:
            sta = DestroyList(&L);
            if (sta == INFEASTABLE)
                printf("线性表未创建\n");
            else if (sta == OK)
                printf("销毁成功\n");
            getchar();
            getchar();
            break;
        case 3:
            sta = ClearList(L);
            if (sta == INFEASTABLE)
                printf("线性表未创建\n");
            else if (sta == OK)
                printf("线性表清空成功\n");
            getchar();
            getchar();
            break;
        case 4:
            sta = ListEmpty(L);
            if (sta == INFEASTABLE)
                printf("线性表未创建\n");
            else if (sta == TRUE)
                printf("线性表为空\n");
            else if (sta == FALSE)
                printf("线性表非空\n");
            getchar();
            getchar();
            break;
        case 5:
            sta = ListLength(L);
            if (sta == ERROR)
                printf("线性表未创建");
            else
                printf("线性表中的元素个数为 %d\n", sta);
            getchar();
            getchar();
            break;
        case 6:
            printf("\n----GetElem功能待实现！\n");
            getchar();
            getchar();
            break;
        case 7:
            printf("\n----LocateElem功能待实现！\n");
            getchar();
            getchar();
            break;
        case 8:
            printf("\n----PriorElem功能待实现！\n");
            getchar();
            getchar();
            break;
        case 9:
            printf("\n----NextElem功能待实现！\n");
            getchar();
            getchar();
            break;
        case 10:
            printf("\n----ListInsert功能待实现！\n");
            getchar();
            getchar();
            break;
        case 11:
            printf("\n----ListDelete功能待实现！\n");
            getchar();
            getchar();
            break;
        case 12:
            //printf("\n----ListTrabverse功能待实现！\n");
            getchar();
            getchar();
            break;
        case 0:
            break;
        } //end of switch
    }     //end of while
    printf("欢迎下次再使用本系统！\n");
} //end of main()

status InitList(List *L)
{
    // 如果已经存在
    if (*L)
        return ERROR;
    // 分配空间
    (*L) = (List)malloc(sizeof(LNode)); // 创建一个带头节点的空链表
    if ((*L) == NULL)
        return (OVERFLOW);
    (*L)->next = NULL;
    (*L)->data = 0; // 0表示当前表的长度为0
    return OK;      // 创建成功

} // InitList

status DestroyList(List *L)
{
    // 未创建
    if ((*L) == NULL)
        return INFEASTABLE;

    // L是这个表的头节点  最后把free(L)
    // 然后把L为NULL
    PtrToLNode temp1 = (*L); // 临时变量指向头部
    PtrToLNode temp2 = temp1;

    while (temp1)
    {
        // 释放各个节点空间
        temp2 = temp1->next;
        free(temp1);
        temp1 = temp2;
    }
    // 将L置为空
    *L = NULL;
    return OK;
}
status ListEmpty(List L)
{
    // 未创建
    if (L == NULL)
        return INFEASTABLE;
    if (L->data == 0)
        return TRUE;
    else
        return FALSE;
}
status ClearList(List L)
{
    // 保留头节点 将头节点data设置为0
    // free 其他节点

    // 未创建
    if (L == NULL)
        return INFEASTABLE;
    PtrToLNode t = L->next;
    if (ListEmpty(L) == TRUE)
        return OK;
    else
        DestroyList(&t);

    L->next = NULL;
    L->data = 0;
    return OK;
}
status ListLength(List L)
{
    // 返回线性表长度

    if (L == NULL) //未创建
        return INFEASTABLE;
    else
        return L->data;
}
status GetElem(List L, int i, int *e)
{
    if (L == NULL) //未创建
        return INFEASTABLE;
    if (ListEmpty(L) == 0)
        return ERROR;

    if (i < 0 || i > ListLength(L)) //i 不合法
        return ERROR;

    int k = 0;
    PtrToLNode p = L->next;
    for (k = 1; k < i; k++)
    {
        p = p->next;
    }
    *e = p->data;
    return OK;
}
PtrToLNode GetAdress(List L, int e)
{
    // 返回某一个元素的前一个元素的地址值 不存在则返回最后一个节点的地址
    PtrToLNode p = L;
    while (p->next && p->next->data != e)
        p = p->next;
    return p;
}
int LocateElem(List L, int *e)
{
    // 返回e所在的为序  从1开始
    if (L == NULL) //未创建
        return INFEASTABLE;

    int i = 1;
    PtrToLNode p = L->next;
    while (p && p->data != e)
    {
        p = p->next;
        i++;
    }
    if (p) // 如果找到
        return i;
    else //没找到
        return ERROR;
}

status PriorElem(List L, int cur_e, int *pre_e)
{
    if (L == NULL) //未创建
        return INFEASTABLE;

    PtrToLNode p = GetAdress(L, cur_e);
    if (p->next == NULL) // 没有这一个元素
        return NOTFOUND;
    else if (p == L) // 第一个元素  没有前驱
        return ERROR;
    else
    {
        *pre_e = p->next->data;
        return OK;
    }
}