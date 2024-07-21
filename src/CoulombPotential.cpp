#include "../includes/global.h"
#include "../includes/prototype.h"
double Wave_function::CoulombPotential(double r,double x){
    double result=0.0;
    for(int n=1;n<=coulomb_expand_b_n;n++){
	for(int l=-coulomb_expand_b_l;l<=coulomb_expand_b_l;l++){
	    int key=(n-1)*(2*coulomb_expand_b_l+1)+l+coulomb_expand_b_l;
	    result=result+bess(r,0,n)*(
		    (Re_b_[key])
		    *cos(l*(x-L_sys*0.5)*PI/L_sys)
		    -(Im_b_[key])
		    *sin(l*(x-L_sys*0.5)*PI/L_sys)
		    )/(pow((bessel_zero[(n-1)*(Mmax+1)]/R_sys),2.0)+pow((l*PI/L_sys),2.0));
	}
    }
    return -result/L_sys;
}

