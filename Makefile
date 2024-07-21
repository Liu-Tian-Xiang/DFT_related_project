CXX =mpiicpx -std=c++11 -O3
LIBS = -lgsl -lgslcblas -lmkl_scalapack_lp64 -lmkl_blacs_intelmpi_lp64 -lmkl_intel_lp64 -lmkl_intel_thread -lmkl_core -liomp5 #-lpython3.10
OUT = ecode
OBJDIR=./objects
SRCDIR=./src

LIBOBJS= \
	$(OBJDIR)/Arrange_Psi.o \
	$(OBJDIR)/scf.o \
	$(OBJDIR)/run.o \
	$(OBJDIR)/printPsi.o \
	$(OBJDIR)/Arrange_Psi_m.o \
	$(OBJDIR)/ALLOC_H.o \
	$(OBJDIR)/IntegralMonte.o \
	$(OBJDIR)/CoulombPotential.o \
	$(OBJDIR)/stRHO.o \
	$(OBJDIR)/set.o \
	$(OBJDIR)/setV.o \
	$(OBJDIR)/SetVxc.o \
	$(OBJDIR)/gtRHO.o \
	$(OBJDIR)/gtV.o \
	$(OBJDIR)/stV.o \
	$(OBJDIR)/surf2D.o \
	$(OBJDIR)/InterpSurf.o \
	$(OBJDIR)/InterpSurf2D.o \
	$(OBJDIR)/FstPs.o \
	$(OBJDIR)/vals2coeffs.o \
	$(OBJDIR)/coeffs2vals.o \
	$(OBJDIR)/FstPsonSolvr.o \
	$(OBJDIR)/PoissonCylinder.o \
	$(OBJDIR)/Multiply.o \
	$(OBJDIR)/BartelsStewart.o \
	$(OBJDIR)/spMatrixFunc.o \
	$(OBJDIR)/surf.o \
	$(OBJDIR)/printcheck.o \
	$(OBJDIR)/surfdensity.o \
	$(OBJDIR)/surfdensity2D.o \
	$(OBJDIR)/surfdensity1D.o \
	$(OBJDIR)/vxc.o \
	$(OBJDIR)/rho_test.o \
	$(OBJDIR)/interpV.o \
	$(OBJDIR)/solve_pde.o \
	$(OBJDIR)/pde_result.o \
	$(OBJDIR)/create_b.o \
	$(OBJDIR)/expandbasisIm.o \
	$(OBJDIR)/expandbasisRe.o \
	$(OBJDIR)/expand.o \
	$(OBJDIR)/rhoShell.o \
	$(OBJDIR)/pcreateb.o \
	$(OBJDIR)/create_vxc.o \
	$(OBJDIR)/pcreatevxc.o \
	$(OBJDIR)/destroy.o \
	$(OBJDIR)/destroy_.o \
	$(OBJDIR)/positive_contribution_two.o \
	$(OBJDIR)/check_orthogonal.o \
	$(OBJDIR)/display_rho.o \
	$(OBJDIR)/python_draw.o \
	$(OBJDIR)/basis_index.o \
	$(OBJDIR)/bess.o \
	$(OBJDIR)/bessel_integration.o \
	$(OBJDIR)/Coulomb_potential.o \
	$(OBJDIR)/Diagonal_Hamiltonian.o \
	$(OBJDIR)/display_Coulomb_potential.o \
	$(OBJDIR)/display_result.o \
	$(OBJDIR)/find_A_index_basis.o \
	$(OBJDIR)/free_everything.o \
	$(OBJDIR)/generate_bessel_integration.o \
	$(OBJDIR)/generate_bessel_zero.o \
	$(OBJDIR)/get_param.o \
	$(OBJDIR)/Get_V_xc1.o \
	$(OBJDIR)/Get_V_xc2.o \
	$(OBJDIR)/Hamiltonian.o \
	$(OBJDIR)/HamiltonianMulticore.o \
	$(OBJDIR)/init.o \
	$(OBJDIR)/MultcoreInit.o \
	$(OBJDIR)/Init_V.o \
	$(OBJDIR)/Integral.o \
	$(OBJDIR)/IntegralMulticore.o \
	$(OBJDIR)/Integral_rho.o \
	$(OBJDIR)/kenetic.o \
	$(OBJDIR)/main.o \
	$(OBJDIR)/parain.o \
	$(OBJDIR)/positive_contribution.o \
	$(OBJDIR)/print_basis_index.o \
	$(OBJDIR)/print_matrix.o \
	$(OBJDIR)/print_m_eig.o \
	$(OBJDIR)/print_wave_function.o \
	$(OBJDIR)/renew_Psi.o \
	$(OBJDIR)/rho.o \
	$(OBJDIR)/V_Coulomb.o \
	$(OBJDIR)/ChangeCoeffs.o \
	$(OBJDIR)/ADIShift.o \
	$(OBJDIR)/pts.o \
	$(OBJDIR)/printStuff.o \
	$(OBJDIR)/Diagonal_parallel.o \


$(OUT): objdir $(LIBOBJS)
	$(CXX) $(LIBOBJS) -o $@ $(LIBS)

objdir:
	mkdir -p $(OBJDIR)

$(OBJDIR)/run.o: $(SRCDIR)/run.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/scf.o: $(SRCDIR)/scf.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/printPsi.o: $(SRCDIR)/printPsi.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Arrange_Psi_m.o: $(SRCDIR)/Arrange_Psi_m.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/ALLOC_H.o: $(SRCDIR)/ALLOC_H.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/GetStaticHamilton.o: $(SRCDIR)/GetStaticHamilton.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/IntegralMonte.o: $(SRCDIR)/IntegralMonte.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/set.o: $(SRCDIR)/set.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/stV.o: $(SRCDIR)/stV.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/gtV.o: $(SRCDIR)/gtV.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/gtRHO.o: $(SRCDIR)/gtRHO.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/stRHO.o: $(SRCDIR)/stRHO.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/surf2D.o: $(SRCDIR)/surf2D.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/InterpSurf2D.o: $(SRCDIR)/InterpSurf2D.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/InterpSurf.o: $(SRCDIR)/InterpSurf.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/FstPs.o: $(SRCDIR)/FstPs.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/coeffs2vals.o: $(SRCDIR)/coeffs2vals.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/vals2coeffs.o: $(SRCDIR)/vals2coeffs.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/FstPsonSolvr.o: $(SRCDIR)/FstPsonSolvr.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/PoissonCylinder.o: $(SRCDIR)/PoissonCylinder.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/SetVxc.o: $(SRCDIR)/SetVxc.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/printcheck.o: $(SRCDIR)/printcheck.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/printStuff.o: $(SRCDIR)/printStuff.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/pts.o: $(SRCDIR)/pts.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/ADIShift.o: $(SRCDIR)/ADIShift.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/ChangeCoeffs.o: $(SRCDIR)/ChangeCoeffs.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Multiply.o: $(SRCDIR)/Multiply.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/BartelsStewart.o: $(SRCDIR)/BartelsStewart.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/spMatrixFunc.o: $(SRCDIR)/spMatrixFunc.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/interpV.o: $(SRCDIR)/interpV.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/spectrumFC.o: $(SRCDIR)/spectrumFC.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/surfdensity1D.o: $(SRCDIR)/surfdensity1D.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/surfdensity2D.o: $(SRCDIR)/surfdensity2D.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/surfdensity.o: $(SRCDIR)/surfdensity.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/surf.o: $(SRCDIR)/surf.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/interp_vxc2.o: $(SRCDIR)/interp_vxc2.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/pde_result.o: $(SRCDIR)/pde_result.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/vxc.o: $(SRCDIR)/vxc.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/destroy_.o: $(SRCDIR)/destroy_.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Pde_V.o: $(SRCDIR)/Pde_V.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/solve_pde.o: $(SRCDIR)/solve_pde.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/pde_solution.o: $(SRCDIR)/pde_solution.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/destroy.o: $(SRCDIR)/destroy.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/destroy_wave.o: $(SRCDIR)/destroy_wave.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/rhoShell.o: $(SRCDIR)/rhoShell.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/expandbasisRe.o: $(SRCDIR)/expandbasisRe.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/expandbasisIm.o: $(SRCDIR)/expandbasisIm.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/expand.o: $(SRCDIR)/expand.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/create_vxc.o: $(SRCDIR)/create_vxc.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/pcreatevxc.o: $(SRCDIR)/pcreatevxc.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/pcreateb.o: $(SRCDIR)/pcreateb.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/create_b.o: $(SRCDIR)/create_b.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/criteria.o: $(SRCDIR)/criteria.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/rho_design.o: $(SRCDIR)/rho_design.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/display_rho_surf.o: $(SRCDIR)/display_rho_surf.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/pde_solver2.o: $(SRCDIR)/pde_solver2.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/pde_solver.o: $(SRCDIR)/pde_solver.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/V_Cpde.o: $(SRCDIR)/V_Cpde.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/setV.o: $(SRCDIR)/setV.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/splineV.o: $(SRCDIR)/splineV.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/generate_pde_matrix.o: $(SRCDIR)/generate_pde_matrix.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/IntegralMulticore.o: $(SRCDIR)/IntegralMulticore.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Integral_monte.o: $(SRCDIR)/Integral_monte.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/interp_V_xc2.o: $(SRCDIR)/interp_V_xc2.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/spline.o: $(SRCDIR)/spline.cpppp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/record_rho.o: $(SRCDIR)/record_rho.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/generate_b_old.o: $(SRCDIR)/generate_b_old.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/generate_b.o: $(SRCDIR)/generate_b.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/odd_b.o: $(SRCDIR)/odd_b.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/even_b.o: $(SRCDIR)/even_b.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Re_b.o: $(SRCDIR)/Re_b.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Im_b.o: $(SRCDIR)/Im_b.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Delta.o: $(SRCDIR)/Delta.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/sinX_X.o: $(SRCDIR)/sinX_X.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/singleJ_integrate.o: $(SRCDIR)/singleJ_integrate.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/check_orthogonal.o: $(SRCDIR)/check_orthogonal.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/positive.o: $(SRCDIR)/positive.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/python_draw.o: $(SRCDIR)/python_draw.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/get_state_degenerate.o: $(SRCDIR)/get_state_degenerate.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/bak_psi.o: $(SRCDIR)/bak_psi.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/display_Vxc1.o: $(SRCDIR)/display_Vxc1.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Diagonal_parallel.o: $(SRCDIR)/Diagonal_parallel.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Arrange_Psi.o: $(SRCDIR)/Arrange_Psi.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/basis_index.o: $(SRCDIR)/basis_index.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/bess.o: $(SRCDIR)/bess.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/bessel_integration.o: $(SRCDIR)/bessel_integration.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/CoulombPotential.o: $(SRCDIR)/CoulombPotential.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Coulomb_potential.o: $(SRCDIR)/Coulomb_potential.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Diagonal_Hamiltonian.o: $(SRCDIR)/Diagonal_Hamiltonian.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/surf_pdeV.o: $(SRCDIR)/surf_pdeV.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/display_Coulomb_potential.o: $(SRCDIR)/display_Coulomb_potential.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/display_Psi_wave.o: $(SRCDIR)/display_Psi_wave.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/display_result.o: $(SRCDIR)/display_result.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/display_rho.o: $(SRCDIR)/display_rho.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/eigen_m_difference.o: $(SRCDIR)/eigen_m_difference.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/find_A_index_basis.o: $(SRCDIR)/find_A_index_basis.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/free_everything.o: $(SRCDIR)/free_everything.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/get_sinthree_integration.o: $(SRCDIR)/get_sinthree_integration.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/generate_sinthree_integration.o: $(SRCDIR)/generate_sinthree_integration.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/generate_bessel_integration.o: $(SRCDIR)/generate_bessel_integration.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/generate_bessel_zero.o: $(SRCDIR)/generate_bessel_zero.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/get_bessel_integration.o: $(SRCDIR)/get_bessel_integration.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/get_param.o: $(SRCDIR)/get_param.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Get_V_xc1.o: $(SRCDIR)/Get_V_xc1.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Get_V_xc2.o: $(SRCDIR)/Get_V_xc2.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/HamiltonianMulticore.o: $(SRCDIR)/HamiltonianMulticore.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Hamiltonian.o: $(SRCDIR)/Hamiltonian.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/MultcoreInit.o: $(SRCDIR)/MultcoreInit.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/init.o: $(SRCDIR)/init.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Init_V.o: $(SRCDIR)/Init_V.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Integral2.o: $(SRCDIR)/Integral2.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Integral.o: $(SRCDIR)/Integral.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Integral_rho.o: $(SRCDIR)/Integral_rho.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/kenetic.o: $(SRCDIR)/kenetic.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/kenetic_matrix.o: $(SRCDIR)/kenetic_matrix.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/main.o: $(SRCDIR)/main.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/parain.o: $(SRCDIR)/parain.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/positive_contribution_two.o: $(SRCDIR)/positive_contribution_two.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/positive_contribution.o: $(SRCDIR)/positive_contribution.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/print_basis_index.o: $(SRCDIR)/print_basis_index.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/print_matrix.o: $(SRCDIR)/print_matrix.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/print_m_eig.o: $(SRCDIR)/print_m_eig.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/print_Psi_eig.o: $(SRCDIR)/print_Psi_eig.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/print_wave_function.o: $(SRCDIR)/print_wave_function.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Psi_eigenvalue_difference.o: $(SRCDIR)/Psi_eigenvalue_difference.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/Psi_wave_function.o: $(SRCDIR)/Psi_wave_function.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/renew_Psi.o: $(SRCDIR)/renew_Psi.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/rho.o: $(SRCDIR)/rho.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/rho_test.o: $(SRCDIR)/rho_test.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/rho_psi_old.o: $(SRCDIR)/rho_psi_old.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/sin_integ_monte.o: $(SRCDIR)/sin_integ_monte.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/sin_integration.o: $(SRCDIR)/sin_integration.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/syn_index.o: $(SRCDIR)/syn_index.cpp
	$(CXX) -g -c $< -o $@
$(OBJDIR)/V_Coulomb.o: $(SRCDIR)/V_Coulomb.cpp
	$(CXX) -g -c $< -o $@

clean:
	rm -rf $(OBJDIR) $(OUT)
