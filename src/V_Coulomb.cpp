#include "../includes/global.h"
#include "../includes/prototype.h"

double V_Coulomb(int n_1,int l_1,int n_2,int l_2,int m){
    double V_temp=0.0;
    for(int n=1;n<=coulomb_expand_b_n;n++){
	for(int l=-coulomb_expand_b_l;l<=coulomb_expand_b_l;l++){
	    int l_plus=l_1+l_2;
	    int l_minus=l_1-l_2;
	    int key=(n-1)*(2*coulomb_expand_b_l+1)+l+coulomb_expand_b_l;
	    int lm_rm=l_minus%2;
	    int k=lm_rm?((l_minus-1)/2):(l_minus/2);
	    if(lm_rm){
	    V_temp=V_temp+get_bessel_integration(n,n_1,n_2,m)/(pow(bessel_zero[(n-1)*(Mmax+1)]/R_sys,2.0)+pow((l*PI/L_sys),2.0))
		*(
			//(Psi_1.Im_b_[key]+Psi_1.Im_vxc_[key])
			(Psi_1.Im_b_[key])
			*(
			    sin(0.5*(l_plus)*PI)*(Delta((l_plus-l))-Delta((l_plus+l)))
			    -sin(0.5*(l_minus)*PI)*(Delta((l_minus-l))-Delta((l_minus+l)))
			 )
		 );
	    }else{
		V_temp=V_temp+get_bessel_integration(n,n_1,n_2,m)/(pow(bessel_zero[(n-1)*(Mmax+1)]/R_sys,2.0)+pow((l*PI/L_sys),2.0))
		    *(
			    //-(Psi_1.Re_b_[key]+Psi_1.Re_vxc_[key])
			    -(Psi_1.Re_b_[key])
			    *(
				cos(0.5*(l_minus)*PI)*(Delta((l_minus+l))+Delta((l_minus-l)))
				-cos(0.5*(l_plus)*PI)*(Delta((l_plus+l))+Delta((l_plus-l)))
			     )
		     );

	    }
	}
    }
    return V_temp*0.5/L_sys;
}

