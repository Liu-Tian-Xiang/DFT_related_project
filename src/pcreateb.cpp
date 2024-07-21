
#include "../includes/global.h"
#include "../includes/prototype.h"
void Wave_function::pcreateb(){
    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);

    int Nk=(2*coulomb_expand_b_l+1)*coulomb_expand_b_n;
    int period=(Nk%numprocs?Nk/numprocs+1:Nk/numprocs);
    double* SectionIm=(double *)calloc(period,sizeof(double)); 
    double* SectionRe=(double *)calloc(period,sizeof(double)); 

    if(!Im_b_) Im_b_=(double *)calloc(numprocs*period,sizeof(double));
    if(!Re_b_) Re_b_=(double *)calloc(numprocs*period,sizeof(double));
    int o=0;
    double result=0.0;

    //for(int n=1;n<=coulomb_expand_b_n;n++){
//	for(int l=-coulomb_expand_b_l;l<=coulomb_expand_b_l;l++){

    for(int ii=1;ii<=period;ii++){
	if(id*period+ii<=Nk){
	    int n=(id*period+ii-1)/(2*coulomb_expand_b_l+1)+1;
	    int l=(id*period+ii-1)%(2*coulomb_expand_b_l+1)-coulomb_expand_b_l;

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
		    cosine_temp+=temp_cosine*2.0;
		    sine_temp+=temp_sine*2.0;
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

	    SectionIm[ii-1]=sine_temp*2;/*positive_contribution_two(n,l);*/
	    SectionRe[ii-1]=cosine_temp*2+positive_contribution(n,l);
	    //Im_b_[o]=sine_temp*2;/*positive_contribution_two(n,l);*/
	    //Re_b_[o]=cosine_temp*2/*+positive_contribution(n,l)*/;
	//    o=o+1; 
	}
    }

    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Gather(SectionIm,period,MPI_DOUBLE,Im_b_,period,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Gather(SectionRe,period,MPI_DOUBLE,Re_b_,period,MPI_DOUBLE,0,MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Bcast(Im_b_,Nk,MPI_DOUBLE,0,MPI_COMM_WORLD); 
    MPI_Bcast(Re_b_,Nk,MPI_DOUBLE,0,MPI_COMM_WORLD); 
    MPI_Barrier(MPI_COMM_WORLD);
    free(SectionIm);
    free(SectionRe);

}

