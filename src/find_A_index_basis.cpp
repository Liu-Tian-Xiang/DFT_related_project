#include "../includes/global.h"
#include "../includes/prototype.h"
int find_A_index_basis(int m,int n,int l){
     int A_temp=0;
          for(int n_temp=0;n_temp<n-1;n_temp++){
               A_temp=A_temp+index_basis[m].Lmax[n_temp];
          }
     return A_temp+abs(l)-1;
}

