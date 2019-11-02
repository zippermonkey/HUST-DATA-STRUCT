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
PtrToLNode GetAdress(List L, int e);             // 返回某一个元素的前一个元素的地址值 不存在则返回最后一个节点的地址
status isinit(List L);                           // 判断L是否初始化
status InitList(List *L);                        // 初始化表
status DestroyList(List *L);                     // 摧毁表
status ClearList(List L);                        // 清空表
status ListEmpty(List L);                        // 表是否为空
status ListLength(List L);                       // 返回线性表长度
status GetElem(List L, int i, int *e);           // 用e返回第i位置的值
int LocateElem(List L, int e);                   // 返回e所在的位序
status PriorElem(List L, int cur_e, int *pre_e); // 用pre_e 带回 cur_e 的前驱
status NextElem(List L, int cur_e, int *next_e); // 用next_e带回 cur_e 的后继
status ListInsert(List L, int i, int e);         // 在i的位置上插入e
status ListDelete(List L, int i, int *e);        //  删除i的位置的值 用e带出
status ListTrabverse(List L);                    // 遍历

int main(void)
{
    List L = NULL;
    int op = 1;
    // 临时变量
    int i = 0, e = 0;
    int cur_e = 0, next_e = 0, pre_e = 0;
    status sta = OK;
    while (op)
    {
        system("cls");
        printf("\n\n");
        printf("      Menu for Linear Table On Sequence Structure \n");
        printf("-------------------------------------------------\n");
        printf("    	  - 1. InitList         - 7. LocateElem\n");
        printf("    	  - 2. DestroyList      - 8. PriorElem\n");
        printf("    	  - 3. ClearList        - 9. NextElem \n");
        printf("    	  - 4. ListEmpty        - 10. ListInsert\n");
        printf("    	  - 5. ListLength       - 11. ListDelete\n");
        printf("    	  - 6. GetElem          - 12. ListTrabverse\n");
        printf("    	  - 0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("    请选择你的操作[0~12]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            // sta = InitList(&L);
            // if (sta == OK)
            //     printf("线性表创建成功！\n");
            // else if (sta == OVERFLOW)
            //     printf("线性表创建失败！\n");
            // else if (sta == ERROR)
            //     printf("线性表已经创建\n");
            if (isinit(L))
                printf("线性表已经创建, 请选择2销毁 或者3清空\n");
            else
            {
                sta = InitList(&L);
                if (sta == OK)
                    printf("线性表创建成功！\n");
                else if (sta == OVERFLOW)
                    printf("线性表创建失败！\n");
            }
            getchar();
            getchar();
            break;
        case 2:
            // sta = DestroyList(&L);
            // if (sta == INFEASTABLE)
            //     printf("线性表未创建\n");
            // else if (sta == OK)
            //     printf("销毁成功\n");
            if (isinit(L) == FALSE)
                printf("线性表未创建\n");
            else
            {
                DestroyList(&L);
                printf("销毁成功\n");
            }
            getchar();
            getchar();
            break;
        case 3:
            // sta = ClearList(L);
            // if (sta == INFEASTABLE)
            //     printf("线性表未创建\n");
            // else if (sta == OK)
            //     printf("线性表清空成功\n");
            if (isinit(L) == FALSE)
                printf("线性表未创建\n");
            else
            {
                ClearList(L);
                printf("线性表清空成功\n");
            }
            getchar();
            getchar();
            break;
        case 4:
            // sta = ListEmpty(L);
            // if (sta == INFEASTABLE)
            //     printf("线性表未创建\n");
            // else if (sta == TRUE)
            //     printf("线性表为空\n");
            // else if (sta == FALSE)
            //     printf("线性表非空\n");
            if (isinit(L) == FALSE)
                printf("线性表未创建\n");
            else
            {
                if (ListEmpty(L) == TRUE)
                    printf("线性表为空\n");
                else
                    printf("线性表非空\n");
            }
            getchar();
            getchar();
            break;
        case 5:
            // sta = ListLength(L);
            // if (sta == ERROR)
            //     printf("线性表未创建\n");
            // else
            //     printf("线性表中的元素个数为 %d\n", sta);
            if (isinit(L) == FALSE)
                printf("线性表未创建\n");
            else
            {
                printf("线性表中的元素个数为 %d\n", ListLength(L));
            }
            getchar();
            getchar();
            break;
        case 6:
            // printf("请输入要取得元素的位序i: ");
            // scanf("%d", &i);
            // sta = GetElem(L, i, &e);
            // if (sta == ERROR)
            //     printf("线性表未创建\n");
            // else if (sta == ERROR)
            //     printf("i值不合法\n");
            // else if (sta == OK)
            //     printf("第%d位元素是%d\n", i, e);
            if (isinit(L) == FALSE)
                printf("线性表未创建\n");
            else
            {
                printf("请输入要取得元素的位序i: ");
                scanf("%d", &i);
                sta = GetElem(L, i, &e);

                if (sta == ERROR)
                    printf("i值不合法\n");
                else if (sta == OK)
                    printf("第%d位元素是%d\n", i, e);
            }
            getchar();
            getchar();
            break;
        case 7:
            if (isinit(L) == FALSE)
                printf("线性表未创建\n");
            else
            {
                printf("请输入要查找的元素值：");
                scanf("%d", &e);
                sta = LocateElem(L, e);
                if (sta == NOTFOUND)
                    printf("线性表中无此元素\n");
                else
                    printf("元素%d的位序是%d", e, sta);
            }
            getchar();
            getchar();
            break;
        case 8:
            if (isinit(L) == FALSE)
                printf("线性表未创建\n");
            else
            {
                printf("请输入要查找其前驱的元素值：");
                scanf("%d", &cur_e);
                sta = PriorElem(L, cur_e, &pre_e);
                if (sta == NOTFOUND)
                    printf("线性表中无此元素\n");
                else if (sta == ERROR)
                    printf("%d是第一个元素没有前驱\n", cur_e);
                else
                    printf("%d的前驱是%d\n", cur_e, pre_e);
            }
            getchar();
            getchar();
            break;
        case 9:
            if (isinit(L) == FALSE)
                printf("线性表未创建\n");
            else
            {
                printf("请输入要查找其后继的元素值：");
                scanf("%d", &cur_e);
                sta = NextElem(L, cur_e, &next_e);
                if (sta == NOTFOUND)
                    printf("线性表中无此元素\n");
                else if (sta == ERROR)
                    printf("%d是最后一个元素没有后继\n", cur_e);
                else
                    printf("%d的后继是%d\n", cur_e, next_e);
            }
            getchar();
            getchar();
            break;
        case 10:
            if (isinit(L) == FALSE)
                printf("线性表未创建\n");
            else
            {
                printf("请输入要插入的位置:");
                scanf("%d", &i);
                printf("请输入要插入的元素：");
                scanf("%d", &e);
                sta = ListInsert(L, i, e);
                if (sta == ERROR)
                    printf("插入位置不合法\n");
                else
                    printf("插入成功\n");
            }
            getchar();
            getchar();
            break;
        case 11:
            if (isinit(L) == FALSE)
                printf("线性表未创建\n");
            else
            {
                printf("请输入要删除的位置:");
                scanf("%d", &i);

                sta = ListDelete(L, i, &e);
                if (sta == ERROR)
                    printf("删除位置不合法\n");
                else
                    printf("删除%d成功\n", e);
            }
            getchar();
            getchar();
            break;
        case 12:
            if (isinit(L) == FALSE)
                printf("线性表未创建\n");
            else
            {
                sta = ListTrabverse(L);
                if (sta == ERROR)
                    printf("线性表为空表\n");
            }
            getchar();
            getchar();
            break;
        case 0:
            break;
        } //end of switch
    }     //end of while
    printf("欢迎下次再使用本系统！\n");
} //end of main()

status isinit(List L)
{
    if (L == NULL)
        return FALSE;
    else
        return TRUE;
}

PtrToLNode GetAdress(List L, int e)
{
    // 返回某一个元素的前一个元素的地址值 不存在则返回最后一个节点的地址
    PtrToLNode p = L;
    while (p->next && p->next->data != e)
        p = p->next;
    return p;
}

status InitList(List *L)
{
    // 如果已经存在
    // if (*L)
    //     return ERROR;
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
    // // 未创建
    // if ((*L) == NULL)
    //     return INFEASTABLE;

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
    // if (L == NULL)
    //     return INFEASTABLE;
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
    // if (L == NULL)
    //     return INFEASTABLE;
    PtrToLNode t = L->next;
    if (ListEmpty(L) == TRUE)
        return OK;
    else
        DestroyList(&t);
    L->next = NULL;
    L->data = 0;
    return OK;
}
int ListLength(List L)
{
    // 返回线性表长度

    // if (L == NULL) //未创建
    //     return INFEASTABLE;
    // else
    return L->data;
}
status GetElem(List L, int i, int *e)
{
    // if (L == NULL) //未创建
    //     return INFEASTABLE;
    // if (ListEmpty(L) == 0)
    //     return ERROR;

    if (i < 1 || i > ListLength(L)) //i 不合法
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

int LocateElem(List L, int e)
{
    // 返回e所在的为序  从1开始
    // if (L == NULL) //未创建
    //     return INFEASTABLE;

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
        return NOTFOUND;
}

status PriorElem(List L, int cur_e, int *pre_e)
{
    // if (L == NULL) //未创建
    //     return INFEASTABLE;

    PtrToLNode p = GetAdress(L, cur_e);
    if (p->next == NULL) // 没有这一个元素
        return NOTFOUND;
    else if (p == L) // 第一个元素  没有前驱
        return ERROR;
    else
    {
        *pre_e = p->data;
        return OK;
    }
}

status NextElem(List L, int cur_e, int *next_e)
{
    // if (L == NULL) //未创建
    //     return INFEASTABLE;

    PtrToLNode p = GetAdress(L, cur_e);
    if (p->next == NULL) // 没有这一个元素
        return NOTFOUND;
    else if (p->next->next == NULL) // 最后一个元素  没有后继
        return ERROR;
    else
    {
        *next_e = p->next->next->data;
        return OK;
    }
}

status ListInsert(List L, int i, int e)
{
    //在i的位置上插入e
    PtrToLNode p = L; // p为要插入的位置的前一个位置

    if (i < 1 || i > ListLength(L) + 1) //i 不合法
        return ERROR;
    else
        while (--i)
            p = p->next;
    PtrToLNode q = (PtrToLNode)malloc(sizeof(LNode));
    q->data = e;
    q->next = p->next;
    p->next = q;
    L->data++;
    return OK;
}

status ListDelete(List L, int i, int *e)
{
    // 删除i的位置的值 用e带出

    PtrToLNode p = L;               // p为要删除的位置的前一个位置
    if (i < 1 || i > ListLength(L)) //i 不合法
        return ERROR;
    else
        while (--i)
            p = p->next;
    PtrToLNode q = p->next;
    p->next = q->next;
    *e = q->data;
    free(q);
    L->data--;
    return OK;
}
status ListTrabverse(List L)
{ // 遍历
    if (ListEmpty(L) == TRUE)
        return ERROR;
    else
    {
        PtrToLNode p = L->next;
        while (p)
        {
            printf("%d", p->data);
            p = p->next;
            if (p)
                printf("  -->  ");
        }
    }
    printf("\n");
    return OK;
}