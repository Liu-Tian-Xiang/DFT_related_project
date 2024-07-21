
#include "../includes/global.h"
#include "../includes/prototype.h"
double kenetic(int i,int m,int n,int l){
    int tot=index_basis[m].Tot; 
    int up=i/tot+1;
    int down=i%tot;
    if(down==0){
	down=tot;
	up=up-1;
    }
    if(up==down){
	double temp=pow(bessel_zero[(n-1)*(Mmax+1)+m]/R_sys,2)+pow(l*PI/L_sys,2);
	return 0.5*temp;
    }
    return 0.0;
}
