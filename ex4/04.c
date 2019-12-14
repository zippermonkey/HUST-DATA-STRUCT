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
#define LISTNUM 10 //��ͼ����Ŀ

typedef int Status;

//---------����----------------
// ���ж���
typedef struct Node *PtrToQNode;
struct Node
{ /* �����еĽ�� */
    int Data;
    PtrToQNode Next;
};

struct QMgr
{
    PtrToQNode Front, Rear; /* ���е�ͷ��βָ�� */
};
typedef struct QMgr *Queue;

// ------ ����ͼ��ʮ������洢��ʾ--------
typedef char VertexType;
typedef int KeyType;
#define MAX_VERTEX_NUM 20
int visited[MAX_VERTEX_NUM];

typedef struct ArcBox
{                                 // ���ṹ
    int tailvex, headvex;         //�û���β��ͷ�����λ��
    struct ArcBox *hlink, *tlink; //�ֱ�Ϊ��ͷ��ͬ�ͻ�β��ͬ�Ļ�������
    // info
} ArcBox;
typedef struct VexNode
{
    // ����ṹ
    VertexType data;
    KeyType key; // �����붥��洢λ����ͬ
    ArcBox *firstin, *firstout;
} VexNode;
typedef struct
{
    VexNode xlist[MAX_VERTEX_NUM]; //��ͷ����
    int vexnum, arcnum;            //����ͼ��ǰ�Ķ������ͻ���
    int isinit;                    // ����Ƿ񴴽�  ����ʱ ��Ϊ0
} OLGraph;

// ��������
/*--------����-------*/
Queue CreateQueue();       // ��������
bool IsEmptyQ(Queue Q);    // ����Ϊ�գ�
int DeleteQ(Queue Q);      // ����
bool AddQ(Queue Q, int X); // ���

/*-------����ͼ------*/
int LocateVex_bydata(OLGraph *G, VertexType v);     // ��λv��G�е�λ��
Status CreateDG(OLGraph *G);                        // v �㼯��  vr�߼��� // ����ȳ�����
Status DestroyGraph(OLGraph(*G));                   // ����ͼ
Status PutVex(OLGraph *G, KeyType key, char value); // ���㸳ֵ
int FirstAdjVex(OLGraph *G, int v);                 // ��ȡ��һ�ڽӶ���
int NextAdjVex(OLGraph *G, int i, int j);           // ��ȡ��һ�ڽӵ�
Status InsertVex(OLGraph *G, char v);               // ���붥��
Status DeleteVex(OLGraph *G, char v);               // ɾ������
Status InsertArc(OLGraph *G, char v, char w);       // ���뻡
Status DeleteArc(OLGraph *G, char v, char w);       // ɾ����
Status DFSTraverse(OLGraph *G);                     // �����������
void DFS(OLGraph *G, int v);                        // �����������
Status BFSTraverse(OLGraph *G);                     // �����������  ʹ�ø�������

int GetID()
{
    // ����ID
    int id = 0;
    printf("������id(1-%d)��", LISTNUM);
    scanf("%d", &id);
    while (id < 1 || id > LISTNUM)
    {
        printf("idֵ��Ч������������id(1-%d)��", LISTNUM);
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
    char ch1, ch2; // ��������
    for (i = 0; i < LISTNUM; i++)
        G[i].isinit = 0;
    // CreateDG(&G);
    // DestroyGraph(&G);

    // �˵�
    while (op)
    {
        system("cls"); //��������
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
        printf("��ѡ����Ĳ���[0-14]: ");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            // ����
            id = GetID() - 1;
            if (CreateDG(G + id) == OK)
                printf("�����ɹ�\n");
            else
                printf("����ʧ��\n");
            getchar();
            getchar();
            break;
        case 2:
            // Destroy
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("��ID��ͼδ����\n");
            else
            {
                if (DestroyGraph(G + id) == OK)
                    printf("���ٳɹ�!\n");
                else
                    printf("����ʧ��!\n");
            }
            getchar();
            getchar();
            break;
        case 3:
            //LocateVex
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("��ID��ͼδ����\n");
            else
            {
                printf("������Ҫ���ҵĶ����key");
                scanf("%d", &key);
                if (LocateVex(G + id, key) == -1)
                    printf("�ö��㲻����\n");
                else
                    printf("�ö����keyΪ%d\n", LocateVex(G + id, ch1));
            }
            getchar();
            getchar();
            break;
        case 4:
            // PutVex
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("��ID��ͼδ����\n");
            else
            {
                printf("��������Ҫ���ҵĶ����keyֵ: ");
                scanf("%d", &key);
                if (key >= G[id].vexnum || key < 0)
                    printf("ͼ�в����ڸ�keyֵ�Ķ���\n");
                else
                {
                    printf("������Ҫ�����ֵ: ");
                    fflush(stdin);
                    scanf("%c", &ch1);
                    if (PutVex(G + id, key, ch1) == OK)
                        printf("��ֵ�ɹ�\n");
                    else
                        printf("��ֵʧ��\n");
                }
            }
            getchar();
            getchar();
            break;
        case 5:
            // FirstAdjVex
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("��ID��ͼδ����\n");
            else
            {
                printf("���붥���λ��: ");
                scanf("%d", &u);
                if (u < 0 || u > G[id].vexnum - 1)
                    printf("λ��ֵ���Ϸ�");
                else
                {
                    if (FirstAdjVex(G + id, u) == -1)
                        printf("�ö���û���ڽӶ���\n");
                    else
                        printf("�ö���ĵ�һ�ڽӵ��λ����%d", FirstAdjVex(G + id, u));
                }
            }
            getchar();
            getchar();
            break;
        case 6:
            // NextAdjVex
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("��ID��ͼδ����\n");
            else
            {
                printf("�������������λ��: ");
                scanf("%d%d", &u, &v);
                if (u < 0 || u > G[id].vexnum - 1)
                    printf("λ��ֵ���Ϸ�");
                if (v < 0 || v > G[id].vexnum - 1)
                    printf("λ��ֵ���Ϸ�");
                else if (NextAdjVex(G + id, u, v) == -1)
                    printf("�ö��������һ���ڽӶ���\n");
                else
                    printf("�ö������һ���ڽӵ��λ����%d\n", NextAdjVex(G + id, u, v));
            }
            getchar();
            getchar();
            break;
        case 7:
            // InsertVex
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("��ID��ͼδ����\n");
            else
            {
                printf("������Ҫ����Ķ����value: ");
                fflush(stdin);
                scanf("%c", &ch1);
                if (InsertVex(G + id, ch1) == OK)
                    printf("����ɹ�\n");
            }
            getchar();
            getchar();
            break;
        case 8:
            // DeleteVex
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("��ID��ͼδ����\n");
            else
            {
                printf("������Ҫɾ���Ķ����ֵ: ");
                fflush(stdin);
                scanf("%c", &ch1);
                if (LocateVex_bydata(G + id, ch1) < 0)
                    printf("�ö��㲻����\n");
                else
                {
                    if (DeleteVex(G + id, ch1) == OK)
                        printf("ɾ���ɹ�\n");
                }
            }
            getchar();
            getchar();
            break;
        case 9:
            // InserArc
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("��ID��ͼδ����\n");
            else
            {
                printf("�����뻡���ӵ��������� һ���ո�ֿ�: ");
                fflush(stdin);
                scanf("%c %c", &ch1, &ch2);
                if (InsertArc(G + id, ch1, ch2) == OK)
                    printf("����ɹ�\n");
                else
                    printf("����ʧ��\n");
            }
            getchar();
            getchar();
            break;
        case 10:
            //DeleteArc
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("��ID��ͼδ����\n");
            else
            {
                printf("�����뻡���ӵ��������� һ���ո�ֿ�: ");
                fflush(stdin);
                scanf("%c %c", &ch1, &ch2);
                if (LocateVex_bydata(G + id, ch1) < 0 || LocateVex_bydata(G + id, ch2) < 0)
                    printf("���㲻����\n");
                else
                {
                    if (DeleteArc(G + id, ch1, ch2) == OK)
                        printf("ɾ���ɹ�\n");
                }
            }
            getchar();
            getchar();
            break;
        case 11:
            // DFS
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("��ID��ͼδ����\n");
            else
            {
                printf("�����������\n");
                DFSTraverse(G + id);
            }
            getchar();
            getchar();
            break;
        case 12:
            //BFS
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("��ID��ͼδ����\n");
            else
            {
                printf("�����������\n");
                BFSTraverse(G + id);
            }
            getchar();
            getchar();
            break;
        case 13:
            id = GetID() - 1;
            if (G[id].isinit == 0)
                printf("��ID��ͼδ����\n");
            else
            {
                if (Save(G + id) == OK)
                    printf("����ɹ�\n");
            }
            getchar();
            getchar();
            break;
        case 14:
            id = GetID() - 1;
            if (Load(G + id) == OK)
                printf("���سɹ�\n");
            getchar();
            getchar();
            break;
        default:
            break;
        }
    }
    return 0;
}
// ���ܺ���

/* ���в��� */
Queue CreateQueue()
{
    // ����һ������
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
        printf("���п�");
        return ERROR;
    }
    else
    {
        FrontCell = Q->Front;
        if (Q->Front == Q->Rear)       /* ������ֻ��һ��Ԫ�� */
            Q->Front = Q->Rear = NULL; /* ɾ���������Ϊ�� */
        else
            Q->Front = Q->Front->Next;
        FrontElem = FrontCell->Data;

        free(FrontCell); /* �ͷű�ɾ�����ռ�  */
        return FrontElem;
    }
}

bool AddQ(Queue Q, int X)
{ //��ӽڵ㵽����  �ֶ��п��벻��
    PtrToQNode RearCell = (PtrToQNode)malloc(sizeof(struct Node));
    RearCell->Data = X;
    RearCell->Next = NULL;

    if (Q->Front == NULL) //�������֮ǰΪ��
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

// ����ͼ����
int LocateVex_bydata(OLGraph *G, VertexType v)
{
    // ��λv��G�е�λ��
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
    // ��λkey��G�е�λ��
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
    // v �㼯��  vr�߼��� // ����ȳ�����
    //(*G).xlist = (VexNode *)malloc(MAX_VERTEX_NUM * sizeof(VexNode));
    int i = 0, j = 0;
    int k = 0;
    char v1, v2;
    ArcBox *p = NULL;
    printf("���������붥�����ͻ�����");
    scanf("%d%d", &(G->vexnum), &(G->arcnum));
    fflush(stdin);
    for (i = 0; i < (*G).vexnum; ++i)
    {
        // �洢������Ϣ
        printf("�����붥��ֵ");
        scanf("%c", &((*G).xlist[i].data));
        fflush(stdin);
        (*G).xlist[i].firstout = NULL;
        (*G).xlist[i].firstin = NULL;
        G->xlist[i].key = i; // �ڵ�key�洢Ϊ�����������е��±�
    }
    for (k = 0; k < (*G).arcnum; ++k)
    {
        printf("�����뻡��Ϣ �ÿո�ֿ����: ");
        scanf("%c %c", &v1, &v2);
        fflush(stdin);
        i = LocateVex_bydata(G, v1);
        j = LocateVex_bydata(G, v2);
        if (i == -1 || j == -1) //�������Ļ���Ϣ���� ���ڵ����
        {
            printf("ERROR\n");
            return ERROR;
        }
        p = (ArcBox *)malloc(sizeof(ArcBox));
        (*p).tailvex = i;
        (*p).headvex = j;
        (*p).hlink = (*G).xlist[j].firstin;  // ��ͷ
        (*p).tlink = (*G).xlist[i].firstout; //��β
        (*G).xlist[j].firstin = p;
        (*G).xlist[i].firstout = p; //����뻡�ͳ�����ͷ�Ĳ���
    }
    G->isinit = 1;
    return OK;
}
Status DestroyGraph(OLGraph(*G))
{
    // ����ͼ
    // �����ٻ�
    // ѡȡ����ɾ��

    ArcBox *p = NULL;
    ArcBox *q = NULL;
    int i = 0;
    int j = 0;
    for (i = 0; i < G->vexnum; i++)
    {
        p = G->xlist[i].firstout;
        q = p;
        // ѭ��ɾ�����л�
        while (p)
        {
            // �ͷŸ����ڵ�ռ�
            q = p->tlink;
            free(p);
            p = q;
        }
    }
    //ɾ�����ж���
    //free(G->xlist);
    G->isinit = 0;
    return OK;
}
Status PutVex(OLGraph *G, KeyType key, char value)
{ // ���㸳ֵ
    int i = LocateVex(G, key);
    if (i < 0)
    { // ���㲻����
        return ERROR;
    }

    G->xlist[i].data = value;
    return OK;
}
int FirstAdjVex(OLGraph *G, int v)
{
    // ��ȡ��һ�ڽӶ���
    if (v < 0 || v > (*G).vexnum - 1) // v���Ϸ�
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
    if (i < 0 || i > (*G).vexnum) // i���Ϸ�
        return ERROR;
    if (j < 0 || j > (*G).vexnum) // j���Ϸ�
        return ERROR;

    pArc = (*G).xlist[i].firstout;
    while (pArc && pArc->headvex != j)
    {
        // �ҵ���
        pArc = pArc->tlink;
    }
    if (pArc)
    {
        // ��һ��
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
    // ���붥��
    G->xlist[G->vexnum].data = v;
    G->xlist[G->vexnum].firstin = G->xlist[G->vexnum].firstout = NULL;
    G->xlist[G->vexnum].key = G->vexnum; // key
    G->vexnum++;
    return OK;
}
Status DeleteVex(OLGraph *G, char v)
{
    // ɾ������
    int j, k;
    ArcBox *p, *q;

    k = LocateVex_bydata(G, v); // k �Ǵ�ɾ���ڵ��λ��
    if (k < 0)
    {
        return ERROR;
    }
    //ɾ��v�ĳ���
    //v�ĳ���Ҳ��������������뻡����Ҫ�����������뻡������ɾ��v�ĳ���
    for (j = 0; j < G->vexnum; j++)
    { // j ������������
        if (j == k)
        {
            continue;
        }
        p = G->xlist[j].firstin; // �뻡����
        while (p)
        {
            if (k == p->tailvex && p == G->xlist[j].firstin) //�����ɾ���Ϊ�׽��
            {
                G->xlist[j].firstin = p->hlink;
                break;
            }
            else if (k != p->tailvex) //��ǰ��㲻�Ǵ�ɾ���
            {
                q = p;
                p = p->hlink;
            }
            else //��ɾ��㲻���׽ڵ�
            {
                q->hlink = p->hlink;
                break;
            }
        }
    }
    //ɾ��v�ĳ���
    p = G->xlist[k].firstout;
    while (p)
    {
        q = p->tlink;

        free(p);
        G->arcnum--;
        p = q;
    }
    //ɾ������v���뻡
    //����v���뻡Ҳ������������ĳ�����������Ҫ���������ĳ���������ɾ��v���뻡
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
    //ɾ������v���뻡
    p = G->xlist[k].firstin;
    while (p)
    {
        q = p->hlink;

        free(p);
        p = q;
        G->arcnum--;
    }
    //���>k�Ķ���������ǰ��  ͬʱ�ǵøı�key
    for (j = k + 1; j < G->vexnum; j++)
    {
        G->xlist[j].key--;
        G->xlist[j - 1] = G->xlist[j];
    }
    G->vexnum--;
    //������>k��Ҫ��1
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
    // ���뻡
    int i, j;
    ArcBox *p = NULL;
    ArcBox *x = (ArcBox *)malloc(sizeof(ArcBox));
    ArcBox *Temp = NULL;
    i = LocateVex_bydata(G, v);
    j = LocateVex_bydata(G, w);
    // ������Ѿ�����
    Temp = G->xlist[i].firstout;
    while (Temp)
    {
        if (Temp->headvex == j)
            return ERROR;
        Temp = Temp->tlink;
    }

    // ���컡
    x->headvex = j;
    x->tailvex = i;
    x->hlink = G->xlist[j].firstin; //����ȳ�����
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
    p = G->xlist[i].firstout; // pΪ����v�ĵ�һ������
    q = p;
    // �ҳ��������ҵ�Ҫɾ������һ����
    // ���� p->headvex == j;

    // 1. ���Ҫɾ���Ļ�����ͷ�ڵ� Ҳ���ǵ�ǰ��p
    if (p && p->headvex == j) // ͷ�ڵ�
    {
        G->xlist[i].firstout = p->tlink;
    }
    else
    {
        // ����ͷ�ڵ�
        // �ҵ�ͷ�ڵ�
        while (p && p->headvex != j)
        {
            q = p;
            p = p->tlink;
        }
        if (p)
            q->tlink = p->tlink;
    } // ����ɾ���ɹ�

    // �뻡ɾ��
    p = G->xlist[i].firstin; // pΪ����v�ĵ�һ������
    q = p;
    // �ҳ��������ҵ�Ҫɾ������һ����
    // ���� p->headvex == j;

    // 2. ���Ҫɾ���Ļ�����ͷ�ڵ� Ҳ���ǵ�ǰ��p
    if (p && p->tailvex == i) // ͷ�ڵ�
    {
        G->xlist[j].firstin = p->hlink;
    }
    else
    {
        // ����ͷ�ڵ�
        // �ҵ�ͷ�ڵ�
        while (p && p->tailvex != j)
        {
            q = p;
            p = p->hlink;
        }
        if (p)
            q->hlink = p->hlink;
    } // ru��ɾ���ɹ�
    free(p);
    G->arcnum--;
    return OK;
}

Status DFSTraverse(OLGraph *G)
{
    // �����������
    int v = 0;
    for (v = 0; v < (*G).vexnum; v++)
        visited[v] = 0;
    for (v = 0; v < G->vexnum; v++)
    {
        if (!visited[v])
            DFS(G, v); //��û�з��ʵĶ������������ȱ���
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
    // �����������  ʹ�ø�������
    int v = 0;
    int u = 0;
    int w = 0;
    for (v = 0; v < G->vexnum; v++)
    {
        visited[v] = 0;
    }
    // ��ʼ������
    Queue Q = CreateQueue();
    for (v = 0; v < G->vexnum; v++)
    {
        if (!visited[v])
        {
            visited[v] = 1;
            printf("%c  ", G->xlist[v].data);
            AddQ(Q, v); // ���ոշ��ʵĶ���������
            while (!IsEmptyQ(Q))
            {
                // �Ӷ����е���һ��
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
    printf("������Ҫ������ļ���: ");
    scanf("%s", &filename);
    if ((fp = fopen(filename, "wb")) == NULL)
    {
        printf("�����ļ�ʧ�ܣ�\n");
        return ERROR;
    }
    // ����ͼ��Ϣ  vexnum arcnum
    fwrite(&G->vexnum, sizeof(int), 1, fp);
    fwrite(&G->arcnum, sizeof(int), 1, fp);

    // ������Ϣ Data Key
    int i = 0;
    for (i = 0; i < G->vexnum; i++)
    {
        fwrite(&(G->xlist[i].data), sizeof(VertexType), 1, fp);
        fwrite(&(G->xlist[i].key), sizeof(KeyType), 1, fp);
    }
    // ����Ϣ ���ն��������˳��洢
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
    printf("������Ҫ���ص��ļ���: ");
    scanf("%s", &filename);
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("�ļ�����ʧ�ܣ�\n");
        return ERROR;
    }
    fread(&(G->vexnum), sizeof(int), 1, fp);
    fread(&(G->arcnum), sizeof(int), 1, fp);
    G->isinit = 1;
    // �ָ�����data key
    int m = 0;
    for (m = 0; m < G->vexnum; m++)
    {
        fread(&(G->xlist[m].data), sizeof(VertexType), 1, fp);
        fread(&(G->xlist[m].key), sizeof(KeyType), 1, fp);
        G->xlist[m].firstout = NULL;
        G->xlist[m].firstin = NULL;
    }
    // �ָ�����Ϣ  ��֪ i j ��i �� j
    int n = 0;
    for (n = 0; n < G->arcnum; n++)
    {
        p = (ArcBox *)malloc(sizeof(ArcBox));
        fread(&(i), sizeof(int), 1, fp);
        fread(&(j), sizeof(int), 1, fp);
        p->tailvex = i;
        p->headvex = j;
        p->hlink = G->xlist[j].firstin;  // ��ͷ
        p->tlink = G->xlist[i].firstout; //��β
        G->xlist[j].firstin = p;
        G->xlist[i].firstout = p; //����뻡�ͳ�����ͷ�Ĳ���
    }
    fclose(fp);
    return OK;
}