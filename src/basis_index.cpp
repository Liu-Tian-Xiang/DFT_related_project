#include "../includes/global.h"
#include "../includes/prototype.h"
void basis_index(int m){
    int l,tot,n;
    double En=0,El,El1;
    index_basis[m].m=m;
    El1=pow(PI/L_sys,2);
    n=0;
    while(En<(Ec*Ef0-El1))
    {
        n+=1;
        En=pow(gsl_sf_bessel_zero_Jnu(m,n)/R_sys,2);
    }

    index_basis[m].Nmax=n-1;
    index_basis[m].Lmax=(int*)malloc((n-1)*sizeof(int));
    tot=0;
    for(n=1;n<=index_basis[m].Nmax;n++){
        l=0;En=pow(gsl_sf_bessel_zero_Jnu(m,n)/R_sys,2);
        El1=0;
        while(El1<(Ec*Ef0-En))
        {
            l+=1;
            El1=pow(l*PI/L_sys,2);
            tot+=1;
        }
        tot-=1;
        index_basis[m].Lmax[n-1]=l-1;
    }
    index_basis[m].Tot=tot;
}

