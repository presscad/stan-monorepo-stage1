/*---------------------------------------------------------------
 * Programmer(s): Daniel R. Reynolds @ SMU
 *---------------------------------------------------------------
 * LLNS/SMU Copyright Start
 * Copyright (c) 2018, Southern Methodist University and 
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
 * Header file with Butcher table IDs for built-in DIRK methods.
 *--------------------------------------------------------------*/

#ifndef _ARKODE_DIRK_TABLES_H
#define _ARKODE_DIRK_TABLES_H

#include <arkode/arkode_butcher.h>

#ifdef __cplusplus  /* wrapper to enable C++ usage */
extern "C" {
#endif

/* Butcher table accessor IDs
     ERK:    0 -  99
     DIRK: 100 - 199          */
#define SDIRK_2_1_2             100
#define BILLINGTON_3_3_2        101
#define TRBDF2_3_3_2            102
#define KVAERNO_4_2_3           103
#define ARK324L2SA_DIRK_4_2_3   104
#define CASH_5_2_4              105
#define CASH_5_3_4              106
#define SDIRK_5_3_4             107
#define KVAERNO_5_3_4           108
#define ARK436L2SA_DIRK_6_3_4   109
#define KVAERNO_7_4_5           110
#define ARK548L2SA_DIRK_8_4_5   111

/* Utility #defines to ensure valid input IDs for DIRK tables */
#define MIN_DIRK_NUM            100
#define MAX_DIRK_NUM            111

/* Accessor routine to load built-in DIRK table */  
SUNDIALS_EXPORT ARKodeButcherTable ARKodeButcherTable_LoadDIRK(int imethod);

  
#ifdef __cplusplus
}
#endif

#endif
