#include <stdio.h>
int m[7][7]={0};
int c[7][7]={0};
int fun(int *p,int i,int j){
    if(i==j){
        return 0;
    }
    m[i][j]=-1e6;
    for(int k=i;k<j;k++){
        int q=fun(p,i,k)+fun(p,k+1,j)+p[i-1]*p[k]*p[j];
        if(m[i][j]<q){
            m[i][j]=q;
            c[i][j]=k;
        }
    }
    return m[i][j];
}   
int main(){
    int p[7]={5,10,3,12,5,50,6};
    fun(p,1,6);
    for(int i=1;i<7;i++){
        for(int j=1;j<7;j++){
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }
}
