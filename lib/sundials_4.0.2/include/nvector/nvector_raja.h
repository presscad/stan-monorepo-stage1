/* -----------------------------------------------------------------
 * Programmer(s): Slaven Peles @ LLNL
 * -----------------------------------------------------------------
 * SUNDIALS Copyright Start
 * Copyright (c) 2002-2019, Lawrence Livermore National Security
 * and Southern Methodist University.
 * All rights reserved.
 *
 * See the top-level LICENSE and NOTICE files for details.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 * SUNDIALS Copyright End
 * -----------------------------------------------------------------
 * This is the header file for the RAJA implementation of the
 * NVECTOR module.
 *
 * Part I contains declarations specific to the RAJA
 * implementation of the supplied NVECTOR module.
 *
 * Part II contains the prototype for the constructor N_VNew_Raja
 * as well as implementation-specific prototypes for various useful
 * vector operations.
 *
 * Notes:
 *
 *   - The definition of the generic N_Vector structure can be found
 *     in the header file sundials_nvector.h.
 *
 *   - The definition of the type 'realtype' can be found in the
 *     header file sundials_types.h, and it may be changed (at the
 *     configuration stage) according to the user's needs.
 *     The sundials_types.h file also contains the definition
 *     for the type 'booleantype'.
 *
 *   - N_Vector arguments to arithmetic vector operations need not
 *     be distinct. For example, the following call:
 *
 *       N_VLinearSum_Raja(a,x,b,y,y);
 *
 *     (which stores the result of the operation a*x+b*y in y)
 *     is legal.
 * -----------------------------------------------------------------*/

#ifndef _NVECTOR_RAJA_H
#define _NVECTOR_RAJA_H

#include <stdio.h>
#include <sundials/sundials_nvector.h>
#include <sundials/sundials_config.h>

#ifdef __cplusplus  /* wrapper to enable C++ usage */
extern "C" {
#endif



/*
 * -----------------------------------------------------------------
 * PART I: RAJA implementation of N_Vector
 * -----------------------------------------------------------------
 */

/* RAJA implementation of the N_Vector 'content' structure
   contains the length of the vector, a pointer to an array
   of 'realtype' components, and a flag indicating ownership of
   the data */

struct _N_VectorContent_Raja {};

typedef struct _N_VectorContent_Raja *N_VectorContent_Raja;



/*
 * -----------------------------------------------------------------
 * PART II: functions exported by nvector_raja
 *
 * CONSTRUCTORS:
 *    N_VNew_Raja
 *    N_VNewEmpty_Raja
 *    N_VMake_Raja
 * DESTRUCTORS:
 *    N_VDestroy_Raja
 * ENABLE/DISABLE FUSED OPS:
 *    N_VEnableFusedOps_Raja
 *    N_VEnableLinearCombination_Raja
 *    N_VEnableScaleAddMulti_Raja
 *    N_VEnableDotProdMulti_Raja
 *    N_VEnableLinearSumVectorArray_Raja
 *    N_VEnableScaleVectorArray_Raja
 *    N_VEnableConstVectorArray_Raja
 *    N_VEnableWrmsNormVectorArray_Raja
 *    N_VEnableWrmsNormMaskVectorArray_Raja
 *    N_VEnableScaleAddMultiVectorArray_Raja
 *    N_VEnableLinearCombinationVectorArray_Raja
 * OTHER:
 *    N_VGetLength_Raja
 *    N_VGetHostArrayPointer_Raja
 *    N_VGetDeviceArrayPointer_Raja
 *    N_VPrint_Raja
 *    N_VPrintFile_Raja
 * -----------------------------------------------------------------
 */

/*
 * -----------------------------------------------------------------
 * Function : N_VNew_Raja
 * -----------------------------------------------------------------
 * This function creates and allocates memory for a RAJA vector on
 * a single node.
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT N_Vector N_VNew_Raja(sunindextype length);

/*
 * -----------------------------------------------------------------
 * Function : N_VNewEmpty_Raja
 * -----------------------------------------------------------------
 * This function creates a new RAJA N_Vector with an empty (NULL)
 * data array.
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT N_Vector N_VNewEmpty_Raja();

/*
 * -----------------------------------------------------------------
 * Function : N_VMake_Raja
 * -----------------------------------------------------------------
 * This function creates and an NVECTOR wrapper around a
 * user-supplied sunrajavec::Vector.
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT N_Vector N_VMake_Raja(N_VectorContent_Raja c);

/*
 * -----------------------------------------------------------------
 * Function : N_VGetLength_Raja
 * -----------------------------------------------------------------
 * This function returns the length of the vector.
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT sunindextype N_VGetLength_Raja(N_Vector v);

/*
 * -----------------------------------------------------------------
 * Function : N_VGetHostArrayPointer_Raja
 * -----------------------------------------------------------------
 * This function returns pointer to the host raw data.
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT realtype *N_VGetHostArrayPointer_Raja(N_Vector v);

/*
 * -----------------------------------------------------------------
 * Function : N_VGetDeviceArrayPointer_Raja
 * -----------------------------------------------------------------
 * This function returns pointer to the device raw data.
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT realtype *N_VGetDeviceArrayPointer_Raja(N_Vector v);

/*
 * -----------------------------------------------------------------
 * Function : N_VCopyTotDevice_Raja
 * -----------------------------------------------------------------
 * This function copies host data to the device.
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT void N_VCopyToDevice_Raja(N_Vector v);

/*
 * -----------------------------------------------------------------
 * Function : N_VCopyTotDevice_Raja
 * -----------------------------------------------------------------
 * This function copies vector data from the device to the host.
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT void N_VCopyFromDevice_Raja(N_Vector v);

/*
 * -----------------------------------------------------------------
 * Function : N_VPrint_Raja
 * -----------------------------------------------------------------
 * This function prints the content of a RAJA vector to stdout.
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT void N_VPrint_Raja(N_Vector v);

/*
 * -----------------------------------------------------------------
 * Function : N_VPrintFile_Raja
 * -----------------------------------------------------------------
 * This function prints the content of a RAJA vector to outfile.
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT void N_VPrintFile_Raja(N_Vector v, FILE *outfile);

/*
 * -----------------------------------------------------------------
 * RAJA implementations of various useful vector operations
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT N_Vector_ID N_VGetVectorID_Raja(N_Vector v);
SUNDIALS_EXPORT N_Vector N_VCloneEmpty_Raja(N_Vector w);
SUNDIALS_EXPORT N_Vector N_VClone_Raja(N_Vector w);
SUNDIALS_EXPORT void N_VDestroy_Raja(N_Vector v);
SUNDIALS_EXPORT void N_VSpace_Raja(N_Vector v, sunindextype *lrw, sunindextype *liw);
SUNDIALS_EXPORT realtype *N_VGetArrayPointer_Raja(N_Vector v);
SUNDIALS_EXPORT void N_VSetArrayPointer_Raja(realtype *v_data, N_Vector v);

/* standard vector operations */
SUNDIALS_EXPORT void N_VLinearSum_Raja(realtype a, N_Vector x, realtype b, N_Vector y, N_Vector z);
SUNDIALS_EXPORT void N_VConst_Raja(realtype c, N_Vector z);
SUNDIALS_EXPORT void N_VProd_Raja(N_Vector x, N_Vector y, N_Vector z);
SUNDIALS_EXPORT void N_VDiv_Raja(N_Vector x, N_Vector y, N_Vector z);
SUNDIALS_EXPORT void N_VScale_Raja(realtype c, N_Vector x, N_Vector z);
SUNDIALS_EXPORT void N_VAbs_Raja(N_Vector x, N_Vector z);
SUNDIALS_EXPORT void N_VInv_Raja(N_Vector x, N_Vector z);
SUNDIALS_EXPORT void N_VAddConst_Raja(N_Vector x, realtype b, N_Vector z);
SUNDIALS_EXPORT realtype N_VDotProd_Raja(N_Vector x, N_Vector y);
SUNDIALS_EXPORT realtype N_VMaxNorm_Raja(N_Vector x);
SUNDIALS_EXPORT realtype N_VWrmsNorm_Raja(N_Vector x, N_Vector w);
SUNDIALS_EXPORT realtype N_VWrmsNormMask_Raja(N_Vector x, N_Vector w, N_Vector id);
SUNDIALS_EXPORT realtype N_VMin_Raja(N_Vector x);
SUNDIALS_EXPORT realtype N_VWL2Norm_Raja(N_Vector x, N_Vector w);
SUNDIALS_EXPORT realtype N_VL1Norm_Raja(N_Vector x);
SUNDIALS_EXPORT void N_VCompare_Raja(realtype c, N_Vector x, N_Vector z);
SUNDIALS_EXPORT booleantype N_VInvTest_Raja(N_Vector x, N_Vector z);
SUNDIALS_EXPORT booleantype N_VConstrMask_Raja(N_Vector c, N_Vector x, N_Vector m);
SUNDIALS_EXPORT realtype N_VMinQuotient_Raja(N_Vector num, N_Vector denom);

/* fused vector operations */
SUNDIALS_EXPORT int N_VLinearCombination_Raja(int nvec, realtype* c, N_Vector* X,
                                              N_Vector z);
SUNDIALS_EXPORT int N_VScaleAddMulti_Raja(int nvec, realtype* c, N_Vector x,
                                          N_Vector* Y, N_Vector* Z);

/* vector array operations */
SUNDIALS_EXPORT int N_VLinearSumVectorArray_Raja(int nvec,
                                                 realtype a, N_Vector* X,
                                                 realtype b, N_Vector* Y,
                                                 N_Vector* Z);
SUNDIALS_EXPORT int N_VScaleVectorArray_Raja(int nvec, realtype* c, N_Vector* X,
                                             N_Vector* Z);
SUNDIALS_EXPORT int N_VConstVectorArray_Raja(int nvec, realtype c, N_Vector* Z);
SUNDIALS_EXPORT int N_VScaleAddMultiVectorArray_Raja(int nvec, int nsum,
                                                     realtype* a,
                                                     N_Vector* X, N_Vector** Y,
                                                     N_Vector** Z);
SUNDIALS_EXPORT int N_VLinearCombinationVectorArray_Raja(int nvec, int nsum,
                                                         realtype* c,
                                                         N_Vector** X,
                                                         N_Vector* Z);


/*
 * -----------------------------------------------------------------
 * Enable / disable fused vector operations
 * -----------------------------------------------------------------
 */

SUNDIALS_EXPORT int N_VEnableFusedOps_Raja(N_Vector v, booleantype tf);

SUNDIALS_EXPORT int N_VEnableLinearCombination_Raja(N_Vector v, booleantype tf);
SUNDIALS_EXPORT int N_VEnableScaleAddMulti_Raja(N_Vector v, booleantype tf);

SUNDIALS_EXPORT int N_VEnableLinearSumVectorArray_Raja(N_Vector v, booleantype tf);
SUNDIALS_EXPORT int N_VEnableScaleVectorArray_Raja(N_Vector v, booleantype tf);
SUNDIALS_EXPORT int N_VEnableConstVectorArray_Raja(N_Vector v, booleantype tf);
SUNDIALS_EXPORT int N_VEnableScaleAddMultiVectorArray_Raja(N_Vector v, booleantype tf);
SUNDIALS_EXPORT int N_VEnableLinearCombinationVectorArray_Raja(N_Vector v, booleantype tf);

#ifdef __cplusplus
}
#endif

#endif
