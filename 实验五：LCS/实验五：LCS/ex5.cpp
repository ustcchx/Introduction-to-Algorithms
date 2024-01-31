#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 1000
void LCS_1(int m,int n,char *p,char *q){
    int temp[m+1][n+1];//n<=m
    for(int i=0;i<=n;i++) temp[0][i]=0;
    for(int i=0;i<=m;i++) temp[i][0]=0;
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(p[i]==q[j]) temp[i][j]=temp[i-1][j-1]+1;
            else temp[i][j]=(temp[i-1][j]>temp[i][j-1])?temp[i-1][j]:temp[i][j-1];
        }
    }
    if(temp[m][n]==0){
        printf("NULL\n");
        return;
    }
    else{
        printf("%d\n",temp[m][n]);
        char s[N];int x=m,y=n,s_len=0;
        while(x&&y){
            if(p[x]==q[y]) s[s_len++]=q[y],x--,y--;
            else if(temp[x][y-1]>=temp[x-1][y]) y--;
            else x--;
        }
        printf("LCS1: ");
        for(int i=s_len-1;i>=0;i--) printf("%c ",s[i]);
        printf("\n");
    }
    printf("\n");
}
void LCS_2(int m,int n,char *p,char *q){
    int temp1[n+1]={0},temp2[n+1]={0};//n<=m
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(p[i]==q[j]) temp1[j]=temp2[j-1]+1;
            else temp1[j]=(temp1[j-1]>temp2[j])?temp1[j-1]:temp2[j];
        }
        for(int k=1;k<=n;k++) temp2[k]=temp1[k];
    }
    if(temp1[n]==0){
        printf("NULL\n");
        return;
    }
    else printf("LCS2: %d\n",temp1[n]);
    printf("\n");
}
void LCS_3(int m,int n,char *p,char *q){
    int temp[n+1]={0},s=0;//n<=m
    for(int i=1;i<=m;i++){
        for(int j=1;j<=n;j++){
            if(p[i]==q[j]) temp[j]=s+1;
            else{
                s=temp[j];
                temp[j]=(temp[j-1]>temp[j])?temp[j-1]:temp[j];
            }
        }
    }
    if(temp[n]==0){
        printf("NULL\n");
        return;
    }
    else printf("LCS3: %d\n",temp[n]);
    printf("\n");
}
int main(){
    char q[N],p[N];
    FILE *fp=fopen("data.txt","r+");
    fscanf(fp,"%s",q);
    fscanf(fp,"%s",p);
    if(strlen(p)<=strlen(q)){
        LCS_1(strlen(q),strlen(p),q,p);
        LCS_2(strlen(q),strlen(p),q,p);
        LCS_3(strlen(q),strlen(p),q,p);
    }
    else{
        LCS_1(strlen(p),strlen(q),p,q);
        LCS_2(strlen(p),strlen(q),p,q);
        LCS_3(strlen(p),strlen(q),p,q);
    }
    
}