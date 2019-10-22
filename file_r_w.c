#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    char c;
    int d;
    float f;
} ElemType;
typedef struct
{
    ElemType elem[10];
    int length;
} SqList;
SqList L = {
    {
    {'a', 1, 1.1}, 
    {'b', 2, 2.2}, 
    {'c', 3, 3.3}, {'d', 4, 4.4}
    }, 
    4};

int main(int argc, char *argv[])
{
    FILE *fp;
    char filename[30];
    int i;
    printf("input file name: ");
    scanf("%s", filename);

    //写文件的方法
    if ((fp = fopen(filename, "wb")) == NULL)
    {
        printf("File open error\n ");
        return 1;
    }
    fwrite(L.elem, sizeof(ElemType), L.length, fp);
    //这里是1次性写入，对于其它物理结构，可通过遍历，逐个访问数据元素
    //并写入到文件中。也可以先写入表长，再写入全部元素，这样读入会更方便
    fclose(fp);

    //读文件的方法
    L.length = 0;
    if ((fp = fopen(filename, "rb")) == NULL)
    {
        printf("File open erroe\n ");
        return 1;
    }
    while (fread(&L.elem[L.length], sizeof(ElemType), 1, fp))
        L.length++;
    //这里从文件中逐个读取数据元素恢复顺序表，对于不同的物理结构，可通过读//取的数据元素恢复内存中的物理结构。
    fclose(fp);
    return 0;
}
