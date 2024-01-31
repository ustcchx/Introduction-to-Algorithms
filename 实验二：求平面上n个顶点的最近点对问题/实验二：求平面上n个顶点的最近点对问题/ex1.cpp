#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <algorithm>
#include <time.h>

const int MINILENGTH = 20;



void Qsort(int *A, int start, int end);
void insert_sort(int *A, int start, int end);
void Partition(int *A, int start, int end, int *p_s, int *p_e);
void testsort(char *s);
void test_(char *s,int times);
void merge_sort_recursive(int A[], int B[], int start, int end);
void merge_sort(int A[], const int len);
int cmp(const void *a, const void *b);

int test(int *A,int *B, int num){
    for (int i = 0; i < num;i++){
        if(A[i] != B[i]){
            printf("error\n");
            return -1;
        }
    }
    return 0;
}

int main(){
    testsort((char*)"data.txt");
    //testsort((char*)"0.in");
    //testsort((char*)"1.in");
    //testsort((char*)"2.in");
    //testsort((char*)"3.in");
    test_((char *)"data.txt", 100);
    //test_((char *)"0.in", 100);
    //test_((char *)"1.in", 100);
    //test_((char *)"2.in", 10);
    //test_((char *)"3.in", 10);
}

void Qsort(int *A, int start,int end){
    
    int s, e;
    Partition(A, start, end, &s, &e);
    if(s > start)
        if(s - start <= MINILENGTH)
            insert_sort(A, start, s);
        else
            Qsort(A, start, s);
    if (e < end){
        if(end - e <= MINILENGTH)
            insert_sort(A, e, end);
        else
            Qsort(A, e, end);
    }
}   

void Partition(int *A, int start, int end, int *p_s,int *p_e){
    int s = *p_s;
    int e = *p_e;

    int i,tmp,ptr1,ptr2;
    int start_value, mid_value, end_value;


    start_value = A[start];
    end_value = A[end];
    mid_value = A[(start + end) / 2];

    if(end_value - start_value > 1){
        if(end_value < mid_value){
            if(start_value > mid_value){
                A[end] = mid_value;
                A[(start + end) / 2] = end_value;
            }
            else if(start_value > end_value){
                A[start] = end_value;
                A[end] = start_value;
            }
        }
        else{
            if (mid_value > start_value){
                A[end] = mid_value;
                A[(start + end) / 2] = end_value;
            }
            else if(start_value < end_value){
                A[start] = end_value;
                A[end] = start_value;
            }
        }
    }

    end_value = A[end];

    for (i = start,ptr1 = start,ptr2 = end; i < ptr2;i++){
        if(A[i] < end_value){
            if(i != ptr1){
                tmp = A[i];
                A[i] = A[ptr1];
                A[ptr1] = tmp;
            }
            ptr1++;
        }
        else if(A[i] == end_value){
            ptr2--;
            A[i] = A[ptr2];
            A[ptr2] = end_value;
            i--;
        }
    }

    if(ptr2 > ptr1){
        i = ptr2;
        ptr2 = ptr1;
        for (;i <= end;i++)
        {
            A[i] = A[ptr2];
            A[ptr2] = end_value;
            ptr2++;
        }
    }
    else{
        ptr2 = end;
    }


    //debug

    *p_s = ptr1 - 1;
    *p_e = ptr2;

    return;
}

void insert_sort(int *A,int start, int end){
    int i, j;
    int tmp;
    for (i = start + 1; i <= end;i++){
        tmp = A[i];
        for (j = i - 1; j >= start;j--){
            if(tmp < A[j]){
                A[j+1] = A[j];
            }
            else{
                A[j + 1] = tmp;
                break;
            }
        }
        if(j == start - 1)
            A[start] = tmp;
    }
}

void testsort(char*s){
    int num = 0;
    int *A, *B, *C,*D;
    int len = 0;
    for (; len < strlen(s);len++){
        if(s[len] == '.')
            break;
    }
    char path[100]="data.txt";

    FILE *f;
    if (!(f = fopen(path, "r")))
    {
        printf("open error\n");
        exit(1);
    }

    fscanf(f,"%d", &num);
    A = new int[num];
    B = new int[num];
    C = new int[num];
    D = new int[num];

    for (int i = 0; i < num;i++){
        fscanf(f,"%d", A + i);
        B[i] = A[i];
        C[i] = A[i];
        D[i] = A[i];
    }

    if(fclose(f)!=0) 
    {
    	printf("file closed error\n"); 
    	exit(1); 
    }

    clock_t std_start, std_finish;
    clock_t p_start, p_finish;
    clock_t i_start, i_finish;
    clock_t m_start, m_finish;

    std_start = clock();
    qsort(A, num,sizeof(int),cmp);
    std_finish = clock();

    p_start = clock();
    Qsort(B, 0, num - 1);
    p_finish = clock();

    test(A,B,num);
    //i_start = clock();
    //insert_sort(D, 0, num - 1);
    //i_finish = clock();
//
    //
//
    //m_start = clock();
    //merge_sort(C, num);
    //m_finish = clock();

    printf("test %s\n��������������������������������������������������������������\n", s);
    printf("std::sort: %d-%d = %d ms\n",std_finish,std_start, std_finish - std_start);
    printf("Qsort:  %d-%d =%d ms\n",p_finish,p_start, p_finish - p_start);
    //printf("InsertSort:  %d ms\n", i_finish - i_start);
    //printf("MergeSort:  %d ms\n", m_finish - m_start);
/*
���
��������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������������
*/

    strcpy(path, "data/");
    strncat(path, s, len);
    strcat(path, "_sortedA.txt");
    if (!(f = fopen(path, "w")))
    {
        printf("open error\n");
        exit(1);
    }
    
    for (int i = 0; i < num;i++){
        fprintf(f,"%d ", *(A + i));
    }

    if(fclose(f)) 
    {
    	printf("file closed error\n"); 
    	exit(1); 
    }

    strcpy(path, "data/");
    strncat(path, s, len);
    strcat(path, "_sortedB.txt");
    if (!(f = fopen(path, "w")))
    {
        printf("open error\n");
        exit(1);
    }
    
    for (int i = 0; i < num;i++){
        fprintf(f,"%d ", *(B + i));
    }

    if(fclose(f)) 
    {
    	printf("file closed error\n"); 
    	exit(1); 
    }

    delete A;
    delete B;
    delete C;
    delete D;
}

void test_(char* s, int times){
    int num = 0;
    int *A, *B;
    int len = 0;
    for (; len < strlen(s);len++){
        if(s[len] == '.')
            break;
    }
    char path[100];

    strcpy(path, "data/");
    strcat(path, s);
    FILE *f;
    if (!(f = fopen(path, "r")))
    {
        printf("open error\n");
        exit(1);
    }

    fscanf(f,"%d", &num);
    A = new int[num];
    B = new int[num];

    for (int i = 0; i < num;i++){
        fscanf(f,"%d", A + i);
        B[i] = A[i];
    }

    if(fclose(f)!=0) 
    {
    	printf("file closed error\n"); 
    	exit(1); 
    }

    clock_t start, finish;
    int time_sum1 = 0;
    int time_sum2 = 0;
    int time_sum3 = 0;
    printf("test %s\n��������������������������������������������������������������\n ", s);
    start = clock();
    for (int i = 0; i < times; i++)
    {
        qsort(A, num,sizeof(int),cmp);
        for (int i = 0; i < num;i++){
            A[i] = B[i];
        }
    }
    finish = clock();
    time_sum1 = finish - start;
    start = clock();
    for (int i = 0; i < times; i++)
    {
        Qsort(A,0,num);
        for (int i = 0; i < num;i++){
            A[i] = B[i];
        }
    }
    finish = clock();
    time_sum2 = finish - start;

    start = clock();
    for (int i = 0; i < times; i++)
    {
        merge_sort(A, num);
        
        for (int i = 0; i < num;i++){
            A[i] = B[i];
        }
    }
    finish = clock();
    time_sum3 = finish - start;
    printf("��������������������������������������������������������������\n");
    printf("qsort ����ʱ %d ms,ƽ����ʱ %f\n", time_sum1,(float)time_sum1/times);
    printf("Qsort ����ʱ %d ms,ƽ����ʱ %f\n", time_sum2,(float)time_sum2/times);
    printf("Mergesort ����ʱ %d ms,ƽ����ʱ %f\n", time_sum3,(float)time_sum3/times);
    printf("Qsort/sort  %f \n\n", (float)time_sum2/(float)time_sum1);
    

    delete A;
    delete B;
}

void merge_sort_recursive(int A[], int B[], int start, int end) {
    if (start >= end)
        return;
    int len = end - start, mid = (len >> 1) + start;
    int start1 = start, end1 = mid;
    int start2 = mid + 1, end2 = end;
    merge_sort_recursive(A, B, start1, end1);
    merge_sort_recursive(A, B, start2, end2);
    int k = start;
    while (start1 <= end1 && start2 <= end2)
        B[k++] = A[start1] < A[start2] ? A[start1++] : A[start2++];
    while (start1 <= end1)
        B[k++] = A[start1++];
    while (start2 <= end2)
        B[k++] = A[start2++];
    for (k = start; k <= end; k++)
        A[k] = B[k];
}
void merge_sort(int A[], const int len) {
    int B[len];
    merge_sort_recursive(A, B, 0, len - 1);
}


int cmp(const void *a,const void *b) {
	return *(int*)a-*(int*)b;
}