#include "../includes/global.h"
#include "../includes/prototype.h"

double Get_V_xc2(double r,double x,spline_space* ptr){
    double re=0.0;
    double den=0;


	den=Psi_1.rho(r,x);
/*
    if(Mix.spline_values_!=NULL){
	den=interpV(r,x/2.0,&Mix);
    }else{
	//den=Psi_1.gtRHO(r,x);
	den=Psi_1.rho(r,x);
    }
*/
    if(den<1e-5) return 0.0; 
    //////////////////den=den*2.0;
    double r_s=pow(3/(4*PI*den),1.0/3)/a0;
    //    double denominator=(1.3334+1.0529*sqrt(r_s)); 
    //re=-0.916*pow(den,1.0/3)/kk-0.2846/
    //    (1.3334+1.0529*sqrt(kk)*pow(den,-1.0/6));
    //   re=-4*0.916/(3*r_s)-0.2846/denominator-0.2846*1.0529*sqrt(r_s)/(pow(denominator,2.0)*6);
    re=-4*0.916/(3*r_s)-0.88/(r_s+7.8)-0.88*r_s/(3*pow(r_s+7.8,2.0)); 
    return re;
}
