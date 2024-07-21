#include "../includes/global.h"
#include "../includes/prototype.h"
double Coulomb_potential(double r,double x){
    double result=0.0;
    for(int n=1;n<=coulomb_expand_b_n;n++){
	for(int l=-coulomb_expand_b_l;l<=coulomb_expand_b_l;l++){
	    int key=(n-1)*(2*coulomb_expand_b_l+1)+l+coulomb_expand_b_l;
	    result=result+bess(r,0,n)*(
		    (Psi_1.Re_b_[key])
		    *cos(l*(x-L_sys*0.5)*PI/L_sys)
		    -(Psi_1.Im_b_[key])
		    *sin(l*(x-L_sys*0.5)*PI/L_sys)
		    )/(pow((bessel_zero[(n-1)*(Mmax+1)]/R_sys),2.0)+pow((l*PI/L_sys),2.0));
	}
    }
    return 1e-3*V_divide*E_divide*result/L_sys;
}

