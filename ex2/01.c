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
PtrToLNode GetAdress(List L, int e);             // ����ĳһ��Ԫ�ص�ǰһ��Ԫ�صĵ�ֵַ �������򷵻����һ���ڵ�ĵ�ַ
status isinit(List L);                           // �ж�L�Ƿ��ʼ��
status InitList(List *L);                        // ��ʼ����
status DestroyList(List *L);                     // �ݻٱ�
status ClearList(List L);                        // ��ձ�
status ListEmpty(List L);                        // ���Ƿ�Ϊ��
status ListLength(List L);                       // �������Ա���
status GetElem(List L, int i, int *e);           // ��e���ص�iλ�õ�ֵ
int LocateElem(List L, int e);                   // ����e���ڵ�λ��
status PriorElem(List L, int cur_e, int *pre_e); // ��pre_e ���� cur_e ��ǰ��
status NextElem(List L, int cur_e, int *next_e); // ��next_e���� cur_e �ĺ��
status ListInsert(List L, int i, int e);         // ��i��λ���ϲ���e
status ListDelete(List L, int i, int *e);        //  ɾ��i��λ�õ�ֵ ��e����
status ListTrabverse(List L);                    // ����

int main(void)
{
    List L = NULL;
    int op = 1;
    // ��ʱ����
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
        printf("    ��ѡ����Ĳ���[0~12]:");
        scanf("%d", &op);
        switch (op)
        {
        case 1:
            // sta = InitList(&L);
            // if (sta == OK)
            //     printf("���Ա����ɹ���\n");
            // else if (sta == OVERFLOW)
            //     printf("���Ա���ʧ�ܣ�\n");
            // else if (sta == ERROR)
            //     printf("���Ա��Ѿ�����\n");
            if (isinit(L))
                printf("���Ա��Ѿ�����, ��ѡ��2���� ����3���\n");
            else
            {
                sta = InitList(&L);
                if (sta == OK)
                    printf("���Ա����ɹ���\n");
                else if (sta == OVERFLOW)
                    printf("���Ա���ʧ�ܣ�\n");
            }
            getchar();
            getchar();
            break;
        case 2:
            // sta = DestroyList(&L);
            // if (sta == INFEASTABLE)
            //     printf("���Ա�δ����\n");
            // else if (sta == OK)
            //     printf("���ٳɹ�\n");
            if (isinit(L) == FALSE)
                printf("���Ա�δ����\n");
            else
            {
                DestroyList(&L);
                printf("���ٳɹ�\n");
            }
            getchar();
            getchar();
            break;
        case 3:
            // sta = ClearList(L);
            // if (sta == INFEASTABLE)
            //     printf("���Ա�δ����\n");
            // else if (sta == OK)
            //     printf("���Ա���ճɹ�\n");
            if (isinit(L) == FALSE)
                printf("���Ա�δ����\n");
            else
            {
                ClearList(L);
                printf("���Ա���ճɹ�\n");
            }
            getchar();
            getchar();
            break;
        case 4:
            // sta = ListEmpty(L);
            // if (sta == INFEASTABLE)
            //     printf("���Ա�δ����\n");
            // else if (sta == TRUE)
            //     printf("���Ա�Ϊ��\n");
            // else if (sta == FALSE)
            //     printf("���Ա�ǿ�\n");
            if (isinit(L) == FALSE)
                printf("���Ա�δ����\n");
            else
            {
                if (ListEmpty(L) == TRUE)
                    printf("���Ա�Ϊ��\n");
                else
                    printf("���Ա�ǿ�\n");
            }
            getchar();
            getchar();
            break;
        case 5:
            // sta = ListLength(L);
            // if (sta == ERROR)
            //     printf("���Ա�δ����\n");
            // else
            //     printf("���Ա��е�Ԫ�ظ���Ϊ %d\n", sta);
            if (isinit(L) == FALSE)
                printf("���Ա�δ����\n");
            else
            {
                printf("���Ա��е�Ԫ�ظ���Ϊ %d\n", ListLength(L));
            }
            getchar();
            getchar();
            break;
        case 6:
            // printf("������Ҫȡ��Ԫ�ص�λ��i: ");
            // scanf("%d", &i);
            // sta = GetElem(L, i, &e);
            // if (sta == ERROR)
            //     printf("���Ա�δ����\n");
            // else if (sta == ERROR)
            //     printf("iֵ���Ϸ�\n");
            // else if (sta == OK)
            //     printf("��%dλԪ����%d\n", i, e);
            if (isinit(L) == FALSE)
                printf("���Ա�δ����\n");
            else
            {
                printf("������Ҫȡ��Ԫ�ص�λ��i: ");
                scanf("%d", &i);
                sta = GetElem(L, i, &e);

                if (sta == ERROR)
                    printf("iֵ���Ϸ�\n");
                else if (sta == OK)
                    printf("��%dλԪ����%d\n", i, e);
            }
            getchar();
            getchar();
            break;
        case 7:
            if (isinit(L) == FALSE)
                printf("���Ա�δ����\n");
            else
            {
                printf("������Ҫ���ҵ�Ԫ��ֵ��");
                scanf("%d", &e);
                sta = LocateElem(L, e);
                if (sta == NOTFOUND)
                    printf("���Ա����޴�Ԫ��\n");
                else
                    printf("Ԫ��%d��λ����%d", e, sta);
            }
            getchar();
            getchar();
            break;
        case 8:
            if (isinit(L) == FALSE)
                printf("���Ա�δ����\n");
            else
            {
                printf("������Ҫ������ǰ����Ԫ��ֵ��");
                scanf("%d", &cur_e);
                sta = PriorElem(L, cur_e, &pre_e);
                if (sta == NOTFOUND)
                    printf("���Ա����޴�Ԫ��\n");
                else if (sta == ERROR)
                    printf("%d�ǵ�һ��Ԫ��û��ǰ��\n", cur_e);
                else
                    printf("%d��ǰ����%d\n", cur_e, pre_e);
            }
            getchar();
            getchar();
            break;
        case 9:
            if (isinit(L) == FALSE)
                printf("���Ա�δ����\n");
            else
            {
                printf("������Ҫ�������̵�Ԫ��ֵ��");
                scanf("%d", &cur_e);
                sta = NextElem(L, cur_e, &next_e);
                if (sta == NOTFOUND)
                    printf("���Ա����޴�Ԫ��\n");
                else if (sta == ERROR)
                    printf("%d�����һ��Ԫ��û�к��\n", cur_e);
                else
                    printf("%d�ĺ����%d\n", cur_e, next_e);
            }
            getchar();
            getchar();
            break;
        case 10:
            if (isinit(L) == FALSE)
                printf("���Ա�δ����\n");
            else
            {
                printf("������Ҫ�����λ��:");
                scanf("%d", &i);
                printf("������Ҫ�����Ԫ�أ�");
                scanf("%d", &e);
                sta = ListInsert(L, i, e);
                if (sta == ERROR)
                    printf("����λ�ò��Ϸ�\n");
                else
                    printf("����ɹ�\n");
            }
            getchar();
            getchar();
            break;
        case 11:
            if (isinit(L) == FALSE)
                printf("���Ա�δ����\n");
            else
            {
                printf("������Ҫɾ����λ��:");
                scanf("%d", &i);

                sta = ListDelete(L, i, &e);
                if (sta == ERROR)
                    printf("ɾ��λ�ò��Ϸ�\n");
                else
                    printf("ɾ��%d�ɹ�\n", e);
            }
            getchar();
            getchar();
            break;
        case 12:
            if (isinit(L) == FALSE)
                printf("���Ա�δ����\n");
            else
            {
                sta = ListTrabverse(L);
                if (sta == ERROR)
                    printf("���Ա�Ϊ�ձ�\n");
            }
            getchar();
            getchar();
            break;
        case 0:
            break;
        } //end of switch
    }     //end of while
    printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
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
    // ����ĳһ��Ԫ�ص�ǰһ��Ԫ�صĵ�ֵַ �������򷵻����һ���ڵ�ĵ�ַ
    PtrToLNode p = L;
    while (p->next && p->next->data != e)
        p = p->next;
    return p;
}

status InitList(List *L)
{
    // ����Ѿ�����
    // if (*L)
    //     return ERROR;
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
    // // δ����
    // if ((*L) == NULL)
    //     return INFEASTABLE;

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
    // if (L == NULL)
    //     return INFEASTABLE;
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
    // �������Ա���

    // if (L == NULL) //δ����
    //     return INFEASTABLE;
    // else
    return L->data;
}
status GetElem(List L, int i, int *e)
{
    // if (L == NULL) //δ����
    //     return INFEASTABLE;
    // if (ListEmpty(L) == 0)
    //     return ERROR;

    if (i < 1 || i > ListLength(L)) //i ���Ϸ�
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
    // ����e���ڵ�Ϊ��  ��1��ʼ
    // if (L == NULL) //δ����
    //     return INFEASTABLE;

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
        return NOTFOUND;
}

status PriorElem(List L, int cur_e, int *pre_e)
{
    // if (L == NULL) //δ����
    //     return INFEASTABLE;

    PtrToLNode p = GetAdress(L, cur_e);
    if (p->next == NULL) // û����һ��Ԫ��
        return NOTFOUND;
    else if (p == L) // ��һ��Ԫ��  û��ǰ��
        return ERROR;
    else
    {
        *pre_e = p->data;
        return OK;
    }
}

status NextElem(List L, int cur_e, int *next_e)
{
    // if (L == NULL) //δ����
    //     return INFEASTABLE;

    PtrToLNode p = GetAdress(L, cur_e);
    if (p->next == NULL) // û����һ��Ԫ��
        return NOTFOUND;
    else if (p->next->next == NULL) // ���һ��Ԫ��  û�к��
        return ERROR;
    else
    {
        *next_e = p->next->next->data;
        return OK;
    }
}

status ListInsert(List L, int i, int e)
{
    //��i��λ���ϲ���e
    PtrToLNode p = L; // pΪҪ�����λ�õ�ǰһ��λ��

    if (i < 1 || i > ListLength(L) + 1) //i ���Ϸ�
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
    // ɾ��i��λ�õ�ֵ ��e����

    PtrToLNode p = L;               // pΪҪɾ����λ�õ�ǰһ��λ��
    if (i < 1 || i > ListLength(L)) //i ���Ϸ�
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
{ // ����
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