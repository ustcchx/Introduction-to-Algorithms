#include <cstdio>
#include <iostream>
using namespace std;
struct TNode{
    bool color; //0红，1黑
    int max;
    int int_low;
    int int_high;
    struct TNode *L,*R,*p;
};
TNode *Head;
typedef struct TNode TNode;
void LEFT_ro(TNode *p){
    if(p->p!=NULL){
        if(p->p->L==p) p->p->L=p->R;
        else p->p->R=p->R;
    }
    else{
        Head=p->R;
    }
    int a1=((p->R->L==NULL)?(-1e3):(p->R->L->max));
    int a2=(p->L==NULL)?(-1e3):(p->L->max);
    int a3=(p->R->R==NULL)?(-1e3):(p->R->R->max);
    p->max=max(max(a1,a2),p->int_high);
    p->R->max=max(max(p->max,p->R->int_high),a3);
    TNode *temp=p->R->L;
    p->R->p=p->p;
    p->R->L=p;
    p->p=p->R;
    p->R=temp;
    if(temp) temp->p=p;
}
void RIGHT_ro(TNode *p){
    if(p->p!=NULL){
        if(p->p->L==p) p->p->L=p->L;
        else p->p->R=p->L;
    }
    else{
        Head=p->L;
    }
    int a1=((p->L->R==NULL)?(-1e3):(p->L->R->max));
    int a2=(p->R==NULL)?(-1e3):(p->R->max);
    int a3=(p->L->L==NULL)?(-1e3):(p->L->L->max);
    p->max=max(max(a1,a2),p->int_high);
    p->L->max=max(max(p->max,p->L->int_high),a3);
    
    TNode *temp=p->L->R;
    p->L->R=p;
    p->L->p=p->p;
    p->p=p->L;
    p->L=temp;
    if(temp) temp->p=p;
}
void RB_insert_fixup(TNode *z){
    while(z->p->color==0){
        if(z->p->p->L==z->p){
            TNode *y=z->p->p->R;
            if(y!=NULL&&y->color==0){
                z->p->color=1;
                y->color=1;
                z->p->p->color=0;
                z=z->p->p;
            }
            else if(z==z->p->R){
                z=z->p;
                LEFT_ro(z);
            }
            else{
                z->p->color=1;
                z->p->p->color=0;
                RIGHT_ro(z->p->p);
            }
            
        }
        else{
            TNode *y=z->p->p->L;
            if(y!=NULL&&y->color==0){
                z->p->color=1;
                y->color=1;
                z->p->p->color=0;
                z=z->p->p;
            }
            else if(z==z->p->L){
                z=z->p;
                RIGHT_ro(z);
            }
            else{
                z->p->color=1;
                z->p->p->color=0;
                LEFT_ro(z->p->p);
            }
        }
        Head->color=1;
        if(z==Head) break;
    }
    
}
void RB_insert(TNode *z){
    TNode *p=Head,*pre;
    while(true){
        if(z->int_low<=p->int_low) pre=p,p=p->L;
        else pre=p,p=p->R;
        if(z->max>pre->max) pre->max=z->max; 
        if(p==NULL){
            if((pre->int_low)>=(z->int_low)) {pre->L=z;}
            else {pre->R=z;}
            z->L=NULL,z->R=NULL,z->p=pre;
            break;
        }
    }
    RB_insert_fixup(z);
}
void RB_search(TNode *z,TNode *Head_,int &flag){
    TNode *p=Head_;
    if(!p){
        // printf("nil\n");
        return ;
    } 
    if(!((p->int_low>z->int_high)||(p->int_high<z->int_low))){
        printf("[%d %d], ",p->int_low,p->int_high);
        flag=1;
        RB_search(z,p->L,flag);
        RB_search(z,p->R,flag);
    }
    
    else if(p->int_low>z->int_high){
        int a1=(p->L==NULL)?-1e3:p->L->max;
        int a2=(p->R==NULL)?-1e3:p->R->max;
        if(!(p->L)) return;
        // printf("nil\n");
        if(z->int_low>a1) return ;
        else RB_search(z,p->L,flag); 
        return;
    }
    else if(p->int_high<z->int_low){
        int a1=(p->L==NULL)?-1e3:p->L->max;
        int a2=(p->R==NULL)?-1e3:p->R->max;
        if(a1>=z->int_low) RB_search(z,p->L,flag);
        if(a2>=z->int_low) RB_search(z,p->R,flag);
        
        return ;
    }
    // if(p->L&&p->L->max>=z->max){
    //     RB_search(z,p->L,flag);
    // }
    // if(p->R&&p->R->max>=z->max){
    //     if(z->int_low<p->int_low) return;
    //     else RB_search(z,p->R,flag);
    // }
    // printf("nil\n");
    return;
}
void LNR(TNode *p){
    if(p==NULL) return;
    LNR(p->L);
    printf("%d,%d,%d\n",p->int_low,p->int_high,p->max);
    LNR(p->R);
}
int main(){
    TNode *p;
    int N;
    FILE *fp=fopen("insert.txt","r+");
    fscanf(fp,"%d\n",&N);
    p=(TNode *)malloc(sizeof(TNode)*(2*N));
    for(int i=0;i<N;i++){
        fscanf(fp,"%d %d",&p[i].int_low,&p[i].int_high);
        p[i].max=p[i].int_high;
        p[i].color=0;
    }
    Head=&p[0];
    Head->color=1,Head->L=NULL,Head->R=NULL,Head->p=NULL;
    Head->max=Head->int_high;
    for(int i=1;i<N;i++) RB_insert(&p[i]);
    // LNR(Head);
    while(true){
        TNode *p;
        cin >> p->int_low >> p->int_high;
        p->max=p->int_high;
        if(p->int_low>p->int_high){
            printf("input wrong\n");
            continue;
        }  
        int flag=0;
        RB_search(p,Head,flag);
        if(flag==0){
            printf("nil");
        }
        printf("\n");
    }
}