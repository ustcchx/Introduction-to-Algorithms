// #pragma GCC optimize(2)
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <time.h>
using namespace std;
int S=0;
void swap_1(int *a,int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}
int cmp(const void *a,const void *b) {
	return *(int*)a-*(int*)b;
}
int mid_three(int *a,int l,int m,int n){
    if(*(a+m)>=*(a+n)){
        if(*(a+l)>=*(a+m)) return m;
        else if(*(a+l)>=*(a+n)) return l;
        else return n;
    }
    else if(*(a+l)>=*(a+n)) return n;
    else if(*(a+l)>=*(a+m)) return l;
    else return m; 
}
int partition_1(int *a,int p,int r){
    if(p==r) return p;
    int i=p-1;
    for(int *tp=a+p;tp<a+r;++tp){
        if(*tp<*(a+r)){
            swap_1(a+(++i),tp);
        }
    }
    swap_1(a+r,a+(++i));
    return i;
}//固定基准
int partition_2(int *a,int p,int r){
    if(p==r) return p;
    int s=rand()%(r-p+1)+p;
    int i=p-1;
    swap_1(a+s,a+r);
    for(int *tp=a+p;tp<a+r;++tp){
        if(*tp<*(a+r)){
            swap_1(a+(++i),tp);
        }
    }
    swap_1(a+r,a+(++i));
    return i;
}//随机基准
int partition_3(int *a,int p,int r){
    int s=mid_three(a,p,r,(r+p)>>1);
    int i=p-1;
    swap_1(a+s,a+r);
    for(int *tp=a+p;tp<a+r;++tp){
        if(*tp<*(a+r)){
            swap_1(a+(++i),tp);
        }
    }
    swap_1(a+r,a+(++i));
    return i;
}//取中基准
void qsort_1(int *a,int p,int r){
    if(p>=r) return;
    int q=partition_1(a,p,r);
    qsort_1(a,p,q-1);
    qsort_1(a,q+1,r);
}//固定基准
void qsort_2(int *a,int p,int r){
    if(p>=r) return;
    int q=partition_2(a,p,r);
    qsort_2(a,p,q-1);
    qsort_2(a,q+1,r);
}//随机基准
void qsort_3(int *a,int p,int r){
    if(p>=r) return;
    int q=partition_3(a,p,r);
    qsort_3(a,p,q-1);
    qsort_3(a,q+1,r);
}//随机取中基准
void insert_sort(int *a,int p,int r){
    for(int i=p+1;i<=r;++i){
        for(int *tp=a+i-1;tp>=a+p;--tp){
            if(*(tp+1)<*tp) swap_1(tp+1,tp);
            else break;
        }
    }
}//几乎有序情况
void qsort_4(int *a,int p,int r,int k){
    if(r-p+1<=k){
        insert_sort(a,p,r);
        return;
    }
    int q=partition_3(a,p,r);
    qsort_4(a,p,q-1,k);
    qsort_4(a,q+1,r,k);
}//几乎有序情况+三数取中
void partition_4(int *a,int p,int r,int &left,int &right){
    int *ip=a+p-1,*jp=a+p,*tp=a+r-1;
    for(;jp<=tp;jp++){
        if(*jp<a[r]){
            swap_1(++ip,jp);
        }
        else if(*jp==a[r]){
            swap_1(tp--,jp--);
        }
    }
    left=ip-a;
    for(tp=tp+1;tp<=a+r;tp++){
        swap_1(tp,++ip);
    }
    right=ip-a+1;
}//选做
void qsort_5(int *a,int p,int r){
    if(p>=r) return;
    int left,right;
    partition_4(a,p,r,left,right);
    qsort_5(a,p,left);
    qsort_5(a,right,r);
}//选做
void print_all(int *a,int len){
    FILE *fp=fopen("print_data.txt","w+");
    for(int i=0;i<len;i++) fprintf(fp,"%d ",a[i]);
    fclose(fp);
}
void partition_5(int *a,int p,int r,int *left,int *right){
    int s=mid_three(a,p,r,(r+p)>>1);
    swap_1(a+s,a+r);
    int *ip=a+p-1,*jp=ip+1,*tp=a+r-1;
    for(;jp<=tp;++jp){
        if(*jp<*(a+r)){
            swap_1(++ip,jp);
        }
        else if(*jp==*(a+r)){
            swap_1(tp--,jp--);
        }
    }
    *left=ip-a;
    for(tp=tp+1;tp<=a+r;++tp){
        swap_1(tp,++ip);
    }
    *right=ip-a+1;
}//聚集+三数取中+插排优化
void qsort_6(int *a,int p,int r,int k){
    if(r-p+1<=k){
        insert_sort(a,p,r);
        return;
    }
    int left,right;
    partition_5(a,p,r,&left,&right);
    qsort_6(a,p,left,k);
    qsort_6(a,right,r,k);
}//聚集+三数取中+插排优化
int main(){
    srand((unsigned)time(NULL));
    int N;
    int sum_clock=0,time=0;
    FILE *fp=fopen("data.txt","r+");
    fscanf(fp,"%d",&N);
    int *a=(int *)malloc(sizeof(int)*N);
    int *b=(int *)malloc(sizeof(int)*N);
    for(int i=0;i<N;i++) fscanf(fp,"%d",&a[i]);
    while(time<1){
        for(int i=0;i<N;i++) b[i]=a[i];
        clock_t start,end;
        start=clock();
        // qsort_1(b,0,N-1);
        // qsort_2(b,0,N-1);
        // qsort_3(b,0,N-1);
        // qsort_4(b,0,N-1,19);
        // qsort_5(b,0,N-1);
        //  qsort_6(b,0,N-1,19);
    //    qsort(b, N, sizeof(int), cmp);
        // sort(b,b+N);
        insert_sort(b,0,N-1);
        end=clock();
        print_all(b,N);
        sum_clock+=end-start;
        time++;
    }
    printf("%f",static_cast<double>(sum_clock)/CLOCKS_PER_SEC*1000);
}
