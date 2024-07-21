#include "../includes/global.h"
#include "../includes/prototype.h"
double expand(double r,double x,int m,int n_2,int l_2,string type){

    double retR=0;
    double retI=0;
    for(int n=1;n<=coulomb_expand_b_n;n++){
	for(int l=-coulomb_expand_b_l;l<=coulomb_expand_b_l;l++){
	    int key=(n-1)*(2*coulomb_expand_b_l+1)+l+coulomb_expand_b_l;
	    retR=retR
		+(Psi_1.Re_vxc_[key]*cos((l-l_2)*(x-0.5*L_sys)*PI/L_sys)-Psi_1.Im_vxc_[key]*sin((l-l_2)*(x-0.5*L_sys)*PI/L_sys))
		//+(Psi_1.Re_vxc_[key]*cos((l-l_2)*(x)*PI/L_sys)-Psi_1.Im_vxc_[key]*sin((l-l_2)*(x)*PI/L_sys))
		*bess(r,m,n)*bess(r,m,n_2);
	    retI=retI
		+(Psi_1.Re_vxc_[key]*sin((l-l_2)*(x-0.5*L_sys)*PI/L_sys)+Psi_1.Im_vxc_[key]*cos((l-l_2)*(x-0.5*L_sys)*PI/L_sys))
		//+(Psi_1.Re_vxc_[key]*sin((l-l_2)*(x)*PI/L_sys)+Psi_1.Im_vxc_[key]*cos((l-l_2)*(x)*PI/L_sys))
		*bess(r,m,n)*bess(r,m,n_2);
	}
    }
    if(type=="Im"){
	return (retI)*0.5*r/L_sys;
    }else if(type=="Re"){
	return (retR)*0.5*r/L_sys;
    }
    return 0;
}


