#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>  
#include <map>
#include <chrono>
#define N 81306
#define N1 9
using namespace std;
struct arc{
    struct arc* next;
    int next_node;
};
struct node{
    struct arc *first_arc;
};
typedef struct arc arc;
typedef struct node node;
map<int,int> dict;
node nodes[N];
int flag[N]={0};
void read_data(){
    FILE *fp=fopen("twitter_small.txt","r+");
    int len=0;
    while(!feof(fp)){
        int s,d;
        fscanf(fp,"%d %d\n",&s,&d);
        arc *temp_arc=(arc *)malloc(sizeof(arc));
        // cout << s <<  ' ' << d <<endl;
        auto it_1=dict.find(s);
        if(it_1==dict.end()) dict[s]=len++;
        auto it_2=dict.find(d);
        if(it_2==dict.end()) dict[d]=len++; 
        temp_arc->next_node=dict[d];
        temp_arc->next=NULL;     
        if(nodes[dict[s]].first_arc==NULL){
            nodes[dict[s]].first_arc=temp_arc;
        }
        else{
            temp_arc->next=nodes[dict[s]].first_arc;
            nodes[dict[s]].first_arc=temp_arc;
        }
    }
    cout << len <<endl;
    fclose(fp);
}
int matrix[N1][N1]={0};
map<char,int> dict_1;
int flag_1[N1]={0};
void read_data_1(){
    FILE *fp=fopen("data.txt","r+");
    char s[30];
    fscanf(fp,"%s\n",s);
    // cout << s;
    int len=0;
    while(!feof(fp)){
        char s,d;
        fscanf(fp,"%c-%c\n",&s,&d);
        auto it_1=dict_1.find(s);
        if(it_1==dict_1.end()) dict_1[s]=len++;
        auto it_2=dict_1.find(d);
        if(it_2==dict_1.end()) dict_1[d]=len++; 
        matrix[dict_1[s]][dict_1[d]]=1;
        matrix[dict_1[d]][dict_1[s]]=1;
    }
    for(int i=0;i<N1;i++){
        for(int j=0;j<N1;j++){
            printf("%d ",matrix[i][j]);
        }
        printf("\n");
    }
}
void BFS_matrix(int start,int &time){
    queue<int> q;
    q.push(start);
    flag_1[start]=1;
    while(!q.empty()){
        int temp=q.front();
        time++;
        // cout << time<< ' '<<temp<< endl;
        q.pop();
        int p=0;
        while(p<N1){
            if(matrix[temp][p]==1){
                if(flag_1[p]!=1){
                    flag_1[p]=1;
                    q.push(p);
                }
            }
            p++;
        }
    }
}
void BFS_matrix_all(int &time){
    for(int i=0;i<N1;i++){
        if(flag_1[i]==1) continue;
        else BFS_matrix(i,time);
    }
}
void BFS(int start,int &time){
    queue<node> q;
    q.push(nodes[start]);
    flag[start]=1;
    while(!q.empty()){
        node temp=q.front();
        q.pop();
        arc *p=temp.first_arc;
        time++;
        while(p){
            if(flag[p->next_node]==1) p=p->next;
            else{
                flag[p->next_node]=1;
                q.push(nodes[p->next_node]);
            }
        }
    }
}
void BFS_all(int &time){
    for(int i=0;i<N;i++){
        if(flag[i]==1) continue;
        else BFS(i,time);
    }
}
int main(){
    chrono::system_clock::time_point start_time = std::chrono::system_clock::now();  
    int time=0;
    read_data();
    BFS_all(time);
    cout <<time <<endl;
    chrono::system_clock::time_point end_time = std::chrono::system_clock::now(); 
    std::chrono::duration<double> duration = end_time - start_time;  
    double duration_ms = duration.count() * 1000;   
    cout << "time: " << duration_ms << " ms" << std::endl; 

    chrono::system_clock::time_point start_time_1 = std::chrono::system_clock::now();  
    int time1=0;
    read_data_1();
    BFS_matrix_all(time1);
    cout << time1 <<endl;
    chrono::system_clock::time_point end_time_1 = std::chrono::system_clock::now(); 
    std::chrono::duration<double> duration_1 = end_time_1 - start_time_1;  
    double duration_ms_1 = duration_1.count() * 1000;   
    cout << "time: " << duration_ms_1 << " ms" << std::endl; 
    return 0;
}