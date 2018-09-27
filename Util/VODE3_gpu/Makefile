all: fmain.exe fmain_vode.exe fmain_gpu.exe


# Set SUNDIALS_INSTALL as an environment variable for a sundials installation 
# of a version older than 3.0 which has built cvode

prefix       = ${SUNDIALS_INSTALL}
exec_prefix  = ${SUNDIALS_INSTALL}
includedir   = ${SUNDIALS_INSTALL}/include
libdir       = ${SUNDIALS_INSTALL}/lib

F90         = pgfortran
F90FLAGS    = -O0 -g
F90_LDFLAGS = -O0 -g
F90_LIBS    =  -lm /usr/lib/x86_64-linux-gnu/librt.so
F90_LIBS    =  -lm /usr/lib64/librt.so

NVCC     = /sw/summitdev/cuda/9.0.69/bin/nvcc
NVCCFLAGS = 
CPP      = /usr/bin/cc
CPPFLAGS = -O0 -DNDEBUG
CXX      = /usr/bin/c++
CXXFLAGS = -O0 -DNDEBUG
LDFLAGS  = 
LIBS     =  -lm /usr/lib64/librt.so
CUDALIBS = /sw/summitdev/cuda/9.0.69/lib64/libcudart.so

LINKFLAGS = -Wl,-rpath,${SUNDIALS_INSTALL}/lib

EXAMPLES = constants_mod constants_cosmo comoving_params reion_aux_module comoving_nd fsunlinsol_dense fnvector_serial fsunmat_dense fcvode farkode meth_params misc_params vode_aux atomic_rates eos_hc eos_params fcvode_extras f_rhs integrate_state_vode_3d ../BLAS/daxpy ../BLAS/ddot  ../BLAS/dscal  ../BLAS/idamax  ../BLAS/dcopy ../VODE/dewset ../VODE/dgesl ../VODE/dvhin  ../VODE/dvjac   ../VODE/dvnlsd ../VODE/dvode ../VODE/dvsol ../VODE/dvstep ../VODE/ixsav ../VODE/xsetf ../VODE/dacopy ../VODE/dgbfa ../VODE/dgefa ../VODE/dumach ../VODE/dvindy ../VODE/dvjust ../VODE/dvnorm ../VODE/dvset ../VODE/dvsrco ../VODE/iumach ../VODE/xerrwd ../VODE/xsetun ../VODE/dgbsl

EXAMPLES_VODE = constants_mod constants_cosmo comoving_params reion_aux_module comoving_nd meth_params misc_params vode_aux atomic_rates eos_hc eos_params f_rhs integrate_state_vode_3d ../BLAS/daxpy ../BLAS/ddot  ../BLAS/dscal  ../BLAS/idamax  ../BLAS/dcopy ../VODE/dewset ../VODE/dgesl ../VODE/dvhin  ../VODE/dvjac   ../VODE/dvnlsd ../VODE/dvode ../VODE/dvsol ../VODE/dvstep ../VODE/ixsav ../VODE/xsetf ../VODE/dacopy ../VODE/dgbfa ../VODE/dgefa ../VODE/dumach ../VODE/dvindy ../VODE/dvjust ../VODE/dvnorm ../VODE/dvset ../VODE/dvsrco ../VODE/iumach ../VODE/xerrwd ../VODE/xsetun ../VODE/dgbsl

OBJECTS_VODE  = ${EXAMPLES_VODE:=.o}
OBJECTS  = ${EXAMPLES:=.o}

# -----------------------------------------------------------------------------------------

.SUFFIXES : .o .f90 .f .cuf

 %.o: %.mod

.f90.o :
	${F90} ${F90FLAGS} ${INCLUDES} -c $< -o $(*F).o

.f.o :
	${F90} ${F90FLAGS} ${INCLUDES} -c $< -o $(@D)/$(*F).o

.cuf.o :
	${F90} ${F90FLAGS} ${INCLUDES} -c $< -o $(*F).o

# -----------------------------------------------------------------------------------------

all: fmain_vode.exe fmain.exe fmain_gpu.exe

fmain_vode.exe: ${OBJECTS_VODE} fmain_vode.o
	${F90} ${F90FLAGS} -o fmain_vode.exe -I${includedir} ${OBJECTS_VODE} fmain_vode.o ${LIBS} -L${libdir} -lsundials_fcvode -lsundials_cvode -lsundials_fcvode -lsundials_fnvecserial -lsundials_nvecserial -lsundials_arkode ${CUDALIBS} /sw/summitdev/cuda/9.0.69/lib64/libcu*.so
	echo "${F90} ${F90_LDFLAGS} -o fmain_vode.exe -I${includedir} ${OBJECTS_VODE} fmain_vode.o ${F90_LIBS} -L${libdir} -lsundials_fcvode -lsundials_cvode -lsundials_fcvode -lsundials_fnvecserial -lsundials_nvecserial" 

fmain.exe: ${OBJECTS} fmain.o
	${NVCC} ${NVCC_LDFLAGS} -o fmain.exe -I${includedir} ${OBJECTS} fmain.o ${LIBS} -L${libdir} -lsundials_fcvode -lsundials_cvode -lsundials_fcvode -lsundials_fnvecserial -lsundials_nvecserial -lsundials_arkode ${CUDALIBS} -L/sw/summitdev/gcc/6.3.1-20170301/lib64 -lgfortran
	echo "${F90} ${F90_LDFLAGS} -o fmain_vode.exe -I${includedir} ${OBJECTS} fmain_vode.o ${F90_LIBS} -L${libdir} -lsundials_fcvode -lsundials_cvode -lsundials_fcvode -lsundials_fnvecserial -lsundials_nvecserial" 

fmain_gpu.exe: fmain_gpu.cuf constants_mod.f90 reion_aux_module.f90 comoving_nd.f90 comoving_params.f90 constants_cosmo.f90
	pgfortran -o fmain_gpu.exe fmain_gpu.cuf constants_mod.f90  reion_aux_module.f90 comoving_nd.f90 comoving_params.f90  constants_cosmo.f90
#fmain_gpu.exe: fmain_gpu.o reion_aux_module.o constants_mod.o
#	${F90} ${F90FLAGS} -o fmain_gpu.exe fmain_gpu.o reion_aux_module.o constants_mod.o /sw/summitdev/cuda/9.0.69/lib64/libcu*.so

clean:
	rm -f ${OBJECTS} ${EXAMPLES:=.mod} ${OBJECTS_VODE} ${EXAMPLES_VODE:=.mod}

realclean:
	rm -f ${OBJECTS} ${EXAMPLES:=.mod} ${OBJECTS_VODE} ${EXAMPLES_VODE:=.mod}
	rm -f *.mod *.o *.exe
