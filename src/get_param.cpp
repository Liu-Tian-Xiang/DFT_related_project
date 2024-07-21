
#include "../includes/global.h"
#include "../includes/prototype.h"
int* get_param(int m,int i,int *p){
    p=(int *)calloc(4,sizeof(int));
    int tot=index_basis[m].Tot; 
    int up=i/tot+1;
    int down=i%tot;
    int n_1=1,n_2=1;
    p[0]=1;p[1]=1;p[2]=1;p[3]=1; 
    if(down==0){
        down=tot;
        up=up-1;
    } 
    if(up>1){ 
        while((find_A_index_basis(m,p[0],p[1])+1)<=up){
            if(up<=index_basis[m].Lmax[n_1-1]){
                p[0]=n_1;p[1]=up; 
                break; 
            } 
            up=up-index_basis[m].Lmax[n_1-1]; 
            n_1=n_1+1; 
        }
    }
    ///////////////////////////////////////////////////////////////////////////// 
    while((find_A_index_basis(m,p[2],p[3])+1)<=down){
        if(down<=index_basis[m].Lmax[n_2-1]){
            p[2]=n_2;p[3]=down; 
            break; 
        } 
        down=down-index_basis[m].Lmax[n_2-1]; 
        n_2=n_2+1; 
    }
    //printf("[%d]_[%d][%d][%d][%d]\n",i,p[0],p[1],p[2],p[3]); 
    return p;
}

