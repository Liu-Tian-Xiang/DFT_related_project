
#include "../includes/global.h"
#include "../includes/prototype.h"
void Wave_function::create_b(){

    if(Im_b_==NULL) Im_b_=(double *)calloc((2*coulomb_expand_b_l+1)*coulomb_expand_b_n,sizeof(double));
    if(Re_b_==NULL) Re_b_=(double *)calloc((2*coulomb_expand_b_l+1)*coulomb_expand_b_n,sizeof(double));
    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
 
    int o=0;
    double result=0.0;
    for(int n=1;n<=coulomb_expand_b_n;n++){
	for(int l=-coulomb_expand_b_l;l<=coulomb_expand_b_l;l++){

	    double cosine_temp=0.0;
	    double sine_temp=0.0;
	    int number=occupied_electrons;
	    for(int i=0;i<number;i++){ 
		int m=wf[i].m; 
		int Nmax=index_basis[m].Nmax;
		int Ind1=0;                                 
		double temp_sine=0.0;
		double temp_cosine=0.0;
		for(int n_1=1;n_1<=Nmax;n_1++){
		    for(int l_1=1;l_1<=index_basis[m].Lmax[n_1-1];l_1++){
			int Ind2=0;
			for(int n_2=1;n_2<=Nmax;n_2++){
			    for(int l_2=1;l_2<=index_basis[m].Lmax[n_2-1];l_2++){
				int l_plus=(l_1+l_2);
				int l_minus=(l_1-l_2);
				if(l_plus%2==0 | l_minus==0){
				    temp_cosine+=get_bessel_integration(n,n_1,n_2,m)*
					wf[i].A_nl[Ind1]*
					wf[i].A_nl[Ind2]*
					(
					 Delta((l_plus-l))*cos(PI*0.5*l_plus)
					 -Delta((l_minus-l))*cos(PI*0.5*l_minus)
					 //+Delta((-l_plus-l))*cos(PI*0.5*l_plus)
					 //-Delta((-l_minus-l))*cos(PI*0.5*l_minus)
					);
				}else{
				    temp_sine+=get_bessel_integration(n,n_1,n_2,m)*
					wf[i].A_nl[Ind1]*
					wf[i].A_nl[Ind2]*
					(
					 Delta((l_plus-l))*sin(PI*0.5*(l_plus))
					 -Delta((l_minus-l))*sin(PI*0.5*(l_minus))
					 //-Delta((-l_plus-l))*sin(PI*0.5*(l_plus))
					 //+Delta((-l_minus-l))*sin(PI*0.5*(l_minus))
					);
				}
				Ind2=Ind2+1;
			    }
			}
			Ind1=Ind1+1;
		    }
		}
/*
		if(m!=0 & i!=number-1){
		    cosine_temp+=temp_cosine*2;
		    sine_temp+=temp_sine*2;
		    number=number-1;
		}else{
		    cosine_temp+=temp_cosine;
		    sine_temp+=temp_sine;
		}
*/
		    cosine_temp+=temp_cosine;
		    sine_temp+=temp_sine;
	    }
	    ///////////////////////////////////////////////////////////////////////

	    Im_b_[o]=sine_temp*2;/*positive_contribution_two(n,l);*/
	    Re_b_[o]=cosine_temp*2+positive_contribution(n,l);
	    o=o+1; 
	}
    }


}
