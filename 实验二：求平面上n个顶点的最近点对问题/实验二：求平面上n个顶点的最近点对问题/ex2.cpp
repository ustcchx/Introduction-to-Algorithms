#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <cmath>
#include <ctime>
#include <ctime>
using namespace std;
#define N 11000
struct dot{
    float x,y;    
};
typedef struct dot dot;
float dist(dot a,dot b){
    return sqrt((a.x-b.x)*(a.x-b.x)+(a.y-b.y)*(a.y-b.y));
}
int cmp_x(const void *a,const void *b) {
	return (*(dot*)a).x-(*(dot*)b).x;
}
int cmp_y(const void *a,const void *b) {
	return (*(dot*)a).y-(*(dot*)b).y;
}
void sort_by_x(dot *dot_arr,int p,int r){
    qsort(dot_arr+p*sizeof(dot),r-p+1,sizeof(dot),cmp_x);
}
void sort_by_y(dot *dot_arr,int p,int r){
    qsort(dot_arr+p*sizeof(dot),r-p+1,sizeof(dot),cmp_y);
}
float min_dist(dot *dot_arr,dot *dot_arr_y,int p,int r,dot &min_dot_l,dot &min_dot_r){
    if(p==r) return 1e6;
    else if(r-p==1){
        min_dot_l=dot_arr[p],min_dot_r=dot_arr[r];
        if(dot_arr_y[p].y>dot_arr_y[r].y){
            dot temp=dot_arr_y[p];
            dot_arr_y[p]=dot_arr_y[r];
            dot_arr_y[r]=temp;
        }
        return dist(dot_arr[p],dot_arr[r]);
    }
    int mid=(p+r)/2;
    dot min_dot_l_1,min_dot_r_1,min_dot_l_2,min_dot_r_2;
    float l_min=min_dist(dot_arr,dot_arr_y,p,mid,min_dot_l_1,min_dot_r_1),r_min=min_dist(dot_arr,dot_arr_y,mid+1,r,min_dot_l_2,min_dot_r_2),min;
    if(l_min<=r_min) min=l_min,min_dot_l=min_dot_l_1,min_dot_r=min_dot_r_1;
    else min=r_min,min_dot_l=min_dot_l_2,min_dot_r=min_dot_r_2;
    float x_floor=dot_arr[mid].x-min;
    dot temp[N],temp_right[N/2];int temp_len=0,temp_right_len=0;
    float r_x_ceil=dot_arr[mid].x+min,r_x_floor=dot_arr[mid].x-min;
    int left_p=p,right_p=mid+1;
    while((left_p<=mid)&&(right_p<=r)){
        if(dot_arr_y[left_p].y<=dot_arr_y[right_p].y){
            temp[temp_len++]=dot_arr_y[left_p++];
            if(dot_arr_y[left_p-1].x>=r_x_floor) temp_right[temp_right_len++]=dot_arr_y[left_p-1];
            }
            else{
                temp[temp_len++]=dot_arr_y[right_p++];
                if(dot_arr_y[right_p-1].x<=r_x_ceil) temp_right[temp_right_len++]=dot_arr_y[right_p-1];
            }
    }
    if(left_p>mid){
        for(int i=right_p;i<=r;i++){
            temp[temp_len++]=dot_arr_y[i];
            if(dot_arr_y[i].x<=r_x_ceil&&dot_arr_y[i].x>=r_x_floor) temp_right[temp_right_len++]=dot_arr_y[i];  
        }  
    }
    else{
       for(int i=left_p;i<=mid;i++){
          temp[temp_len++]=dot_arr_y[i];
          if(dot_arr_y[i].x<=r_x_ceil&&dot_arr_y[i].x>=r_x_floor) temp_right[temp_right_len++]=dot_arr_y[i];
       }
}
    for(int i=0;i<temp_len;i++){
        dot_arr_y[p+i]=temp[i];
    }
    for(int i=0;i<temp_right_len;i++){
         for(int j=0;j<8&&i+j+1<temp_right_len;j++){
                float dist_=dist(temp_right[i],temp_right[i+j+1]);
                if(dist_<min){
                    min_dot_l=temp_right[i];
                    min_dot_r=temp_right[i+j+1];
                    min=dist_;
                }
            }
    }
    return min;
}

float min_dist_2(dot *a,int p,int r,dot &S1,dot &S2){
    float min_dist=1e6;
    for(int i=p;i<=r;i++){
        for(int j=i+1;j<=r;j++){
            float t=dist(a[i],a[j]);
            if(min_dist>t){
                S1=a[i],S2=a[j];
                min_dist=t;
            }
        }
    }
    return min_dist;
}
void get_in(dot *a){
    FILE *fp=fopen("data.txt","r+");
    int i=0,k;
    while(i<10000){
        fscanf(fp,"%d %f %f\n",&k,&a[i].x,&a[i].y);
        // if(abs(a[i].x)<1e10){
            // printf("%d %f %f\n",i,a[i].x,a[i].y);
            // break;
        // }
        i++;
    }
    fclose(fp);
}
int main(){
    srand((unsigned int)time(NULL));
    dot a[10000],b[10000];
    get_in(a);
    
    sort_by_x(a,0,9999);
    for(int i=0;i<10000;i++) b[i]=a[i];
    dot S1,S2,S3,S4;
    clock_t t1=clock();
    float dist1=min_dist(a,b,0,9999,S1,S2);
    clock_t t2=clock();
    float dist2=min_dist_2(a,0,9999,S3,S4);
    clock_t t3=clock();
    printf("S1:(%f %f) S2(%f %f) dis:%f time:%d\n",S1.x,S1.y,S2.x,S2.y,dist1,t2-t1);
    printf("S1:(%f %f) S2(%f %f) dis:%f time:%d\n",S3.x,S3.y,S4.x,S4.y,dist2,t3-t2);
}
