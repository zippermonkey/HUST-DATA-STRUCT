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
};
typedef struct QMgr *Queue;

int GetID(); //输入树的ID
Status InitBiTree(BiTree *T);
Status CreateBiTree(BiTree *T);
Status DestroyBiTree(BiTree *T);
Status ClearBiTree(BiTree T);
int BiTreeDepth(BiTree T);                                  //求二叉树深度 递归实现
Status BiTreeEmpty(BiTree T);                               // 判断空二叉树
Position LocateNode(BiTree T, KeyType e);                   // e为关键字返回e所在节点指针 如果没有 返回NULL
Status PreOrderTraverse(BiTree T);                          //前序
Status InOrderTraverse(BiTree T);                           //中序
Status PostOrderTraverse(BiTree T);                         //后序
Status LevelTraverse(BiTree T);                             //层序
Status Assign(BiTree T, KeyType e, ElemType value);         //  节点赋值
Position GetSibling(BiTree T, KeyType e);                   //获取节点e的兄弟节点
Status InsertNode(BiTree T, KeyType e, int LR, ElemType c); //插入节点
Status DeleteNode(BiTree T, KeyType e);                     // 删除节点
Status PrintTNodeInfo(Position node);                       //打印一个节点的信息
Status PrintAllInfo(BiTree T, Position node);               //打印一个节点的信息
Status SaveTreeToFile(BiTree T);                            // 将树保存到文件里面 存储key和Data
Status LoadTreeFromFile(BiTree *T);                         // 从文件恢复二叉树
int main()
{
    TreeMgr L;
    BiTree T1, T2;
    Position p;
    int op = 1, key;
    int i;
    int LR = 0;
    int id = 1; // n代表在那棵树上操作  默认第一棵树
    char ch;
    char c;
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
        printf("1. InitBiTree\t\t\t\t2. CreateBiTree\n");
        printf("3. DestroyBiTree\t\t\t4. ClearBiTree\n");
        printf("5. BiTreeEmpty\t\t\t\t6. BiTreeDepth\n");
        printf("7.LocateNode\t\t\t\t8. Assign \n");
        printf("9. GetSibling\t\t\t\t10. InsertNode \n");
        printf("11. DeleteNode\t\t\t\t12. PreOrderTraverse \n");
        printf("13. InOrderTraverse\t\t\t14. PostOrderTraverse \n");
        printf("15. LevelOrderTraverse\t\t\t16. SaveTree\n");
        printf("17. LoadTree\t\t\t\t0. Exit\n");
        printf("-------------------------------------------------\n");

        printf("请选择你的操作[0~15]:");
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
                {
                    printf("key为%d的节点的地址是%p\n", e, p);
                    PrintAllInfo(L.elem[id - 1].Head, p);
                }
            }
            getchar();
            getchar();
            break;
        case 8:
            // Assign
            id = GetID();
            if (L.elem[id - 1].Head == NULL) // 未初始化
                printf("二叉树不存在！\n");
            else
            {
                printf("请输入要赋值的节点的key:");
                scanf("%d", &e);
                p = LocateNode(L.elem[id - 1].Head, e);
                if (p == NULL)
                    printf("不存在key为%d的节点\n", e);
                else
                {
                    printf("请输入要更改的值：");
                    while ((c = getchar()) != EOF && c != '\n')
                        ;
                    scanf("%c", &ch);
                    Assign(L.elem[id - 1].Head, e, ch);
                    printf("赋值成功\n");
                }
            }
            getchar();
            getchar();
            break;
        case 9:
            //GetSibling
            id = GetID();
            if (L.elem[id - 1].Head == NULL) // 未初始化
                printf("二叉树不存在！\n");
            else
            {
                printf("请输入要查找的节点的key:");
                scanf("%d", &e);
                p = LocateNode(L.elem[id - 1].Head, e);
                if (p == NULL)
                    printf("不存在key为%d的节点\n", e);
                else
                {
                    p = GetSibling(L.elem[id - 1].Head, e);
                    if (p)
                    {
                        printf("key为%d的节点的兄弟的地址是%p\n", e, p);
                        PrintAllInfo(L.elem[id - 1].Head, p);
                    }
                    else
                    {
                        printf("key为%d的节点没有兄弟节点\n", e);
                    }
                }
            }
            getchar();
            getchar();
            break;
        case 10:
            // InsertNode
            id = GetID();
            if (L.elem[id - 1].Head == NULL) // 未初始化
                printf("二叉树不存在！\n");
            else
            {
                printf("请输入要查找的节点的key:");
                scanf("%d", &e);
                p = LocateNode(L.elem[id - 1].Head, e);
                if (p == NULL)
                    printf("不存在key为%d的节点\n", e);
                else
                {
                    printf("请输入要插入的字符量:");
                    while ((c = getchar()) != EOF && c != '\n')
                        ;
                    scanf("%c", &ch);
                    printf("插入在左树或者右树（左0右1）");
                    scanf("%d", &LR);
                    if (InsertNode(L.elem[id - 1].Head, e, LR, ch) == OK)
                        printf("插入成功\n");
                }
            }
            getchar();
            getchar();
            break;
        case 11:
            // DeleteNode
            id = GetID();
            if (L.elem[id - 1].Head == NULL) // 未初始化
                printf("二叉树不存在！\n");
            else
            {
                printf("请输入要查找的节点的key:");
                scanf("%d", &e);
                p = LocateNode(L.elem[id - 1].Head, e);
                if (p == NULL)
                    printf("不存在key为%d的节点\n", e);
                else
                {
                    DeleteNode(L.elem[id - 1].Head, e);
                    printf("删除成功\n");
                }
            }

            getchar();
            getchar();
            break;
        case 12:
            id = GetID();
            if (L.elem[id - 1].Head == NULL) // 未初始化
                printf("二叉树不存在！\n");
            else
                PreOrderTraverse(L.elem[id - 1].Head);
            getchar();
            getchar();
            break;
        case 13:
            id = GetID();
            if (L.elem[id - 1].Head == NULL) // 未初始化
                printf("二叉树不存在！\n");
            else
                InOrderTraverse(L.elem[id - 1].Head);
            getchar();
            getchar();
            break;
        case 14:
            id = GetID();
            if (L.elem[id - 1].Head == NULL) // 未初始化
                printf("二叉树不存在！\n");
            else
                PostOrderTraverse(L.elem[id - 1].Head);
            getchar();
            getchar();
            break;
        case 15:
            id = GetID();
            if (L.elem[id - 1].Head == NULL) // 未初始化
                printf("二叉树不存在！\n");
            else
                LevelTraverse(L.elem[id - 1].Head);
            getchar();
            getchar();
            break;
        case 16:
            // Save
            id = GetID();
            if (L.elem[id - 1].Head == NULL) // 未初始化
                printf("二叉树不存在！\n");
            else
                SaveTreeToFile(L.elem[id - 1].Head);
            getchar();
            getchar();
            break;
        case 17:
            id = GetID();
            if (L.elem[id - 1].Head == NULL) // 未初始化
                printf("二叉树不存在！\n");
            else
                LoadTreeFromFile(&(L.elem[id - 1].Head));
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

    if (Q->Front == NULL) //如果队列之前为空
    {
        Q->Rear = RearCell;
        Q->Front = RearCell;
    }
    else
    {
        Q->Rear->Next = RearCell;
        Q->Rear = Q->Rear->Next;
    }
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
    (*T)->key = 0;
    (*T)->Data = '#'; //左右子树为空
    return OK;
}

Status CreateBiTree(BiTree *T)
{
    // 如果使用堆栈实现 key 为满二叉树的顺序
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
                quit = 0;
            }
        }
        else
        {
            Temp = (BiTree)malloc(sizeof(struct TNode));
            Temp->Data = ch;
            Temp->Left = Temp->Right = NULL;
            Push(S, Temp);
            if (isroot)
            {
                Temp->key = 1; //根节点key为1
                (*T)->Right = Temp;
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
        ;
    return OK;
}

Status PreOrderTraverse(BiTree T)
{
    // 递归前序遍历
    if (T == NULL)
        return 0;
    else
    {
        if (T->key != 0)
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
        if (T->key != 0)
            printf("%c  ", T->Data);
    }
    return OK;
}
Status InOrderTraverse(BiTree T)
{ //T是头节点

    BiTree P = T->Right; //P作为树的根结点
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
    AddQ(Q, T->Right); //将根节点放入队列
    while (!IsEmptyQ(Q))
    {
        P = DeleteQ(Q);
        printf("%c  ", P->Data);
        if (P->Left)
            AddQ(Q, P->Left);
        if (P->Right)
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
    // 传入头节点 最后只剩下头节点
    DestroyBiTree(&(T->Right));
    T->Right = NULL;
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
        if (T->key == 0)
            return MaxH;
        return 1 + MaxH;
    }
    return 0;
}
Status BiTreeEmpty(BiTree T)
{
    // 判断空二叉树
    if (T->Right == NULL)
        return TRUE;
    else
        return FALSE;
}
Position LocateNode(BiTree T, KeyType e)
{
    if (e <= 0)
        return NULL;

    // 利用key 反向生成查找序列
    BiTree P = T->Right;
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
    if (e <= 0)
        return ERROR;
    Position Temp = LocateNode(T, e);
    Temp->Data = value;
    return OK;
}
Position GetSibling(BiTree T, KeyType e)
{
    // 获取兄弟节点
    KeyType se;
    // if (e == 1)
    //     return NULL;
    se = (e % 2) ? e - 1 : e + 1;
    return LocateNode(T, se);
}

Status InsertNode(BiTree T, KeyType e, int LR, ElemType c)
{
    // 插入节点  问题：修改key
    // LR 0 左   1 右

    // 第一步 找到e节点
    Position P = LocateNode(T, e);
    Position X = NULL;
    Position SubTree = NULL;
    // 2 修改树结构
    if (P == NULL) // 可以去除  main保证一定存在
    {
        // 如果e不存在
        return ERROR;
    }
    else
    {
        X = (Position)malloc(sizeof(struct TNode));
        X->Data = c;
        X->Left = NULL;
        if (LR == 0) //左边
        {
            X->key = P->key * 2;
            SubTree = P->Left;
            P->Left = X;
        }
        else if (LR == 1) //右边
        {
            X->key = P->key * 2 + 1;
            SubTree = P->Right;
            P->Right = X;
        }
        else //LR 非法
        {
            return ERROR;
        }
        X->Right = SubTree;
    }
    // 3 修改子树key  SubTree
    Stack S = CreateStack();
    //SubTree->key = X->key*2+1; // 初始化子树根key
    Position Temp = SubTree;

    BiTree Cur = X;
    int L = 0;
    while (Temp || !IsEmptyS(S))
    {
        while (Temp)
        { // 一直沿you压入堆栈
            if (L == 0)
            {
                Temp->key = Cur->key * 2 + 1;
            }
            else
            {
                Temp->key = Cur->key * 2;
                L = 0;
            }
            Cur = Temp;
            Push(S, Temp);
            Temp = Temp->Right;
        }
        if (!IsEmptyS(S))
        {
            Temp = Pop(S);
            Cur = Temp;
            Temp = Temp->Left; // 转向zuo子树
            L = 1;
        }
    }
    return OK;
}
Status DeleteNode(BiTree T, KeyType e)
{
    // 删除key为e的节点
    // 1 找到其父节点

    // 判断e是否存在  //主函数里搞定了 可以删除
    if (LocateNode(T, e) == NULL)
        return ERROR;

    // F 表示e的父节点
    Position F;
    if (e == 1)
        F = T;
    else
        F = LocateNode(T, e / 2);
    // D 表示要删除的节点
    Position D = LocateNode(T, e);

    // 先做节点的调整

    //D 是 F的左还是右
    Position *FChild = NULL;
    if (e % 2 == 0)
        FChild = &(F->Left);
    else if (e % 2 == 1)
        FChild = &(F->Right);

    // 如果是叶子节点 直接处理了
    if (D->Left == NULL && D->Right == NULL)
    { //D是叶子节点
        *FChild = NULL;
        free(D);
        return OK;
    }
    else
    {
        // 度为1 2
        if (D->Left)
        {
            *FChild = D->Left;
        }
        else if (D->Right)
        {
            *FChild = D->Right;
        }
        // 找到D的左子树的最右边节点 用MR表示
        Position MR = D->Left;
        while (MR && MR->Right)
            MR = MR->Right;
        if (MR)
            MR->Right = D->Right;

        // 2. 修改key
        // 此时正确的key是F里面的  要修改的子树的根是*FChild
        BiTree SubTree = *FChild;
        Position Temp = SubTree;
        Position Cur = F;

        Stack S = CreateStack();
        int L;
        L = (e % 2 == 0) ? 1 : 0;
        while (Temp || !IsEmptyS(S))
        {
            while (Temp)
            { // 一直沿you压入堆栈
                if (L == 0)
                {
                    Temp->key = Cur->key * 2 + 1;
                }
                else
                {
                    Temp->key = Cur->key * 2;
                    L = 0;
                }
                Cur = Temp;
                Push(S, Temp);
                Temp = Temp->Right;
            }
            if (!IsEmptyS(S))
            {
                Temp = Pop(S);
                Cur = Temp;
                Temp = Temp->Left; // 转向zuo子树
                L = 1;
            }
        }
        return OK;
    }
}
Status PrintTNodeInfo(Position node)
{
    // key Data
    printf("key: %d\nData: %c\n", node->key, node->Data);
    return OK;
}
Status PrintAllInfo(BiTree T, Position node)
{
    Position parents = LocateNode(T, node->key / 2);
    PrintTNodeInfo(node);
    if (parents)
    {
        printf("Parents info:\n");
        PrintTNodeInfo(parents);
    }
    if (node->Left)
    {
        printf("Left child info:\n");
        PrintTNodeInfo(node->Left);
    }
    if (node->Right)
    {
        printf("Right child info:\n");
        PrintTNodeInfo(node->Right);
    }
    return OK;
}

Status SaveTreeToFile(BiTree T)
{
    FILE *fp;
    char filename[41];
    printf("Please input filename: ");
    scanf("%s", filename);
    // 写文件
    if ((fp = fopen(filename, "wb")) == NULL) //文件打开失败
    {
        printf("File open error\n ");
        return ERROR;
    }
    // 使用层序遍历的顺序保存  照抄一下层序
    Queue Q;
    BiTree P;
    KeyType key;
    ElemType data;
    Q = CreateQueue();
    AddQ(Q, T->Right); //将根节点放入队列
    while (!IsEmptyQ(Q))
    {
        P = DeleteQ(Q);
        //printf("%c  ", P->Data);  改成保存
        key = P->key;
        data = P->Data;
        fwrite(&(key), sizeof(KeyType), 1, fp);
        fwrite(&(data), sizeof(ElemType), 1, fp);
        if (P->Left)
            AddQ(Q, P->Left);
        if (P->Right)
            AddQ(Q, P->Right);
    }
    fclose(fp);
    return OK;
}
Status LoadTreeFromFile(BiTree *T)
{
    FILE *fp;
    BiTree P = (*T);
    BiTree Temp = NULL;
    char filename[41];
    printf("input filename: ");
    scanf("%s", filename);
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("File open error\n ");
        return ERROR;
    }
    // 1. 根节点
    Temp = (BiTree)malloc(sizeof(struct TNode));
    fread(&(Temp->key), sizeof(KeyType), 1, fp);
    fread(&(Temp->Data), sizeof(ElemType), 1, fp);
    Temp->Left = Temp->Right = NULL;
    (*T)->Right = Temp;

    //2. 其他节点
    Temp = (BiTree)malloc(sizeof(struct TNode));
    while (fread(&(Temp->key), sizeof(KeyType), 1, fp) && fread(&(Temp->Data), sizeof(ElemType), 1, fp))
    {
        Temp->Left = Temp->Right = NULL;
        P = LocateNode((*T), Temp->key / 2);
        if (Temp->key % 2 == 0) // Temp是p的左儿子
            P->Left = Temp;
        else if (Temp->key % 2 == 1)
            P->Right = Temp;
        Temp = (BiTree)malloc(sizeof(struct TNode));
    }
    fclose(fp);
    return OK;
}