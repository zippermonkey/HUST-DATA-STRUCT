/* Linear Table On Sequence Structure */
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR -1
#define INFEASTABLE -1
#define OVERFLOW -2
#define MAX_NAME 3
#define LISTNUM 10 //多图的数目

typedef int Status;

//---------队列----------------
// 队列定义
typedef struct Node *PtrToQNode;
struct Node
{ /* 队列中的结点 */
    int Data;
    PtrToQNode Next;
};

struct QMgr
{
    PtrToQNode Front, Rear; /* 队列的头、尾指针 */
};
typedef struct QMgr *Queue;

// ------ 有向图的十字链表存储表示--------
typedef char VertexType;
typedef int KeyType;
#define MAX_VERTEX_NUM 20
int visited[MAX_VERTEX_NUM];

typedef struct ArcBox
{                                 // 弧结构
    int tailvex, headvex;         //该弧的尾和头顶点的位置
    struct ArcBox *hlink, *tlink; //分别为弧头相同和弧尾相同的弧的链域
    // info
} ArcBox;
typedef struct VexNode
{
    // 顶点结构
    VertexType data;
    KeyType key; // 保持与顶点存储位置相同
    ArcBox *firstin, *firstout;
} VexNode;
typedef struct
{
    VexNode xlist[MAX_VERTEX_NUM]; //表头向量
    int vexnum, arcnum;            //有向图当前的顶点数和弧数
    int isinit;                    // 标记是否创建  销毁时 置为0
} OLGraph;

// 函数声明
/*--------队列-------*/
Queue CreateQueue();       // 创建队列
bool IsEmptyQ(Queue Q);    // 队列为空？
int DeleteQ(Queue Q);      // 出队
bool AddQ(Queue Q, int X); // 入队

/*-------有向图------*/
int LocateVex_bydata(OLGraph *G, VertexType v);     // 定位v在G中的位置
Status CreateDG(OLGraph *G);                        // v 点集合  vr边集合 // 后进先出链表
Status DestroyGraph(OLGraph(*G));                   // 销毁图
Status PutVex(OLGraph *G, KeyType key, char value); // 顶点赋值
int FirstAdjVex(OLGraph *G, int v);                 // 获取第一邻接顶点
int NextAdjVex(OLGraph *G, int i, int j);           // 获取下一邻接点
Status InsertVex(OLGraph *G, char v);               // 插入顶点
Status DeleteVex(OLGraph *G, char v);               // 删除顶点
Status InsertArc(OLGraph *G, char v, char w);       // 插入弧
Status DeleteArc(OLGraph *G, char v, char w);       // 删除弧
Status DFSTraverse(OLGraph *G);                     // 深度优先搜索
void DFS(OLGraph *G, int v);                        // 深度优先搜索
Status BFSTraverse(OLGraph *G);                     // 广度优先搜索  使用辅助队列

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
int main()
{
    int op = 1;
    OLGraph G[LISTNUM];
    int i = 0;
    int id = 0;
    int v = 0, u = 0, w = 0, key = 0;
    char ch1, ch2; // 用来查找
    for (i = 0; i < LISTNUM; i++)
        G[i].isinit = 0;
    // CreateDG(&G);
    // DestroyGraph(&G);

    // 菜单
    while (op)
    {
        system("cls"); //用于清屏
        printf("\n\n");
        printf("     Menu for Undirected Graph On Chain Structure \n");
        printf("*********************************************************\n");
        printf("1.  CreateGraph \t 2.  DestroyGraph\n");
        printf("3.  LocateVex   \t 4.  PutVex\n");
        printf("5.  FirstAdjVex      \t 6.  NextAdjVex\n");
        printf("7.  InsertVex  \t\t 8.  DeleteVex\n");
        printf("9.  InsertArc   \t 10. DeleteArc\n");
        printf("11. DFSTraverse   \t 12. BFSTraverse\n");
        printf("13. Save \t\t 14. Load\n");
        printf("0.  Exit        \n");
        printf("********************************************************\n");
        printf("请选择你的操作[0-14]: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            // 创建
            id = GetID() - 1;
            if (CreateDG(G + id) == OK)
                printf("创建成功\n");
            else
                printf("创建失败\n");
            getchar();
            getchar();
            break;
        case 2:
            // Destroy
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("该ID的图未创建\n");
            else
            {
                if (DestroyGraph(G + id) == OK)
                    printf("销毁成功!\n");
                else
                    printf("销毁失败!\n");
            }
            getchar();
            getchar();
            break;
        case 3:
            //LocateVex
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("请输入要查找的顶点的key");
                scanf("%d", &key);
                if (LocateVex(G + id, key) == -1)
                    printf("该顶点不存在\n");
                else
                    printf("该顶点的key为%d\n", LocateVex(G + id, ch1));
            }
            getchar();
            getchar();
            break;
        case 4:
            // PutVex
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("请输入所要查找的顶点的key值: ");
                scanf("%d", &key);
                if (key >= G[id].vexnum || key < 0)
                    printf("图中不存在该key值的顶点\n");
                else
                {
                    printf("请输入要赋予的值: ");
                    fflush(stdin);
                    scanf("%c", &ch1);
                    if (PutVex(G + id, key, ch1) == OK)
                        printf("赋值成功\n");
                    else
                        printf("赋值失败\n");
                }
            }
            getchar();
            getchar();
            break;
        case 5:
            // FirstAdjVex
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("输入顶点的位序: ");
                scanf("%d", &u);
                if (u < 0 || u > G[id].vexnum - 1)
                    printf("位序值不合法");
                else
                {
                    if (FirstAdjVex(G + id, u) == -1)
                        printf("该顶点没有邻接顶点\n");
                    else
                        printf("该顶点的第一邻接点的位置是%d", FirstAdjVex(G + id, u));
                }
            }
            getchar();
            getchar();
            break;
        case 6:
            // NextAdjVex
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("输入两个顶点的位序: ");
                scanf("%d%d", &u, &v);
                if (u < 0 || u > G[id].vexnum - 1)
                    printf("位序值不合法");
                if (v < 0 || v > G[id].vexnum - 1)
                    printf("位序值不合法");
                else if (NextAdjVex(G + id, u, v) == -1)
                    printf("该顶点是最后一个邻接顶点\n");
                else
                    printf("该顶点的下一个邻接点的位置是%d\n", NextAdjVex(G + id, u, v));
            }
            getchar();
            getchar();
            break;
        case 7:
            // InsertVex
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("请输入要插入的顶点的value: ");
                fflush(stdin);
                scanf("%c", &ch1);
                if (InsertVex(G + id, ch1) == OK)
                    printf("插入成功\n");
            }
            getchar();
            getchar();
            break;
        case 8:
            // DeleteVex
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("请输入要删除的顶点的值: ");
                fflush(stdin);
                scanf("%c", &ch1);
                if (LocateVex_bydata(G + id, ch1) < 0)
                    printf("该顶点不存在\n");
                else
                {
                    if (DeleteVex(G + id, ch1) == OK)
                        printf("删除成功\n");
                }
            }
            getchar();
            getchar();
            break;
        case 9:
            // InserArc
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("请输入弧连接的两个顶点 一个空格分开: ");
                fflush(stdin);
                scanf("%c %c", &ch1, &ch2);
                if (InsertArc(G + id, ch1, ch2) == OK)
                    printf("插入成功\n");
                else
                    printf("插入失败\n");
            }
            getchar();
            getchar();
            break;
        case 10:
            //DeleteArc
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("请输入弧连接的两个顶点 一个空格分开: ");
                fflush(stdin);
                scanf("%c %c", &ch1, &ch2);
                if (LocateVex_bydata(G + id, ch1) < 0 || LocateVex_bydata(G + id, ch2) < 0)
                    printf("顶点不存在\n");
                else
                {
                    if (DeleteArc(G + id, ch1, ch2) == OK)
                        printf("删除成功\n");
                }
            }
            getchar();
            getchar();
            break;
        case 11:
            // DFS
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("深度优先搜索\n");
                DFSTraverse(G + id);
            }
            getchar();
            getchar();
            break;
        case 12:
            //BFS
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("该ID的图未创建\n");
            else
            {
                printf("广度优先搜索\n");
                BFSTraverse(G + id);
            }
            getchar();
            getchar();
            break;
        case 13:
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("该ID的图未创建\n");
            else
            {
                if (Save(G + id) == OK)
                    printf("保存成功\n");
            }
            getchar();
            getchar();
            break;
        case 14:
            id = GetID() - 1;
            if (Load(G + id) == OK)
                printf("加载成功\n");
            getchar();
            getchar();
            break;
        default:
            break;
        }
    }
    return 0;
}
// 功能函数

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

int DeleteQ(Queue Q)
{
    PtrToQNode FrontCell;
    int FrontElem;

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

bool AddQ(Queue Q, int X)
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

// 有向图操作
int LocateVex_bydata(OLGraph *G, VertexType v)
{
    // 定位v在G中的位置
    int i = 0;
    for (i = 0; i < G->vexnum; ++i)
    {
        if (v == G->xlist[i].data)
            return i;
    }
    return -1;
}
int LocateVex(OLGraph *G, KeyType v)
{
    // 定位key在G中的位置
    int i = 0;
    for (i = 0; i < G->vexnum; ++i)
    {
        if (v == G->xlist[i].key)
            return i;
    }
    return -1;
}
Status CreateDG(OLGraph *G)
{
    // v 点集合  vr边集合 // 后进先出链表
    //(*G).xlist = (VexNode *)malloc(MAX_VERTEX_NUM * sizeof(VexNode));
    int i = 0, j = 0;
    int k = 0;
    char v1, v2;
    ArcBox *p = NULL;
    printf("请依次输入顶点数和弧数：");
    scanf("%d%d", &(G->vexnum), &(G->arcnum));
    fflush(stdin);
    for (i = 0; i < (*G).vexnum; ++i)
    {
        // 存储顶点信息
        printf("请输入顶点值");
        scanf("%c", &((*G).xlist[i].data));
        fflush(stdin);
        (*G).xlist[i].firstout = NULL;
        (*G).xlist[i].firstin = NULL;
        G->xlist[i].key = i; // 节点key存储为顶点在数组中的下标
    }
    for (k = 0; k < (*G).arcnum; ++k)
    {
        printf("请输入弧信息 用空格分开结点: ");
        scanf("%c %c", &v1, &v2);
        fflush(stdin);
        i = LocateVex_bydata(G, v1);
        j = LocateVex_bydata(G, v2);
        if (i == -1 || j == -1) //如果输入的弧信息错误 （节点错误）
        {
            printf("ERROR\n");
            return ERROR;
        }
        p = (ArcBox *)malloc(sizeof(ArcBox));
        (*p).tailvex = i;
        (*p).headvex = j;
        (*p).hlink = (*G).xlist[j].firstin;  // 弧头
        (*p).tlink = (*G).xlist[i].firstout; //弧尾
        (*G).xlist[j].firstin = p;
        (*G).xlist[i].firstout = p; //完成入弧和出弧链头的插入
    }
    G->isinit = 1;
    return OK;
}
Status DestroyGraph(OLGraph(*G))
{
    // 销毁图
    // 先销毁弧
    // 选取出度删除

    ArcBox *p = NULL;
    ArcBox *q = NULL;
    int i = 0;
    int j = 0;
    for (i = 0; i < G->vexnum; i++)
    {
        p = G->xlist[i].firstout;
        q = p;
        // 循环删除所有弧
        while (p)
        {
            // 释放各个节点空间
            q = p->tlink;
            free(p);
            p = q;
        }
    }
    //删除所有顶点
    //free(G->xlist);
    G->isinit = 0;
    return OK;
}
Status PutVex(OLGraph *G, KeyType key, char value)
{ // 顶点赋值
    int i = LocateVex(G, key);
    if (i < 0)
    { // 顶点不存在
        return ERROR;
    }

    G->xlist[i].data = value;
    return OK;
}
int FirstAdjVex(OLGraph *G, int v)
{
    // 获取第一邻接顶点
    if (v < 0 || v > (*G).vexnum - 1) // v不合法
        return ERROR;
    ArcBox *p = (*G).xlist[v].firstout;
    if (p)
    {
        return p->headvex;
    }
    else
    {
        return -1;
    }
}
int NextAdjVex(OLGraph *G, int i, int j)
{
    ArcBox *pArc;
    if (i < 0 || i > (*G).vexnum) // i不合法
        return ERROR;
    if (j < 0 || j > (*G).vexnum) // j不合法
        return ERROR;

    pArc = (*G).xlist[i].firstout;
    while (pArc && pArc->headvex != j)
    {
        // 找到弧
        pArc = pArc->tlink;
    }
    if (pArc)
    {
        // 下一个
        pArc = pArc->tlink;
    }
    if (pArc)
    {
        return pArc->headvex;
    }
    else
    {
        return -1;
    }
}

Status InsertVex(OLGraph *G, char v)
{
    // 插入顶点
    G->xlist[G->vexnum].data = v;
    G->xlist[G->vexnum].firstin = G->xlist[G->vexnum].firstout = NULL;
    G->xlist[G->vexnum].key = G->vexnum; // key
    G->vexnum++;
    return OK;
}
Status DeleteVex(OLGraph *G, char v)
{
    // 删除顶点
    int j, k;
    ArcBox *p, *q;

    k = LocateVex_bydata(G, v); // k 是待删除节点的位序
    if (k < 0)
    {
        return ERROR;
    }
    //删除v的出弧
    //v的出弧也就是其他顶点的入弧，需要在其他弧的入弧链表中删除v的出弧
    for (j = 0; j < G->vexnum; j++)
    { // j 代表了其他弧
        if (j == k)
        {
            continue;
        }
        p = G->xlist[j].firstin; // 入弧链表
        while (p)
        {
            if (k == p->tailvex && p == G->xlist[j].firstin) //如果待删结点为首结点
            {
                G->xlist[j].firstin = p->hlink;
                break;
            }
            else if (k != p->tailvex) //当前结点不是待删结点
            {
                q = p;
                p = p->hlink;
            }
            else //待删结点不是首节点
            {
                q->hlink = p->hlink;
                break;
            }
        }
    }
    //删除v的出弧
    p = G->xlist[k].firstout;
    while (p)
    {
        q = p->tlink;

        free(p);
        G->arcnum--;
        p = q;
    }
    //删除顶点v的入弧
    //顶点v的入弧也就是其他顶点的出弧，我们需要在其他弧的出弧链表中删除v的入弧
    for (j = 0; j < G->vexnum; j++)
    {
        if (j == k)
        {
            continue;
        }
        p = G->xlist[j].firstout;
        while (p)
        {
            if (k == p->headvex && p == G->xlist[j].firstout)
            {
                G->xlist[j].firstout = p->tlink;
                break;
            }
            else if (k != p->headvex)
            {
                q = p;
                p = p->tlink;
            }
            else
            {
                q->tlink = p->tlink;
                break;
            }
        }
    }
    //删除顶点v的入弧
    p = G->xlist[k].firstin;
    while (p)
    {
        q = p->hlink;

        free(p);
        p = q;
        G->arcnum--;
    }
    //序号>k的顶点依次向前移  同时记得改变key
    for (j = k + 1; j < G->vexnum; j++)
    {
        G->xlist[j].key--;
        G->xlist[j - 1] = G->xlist[j];
    }
    G->vexnum--;
    //结点序号>k的要减1
    for (j = 0; j < G->vexnum; j++)
    {
        p = G->xlist[j].firstout;
        while (p)
        {
            if (p->headvex > k)
            {
                p->headvex--;
            }
            if (p->tailvex > k)
            {
                p->tailvex--;
            }
            p = p->tlink;
        }
    }
    return OK;
}

Status InsertArc(OLGraph *G, char v, char w)
{
    // 插入弧
    int i, j;
    ArcBox *p = NULL;
    ArcBox *x = (ArcBox *)malloc(sizeof(ArcBox));
    ArcBox *Temp = NULL;
    i = LocateVex_bydata(G, v);
    j = LocateVex_bydata(G, w);
    // 如果弧已经存在
    Temp = G->xlist[i].firstout;
    while (Temp)
    {
        if (Temp->headvex == j)
            return ERROR;
        Temp = Temp->tlink;
    }

    // 构造弧
    x->headvex = j;
    x->tailvex = i;
    x->hlink = G->xlist[j].firstin; //后进先出链表
    x->tlink = G->xlist[i].firstout;
    G->xlist[i].firstout = x;
    G->xlist[j].firstin = x;
    G->arcnum++;
    return OK;
}

Status DeleteArc(OLGraph *G, char v, char w)
{
    int i, j;
    ArcBox *p, *q;
    i = LocateVex_bydata(G, v);
    j = LocateVex_bydata(G, w);
    if (i < 0 || j < 0)
    {
        return ERROR;
    }
    p = G->xlist[i].firstout; // p为顶点v的第一条出弧
    q = p;
    // 找出弧链中找到要删除的那一条弧
    // 特征 p->headvex == j;

    // 1. 如果要删除的弧就是头节点 也就是当前的p
    if (p && p->headvex == j) // 头节点
    {
        G->xlist[i].firstout = p->tlink;
    }
    else
    {
        // 不是头节点
        // 找到头节点
        while (p && p->headvex != j)
        {
            q = p;
            p = p->tlink;
        }
        if (p)
            q->tlink = p->tlink;
    } // 出弧删除成功

    // 入弧删除
    p = G->xlist[i].firstin; // p为顶点v的第一条出弧
    q = p;
    // 找出弧链中找到要删除的那一条弧
    // 特征 p->headvex == j;

    // 2. 如果要删除的弧就是头节点 也就是当前的p
    if (p && p->tailvex == i) // 头节点
    {
        G->xlist[j].firstin = p->hlink;
    }
    else
    {
        // 不是头节点
        // 找到头节点
        while (p && p->tailvex != j)
        {
            q = p;
            p = p->hlink;
        }
        if (p)
            q->hlink = p->hlink;
    } // ru弧删除成功
    free(p);
    G->arcnum--;
    return OK;
}

Status DFSTraverse(OLGraph *G)
{
    // 深度优先搜索
    int v = 0;
    for (v = 0; v < (*G).vexnum; v++)
        visited[v] = 0;
    for (v = 0; v < G->vexnum; v++)
    {
        if (!visited[v])
            DFS(G, v); //对没有访问的顶点调用深度优先遍历
    }
}

void DFS(OLGraph *G, int v)
{
    visited[v] = 1;
    printf("%c  ", G->xlist[v].data);
    int w = 0;
    for (w = FirstAdjVex(G, v); w >= 0; w = NextAdjVex(G, v, w))
    {
        if (!visited[w])
            DFS(G, w);
    }
}

Status BFSTraverse(OLGraph *G)
{
    // 广度优先搜索  使用辅助队列
    int v = 0;
    int u = 0;
    int w = 0;
    for (v = 0; v < G->vexnum; v++)
    {
        visited[v] = 0;
    }
    // 初始化队列
    Queue Q = CreateQueue();
    for (v = 0; v < G->vexnum; v++)
    {
        if (!visited[v])
        {
            visited[v] = 1;
            printf("%c  ", G->xlist[v].data);
            AddQ(Q, v); // 将刚刚访问的顶点加入队列
            while (!IsEmptyQ(Q))
            {
                // 从队列中弹出一个
                u = DeleteQ(Q);
                for (w = FirstAdjVex(G, u); w >= 0; w = NextAdjVex(G, u, w))
                {
                    if (!visited[w])
                    {
                        visited[w] = 1;
                        printf("%c  ", G->xlist[w].data);
                        AddQ(Q, w);
                    }
                }
            }
        }
    }
    return OK;
}
Status Save(OLGraph *G)
{
    FILE *fp;
    char filename[41];
    ArcBox *head = NULL;
    printf("请输入要保存的文件名: ");
    scanf("%s", &filename);
    if ((fp = fopen(filename, "wb")) == NULL)
    {
        printf("保存文件失败！\n");
        return ERROR;
    }
    // 保存图信息  vexnum arcnum
    fwrite(&G->vexnum, sizeof(int), 1, fp);
    fwrite(&G->arcnum, sizeof(int), 1, fp);

    // 顶点信息 Data Key
    int i = 0;
    for (i = 0; i < G->vexnum; i++)
    {
        fwrite(&(G->xlist[i].data), sizeof(VertexType), 1, fp);
        fwrite(&(G->xlist[i].key), sizeof(KeyType), 1, fp);
    }
    // 弧信息 按照顶点出弧的顺序存储
    for (i = 0; i < G->vexnum; i++)
    {
        head = G->xlist[i].firstout;
        while (head)
        {
            fwrite(&(head->tailvex), sizeof(int), 1, fp);
            fwrite(&(head->headvex), sizeof(int), 1, fp);
            head = head->tlink;
        }
    }
    fclose(fp);
    return OK;
}
Status Load(OLGraph *G)
{
    FILE *fp;
    ArcBox *p;
    int i = 0;
    int j = 0;
    char filename[41];
    printf("请输入要加载的文件名: ");
    scanf("%s", &filename);
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("文件加载失败！\n");
        return ERROR;
    }
    fread(&(G->vexnum), sizeof(int), 1, fp);
    fread(&(G->arcnum), sizeof(int), 1, fp);
    G->isinit = 1;
    // 恢复顶点data key
    int m = 0;
    for (m = 0; m < G->vexnum; m++)
    {
        fread(&(G->xlist[m].data), sizeof(VertexType), 1, fp);
        fread(&(G->xlist[m].key), sizeof(KeyType), 1, fp);
        G->xlist[m].firstout = NULL;
        G->xlist[m].firstin = NULL;
    }
    // 恢复弧信息  已知 i j 先i 后 j
    int n = 0;
    for (n = 0; n < G->arcnum; n++)
    {
        p = (ArcBox *)malloc(sizeof(ArcBox));
        fread(&(i), sizeof(int), 1, fp);
        fread(&(j), sizeof(int), 1, fp);
        p->tailvex = i;
        p->headvex = j;
        p->hlink = G->xlist[j].firstin;  // 弧头
        p->tlink = G->xlist[i].firstout; //弧尾
        G->xlist[j].firstin = p;
        G->xlist[i].firstout = p; //完成入弧和出弧链头的插入
    }
    fclose(fp);
    return OK;
}