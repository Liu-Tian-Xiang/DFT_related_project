#include "../includes/global.h"
#include "../includes/prototype.h"
void print_m_eig(int e_m,double *w){
   int n=index_basis[e_m].Tot; 
    for(int i=0;i<n;i++){
        printf("Psi[%d].Tot-eig=%1.3e\n",i,w[i]);
    }printf("______%d__end______________________________________________\n",e_m);
}
