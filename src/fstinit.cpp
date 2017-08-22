/*
  fst - An R-package for ultra fast storage and retrieval of datasets.
  Header File
  Copyright (C) 2017, Mark AJ Klik

  BSD 2-Clause License (http://www.opensource.org/licenses/bsd-license.php)

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are
  met:

  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.

  * Redistributions in binary form must reproduce the above
    copyright notice, this list of conditions and the following disclaimer
    in the documentation and/or other materials provided with the
    distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
    "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
    LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
    A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
    OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
    SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
    LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
    DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
    THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
    (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

  You can contact the author at :
  - fst source repository : https://github.com/fstPackage/fst
*/

#include <Rcpp.h>

#include "openmp.h"
#include "FastStore.h"
#include "fstcompress.h"


/* FIXME:
   Check these declarations against the C/Fortran source code.
*/

/* .Call calls */
// extern SEXP _fst_fstcomp(SEXP, SEXP, SEXP);
// extern SEXP _fst_fstdecomp(SEXP);
// extern SEXP _fst_fstmetadata(SEXP);
// extern SEXP _fst_fstretrieve(SEXP, SEXP, SEXP, SEXP);
// extern SEXP _fst_fststore(SEXP, SEXP, SEXP, SEXP);
// extern SEXP _fst_getnrofthreads();
// extern SEXP _fst_hasopenmp();
// extern SEXP _fst_setnrofthreads(SEXP);

static const R_CallMethodDef CallEntries[] = {
    {"_fst_fstcomp",        (DL_FUNC) &fstcomp,        3},
    {"_fst_fstdecomp",      (DL_FUNC) &fstdecomp,      1},
    {"_fst_fstmetadata",    (DL_FUNC) &fstmetadata,    1},
    {"_fst_fstretrieve",    (DL_FUNC) &fstretrieve,    4},
    {"_fst_fststore",       (DL_FUNC) &fststore,       4},
    {"_fst_getnrofthreads", (DL_FUNC) &getnrofthreads, 0},
    {"_fst_hasopenmp",      (DL_FUNC) &hasopenmp,      0},
    {"_fst_setnrofthreads", (DL_FUNC) &setnrofthreads, 1},
    {NULL, NULL, 0}
};


void R_init_fst(DllInfo *dll)
{
  R_registerRoutines(dll, NULL, CallEntries, NULL, NULL);
  R_useDynamicSymbols(dll, FALSE);

  // TODO (from data.table repository):
  // create strings in advance for speed, same techique as R_*Symbol
  // char_integer64 = PRINTNAME(install("integer64"));
  // char_ITime =     PRINTNAME(install("ITime"));
  // char_Date =      PRINTNAME(install("Date"));   // used for IDate too since IDate inherits from Date
  // char_POSIXct =   PRINTNAME(install("POSIXct"));
  // char_nanotime =  PRINTNAME(install("nanotime"));

  // if (TYPEOF(char_integer64) != CHARSXP)
  // {
  //   error("PRINTNAME(install(\"integer64\")) has returned %s not %s",
  //   type2char(TYPEOF(char_integer64)), type2char(CHARSXP));
  // }

  // create commonly used symbols, same as R_*Symbol
  // sym_sorted  = install("sorted");

  avoid_openmp_hang_within_fork();
}
