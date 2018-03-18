#include "Nyx.H"
#include "Nyx_F.H"

using namespace amrex;

using std::string;

void
Nyx::update_state_with_sources( MultiFab& S_old, MultiFab& S_new, 
                                MultiFab& ext_src_old, MultiFab& hydro_src, 
                                MultiFab& grav, MultiFab& divu_cc,
                                amrex::Real dt, amrex::Real a_old, amrex::Real a_new)
{
    for (MFIter mfi(S_old,true); mfi.isValid(); ++mfi)
    {
        const Box& bx = mfi.tilebox();
        fort_update_state
            (
             bx.loVect(), bx.hiVect(), 
             BL_TO_FORTRAN(S_old[mfi]),
             BL_TO_FORTRAN(S_new[mfi]),
             BL_TO_FORTRAN(ext_src_old[mfi]),
             BL_TO_FORTRAN(hydro_src[mfi]),
             BL_TO_FORTRAN(grav[mfi]),
             BL_TO_FORTRAN(divu_cc[mfi]),
             &dt, &a_old, &a_new, &print_fortran_warnings, &do_grav);
   }
}
