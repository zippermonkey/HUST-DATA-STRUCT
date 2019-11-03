// 没有多表

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
typedef int ElemType; //数据元素类型定义

/*-------page 22 on textbook -------*/
#define LIST_INIT_SIZE 100
#define LISTINCREMENT 10
typedef struct { //顺序表（顺序结构）的定义
  ElemType *elem;
  char name[41]; //表名字 在初始化表的时候写入
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
status LocateElem(SqList *L, ElemType e); //简化过
status PriorElem(SqList *L, ElemType cur, ElemType *pre_e);
status NextElem(SqList *L, ElemType cur, ElemType *next_e);
status ListInsert(SqList *L, int i, ElemType e);
status ListDelete(SqList *L, int i, ElemType *e);
status ListTrabverse(SqList *L); //简化过
/*--------------------------------------------*/

status SaveList(SqList *L);  // 保存数据到文件
status LoadList(SqList *L);  // 从文件加载数据
status InputData(SqList *L); // 手动输入数据

// 多表操作
status ShowLists(Table *head);          // 显示
status Remove(Table *head);             //删除
status AddList(Table *head, SqList *L); //增加
status Choose(Table *head, SqList **L); // 选择
int LengthofTable(Table *head);         // 求长度

int main(void) {
  SqList *L = NULL;
  Table *head = (Table *)malloc(sizeof(Table));
  head->next = NULL;
  int op = 1;
  /********/
  // 此处为定义的一些临时变量  具体作用看不同的case
  int i = 0;
  int e = -1;
  int pre_e = -1;
  int next_e = -1;
  status sta = OK; // 表示函数返回值
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
    printf("请选择你的操作[0~19]:");
    scanf("%d", &op);
    switch (op) {
    case 1:
      // 初始化一个线性表
      if (InitList(&L) == OVERFLOW)
        printf("线性表创建失败！\n");
      else
        printf("线性表创建成功！\n");
      printf("按任意键继续\n");
      getchar();
      getchar();
      break;
    case 2:
      // 销毁线性表
      if (DestroyList(&L) == INFEASTABLE)
        printf("线性表销毁失败 因为线性表未创建！\n");
      else
        printf("线性表销毁成功！\n");
      printf("按任意键继续\n");
      getchar();
      getchar();

      break;
    case 3:
      // 清空线性表
      if (ClearList(L) == OK)
        printf("线性表清空成功！\n");
      else
        printf("线性表未创建，清空失败！\n");
      printf("按任意键继续\n");
      getchar();
      getchar();

      break;
    case 4:
      // 判断线性表是否为空
      if (ListEmpty(L) == INFEASTABLE)
        printf("线性表未创建！\n");
      else if (ListEmpty(L) == FALSE)
        printf("线性表不为空！\n");
      else
        printf("线性表为空！\n");
      printf("按任意键继续\n");
      getchar();
      getchar();

      break;
    case 5:
      // 求线性表长度
      if (ListLength(L) != INFEASTABLE)
        printf("线性表长度为%d\n", ListLength(L));
      else
        printf("线性表未创建\n");
      printf("按任意键继续\n");
      getchar();
      getchar();
      break;
    case 6:
      // 取得表中的第i位元素  从1开始数
      printf("请输入要取得线性表中的哪一位元素(i) 从1开始数： ");
      scanf("%d", &i);
      sta = GetElem(L, i, &e); // sta表示函数状态
      if (sta != OK) {
        if (sta == INFEASTABLE)
          printf("线性表未创建\n");
        else if (sta == ERROR)
          printf("i值不合法\n");
      } else {
        printf("第%d位元素是%d\n", i, e);
      }
      printf("按任意键继续\n");
      getchar();
      getchar();

      break;
    case 7:
      //输入一个元素值 将返回它在表中的位置
      printf("请输入一个元素值 将返回它在表中的位置\n");
      scanf("%d", &e);
      sta = LocateElem(L, e); // t表示函数的状态
      if (sta == INFEASTABLE) {
        printf("线性表未创建\n");
      } else if (sta == NOTFOUND) {
        printf("表中没有这个元素\n");
      } else {
        printf("%d的位置是%d\n", e, sta);
      }
      printf("按任意键继续\n");
      getchar();
      getchar();

      break;
    case 8:
      // 求元素前驱
      printf("输入线性表中的一个数: ");
      scanf("%d", &e);
      sta = PriorElem(L, e, &pre_e); // sta 表示函数返回值
      if (sta == OK)
        printf("%d的前驱是%d\n", e, pre_e);
      else if (sta == INFEASTABLE)
        printf("线性表未创建\n");
      else if (sta == ERROR)
        printf("%d为第一个元素,没有前驱\n", e);
      else if (sta == NOTFOUND)
        printf("表中不存在元素%d\n", e);
      printf("按任意键继续\n");
      getchar();
      getchar();

      break;
    case 9:
      // 求元素后继
      printf("输入线性表中的一个数: ");
      scanf("%d", &e);
      sta = NextElem(L, e, &next_e); // sta 表示函数返回值
      if (sta == OK)
        printf("%d的后继是%d\n", e, next_e);
      else if (sta == INFEASTABLE)
        printf("线性表未创建\n");
      else if (sta == ERROR)
        printf("%d为最后一个元素,没有后继\n", e);
      else if (sta == NOTFOUND)
        printf("不存在元素%d\n", e);
      printf("按任意键继续\n");
      getchar();
      getchar();
      break;
    case 10:
      // 插入元素
      printf("输入插入的位置i（从1开始计数）\n");
      scanf("%d", &i);
      printf("输入插入的值e\n");
      scanf("%d", &e);
      sta = ListInsert(L, i, e);
      if (sta == OK)
        printf("插入成功！\n");
      else if (sta == INFEASTABLE)
        printf("线性表未创建\n");
      else if (sta == ERROR)
        printf("插入位置不合法\n");
      printf("按任意键继续\n");
      getchar();
      getchar();

      break;
    case 11:
      // 删除元素
      printf("输入删除的位置i（从1开始计数）\n");
      scanf("%d", &i);
      sta = ListDelete(L, i, &e);
      if (sta == OK) {
        printf("删除%d成功！\n", e);
      } else if (sta == INFEASTABLE)
        printf("线性表未创建\n");

      else if (sta == ERROR)
        printf("删除位置不合法\n");
      printf("按任意键继续\n");
      getchar();
      getchar();

      break;
    case 12:
      // 遍历元素
      sta = ListTrabverse(L);
      if (sta == INFEASTABLE)
        printf("线性表未创建\n");
      else if (sta == ERROR)
        printf("线性表为空\n");

      printf("按任意键继续\n");
      getchar();
      getchar();

      break;
    case 13:
      sta = InputData(L);
      if (sta == INFEASTABLE) {
        printf("线性表未创建\n");
      }
      printf("按任意键继续\n");
      getchar();
      getchar();
      break;

    case 14:
      // 将当前表保存到文件
      sta = SaveList(L);
      if (sta == INFEASTABLE)
        printf("线性表未创建\n");
      else if (sta == ERROR)
        printf("文件打开失败\n");
      else
        printf("保存为%s成功\n", L->name);
      printf("按任意键继续\n");
      getchar();
      getchar();
      break;
    case 15:
      // 从文件加载表 前提是先创建表
      sta = LoadList(L);
      if (sta == INFEASTABLE)
        printf("线性表未创建\n");
      else if (sta == ERROR)
        printf("文件打开失败\n");
      else
        printf("加载成功\n");
      getchar();
      getchar();
      break;
    case 16:
      // 从多表中选取一个表
      sta = Choose(head, &L);
      if (sta == ERROR)
        printf("序号不合法");
      else if (sta == OK)
        printf("按任意键继续\n");
      getchar();
      getchar();
      break;

    case 17:
      // 添加
      sta = AddList(head, L);
      if (sta == INFEASTABLE)
        printf("线性表未创键\n");
      printf("按任意键继续\n");
      getchar();
      getchar();
      break;
    case 18:
      // 显示
      sta = ShowLists(head);
      printf("按任意键继续\n");
      getchar();
      getchar();
      break;

    case 19:
      sta = Remove(head);
      if (sta == ERROR)
        printf("i值不合法\n");
      else
        printf("按任意键继续\n");
      getchar();
      getchar();
      break;
    case 0:
      break;

    default:
      printf("请输入有效值\n");
      getchar();
      getchar();
      break;
    } // end of switch
  }   // end of while
  printf("欢迎下次再使用本系统！\n");
  return 0;
} // end of main()

status InitList(SqList **L) {
  *L = (SqList *)malloc(sizeof(SqList));
  if (*L == NULL) {
    // L动态内存分配失败
    return OVERFLOW;
  }
  (*L)->elem = (ElemType *)malloc(sizeof(ElemType) * LIST_INIT_SIZE);
  if ((*L)->elem == NULL) {
    // L->elem动态内存分配失败
    return OVERFLOW;
  }
  printf("请输入表名字 不超过40个字符\n");
  scanf("%s", (*L)->name);
  (*L)->length = 0;
  (*L)->listsize = LIST_INIT_SIZE;
  return OK;
}
status DestroyList(SqList **L) {
  if ((*L) == NULL) // 线性表未创建
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
  if (!L) // 线性表未创建
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;
  L->length = 0;
  return OK;
}
status ListEmpty(SqList *L) {
  if (!L) // 线性表未创建
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;
  return L->length == 0; // L->length == 0则为空表
}
int ListLength(SqList *L) {
  if (!L) // 线性表未创建
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  return L->length;
}
status GetElem(SqList *L, int i, ElemType *e) {
  if (!L) // 线性表未创建
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  if (i < 1 || i > L->length) // 请求越界
  {
    return ERROR;
  }

  *e = *(L->elem + i - 1); // 把e指向要取得的元素
  return OK;
}

int LocateElem(SqList *L, ElemType e) {
  // 以1开始
  if (!L) // 线性表未创建
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;
  for (int i = 1; i <= L->length; i++) {
    if (e == L->elem[i - 1]) {
      return i; //返回第位置i  i从1开始
    }
  }
  return NOTFOUND; //没有找到
}

status PriorElem(SqList *L, ElemType cur, ElemType *pre_e) {
  if (!L) // 线性表未创建
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  // 寻找元素cur
  int i = 1;
  for (i = 1; i <= L->length; i++)
    if (cur == L->elem[i - 1])
      break;
  if (i == L->length + 1) // 没找到
  {
    return NOTFOUND;
  } else if (i == 1) // 如果cur为第一个元素 则没有前驱
  {
    return ERROR;
  } else {
    *pre_e = *(L->elem + (i - 2));
    return OK;
  }
}

status NextElem(SqList *L, ElemType cur, ElemType *next_e) {
  if (!L) // 线性表未创建
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  // 寻找元素cur
  int i = 1;
  for (i = 1; i <= L->length; i++) {
    if (cur == L->elem[i - 1]) {
      break;
    }
  }
  if (i == L->length + 1) // 没找到
  {
    return NOTFOUND;
  } else if (i == L->length) // 如果cur为最后一个元素 则没有后继
  {
    return ERROR;
  } else {
    *next_e = *(L->elem + (i));
    return OK;
  }
}
status ListInsert(SqList *L, int i, ElemType e) {
  // 插入元素
  if (!L) // 线性表未创建
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  if (i < 1 || i > L->length + 1) // 插入位置不合法
    return ERROR;

  if (L->length >= L->listsize) { // 空间不足 重新分配
    ElemType *newbase = (ElemType *)realloc(
        L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
    if (!newbase)
      exit(OVERFLOW);
    L->elem = newbase;
    L->listsize += LISTINCREMENT;
  }

  ElemType *q = &(L->elem[i - 1]); // q为要插入的位置

  for (ElemType *p = &(L->elem[L->length - 1]); p >= q; --p)
    // 插入位置及之后的元素右移
    *(p + 1) = *p;

  *q = e;
  L->length++;
  return OK;
}

status ListDelete(SqList *L, int i, ElemType *e) {
  // 在顺序线性表L中删除第i个元素 并用e返回值
  // i的合法位置为1<= i <= L->length
  if (!L) // 线性表未创建
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  if (i < 1 || i > L->length) // i值不合法
    return ERROR;

  ElemType *p = &(L->elem[i - 1]); // p为要删除的元素地址
  *e = *p;

  ElemType *q = &(L->elem[L->length - 1]); // q为表尾元素地址

  for (p++; p <= q; p++) // 元素移动
    *(p - 1) = *p;

  L->length--;
  return OK;
}
status ListTrabverse(SqList *L) {
  if (!L) // 线性表未创建

    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  if (L->length == 0)
    // 空表
    return ERROR;
  for (int i = 0; i < L->length; i++) {
    // 遍历
    printf("%d", L->elem[i]);
    if (i < L->length - 1)
      printf(" --> ");
  }
  putchar('\n');
  return OK;
}

status InputData(SqList *L) {
  // 手动输入数据

  if (!L) // 线性表未创建
  {
    return INFEASTABLE;
  } else if (!L->elem) {
    return INFEASTABLE;
  }
  printf("请输入数据（整数），以空格分隔,以q退出\n");
  int x = 0;

  while ((scanf("%d", &x) == 1)) {
    if (L->length >= L->listsize) { // 空间不足 重新分配
      ElemType *newbase = (ElemType *)realloc(
          L->elem, (L->listsize + LISTINCREMENT) * sizeof(ElemType));
      if (!newbase)
        exit(OVERFLOW);
      L->elem = newbase;
      L->listsize += LISTINCREMENT;
    }
    L->elem[L->length++] = x; // 写入数据
  }
  return OK;
}

status SaveList(SqList *L) {
  if (!L) // 线性表未创建
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  FILE *fp;
  // 写文件
  if ((fp = fopen(L->name, "wb")) == NULL) //文件打开失败
  {
    printf("File open error\n ");
    return ERROR;
  }
  fwrite(L->elem, sizeof(ElemType), L->length, fp);
  fclose(fp);
  return OK;
}
status LoadList(SqList *L) {
  if (!L) // 线性表未创建
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;

  //读文件
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
  if (!L) // 线性表未创建
    return INFEASTABLE;
  else if (!L->elem)
    return INFEASTABLE;
  Table *p = (Table *)malloc(sizeof(Table));
  p->list = L;
  p->next = NULL;
  // 后进先出  带头节点
  p->next = head->next;
  head->next = p;
  return OK;
}

status ShowLists(Table *head) {
  Table *p = head->next;
  int i = 1;
  printf("序号\t表长\t表名\n");
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
  printf("请输入选择的表的序号：");
  scanf("%d", &i);
  if (i < 1 || i > LengthofTable(head)) // 序号不合法
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
  printf("输入删除序号：");
  scanf("%d", &i);
  if (i < 1 || i > LengthofTable(head)) // 序号不合法
    return ERROR;

  Table *p = head;
  int j = 0;
  for (j = 1; j < i; j++) {
    p = p->next;
  }
  Table *q = p->next; // 改变结构  删除节点
  p->next = q->next;
  free(q->list->elem);
  free(q->list);
  free(q);
  return OK;
}