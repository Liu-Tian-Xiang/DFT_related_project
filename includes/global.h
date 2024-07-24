#ifndef GLOBAL_H
#define GLOBAL_H
//define the constants
#include <gsl/gsl_linalg.h>
#include <gsl/gsl_spline2d.h>
#include <gsl/gsl_sf_bessel.h>
#include <gsl/gsl_integration.h>
#include <gsl/gsl_monte.h>
#include <gsl/gsl_monte_plain.h>
#include "gsl/gsl_sf.h"
#include "mkl_scalapack.h"
#include "mkl_lapacke.h"
#include "mkl_lapack.h"
#include <mkl_pblas.h>
#include <mkl_blacs.h>
#include <fftw3.h>
//#include "python2.7/Python.h"
#include "python3.9/Python.h"

#include <vector>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <mpi.h>
#define a0 0.052917721067 //Bohr radius in unit of nanometer.
#define ELECTRON_CHARGE (1.602176487e-19)/* A s */
#define VACUUM_PERMITTIVITY (8.854187817e-12)/* A^2 s^4 / kg m^3 */
#define h_bar (1.05457162825e-34) /* kg m^2 / s */
#define m_e (9.10938188e-31) /* kg */
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"
#define BLUE    "\x1b[34m"
#define MAGENTA "\x1b[35m"
#define CYAN    "\x1b[36m"
#define RESET   "\x1b[0m"

extern int occupied_electrons,Mmax,coulomb_expand_b_l,coulomb_expand_b_n;
extern double PI,delta_rho,delta;
extern double R,L,N,R_sys,L_sys,BoxMag,Ec,rs;
extern double n0,kf,lf,Ef0,k_xc;
extern double erf_eigen,BoxMag_R;
extern double *trip_integrate_bessel;
extern double E_divide,V_divide,E_g;

typedef double (*FuncPtr)(double r,double x);
extern double *bessel_zero;
extern double *bessel_Jn;
extern int print_mode;
extern int flag;
extern int loop_number;
extern int calc_mode,instr;


enum 
{
 M_START_STATIC_CALC = 1,
 M_STOP = 99    
};

enum 
{
 I_SETUP_RPSI          =  1,
 I_END                 =  2,
 I_RANDOMIZE_RPSI      =  3,
 I_LOAD_RPSI           =  4,
 I_SETUP_HAMILTONIAN   =  5,
 I_SCF                 =  6,
 I_LCAO                =  7,
 I_PRINT_BASIS         =  8,
 I_FREE                =  9 
};


class _HAMILTONIAN
{
    public:
	int m;
	int Nmax;
	int Tot;
	double dt;
	double *h;
};
typedef class _HAMILTONIAN HAMILTONIAN;
extern HAMILTONIAN *ht; 


struct _INDEX_JELLIUM_ROD
{
    int m;
    int Nmax;
    int Tot;
    int *Lmax;
};
typedef struct _INDEX_JELLIUM_ROD INDEX_JELLIUM_ROD;
extern INDEX_JELLIUM_ROD *index_basis; 

class _spline
{
    private:
    public:
	double points;
	double mesh;
	double *spline_values_;
	double *spline_r_coords_; 
	double *spline_z_coords_; 
	gsl_spline2d* spline_;
	gsl_interp_accel* interp_r_accel_;
	gsl_interp_accel* interp_z_accel_;

	gsl_vector* pde_result();
	MKL_Complex16 *FstPsonSolvr(int n1,int n2,int n3);

	void FstPs(int loop_number);
	void solve_pde(int loop_number);
	void vxc();
	void set();
	void setV();
	void destroy_();
};
typedef class _spline spline_space;
extern spline_space cylinder,spline_vxc,FstPoisson,Mix,MixV;

class _Wave_function
{
    public:
	double *Im_b_;
	double *Re_b_;
	double *Im_vxc_;
	double *Re_vxc_;

	double points;
	double mesh;
	double *spline_values_;
	double *spline_r_coords_; 
	double *spline_z_coords_; 
	gsl_spline2d* spline_;
	gsl_interp_accel* interp_r_accel_;
	gsl_interp_accel* interp_z_accel_;

	double *spline_values_V;
	double *spline_r_coords_V; 
	double *spline_z_coords_V; 
	gsl_spline2d* spline_V;
	gsl_interp_accel* interp_r_accel_V;
	gsl_interp_accel* interp_z_accel_V;


	struct _wave
	{
	    int m;
	    double eig; 
	    double *A_nl;
	}*wf;

	//struct _wave tp[100];
	void printcheck(char name);
	void SetVxc();
	void create_b();
	void create_vxc();
	void pcreateb();
	void pcreatevxc();
	double gtRHO(double r,double x);
	void stRHO();
	double CoulombPotential(double r,double x);
	double gtV(double r,double x);
	void stV();

	void destroy_wave();
	void destroy_b();
	void destroy();
	double rho(double r,double x);
    private:
	int Omega;
};
typedef class _Wave_function Wave_function;
extern Wave_function Psi_1,Psi_2,Psi_3,Psi_new,Psi_4,Psi_5;

class _spMatrix{
    public:
	struct _spdiags
	{
	    int i;
	    int j;
	    double eval; 
	}*spdiags;
	void Create_spMatrix2(double *v,int *shift,int lds,int dim);
	void Create_spMatrix(double *v,double *w,int *shift,int dim);
	void Print_spMatrix();
	void destroy_spMatrix();
	double element(int i,int j);
    private:
	int dimStruct;
	int dimMatrix;
};
typedef class _spMatrix spMatrix;
//define group
struct _group
{
    MPI_Group group_parts;
    MPI_Comm group_parts_comm;
};
typedef struct _group group_creat;
extern group_creat *group;
extern MPI_Group world_group,group_gather;
extern MPI_Comm gather_comm; 

////Fun define
typedef double (*Fun)(double x,double y,spline_space *ptr);
////Function
double Init_V(double r,double x,spline_space* ptr);
double Get_V_xc2(double r,double x,spline_space *ptr);
double Integral(int n_1,int l_1,int n_2,int l_2,int m,Fun pV,spline_space *who);
double interpV(double x,double y,spline_space *ptr);
spMatrix leg2ultra_mat(int m);
void surfdensity(int i,char *prename,void *ptr);
double Coulomb_potential(double r,double x);
void surf2D(int i,char *prename,FuncPtr pV);
double Integral_monte(int n_1,int l_1,int n_2,int l_2,int m,FuncPtr pV);
double FuncPtr_inner(double r,void *params);
double FuncPtr_outer(double x,void *params);
double Integral_rho(FuncPtr pV);
void InterpSurf(int i,char *prename,spline_space *ptr);
void InterpSurf2D(int i,char *prename,spline_space *ptr);

#endif
