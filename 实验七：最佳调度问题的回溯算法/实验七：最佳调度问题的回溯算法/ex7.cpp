// #pragma GCC optimize(3,"Ofast","inline")
#include <cstdio>
#include <stdlib.h> 
#include <chrono>
#include <iostream>
using namespace std;
struct pair_{
    int i;
    int weight;
};
typedef struct pair_ pair_;
int cmp_2(const void *a, const void *b){
    return ((pair_*) b)->weight-((pair_*) a)->weight;
}
int cmp(const void *a, const void *b){
    return *((int*) b)-*((int*) a);
}

void dfs(int *solution,int *good_solution,int *weight,int *all_time,int m,int k,int n,int &temp_min){
    while(true){
        if(m==-1) break;
        else if(m>=n){
            m=m-1;
            int temp_max_time=0;
            for(int i=0;i<k;i++)   if(temp_max_time<all_time[i]) temp_max_time=all_time[i];
            if(temp_max_time<temp_min){
                temp_min=temp_max_time;
                for(int i=0;i<n;i++){
                    good_solution[i]=solution[i];
                }
            }
        }
        int flag=0;
        do{ 
            flag=0;
            solution[m]++;
            if(solution[m]>k) break;
            for(int i=0;i<solution[m];i++){
                if(all_time[i]==all_time[solution[m]]){
                    flag=1;break;
                }
            }
            if(solution[m]-2>=0) all_time[solution[m]-2]-=weight[m];
            all_time[solution[m]-1]+=weight[m];
        }while(all_time[solution[m]-1]>temp_min||flag);
        if(solution[m]>k){
            all_time[k-1]-=weight[m];
            solution[m]=0;
            m=m-1;
            continue;
        }
        else{
            m++;
            continue;
        }
    }
}
int main(){
    char f_name[20];
    int n,k;
    cin >> f_name;
    FILE *fp=fopen(f_name,"r+");
    fscanf(fp,"%d %d\n",&n,&k);
    chrono::system_clock::time_point start_time = std::chrono::system_clock::now();  
    int temp_weight[n];
    pair_ weight[n];
    for(int i=0;i<n;i++){
        fscanf(fp,"%d ",&temp_weight[i]);
        weight[i].weight=temp_weight[i];
        weight[i].i=i;
    }
    int solution[n];
    qsort(temp_weight,n,sizeof(int),cmp);
    qsort(weight,n,sizeof(pair_),cmp_2);
    // 先贪心给出一个解
    int r=k,flag=1;
    for(int i=0;i<n;i++){
        if(flag) solution[i]=r--;
        else solution[i]=r++;
        if(r==1 || r==k){
            if(r==1) solution[++i]=1;
            else solution[++i]=k;
            flag=1-flag;
        }
    }
    int all_time[k]={0};
    for(int i=0;i<n;i++){
        all_time[solution[i]-1]+=temp_weight[i];
    }
    int temp_max_time=0;
    for(int i=0;i<k;i++)   if(temp_max_time<all_time[i]) temp_max_time=all_time[i];
    int _all_time[k]={0},_solution[n]={0},good_solution[n]={0};
    dfs(_solution,good_solution,temp_weight,_all_time,0,k,n,temp_max_time);
    printf("total time: %d\n",temp_max_time);
    for(int s=0;s<k;s++){
        int sum_=0;
        printf("machine%d solution: ",s+1);
        for(int i=0;i<n;i++){
            if(good_solution[i]-1==s){
                sum_+=temp_weight[i];
                printf("%d ",weight[i].i+1);
            }
        }
        printf("\n");
        // printf("::%d\n",sum_);
    }
    chrono::system_clock::time_point end_time = std::chrono::system_clock::now(); 
    std::chrono::duration<double> duration = end_time - start_time;  
    double duration_ms = duration.count() * 1000;   
    cout << "time: " << duration_ms << " ms" << std::endl; 
    
    
}
