#ifndef PROTOTYPE_H
#define PROTOTYPE_H
using namespace::std;

typedef double (*Func)(int n_1,int l_1,int m);

extern std::vector<int> i_stack;

//octopus
#ifdef __cplusplus
extern "C" {
#endif

#ifdef __cplusplus
}
#endif
//

extern inline double cos_half (int l)
{
    return ((l/2)%2)?(-1):1;
}
extern inline double sin_half (int l)
{
    return (((l-1)/2)%2)?(-1):1;
}
extern inline double Delta (double l)
{
    if(l==0) 
	return 1.0; 
    else 
	return 2.0*sin(l*PI*0.5)/(l*PI);
}
extern inline double Delta (int l)
{
    if (l==0)
      return 1.0;
    else if (l%2==0)
      return 0.0;
    else
      return 2.0/(l*PI)*sin_half(l);
}

extern inline double get_bessel_integration(int n,int n_1,int n_2,int m/*,double *bessel*/){
    return trip_integrate_bessel[(n-1)*index_basis[0].Nmax*index_basis[0].Nmax*(Mmax+1)+(n_1-1)*index_basis[0].Nmax*(Mmax+1)+(n_2-1)*(Mmax+1)+m];
}

void scf();
void run();
void run_init();
void define_run_modes();
void push_sub();
void ALLOC_H();
void GetStaticHamilton(int m,double *H);
double IntegralMonte(int n_1,int l_1,int n_2,int l_2,int m,Fun pV,spline_space *who);
void cacMmax();
void MultcoreInit();
void ultra1mx2cheb(double* Xk,int ldX,int rdX,double Xk_temp[]);
void multiply(lapack_complex_double* A,lapack_complex_double* B,lapack_complex_double *C,int ldR,int ldZ);
void surf_Coulomb_potential(int i);
double positive_contribution_two(int n,int l);
double system_basis(double r,double x,int l,int m,int n);
double criteria(double x);
void surf_pdeV(int i);
void HamiltonianMulticore(int m,int loop_number);
double rho_design(double r,double x);
double rho_test(double r,double x);
void display_rho_surf(int i);
gsl_vector *pde_solver(int loop_number);
double V_Cpde(double x,double y);
void splineV(int loop_number);
gsl_vector *generate_pde_matrix(int loop_number);
void generate_ReImb();
double interp_V_xc2(double r,double z);
void spline();
void record_rho();
void generate_b();
void generate_b_old();
double Delta(int l);
double Delta(double l);
double singleJ_integrate(int n);
void check_orthogonal();
double positive(int n,int l);
void python_draw(int loop_number);
void generate_sinthree_integration();
double get_sinthree_integration(int l,int l_1,int l_2);
double sin_integration(int l,int l_1, int l_2);
void get_state_degenerate();
void bak_psi(int flag);
double compare_rho(double r,double x);
void display_Vxc1(int i);
void generate_wf();
void display_rho(int i);
int renew_Psi(int m,double *w,double *z,int flag);
void display_Coulomb_potential(int i);
void free_everything();
void Hamiltonian(int m,int loop_number);
void print_wave_function(int flag,int loop_number);
double single_bessel(double r,void *params);
double positive_contribution(int n,int l);
double eigen_m_difference(double *w,int m);
void display_Psi_wave(int i);
void surf(int i,char *prename,FuncPtr pV);
void cac_mmax();
void init();
void generate_bessel_integration();
//double get_bessel_integration(int n,int n_1,int n_2,int m);
void surfdensity2D(int i,char *prename,void *ptr);
void surfdensity1D(int i,char *prename,void *ptr);
double Get_V_xc1(double r,double x,spline_space* ptr);
void print_Psi_eig(int flag,int loop_number);
double V_Coulomb(int n_1,int l_1,int n_2,int l_2,int m);
double rho_psi(double r,double x);
int* get_param(int m,int i,int *p);
double bess(double r,int m, int n);
int Diagonal_parallel(double *H,int m,int flag);
int Diagonal_Hamiltonian_parallel(double *H,int m,int flag);
int parallel_diag_H(double *H,int m,int flag);
void syn_index(double *w,int m);
double rho_psi_old(double r,double x);
double func_inner(double r,void *params);
double func_outer(double x,void *params);
double func_Mouter(double x,void *params);
double IntegralMulticore(int n_1,int l_1,int n_2,int l_2,int m,Fun/*cPtr*/ pV,spline_space *who);
double func_Minner(double r,void *params);
void print_matrix(int m,double *z);
void basis_index(int m);
void generate_bessel_zero();
double Psi_wave_function(double r,double phi,double x,int m);
double kenetic_matrix(int m,int n,int l);
double bessel(double r,void *params);
double bessel_integration(int n,int n_1, int n_2,int m);
int find_A_index_basis(int m,int n,int l);
void Arrange_Psi();
void printPsi();
void Arrange_Psi_m();
void print_basis_index();
double kenetic(int i,int m,int n,int l);
int main(int argc,char *argv[]);
void set_input_para(const char *file, vector<string> s, double *p);
void display_result(int i,double delta);
double Psi_eigenvalue_difference();
void print_m_eig(int e_m,double *w);
int parallel_H(double *H,int m,int flag);
void pdsyevx_func(double *A_glob,int tot,double *Z_glob,double *W);
int Diagonal_Hamiltonian(double *H,int m,int flag);
///////Fst
MKL_Complex16 rhs(int k,double r,double th,double z);
void chebpts(int n,double r[]);
void printResult(char Name[],MKL_Complex16 F[],int n1,int n2,int n3,double tol);
void printResult(char Name[],double F[],int n1,int n2,int n3,double tol);
void trigpts(int n,double th[],double coeffs);
void print_matrix( char* desc, MKL_INT m, MKL_INT n, lapack_complex_double* a, MKL_INT lda );
void print_rmatrix( char* desc, MKL_INT m, MKL_INT n, double* a, MKL_INT lda );
void print_matrix(int n,double *z);
double *cheb2leg(double *c_cheb,int len,bool normalize);
double *cheb2leg_direct(double *c_cheb,int len,bool normalize);
void BartelsStewart(lapack_complex_double *A,lapack_complex_double *B,lapack_complex_double *C,lapack_complex_double *D,lapack_complex_double *E,bool xsplit,bool ysplit,int N,MKL_Complex16 XX[],int ldZ);
double *cheb2leg_fast(double *c_cheb,int len,bool normalize);
int ADIshifts(double a,double b,double c,double d,double tol,double *p,double *q);
double *cheb2ultra(double *X,int ldX,int ldS);
double *cheb2leg_mat(int N);
double *ultra1mx2leg_mat(int N);
double *ultra1mx2cheb(double *X,int ldR,int ldZ);
double *leg2cheb_mat(int N);

double* Multiply(spMatrix *A,int ldA,int ldk,spMatrix *B,int ldB);
double* Multiply(double *X,int ldX,int ldk,spMatrix *S,int ldS);
double* Multiply(spMatrix *S,int ldS,int ldk,double *X,int ldX);
double* Multiply(double *S,int ldS,int ldk,double *X,int ldX);
void vals2coeffs(MKL_Complex16 F[],int n1,int n2,int n3,MKL_Complex16 FF[]);
void c2vals2coeffs(MKL_Complex16 Fk[],int ldFk,MKL_Complex16 FF[],int ldFF);
void trivals2coeffs(MKL_Complex16 Fk[],int ldFk,MKL_Complex16 FF[],int ldFF);
void coeffs2vals(MKL_Complex16 F[],int n1,int n2,int n3,MKL_Complex16 FF[]);
void c2coeffs2vals(MKL_Complex16 Fk[],int ldFk,MKL_Complex16 FF[],int ldFF,int k,int flag);
void tricoeffs2vals(MKL_Complex16 Fk[],int ldFk,MKL_Complex16 FF[],int ldFF,int k,int flag);
void PoissonCylinder(double *F,double tol,int ldR,int ldT,int ldZ,double FF[]);

double expandbasis(int n_1,int l_1,int n_2,int l_2,int m,Fun/*cPtr*/ pV,spline_space *who);
double expandbasisRe(int n_1,int l_1,int n_2,int l_2,int m,Fun/*cPtr*/ pV,spline_space *who);
double expandbasisIm(int n_1,int l_1,int n_2,int l_2,int m,Fun/*cPtr*/ pV,spline_space *who);
double expand(double r,double x,int m,int n_2,int l_2,string type);
double One(double r,double x,spline_space* ptr);
double rhoShell(double r,double x,spline_space* ptr);


#endif
