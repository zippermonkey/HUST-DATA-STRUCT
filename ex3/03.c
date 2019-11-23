#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define MAX_NUM 10

#define LIST_INIT_SIZE 50
#define LISTINCREMENT 10

#define LISTNUM 20

typedef char ElemType;
typedef int KeyType;
typedef int Status;

// 树节点定义
typedef struct TNode *Position;
typedef Position BiTree; // 二叉树类型
struct TNode
{
    KeyType key; //节点唯一标识符
    ElemType Data;
    BiTree Left, Right;
};

typedef struct treeinfo
{
    // 记录树的信息 名字 和 头节点
    char name[40];
    BiTree Head;
} TreeInfo;

typedef struct Trees // 多个二叉树管理
{
    int length;             // 存下的树的数目
    int listsize;           // 大小
    TreeInfo elem[LISTNUM]; // 每个元素包含树的基本属性  名字，头节点
} TreeMgr;

// 堆栈定义 链表实现
typedef struct SNode *PtrToSNode;
struct SNode
{
    BiTree Data;
    PtrToSNode Next;
};
typedef PtrToSNode Stack;

// 队列定义
typedef struct Node *PtrToQNode;
struct Node
{ /* 队列中的结点 */
    BiTree Data;
    PtrToQNode Next;
};

struct QMgr
{
    PtrToQNode Front, Rear; /* 队列的头、尾指针 */
    int MaxSize;            /* 队列最大容量 */
};
typedef struct QMgr *Queue;

int GetID(); //输入树的ID
Status InitBiTree(BiTree *T);
Status CreateBiTree(BiTree *T);
Status DestroyBiTree(BiTree *T);
Status ClearBiTree(BiTree T);
int BiTreeDepth(BiTree T);                          //求二叉树深度 递归实现
Status BiTreeEmpty(BiTree T);                       // 判断空二叉树
Position LocateNode(BiTree T, KeyType e);           // e为关键字返回e所在节点指针 如果没有 返回NULL
Status PreOrderTraverse(BiTree T);                  //前序
Status InOrderTraverse(BiTree T);                   //中序
Status PostOrderTraverse(BiTree T);                 //后序
Status LevelTraverse(BiTree T);                     //层序
Status Assign(BiTree T, KeyType e, ElemType value); //  节点赋值
Position GetSibling(T, e);                          //获取节点e的兄弟节点

int main()
{
    TreeMgr L;
    BiTree T1, T2;
    Position p;
    int op = 1, key;
    int i;
    int id = 1; // n代表在那棵树上操作  默认第一棵树
    char ch;
    int e = 0;
    for (i = 0; i < 20; i++)
    { // 初始化树管理
        L.elem[i].Head = NULL;
    }
    while (op)
    {
        //windows
        //system("cls"); //系统函数，用于清屏
        //linux
        system("clear");
        printf("\n\n");
        printf("     Menu for Binary Tree On Binary Linked List \n\n");
        printf("-------------------------------------------------\n");
        printf("    	  1. InitBiTree           2.CreateBiTree\n");
        printf("    	  3. DestroyBiTree           4.ClearBiTree\n");
        printf("    	  5. BiTreeEmpty           6. BiTreeDepth\n");
        printf("    	  7.LocateNode           \n");

        printf("            0. Exit\n");
        printf("-------------------------------------------------\n");
        printf("请选择你的操作[0~19]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            // 初始化树
            //if(L.elem[n-1].Head == NULL)  // 如果没有初始化
            id = GetID();
            InitBiTree(&(L.elem[id - 1].Head));
            printf("二叉树初始化成功\n");
            getchar();
            getchar();
            break;
        case 2:
            // 创建树
            id = GetID();
            if (L.elem[id - 1].Head == NULL) // 未初始化
                printf("二叉树不存在！\n");
            else
            {
                printf("前序 \'#\'表示空节点\n");
                if (CreateBiTree(&(L.elem[id - 1].Head)) == OK)
                    printf("二叉树创建成功\n\n");
            }
            break;
        case 3:
            // 销毁二叉树
            id = GetID();
            if (L.elem[id - 1].Head == NULL) // 未初始化
                printf("二叉树不存在！\n");
            else
            {
                DestroyBiTree(&(L.elem[id - 1].Head));
                printf("销毁成功\n");
            }
            getchar();
            getchar();
            break;
        case 4:
            // 清空二叉树 同时根节点为无效数据
            id = GetID();
            if (L.elem[id - 1].Head == NULL) // 未初始化
                printf("二叉树不存在！\n");
            else
            {
                ClearBiTree(L.elem[id - 1].Head);
                printf("清空成功\n");
            }
            getchar();
            getchar();
            break;
        case 5:
            // 判断空树
            id = GetID();
            if (L.elem[id - 1].Head == NULL) // 未初始化
                printf("二叉树不存在！\n");
            else
            {
                if (BiTreeEmpty(L.elem[id - 1].Head) == TRUE)
                    printf("二叉树为空\n");
                else
                    printf("二叉树不为空\n");
            }
            getchar();
            getchar();
            break;
        case 6:
            // 求深度 注意空树
            id = GetID();
            if (L.elem[id - 1].Head == NULL) // 未初始化
                printf("二叉树不存在！\n");
            else
            {
                // 空树处理
                if (BiTreeEmpty(L.elem[id - 1].Head))
                    printf("二叉树是空树 高度为0\n");
                else
                {
                    printf("二叉树的深度是%d\n", BiTreeDepth(L.elem[id - 1].Head));
                }
            }
            getchar();
            getchar();
            break;
        case 7:
            // LocateNode
            id = GetID();
            if (L.elem[id - 1].Head == NULL) // 未初始化
                printf("二叉树不存在！\n");
            else
            {
                printf("请输入要查找的key:");
                scanf("%d", &e);
                p = LocateNode(L.elem[id - 1].Head, e);
                if (p == NULL)
                    printf("不存在key为%d的节点\n", e);
                else
                    printf("key为%d的节点的地址是%p\n", e, p);
            }
            getchar();
            getchar();
            break;
        default:
            break;
        }
    }
    system("pause");
    return 0;
}
//堆栈操作
Stack CreateStack()
{ /* 构建一个堆栈的头结点，返回该结点指针 */
    Stack S;

    S = (Stack)malloc(sizeof(struct SNode));
    S->Next = NULL;
    return S;
}

bool IsEmptyS(Stack S)
{ /* 判断堆栈S是否为空，若是返回true；否则返回false */
    return (S->Next == NULL);
}

bool Push(Stack S, BiTree X)
{ /* 将元素X压入堆栈S */
    PtrToSNode TmpCell;

    TmpCell = (PtrToSNode)malloc(sizeof(struct SNode));
    TmpCell->Data = X;
    TmpCell->Next = S->Next;
    S->Next = TmpCell;
    return true;
}

BiTree Pop(Stack S)
{ /* 删除并返回堆栈S的栈顶元素 */
    PtrToSNode FirstCell;
    BiTree TopElem;

    if (IsEmptyS(S))
    {
        printf("堆栈空");
        return ERROR;
    }
    else
    {
        FirstCell = S->Next;
        TopElem = FirstCell->Data;
        S->Next = FirstCell->Next;
        free(FirstCell);
        return TopElem;
    }
}

/* 队列操作 */
Queue CreateQueue()
{
    // 创建一个队列
    Queue Q;

    Q = (Queue)malloc(sizeof(struct QMgr));
    Q->Front = NULL;
    Q->Rear = NULL;
    Q->MaxSize = 0;
    return Q;
}

bool IsEmptyQ(Queue Q)
{
    return (Q->Front == NULL);
}

BiTree DeleteQ(Queue Q)
{
    PtrToQNode FrontCell;
    BiTree FrontElem;

    if (IsEmptyQ(Q))
    {
        printf("队列空");
        return ERROR;
    }
    else
    {
        FrontCell = Q->Front;
        if (Q->Front == Q->Rear)       /* 若队列只有一个元素 */
            Q->Front = Q->Rear = NULL; /* 删除后队列置为空 */
        else
            Q->Front = Q->Front->Next;
        FrontElem = FrontCell->Data;

        free(FrontCell); /* 释放被删除结点空间  */
        return FrontElem;
    }
}

bool AddQ(Queue Q, BiTree X)
{ //添加节点到队列  分队列空与不空
    PtrToQNode RearCell = (PtrToQNode)malloc(sizeof(struct Node));
    RearCell->Data = X;
    RearCell->Next = NULL;

    Q->Rear->Next = RearCell;
    Q->Rear = Q->Rear->Next;
    Q->MaxSize++;

    if (Q->Front == NULL) //如果队列之前为空
        Q->Front = RearCell;

    return true;
}

int GetID()
{
    // 输入ID
    int id = 0;
    printf("请输入id(1-%d)：", LISTNUM);
    scanf("%d", &id);
    while (id < 1 || id > LISTNUM)
    {
        printf("id值无效，请重新输入id(1-%d)：", LISTNUM);
        scanf("%d", &id);
    }
    return id;
}

/* 二叉树操作 */
Status InitBiTree(BiTree *T)
{
    // 初始化
    (*T) = (BiTree)malloc(sizeof(struct TNode));
    (*T)->Left = NULL;
    (*T)->Right = NULL;
    (*T)->Data = '#'; //左右子树为空
    return OK;
}

Status CreateBiTree(BiTree *T)
{ //待修改  问题：怎么添加唯一表示符号key 同时让key有意义
    // 如果使用堆栈实现 key 为满二叉树的顺序
    //fflush(stdin);
    char ch; //读取字符
    char c;
    while ((c = getchar()) != EOF && c != '\n')
        ;
    int i = 1; //i作为key
    int quit = 0;
    // 先不管根
    BiTree Temp = NULL; //临时节点
    BiTree Cur;
    Stack S = CreateStack(); // 创建一个空堆栈 记得free掉
    int isroot = 1;
    int R = 0;
    do
    {
        scanf("%c", &ch);
        while ((c = getchar()) != EOF && c != '\n')
            ;
        if (ch == '#')
        {
            Temp = NULL;
            if (R)
                quit = 1;
            if (!IsEmptyS(S))
            {
                Temp = Pop(S);
                i = Temp->key;
                R = 1;
                Cur = Temp;
                Temp = Temp->Right;
            }
        }
        else
        {
            Temp = (BiTree)malloc(sizeof(struct TNode));
            Temp->Data = ch;
            Push(S, Temp);
            if (isroot)
            {
                Temp->key = 1; //根节点key为1
                (*T) = Temp;
                isroot = 0;
            }
            else
            {
                if (R) // 如果当前是右子树
                {
                    Cur->Right = Temp;
                    Temp->key = i * 2 + 1;
                    R = 0;
                }
                else
                {
                    Cur->Left = Temp;
                    Temp->key = i * 2;
                }
                i = Temp->key; // 用i记住放入堆栈的元素的key
            }
            Cur = Temp;
            Temp = Temp->Left;
        }
    } while (!IsEmptyS(S) || quit == 0);
    free(S);
    while ((c = getchar()) != EOF && c != '\n')
        return OK;
}

Status PreOrderTraverse(BiTree T)
{
    // 递归前序遍历
    if (T == NULL)
        return 0;
    else
    {
        printf("%c  ", T->Data);
        PreOrderTraverse(T->Left);
        PreOrderTraverse(T->Right);
    }
    return OK;
}
Status PostOrderTraverse(BiTree T)
{
    // 递归后序遍历
    if (T == NULL)
        return 0;
    else
    {
        PreOrderTraverse(T->Left);
        PreOrderTraverse(T->Right);
        printf("%c  ", T->Data);
    }
    return OK;
}
Status InOrderTraverse(BiTree T)
{
    BiTree P = T;
    Stack S = CreateStack();
    while (P || !IsEmptyS(S))
    {
        while (P)
        { // 一直沿左压入堆栈
            Push(S, P);
            P = P->Left;
        }
        if (!IsEmptyS(S))
        {
            P = Pop(S);
            printf("%c  ", P->Data);
            P = P->Right; // 转向右子树
        }
    }
}

Status LevelTraverse(BiTree T)
{
    // 层序遍历  不用管空树 在main中处理
    // 使用队列实现
    Queue Q;
    BiTree P;
    Q = CreateQueue();
    AddQ(Q, T); //将根节点放入队列
    while (!IsEmptyQ(Q))
    {
        P = DeleteQ(Q);
        printf("%c  ", P->Data);
        if (T->Left)
            AddQ(Q, P->Left);
        if (T->Right)
            AddQ(Q, P->Right);
    }
    return OK;
}

Status DestroyBiTree(BiTree *T)
{
    // 递归将左右子树销毁
    if (*T)
    {
        if ((*T)->Left)
            DestroyBiTree(&((*T)->Left));
        if ((*T)->Right)
            DestroyBiTree(&((*T)->Right));
        free(*T); // 说明是叶子节点
        (*T) = NULL;
    }
    return OK;
}

Status ClearBiTree(BiTree T)
{
    // 分别将左右子树销毁
    DestroyBiTree(&(T->Left));
    DestroyBiTree(&(T->Right));
    T->Data = '#'; // 同时将根结点设置为空
    return OK;
}
int BiTreeDepth(BiTree T)
{
    // 递归求二叉树深度
    int HL, HR, MaxH;
    if (T)
    {
        HL = BiTreeDepth(T->Left);
        HR = BiTreeDepth(T->Right);
        MaxH = (HL > HR) ? HL : HR;
        return 1 + MaxH;
    }
    return 0;
}
Status BiTreeEmpty(BiTree T)
{
    // 判断空二叉树
    if (T->Data == '#')
        return TRUE;
    else
        return FALSE;
}
Position LocateNode(BiTree T, KeyType e)
{
    // 利用key 反向生成查找序列
    BiTree P = T;
    int n = (int)(log2(e)); // 序列长度
    int x = e;
    int path[n]; // 左0右1
    int i = 0;
    for (i = n - 1; i >= 0; i--)
    {
        // 反向生成查找序列
        if (x % 2 == 1)
            path[i] = 1;
        else
            path[i] = 0;
        x /= 2;
    }
    for (i = 0; i < n && P; i++)
    {
        if (path[i]) // 右边
            P = P->Right;
        else
            P = P->Left;
    }
    return P;
}
Status Assign(BiTree T, KeyType e, ElemType value)
{
    //节点赋值
    Position Temp = LocateNode(T, e);
    if (Temp == NULL) //没有key为e的节点
        return ERROR;
    else
    {
        Temp->Data = value;
        return OK;
    }
}
Position GetSibling(T, e)
{
    // 获取兄弟节点
    int se;
    se = (e % 2) ? e - 1 : e + 1;
    return LocateNode(T, se);
}