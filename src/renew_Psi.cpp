

#include "../includes/global.h"
#include "../includes/prototype.h"
int renew_Psi(int m,double *w,double *z,int flag){
    int n=index_basis[m].Tot;
    int Eselect=min(occupied_electrons,n);

//    if(Psi_f[occupied_electrons-1].eig>=w[0]){bak_psi(flag);}else{return -flag;}

    for(int nl_1=0;nl_1<Eselect;nl_1++){
	if(flag<occupied_electrons){ 
	    //---------------------------------------------------- 
	    Psi_1.wf[flag].m=m;
	    Psi_1.wf[flag].eig=w[nl_1];
	    Psi_1.wf[flag].A_nl=(double*)calloc(n,sizeof(double));
	    for(int nl_2=0;nl_2<n;nl_2++){
		Psi_1.wf[flag].A_nl[nl_2]=(fabs(z[nl_1*n+nl_2])>1e-5?z[nl_1*n+nl_2]:0);
	    }                        
	    flag=flag+1; 
	    if(flag==occupied_electrons){Arrange_Psi();} 
	}else{
	    for(int i=0;(Psi_1.wf[occupied_electrons-i-1].eig>=w[nl_1+i] & i<Eselect & nl_1+i<Eselect);i++){
		//---------------------------------------------------- 
		Psi_1.wf[occupied_electrons-i-1].m=m;
		Psi_1.wf[occupied_electrons-i-1].eig=w[nl_1+i];
		free(Psi_1.wf[occupied_electrons-i-1].A_nl);
		Psi_1.wf[occupied_electrons-i-1].A_nl=(double*)calloc(n,sizeof(double));
		for(int nl_2=0;nl_2<n;nl_2++){
		    Psi_1.wf[occupied_electrons-i-1].A_nl[nl_2]=(fabs(z[n*(nl_1+i)+nl_2])>1e-5?z[n*(nl_1+i)+nl_2]:0.0);
		}
	    }
	    Arrange_Psi();
	    break;
	}
    }
    return flag;
}
