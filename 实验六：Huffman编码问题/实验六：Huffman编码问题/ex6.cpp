#include <cstdio>
#include <queue>
#include <iostream>
using namespace std;
#define N 1000;
struct node{
    int fre,pos;
    int par,lch,rch;
    char code[50];
    int code_len;
};
struct tmp{
    bool operator() (node a,node b){
        return a.fre>b.fre;
    }
};
typedef struct node node;
priority_queue<node, vector<node>, tmp> q;
node fre_char[187];
void get_fre_char(){
    for(int i=0;i<187;i++){
        fre_char[i].fre=0;
        fre_char[i].lch=-1;
        fre_char[i].rch=-1;
        fre_char[i].par=-1;
        fre_char[i].pos=i;
        fre_char[i].code_len=0;
    }
    FILE *fp=fopen("orignal.txt","r+");
    while(true){
        char s;
        fscanf(fp,"%c ",&s);
        if(feof(fp)){
            break;
        }
        fre_char[(int)(s-33)].fre+=1;
    }
    for(int i=0;i<94;i++){
        q.push(fre_char[i]);
    }
}
void get_h_tree(){
    int pos_i=94;
    while(true){
        node min1=q.top();
        q.pop();
        node min2=q.top();
        q.pop();
        fre_char[min1.pos].par=pos_i;
        fre_char[min2.pos].par=pos_i;
        fre_char[pos_i].lch=min1.pos;
        fre_char[pos_i].rch=min2.pos;
        node temp;
        temp.fre=min1.fre+min2.fre;
        temp.pos=pos_i++;
        q.push(temp);
        if(q.size()==1) break;
    }
}
void get_code(){
    for(int i=0;i<94;i++){
        int p=i;
        while(p!=186){
            if(fre_char[fre_char[p].par].lch==p) fre_char[i].code[fre_char[i].code_len++]='0';
            else fre_char[i].code[fre_char[i].code_len++]='1';
            p=fre_char[p].par;
        }
        for(int i=0;i<=fre_char[i].code_len/2;i++){
            char temp=fre_char[i].code[i];
            fre_char[i].code[i]=fre_char[i].code[fre_char[i].code_len-i-1];
            fre_char[i].code[fre_char[i].code_len-i-1]=temp;
        }
    }
}
int main(){
    get_fre_char();
    get_h_tree();
    get_code();
    FILE *fp=fopen("table.txt","r+");
    for(int i=0;i<94;i++){
        char temp=char(fre_char[i].pos+33);
        fprintf(fp,"%c  %d  %s\n",temp,fre_char[i].fre,fre_char[i].code);
        // cout << char(fre_char[i].pos+33) << ":" << fre_char[i].fre << ' ';
        // cout << fre_char[i].code << endl;
    }
    float sum=0.0,orin_sum=0.0;
    for(int i=0;i<94;i++) sum+=fre_char[i].code_len*fre_char[i].fre,orin_sum+=7*fre_char[i].fre;
    cout <<  "\ncompress_rate:" << sum/orin_sum;
    return 0;
}