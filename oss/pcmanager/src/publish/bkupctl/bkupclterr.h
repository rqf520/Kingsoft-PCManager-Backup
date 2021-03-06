#pragma once

#include "bkerror.h"

#define BK_FACILITY_UPCLT_LOGIC         7

#define E_BKUPCLT_LOAD_VERSION_DAT      BKERR_MAKE_ERROR(BK_FACILITY_UPCLT_LOGIC, 1)
#define E_BKUPCLT_LOAD_FINDEX_DAT       BKERR_MAKE_ERROR(BK_FACILITY_UPCLT_LOGIC, 2)
#define E_BKUPCLT_INIT_PATH             BKERR_MAKE_ERROR(BK_FACILITY_UPCLT_LOGIC, 3)
#define E_BKUPCLT_FILE_HASH_CHECK       BKERR_MAKE_ERROR(BK_FACILITY_UPCLT_LOGIC, 4)
#define E_BKUPCTL_INTERRUPT             BKERR_MAKE_ERROR(BK_FACILITY_UPCLT_LOGIC, 5)