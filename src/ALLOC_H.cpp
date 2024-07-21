#include "../includes/global.h"
#include "../includes/prototype.h"

void ALLOC_H(){

    ht=(HAMILTONIAN*)calloc(Mmax+1,sizeof(HAMILTONIAN));
    for(int m=0;m<=Mmax;m++){
	int n=index_basis[m].Tot;
	ht[m].m=index_basis[m].m;
	ht[m].Nmax=index_basis[m].Nmax;
	ht[m].Tot=n;
	ht[m].dt=0.001;
	ht[m].h=(double *)calloc(n*n,sizeof(double));
	//ht[m].h=NULL;
    }

}
