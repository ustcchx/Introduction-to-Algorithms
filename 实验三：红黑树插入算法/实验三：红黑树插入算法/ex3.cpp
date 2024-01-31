#include <cstdio>
#include <iostream>
using namespace std;
struct TNode{
    bool color; //0红，1黑
    int key;
    struct TNode *L,*R,*p;
};
TNode *Head;
typedef struct TNode TNode;
void LNR(TNode *p,FILE *fp){
    if(p==NULL) return;
    LNR(p->L,fp);
    if(p->color==0) fprintf(fp,"%d,红\n",p->key);
    else fprintf(fp,"%d,黑\n",p->key);
    LNR(p->R,fp);
}
void NLR(TNode *p,FILE *fp){
    if(p==NULL) return;
    if(p->color==0) fprintf(fp,"%d,红\n",p->key);
    else fprintf(fp,"%d,黑\n",p->key);
    NLR(p->L,fp);
    NLR(p->R,fp);
}
void LOT(int N,FILE *fp){
    TNode *q=(TNode *)malloc(sizeof(TNode)*N);
    int q_len=1;
    q[0]=*Head;
    do{ 
        if(q[0].color==0) fprintf(fp,"%d,红\n",q[0].key);
        else fprintf(fp,"%d,黑\n",q[0].key);
        // if(q[0].L) printf("L: %d  ",q[0].L->key);
        // if(q[0].R) printf("R: %d  ",q[0].R->key);
        // if(q[0].p) printf("p: %d  ",q[0].p->key);
        // printf("\n");
        TNode s=q[0];
        for(int i=0;i<=q_len-2;i++){
            q[i]=q[i+1];
        }
        q_len--;
        if(s.L!=NULL) q[q_len++]=*(s.L);
        if(s.R!=NULL) q[q_len++]=*(s.R);
    }while(q_len);
}
void LEFT_ro(TNode *p){
    if(p->p!=NULL){
        if(p->p->L==p) p->p->L=p->R;
        else p->p->R=p->R;
    }
    else{
        Head=p->R;
    }
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
                printf("1 ");
            }
            else if(z==z->p->R){
                z=z->p;
                LEFT_ro(z);
                printf("2 ");
            }
            else{
                z->p->color=1;
                z->p->p->color=0;
                RIGHT_ro(z->p->p);
                printf("3 ");
            }
            
        }
        else{
            TNode *y=z->p->p->L;
            if(y!=NULL&&y->color==0){
                z->p->color=1;
                y->color=1;
                z->p->p->color=0;
                z=z->p->p;
                printf("4 ");
            }
            else if(z==z->p->L){
                z=z->p;
                RIGHT_ro(z);
                printf("5 ");
            }
            else{
                z->p->color=1;
                z->p->p->color=0;
                LEFT_ro(z->p->p);
                printf("6 ");
            }
        }
        Head->color=1;
        if(z==Head) break;
    }
    
}
void RB_insert(TNode *z){
    TNode *p=Head,*pre;
    while(true){
        if(z->key<=p->key) pre=p,p=p->L;
        else pre=p,p=p->R;
        if(p==NULL){
            if((pre->key)>=(z->key)) {pre->L=z;}
            else {pre->R=z;}
            z->L=NULL,z->R=NULL,z->p=pre;
            break;
        }
    }
    RB_insert_fixup(z);
}
int main(){
    TNode *p;
    int N;
    FILE *fp=fopen("insert.txt","r+");
    FILE *p1=fopen("LOT.txt","r+");
    FILE *p2=fopen("LNR.txt","r+");
    FILE *p3=fopen("NLR.txt","r+");
    fscanf(fp,"%d\n",&N);
    p=(TNode *)malloc(sizeof(TNode)*(2*N));
    for(int i=0;i<N;i++){
        fscanf(fp,"%d ",&p[i].key);
        p[i].color=0;
    }
    Head=&p[0];
    Head->color=1,Head->L=NULL,Head->R=NULL,Head->p=NULL;
    for(int i=1;i<N;i++) RB_insert(&p[i]);
    LOT(N+1,p1);
    LNR(Head,p2);
    NLR(Head,p3);
}