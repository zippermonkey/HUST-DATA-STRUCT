// ��ʼ����  InitList(L);
// DestroyList(L)
//ClearList(L)
// ListEmpty(L)
//��ʼ���������Ա�L�Ѵ��ڣ������������LΪ�ձ��򷵻�TRUE,���򷵻�FALSE

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
 * дһ������������ĳһ��Ԫ�ص�ǰһ��Ԫ�صĵ�ֵַ��ܷ���  �������򷵻����һ���ڵ��λ��
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
typedef int ElemType; //����Ԫ�����Ͷ���

/*------- �ڵ㶨�� -------*/
typedef struct node
{
    ElemType data;
    struct node *next;
} LNode;

typedef LNode *PtrToLNode; // PtrToLNode ����(PtrToLNode)malloc(sizeof(LNode));

// �ɴ˶������Ա�
typedef PtrToLNode List; //  List��������һ����  ����ͷ�ڵ㣩 List L = (List)malloc(sizeof(LNode))  ͷ�ڵ�������������泤��;

/*-------------��������-----------------*/
status InitList(List *L);                        // ��ʼ����
status DestroyList(List *L);                     // �ݻٱ�
status ClearList(List L);                        // ��ձ�
status ListEmpty(List L);                        // ���Ƿ�Ϊ��
status ListLength(List L);                       // �������Ա���
status GetElem(List L, int i, int *e);           // ��e���ص�iλ�õ�ֵ
int LocateElem(List L, int *e);                  // ����e���ڵ�λ��
status PriorElem(List L, int cur_e, int *pre_e); // ��pre_e ���� cur_e ��ǰ��
status NextElem(List L, int cur_e, int *next_e); // ��next_e���� cur_e �ĺ��

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
        printf("    ��ѡ����Ĳ���[0~12]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            sta = InitList(&L);
            if (sta == OK)
                printf("���Ա����ɹ���\n");
            else if (sta == OVERFLOW)
                printf("���Ա���ʧ�ܣ�\n");
            else if (sta == ERROR)
                printf("���Ա��Ѿ�����\n");
            getchar();
            getchar();
            break;
        case 2:
            sta = DestroyList(&L);
            if (sta == INFEASTABLE)
                printf("���Ա�δ����\n");
            else if (sta == OK)
                printf("���ٳɹ�\n");
            getchar();
            getchar();
            break;
        case 3:
            sta = ClearList(L);
            if (sta == INFEASTABLE)
                printf("���Ա�δ����\n");
            else if (sta == OK)
                printf("���Ա���ճɹ�\n");
            getchar();
            getchar();
            break;
        case 4:
            sta = ListEmpty(L);
            if (sta == INFEASTABLE)
                printf("���Ա�δ����\n");
            else if (sta == TRUE)
                printf("���Ա�Ϊ��\n");
            else if (sta == FALSE)
                printf("���Ա�ǿ�\n");
            getchar();
            getchar();
            break;
        case 5:
            sta = ListLength(L);
            if (sta == ERROR)
                printf("���Ա�δ����");
            else
                printf("���Ա��е�Ԫ�ظ���Ϊ %d\n", sta);
            getchar();
            getchar();
            break;
        case 6:
            printf("\n----GetElem���ܴ�ʵ�֣�\n");
            getchar();
            getchar();
            break;
        case 7:
            printf("\n----LocateElem���ܴ�ʵ�֣�\n");
            getchar();
            getchar();
            break;
        case 8:
            printf("\n----PriorElem���ܴ�ʵ�֣�\n");
            getchar();
            getchar();
            break;
        case 9:
            printf("\n----NextElem���ܴ�ʵ�֣�\n");
            getchar();
            getchar();
            break;
        case 10:
            printf("\n----ListInsert���ܴ�ʵ�֣�\n");
            getchar();
            getchar();
            break;
        case 11:
            printf("\n----ListDelete���ܴ�ʵ�֣�\n");
            getchar();
            getchar();
            break;
        case 12:
            //printf("\n----ListTrabverse���ܴ�ʵ�֣�\n");
            getchar();
            getchar();
            break;
        case 0:
            break;
        } //end of switch
    }     //end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
} //end of main()

status InitList(List *L)
{
    // ����Ѿ�����
    if (*L)
        return ERROR;
    // ����ռ�
    (*L) = (List)malloc(sizeof(LNode)); // ����һ����ͷ�ڵ�Ŀ�����
    if ((*L) == NULL)
        return (OVERFLOW);
    (*L)->next = NULL;
    (*L)->data = 0; // 0��ʾ��ǰ��ĳ���Ϊ0
    return OK;      // �����ɹ�

} // InitList

status DestroyList(List *L)
{
    // δ����
    if ((*L) == NULL)
        return INFEASTABLE;

    // L��������ͷ�ڵ�  ����free(L)
    // Ȼ���LΪNULL
    PtrToLNode temp1 = (*L); // ��ʱ����ָ��ͷ��
    PtrToLNode temp2 = temp1;

    while (temp1)
    {
        // �ͷŸ����ڵ�ռ�
        temp2 = temp1->next;
        free(temp1);
        temp1 = temp2;
    }
    // ��L��Ϊ��
    *L = NULL;
    return OK;
}
status ListEmpty(List L)
{
    // δ����
    if (L == NULL)
        return INFEASTABLE;
    if (L->data == 0)
        return TRUE;
    else
        return FALSE;
}
status ClearList(List L)
{
    // ����ͷ�ڵ� ��ͷ�ڵ�data����Ϊ0
    // free �����ڵ�

    // δ����
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
    // �������Ա���

    if (L == NULL) //δ����
        return INFEASTABLE;
    else
        return L->data;
}
status GetElem(List L, int i, int *e)
{
    if (L == NULL) //δ����
        return INFEASTABLE;
    if (ListEmpty(L) == 0)
        return ERROR;

    if (i < 0 || i > ListLength(L)) //i ���Ϸ�
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
    // ����ĳһ��Ԫ�ص�ǰһ��Ԫ�صĵ�ֵַ �������򷵻����һ���ڵ�ĵ�ַ
    PtrToLNode p = L;
    while (p->next && p->next->data != e)
        p = p->next;
    return p;
}
int LocateElem(List L, int *e)
{
    // ����e���ڵ�Ϊ��  ��1��ʼ
    if (L == NULL) //δ����
        return INFEASTABLE;

    int i = 1;
    PtrToLNode p = L->next;
    while (p && p->data != e)
    {
        p = p->next;
        i++;
    }
    if (p) // ����ҵ�
        return i;
    else //û�ҵ�
        return ERROR;
}

status PriorElem(List L, int cur_e, int *pre_e)
{
    if (L == NULL) //δ����
        return INFEASTABLE;

    PtrToLNode p = GetAdress(L, cur_e);
    if (p->next == NULL) // û����һ��Ԫ��
        return NOTFOUND;
    else if (p == L) // ��һ��Ԫ��  û��ǰ��
        return ERROR;
    else
    {
        *pre_e = p->next->data;
        return OK;
    }
}