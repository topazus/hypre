/*--------------------------------------------------------------------------
 * Author:        Andy Cleary
 *                Centre for Applied Scientific Computing
 *                Lawrence Livermore Labs
 * Revision History:
 *  5-22-97: AJC. Original Version.
 *--------------------------------------------------------------------------*/


#define INCFACTFact

/*****************************************************************************
 * C to Fortran interfacing macros
 *****************************************************************************/

/*****************************************************************************
 * C routine would use this macro to call "incfactt_driver.f" :
 *
 *  CALL_INCFACTT_DRIVER(n, nnz,
 *                   ia, ja, a,
 *                   ipar, rpar,
 *                   lenpmx,
#ifdef ILUFact
 *                   plu, jlu, ju, perm, qperm, rscale, cscale,
#elif defined ICFact
 *                   plu, jlu, perm, qperm, scale,
#endif
 *                   iwork, liw, rwork, lrw,
 *                   ier_incfactt, ier_input);
 *
 *****************************************************************************/
#ifdef _CRAYMPP
#define INCFACTT_DRIVER INCFACTT_DRIVER
#else
#define INCFACTT_DRIVER incfactt_driver__
#endif

#ifdef ILUFact
#define CALL_INCFACTT_DRIVER(n, nnz,\
                         ia, ja, a, \
                         ipar, rpar,\
                         lenpmx,\
                         plu, jlu, ju, perm, qperm, rscale, cscale, \
                         iwork, liw, rwork, lrw,\
                         ier_incfactt, ier_input) \
             INCFACTT_DRIVER(&n, &nnz,\
                         ia, ja, a, \
                         ipar, rpar,\
                         &lenpmx,\
                         plu, jlu, ju, perm, qperm, rscale, cscale, \
                         iwork, &liw, rwork, &lrw,\
                         &ier_incfactt, &ier_input)
#elif defined ICFact
#define CALL_INCFACTT_DRIVER(n, nnz,\
                         ia, ja, a, \
                         ipar, rpar,\
                         lenpmx,\
                         plu, jlu, perm, qperm, scale, \
                         iwork, liw, rwork, lrw,\
                         ier_incfactt, ier_input) \
             INCFACTT_DRIVER(&n, &nnz,\
                         ia, ja, a, \
                         ipar, rpar,\
                         &lenpmx,\
                         plu, jlu, perm, qperm, scale, \
                         iwork, &liw, rwork, &lrw,\
                         &ier_incfactt, &ier_input)
#endif

void INCFACTT_DRIVER(int *n, int *nnz,
                 int *ia, int *ja, double *a,
                 int *ipar, double *rpar,
                 int *lenpmx,
                 double *plu, int *jlu, 
#ifdef ILUFact
                 int *ju, 
#endif
                 int *perm, int *qperm, 
#ifdef ILUFact
                 double *rscale, double *cscale, 
#endif
#ifdef ICFact
                 double *scale,
#endif
                 int *iwork, int *liw, double *rwork, int *lrw,
                 int *ier_incfactt, int *ier_input);



/*****************************************************************************
 * C routine would use this macro to call "ksp_driver.f" :
 *
 *  CALL_KSP_DRIVER(n, nnz,
 *                   ia, ja, a, rhs, sol,
 *                   ipar, rpar,
 *                   lenpmx,
#ifdef ILUFact
 *                   plu, jlu, ju, perm, qperm, rscale, cscale,
#elif defined ICFact
 *                   plu, jlu, perm, qperm, scale,
#endif
 *                   rwork, lrw,
 *                   ier_ksp, ier_input);
 *
 *****************************************************************************/
#ifdef _CRAYMPP
#define KSP_DRIVER KSP_DRIVER
#else
#define KSP_DRIVER ksp_driver__
#endif

#ifdef ILUFact
#define CALL_KSP_DRIVER(n, nnz,\
                         ia, ja, a, rhs, sol,\
                         ipar, rpar,\
                         lenpmx,\
                         plu, jlu, ju, perm, qperm, rscale, cscale, \
                         rwork, lrw,\
                         ier_ksp, ier_input) \
             KSP_DRIVER(&n, &nnz,\
                         ia, ja, a, rhs, sol,\
                         ipar, rpar,\
                         &lenpmx,\
                         plu, jlu, ju, perm, qperm, rscale, cscale, \
                         rwork, &lrw,\
                         &ier_ksp, &ier_input)
#elif defined ICFact
#define CALL_KSP_DRIVER(n, nnz,\
                         ia, ja, a, rhs, sol,\
                         ipar, rpar,\
                         lenpmx,\
                         plu, jlu, perm, qperm, scale, \
                         rwork, lrw,\
                         ier_ksp, ier_input) \
             KSP_DRIVER(&n, &nnz,\
                         ia, ja, a, rhs, sol,\
                         ipar, rpar,\
                         &lenpmx,\
                         plu, jlu, perm, qperm, scale, \
                         rwork, &lrw,\
                         &ier_ksp, &ier_input)
#endif

void KSP_DRIVER(int *n, int *nnz,
                 int *ia, int *ja, double *a, double *rhs, double *sol,
                 int *ipar, double *rpar,
                 int *lenpmx,
                 double *plu, int *jlu, 
#ifdef ILUFact
                 int *ju,
#endif 
                 int *perm, int *qperm, 
#ifdef ILUFact
                 double *rscale, double *cscale,
#endif 
#ifdef ICFact
                 double *scale,
#endif 
                 double *rwork, int *lrw,
                 int *ier_ksp, int *ier_input);


/*****************************************************************************
 * C routine would use this macro to call "dvperm" :
 *
 *  CALL_DVPERM(n, x, perm);
 *
 *****************************************************************************/
#ifdef _CRAYMPP
#define DVPERM DVPERM
#else
#define DVPERM dvperm_
#endif

#define CALL_DVPERM(n, x, perm) \
             DVPERM(&n, x, perm)

void DVPERM(int *n, double *x, int *perm);

/*****************************************************************************
 * C routine would use this macro to call "csrssr" :
 *
 *  CALL_CSRSSR(n, a, ja, ia, nzmax, ao, jao, iao, ierr);
 *
 *****************************************************************************/
#ifdef _CRAYMPP
#define CSRSSR CSRSSR
#else
#define CSRSSR csrssr_
#endif

#define CALL_CSRSSR(n, a, ja, ia, nzmax, ao, jao, iao, ierr ) \
             CSRSSR(&n, a, ja, ia, &nzmax, ao, jao, iao, &ierr )

void CSRSSR(int *n, double *a, int *ja, int *ia, int *nzmax,
            double *ao, int *jao, int *iao, int *ierr );
