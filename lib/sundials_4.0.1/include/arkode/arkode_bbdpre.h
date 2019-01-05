/*---------------------------------------------------------------
 * Programmer(s): Daniel R. Reynolds @ SMU
 *---------------------------------------------------------------
 * LLNS/SMU Copyright Start
 * Copyright (c) 2017, Southern Methodist University and 
 * Lawrence Livermore National Security
 *
 * This work was performed under the auspices of the U.S. Department 
 * of Energy by Southern Methodist University and Lawrence Livermore 
 * National Laboratory under Contract DE-AC52-07NA27344.
 * Produced at Southern Methodist University and the Lawrence 
 * Livermore National Laboratory.
 *
 * All rights reserved.
 * For details, see the LICENSE file.
 * LLNS/SMU Copyright End
 *---------------------------------------------------------------
 * This is the header file for the ARKBBDPRE module, for a
 * band-block-diagonal preconditioner, i.e. a block-diagonal
 * matrix with banded blocks, for use with the ARKSPILS 
 * interface, and the MPI-parallel NVECTOR module.
 *
 * Summary:
 *
 * These routines provide a preconditioner matrix that is
 * block-diagonal with banded blocks. The blocking corresponds
 * to the distribution of the dependent variable vector y among
 * the processors. Each preconditioner block is generated from
 * the Jacobian of the local part (on the current processor) of a
 * given function g(t,y) approximating f(t,y). The blocks are
 * generated by a difference quotient scheme on each processor
 * independently. This scheme utilizes an assumed banded
 * structure with given half-bandwidths, mudq and mldq.
 * However, the banded Jacobian block kept by the scheme has
 * half-bandwiths mukeep and mlkeep, which may be smaller.
 *
 * Note: this preconditioner does not work for IVPs involving
 * a non-identity mass matrix.
 *
 * The user's calling program should have the following form:
 *
 *   #include <nvector_parallel.h>
 *   #include <arkode/arkode_spils.h>
 *   #include <arkode/arkode_bbdpre.h>
 *   ...
 *   void *arkode_mem;
 *   ...
 *   Set y0
 *   ...
 *   SUNLinearSolver LS = SUNSPBCGS(y0, pretype, maxl);
 *     -or-
 *   SUNLinearSolver LS = SUNSPFGMR(y0, pretype, maxl);
 *     -or-
 *   SUNLinearSolver LS = SUNSPGMR(y0, pretype, maxl);
 *     -or-
 *   SUNLinearSolver LS = SUNSPTFQMR(y0, pretype, maxl);
 *     -or-
 *   SUNLinearSolver LS = SUNPCG(y0, pretype, maxl);
 *   ...
 *   arkode_mem = ARKodeCreate();
 *   ier = ARKodeInit(...);
 *   ...
 *   ier = ARKSpilsSetLinearSolver(arkode_mem, LS);
 *   ...
 *   flag = ARKBBDPrecInit(arkode_mem, Nlocal, mudq, mldq,
 *                         mukeep, mlkeep, dqrely, gloc, cfn);
 *   ...
 *   ier = ARKode(...);
 *   ...
 *   Free y0
 *   ...
 *   ARKodeFree(&arkode_mem);
 *   ...
 *   SUNLinSolFree(LS);
 *   ...
 * 
 * The user-supplied routines required are:
 *
 *   fi   = function defining the implicit ODE right-hand side fi(t,y).
 *
 *   gloc = function defining the approximation g(t,y).
 *
 *   cfn  = function to perform communication need for gloc.
 *
 * Notes:
 *
 * 1) This header file is included by the user for the definition
 *    of the ARKBBDData type and for needed function prototypes.
 *
 * 2) The ARKBBDPrecInit call includes half-bandwiths mudq and mldq
 *    to be used in the difference quotient calculation of the
 *    approximate Jacobian. They need not be the true
 *    half-bandwidths of the Jacobian of the local block of g,
 *    when smaller values may provide a greater efficiency.
 *    Also, the half-bandwidths mukeep and mlkeep of the retained
 *    banded approximate Jacobian block may be even smaller,
 *    to reduce storage and computation costs further.
 *    For all four half-bandwidths, the values need not be the
 *    same on every processor.
 *
 * 3) The actual name of the user's fi function is passed to
 *    ARKodeInit, and the names of the user's gloc and cfn
 *    functions are passed to ARKBBDPrecInit.
 *
 * 4) The pointer to the user-defined data block user_data, which is
 *    set through ARKodeSetUserData is also available to the user in
 *    gloc and cfn.
 *
 * 5) Optional outputs specific to this module are available by
 *    way of routines listed below. These include work space sizes
 *    and the cumulative number of gloc calls. The costs
 *    associated with this module also include nsetups banded LU
 *    factorizations, nlinsetups cfn calls, and npsolves banded
 *    backsolve calls, where nlinsetups and npsolves are
 *    integrator/ARKSPILS optional outputs.
 *--------------------------------------------------------------*/

#ifndef _ARKBBDPRE_H
#define _ARKBBDPRE_H

#include <sundials/sundials_nvector.h>

#ifdef __cplusplus  /* wrapper to enable C++ usage */
extern "C" {
#endif

/*---------------------------------------------------------------
  Type: ARKLocalFn

  The user must supply a function g(t,y) which approximates the
  implicit right-hand side function fi for the system 
    My'=fe(t,y)+fi(t,y), 
  and which is computed locally (without interprocess 
  communication).  (The case where g is mathematically identical 
  to fi is allowed.)  The implementation of this function must 
  have type ARKLocalFn.

  This function takes as input the local vector size Nlocal, the
  independent variable value t, the local real dependent
  variable vector y, and a pointer to the user-defined data
  block user_data. It is to compute the local part of g(t,y) and
  store this in the vector g.
  (Allocation of memory for y and g is handled within the
  preconditioner module.)
  The user_data parameter is the same as that specified by the 
  user through the ARKodeSetUserData routine.

  An ARKLocalFn should return 0 if successful, a positive value 
  if a recoverable error occurred, and a negative value if an 
  unrecoverable error occurred.
  ---------------------------------------------------------------*/
typedef int (*ARKLocalFn)(sunindextype Nlocal, realtype t, 
                          N_Vector y, N_Vector g, void *user_data);


/*---------------------------------------------------------------
  Type: ARKCommFn

  The user may supply a function of type ARKCommFn which performs
  all interprocess communication necessary to evaluate the
  approximate right-hand side function described above.

  This function takes as input the local vector size Nlocal,
  the independent variable value t, the dependent variable
  vector y, and a pointer to the user-defined data block 
  user_data. The user_data parameter is the same as that 
  specified by the user through the ARKodeSetUserData routine. 
  The ARKCommFn cfn is expected to save communicated data in 
  space defined within the structure user_data. 
  Note: An ARKCommFn cfn does not have a return value.

  Each call to the ARKCommFn cfn is preceded by a call to the
  ARKRhsFn fi with the same (t,y) arguments. Thus cfn can omit 
  any communications done by fi if relevant to the evaluation of 
  g.  If all necessary communication was done by fi, the user 
  can pass NULL for cfn in ARKBBDPrecInit (see below).

  An ARKCommFn should return 0 if successful, a positive value 
  if a recoverable error occurred, and a negative value if an 
  unrecoverable error occurred.
  ---------------------------------------------------------------*/
typedef int (*ARKCommFn)(sunindextype Nlocal, realtype t, 
                         N_Vector y, void *user_data);


/*---------------------------------------------------------------
  ARKBBDPrecInit:

  ARKBBDPrecInit allocates and initializes the BBD preconditioner.

  The parameters of ARKBBDPrecInit are as follows:

  arkode_mem is the pointer to the integrator memory.

  Nlocal is the length of the local block of the vectors y etc.
         on the current processor.

  mudq, mldq are the upper and lower half-bandwidths to be used
             in the difference quotient computation of the local
             Jacobian block.

  mukeep, mlkeep are the upper and lower half-bandwidths of the
                 retained banded approximation to the local Jacobian
                 block.

  dqrely is an optional input. It is the relative increment
         in components of y used in the difference quotient
         approximations. To specify the default, pass 0.
         The default is dqrely = sqrt(unit roundoff).

  gloc is the name of the user-supplied function g(t,y) that
       approximates f and whose local Jacobian blocks are
       to form the preconditioner.

  cfn is the name of the user-defined function that performs
      necessary interprocess communication for the
      execution of gloc.

  The return value of ARKBBDPrecInit is one of:
    ARKSPILS_SUCCESS if no errors occurred
    ARKSPILS_MEM_NULL if the integrator memory is NULL
    ARKSPILS_LMEM_NULL if the linear solver memory is NULL
    ARKSPILS_ILL_INPUT if an input has an illegal value
    ARKSPILS_MEM_FAIL if a memory allocation request failed
  ---------------------------------------------------------------*/
SUNDIALS_EXPORT int ARKBBDPrecInit(void *arkode_mem, 
                                   sunindextype Nlocal, 
                                   sunindextype mudq, 
                                   sunindextype mldq, 
                                   sunindextype mukeep, 
                                   sunindextype mlkeep, 
                                   realtype dqrely,
                                   ARKLocalFn gloc,
                                   ARKCommFn cfn);


/*---------------------------------------------------------------
  ARKBBDPrecReInit:

  ARKBBDPrecReInit re-initializes the BBDPRE module when solving a
  sequence of problems of the same size with ARKSPILS/ARKBBDPRE 
  provided there is no change in Nlocal, mukeep, or mlkeep. After 
  solving one problem, and after calling ARKodeReInit to 
  re-initialize the integrator for a subsequent problem, call 
  ARKBBDPrecReInit.

  All arguments have the same names and meanings as those
  of ARKBBDPrecInit.

  The return value of ARKBBDPrecReInit is one of:
    ARKSPILS_SUCCESS if no errors occurred
    ARKSPILS_MEM_NULL if the integrator memory is NULL
    ARKSPILS_LMEM_NULL if the linear solver memory is NULL
    ARKSPILS_PMEM_NULL if the preconditioner memory is NULL
  ---------------------------------------------------------------*/
SUNDIALS_EXPORT int ARKBBDPrecReInit(void *arkode_mem, 
                                     sunindextype mudq, 
                                     sunindextype mldq, 
                                     realtype dqrely);


/*---------------------------------------------------------------
  BBDPRE optional output extraction routines:

  ARKBBDPrecGetWorkSpace returns the BBDPRE real and integer work 
                         space sizes.
  ARKBBDPrecGetNumGfnEvals returns the number of calls to gfn.

  The return value of ARKBBDPrecGet* is one of:
    ARKSPILS_SUCCESS if no errors occurred
    ARKSPILS_MEM_NULL if the integrator memory is NULL
    ARKSPILS_LMEM_NULL if the linear solver memory is NULL
    ARKSPILS_PMEM_NULL if the preconditioner memory is NULL
  ---------------------------------------------------------------*/

SUNDIALS_EXPORT int ARKBBDPrecGetWorkSpace(void *arkode_mem, 
                                           long int *lenrwLS, 
                                           long int *leniwLS);
SUNDIALS_EXPORT int ARKBBDPrecGetNumGfnEvals(void *arkode_mem, 
                                             long int *ngevalsBBDP);

#ifdef __cplusplus
}
#endif

#endif
