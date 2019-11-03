// û�ж��

/* Linear Table On Sequence Structure */
#include <malloc.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>

/*---------page 10 on textbook ---------*/
#define TRUE 1
#define FALSE 0
#define OK 1
#define ERROR 0
#define INFEASTABLE -1
#define OVERFLOW -2
#define NOTFOUND -3

typedef int status;
typedef int ElemType; //����Ԫ�����Ͷ���

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef struct { //˳���˳��ṹ���Ķ���
  ElemType *elem;
  char name[41]; //������ �ڳ�ʼ�����ʱ��д��
  int length;
  int listsize;
} SqList;

struct table {
  SqList *list;
  struct table *next;
};
typedef struct table Table;

/*-----page 19 on textbook ---------*/
status InitList(SqList **L);
status DestroyList(SqList **L);
status ClearList(SqList *L);
status ListEmpty(SqList *L);
int ListLength(SqList *L);
status GetElem(SqList *L, int i, ElemType *e);
status LocateElem(SqList *L, ElemType e); //�򻯹�
status PriorElem(SqList *L, ElemType cur, ElemType *pre_e);
status NextElem(SqList *L, ElemType cur, ElemType *next_e);
status ListInsert(SqList *L, int i, ElemType e);
status ListDelete(SqList *L, int i, ElemType *e);
status ListTrabverse(SqList *L); //�򻯹�
/*--------------------------------------------*/

status SaveList(SqList *L);  // �������ݵ��ļ�
status LoadList(SqList *L);  // ���ļ���������
status InputData(SqList *L); // �ֶ���������

// ������
status ShowLists(Table *head);          // ��ʾ
status Remove(Table *head);             //ɾ��
status AddList(Table *head, SqList *L); //����
status Choose(Table *head, SqList **L); // ѡ��
int LengthofTable(Table *head);         // �󳤶�

int main(void) {
  SqList *L = NULL;
  Table *head = (Table *)malloc(sizeof(Table));
  head->next = NULL;
  int op = 1;
  /********/
  // �˴�Ϊ�����һЩ��ʱ����  �������ÿ���ͬ��case
  int i = 0;
  int e = -1;
  int pre_e = -1;
  int next_e = -1;
  status sta = OK; // ��ʾ��������ֵ
  /********/
  while (op) {
    // linux
    // system("clear");

    // windows
    system("cls");

    printf("\n\n");
    printf("      Menu for Linear Table On Sequence Structure \n\n");
    printf("-------------------------------------------------\n");
    printf("    	  1. InitList           7. LocateElem\n");
    printf("    	  2. DestroyList        8. PriorElem\n");
    printf("    	  3. ClearList          9. NextElem \n");
    printf("    	  4. ListEmpty          10. ListInsert\n");
    printf("    	  5. ListLength         11. ListDelete\n");
    printf("    	  6. GetElem            12. ListTrabverse\n");
    printf("    	  13. InputData         14. SavaList\n");
    printf("    	  15. LoadList          16. Choose\n");
    printf("    	  17. AddToTable        18. ShowLists\n");
    printf("    	  19. Remove            0. Exit\n");
    printf("-------------------------------------------------\n");
    printf("��ѡ����Ĳ���[0~19]:");
    scanf("%d", &op);
    switch (op) {
    case 1:
      // ��ʼ��һ�����Ա�
      if (InitList(&L) == OVERFLOW)
        printf("���Ա���ʧ�ܣ�\n");
      else
        printf("���Ա����ɹ���\n");
      printf("�����������\n");
      getchar();
      getchar();
      break;
    case 2:
      // �������Ա�
      if (DestroyList(&L) == INFEASTABLE)
        printf("���Ա�����ʧ�� ��Ϊ���Ա�δ������\n");
      else
        printf("���Ա����ٳɹ���\n");
      printf("�����������\n");
      getchar();
      getchar();

      break;
    case 3:
      // ������Ա�
      if (ClearList(L) == OK)
        printf("���Ա���ճɹ���\n");
      else
        printf("���Ա�δ���������ʧ�ܣ�\n");
      printf("�����������\n");
      getchar();
      getchar();

      break;
    case 4:
      // �ж����Ա��Ƿ�Ϊ��
      if (ListEmpty(L) == INFEASTABLE)
        printf("���Ա�δ������\n");
      else if (ListEmpty(L) == FALSE)
        printf("���Ա�Ϊ�գ�\n");
      else
        printf("���Ա�Ϊ�գ�\n");
      printf("�����������\n");
      getchar();
      getchar();

      break;
    case 5:
      // �����Ա���
      if (ListLength(L) != INFEASTABLE)
        printf("���Ա���Ϊ%d\n", ListLength(L));
      else
        printf("���Ա�δ����\n");
      printf("�����������\n");
      getchar();
      getchar();
      break;
    case 6:
      // ȡ�ñ��еĵ�iλԪ��  ��1��ʼ��
      printf("������Ҫȡ�����Ա��е���һλԪ��(i) ��1��ʼ���� ");
      scanf("%d", &i);
      sta = GetElem(L, i, &e); // sta��ʾ����״̬
      if (sta != OK) {
        if (sta == INFEASTABLE)
          printf("���Ա�δ����\n");
        else if (sta == ERROR)
          printf("iֵ���Ϸ�\n");
      } else {
        printf("��%dλԪ����%d\n", i, e);
      }
      printf("�����������\n");
      getchar();
      getchar();

      break;
    case 7:
      //����һ��Ԫ��ֵ ���������ڱ��е�λ��
      printf("������һ��Ԫ��ֵ ���������ڱ��е�λ��\n");
      scanf("%d", &e);
      sta = LocateElem(L, e); // t��ʾ������״̬
      if (sta == INFEASTABLE) {
        printf("���Ա�δ����\n");
      } else if (sta == NOTFOUND) {
        printf("����û�����Ԫ��\n");
      } else {
        printf("%d��λ����%d\n", e, sta);
      }
      printf("�����������\n");
      getchar();
      getchar();

      break;
    case 8:
      // ��Ԫ��ǰ��
      printf("�������Ա��е�һ����: ");
      scanf("%d", &e);
      sta = PriorElem(L, e, &pre_e); // sta ��ʾ��������ֵ
      if (sta == OK)
        printf("%d��ǰ����%d\n", e, pre_e);
      else if (sta == INFEASTABLE)
        printf("���Ա�δ����\n");
      else if (sta == ERROR)
        printf("%dΪ��һ��Ԫ��,û��ǰ��\n", e);
      else if (sta == NOTFOUND)
        printf("���в�����Ԫ��%d\n", e);
      printf("�����������\n");
      getchar();
      getchar();

      break;
    case 9:
      // ��Ԫ�غ��
      printf("�������Ա��е�һ����: ");
      scanf("%d", &e);
      sta = NextElem(L, e, &next_e); // sta ��ʾ��������ֵ
      if (sta == OK)
        printf("%d�ĺ����%d\n", e, next_e);
      else if (sta == INFEASTABLE)
        printf("���Ա�δ����\n");
      else if (sta == ERROR)
        printf("%dΪ���һ��Ԫ��,û�к��\n", e);
      else if (sta == NOTFOUND)
        printf("������Ԫ��%d\n", e);
      printf("�����������\n");
      getchar();
      getchar();
      break;
    case 10:
      // ����Ԫ��
      printf("��������λ��i����1��ʼ������\n");
      scanf("%d", &i);
      printf("��������ֵe\n");
      scanf("%d", &e);
      sta = ListInsert(L, i, e);
      if (sta == OK)
        printf("����ɹ���\n");
      else if (sta == INFEASTABLE)
        printf("���Ա�δ����\n");
      else if (sta == ERROR)
        printf("����λ�ò��Ϸ�\n");
      printf("�����������\n");
      getchar();
      getchar();

      break;
    case 11:
      // ɾ��Ԫ��
      printf("����ɾ����λ��i����1��ʼ������\n");
      scanf("%d", &i);
      sta = ListDelete(L, i, &e);
      if (sta == OK) {
        printf("ɾ��%d�ɹ���\n", e);
      } else if (sta == INFEASTABLE)
        printf("���Ա�δ����\n");

      else if (sta == ERROR)
        printf("ɾ��λ�ò��Ϸ�\n");
      printf("�����������\n");
      getchar();
      getchar();

      break;
    case 12:
      // ����Ԫ��
      sta = ListTrabverse(L);
      if (sta == INFEASTABLE)
        printf("���Ա�δ����\n");
      else if (sta == ERROR)
        printf("���Ա�Ϊ��\n");

      printf("�����������\n");
      getchar();
      getchar();

      break;
    case 13:
      sta = InputData(L);
      if (sta == INFEASTABLE) {
        printf("���Ա�δ����\n");
      }
      printf("�����������\n");
      getchar();
      getchar();
      break;

    case 14:
      // ����ǰ���浽�ļ�
      sta = SaveList(L);
      if (sta == INFEASTABLE)
        printf("���Ա�δ����\n");
      else if (sta == ERROR)
        printf("�ļ���ʧ��\n");
      else
        printf("����Ϊ%s�ɹ�\n", L->name);
      printf("�����������\n");
      getchar();
      getchar();
      break;
    case 15:
      // ���ļ����ر� ǰ�����ȴ�����
      sta = LoadList(L);
      if (sta == INFEASTABLE)
        printf("���Ա�δ����\n");
      else if (sta == ERROR)
        printf("�ļ���ʧ��\n");
      else
        printf("���سɹ�\n");
      getchar();
      getchar();
      break;
    case 16:
      // �Ӷ����ѡȡһ����
      sta = Choose(head, &L);
      if (sta == ERROR)
        printf("��Ų��Ϸ�");
      else if (sta == OK)
        printf("�����������\n");
      getchar();
      getchar();
      break;

    case 17:
      // ���
      sta = AddList(head, L);
      if (sta == INFEASTABLE)
        printf("���Ա�δ����\n");
      printf("�����������\n");
      getchar();
      getchar();
      break;
    case 18:
      // ��ʾ
      sta = ShowLists(head);
      printf("�����������\n");
      getchar();
      getchar();
      break;

    case 19:
      sta = Remove(head);
      if (sta == ERROR)
        printf("iֵ���Ϸ�\n");
      else
        printf("�����������\n");
      getchar();
      getchar();
      break;
    case 0:
      break;

    default:
      printf("��������Чֵ\n");
      getchar();
      getchar();
      break;
    } // end of switch
  }   // end of while
  printf("��ӭ�´���ʹ�ñ�ϵͳ��\n");
  return 0;
} // end of main()

status InitList(SqList **L) {
  *L = (SqList *)malloc(sizeof(SqList));
  if (*L == NULL) {
    // L��̬�ڴ����ʧ��
    return OVERFLOW;
  }
  (*L)->elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
  if ((*L)->elem == NULL) {
    // L->elem��̬�ڴ����ʧ��
    return OVERFLOW;
  }
  printf("����������� ������40���ַ�\n");
  scanf("%s", (*L)->name);
  (*L)->length = 0;
  (*L)->listsize = LIST_INIT_SIZE;
  return OK;
}
status DestroyList(SqList **L) {
  if ((*L) == NULL) // ���Ա�δ����
    return INFEASTABLE;
  else if (!(*L)->elem)
    return INFEASTABLE;

  (*L)->listsize = (*L)->length = 0;
  free((*L)->elem);
  (*L)->elem = NULL;
  free(*L);
  *L = NULL;
  return OK;
}
status ClearList(SqList *L) {
  if (!L) // ���Ա�δ����
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;
  L->length = 0;
  return OK;
}
status ListEmpty(SqList *L) {
  if (!L) // ���Ա�δ����
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;
  return L->length == 0; // L->length == 0��Ϊ�ձ�
}
int ListLength(SqList *L) {
  if (!L) // ���Ա�δ����
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  return L->length;
}
status GetElem(SqList *L, int i, ElemType *e) {
  if (!L) // ���Ա�δ����
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  if (i < 1 || i > L->length) // ����Խ��
  {
    return ERROR;
  }

  *e = *(L->elem + i - 1); // ��eָ��Ҫȡ�õ�Ԫ��
  return OK;
}

int LocateElem(SqList *L, ElemType e) {
  // ��1��ʼ
  if (!L) // ���Ա�δ����
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;
  for (int i = 1; i <= L->length; i++) {
    if (e == L->elem[i - 1]) {
      return i; //���ص�λ��i  i��1��ʼ
    }
  }
  return NOTFOUND; //û���ҵ�
}

status PriorElem(SqList *L, ElemType cur, ElemType *pre_e) {
  if (!L) // ���Ա�δ����
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  // Ѱ��Ԫ��cur
  int i = 1;
  for (i = 1; i <= L->length; i++)
    if (cur == L->elem[i - 1])
      break;
  if (i == L->length + 1) // û�ҵ�
  {
    return NOTFOUND;
  } else if (i == 1) // ���curΪ��һ��Ԫ�� ��û��ǰ��
  {
    return ERROR;
  } else {
    *pre_e = *(L->elem + (i - 2));
    return OK;
  }
}

status NextElem(SqList *L, ElemType cur, ElemType *next_e) {
  if (!L) // ���Ա�δ����
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  // Ѱ��Ԫ��cur
  int i = 1;
  for (i = 1; i <= L->length; i++) {
    if (cur == L->elem[i - 1]) {
      break;
    }
  }
  if (i == L->length + 1) // û�ҵ�
  {
    return NOTFOUND;
  } else if (i == L->length) // ���curΪ���һ��Ԫ�� ��û�к��
  {
    return ERROR;
  } else {
    *next_e = *(L->elem + (i));
    return OK;
  }
}
status ListInsert(SqList *L, int i, ElemType e) {
  // ����Ԫ��
  if (!L) // ���Ա�δ����
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  if (i < 1 || i > L->length + 1) // ����λ�ò��Ϸ�
    return ERROR;

  if (L->length >= L->listsize) { // �ռ䲻�� ���·���
    ElemType *newbase = (ElemType *)realloc(
        L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
    if (!newbase)
      exit(OVERFLOW);
    L->elem = newbase;
    L->listsize += LISTINCREMENT;
  }

  ElemType *q = &(L->elem[i - 1]); // qΪҪ�����λ��

  for (ElemType *p = &(L->elem[L->length - 1]); p >= q; --p)
    // ����λ�ü�֮���Ԫ������
    *(p + 1) = *p;

  *q = e;
  L->length++;
  return OK;
}

status ListDelete(SqList *L, int i, ElemType *e) {
  // ��˳�����Ա�L��ɾ����i��Ԫ�� ����e����ֵ
  // i�ĺϷ�λ��Ϊ1<= i <= L->length
  if (!L) // ���Ա�δ����
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  if (i < 1 || i > L->length) // iֵ���Ϸ�
    return ERROR;

  ElemType *p = &(L->elem[i - 1]); // pΪҪɾ����Ԫ�ص�ַ
  *e = *p;

  ElemType *q = &(L->elem[L->length - 1]); // qΪ��βԪ�ص�ַ

  for (p++; p <= q; p++) // Ԫ���ƶ�
    *(p - 1) = *p;

  L->length--;
  return OK;
}
status ListTrabverse(SqList *L) {
  if (!L) // ���Ա�δ����

    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  if (L->length == 0)
    // �ձ�
    return ERROR;
  for (int i = 0; i < L->length; i++) {
    // ����
    printf("%d", L->elem[i]);
    if (i < L->length - 1)
      printf(" --> ");
  }
  putchar('\n');
  return OK;
}

status InputData(SqList *L) {
  // �ֶ���������

  if (!L) // ���Ա�δ����
  {
    return INFEASTABLE;
  } else if (!L->elem) {
    return INFEASTABLE;
  }
  printf("���������ݣ����������Կո�ָ�,��q�˳�\n");
  int x = 0;

  while ((scanf("%d", &x) == 1)) {
    if (L->length >= L->listsize) { // �ռ䲻�� ���·���
      ElemType *newbase = (ElemType *)realloc(
          L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
      if (!newbase)
        exit(OVERFLOW);
      L->elem = newbase;
      L->listsize += LISTINCREMENT;
    }
    L->elem[L->length++] = x; // д������
  }
  return OK;
}

status SaveList(SqList *L) {
  if (!L) // ���Ա�δ����
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  FILE *fp;
  // д�ļ�
  if ((fp = fopen(L->name, "wb")) == NULL) //�ļ���ʧ��
  {
    printf("File open error\n ");
    return ERROR;
  }
  fwrite(L->elem, sizeof(ElemType), L->length, fp);
  fclose(fp);
  return OK;
}
status LoadList(SqList *L) {
  if (!L) // ���Ա�δ����
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  //���ļ�
  FILE *fp;
  char filename[30];
  printf("input file name: ");
  scanf("%s", filename);
  L->length = 0;
  if ((fp = fopen(filename, "rb")) == NULL) {
    printf("File open error\n ");
    return ERROR;
  }
  while (fread(&(L->elem[L->length]), sizeof(ElemType), 1, fp))
    L->length++;
  fclose(fp);
  return OK;
}

status AddList(Table *head, SqList *L) {
  if (!L) // ���Ա�δ����
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;
  Table *p = (Table *)malloc(sizeof(Table));
  p->list = L;
  p->next = NULL;
  // ����ȳ�  ��ͷ�ڵ�
  p->next = head->next;
  head->next = p;
  return OK;
}

status ShowLists(Table *head) {
  Table *p = head->next;
  int i = 1;
  printf("���\t��\t����\n");
  while (p) {
    if (p->list->elem == NULL) {
      i++;
      p = p->next;
      continue;
    }
    printf("%d\t%d\t%s\n", i++, p->list->length, p->list->name);
    p = p->next;
  }
  return OK;
}

int LengthofTable(Table *head) {

  int i = 0;
  Table *p = head->next;
  while (p) {
    i++;
    p = p->next;
  }
  return i;
}

status Choose(Table *head, SqList **L) {
  int i = 0;
  Table *p = head->next;
  Table *q = p;
  ShowLists(head);
  printf("������ѡ��ı����ţ�");
  scanf("%d", &i);
  if (i < 1 || i > LengthofTable(head)) // ��Ų��Ϸ�
    return ERROR;
  int k = i;
  for (k = 1; k < i; k++) {
    q = q->next;
  }
  if (q->list->elem == NULL)
    return ERROR;
  int j = 0;
  for (j = 1; j < i; j++) {
    p = p->next;
  }
  (*L) = p->list;
  return OK;
}

status Remove(Table *head) {
  int i = 0;
  ShowLists(head);
  printf("����ɾ����ţ�");
  scanf("%d", &i);
  if (i < 1 || i > LengthofTable(head)) // ��Ų��Ϸ�
    return ERROR;

  Table *p = head;
  int j = 0;
  for (j = 1; j < i; j++) {
    p = p->next;
  }
  Table *q = p->next; // �ı�ṹ  ɾ���ڵ�
  p->next = q->next;
  free(q->list->elem);
  free(q->list);
  free(q);
  return OK;
}