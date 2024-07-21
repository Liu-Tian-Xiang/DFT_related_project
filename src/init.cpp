#include "../includes/global.h"
#include "../includes/prototype.h"

void cac_mmax(){
    Mmax=0;
    while(pow(gsl_sf_bessel_zero_Jnu(Mmax,1)/R_sys,2.0)+pow(PI/L_sys,2.0)<Ec*Ef0)
    {Mmax+=1;}
    Mmax=Mmax-1;
}
void init(){
    int id,numprocs;
    MPI_Comm_rank(MPI_COMM_WORLD,&id);
    MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
    const char *input_file="./inputs/para2.in";
    double retp[20];
    if(id==0){ 
	vector<string> input_para(10);
	input_para[0]="R";
	input_para[1]="L";
	input_para[2]="N";
	input_para[3]="Ec";
	input_para[4]="rs";
	input_para[5]="BoxMag_R";
	input_para[6]="BoxMag";
	input_para[7]="erf_eigen";
	input_para[8]="coulomb_expand_b_l";
	input_para[9]="coulomb_expand_b_n";
	set_input_para(input_file,input_para,retp);
    } 
    MPI_Bcast(retp,20,MPI_DOUBLE,0,MPI_COMM_WORLD);
    R=retp[0];
    L=retp[1];
    N=retp[2];
    Ec=retp[3];
    rs=retp[4];
    BoxMag_R=retp[5];
    BoxMag=retp[6];
    erf_eigen=retp[7]; 
    coulomb_expand_b_l=retp[8];
    coulomb_expand_b_n=retp[9];

    ////////Parameter_Calculation/////////////////////////////////////////////
    PI=4.0*atan(1.0);
    E_divide=h_bar*h_bar/(m_e*ELECTRON_CHARGE)*1e21;
    V_divide=ELECTRON_CHARGE/(4*PI*VACUUM_PERMITTIVITY*E_divide)*1e12;
    E_g=1000*ELECTRON_CHARGE*1e9/(2.0*a0*4*PI*VACUUM_PERMITTIVITY*E_divide);
    kf=pow(9*PI/4,1.0/3)/(rs*a0);//k_f=(3\pi^2n)^{1/3},n=3/(4\pi rs^3), k_f=(9\pi/4)^{1/3}/rs;
    n0=3.0/(4*PI*pow(rs*a0,3));
    Ef0=0.5*pow(kf,2);
    lf=2*PI/kf;

    occupied_electrons=floor(PI*pow(R,2)*L*2*n0/2);
    L=occupied_electrons*2/(PI*pow(R,2)*n0*2); 
    R_sys=R+BoxMag_R;
    L_sys=2*L+2.0*BoxMag+N;
    /////////////////////////////////////////////////////////////////////////

    cac_mmax(); 
    index_basis=(INDEX_JELLIUM_ROD*)calloc(Mmax+1,sizeof(INDEX_JELLIUM_ROD));
    for (int i = 0; i <=Mmax; i++){
	basis_index(i);
    }
    ALLOC_H();

    if(id==0){
	printf("\n\n\n---print__init---\n");  
	printf("\t\tPI=%1.9f\n",PI); 
	printf("\t\tR=%1.4f\n",R); 
	printf("\t\tL=%1.4f\n",L); 
	printf("\t\tN=%1.4f\n",N); 
	printf("\t\tR_sys=%1.4f\n",R_sys); 
	printf("\t\tL_sys=%1.4f\n",L_sys); 
	printf("\t\tE_divide=%1.9f\n",E_divide); 
	printf("\t\tV_divide=%1.9f\n",V_divide); 
	printf("\t\t" RED"kf=%1.9f" RESET"\n",kf); 
	printf("\t\t" GREEN"n0=%1.9f" RESET"\n",n0); 
	printf("\t\t" YELLOW"Ef0=%1.9f" RESET"\n",Ef0); 
	printf("\t\t" RED"lf=%1.9f" RESET"\n",lf); 
	printf("\t\tMmax=%d\n",Mmax); 
	printf("\t\tE_g=%1.3e\n",E_g); 
	printf("\t\t" CYAN"occupied_electrons=%d" RESET"\n",occupied_electrons);
	printf("\t\t" CYAN"E_theory=%1.5f" RESET"\n",n0*1e-10/(VACUUM_PERMITTIVITY));
    } 
    generate_bessel_zero();
    generate_bessel_integration();

    //if(id==0) printf("ylm=%1.4f\n",ylm(2.0,3.0,4.0,2,2));

}

