#include "../includes/global.h"
#include "../includes/prototype.h"
double rho_test(double r,double x){
   int number=occupied_electrons;
   double rho=0.0;
    for(int i=0;i<number;i++){ 
        int m=Psi_1.wf[i].m; 
        int Nmax=index_basis[m].Nmax;
        int Ind1=0;                                 
        double rho_temp=0.0;
        for(int n_1=1;n_1<=Nmax;n_1++){
            for(int l_1=1;l_1<=index_basis[m].Lmax[n_1-1];l_1++){
                int Ind2=0;
                for(int n_2=1;n_2<=Nmax;n_2++){
                    for(int l_2=1;l_2<=index_basis[m].Lmax[n_2-1];l_2++){
                        rho_temp=rho_temp+
                            Psi_1.wf[i].A_nl[Ind1]*
                            Psi_1.wf[i].A_nl[Ind2]*
                            bess(r,m,n_1)*bess(r,m,n_2)*
                            sin(x*PI*l_1/L_sys)*
                            sin(x*PI*l_2/L_sys);
                        Ind2=Ind2+1;
                    }
                }
                Ind1=Ind1+1;
            }
        }
        if(m!=0 & i!=number-1){rho=rho+rho_temp*2.0;number=number-1;}else{rho=rho+rho_temp;}
    }
    return 2*rho/(PI*L_sys);
}

