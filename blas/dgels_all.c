#include "f2c.h"

#define log10e 0.43429448190325182765

#ifdef KR_headers
double log();
double d_lg10(x) doublereal *x;
#else
/*
#undef abs
#include "math.h"
*/
double log(double); /* declaration added 2/17/00 */
double d_lg10(doublereal *x)
#endif
{
return( log10e * log(*x) );
}
#include "f2c.h"

#ifdef KR_headers
double d_sign(a,b) doublereal *a, *b;
#else
double d_sign(doublereal *a, doublereal *b)
#endif
{
double x;
x = (*a >= 0 ? *a : - *a);
return( *b >= 0 ? x : -x);
}
#include "f2c.h"

/* Subroutine */ int dgelq2_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *info)
{
/*  -- LAPACK routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    DGELQ2 computes an LQ factorization of a real m by n matrix A:   
    A = L * Q.   

    Arguments   
    =========   

    M       (input) INTEGER   
            The number of rows of the matrix A.  M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix A.  N >= 0.   

    A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)   
            On entry, the m by n matrix A.   
            On exit, the elements on and below the diagonal of the array 
  
            contain the m by min(m,n) lower trapezoidal matrix L (L is   
            lower triangular if m <= n); the elements above the diagonal, 
  
            with the array TAU, represent the orthogonal matrix Q as a   
            product of elementary reflectors (see Further Details).   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,M).   

    TAU     (output) DOUBLE PRECISION array, dimension (min(M,N))   
            The scalar factors of the elementary reflectors (see Further 
  
            Details).   

    WORK    (workspace) DOUBLE PRECISION array, dimension (M)   

    INFO    (output) INTEGER   
            = 0: successful exit   
            < 0: if INFO = -i, the i-th argument had an illegal value   

    Further Details   
    ===============   

    The matrix Q is represented as a product of elementary reflectors   

       Q = H(k) . . . H(2) H(1), where k = min(m,n).   

    Each H(i) has the form   

       H(i) = I - tau * v * v'   

    where tau is a real scalar, and v is a real vector with   
    v(1:i-1) = 0 and v(i) = 1; v(i+1:n) is stored on exit in A(i,i+1:n), 
  
    and tau in TAU(i).   

    ===================================================================== 
  


       Test the input arguments   

    
   Parameter adjustments   
       Function Body */
    /* System generated locals */
    integer i__1, i__2, i__3;
    /* Local variables */
    static integer i, k;
    extern /* Subroutine */ int dlarf_(char *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, integer *, 
	    doublereal *), dlarfg_(integer *, doublereal *, 
	    doublereal *, integer *, doublereal *), xerbla_(char *, integer *);
    static doublereal aii;


#define TAU(I) tau[(I)-1]
#define WORK(I) work[(I)-1]

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]

    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGELQ2", &i__1);
	return 0;
    }

    k = min(*m,*n);

    i__1 = k;
    for (i = 1; i <= k; ++i) {

/*        Generate elementary reflector H(i) to annihilate A(i,i+1:n) 
*/

	i__2 = *n - i + 1;
/* Computing MIN */
	i__3 = i + 1;
	dlarfg_(&i__2, &A(i,i), &A(i,min(i+1,*n)), lda,
		 &TAU(i));
	if (i < *m) {

/*           Apply H(i) to A(i+1:m,i:n) from the right */

	    aii = A(i,i);
	    A(i,i) = 1.;
	    i__2 = *m - i;
	    i__3 = *n - i + 1;
	    dlarf_("Right", &i__2, &i__3, &A(i,i), lda, &TAU(i), &
		    A(i+1,i), lda, &WORK(1));
	    A(i,i) = aii;
	}
/* L10: */
    }
    return 0;

/*     End of DGELQ2 */

} /* dgelq2_ */

#include "f2c.h"

/* Subroutine */ int dgelqf_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *lwork, integer *info)
{
/*  -- LAPACK routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    DGELQF computes an LQ factorization of a real M-by-N matrix A:   
    A = L * Q.   

    Arguments   
    =========   

    M       (input) INTEGER   
            The number of rows of the matrix A.  M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix A.  N >= 0.   

    A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)   
            On entry, the M-by-N matrix A.   
            On exit, the elements on and below the diagonal of the array 
  
            contain the m-by-min(m,n) lower trapezoidal matrix L (L is   
            lower triangular if m <= n); the elements above the diagonal, 
  
            with the array TAU, represent the orthogonal matrix Q as a   
            product of elementary reflectors (see Further Details).   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,M).   

    TAU     (output) DOUBLE PRECISION array, dimension (min(M,N))   
            The scalar factors of the elementary reflectors (see Further 
  
            Details).   

    WORK    (workspace/output) DOUBLE PRECISION array, dimension (LWORK) 
  
            On exit, if INFO = 0, WORK(1) returns the optimal LWORK.   

    LWORK   (input) INTEGER   
            The dimension of the array WORK.  LWORK >= max(1,M).   
            For optimum performance LWORK >= M*NB, where NB is the   
            optimal blocksize.   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value   

    Further Details   
    ===============   

    The matrix Q is represented as a product of elementary reflectors   

       Q = H(k) . . . H(2) H(1), where k = min(m,n).   

    Each H(i) has the form   

       H(i) = I - tau * v * v'   

    where tau is a real scalar, and v is a real vector with   
    v(1:i-1) = 0 and v(i) = 1; v(i+1:n) is stored on exit in A(i,i+1:n), 
  
    and tau in TAU(i).   

    ===================================================================== 
  


       Test the input arguments   

    
   Parameter adjustments   
       Function Body */
    /* Table of constant values */
    static integer c__1 = 1;
    static integer c_n1 = -1;
    static integer c__3 = 3;
    static integer c__2 = 2;
    
    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    /* Local variables */
    static integer i, k, nbmin, iinfo;
    extern /* Subroutine */ int dgelq2_(integer *, integer *, doublereal *, 
	    integer *, doublereal *, doublereal *, integer *);
    static integer ib, nb;
    extern /* Subroutine */ int dlarfb_(char *, char *, char *, char *, 
	    integer *, integer *, integer *, doublereal *, integer *, 
	    doublereal *, integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    static integer nx;
    extern /* Subroutine */ int dlarft_(char *, char *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, integer *), xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    static integer ldwork, iws;



#define TAU(I) tau[(I)-1]
#define WORK(I) work[(I)-1]

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]

    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    } else if (*lwork < max(1,*m)) {
	*info = -7;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGELQF", &i__1);
	return 0;
    }

/*     Quick return if possible */

    k = min(*m,*n);
    if (k == 0) {
	WORK(1) = 1.;
	return 0;
    }

/*     Determine the block size. */

    nb = ilaenv_(&c__1, "DGELQF", " ", m, n, &c_n1, &c_n1, 6L, 1L);
    nbmin = 2;
    nx = 0;
    iws = *m;
    if (nb > 1 && nb < k) {

/*        Determine when to cross over from blocked to unblocked code.
   

   Computing MAX */
	i__1 = 0, i__2 = ilaenv_(&c__3, "DGELQF", " ", m, n, &c_n1, &c_n1, 6L,
		 1L);
	nx = max(i__1,i__2);
	if (nx < k) {

/*           Determine if workspace is large enough for blocked co
de. */

	    ldwork = *m;
	    iws = ldwork * nb;
	    if (*lwork < iws) {

/*              Not enough workspace to use optimal NB:  reduc
e NB and   
                determine the minimum value of NB. */

		nb = *lwork / ldwork;
/* Computing MAX */
		i__1 = 2, i__2 = ilaenv_(&c__2, "DGELQF", " ", m, n, &c_n1, &
			c_n1, 6L, 1L);
		nbmin = max(i__1,i__2);
	    }
	}
    }

    if (nb >= nbmin && nb < k && nx < k) {

/*        Use blocked code initially */

	i__1 = k - nx;
	i__2 = nb;
	for (i = 1; nb < 0 ? i >= k-nx : i <= k-nx; i += nb) {
/* Computing MIN */
	    i__3 = k - i + 1;
	    ib = min(i__3,nb);

/*           Compute the LQ factorization of the current block   
             A(i:i+ib-1,i:n) */

	    i__3 = *n - i + 1;
	    dgelq2_(&ib, &i__3, &A(i,i), lda, &TAU(i), &WORK(1), &
		    iinfo);
	    if (i + ib <= *m) {

/*              Form the triangular factor of the block reflec
tor   
                H = H(i) H(i+1) . . . H(i+ib-1) */

		i__3 = *n - i + 1;
		dlarft_("Forward", "Rowwise", &i__3, &ib, &A(i,i), 
			lda, &TAU(i), &WORK(1), &ldwork);

/*              Apply H to A(i+ib:m,i:n) from the right */

		i__3 = *m - i - ib + 1;
		i__4 = *n - i + 1;
		dlarfb_("Right", "No transpose", "Forward", "Rowwise", &i__3, 
			&i__4, &ib, &A(i,i), lda, &WORK(1), &
			ldwork, &A(i+ib,i), lda, &WORK(ib + 1), &
			ldwork);
	    }
/* L10: */
	}
    } else {
	i = 1;
    }

/*     Use unblocked code to factor the last or only block. */

    if (i <= k) {
	i__2 = *m - i + 1;
	i__1 = *n - i + 1;
	dgelq2_(&i__2, &i__1, &A(i,i), lda, &TAU(i), &WORK(1), &
		iinfo);
    }

    WORK(1) = (doublereal) iws;
    return 0;

/*     End of DGELQF */

} /* dgelqf_ */

#include "f2c.h"

/* Subroutine */ int dgels_(char *trans, integer *m, integer *n, integer *
	nrhs, doublereal *a, integer *lda, doublereal *b, integer *ldb, 
	doublereal *work, integer *lwork, integer *info)
{
/*  -- LAPACK driver routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    DGELS solves overdetermined or underdetermined real linear systems   
    involving an M-by-N matrix A, or its transpose, using a QR or LQ   
    factorization of A.  It is assumed that A has full rank.   

    The following options are provided:   

    1. If TRANS = 'N' and m >= n:  find the least squares solution of   
       an overdetermined system, i.e., solve the least squares problem   
                    minimize || B - A*X ||.   

    2. If TRANS = 'N' and m < n:  find the minimum norm solution of   
       an underdetermined system A * X = B.   

    3. If TRANS = 'T' and m >= n:  find the minimum norm solution of   
       an undetermined system A**T * X = B.   

    4. If TRANS = 'T' and m < n:  find the least squares solution of   
       an overdetermined system, i.e., solve the least squares problem   
                    minimize || B - A**T * X ||.   

    Several right hand side vectors b and solution vectors x can be   
    handled in a single call; they are stored as the columns of the   
    M-by-NRHS right hand side matrix B and the N-by-NRHS solution   
    matrix X.   

    Arguments   
    =========   

    TRANS   (input) CHARACTER   
            = 'N': the linear system involves A;   
            = 'T': the linear system involves A**T.   

    M       (input) INTEGER   
            The number of rows of the matrix A.  M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix A.  N >= 0.   

    NRHS    (input) INTEGER   
            The number of right hand sides, i.e., the number of   
            columns of the matrices B and X. NRHS >=0.   

    A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)   
            On entry, the M-by-N matrix A.   
            On exit,   
              if M >= N, A is overwritten by details of its QR   
                         factorization as returned by DGEQRF;   
              if M <  N, A is overwritten by details of its LQ   
                         factorization as returned by DGELQF.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,M).   

    B       (input/output) DOUBLE PRECISION array, dimension (LDB,NRHS)   
            On entry, the matrix B of right hand side vectors, stored   
            columnwise; B is M-by-NRHS if TRANS = 'N', or N-by-NRHS   
            if TRANS = 'T'.   
            On exit, B is overwritten by the solution vectors, stored   
            columnwise:   
            if TRANS = 'N' and m >= n, rows 1 to n of B contain the least 
  
            squares solution vectors; the residual sum of squares for the 
  
            solution in each column is given by the sum of squares of   
            elements N+1 to M in that column;   
            if TRANS = 'N' and m < n, rows 1 to N of B contain the   
            minimum norm solution vectors;   
            if TRANS = 'T' and m >= n, rows 1 to M of B contain the   
            minimum norm solution vectors;   
            if TRANS = 'T' and m < n, rows 1 to M of B contain the   
            least squares solution vectors; the residual sum of squares   
            for the solution in each column is given by the sum of   
            squares of elements M+1 to N in that column.   

    LDB     (input) INTEGER   
            The leading dimension of the array B. LDB >= MAX(1,M,N).   

    WORK    (workspace/output) DOUBLE PRECISION array, dimension (LWORK) 
  
            On exit, if INFO = 0, WORK(1) returns the optimal LWORK.   

    LWORK   (input) INTEGER   
            The dimension of the array WORK.   
            LWORK >= min(M,N) + MAX(1,M,N,NRHS).   
            For optimal performance,   
            LWORK >= min(M,N) + MAX(1,M,N,NRHS) * NB   
            where NB is the optimum block size.   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value   

    ===================================================================== 
  


       Test the input arguments.   

    
   Parameter adjustments   
       Function Body */
    /* Table of constant values */
    static integer c__1 = 1;
    static integer c_n1 = -1;
    static doublereal c_b33 = 0.;
    static integer c__0 = 0;
    static doublereal c_b61 = 1.;
    
    /* System generated locals */
    integer i__1, i__2, i__3;
    /* Local variables */
    static doublereal anrm, bnrm;
    static integer brow;
    static logical tpsd;
    static integer i, j, iascl, ibscl;
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int dtrsm_(char *, char *, char *, char *, 
	    integer *, integer *, doublereal *, doublereal *, integer *, 
	    doublereal *, integer *);
    static integer wsize;
    static doublereal rwork[1];
    extern /* Subroutine */ int dlabad_(doublereal *, doublereal *);
    static integer nb;
    extern doublereal dlamch_(char *), dlange_(char *, integer *, 
	    integer *, doublereal *, integer *, doublereal *);
    static integer mn;
    extern /* Subroutine */ int dgelqf_(integer *, integer *, doublereal *, 
	    integer *, doublereal *, doublereal *, integer *, integer *), 
	    dlascl_(char *, integer *, integer *, doublereal *, doublereal *, 
	    integer *, integer *, doublereal *, integer *, integer *),
	     dgeqrf_(integer *, integer *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *, integer *), dlaset_(char *,
	     integer *, integer *, doublereal *, doublereal *, doublereal *, 
	    integer *), xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    static integer scllen;
    static doublereal bignum;
    extern /* Subroutine */ int dormlq_(char *, char *, integer *, integer *, 
	    integer *, doublereal *, integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *, integer *), 
	    dormqr_(char *, char *, integer *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, integer *, 
	    doublereal *, integer *, integer *);
    static doublereal smlnum;



#define RWORK(I) rwork[(I)]
#define WORK(I) work[(I)-1]

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]
#define B(I,J) b[(I)-1 + ((J)-1)* ( *ldb)]

    *info = 0;
    mn = min(*m,*n);
    if (! (lsame_(trans, "N") || lsame_(trans, "T"))) {
	*info = -1;
    } else if (*m < 0) {
	*info = -2;
    } else if (*n < 0) {
	*info = -3;
    } else if (*nrhs < 0) {
	*info = -4;
    } else if (*lda < max(1,*m)) {
	*info = -6;
    } else /* if(complicated condition) */ {
/* Computing MAX */
	i__1 = max(1,*m);
	if (*ldb < max(i__1,*n)) {
	    *info = -8;
	} else /* if(complicated condition) */ {
/* Computing MAX   
   Computing MAX */
	    i__3 = max(*m,*n);
	    i__1 = 1, i__2 = mn + max(i__3,*nrhs);
	    if (*lwork < max(i__1,i__2)) {
		*info = -10;
	    }
	}
    }

/*     Figure out optimal block size */

    if (*info == 0 || *info == -10) {

	tpsd = TRUE_;
	if (lsame_(trans, "N")) {
	    tpsd = FALSE_;
	}

	if (*m >= *n) {
	    nb = ilaenv_(&c__1, "DGEQRF", " ", m, n, &c_n1, &c_n1, 6L, 1L);
	    if (tpsd) {
/* Computing MAX */
		i__1 = nb, i__2 = ilaenv_(&c__1, "DORMQR", "LN", m, nrhs, n, &
			c_n1, 6L, 2L);
		nb = max(i__1,i__2);
	    } else {
/* Computing MAX */
		i__1 = nb, i__2 = ilaenv_(&c__1, "DORMQR", "LT", m, nrhs, n, &
			c_n1, 6L, 2L);
		nb = max(i__1,i__2);
	    }
	} else {
	    nb = ilaenv_(&c__1, "DGELQF", " ", m, n, &c_n1, &c_n1, 6L, 1L);
	    if (tpsd) {
/* Computing MAX */
		i__1 = nb, i__2 = ilaenv_(&c__1, "DORMLQ", "LT", n, nrhs, m, &
			c_n1, 6L, 2L);
		nb = max(i__1,i__2);
	    } else {
/* Computing MAX */
		i__1 = nb, i__2 = ilaenv_(&c__1, "DORMLQ", "LN", n, nrhs, m, &
			c_n1, 6L, 2L);
		nb = max(i__1,i__2);
	    }
	}

/* Computing MAX */
	i__1 = max(*m,*n);
	wsize = mn + max(i__1,*nrhs) * nb;
	WORK(1) = (doublereal) wsize;

    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGELS ", &i__1);
	return 0;
    }

/*     Quick return if possible   

   Computing MIN */
    i__1 = min(*m,*n);
    if (min(i__1,*nrhs) == 0) {
	i__1 = max(*m,*n);
	dlaset_("Full", &i__1, nrhs, &c_b33, &c_b33, &B(1,1), ldb);
	return 0;
    }

/*     Get machine parameters */

    smlnum = dlamch_("S") / dlamch_("P");
    bignum = 1. / smlnum;
    dlabad_(&smlnum, &bignum);

/*     Scale A, B if max element outside range [SMLNUM,BIGNUM] */

    anrm = dlange_("M", m, n, &A(1,1), lda, rwork);
    iascl = 0;
    if (anrm > 0. && anrm < smlnum) {

/*        Scale matrix norm up to SMLNUM */

	dlascl_("G", &c__0, &c__0, &anrm, &smlnum, m, n, &A(1,1), lda, 
		info);
	iascl = 1;
    } else if (anrm > bignum) {

/*        Scale matrix norm down to BIGNUM */

	dlascl_("G", &c__0, &c__0, &anrm, &bignum, m, n, &A(1,1), lda, 
		info);
	iascl = 2;
    } else if (anrm == 0.) {

/*        Matrix all zero. Return zero solution. */

	i__1 = max(*m,*n);
	dlaset_("F", &i__1, nrhs, &c_b33, &c_b33, &B(1,1), ldb);
	goto L50;
    }

    brow = *m;
    if (tpsd) {
	brow = *n;
    }
    bnrm = dlange_("M", &brow, nrhs, &B(1,1), ldb, rwork);
    ibscl = 0;
    if (bnrm > 0. && bnrm < smlnum) {

/*        Scale matrix norm up to SMLNUM */

	dlascl_("G", &c__0, &c__0, &bnrm, &smlnum, &brow, nrhs, &B(1,1), 
		ldb, info);
	ibscl = 1;
    } else if (bnrm > bignum) {

/*        Scale matrix norm down to BIGNUM */

	dlascl_("G", &c__0, &c__0, &bnrm, &bignum, &brow, nrhs, &B(1,1), 
		ldb, info);
	ibscl = 2;
    }

    if (*m >= *n) {

/*        compute QR factorization of A */

	i__1 = *lwork - mn;
	dgeqrf_(m, n, &A(1,1), lda, &WORK(1), &WORK(mn + 1), &i__1, info)
		;

/*        workspace at least N, optimally N*NB */

	if (! tpsd) {

/*           Least-Squares Problem min || A * X - B ||   

             B(1:M,1:NRHS) := Q' * B(1:M,1:NRHS) */

	    i__1 = *lwork - mn;
	    dormqr_("Left", "Transpose", m, nrhs, n, &A(1,1), lda, &WORK(
		    1), &B(1,1), ldb, &WORK(mn + 1), &i__1, info)
		    ;

/*           workspace at least NRHS, optimally NRHS*NB   

             B(1:N,1:NRHS) := inv(R) * B(1:N,1:NRHS) */

	    dtrsm_("Left", "Upper", "No transpose", "Non-unit", n, nrhs, &
		    c_b61, &A(1,1), lda, &B(1,1), ldb);

	    scllen = *n;

	} else {

/*           Overdetermined system of equations A' * X = B   

             B(1:N,1:NRHS) := inv(R') * B(1:N,1:NRHS) */

	    dtrsm_("Left", "Upper", "Transpose", "Non-unit", n, nrhs, &c_b61, 
		    &A(1,1), lda, &B(1,1), ldb);

/*           B(N+1:M,1:NRHS) = ZERO */

	    i__1 = *nrhs;
	    for (j = 1; j <= *nrhs; ++j) {
		i__2 = *m;
		for (i = *n + 1; i <= *m; ++i) {
		    B(i,j) = 0.;
/* L10: */
		}
/* L20: */
	    }

/*           B(1:M,1:NRHS) := Q(1:N,:) * B(1:N,1:NRHS) */

	    i__1 = *lwork - mn;
	    dormqr_("Left", "No transpose", m, nrhs, n, &A(1,1), lda, &
		    WORK(1), &B(1,1), ldb, &WORK(mn + 1), &i__1, info);

/*           workspace at least NRHS, optimally NRHS*NB */

	    scllen = *m;

	}

    } else {

/*        Compute LQ factorization of A */

	i__1 = *lwork - mn;
	dgelqf_(m, n, &A(1,1), lda, &WORK(1), &WORK(mn + 1), &i__1, info)
		;

/*        workspace at least M, optimally M*NB. */

	if (! tpsd) {

/*           underdetermined system of equations A * X = B   

             B(1:M,1:NRHS) := inv(L) * B(1:M,1:NRHS) */

	    dtrsm_("Left", "Lower", "No transpose", "Non-unit", m, nrhs, &
		    c_b61, &A(1,1), lda, &B(1,1), ldb);

/*           B(M+1:N,1:NRHS) = 0 */

	    i__1 = *nrhs;
	    for (j = 1; j <= *nrhs; ++j) {
		i__2 = *n;
		for (i = *m + 1; i <= *n; ++i) {
		    B(i,j) = 0.;
/* L30: */
		}
/* L40: */
	    }

/*           B(1:N,1:NRHS) := Q(1:N,:)' * B(1:M,1:NRHS) */

	    i__1 = *lwork - mn;
	    dormlq_("Left", "Transpose", n, nrhs, m, &A(1,1), lda, &WORK(
		    1), &B(1,1), ldb, &WORK(mn + 1), &i__1, info)
		    ;

/*           workspace at least NRHS, optimally NRHS*NB */

	    scllen = *n;

	} else {

/*           overdetermined system min || A' * X - B ||   

             B(1:N,1:NRHS) := Q * B(1:N,1:NRHS) */

	    i__1 = *lwork - mn;
	    dormlq_("Left", "No transpose", n, nrhs, m, &A(1,1), lda, &
		    WORK(1), &B(1,1), ldb, &WORK(mn + 1), &i__1, info);

/*           workspace at least NRHS, optimally NRHS*NB   

             B(1:M,1:NRHS) := inv(L') * B(1:M,1:NRHS) */

	    dtrsm_("Left", "Lower", "Transpose", "Non-unit", m, nrhs, &c_b61, 
		    &A(1,1), lda, &B(1,1), ldb);

	    scllen = *m;

	}

    }

/*     Undo scaling */

    if (iascl == 1) {
	dlascl_("G", &c__0, &c__0, &anrm, &smlnum, &scllen, nrhs, &B(1,1)
		, ldb, info);
    } else if (iascl == 2) {
	dlascl_("G", &c__0, &c__0, &anrm, &bignum, &scllen, nrhs, &B(1,1)
		, ldb, info);
    }
    if (ibscl == 1) {
	dlascl_("G", &c__0, &c__0, &smlnum, &bnrm, &scllen, nrhs, &B(1,1)
		, ldb, info);
    } else if (ibscl == 2) {
	dlascl_("G", &c__0, &c__0, &bignum, &bnrm, &scllen, nrhs, &B(1,1)
		, ldb, info);
    }

L50:
    WORK(1) = (doublereal) wsize;

    return 0;

/*     End of DGELS */

} /* dgels_ */

#include "f2c.h"

/* Subroutine */ int dgeqr2_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *info)
{
/*  -- LAPACK routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    DGEQR2 computes a QR factorization of a real m by n matrix A:   
    A = Q * R.   

    Arguments   
    =========   

    M       (input) INTEGER   
            The number of rows of the matrix A.  M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix A.  N >= 0.   

    A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)   
            On entry, the m by n matrix A.   
            On exit, the elements on and above the diagonal of the array 
  
            contain the min(m,n) by n upper trapezoidal matrix R (R is   
            upper triangular if m >= n); the elements below the diagonal, 
  
            with the array TAU, represent the orthogonal matrix Q as a   
            product of elementary reflectors (see Further Details).   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,M).   

    TAU     (output) DOUBLE PRECISION array, dimension (min(M,N))   
            The scalar factors of the elementary reflectors (see Further 
  
            Details).   

    WORK    (workspace) DOUBLE PRECISION array, dimension (N)   

    INFO    (output) INTEGER   
            = 0: successful exit   
            < 0: if INFO = -i, the i-th argument had an illegal value   

    Further Details   
    ===============   

    The matrix Q is represented as a product of elementary reflectors   

       Q = H(1) H(2) . . . H(k), where k = min(m,n).   

    Each H(i) has the form   

       H(i) = I - tau * v * v'   

    where tau is a real scalar, and v is a real vector with   
    v(1:i-1) = 0 and v(i) = 1; v(i+1:m) is stored on exit in A(i+1:m,i), 
  
    and tau in TAU(i).   

    ===================================================================== 
  


       Test the input arguments   

    
   Parameter adjustments   
       Function Body */
    /* Table of constant values */
    static integer c__1 = 1;
    
    /* System generated locals */
    integer i__1, i__2, i__3;
    /* Local variables */
    static integer i, k;
    extern /* Subroutine */ int dlarf_(char *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, integer *, 
	    doublereal *), dlarfg_(integer *, doublereal *, 
	    doublereal *, integer *, doublereal *), xerbla_(char *, integer *);
    static doublereal aii;



#define TAU(I) tau[(I)-1]
#define WORK(I) work[(I)-1]

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]

    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGEQR2", &i__1);
	return 0;
    }

    k = min(*m,*n);

    i__1 = k;
    for (i = 1; i <= k; ++i) {

/*        Generate elementary reflector H(i) to annihilate A(i+1:m,i) 
*/

	i__2 = *m - i + 1;
/* Computing MIN */
	i__3 = i + 1;
	dlarfg_(&i__2, &A(i,i), &A(min(i+1,*m),i), &
		c__1, &TAU(i));
	if (i < *n) {

/*           Apply H(i) to A(i:m,i+1:n) from the left */

	    aii = A(i,i);
	    A(i,i) = 1.;
	    i__2 = *m - i + 1;
	    i__3 = *n - i;
	    dlarf_("Left", &i__2, &i__3, &A(i,i), &c__1, &TAU(i), &
		    A(i,i+1), lda, &WORK(1));
	    A(i,i) = aii;
	}
/* L10: */
    }
    return 0;

/*     End of DGEQR2 */

} /* dgeqr2_ */

#include "f2c.h"

/* Subroutine */ int dgeqrf_(integer *m, integer *n, doublereal *a, integer *
	lda, doublereal *tau, doublereal *work, integer *lwork, integer *info)
{
/*  -- LAPACK routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    DGEQRF computes a QR factorization of a real M-by-N matrix A:   
    A = Q * R.   

    Arguments   
    =========   

    M       (input) INTEGER   
            The number of rows of the matrix A.  M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix A.  N >= 0.   

    A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)   
            On entry, the M-by-N matrix A.   
            On exit, the elements on and above the diagonal of the array 
  
            contain the min(M,N)-by-N upper trapezoidal matrix R (R is   
            upper triangular if m >= n); the elements below the diagonal, 
  
            with the array TAU, represent the orthogonal matrix Q as a   
            product of min(m,n) elementary reflectors (see Further   
            Details).   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,M).   

    TAU     (output) DOUBLE PRECISION array, dimension (min(M,N))   
            The scalar factors of the elementary reflectors (see Further 
  
            Details).   

    WORK    (workspace/output) DOUBLE PRECISION array, dimension (LWORK) 
  
            On exit, if INFO = 0, WORK(1) returns the optimal LWORK.   

    LWORK   (input) INTEGER   
            The dimension of the array WORK.  LWORK >= max(1,N).   
            For optimum performance LWORK >= N*NB, where NB is   
            the optimal blocksize.   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value   

    Further Details   
    ===============   

    The matrix Q is represented as a product of elementary reflectors   

       Q = H(1) H(2) . . . H(k), where k = min(m,n).   

    Each H(i) has the form   

       H(i) = I - tau * v * v'   

    where tau is a real scalar, and v is a real vector with   
    v(1:i-1) = 0 and v(i) = 1; v(i+1:m) is stored on exit in A(i+1:m,i), 
  
    and tau in TAU(i).   

    ===================================================================== 
  


       Test the input arguments   

    
   Parameter adjustments   
       Function Body */
    /* Table of constant values */
    static integer c__1 = 1;
    static integer c_n1 = -1;
    static integer c__3 = 3;
    static integer c__2 = 2;
    
    /* System generated locals */
    integer i__1, i__2, i__3, i__4;
    /* Local variables */
    static integer i, k, nbmin, iinfo;
    extern /* Subroutine */ int dgeqr2_(integer *, integer *, doublereal *, 
	    integer *, doublereal *, doublereal *, integer *);
    static integer ib, nb;
    extern /* Subroutine */ int dlarfb_(char *, char *, char *, char *, 
	    integer *, integer *, integer *, doublereal *, integer *, 
	    doublereal *, integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    static integer nx;
    extern /* Subroutine */ int dlarft_(char *, char *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, integer *), xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    static integer ldwork, iws;



#define TAU(I) tau[(I)-1]
#define WORK(I) work[(I)-1]

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]

    *info = 0;
    if (*m < 0) {
	*info = -1;
    } else if (*n < 0) {
	*info = -2;
    } else if (*lda < max(1,*m)) {
	*info = -4;
    } else if (*lwork < max(1,*n)) {
	*info = -7;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DGEQRF", &i__1);
	return 0;
    }

/*     Quick return if possible */

    k = min(*m,*n);
    if (k == 0) {
	WORK(1) = 1.;
	return 0;
    }

/*     Determine the block size. */

    nb = ilaenv_(&c__1, "DGEQRF", " ", m, n, &c_n1, &c_n1, 6L, 1L);
    nbmin = 2;
    nx = 0;
    iws = *n;
    if (nb > 1 && nb < k) {

/*        Determine when to cross over from blocked to unblocked code.
   

   Computing MAX */
	i__1 = 0, i__2 = ilaenv_(&c__3, "DGEQRF", " ", m, n, &c_n1, &c_n1, 6L,
		 1L);
	nx = max(i__1,i__2);
	if (nx < k) {

/*           Determine if workspace is large enough for blocked co
de. */

	    ldwork = *n;
	    iws = ldwork * nb;
	    if (*lwork < iws) {

/*              Not enough workspace to use optimal NB:  reduc
e NB and   
                determine the minimum value of NB. */

		nb = *lwork / ldwork;
/* Computing MAX */
		i__1 = 2, i__2 = ilaenv_(&c__2, "DGEQRF", " ", m, n, &c_n1, &
			c_n1, 6L, 1L);
		nbmin = max(i__1,i__2);
	    }
	}
    }

    if (nb >= nbmin && nb < k && nx < k) {

/*        Use blocked code initially */

	i__1 = k - nx;
	i__2 = nb;
	for (i = 1; nb < 0 ? i >= k-nx : i <= k-nx; i += nb) {
/* Computing MIN */
	    i__3 = k - i + 1;
	    ib = min(i__3,nb);

/*           Compute the QR factorization of the current block   
             A(i:m,i:i+ib-1) */

	    i__3 = *m - i + 1;
	    dgeqr2_(&i__3, &ib, &A(i,i), lda, &TAU(i), &WORK(1), &
		    iinfo);
	    if (i + ib <= *n) {

/*              Form the triangular factor of the block reflec
tor   
                H = H(i) H(i+1) . . . H(i+ib-1) */

		i__3 = *m - i + 1;
		dlarft_("Forward", "Columnwise", &i__3, &ib, &A(i,i), lda, &TAU(i), &WORK(1), &ldwork);

/*              Apply H' to A(i:m,i+ib:n) from the left */

		i__3 = *m - i + 1;
		i__4 = *n - i - ib + 1;
		dlarfb_("Left", "Transpose", "Forward", "Columnwise", &i__3, &
			i__4, &ib, &A(i,i), lda, &WORK(1), &ldwork,
			 &A(i,i+ib), lda, &WORK(ib + 1), &
			ldwork);
	    }
/* L10: */
	}
    } else {
	i = 1;
    }

/*     Use unblocked code to factor the last or only block. */

    if (i <= k) {
	i__2 = *m - i + 1;
	i__1 = *n - i + 1;
	dgeqr2_(&i__2, &i__1, &A(i,i), lda, &TAU(i), &WORK(1), &
		iinfo);
    }

    WORK(1) = (doublereal) iws;
    return 0;

/*     End of DGEQRF */

} /* dgeqrf_ */


/*  -- translated by f2c (version 19940927).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Subroutine */ int dger_(integer *m, integer *n, doublereal *alpha, 
	doublereal *x, integer *incx, doublereal *y, integer *incy, 
	doublereal *a, integer *lda)
{


    /* System generated locals */

    /* Local variables */
    static integer info;
    static doublereal temp;
    static integer i, j, ix, jy, kx;
    extern /* Subroutine */ int xerbla_(char *, integer *);


/*  Purpose   
    =======   

    DGER   performs the rank 1 operation   

       A := alpha*x*y' + A,   

    where alpha is a scalar, x is an m element vector, y is an n element 
  
    vector and A is an m by n matrix.   

    Parameters   
    ==========   

    M      - INTEGER.   
             On entry, M specifies the number of rows of the matrix A.   
             M must be at least zero.   
             Unchanged on exit.   

    N      - INTEGER.   
             On entry, N specifies the number of columns of the matrix A. 
  
             N must be at least zero.   
             Unchanged on exit.   

    ALPHA  - DOUBLE PRECISION.   
             On entry, ALPHA specifies the scalar alpha.   
             Unchanged on exit.   

    X      - DOUBLE PRECISION array of dimension at least   
             ( 1 + ( m - 1 )*abs( INCX ) ).   
             Before entry, the incremented array X must contain the m   
             element vector x.   
             Unchanged on exit.   

    INCX   - INTEGER.   
             On entry, INCX specifies the increment for the elements of   
             X. INCX must not be zero.   
             Unchanged on exit.   

    Y      - DOUBLE PRECISION array of dimension at least   
             ( 1 + ( n - 1 )*abs( INCY ) ).   
             Before entry, the incremented array Y must contain the n   
             element vector y.   
             Unchanged on exit.   

    INCY   - INTEGER.   
             On entry, INCY specifies the increment for the elements of   
             Y. INCY must not be zero.   
             Unchanged on exit.   

    A      - DOUBLE PRECISION array of DIMENSION ( LDA, n ).   
             Before entry, the leading m by n part of the array A must   
             contain the matrix of coefficients. On exit, A is   
             overwritten by the updated matrix.   

    LDA    - INTEGER.   
             On entry, LDA specifies the first dimension of A as declared 
  
             in the calling (sub) program. LDA must be at least   
             max( 1, m ).   
             Unchanged on exit.   


    Level 2 Blas routine.   

    -- Written on 22-October-1986.   
       Jack Dongarra, Argonne National Lab.   
       Jeremy Du Croz, Nag Central Office.   
       Sven Hammarling, Nag Central Office.   
       Richard Hanson, Sandia National Labs.   



       Test the input parameters.   

    
   Parameter adjustments   
       Function Body */
#define X(I) x[(I)-1]
#define Y(I) y[(I)-1]

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]

    info = 0;
    if (*m < 0) {
	info = 1;
    } else if (*n < 0) {
	info = 2;
    } else if (*incx == 0) {
	info = 5;
    } else if (*incy == 0) {
	info = 7;
    } else if (*lda < max(1,*m)) {
	info = 9;
    }
    if (info != 0) {
	xerbla_("DGER  ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*m == 0 || *n == 0 || *alpha == 0.) {
	return 0;
    }

/*     Start the operations. In this version the elements of A are   
       accessed sequentially with one pass through A. */

    if (*incy > 0) {
	jy = 1;
    } else {
	jy = 1 - (*n - 1) * *incy;
    }
    if (*incx == 1) {
	for (j = 1; j <= *n; ++j) {
	    if (Y(jy) != 0.) {
		temp = *alpha * Y(jy);
		for (i = 1; i <= *m; ++i) {
		    A(i,j) += X(i) * temp;
/* L10: */
		}
	    }
	    jy += *incy;
/* L20: */
	}
    } else {
	if (*incx > 0) {
	    kx = 1;
	} else {
	    kx = 1 - (*m - 1) * *incx;
	}
	for (j = 1; j <= *n; ++j) {
	    if (Y(jy) != 0.) {
		temp = *alpha * Y(jy);
		ix = kx;
		for (i = 1; i <= *m; ++i) {
		    A(i,j) += X(ix) * temp;
		    ix += *incx;
/* L30: */
		}
	    }
	    jy += *incy;
/* L40: */
	}
    }

    return 0;

/*     End of DGER  . */

} /* dger_ */

#include "f2c.h"

/* Subroutine */ int dlabad_(doublereal *small, doublereal *large)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1992   


    Purpose   
    =======   

    DLABAD takes as input the values computed by SLAMCH for underflow and 
  
    overflow, and returns the square root of each of these values if the 
  
    log of LARGE is sufficiently large.  This subroutine is intended to   
    identify machines with a large exponent range, such as the Crays, and 
  
    redefine the underflow and overflow limits to be the square roots of 
  
    the values computed by DLAMCH.  This subroutine is needed because   
    DLAMCH does not compensate for poor arithmetic in the upper half of   
    the exponent range, as is found on a Cray.   

    Arguments   
    =========   

    SMALL   (input/output) DOUBLE PRECISION   
            On entry, the underflow threshold as computed by DLAMCH.   
            On exit, if LOG10(LARGE) is sufficiently large, the square   
            root of SMALL, otherwise unchanged.   

    LARGE   (input/output) DOUBLE PRECISION   
            On entry, the overflow threshold as computed by DLAMCH.   
            On exit, if LOG10(LARGE) is sufficiently large, the square   
            root of LARGE, otherwise unchanged.   

    ===================================================================== 
  


       If it looks like we're on a Cray, take the square root of   
       SMALL and LARGE to avoid overflow and underflow problems. */
    /* Builtin functions */
    double d_lg10(doublereal *), sqrt(doublereal);


    if (d_lg10(large) > 2e3) {
	*small = sqrt(*small);
	*large = sqrt(*large);
    }

    return 0;

/*     End of DLABAD */

} /* dlabad_ */

#include "f2c.h"

doublereal dlamch_(char *cmach)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1992   


    Purpose   
    =======   

    DLAMCH determines double precision machine parameters.   

    Arguments   
    =========   

    CMACH   (input) CHARACTER*1   
            Specifies the value to be returned by DLAMCH:   
            = 'E' or 'e',   DLAMCH := eps   
            = 'S' or 's ,   DLAMCH := sfmin   
            = 'B' or 'b',   DLAMCH := base   
            = 'P' or 'p',   DLAMCH := eps*base   
            = 'N' or 'n',   DLAMCH := t   
            = 'R' or 'r',   DLAMCH := rnd   
            = 'M' or 'm',   DLAMCH := emin   
            = 'U' or 'u',   DLAMCH := rmin   
            = 'L' or 'l',   DLAMCH := emax   
            = 'O' or 'o',   DLAMCH := rmax   

            where   

            eps   = relative machine precision   
            sfmin = safe minimum, such that 1/sfmin does not overflow   
            base  = base of the machine   
            prec  = eps*base   
            t     = number of (base) digits in the mantissa   
            rnd   = 1.0 when rounding occurs in addition, 0.0 otherwise   
            emin  = minimum exponent before (gradual) underflow   
            rmin  = underflow threshold - base**(emin-1)   
            emax  = largest exponent before overflow   
            rmax  = overflow threshold  - (base**emax)*(1-eps)   

   ===================================================================== 
*/
/* >>Start of File<<   
       Initialized data */
    static logical first = TRUE_;
    /* System generated locals */
    integer i__1;
    doublereal ret_val;
    /* Builtin functions */
    double pow_di(doublereal *, integer *);
    /* Local variables */
    static doublereal base;
    static integer beta;
    static doublereal emin, prec, emax;
    static integer imin, imax;
    static logical lrnd;
    static doublereal rmin, rmax, t, rmach;
    extern logical lsame_(char *, char *);
    static doublereal small, sfmin;
    extern /* Subroutine */ int dlamc2_(integer *, integer *, logical *, 
	    doublereal *, integer *, doublereal *, integer *, doublereal *);
    static integer it;
    static doublereal rnd, eps;



    if (first) {
	first = FALSE_;
	dlamc2_(&beta, &it, &lrnd, &eps, &imin, &rmin, &imax, &rmax);
	base = (doublereal) beta;
	t = (doublereal) it;
	if (lrnd) {
	    rnd = 1.;
	    i__1 = 1 - it;
	    eps = pow_di(&base, &i__1) / 2;
	} else {
	    rnd = 0.;
	    i__1 = 1 - it;
	    eps = pow_di(&base, &i__1);
	}
	prec = eps * base;
	emin = (doublereal) imin;
	emax = (doublereal) imax;
	sfmin = rmin;
	small = 1. / rmax;
	if (small >= sfmin) {

/*           Use SMALL plus a bit, to avoid the possibility of rou
nding   
             causing overflow when computing  1/sfmin. */

	    sfmin = small * (eps + 1.);
	}
    }

    if (lsame_(cmach, "E")) {
	rmach = eps;
    } else if (lsame_(cmach, "S")) {
	rmach = sfmin;
    } else if (lsame_(cmach, "B")) {
	rmach = base;
    } else if (lsame_(cmach, "P")) {
	rmach = prec;
    } else if (lsame_(cmach, "N")) {
	rmach = t;
    } else if (lsame_(cmach, "R")) {
	rmach = rnd;
    } else if (lsame_(cmach, "M")) {
	rmach = emin;
    } else if (lsame_(cmach, "U")) {
	rmach = rmin;
    } else if (lsame_(cmach, "L")) {
	rmach = emax;
    } else if (lsame_(cmach, "O")) {
	rmach = rmax;
    }

    ret_val = rmach;
    return ret_val;

/*     End of DLAMCH */

} /* dlamch_ */

#include "f2c.h"

/* Subroutine */ int dlamc1_(integer *beta, integer *t, logical *rnd, logical 
	*ieee1)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1992   


    Purpose   
    =======   

    DLAMC1 determines the machine parameters given by BETA, T, RND, and   
    IEEE1.   

    Arguments   
    =========   

    BETA    (output) INTEGER   
            The base of the machine.   

    T       (output) INTEGER   
            The number of ( BETA ) digits in the mantissa.   

    RND     (output) LOGICAL   
            Specifies whether proper rounding  ( RND = .TRUE. )  or   
            chopping  ( RND = .FALSE. )  occurs in addition. This may not 
  
            be a reliable guide to the way in which the machine performs 
  
            its arithmetic.   

    IEEE1   (output) LOGICAL   
            Specifies whether rounding appears to be done in the IEEE   
            'round to nearest' style.   

    Further Details   
    ===============   

    The routine is based on the routine  ENVRON  by Malcolm and   
    incorporates suggestions by Gentleman and Marovich. See   

       Malcolm M. A. (1972) Algorithms to reveal properties of   
          floating-point arithmetic. Comms. of the ACM, 15, 949-951.   

       Gentleman W. M. and Marovich S. B. (1974) More on algorithms   
          that reveal properties of floating point arithmetic units.   
          Comms. of the ACM, 17, 276-277.   

   ===================================================================== 
*/
    /* Initialized data */
    static logical first = TRUE_;
    /* System generated locals */
    doublereal d__1, d__2;
    /* Local variables */
    static logical lrnd;
    static doublereal a, b, c, f;
    static integer lbeta;
    static doublereal savec;
    extern doublereal dlamc3_(doublereal *, doublereal *);
    static logical lieee1;
    static doublereal t1, t2;
    static integer lt;
    static doublereal one, qtr;



    if (first) {
	first = FALSE_;
	one = 1.;

/*        LBETA,  LIEEE1,  LT and  LRND  are the  local values  of  BE
TA,   
          IEEE1, T and RND.   

          Throughout this routine  we use the function  DLAMC3  to ens
ure   
          that relevant values are  stored and not held in registers, 
 or   
          are not affected by optimizers.   

          Compute  a = 2.0**m  with the  smallest positive integer m s
uch   
          that   

             fl( a + 1.0 ) = a. */

	a = 1.;
	c = 1.;

/* +       WHILE( C.EQ.ONE )LOOP */
L10:
	if (c == one) {
	    a *= 2;
	    c = dlamc3_(&a, &one);
	    d__1 = -a;
	    c = dlamc3_(&c, &d__1);
	    goto L10;
	}
/* +       END WHILE   

          Now compute  b = 2.0**m  with the smallest positive integer 
m   
          such that   

             fl( a + b ) .gt. a. */

	b = 1.;
	c = dlamc3_(&a, &b);

/* +       WHILE( C.EQ.A )LOOP */
L20:
	if (c == a) {
	    b *= 2;
	    c = dlamc3_(&a, &b);
	    goto L20;
	}
/* +       END WHILE   

          Now compute the base.  a and c  are neighbouring floating po
int   
          numbers  in the  interval  ( beta**t, beta**( t + 1 ) )  and
 so   
          their difference is beta. Adding 0.25 to c is to ensure that
 it   
          is truncated to beta and not ( beta - 1 ). */

	qtr = one / 4;
	savec = c;
	d__1 = -a;
	c = dlamc3_(&c, &d__1);
	lbeta = (integer) (c + qtr);

/*        Now determine whether rounding or chopping occurs,  by addin
g a   
          bit  less  than  beta/2  and a  bit  more  than  beta/2  to 
 a. */

	b = (doublereal) lbeta;
	d__1 = b / 2;
	d__2 = -b / 100;
	f = dlamc3_(&d__1, &d__2);
	c = dlamc3_(&f, &a);
	if (c == a) {
	    lrnd = TRUE_;
	} else {
	    lrnd = FALSE_;
	}
	d__1 = b / 2;
	d__2 = b / 100;
	f = dlamc3_(&d__1, &d__2);
	c = dlamc3_(&f, &a);
	if (lrnd && c == a) {
	    lrnd = FALSE_;
	}

/*        Try and decide whether rounding is done in the  IEEE  'round
 to   
          nearest' style. B/2 is half a unit in the last place of the 
two   
          numbers A and SAVEC. Furthermore, A is even, i.e. has last  
bit   
          zero, and SAVEC is odd. Thus adding B/2 to A should not  cha
nge   
          A, but adding B/2 to SAVEC should change SAVEC. */

	d__1 = b / 2;
	t1 = dlamc3_(&d__1, &a);
	d__1 = b / 2;
	t2 = dlamc3_(&d__1, &savec);
	lieee1 = t1 == a && t2 > savec && lrnd;

/*        Now find  the  mantissa, t.  It should  be the  integer part
 of   
          log to the base beta of a,  however it is safer to determine
  t   
          by powering.  So we find t as the smallest positive integer 
for   
          which   

             fl( beta**t + 1.0 ) = 1.0. */

	lt = 0;
	a = 1.;
	c = 1.;

/* +       WHILE( C.EQ.ONE )LOOP */
L30:
	if (c == one) {
	    ++lt;
	    a *= lbeta;
	    c = dlamc3_(&a, &one);
	    d__1 = -a;
	    c = dlamc3_(&c, &d__1);
	    goto L30;
	}
/* +       END WHILE */

    }

    *beta = lbeta;
    *t = lt;
    *rnd = lrnd;
    *ieee1 = lieee1;
    return 0;

/*     End of DLAMC1 */

} /* dlamc1_ */

#include "f2c.h"

/* Subroutine */ int dlamc2_(integer *beta, integer *t, logical *rnd, 
	doublereal *eps, integer *emin, doublereal *rmin, integer *emax, 
	doublereal *rmax)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1992   


    Purpose   
    =======   

    DLAMC2 determines the machine parameters specified in its argument   
    list.   

    Arguments   
    =========   

    BETA    (output) INTEGER   
            The base of the machine.   

    T       (output) INTEGER   
            The number of ( BETA ) digits in the mantissa.   

    RND     (output) LOGICAL   
            Specifies whether proper rounding  ( RND = .TRUE. )  or   
            chopping  ( RND = .FALSE. )  occurs in addition. This may not 
  
            be a reliable guide to the way in which the machine performs 
  
            its arithmetic.   

    EPS     (output) DOUBLE PRECISION   
            The smallest positive number such that   

               fl( 1.0 - EPS ) .LT. 1.0,   

            where fl denotes the computed value.   

    EMIN    (output) INTEGER   
            The minimum exponent before (gradual) underflow occurs.   

    RMIN    (output) DOUBLE PRECISION   
            The smallest normalized number for the machine, given by   
            BASE**( EMIN - 1 ), where  BASE  is the floating point value 
  
            of BETA.   

    EMAX    (output) INTEGER   
            The maximum exponent before overflow occurs.   

    RMAX    (output) DOUBLE PRECISION   
            The largest positive number for the machine, given by   
            BASE**EMAX * ( 1 - EPS ), where  BASE  is the floating point 
  
            value of BETA.   

    Further Details   
    ===============   

    The computation of  EPS  is based on a routine PARANOIA by   
    W. Kahan of the University of California at Berkeley.   

   ===================================================================== 
*/
    /* Table of constant values */
    
    /* Initialized data */
    static logical first = TRUE_;
    static logical iwarn = FALSE_;
    /* System generated locals */
    integer i__1;
    doublereal d__1, d__2, d__3, d__4, d__5;
    /* Builtin functions */
    double pow_di(doublereal *, integer *);
    /* Local variables */
    static logical ieee;
    static doublereal half;
    static logical lrnd;
    static doublereal leps, zero, a, b, c;
    static integer i, lbeta;
    static doublereal rbase;
    static integer lemin, lemax, gnmin;
    static doublereal small;
    static integer gpmin;
    static doublereal third, lrmin, lrmax, sixth;
    extern /* Subroutine */ int dlamc1_(integer *, integer *, logical *, 
	    logical *);
    extern doublereal dlamc3_(doublereal *, doublereal *);
    static logical lieee1;
    extern /* Subroutine */ int dlamc4_(integer *, doublereal *, integer *), 
	    dlamc5_(integer *, integer *, integer *, logical *, integer *, 
	    doublereal *);
    static integer lt, ngnmin, ngpmin;
    static doublereal one, two;



    if (first) {
	first = FALSE_;
	zero = 0.;
	one = 1.;
	two = 2.;

/*        LBETA, LT, LRND, LEPS, LEMIN and LRMIN  are the local values
 of   
          BETA, T, RND, EPS, EMIN and RMIN.   

          Throughout this routine  we use the function  DLAMC3  to ens
ure   
          that relevant values are stored  and not held in registers, 
 or   
          are not affected by optimizers.   

          DLAMC1 returns the parameters  LBETA, LT, LRND and LIEEE1. 
*/

	dlamc1_(&lbeta, &lt, &lrnd, &lieee1);

/*        Start to find EPS. */

	b = (doublereal) lbeta;
	i__1 = -lt;
	a = pow_di(&b, &i__1);
	leps = a;

/*        Try some tricks to see whether or not this is the correct  E
PS. */

	b = two / 3;
	half = one / 2;
	d__1 = -half;
	sixth = dlamc3_(&b, &d__1);
	third = dlamc3_(&sixth, &sixth);
	d__1 = -half;
	b = dlamc3_(&third, &d__1);
	b = dlamc3_(&b, &sixth);
	b = abs(b);
	if (b < leps) {
	    b = leps;
	}

	leps = 1.;

/* +       WHILE( ( LEPS.GT.B ).AND.( B.GT.ZERO ) )LOOP */
L10:
	if (leps > b && b > zero) {
	    leps = b;
	    d__1 = half * leps;
/* Computing 5th power */
	    d__3 = two, d__4 = d__3, d__3 *= d__3;
/* Computing 2nd power */
	    d__5 = leps;
	    d__2 = d__4 * (d__3 * d__3) * (d__5 * d__5);
	    c = dlamc3_(&d__1, &d__2);
	    d__1 = -c;
	    c = dlamc3_(&half, &d__1);
	    b = dlamc3_(&half, &c);
	    d__1 = -b;
	    c = dlamc3_(&half, &d__1);
	    b = dlamc3_(&half, &c);
	    goto L10;
	}
/* +       END WHILE */

	if (a < leps) {
	    leps = a;
	}

/*        Computation of EPS complete.   

          Now find  EMIN.  Let A = + or - 1, and + or - (1 + BASE**(-3
)).   
          Keep dividing  A by BETA until (gradual) underflow occurs. T
his   
          is detected when we cannot recover the previous A. */

	rbase = one / lbeta;
	small = one;
	for (i = 1; i <= 3; ++i) {
	    d__1 = small * rbase;
	    small = dlamc3_(&d__1, &zero);
/* L20: */
	}
	a = dlamc3_(&one, &small);
	dlamc4_(&ngpmin, &one, &lbeta);
	d__1 = -one;
	dlamc4_(&ngnmin, &d__1, &lbeta);
	dlamc4_(&gpmin, &a, &lbeta);
	d__1 = -a;
	dlamc4_(&gnmin, &d__1, &lbeta);
	ieee = FALSE_;

	if (ngpmin == ngnmin && gpmin == gnmin) {
	    if (ngpmin == gpmin) {
		lemin = ngpmin;
/*            ( Non twos-complement machines, no gradual under
flow;   
                e.g.,  VAX ) */
	    } else if (gpmin - ngpmin == 3) {
		lemin = ngpmin - 1 + lt;
		ieee = TRUE_;
/*            ( Non twos-complement machines, with gradual und
erflow;   
                e.g., IEEE standard followers ) */
	    } else {
		lemin = min(ngpmin,gpmin);
/*            ( A guess; no known machine ) */
		iwarn = TRUE_;
	    }

	} else if (ngpmin == gpmin && ngnmin == gnmin) {
	    if ((i__1 = ngpmin - ngnmin, abs(i__1)) == 1) {
		lemin = max(ngpmin,ngnmin);
/*            ( Twos-complement machines, no gradual underflow
;   
                e.g., CYBER 205 ) */
	    } else {
		lemin = min(ngpmin,ngnmin);
/*            ( A guess; no known machine ) */
		iwarn = TRUE_;
	    }

	} else if ((i__1 = ngpmin - ngnmin, abs(i__1)) == 1 && gpmin == gnmin)
		 {
	    if (gpmin - min(ngpmin,ngnmin) == 3) {
		lemin = max(ngpmin,ngnmin) - 1 + lt;
/*            ( Twos-complement machines with gradual underflo
w;   
                no known machine ) */
	    } else {
		lemin = min(ngpmin,ngnmin);
/*            ( A guess; no known machine ) */
		iwarn = TRUE_;
	    }

	} else {
/* Computing MIN */
	    i__1 = min(ngpmin,ngnmin), i__1 = min(i__1,gpmin);
	    lemin = min(i__1,gnmin);
/*         ( A guess; no known machine ) */
	    iwarn = TRUE_;
	}
/* **   
   Comment out this if block if EMIN is ok */
	if (iwarn) {
	    first = TRUE_;
	    printf("\n\n WARNING. The value EMIN may be incorrect:- ");
	    printf("EMIN = %8i\n",lemin);
	    printf("If, after inspection, the value EMIN looks acceptable");
            printf("please comment out \n the IF block as marked within the"); 
            printf("code of routine DLAMC2, \n otherwise supply EMIN"); 
            printf("explicitly.\n");
	}
/* **   

          Assume IEEE arithmetic if we found denormalised  numbers abo
ve,   
          or if arithmetic seems to round in the  IEEE style,  determi
ned   
          in routine DLAMC1. A true IEEE machine should have both  thi
ngs   
          true; however, faulty machines may have one or the other. */

	ieee = ieee || lieee1;

/*        Compute  RMIN by successive division by  BETA. We could comp
ute   
          RMIN as BASE**( EMIN - 1 ),  but some machines underflow dur
ing   
          this computation. */

	lrmin = 1.;
	i__1 = 1 - lemin;
	for (i = 1; i <= 1-lemin; ++i) {
	    d__1 = lrmin * rbase;
	    lrmin = dlamc3_(&d__1, &zero);
/* L30: */
	}

/*        Finally, call DLAMC5 to compute EMAX and RMAX. */

	dlamc5_(&lbeta, &lt, &lemin, &ieee, &lemax, &lrmax);
    }

    *beta = lbeta;
    *t = lt;
    *rnd = lrnd;
    *eps = leps;
    *emin = lemin;
    *rmin = lrmin;
    *emax = lemax;
    *rmax = lrmax;

    return 0;


/*     End of DLAMC2 */

} /* dlamc2_ */

#include "f2c.h"

doublereal dlamc3_(doublereal *a, doublereal *b)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1992   


    Purpose   
    =======   

    DLAMC3  is intended to force  A  and  B  to be stored prior to doing 
  
    the addition of  A  and  B ,  for use in situations where optimizers 
  
    might hold one of these in a register.   

    Arguments   
    =========   

    A, B    (input) DOUBLE PRECISION   
            The values A and B.   

   ===================================================================== 
*/
/* >>Start of File<<   
       System generated locals */
    doublereal ret_val;



    ret_val = *a + *b;

    return ret_val;

/*     End of DLAMC3 */

} /* dlamc3_ */

#include "f2c.h"

/* Subroutine */ int dlamc4_(integer *emin, doublereal *start, integer *base)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1992   


    Purpose   
    =======   

    DLAMC4 is a service routine for DLAMC2.   

    Arguments   
    =========   

    EMIN    (output) EMIN   
            The minimum exponent before (gradual) underflow, computed by 
  
            setting A = START and dividing by BASE until the previous A   
            can not be recovered.   

    START   (input) DOUBLE PRECISION   
            The starting point for determining EMIN.   

    BASE    (input) INTEGER   
            The base of the machine.   

   ===================================================================== 
*/
    /* System generated locals */
    doublereal d__1;
    /* Local variables */
    static doublereal zero, a;
    static integer i;
    static doublereal rbase, b1, b2, c1, c2, d1, d2;
    extern doublereal dlamc3_(doublereal *, doublereal *);
    static doublereal one;



    a = *start;
    one = 1.;
    rbase = one / *base;
    zero = 0.;
    *emin = 1;
    d__1 = a * rbase;
    b1 = dlamc3_(&d__1, &zero);
    c1 = a;
    c2 = a;
    d1 = a;
    d2 = a;
/* +    WHILE( ( C1.EQ.A ).AND.( C2.EQ.A ).AND.   
      $       ( D1.EQ.A ).AND.( D2.EQ.A )      )LOOP */
L10:
    if (c1 == a && c2 == a && d1 == a && d2 == a) {
	--(*emin);
	a = b1;
	d__1 = a / *base;
	b1 = dlamc3_(&d__1, &zero);
	d__1 = b1 * *base;
	c1 = dlamc3_(&d__1, &zero);
	d1 = zero;
	for (i = 1; i <= *base; ++i) {
	    d1 += b1;
/* L20: */
	}
	d__1 = a * rbase;
	b2 = dlamc3_(&d__1, &zero);
	d__1 = b2 / rbase;
	c2 = dlamc3_(&d__1, &zero);
	d2 = zero;
	for (i = 1; i <= *base; ++i) {
	    d2 += b2;
/* L30: */
	}
	goto L10;
    }
/* +    END WHILE */

    return 0;

/*     End of DLAMC4 */

} /* dlamc4_ */

#include "f2c.h"

/* Subroutine */ int dlamc5_(integer *beta, integer *p, integer *emin, 
	logical *ieee, integer *emax, doublereal *rmax)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1992   


    Purpose   
    =======   

    DLAMC5 attempts to compute RMAX, the largest machine floating-point   
    number, without overflow.  It assumes that EMAX + abs(EMIN) sum   
    approximately to a power of 2.  It will fail on machines where this   
    assumption does not hold, for example, the Cyber 205 (EMIN = -28625, 
  
    EMAX = 28718).  It will also fail if the value supplied for EMIN is   
    too large (i.e. too close to zero), probably with overflow.   

    Arguments   
    =========   

    BETA    (input) INTEGER   
            The base of floating-point arithmetic.   

    P       (input) INTEGER   
            The number of base BETA digits in the mantissa of a   
            floating-point value.   

    EMIN    (input) INTEGER   
            The minimum exponent before (gradual) underflow.   

    IEEE    (input) LOGICAL   
            A logical flag specifying whether or not the arithmetic   
            system is thought to comply with the IEEE standard.   

    EMAX    (output) INTEGER   
            The largest exponent before overflow   

    RMAX    (output) DOUBLE PRECISION   
            The largest machine floating-point number.   

   ===================================================================== 
  


       First compute LEXP and UEXP, two powers of 2 that bound   
       abs(EMIN). We then assume that EMAX + abs(EMIN) will sum   
       approximately to the bound that is closest to abs(EMIN).   
       (EMAX is the exponent of the required number RMAX). */
    /* Table of constant values */
    static doublereal c_b5 = 0.;
    
    /* System generated locals */
    doublereal d__1;
    /* Local variables */
    static integer lexp;
    static doublereal oldy;
    static integer uexp, i;
    static doublereal y, z;
    static integer nbits;
    extern doublereal dlamc3_(doublereal *, doublereal *);
    static doublereal recbas;
    static integer exbits, expsum, try__;



    lexp = 1;
    exbits = 1;
L10:
    try__ = lexp << 1;
    if (try__ <= -(*emin)) {
	lexp = try__;
	++exbits;
	goto L10;
    }
    if (lexp == -(*emin)) {
	uexp = lexp;
    } else {
	uexp = try__;
	++exbits;
    }

/*     Now -LEXP is less than or equal to EMIN, and -UEXP is greater   
       than or equal to EMIN. EXBITS is the number of bits needed to   
       store the exponent. */

    if (uexp + *emin > -lexp - *emin) {
	expsum = lexp << 1;
    } else {
	expsum = uexp << 1;
    }

/*     EXPSUM is the exponent range, approximately equal to   
       EMAX - EMIN + 1 . */

    *emax = expsum + *emin - 1;
    nbits = exbits + 1 + *p;

/*     NBITS is the total number of bits needed to store a   
       floating-point number. */

    if (nbits % 2 == 1 && *beta == 2) {

/*        Either there are an odd number of bits used to store a   
          floating-point number, which is unlikely, or some bits are 
  
          not used in the representation of numbers, which is possible
,   
          (e.g. Cray machines) or the mantissa has an implicit bit,   
          (e.g. IEEE machines, Dec Vax machines), which is perhaps the
   
          most likely. We have to assume the last alternative.   
          If this is true, then we need to reduce EMAX by one because 
  
          there must be some way of representing zero in an implicit-b
it   
          system. On machines like Cray, we are reducing EMAX by one 
  
          unnecessarily. */

	--(*emax);
    }

    if (*ieee) {

/*        Assume we are on an IEEE machine which reserves one exponent
   
          for infinity and NaN. */

	--(*emax);
    }

/*     Now create RMAX, the largest machine number, which should   
       be equal to (1.0 - BETA**(-P)) * BETA**EMAX .   

       First compute 1.0 - BETA**(-P), being careful that the   
       result is less than 1.0 . */

    recbas = 1. / *beta;
    z = *beta - 1.;
    y = 0.;
    for (i = 1; i <= *p; ++i) {
	z *= recbas;
	if (y < 1.) {
	    oldy = y;
	}
	y = dlamc3_(&y, &z);
/* L20: */
    }
    if (y >= 1.) {
	y = oldy;
    }

/*     Now multiply by BETA**EMAX to get RMAX. */

    for (i = 1; i <= *emax; ++i) {
	d__1 = y * *beta;
	y = dlamc3_(&d__1, &c_b5);
/* L30: */
    }

    *rmax = y;
    return 0;

/*     End of DLAMC5 */

} /* dlamc5_ */

#include "f2c.h"

doublereal dlange_(char *norm, integer *m, integer *n, doublereal *a, integer 
	*lda, doublereal *work)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1992   


    Purpose   
    =======   

    DLANGE  returns the value of the one norm,  or the Frobenius norm, or 
  
    the  infinity norm,  or the  element of  largest absolute value  of a 
  
    real matrix A.   

    Description   
    ===========   

    DLANGE returns the value   

       DLANGE = ( max(abs(A(i,j))), NORM = 'M' or 'm'   
                (   
                ( norm1(A),         NORM = '1', 'O' or 'o'   
                (   
                ( normI(A),         NORM = 'I' or 'i'   
                (   
                ( normF(A),         NORM = 'F', 'f', 'E' or 'e'   

    where  norm1  denotes the  one norm of a matrix (maximum column sum), 
  
    normI  denotes the  infinity norm  of a matrix  (maximum row sum) and 
  
    normF  denotes the  Frobenius norm of a matrix (square root of sum of 
  
    squares).  Note that  max(abs(A(i,j)))  is not a  matrix norm.   

    Arguments   
    =========   

    NORM    (input) CHARACTER*1   
            Specifies the value to be returned in DLANGE as described   
            above.   

    M       (input) INTEGER   
            The number of rows of the matrix A.  M >= 0.  When M = 0,   
            DLANGE is set to zero.   

    N       (input) INTEGER   
            The number of columns of the matrix A.  N >= 0.  When N = 0, 
  
            DLANGE is set to zero.   

    A       (input) DOUBLE PRECISION array, dimension (LDA,N)   
            The m by n matrix A.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(M,1).   

    WORK    (workspace) DOUBLE PRECISION array, dimension (LWORK),   
            where LWORK >= M when NORM = 'I'; otherwise, WORK is not   
            referenced.   

   ===================================================================== 
  


    
   Parameter adjustments   
       Function Body */
    /* Table of constant values */
    static integer c__1 = 1;
    
    /* System generated locals */
    doublereal ret_val, d__1, d__2, d__3;
    /* Builtin functions */
    double sqrt(doublereal);
    /* Local variables */
    static integer i, j;
    static doublereal scale;
    extern logical lsame_(char *, char *);
    static doublereal value;
    extern /* Subroutine */ int dlassq_(integer *, doublereal *, integer *, 
	    doublereal *, doublereal *);
    static doublereal sum;



#define WORK(I) work[(I)-1]

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]

    if (min(*m,*n) == 0) {
	value = 0.;
    } else if (lsame_(norm, "M")) {

/*        Find max(abs(A(i,j))). */

	value = 0.;
	for (j = 1; j <= *n; ++j) {
	    for (i = 1; i <= *m; ++i) {
/* Computing MAX */
		d__2 = value, d__3 = (d__1 = A(i,j), abs(d__1));
		value = max(d__2,d__3);
/* L10: */
	    }
/* L20: */
	}
    } else if (lsame_(norm, "O") || *(unsigned char *)norm == '1') {

/*        Find norm1(A). */

	value = 0.;
	for (j = 1; j <= *n; ++j) {
	    sum = 0.;
	    for (i = 1; i <= *m; ++i) {
		sum += (d__1 = A(i,j), abs(d__1));
/* L30: */
	    }
	    value = max(value,sum);
/* L40: */
	}
    } else if (lsame_(norm, "I")) {

/*        Find normI(A). */

	for (i = 1; i <= *m; ++i) {
	    WORK(i) = 0.;
/* L50: */
	}
	for (j = 1; j <= *n; ++j) {
	    for (i = 1; i <= *m; ++i) {
		WORK(i) += (d__1 = A(i,j), abs(d__1));
/* L60: */
	    }
/* L70: */
	}
	value = 0.;
	for (i = 1; i <= *m; ++i) {
/* Computing MAX */
	    d__1 = value, d__2 = WORK(i);
	    value = max(d__1,d__2);
/* L80: */
	}
    } else if (lsame_(norm, "F") || lsame_(norm, "E")) {

/*        Find normF(A). */

	scale = 0.;
	sum = 1.;
	for (j = 1; j <= *n; ++j) {
	    dlassq_(m, &A(1,j), &c__1, &scale, &sum);
/* L90: */
	}
	value = scale * sqrt(sum);
    }

    ret_val = value;
    return ret_val;

/*     End of DLANGE */

} /* dlange_ */

#include "f2c.h"

doublereal dlapy2_(doublereal *x, doublereal *y)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1992   


    Purpose   
    =======   

    DLAPY2 returns sqrt(x**2+y**2), taking care not to cause unnecessary 
  
    overflow.   

    Arguments   
    =========   

    X       (input) DOUBLE PRECISION   
    Y       (input) DOUBLE PRECISION   
            X and Y specify the values x and y.   

    ===================================================================== 
*/
/* >>Start of File<<   
       System generated locals */
    doublereal ret_val, d__1;
    /* Builtin functions */
    double sqrt(doublereal);
    /* Local variables */
    static doublereal xabs, yabs, w, z;



    xabs = abs(*x);
    yabs = abs(*y);
    w = max(xabs,yabs);
    z = min(xabs,yabs);
    if (z == 0.) {
	ret_val = w;
    } else {
/* Computing 2nd power */
	d__1 = z / w;
	ret_val = w * sqrt(d__1 * d__1 + 1.);
    }
    return ret_val;

/*     End of DLAPY2 */

} /* dlapy2_ */

#include "f2c.h"

/* Subroutine */ int dlarf_(char *side, integer *m, integer *n, doublereal *v,
	 integer *incv, doublereal *tau, doublereal *c, integer *ldc, 
	doublereal *work)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    DLARF applies a real elementary reflector H to a real m by n matrix   
    C, from either the left or the right. H is represented in the form   

          H = I - tau * v * v'   

    where tau is a real scalar and v is a real vector.   

    If tau = 0, then H is taken to be the unit matrix.   

    Arguments   
    =========   

    SIDE    (input) CHARACTER*1   
            = 'L': form  H * C   
            = 'R': form  C * H   

    M       (input) INTEGER   
            The number of rows of the matrix C.   

    N       (input) INTEGER   
            The number of columns of the matrix C.   

    V       (input) DOUBLE PRECISION array, dimension   
                       (1 + (M-1)*abs(INCV)) if SIDE = 'L'   
                    or (1 + (N-1)*abs(INCV)) if SIDE = 'R'   
            The vector v in the representation of H. V is not used if   
            TAU = 0.   

    INCV    (input) INTEGER   
            The increment between elements of v. INCV <> 0.   

    TAU     (input) DOUBLE PRECISION   
            The value tau in the representation of H.   

    C       (input/output) DOUBLE PRECISION array, dimension (LDC,N)   
            On entry, the m by n matrix C.   
            On exit, C is overwritten by the matrix H * C if SIDE = 'L', 
  
            or C * H if SIDE = 'R'.   

    LDC     (input) INTEGER   
            The leading dimension of the array C. LDC >= max(1,M).   

    WORK    (workspace) DOUBLE PRECISION array, dimension   
                           (N) if SIDE = 'L'   
                        or (M) if SIDE = 'R'   

    ===================================================================== 
  


    
   Parameter adjustments   
       Function Body */
    /* Table of constant values */
    static doublereal c_b4 = 1.;
    static doublereal c_b5 = 0.;
    static integer c__1 = 1;
    
    /* System generated locals */
    doublereal d__1;
    /* Local variables */
    extern /* Subroutine */ int dger_(integer *, integer *, doublereal *, 
	    doublereal *, integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int dgemv_(char *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *);



#define V(I) v[(I)-1]
#define WORK(I) work[(I)-1]

#define C(I,J) c[(I)-1 + ((J)-1)* ( *ldc)]

    if (lsame_(side, "L")) {

/*        Form  H * C */

	if (*tau != 0.) {

/*           w := C' * v */

	    dgemv_("Transpose", m, n, &c_b4, &C(1,1), ldc, &V(1), incv, &
		    c_b5, &WORK(1), &c__1);

/*           C := C - v * w' */

	    d__1 = -(*tau);
	    dger_(m, n, &d__1, &V(1), incv, &WORK(1), &c__1, &C(1,1), 
		    ldc);
	}
    } else {

/*        Form  C * H */

	if (*tau != 0.) {

/*           w := C * v */

	    dgemv_("No transpose", m, n, &c_b4, &C(1,1), ldc, &V(1), 
		    incv, &c_b5, &WORK(1), &c__1);

/*           C := C - w * v' */

	    d__1 = -(*tau);
	    dger_(m, n, &d__1, &WORK(1), &c__1, &V(1), incv, &C(1,1), 
		    ldc);
	}
    }
    return 0;

/*     End of DLARF */

} /* dlarf_ */

#include "f2c.h"

/* Subroutine */ int dlarfb_(char *side, char *trans, char *direct, char *
	storev, integer *m, integer *n, integer *k, doublereal *v, integer *
	ldv, doublereal *t, integer *ldt, doublereal *c, integer *ldc, 
	doublereal *work, integer *ldwork)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    DLARFB applies a real block reflector H or its transpose H' to a   
    real m by n matrix C, from either the left or the right.   

    Arguments   
    =========   

    SIDE    (input) CHARACTER*1   
            = 'L': apply H or H' from the Left   
            = 'R': apply H or H' from the Right   

    TRANS   (input) CHARACTER*1   
            = 'N': apply H (No transpose)   
            = 'T': apply H' (Transpose)   

    DIRECT  (input) CHARACTER*1   
            Indicates how H is formed from a product of elementary   
            reflectors   
            = 'F': H = H(1) H(2) . . . H(k) (Forward)   
            = 'B': H = H(k) . . . H(2) H(1) (Backward)   

    STOREV  (input) CHARACTER*1   
            Indicates how the vectors which define the elementary   
            reflectors are stored:   
            = 'C': Columnwise   
            = 'R': Rowwise   

    M       (input) INTEGER   
            The number of rows of the matrix C.   

    N       (input) INTEGER   
            The number of columns of the matrix C.   

    K       (input) INTEGER   
            The order of the matrix T (= the number of elementary   
            reflectors whose product defines the block reflector).   

    V       (input) DOUBLE PRECISION array, dimension   
                                  (LDV,K) if STOREV = 'C'   
                                  (LDV,M) if STOREV = 'R' and SIDE = 'L' 
  
                                  (LDV,N) if STOREV = 'R' and SIDE = 'R' 
  
            The matrix V. See further details.   

    LDV     (input) INTEGER   
            The leading dimension of the array V.   
            If STOREV = 'C' and SIDE = 'L', LDV >= max(1,M);   
            if STOREV = 'C' and SIDE = 'R', LDV >= max(1,N);   
            if STOREV = 'R', LDV >= K.   

    T       (input) DOUBLE PRECISION array, dimension (LDT,K)   
            The triangular k by k matrix T in the representation of the   
            block reflector.   

    LDT     (input) INTEGER   
            The leading dimension of the array T. LDT >= K.   

    C       (input/output) DOUBLE PRECISION array, dimension (LDC,N)   
            On entry, the m by n matrix C.   
            On exit, C is overwritten by H*C or H'*C or C*H or C*H'.   

    LDC     (input) INTEGER   
            The leading dimension of the array C. LDA >= max(1,M).   

    WORK    (workspace) DOUBLE PRECISION array, dimension (LDWORK,K)   

    LDWORK  (input) INTEGER   
            The leading dimension of the array WORK.   
            If SIDE = 'L', LDWORK >= max(1,N);   
            if SIDE = 'R', LDWORK >= max(1,M).   

    ===================================================================== 
  


       Quick return if possible   

    
   Parameter adjustments   
       Function Body */
    /* Table of constant values */
    static integer c__1 = 1;
    static doublereal c_b14 = 1.;
    static doublereal c_b25 = -1.;
    
    /* System generated locals */
    integer i__1;
    /* Local variables */
    static integer i, j;
    extern /* Subroutine */ int dgemm_(char *, char *, integer *, integer *, 
	    integer *, doublereal *, doublereal *, integer *, doublereal *, 
	    integer *, doublereal *, doublereal *, integer *);
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int dcopy_(integer *, doublereal *, integer *, 
	    doublereal *, integer *), dtrmm_(char *, char *, char *, char *, 
	    integer *, integer *, doublereal *, doublereal *, integer *, 
	    doublereal *, integer *);
    static char transt[1];



#undef V
#undef WORK

#define V(I,J) v[(I)-1 + ((J)-1)* ( *ldv)]
#define T(I,J) t[(I)-1 + ((J)-1)* ( *ldt)]
#define C(I,J) c[(I)-1 + ((J)-1)* ( *ldc)]
#define WORK(I,J) work[(I)-1 + ((J)-1)* ( *ldwork)]

    if (*m <= 0 || *n <= 0) {
	return 0;
    }

    if (lsame_(trans, "N")) {
	*(unsigned char *)transt = 'T';
    } else {
	*(unsigned char *)transt = 'N';
    }

    if (lsame_(storev, "C")) {

	if (lsame_(direct, "F")) {

/*           Let  V =  ( V1 )    (first K rows)   
                       ( V2 )   
             where  V1  is unit lower triangular. */

	    if (lsame_(side, "L")) {

/*              Form  H * C  or  H' * C  where  C = ( C1 )   
                                                    ( C2 )   

                W := C' * V  =  (C1'*V1 + C2'*V2)  (stored in 
WORK)   

                W := C1' */

		i__1 = *k;
		for (j = 1; j <= *k; ++j) {
		    dcopy_(n, &C(j,1), ldc, &WORK(1,j), &
			    c__1);
/* L10: */
		}

/*              W := W * V1 */

		dtrmm_("Right", "Lower", "No transpose", "Unit", n, k, &c_b14,
			 &V(1,1), ldv, &WORK(1,1), ldwork);
		if (*m > *k) {

/*                 W := W + C2'*V2 */

		    i__1 = *m - *k;
		    dgemm_("Transpose", "No transpose", n, k, &i__1, &c_b14, &
			    C(*k+1,1), ldc, &V(*k+1,1), ldv,
			     &c_b14, &WORK(1,1), ldwork);
		}

/*              W := W * T'  or  W * T */

		dtrmm_("Right", "Upper", transt, "Non-unit", n, k, &c_b14, &T(1,1), ldt, &WORK(1,1), ldwork);

/*              C := C - V * W' */

		if (*m > *k) {

/*                 C2 := C2 - V2 * W' */

		    i__1 = *m - *k;
		    dgemm_("No transpose", "Transpose", &i__1, n, k, &c_b25, &
			    V(*k+1,1), ldv, &WORK(1,1), 
			    ldwork, &c_b14, &C(*k+1,1), ldc)
			    ;
		}

/*              W := W * V1' */

		dtrmm_("Right", "Lower", "Transpose", "Unit", n, k, &c_b14, &
			V(1,1), ldv, &WORK(1,1), ldwork);

/*              C1 := C1 - W' */

		i__1 = *k;
		for (j = 1; j <= *k; ++j) {
		    for (i = 1; i <= *n; ++i) {
			C(j,i) -= WORK(i,j);
/* L20: */
		    }
/* L30: */
		}

	    } else if (lsame_(side, "R")) {

/*              Form  C * H  or  C * H'  where  C = ( C1  C2 )
   

                W := C * V  =  (C1*V1 + C2*V2)  (stored in WOR
K)   

                W := C1 */

		i__1 = *k;
		for (j = 1; j <= *k; ++j) {
		    dcopy_(m, &C(1,j), &c__1, &WORK(1,j), &c__1);
/* L40: */
		}

/*              W := W * V1 */

		dtrmm_("Right", "Lower", "No transpose", "Unit", m, k, &c_b14,
			 &V(1,1), ldv, &WORK(1,1), ldwork);
		if (*n > *k) {

/*                 W := W + C2 * V2 */

		    i__1 = *n - *k;
		    dgemm_("No transpose", "No transpose", m, k, &i__1, &
			    c_b14, &C(1,*k+1), ldc, &V(*k+1,1), ldv, &c_b14, &WORK(1,1), 
			    ldwork);
		}

/*              W := W * T  or  W * T' */

		dtrmm_("Right", "Upper", trans, "Non-unit", m, k, &c_b14, &T(1,1), ldt, &WORK(1,1), ldwork);

/*              C := C - W * V' */

		if (*n > *k) {

/*                 C2 := C2 - W * V2' */

		    i__1 = *n - *k;
		    dgemm_("No transpose", "Transpose", m, &i__1, k, &c_b25, &
			    WORK(1,1), ldwork, &V(*k+1,1), 
			    ldv, &c_b14, &C(1,*k+1), ldc);
		}

/*              W := W * V1' */

		dtrmm_("Right", "Lower", "Transpose", "Unit", m, k, &c_b14, &
			V(1,1), ldv, &WORK(1,1), ldwork);

/*              C1 := C1 - W */

		i__1 = *k;
		for (j = 1; j <= *k; ++j) {
		    for (i = 1; i <= *m; ++i) {
			C(i,j) -= WORK(i,j);
/* L50: */
		    }
/* L60: */
		}
	    }

	} else {

/*           Let  V =  ( V1 )   
                       ( V2 )    (last K rows)   
             where  V2  is unit upper triangular. */

	    if (lsame_(side, "L")) {

/*              Form  H * C  or  H' * C  where  C = ( C1 )   
                                                    ( C2 )   

                W := C' * V  =  (C1'*V1 + C2'*V2)  (stored in 
WORK)   

                W := C2' */

		i__1 = *k;
		for (j = 1; j <= *k; ++j) {
		    dcopy_(n, &C(*m-*k+j,1), ldc, &WORK(1,j), &c__1);
/* L70: */
		}

/*              W := W * V2 */

		dtrmm_("Right", "Upper", "No transpose", "Unit", n, k, &c_b14,
			 &V(*m-*k+1,1), ldv, &WORK(1,1), 
			ldwork);
		if (*m > *k) {

/*                 W := W + C1'*V1 */

		    i__1 = *m - *k;
		    dgemm_("Transpose", "No transpose", n, k, &i__1, &c_b14, &
			    C(1,1), ldc, &V(1,1), ldv, &c_b14, &
			    WORK(1,1), ldwork);
		}

/*              W := W * T'  or  W * T */

		dtrmm_("Right", "Lower", transt, "Non-unit", n, k, &c_b14, &T(1,1), ldt, &WORK(1,1), ldwork);

/*              C := C - V * W' */

		if (*m > *k) {

/*                 C1 := C1 - V1 * W' */

		    i__1 = *m - *k;
		    dgemm_("No transpose", "Transpose", &i__1, n, k, &c_b25, &
			    V(1,1), ldv, &WORK(1,1), ldwork, &
			    c_b14, &C(1,1), ldc);
		}

/*              W := W * V2' */

		dtrmm_("Right", "Upper", "Transpose", "Unit", n, k, &c_b14, &
			V(*m-*k+1,1), ldv, &WORK(1,1), 
			ldwork);

/*              C2 := C2 - W' */

		i__1 = *k;
		for (j = 1; j <= *k; ++j) {
		    for (i = 1; i <= *n; ++i) {
			C(*m-*k+j,i) -= WORK(i,j)
				;
/* L80: */
		    }
/* L90: */
		}

	    } else if (lsame_(side, "R")) {

/*              Form  C * H  or  C * H'  where  C = ( C1  C2 )
   

                W := C * V  =  (C1*V1 + C2*V2)  (stored in WOR
K)   

                W := C2 */

		i__1 = *k;
		for (j = 1; j <= *k; ++j) {
		    dcopy_(m, &C(1,*n-*k+j), &c__1, &WORK(1,j), &c__1);
/* L100: */
		}

/*              W := W * V2 */

		dtrmm_("Right", "Upper", "No transpose", "Unit", m, k, &c_b14,
			 &V(*n-*k+1,1), ldv, &WORK(1,1), 
			ldwork);
		if (*n > *k) {

/*                 W := W + C1 * V1 */

		    i__1 = *n - *k;
		    dgemm_("No transpose", "No transpose", m, k, &i__1, &
			    c_b14, &C(1,1), ldc, &V(1,1), ldv, &
			    c_b14, &WORK(1,1), ldwork);
		}

/*              W := W * T  or  W * T' */

		dtrmm_("Right", "Lower", trans, "Non-unit", m, k, &c_b14, &T(1,1), ldt, &WORK(1,1), ldwork);

/*              C := C - W * V' */

		if (*n > *k) {

/*                 C1 := C1 - W * V1' */

		    i__1 = *n - *k;
		    dgemm_("No transpose", "Transpose", m, &i__1, k, &c_b25, &
			    WORK(1,1), ldwork, &V(1,1), ldv, &
			    c_b14, &C(1,1), ldc);
		}

/*              W := W * V2' */

		dtrmm_("Right", "Upper", "Transpose", "Unit", m, k, &c_b14, &
			V(*n-*k+1,1), ldv, &WORK(1,1), 
			ldwork);

/*              C2 := C2 - W */

		i__1 = *k;
		for (j = 1; j <= *k; ++j) {
		    for (i = 1; i <= *m; ++i) {
			C(i,*n-*k+j) -= WORK(i,j);
/* L110: */
		    }
/* L120: */
		}
	    }
	}

    } else if (lsame_(storev, "R")) {

	if (lsame_(direct, "F")) {

/*           Let  V =  ( V1  V2 )    (V1: first K columns)   
             where  V1  is unit upper triangular. */

	    if (lsame_(side, "L")) {

/*              Form  H * C  or  H' * C  where  C = ( C1 )   
                                                    ( C2 )   

                W := C' * V'  =  (C1'*V1' + C2'*V2') (stored i
n WORK)   

                W := C1' */

		i__1 = *k;
		for (j = 1; j <= *k; ++j) {
		    dcopy_(n, &C(j,1), ldc, &WORK(1,j), &
			    c__1);
/* L130: */
		}

/*              W := W * V1' */

		dtrmm_("Right", "Upper", "Transpose", "Unit", n, k, &c_b14, &
			V(1,1), ldv, &WORK(1,1), ldwork);
		if (*m > *k) {

/*                 W := W + C2'*V2' */

		    i__1 = *m - *k;
		    dgemm_("Transpose", "Transpose", n, k, &i__1, &c_b14, &C(*k+1,1), ldc, &V(1,*k+1), 
			    ldv, &c_b14, &WORK(1,1), ldwork);
		}

/*              W := W * T'  or  W * T */

		dtrmm_("Right", "Upper", transt, "Non-unit", n, k, &c_b14, &T(1,1), ldt, &WORK(1,1), ldwork);

/*              C := C - V' * W' */

		if (*m > *k) {

/*                 C2 := C2 - V2' * W' */

		    i__1 = *m - *k;
		    dgemm_("Transpose", "Transpose", &i__1, n, k, &c_b25, &V(1,*k+1), ldv, &WORK(1,1), 
			    ldwork, &c_b14, &C(*k+1,1), ldc);
		}

/*              W := W * V1 */

		dtrmm_("Right", "Upper", "No transpose", "Unit", n, k, &c_b14,
			 &V(1,1), ldv, &WORK(1,1), ldwork);

/*              C1 := C1 - W' */

		i__1 = *k;
		for (j = 1; j <= *k; ++j) {
		    for (i = 1; i <= *n; ++i) {
			C(j,i) -= WORK(i,j);
/* L140: */
		    }
/* L150: */
		}

	    } else if (lsame_(side, "R")) {

/*              Form  C * H  or  C * H'  where  C = ( C1  C2 )
   

                W := C * V'  =  (C1*V1' + C2*V2')  (stored in 
WORK)   

                W := C1 */

		i__1 = *k;
		for (j = 1; j <= *k; ++j) {
		    dcopy_(m, &C(1,j), &c__1, &WORK(1,j), &c__1);
/* L160: */
		}

/*              W := W * V1' */

		dtrmm_("Right", "Upper", "Transpose", "Unit", m, k, &c_b14, &
			V(1,1), ldv, &WORK(1,1), ldwork);
		if (*n > *k) {

/*                 W := W + C2 * V2' */

		    i__1 = *n - *k;
		    dgemm_("No transpose", "Transpose", m, k, &i__1, &c_b14, &
			    C(1,*k+1), ldc, &V(1,*k+1), ldv, &c_b14, &WORK(1,1), 
			    ldwork);
		}

/*              W := W * T  or  W * T' */

		dtrmm_("Right", "Upper", trans, "Non-unit", m, k, &c_b14, &T(1,1), ldt, &WORK(1,1), ldwork);

/*              C := C - W * V */

		if (*n > *k) {

/*                 C2 := C2 - W * V2 */

		    i__1 = *n - *k;
		    dgemm_("No transpose", "No transpose", m, &i__1, k, &
			    c_b25, &WORK(1,1), ldwork, &V(1,*k+1), ldv, &c_b14, &C(1,*k+1), ldc);
		}

/*              W := W * V1 */

		dtrmm_("Right", "Upper", "No transpose", "Unit", m, k, &c_b14,
			 &V(1,1), ldv, &WORK(1,1), ldwork);

/*              C1 := C1 - W */

		i__1 = *k;
		for (j = 1; j <= *k; ++j) {
		    for (i = 1; i <= *m; ++i) {
			C(i,j) -= WORK(i,j);
/* L170: */
		    }
/* L180: */
		}

	    }

	} else {

/*           Let  V =  ( V1  V2 )    (V2: last K columns)   
             where  V2  is unit lower triangular. */

	    if (lsame_(side, "L")) {

/*              Form  H * C  or  H' * C  where  C = ( C1 )   
                                                    ( C2 )   

                W := C' * V'  =  (C1'*V1' + C2'*V2') (stored i
n WORK)   

                W := C2' */

		i__1 = *k;
		for (j = 1; j <= *k; ++j) {
		    dcopy_(n, &C(*m-*k+j,1), ldc, &WORK(1,j), &c__1);
/* L190: */
		}

/*              W := W * V2' */

		dtrmm_("Right", "Lower", "Transpose", "Unit", n, k, &c_b14, &
			V(1,*m-*k+1), ldv, &WORK(1,1)
			, ldwork);
		if (*m > *k) {

/*                 W := W + C1'*V1' */

		    i__1 = *m - *k;
		    dgemm_("Transpose", "Transpose", n, k, &i__1, &c_b14, &C(1,1), ldc, &V(1,1), ldv, &c_b14, &WORK(1,1), ldwork);
		}

/*              W := W * T'  or  W * T */

		dtrmm_("Right", "Lower", transt, "Non-unit", n, k, &c_b14, &T(1,1), ldt, &WORK(1,1), ldwork);

/*              C := C - V' * W' */

		if (*m > *k) {

/*                 C1 := C1 - V1' * W' */

		    i__1 = *m - *k;
		    dgemm_("Transpose", "Transpose", &i__1, n, k, &c_b25, &V(1,1), ldv, &WORK(1,1), ldwork, &
			    c_b14, &C(1,1), ldc);
		}

/*              W := W * V2 */

		dtrmm_("Right", "Lower", "No transpose", "Unit", n, k, &c_b14,
			 &V(1,*m-*k+1), ldv, &WORK(1,1), ldwork);

/*              C2 := C2 - W' */

		i__1 = *k;
		for (j = 1; j <= *k; ++j) {
		    for (i = 1; i <= *n; ++i) {
			C(*m-*k+j,i) -= WORK(i,j)
				;
/* L200: */
		    }
/* L210: */
		}

	    } else if (lsame_(side, "R")) {

/*              Form  C * H  or  C * H'  where  C = ( C1  C2 )
   

                W := C * V'  =  (C1*V1' + C2*V2')  (stored in 
WORK)   

                W := C2 */

		i__1 = *k;
		for (j = 1; j <= *k; ++j) {
		    dcopy_(m, &C(1,*n-*k+j), &c__1, &WORK(1,j), &c__1);
/* L220: */
		}

/*              W := W * V2' */

		dtrmm_("Right", "Lower", "Transpose", "Unit", m, k, &c_b14, &
			V(1,*n-*k+1), ldv, &WORK(1,1)
			, ldwork);
		if (*n > *k) {

/*                 W := W + C1 * V1' */

		    i__1 = *n - *k;
		    dgemm_("No transpose", "Transpose", m, k, &i__1, &c_b14, &
			    C(1,1), ldc, &V(1,1), ldv, &c_b14, &
			    WORK(1,1), ldwork);
		}

/*              W := W * T  or  W * T' */

		dtrmm_("Right", "Lower", trans, "Non-unit", m, k, &c_b14, &T(1,1), ldt, &WORK(1,1), ldwork);

/*              C := C - W * V */

		if (*n > *k) {

/*                 C1 := C1 - W * V1 */

		    i__1 = *n - *k;
		    dgemm_("No transpose", "No transpose", m, &i__1, k, &
			    c_b25, &WORK(1,1), ldwork, &V(1,1), 
			    ldv, &c_b14, &C(1,1), ldc);
		}

/*              W := W * V2 */

		dtrmm_("Right", "Lower", "No transpose", "Unit", m, k, &c_b14,
			 &V(1,*n-*k+1), ldv, &WORK(1,1), ldwork);

/*              C1 := C1 - W */

		i__1 = *k;
		for (j = 1; j <= *k; ++j) {
		    for (i = 1; i <= *m; ++i) {
			C(i,*n-*k+j) -= WORK(i,j);
/* L230: */
		    }
/* L240: */
		}

	    }

	}
    }

    return 0;

/*     End of DLARFB */

} /* dlarfb_ */

#include "f2c.h"

/* Subroutine */ int dlarfg_(integer *n, doublereal *alpha, doublereal *x, 
	integer *incx, doublereal *tau)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    DLARFG generates a real elementary reflector H of order n, such   
    that   

          H * ( alpha ) = ( beta ),   H' * H = I.   
              (   x   )   (   0  )   

    where alpha and beta are scalars, and x is an (n-1)-element real   
    vector. H is represented in the form   

          H = I - tau * ( 1 ) * ( 1 v' ) ,   
                        ( v )   

    where tau is a real scalar and v is a real (n-1)-element   
    vector.   

    If the elements of x are all zero, then tau = 0 and H is taken to be 
  
    the unit matrix.   

    Otherwise  1 <= tau <= 2.   

    Arguments   
    =========   

    N       (input) INTEGER   
            The order of the elementary reflector.   

    ALPHA   (input/output) DOUBLE PRECISION   
            On entry, the value alpha.   
            On exit, it is overwritten with the value beta.   

    X       (input/output) DOUBLE PRECISION array, dimension   
                           (1+(N-2)*abs(INCX))   
            On entry, the vector x.   
            On exit, it is overwritten with the vector v.   

    INCX    (input) INTEGER   
            The increment between elements of X. INCX > 0.   

    TAU     (output) DOUBLE PRECISION   
            The value tau.   

    ===================================================================== 
  


    
   Parameter adjustments   
       Function Body */
    /* System generated locals */
    integer i__1;
    doublereal d__1;
    /* Builtin functions */
    double d_sign(doublereal *, doublereal *);
    /* Local variables */
    static doublereal beta;
    extern doublereal dnrm2_(integer *, doublereal *, integer *);
    static integer j;
    extern /* Subroutine */ int dscal_(integer *, doublereal *, doublereal *, 
	    integer *);
    static doublereal xnorm;
    extern doublereal dlapy2_(doublereal *, doublereal *), dlamch_(char *);
    static doublereal safmin, rsafmn;
    static integer knt;


#define X(I) x[(I)-1]


    if (*n <= 1) {
	*tau = 0.;
	return 0;
    }

    i__1 = *n - 1;
    xnorm = dnrm2_(&i__1, &X(1), incx);

    if (xnorm == 0.) {

/*        H  =  I */

	*tau = 0.;
    } else {

/*        general case */

	d__1 = dlapy2_(alpha, &xnorm);
	beta = -d_sign(&d__1, alpha);
	safmin = dlamch_("S") / dlamch_("E");
	if (abs(beta) < safmin) {

/*           XNORM, BETA may be inaccurate; scale X and recompute 
them */

	    rsafmn = 1. / safmin;
	    knt = 0;
L10:
	    ++knt;
	    i__1 = *n - 1;
	    dscal_(&i__1, &rsafmn, &X(1), incx);
	    beta *= rsafmn;
	    *alpha *= rsafmn;
	    if (abs(beta) < safmin) {
		goto L10;
	    }

/*           New BETA is at most 1, at least SAFMIN */

	    i__1 = *n - 1;
	    xnorm = dnrm2_(&i__1, &X(1), incx);
	    d__1 = dlapy2_(alpha, &xnorm);
	    beta = -d_sign(&d__1, alpha);
	    *tau = (beta - *alpha) / beta;
	    i__1 = *n - 1;
	    d__1 = 1. / (*alpha - beta);
	    dscal_(&i__1, &d__1, &X(1), incx);

/*           If ALPHA is subnormal, it may lose relative accuracy 
*/

	    *alpha = beta;
	    i__1 = knt;
	    for (j = 1; j <= knt; ++j) {
		*alpha *= safmin;
/* L20: */
	    }
	} else {
	    *tau = (beta - *alpha) / beta;
	    i__1 = *n - 1;
	    d__1 = 1. / (*alpha - beta);
	    dscal_(&i__1, &d__1, &X(1), incx);
	    *alpha = beta;
	}
    }

    return 0;

/*     End of DLARFG */

} /* dlarfg_ */

#include "f2c.h"

/* Subroutine */ int dlarft_(char *direct, char *storev, integer *n, integer *
	k, doublereal *v, integer *ldv, doublereal *tau, doublereal *t, 
	integer *ldt)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    DLARFT forms the triangular factor T of a real block reflector H   
    of order n, which is defined as a product of k elementary reflectors. 
  

    If DIRECT = 'F', H = H(1) H(2) . . . H(k) and T is upper triangular; 
  

    If DIRECT = 'B', H = H(k) . . . H(2) H(1) and T is lower triangular. 
  

    If STOREV = 'C', the vector which defines the elementary reflector   
    H(i) is stored in the i-th column of the array V, and   

       H  =  I - V * T * V'   

    If STOREV = 'R', the vector which defines the elementary reflector   
    H(i) is stored in the i-th row of the array V, and   

       H  =  I - V' * T * V   

    Arguments   
    =========   

    DIRECT  (input) CHARACTER*1   
            Specifies the order in which the elementary reflectors are   
            multiplied to form the block reflector:   
            = 'F': H = H(1) H(2) . . . H(k) (Forward)   
            = 'B': H = H(k) . . . H(2) H(1) (Backward)   

    STOREV  (input) CHARACTER*1   
            Specifies how the vectors which define the elementary   
            reflectors are stored (see also Further Details):   
            = 'C': columnwise   
            = 'R': rowwise   

    N       (input) INTEGER   
            The order of the block reflector H. N >= 0.   

    K       (input) INTEGER   
            The order of the triangular factor T (= the number of   
            elementary reflectors). K >= 1.   

    V       (input/output) DOUBLE PRECISION array, dimension   
                                 (LDV,K) if STOREV = 'C'   
                                 (LDV,N) if STOREV = 'R'   
            The matrix V. See further details.   

    LDV     (input) INTEGER   
            The leading dimension of the array V.   
            If STOREV = 'C', LDV >= max(1,N); if STOREV = 'R', LDV >= K. 
  

    TAU     (input) DOUBLE PRECISION array, dimension (K)   
            TAU(i) must contain the scalar factor of the elementary   
            reflector H(i).   

    T       (output) DOUBLE PRECISION array, dimension (LDT,K)   
            The k by k triangular factor T of the block reflector.   
            If DIRECT = 'F', T is upper triangular; if DIRECT = 'B', T is 
  
            lower triangular. The rest of the array is not used.   

    LDT     (input) INTEGER   
            The leading dimension of the array T. LDT >= K.   

    Further Details   
    ===============   

    The shape of the matrix V and the storage of the vectors which define 
  
    the H(i) is best illustrated by the following example with n = 5 and 
  
    k = 3. The elements equal to 1 are not stored; the corresponding   
    array elements are modified but restored on exit. The rest of the   
    array is not used.   

    DIRECT = 'F' and STOREV = 'C':         DIRECT = 'F' and STOREV = 'R': 
  

                 V = (  1       )                 V = (  1 v1 v1 v1 v1 ) 
  
                     ( v1  1    )                     (     1 v2 v2 v2 ) 
  
                     ( v1 v2  1 )                     (        1 v3 v3 ) 
  
                     ( v1 v2 v3 )   
                     ( v1 v2 v3 )   

    DIRECT = 'B' and STOREV = 'C':         DIRECT = 'B' and STOREV = 'R': 
  

                 V = ( v1 v2 v3 )                 V = ( v1 v1  1       ) 
  
                     ( v1 v2 v3 )                     ( v2 v2 v2  1    ) 
  
                     (  1 v2 v3 )                     ( v3 v3 v3 v3  1 ) 
  
                     (     1 v3 )   
                     (        1 )   

    ===================================================================== 
  


       Quick return if possible   

    
   Parameter adjustments   
       Function Body */
    /* Table of constant values */
    static integer c__1 = 1;
    static doublereal c_b8 = 0.;
    
    /* System generated locals */
    integer i__1, i__2, i__3;
    doublereal d__1;
    /* Local variables */
    static integer i, j;
    extern logical lsame_(char *, char *);
    extern /* Subroutine */ int dgemv_(char *, integer *, integer *, 
	    doublereal *, doublereal *, integer *, doublereal *, integer *, 
	    doublereal *, doublereal *, integer *), dtrmv_(char *, 
	    char *, char *, integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    static doublereal vii;



#define TAU(I) tau[(I)-1]

#define V(I,J) v[(I)-1 + ((J)-1)* ( *ldv)]
#define T(I,J) t[(I)-1 + ((J)-1)* ( *ldt)]

    if (*n == 0) {
	return 0;
    }

    if (lsame_(direct, "F")) {
	i__1 = *k;
	for (i = 1; i <= *k; ++i) {
	    if (TAU(i) == 0.) {

/*              H(i)  =  I */

		i__2 = i;
		for (j = 1; j <= i; ++j) {
		    T(j,i) = 0.;
/* L10: */
		}
	    } else {

/*              general case */

		vii = V(i,i);
		V(i,i) = 1.;
		if (lsame_(storev, "C")) {

/*                 T(1:i-1,i) := - tau(i) * V(i:n,1:i-1)' 
* V(i:n,i) */

		    i__2 = *n - i + 1;
		    i__3 = i - 1;
		    d__1 = -TAU(i);
		    dgemv_("Transpose", &i__2, &i__3, &d__1, &V(i,1), 
			    ldv, &V(i,i), &c__1, &c_b8, &T(1,i), &c__1);
		} else {

/*                 T(1:i-1,i) := - tau(i) * V(1:i-1,i:n) *
 V(i,i:n)' */

		    i__2 = i - 1;
		    i__3 = *n - i + 1;
		    d__1 = -TAU(i);
		    dgemv_("No transpose", &i__2, &i__3, &d__1, &V(1,i), ldv, &V(i,i), ldv, &c_b8, &T(1,i), &c__1);
		}
		V(i,i) = vii;

/*              T(1:i-1,i) := T(1:i-1,1:i-1) * T(1:i-1,i) */

		i__2 = i - 1;
		dtrmv_("Upper", "No transpose", "Non-unit", &i__2, &T(1,1), ldt, &T(1,i), &c__1);
		T(i,i) = TAU(i);
	    }
/* L20: */
	}
    } else {
	for (i = *k; i >= 1; --i) {
	    if (TAU(i) == 0.) {

/*              H(i)  =  I */

		i__1 = *k;
		for (j = i; j <= *k; ++j) {
		    T(j,i) = 0.;
/* L30: */
		}
	    } else {

/*              general case */

		if (i < *k) {
		    if (lsame_(storev, "C")) {
			vii = V(*n-*k+i,i);
			V(*n-*k+i,i) = 1.;

/*                    T(i+1:k,i) :=   
                              - tau(i) * V(1:n-k+i,i+1
:k)' * V(1:n-k+i,i) */

			i__1 = *n - *k + i;
			i__2 = *k - i;
			d__1 = -TAU(i);
			dgemv_("Transpose", &i__1, &i__2, &d__1, &V(1,i+1), ldv, &V(1,i), &c__1, &
				c_b8, &T(i+1,i), &c__1);
			V(*n-*k+i,i) = vii;
		    } else {
			vii = V(i,*n-*k+i);
			V(i,*n-*k+i) = 1.;

/*                    T(i+1:k,i) :=   
                              - tau(i) * V(i+1:k,1:n-k
+i) * V(i,1:n-k+i)' */

			i__1 = *k - i;
			i__2 = *n - *k + i;
			d__1 = -TAU(i);
			dgemv_("No transpose", &i__1, &i__2, &d__1, &V(i+1,1), ldv, &V(i,1), ldv, &c_b8, &
				T(i+1,i), &c__1);
			V(i,*n-*k+i) = vii;
		    }

/*                 T(i+1:k,i) := T(i+1:k,i+1:k) * T(i+1:k,
i) */

		    i__1 = *k - i;
		    dtrmv_("Lower", "No transpose", "Non-unit", &i__1, &T(i+1,i+1), ldt, &T(i+1,i)
			    , &c__1);
		}
		T(i,i) = TAU(i);
	    }
/* L40: */
	}
    }
    return 0;

/*     End of DLARFT */

} /* dlarft_ */

#include "f2c.h"

/* Subroutine */ int dlascl_(char *type, integer *kl, integer *ku, doublereal 
	*cfrom, doublereal *cto, integer *m, integer *n, doublereal *a, 
	integer *lda, integer *info)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    DLASCL multiplies the M by N real matrix A by the real scalar   
    CTO/CFROM.  This is done without over/underflow as long as the final 
  
    result CTO*A(I,J)/CFROM does not over/underflow. TYPE specifies that 
  
    A may be full, upper triangular, lower triangular, upper Hessenberg, 
  
    or banded.   

    Arguments   
    =========   

    TYPE    (input) CHARACTER*1   
            TYPE indices the storage type of the input matrix.   
            = 'G':  A is a full matrix.   
            = 'L':  A is a lower triangular matrix.   
            = 'U':  A is an upper triangular matrix.   
            = 'H':  A is an upper Hessenberg matrix.   
            = 'B':  A is a symmetric band matrix with lower bandwidth KL 
  
                    and upper bandwidth KU and with the only the lower   
                    half stored.   
            = 'Q':  A is a symmetric band matrix with lower bandwidth KL 
  
                    and upper bandwidth KU and with the only the upper   
                    half stored.   
            = 'Z':  A is a band matrix with lower bandwidth KL and upper 
  
                    bandwidth KU.   

    KL      (input) INTEGER   
            The lower bandwidth of A.  Referenced only if TYPE = 'B',   
            'Q' or 'Z'.   

    KU      (input) INTEGER   
            The upper bandwidth of A.  Referenced only if TYPE = 'B',   
            'Q' or 'Z'.   

    CFROM   (input) DOUBLE PRECISION   
    CTO     (input) DOUBLE PRECISION   
            The matrix A is multiplied by CTO/CFROM. A(I,J) is computed   
            without over/underflow if the final result CTO*A(I,J)/CFROM   
            can be represented without over/underflow.  CFROM must be   
            nonzero.   

    M       (input) INTEGER   
            The number of rows of the matrix A.  M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix A.  N >= 0.   

    A       (input/output) DOUBLE PRECISION array, dimension (LDA,M)   
            The matrix to be multiplied by CTO/CFROM.  See TYPE for the   
            storage type.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,M).   

    INFO    (output) INTEGER   
            0  - successful exit   
            <0 - if INFO = -i, the i-th argument had an illegal value.   

    ===================================================================== 
  


       Test the input arguments   

    
   Parameter adjustments   
       Function Body */
    /* System generated locals */
    integer i__1;
    /* Local variables */
    static logical done;
    static doublereal ctoc;
    static integer i, j;
    extern logical lsame_(char *, char *);
    static integer itype, k1, k2, k3, k4;
    static doublereal cfrom1;
    extern doublereal dlamch_(char *);
    static doublereal cfromc;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    static doublereal bignum, smlnum, mul, cto1;



#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]

    *info = 0;

    if (lsame_(type, "G")) {
	itype = 0;
    } else if (lsame_(type, "L")) {
	itype = 1;
    } else if (lsame_(type, "U")) {
	itype = 2;
    } else if (lsame_(type, "H")) {
	itype = 3;
    } else if (lsame_(type, "B")) {
	itype = 4;
    } else if (lsame_(type, "Q")) {
	itype = 5;
    } else if (lsame_(type, "Z")) {
	itype = 6;
    } else {
	itype = -1;
    }

    if (itype == -1) {
	*info = -1;
    } else if (*cfrom == 0.) {
	*info = -4;
    } else if (*m < 0) {
	*info = -6;
    } else if (*n < 0 || itype == 4 && *n != *m || itype == 5 && *n != *m) {
	*info = -7;
    } else if (itype <= 3 && *lda < max(1,*m)) {
	*info = -9;
    } else if (itype >= 4) {
/* Computing MAX */
	i__1 = *m - 1;
	if (*kl < 0 || *kl > max(i__1,0)) {
	    *info = -2;
	} else /* if(complicated condition) */ {
/* Computing MAX */
	    i__1 = *n - 1;
	    if (*ku < 0 || *ku > max(i__1,0) || (itype == 4 || itype == 5) && 
		    *kl != *ku) {
		*info = -3;
	    } else if (itype == 4 && *lda < *kl + 1 || itype == 5 && *lda < *
		    ku + 1 || itype == 6 && *lda < (*kl << 1) + *ku + 1) {
		*info = -9;
	    }
	}
    }

    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DLASCL", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*n == 0 || *m == 0) {
	return 0;
    }

/*     Get machine parameters */

    smlnum = dlamch_("S");
    bignum = 1. / smlnum;

    cfromc = *cfrom;
    ctoc = *cto;

L10:
    cfrom1 = cfromc * smlnum;
    cto1 = ctoc / bignum;
    if (abs(cfrom1) > abs(ctoc) && ctoc != 0.) {
	mul = smlnum;
	done = FALSE_;
	cfromc = cfrom1;
    } else if (abs(cto1) > abs(cfromc)) {
	mul = bignum;
	done = FALSE_;
	ctoc = cto1;
    } else {
	mul = ctoc / cfromc;
	done = TRUE_;
    }

    if (itype == 0) {

/*        Full matrix */

	i__1 = *n;
	for (j = 1; j <= *n; ++j) {
	    for (i = 1; i <= *m; ++i) {
		A(i,j) *= mul;
/* L20: */
	    }
/* L30: */
	}

    } else if (itype == 1) {

/*        Lower triangular matrix */

	i__1 = *n;
	for (j = 1; j <= *n; ++j) {
	    for (i = j; i <= *m; ++i) {
		A(i,j) *= mul;
/* L40: */
	    }
/* L50: */
	}

    } else if (itype == 2) {

/*        Upper triangular matrix */

	i__1 = *n;
	for (j = 1; j <= *n; ++j) {
	    for (i = 1; i <= min(j,*m); ++i) {
		A(i,j) *= mul;
/* L60: */
	    }
/* L70: */
	}

    } else if (itype == 3) {

/*        Upper Hessenberg matrix */

	i__1 = *n;
	for (j = 1; j <= *n; ++j) {
/* Computing MIN */
	    for (i = 1; i <= min(j+1,*m); ++i) {
		A(i,j) *= mul;
/* L80: */
	    }
/* L90: */
	}

    } else if (itype == 4) {

/*        Lower half of a symmetric band matrix */

	k3 = *kl + 1;
	k4 = *n + 1;
	i__1 = *n;
	for (j = 1; j <= *n; ++j) {
/* Computing MIN */
	    for (i = 1; i <= min(k3,k4-j); ++i) {
		A(i,j) *= mul;
/* L100: */
	    }
/* L110: */
	}

    } else if (itype == 5) {

/*        Upper half of a symmetric band matrix */

	k1 = *ku + 2;
	k3 = *ku + 1;
	i__1 = *n;
	for (j = 1; j <= *n; ++j) {
/* Computing MAX */
	    for (i = max(k1-j,1); i <= k3; ++i) {
		A(i,j) *= mul;
/* L120: */
	    }
/* L130: */
	}

    } else if (itype == 6) {

/*        Band matrix */

	k1 = *kl + *ku + 2;
	k2 = *kl + 1;
	k3 = (*kl << 1) + *ku + 1;
	k4 = *kl + *ku + 1 + *m;
	i__1 = *n;
	for (j = 1; j <= *n; ++j) {
/* Computing MAX */
/* Computing MIN */
	    for (i = max(k1-j,k2); i <= min(k3,k4-j); ++i) {
		A(i,j) *= mul;
/* L140: */
	    }
/* L150: */
	}

    }

    if (! done) {
	goto L10;
    }

    return 0;

/*     End of DLASCL */

} /* dlascl_ */

#include "f2c.h"

/* Subroutine */ int dlaset_(char *uplo, integer *m, integer *n, doublereal *
	alpha, doublereal *beta, doublereal *a, integer *lda)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1992   


    Purpose   
    =======   

    DLASET initializes an m-by-n matrix A to BETA on the diagonal and   
    ALPHA on the offdiagonals.   

    Arguments   
    =========   

    UPLO    (input) CHARACTER*1   
            Specifies the part of the matrix A to be set.   
            = 'U':      Upper triangular part is set; the strictly lower 
  
                        triangular part of A is not changed.   
            = 'L':      Lower triangular part is set; the strictly upper 
  
                        triangular part of A is not changed.   
            Otherwise:  All of the matrix A is set.   

    M       (input) INTEGER   
            The number of rows of the matrix A.  M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix A.  N >= 0.   

    ALPHA   (input) DOUBLE PRECISION   
            The constant to which the offdiagonal elements are to be set. 
  

    BETA    (input) DOUBLE PRECISION   
            The constant to which the diagonal elements are to be set.   

    A       (input/output) DOUBLE PRECISION array, dimension (LDA,N)   
            On exit, the leading m-by-n submatrix of A is set as follows: 
  

            if UPLO = 'U', A(i,j) = ALPHA, 1<=i<=j-1, 1<=j<=n,   
            if UPLO = 'L', A(i,j) = ALPHA, j+1<=i<=m, 1<=j<=n,   
            otherwise,     A(i,j) = ALPHA, 1<=i<=m, 1<=j<=n, i.ne.j,   

            and, for all UPLO, A(i,i) = BETA, 1<=i<=min(m,n).   

    LDA     (input) INTEGER   
            The leading dimension of the array A.  LDA >= max(1,M).   

   ===================================================================== 
  


    
   Parameter adjustments   
       Function Body */
    /* System generated locals */
    /* Local variables */
    static integer i, j;
    extern logical lsame_(char *, char *);



#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]

    if (lsame_(uplo, "U")) {

/*        Set the strictly upper triangular or trapezoidal part of the
   
          array to ALPHA. */

	for (j = 2; j <= *n; ++j) {
/* Computing MIN */
	    for (i = 1; i <= min(j-1,*m); ++i) {
		A(i,j) = *alpha;
/* L10: */
	    }
/* L20: */
	}

    } else if (lsame_(uplo, "L")) {

/*        Set the strictly lower triangular or trapezoidal part of the
   
          array to ALPHA. */

	for (j = 1; j <= min(*m,*n); ++j) {
	    for (i = j + 1; i <= *m; ++i) {
		A(i,j) = *alpha;
/* L30: */
	    }
/* L40: */
	}

    } else {

/*        Set the leading m-by-n submatrix to ALPHA. */

	for (j = 1; j <= *n; ++j) {
	    for (i = 1; i <= *m; ++i) {
		A(i,j) = *alpha;
/* L50: */
	    }
/* L60: */
	}
    }

/*     Set the first min(M,N) diagonal elements to BETA. */

    for (i = 1; i <= min(*m,*n); ++i) {
	A(i,i) = *beta;
/* L70: */
    }

    return 0;

/*     End of DLASET */

} /* dlaset_ */

#include "f2c.h"

/* Subroutine */ int dlassq_(integer *n, doublereal *x, integer *incx, 
	doublereal *scale, doublereal *sumsq)
{
/*  -- LAPACK auxiliary routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       October 31, 1992   


    Purpose   
    =======   

    DLASSQ  returns the values  scl  and  smsq  such that   

       ( scl**2 )*smsq = x( 1 )**2 +...+ x( n )**2 + ( scale**2 )*sumsq, 
  

    where  x( i ) = X( 1 + ( i - 1 )*INCX ). The value of  sumsq  is   
    assumed to be non-negative and  scl  returns the value   

       scl = max( scale, abs( x( i ) ) ).   

    scale and sumsq must be supplied in SCALE and SUMSQ and   
    scl and smsq are overwritten on SCALE and SUMSQ respectively.   

    The routine makes only one pass through the vector x.   

    Arguments   
    =========   

    N       (input) INTEGER   
            The number of elements to be used from the vector X.   

    X       (input) DOUBLE PRECISION   
            The vector for which a scaled sum of squares is computed.   
               x( i )  = X( 1 + ( i - 1 )*INCX ), 1 <= i <= n.   

    INCX    (input) INTEGER   
            The increment between successive values of the vector X.   
            INCX > 0.   

    SCALE   (input/output) DOUBLE PRECISION   
            On entry, the value  scale  in the equation above.   
            On exit, SCALE is overwritten with  scl , the scaling factor 
  
            for the sum of squares.   

    SUMSQ   (input/output) DOUBLE PRECISION   
            On entry, the value  sumsq  in the equation above.   
            On exit, SUMSQ is overwritten with  smsq , the basic sum of   
            squares from which  scl  has been factored out.   

   ===================================================================== 
  


    
   Parameter adjustments   
       Function Body */
    /* System generated locals */
    doublereal d__1;
    /* Local variables */
    static doublereal absxi;
    static integer ix;


#define X(I) x[(I)-1]


    if (*n > 0) {
	for (ix = 1; *incx < 0 ? ix >= (*n-1)**incx+1 : ix <= (*n-1)**incx+1; ix += *incx) {
	    if (X(ix) != 0.) {
		absxi = (d__1 = X(ix), abs(d__1));
		if (*scale < absxi) {
/* Computing 2nd power */
		    d__1 = *scale / absxi;
		    *sumsq = *sumsq * (d__1 * d__1) + 1;
		    *scale = absxi;
		} else {
/* Computing 2nd power */
		    d__1 = absxi / *scale;
		    *sumsq += d__1 * d__1;
		}
	    }
/* L10: */
	}
    }
    return 0;

/*     End of DLASSQ */

} /* dlassq_ */

#include "f2c.h"

/* Subroutine */ int dorm2r_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c, integer *ldc, doublereal *work, integer *info)
{
/*  -- LAPACK routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    DORM2R overwrites the general real m by n matrix C with   

          Q * C  if SIDE = 'L' and TRANS = 'N', or   

          Q'* C  if SIDE = 'L' and TRANS = 'T', or   

          C * Q  if SIDE = 'R' and TRANS = 'N', or   

          C * Q' if SIDE = 'R' and TRANS = 'T',   

    where Q is a real orthogonal matrix defined as the product of k   
    elementary reflectors   

          Q = H(1) H(2) . . . H(k)   

    as returned by DGEQRF. Q is of order m if SIDE = 'L' and of order n   
    if SIDE = 'R'.   

    Arguments   
    =========   

    SIDE    (input) CHARACTER*1   
            = 'L': apply Q or Q' from the Left   
            = 'R': apply Q or Q' from the Right   

    TRANS   (input) CHARACTER*1   
            = 'N': apply Q  (No transpose)   
            = 'T': apply Q' (Transpose)   

    M       (input) INTEGER   
            The number of rows of the matrix C. M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix C. N >= 0.   

    K       (input) INTEGER   
            The number of elementary reflectors whose product defines   
            the matrix Q.   
            If SIDE = 'L', M >= K >= 0;   
            if SIDE = 'R', N >= K >= 0.   

    A       (input) DOUBLE PRECISION array, dimension (LDA,K)   
            The i-th column must contain the vector which defines the   
            elementary reflector H(i), for i = 1,2,...,k, as returned by 
  
            DGEQRF in the first k columns of its array argument A.   
            A is modified by the routine but restored on exit.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.   
            If SIDE = 'L', LDA >= max(1,M);   
            if SIDE = 'R', LDA >= max(1,N).   

    TAU     (input) DOUBLE PRECISION array, dimension (K)   
            TAU(i) must contain the scalar factor of the elementary   
            reflector H(i), as returned by DGEQRF.   

    C       (input/output) DOUBLE PRECISION array, dimension (LDC,N)   
            On entry, the m by n matrix C.   
            On exit, C is overwritten by Q*C or Q'*C or C*Q' or C*Q.   

    LDC     (input) INTEGER   
            The leading dimension of the array C. LDC >= max(1,M).   

    WORK    (workspace) DOUBLE PRECISION array, dimension   
                                     (N) if SIDE = 'L',   
                                     (M) if SIDE = 'R'   

    INFO    (output) INTEGER   
            = 0: successful exit   
            < 0: if INFO = -i, the i-th argument had an illegal value   

    ===================================================================== 
  


       Test the input arguments   

    
   Parameter adjustments   
       Function Body */
    /* Table of constant values */
    static integer c__1 = 1;
    
    /* System generated locals */
    integer i__1;
    /* Local variables */
    static logical left;
    static integer i;
    extern /* Subroutine */ int dlarf_(char *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, integer *, 
	    doublereal *);
    extern logical lsame_(char *, char *);
    static integer i1, i2, i3, ic, jc, mi, ni, nq;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    static logical notran;
    static doublereal aii;


#undef WORK

#define TAU(I) tau[(I)-1]
#define WORK(I) work[(I)-1]

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]
#define C(I,J) c[(I)-1 + ((J)-1)* ( *ldc)]

    *info = 0;
    left = lsame_(side, "L");
    notran = lsame_(trans, "N");

/*     NQ is the order of Q */

    if (left) {
	nq = *m;
    } else {
	nq = *n;
    }
    if (! left && ! lsame_(side, "R")) {
	*info = -1;
    } else if (! notran && ! lsame_(trans, "T")) {
	*info = -2;
    } else if (*m < 0) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*k < 0 || *k > nq) {
	*info = -5;
    } else if (*lda < max(1,nq)) {
	*info = -7;
    } else if (*ldc < max(1,*m)) {
	*info = -10;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DORM2R", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0 || *k == 0) {
	return 0;
    }

    if (left && ! notran || ! left && notran) {
	i1 = 1;
	i2 = *k;
	i3 = 1;
    } else {
	i1 = *k;
	i2 = 1;
	i3 = -1;
    }

    if (left) {
	ni = *n;
	jc = 1;
    } else {
	mi = *m;
	ic = 1;
    }

    i__1 = i2;
    for (i = i1; i3 < 0 ? i >= i2 : i <= i2; i += i3) {
	if (left) {

/*           H(i) is applied to C(i:m,1:n) */

	    mi = *m - i + 1;
	    ic = i;
	} else {

/*           H(i) is applied to C(1:m,i:n) */

	    ni = *n - i + 1;
	    jc = i;
	}

/*        Apply H(i) */

	aii = A(i,i);
	A(i,i) = 1.;
	dlarf_(side, &mi, &ni, &A(i,i), &c__1, &TAU(i), &C(ic,jc), ldc, &WORK(1));
	A(i,i) = aii;
/* L10: */
    }
    return 0;

/*     End of DORM2R */

} /* dorm2r_ */

#include "f2c.h"

/* Subroutine */ int dorml2_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c, integer *ldc, doublereal *work, integer *info)
{
/*  -- LAPACK routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       February 29, 1992   


    Purpose   
    =======   

    DORML2 overwrites the general real m by n matrix C with   

          Q * C  if SIDE = 'L' and TRANS = 'N', or   

          Q'* C  if SIDE = 'L' and TRANS = 'T', or   

          C * Q  if SIDE = 'R' and TRANS = 'N', or   

          C * Q' if SIDE = 'R' and TRANS = 'T',   

    where Q is a real orthogonal matrix defined as the product of k   
    elementary reflectors   

          Q = H(k) . . . H(2) H(1)   

    as returned by DGELQF. Q is of order m if SIDE = 'L' and of order n   
    if SIDE = 'R'.   

    Arguments   
    =========   

    SIDE    (input) CHARACTER*1   
            = 'L': apply Q or Q' from the Left   
            = 'R': apply Q or Q' from the Right   

    TRANS   (input) CHARACTER*1   
            = 'N': apply Q  (No transpose)   
            = 'T': apply Q' (Transpose)   

    M       (input) INTEGER   
            The number of rows of the matrix C. M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix C. N >= 0.   

    K       (input) INTEGER   
            The number of elementary reflectors whose product defines   
            the matrix Q.   
            If SIDE = 'L', M >= K >= 0;   
            if SIDE = 'R', N >= K >= 0.   

    A       (input) DOUBLE PRECISION array, dimension   
                                 (LDA,M) if SIDE = 'L',   
                                 (LDA,N) if SIDE = 'R'   
            The i-th row must contain the vector which defines the   
            elementary reflector H(i), for i = 1,2,...,k, as returned by 
  
            DGELQF in the first k rows of its array argument A.   
            A is modified by the routine but restored on exit.   

    LDA     (input) INTEGER   
            The leading dimension of the array A. LDA >= max(1,K).   

    TAU     (input) DOUBLE PRECISION array, dimension (K)   
            TAU(i) must contain the scalar factor of the elementary   
            reflector H(i), as returned by DGELQF.   

    C       (input/output) DOUBLE PRECISION array, dimension (LDC,N)   
            On entry, the m by n matrix C.   
            On exit, C is overwritten by Q*C or Q'*C or C*Q' or C*Q.   

    LDC     (input) INTEGER   
            The leading dimension of the array C. LDC >= max(1,M).   

    WORK    (workspace) DOUBLE PRECISION array, dimension   
                                     (N) if SIDE = 'L',   
                                     (M) if SIDE = 'R'   

    INFO    (output) INTEGER   
            = 0: successful exit   
            < 0: if INFO = -i, the i-th argument had an illegal value   

    ===================================================================== 
  


       Test the input arguments   

    
   Parameter adjustments   
       Function Body */
    /* System generated locals */
    integer i__1;
    /* Local variables */
    static logical left;
    static integer i;
    extern /* Subroutine */ int dlarf_(char *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, integer *, 
	    doublereal *);
    extern logical lsame_(char *, char *);
    static integer i1, i2, i3, ic, jc, mi, ni, nq;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    static logical notran;
    static doublereal aii;


#define TAU(I) tau[(I)-1]
#define WORK(I) work[(I)-1]

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]
#define C(I,J) c[(I)-1 + ((J)-1)* ( *ldc)]

    *info = 0;
    left = lsame_(side, "L");
    notran = lsame_(trans, "N");

/*     NQ is the order of Q */

    if (left) {
	nq = *m;
    } else {
	nq = *n;
    }
    if (! left && ! lsame_(side, "R")) {
	*info = -1;
    } else if (! notran && ! lsame_(trans, "T")) {
	*info = -2;
    } else if (*m < 0) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*k < 0 || *k > nq) {
	*info = -5;
    } else if (*lda < max(1,*k)) {
	*info = -7;
    } else if (*ldc < max(1,*m)) {
	*info = -10;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DORML2", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0 || *k == 0) {
	return 0;
    }

    if (left && notran || ! left && ! notran) {
	i1 = 1;
	i2 = *k;
	i3 = 1;
    } else {
	i1 = *k;
	i2 = 1;
	i3 = -1;
    }

    if (left) {
	ni = *n;
	jc = 1;
    } else {
	mi = *m;
	ic = 1;
    }

    i__1 = i2;
    for (i = i1; i3 < 0 ? i >= i2 : i <= i2; i += i3) {
	if (left) {

/*           H(i) is applied to C(i:m,1:n) */

	    mi = *m - i + 1;
	    ic = i;
	} else {

/*           H(i) is applied to C(1:m,i:n) */

	    ni = *n - i + 1;
	    jc = i;
	}

/*        Apply H(i) */

	aii = A(i,i);
	A(i,i) = 1.;
	dlarf_(side, &mi, &ni, &A(i,i), lda, &TAU(i), &C(ic,jc), ldc, &WORK(1));
	A(i,i) = aii;
/* L10: */
    }
    return 0;

/*     End of DORML2 */

} /* dorml2_ */

#include "f2c.h"

/* Subroutine */ int dormlq_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c, integer *ldc, doublereal *work, integer *lwork, integer *info)
{
/*  -- LAPACK routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    DORMLQ overwrites the general real M-by-N matrix C with   

                    SIDE = 'L'     SIDE = 'R'   
    TRANS = 'N':      Q * C          C * Q   
    TRANS = 'T':      Q**T * C       C * Q**T   

    where Q is a real orthogonal matrix defined as the product of k   
    elementary reflectors   

          Q = H(k) . . . H(2) H(1)   

    as returned by DGELQF. Q is of order M if SIDE = 'L' and of order N   
    if SIDE = 'R'.   

    Arguments   
    =========   

    SIDE    (input) CHARACTER*1   
            = 'L': apply Q or Q**T from the Left;   
            = 'R': apply Q or Q**T from the Right.   

    TRANS   (input) CHARACTER*1   
            = 'N':  No transpose, apply Q;   
            = 'T':  Transpose, apply Q**T.   

    M       (input) INTEGER   
            The number of rows of the matrix C. M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix C. N >= 0.   

    K       (input) INTEGER   
            The number of elementary reflectors whose product defines   
            the matrix Q.   
            If SIDE = 'L', M >= K >= 0;   
            if SIDE = 'R', N >= K >= 0.   

    A       (input) DOUBLE PRECISION array, dimension   
                                 (LDA,M) if SIDE = 'L',   
                                 (LDA,N) if SIDE = 'R'   
            The i-th row must contain the vector which defines the   
            elementary reflector H(i), for i = 1,2,...,k, as returned by 
  
            DGELQF in the first k rows of its array argument A.   
            A is modified by the routine but restored on exit.   

    LDA     (input) INTEGER   
            The leading dimension of the array A. LDA >= max(1,K).   

    TAU     (input) DOUBLE PRECISION array, dimension (K)   
            TAU(i) must contain the scalar factor of the elementary   
            reflector H(i), as returned by DGELQF.   

    C       (input/output) DOUBLE PRECISION array, dimension (LDC,N)   
            On entry, the M-by-N matrix C.   
            On exit, C is overwritten by Q*C or Q**T*C or C*Q**T or C*Q. 
  

    LDC     (input) INTEGER   
            The leading dimension of the array C. LDC >= max(1,M).   

    WORK    (workspace/output) DOUBLE PRECISION array, dimension (LWORK) 
  
            On exit, if INFO = 0, WORK(1) returns the optimal LWORK.   

    LWORK   (input) INTEGER   
            The dimension of the array WORK.   
            If SIDE = 'L', LWORK >= max(1,N);   
            if SIDE = 'R', LWORK >= max(1,M).   
            For optimum performance LWORK >= N*NB if SIDE = 'L', and   
            LWORK >= M*NB if SIDE = 'R', where NB is the optimal   
            blocksize.   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value   

    ===================================================================== 
  


       Test the input arguments   

    
   Parameter adjustments   
       Function Body */
    /* Table of constant values */
    static integer c__1 = 1;
    static integer c_n1 = -1;
    static integer c__2 = 2;
    static integer c__65 = 65;
    
    /* System generated locals */
    address a__1[2];
    integer i__1, i__2, i__3[2], i__4, i__5;
    char ch__1[2];
    /* Builtin functions   
       Subroutine */ int s_cat(char *, char **, integer *, integer *, ftnlen);
    /* Local variables */
    static logical left;
    static integer i;
    static doublereal t[4160]	/* was [65][64] */;
    extern logical lsame_(char *, char *);
    static integer nbmin, iinfo, i1, i2, i3;
    extern /* Subroutine */ int dorml2_(char *, char *, integer *, integer *, 
	    integer *, doublereal *, integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);
    static integer ib, ic, jc, nb, mi, ni;
    extern /* Subroutine */ int dlarfb_(char *, char *, char *, char *, 
	    integer *, integer *, integer *, doublereal *, integer *, 
	    doublereal *, integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    static integer nq, nw;
    extern /* Subroutine */ int dlarft_(char *, char *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, integer *), xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    static logical notran;
    static integer ldwork;
    static char transt[1];
    static integer iws;


#undef T

#define T(I) t[(I)]
#define WAS(I) was[(I)]
#define TAU(I) tau[(I)-1]
#define WORK(I) work[(I)-1]

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]
#define C(I,J) c[(I)-1 + ((J)-1)* ( *ldc)]

    *info = 0;
    left = lsame_(side, "L");
    notran = lsame_(trans, "N");

/*     NQ is the order of Q and NW is the minimum dimension of WORK */

    if (left) {
	nq = *m;
	nw = *n;
    } else {
	nq = *n;
	nw = *m;
    }
    if (! left && ! lsame_(side, "R")) {
	*info = -1;
    } else if (! notran && ! lsame_(trans, "T")) {
	*info = -2;
    } else if (*m < 0) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*k < 0 || *k > nq) {
	*info = -5;
    } else if (*lda < max(1,*k)) {
	*info = -7;
    } else if (*ldc < max(1,*m)) {
	*info = -10;
    } else if (*lwork < max(1,nw)) {
	*info = -12;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DORMLQ", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0 || *k == 0) {
	WORK(1) = 1.;
	return 0;
    }

/*     Determine the block size.  NB may be at most NBMAX, where NBMAX   
       is used to define the local array T.   

   Computing MIN   
   Writing concatenation */
    i__3[0] = 1, a__1[0] = side;
    i__3[1] = 1, a__1[1] = trans;
    s_cat(ch__1, a__1, i__3, &c__2, 2L);
    i__1 = 64, i__2 = ilaenv_(&c__1, "DORMLQ", ch__1, m, n, k, &c_n1, 6L, 2L);
    nb = min(i__1,i__2);
    nbmin = 2;
    ldwork = nw;
    if (nb > 1 && nb < *k) {
	iws = nw * nb;
	if (*lwork < iws) {
	    nb = *lwork / ldwork;
/* Computing MAX   
   Writing concatenation */
	    i__3[0] = 1, a__1[0] = side;
	    i__3[1] = 1, a__1[1] = trans;
	    s_cat(ch__1, a__1, i__3, &c__2, 2L);
	    i__1 = 2, i__2 = ilaenv_(&c__2, "DORMLQ", ch__1, m, n, k, &c_n1, 
		    6L, 2L);
	    nbmin = max(i__1,i__2);
	}
    } else {
	iws = nw;
    }

    if (nb < nbmin || nb >= *k) {

/*        Use unblocked code */

	dorml2_(side, trans, m, n, k, &A(1,1), lda, &TAU(1), &C(1,1)
		, ldc, &WORK(1), &iinfo);
    } else {

/*        Use blocked code */

	if (left && notran || ! left && ! notran) {
	    i1 = 1;
	    i2 = *k;
	    i3 = nb;
	} else {
	    i1 = (*k - 1) / nb * nb + 1;
	    i2 = 1;
	    i3 = -nb;
	}

	if (left) {
	    ni = *n;
	    jc = 1;
	} else {
	    mi = *m;
	    ic = 1;
	}

	if (notran) {
	    *(unsigned char *)transt = 'T';
	} else {
	    *(unsigned char *)transt = 'N';
	}

	i__1 = i2;
	i__2 = i3;
	for (i = i1; i3 < 0 ? i >= i2 : i <= i2; i += i3) {
/* Computing MIN */
	    i__4 = nb, i__5 = *k - i + 1;
	    ib = min(i__4,i__5);

/*           Form the triangular factor of the block reflector   
             H = H(i) H(i+1) . . . H(i+ib-1) */

	    i__4 = nq - i + 1;
	    dlarft_("Forward", "Rowwise", &i__4, &ib, &A(i,i), lda,
		     &TAU(i), t, &c__65);
	    if (left) {

/*              H or H' is applied to C(i:m,1:n) */

		mi = *m - i + 1;
		ic = i;
	    } else {

/*              H or H' is applied to C(1:m,i:n) */

		ni = *n - i + 1;
		jc = i;
	    }

/*           Apply H or H' */

	    dlarfb_(side, transt, "Forward", "Rowwise", &mi, &ni, &ib, &A(i,i), lda, t, &c__65, &C(ic,jc), ldc, &
		    WORK(1), &ldwork);
/* L10: */
	}
    }
    WORK(1) = (doublereal) iws;
    return 0;

/*     End of DORMLQ */

} /* dormlq_ */

#include "f2c.h"

/* Subroutine */ int dormqr_(char *side, char *trans, integer *m, integer *n, 
	integer *k, doublereal *a, integer *lda, doublereal *tau, doublereal *
	c, integer *ldc, doublereal *work, integer *lwork, integer *info)
{
/*  -- LAPACK routine (version 2.0) --   
       Univ. of Tennessee, Univ. of California Berkeley, NAG Ltd.,   
       Courant Institute, Argonne National Lab, and Rice University   
       September 30, 1994   


    Purpose   
    =======   

    DORMQR overwrites the general real M-by-N matrix C with   

                    SIDE = 'L'     SIDE = 'R'   
    TRANS = 'N':      Q * C          C * Q   
    TRANS = 'T':      Q**T * C       C * Q**T   

    where Q is a real orthogonal matrix defined as the product of k   
    elementary reflectors   

          Q = H(1) H(2) . . . H(k)   

    as returned by DGEQRF. Q is of order M if SIDE = 'L' and of order N   
    if SIDE = 'R'.   

    Arguments   
    =========   

    SIDE    (input) CHARACTER*1   
            = 'L': apply Q or Q**T from the Left;   
            = 'R': apply Q or Q**T from the Right.   

    TRANS   (input) CHARACTER*1   
            = 'N':  No transpose, apply Q;   
            = 'T':  Transpose, apply Q**T.   

    M       (input) INTEGER   
            The number of rows of the matrix C. M >= 0.   

    N       (input) INTEGER   
            The number of columns of the matrix C. N >= 0.   

    K       (input) INTEGER   
            The number of elementary reflectors whose product defines   
            the matrix Q.   
            If SIDE = 'L', M >= K >= 0;   
            if SIDE = 'R', N >= K >= 0.   

    A       (input) DOUBLE PRECISION array, dimension (LDA,K)   
            The i-th column must contain the vector which defines the   
            elementary reflector H(i), for i = 1,2,...,k, as returned by 
  
            DGEQRF in the first k columns of its array argument A.   
            A is modified by the routine but restored on exit.   

    LDA     (input) INTEGER   
            The leading dimension of the array A.   
            If SIDE = 'L', LDA >= max(1,M);   
            if SIDE = 'R', LDA >= max(1,N).   

    TAU     (input) DOUBLE PRECISION array, dimension (K)   
            TAU(i) must contain the scalar factor of the elementary   
            reflector H(i), as returned by DGEQRF.   

    C       (input/output) DOUBLE PRECISION array, dimension (LDC,N)   
            On entry, the M-by-N matrix C.   
            On exit, C is overwritten by Q*C or Q**T*C or C*Q**T or C*Q. 
  

    LDC     (input) INTEGER   
            The leading dimension of the array C. LDC >= max(1,M).   

    WORK    (workspace/output) DOUBLE PRECISION array, dimension (LWORK) 
  
            On exit, if INFO = 0, WORK(1) returns the optimal LWORK.   

    LWORK   (input) INTEGER   
            The dimension of the array WORK.   
            If SIDE = 'L', LWORK >= max(1,N);   
            if SIDE = 'R', LWORK >= max(1,M).   
            For optimum performance LWORK >= N*NB if SIDE = 'L', and   
            LWORK >= M*NB if SIDE = 'R', where NB is the optimal   
            blocksize.   

    INFO    (output) INTEGER   
            = 0:  successful exit   
            < 0:  if INFO = -i, the i-th argument had an illegal value   

    ===================================================================== 
  


       Test the input arguments   

    
   Parameter adjustments   
       Function Body */
    /* Table of constant values */
    static integer c__1 = 1;
    static integer c_n1 = -1;
    static integer c__2 = 2;
    static integer c__65 = 65;
    
    /* System generated locals */
    address a__1[2];
    integer i__1, i__2, i__3[2], i__4, i__5;
    char ch__1[2];
    /* Builtin functions   
       Subroutine */ int s_cat(char *, char **, integer *, integer *, ftnlen);
    /* Local variables */
    static logical left;
    static integer i;
    static doublereal t[4160]	/* was [65][64] */;
    extern logical lsame_(char *, char *);
    static integer nbmin, iinfo, i1, i2, i3;
    extern /* Subroutine */ int dorm2r_(char *, char *, integer *, integer *, 
	    integer *, doublereal *, integer *, doublereal *, doublereal *, 
	    integer *, doublereal *, integer *);
    static integer ib, ic, jc, nb, mi, ni;
    extern /* Subroutine */ int dlarfb_(char *, char *, char *, char *, 
	    integer *, integer *, integer *, doublereal *, integer *, 
	    doublereal *, integer *, doublereal *, integer *, doublereal *, 
	    integer *);
    static integer nq, nw;
    extern /* Subroutine */ int dlarft_(char *, char *, integer *, integer *, 
	    doublereal *, integer *, doublereal *, doublereal *, integer *), xerbla_(char *, integer *);
    extern integer ilaenv_(integer *, char *, char *, integer *, integer *, 
	    integer *, integer *, ftnlen, ftnlen);
    static logical notran;
    static integer ldwork, iws;



#define T(I) t[(I)]
#define WAS(I) was[(I)]
#define TAU(I) tau[(I)-1]
#define WORK(I) work[(I)-1]

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]
#define C(I,J) c[(I)-1 + ((J)-1)* ( *ldc)]

    *info = 0;
    left = lsame_(side, "L");
    notran = lsame_(trans, "N");

/*     NQ is the order of Q and NW is the minimum dimension of WORK */

    if (left) {
	nq = *m;
	nw = *n;
    } else {
	nq = *n;
	nw = *m;
    }
    if (! left && ! lsame_(side, "R")) {
	*info = -1;
    } else if (! notran && ! lsame_(trans, "T")) {
	*info = -2;
    } else if (*m < 0) {
	*info = -3;
    } else if (*n < 0) {
	*info = -4;
    } else if (*k < 0 || *k > nq) {
	*info = -5;
    } else if (*lda < max(1,nq)) {
	*info = -7;
    } else if (*ldc < max(1,*m)) {
	*info = -10;
    } else if (*lwork < max(1,nw)) {
	*info = -12;
    }
    if (*info != 0) {
	i__1 = -(*info);
	xerbla_("DORMQR", &i__1);
	return 0;
    }

/*     Quick return if possible */

    if (*m == 0 || *n == 0 || *k == 0) {
	WORK(1) = 1.;
	return 0;
    }

/*     Determine the block size.  NB may be at most NBMAX, where NBMAX   
       is used to define the local array T.   

   Computing MIN   
   Writing concatenation */
    i__3[0] = 1, a__1[0] = side;
    i__3[1] = 1, a__1[1] = trans;
    s_cat(ch__1, a__1, i__3, &c__2, 2L);
    i__1 = 64, i__2 = ilaenv_(&c__1, "DORMQR", ch__1, m, n, k, &c_n1, 6L, 2L);
    nb = min(i__1,i__2);
    nbmin = 2;
    ldwork = nw;
    if (nb > 1 && nb < *k) {
	iws = nw * nb;
	if (*lwork < iws) {
	    nb = *lwork / ldwork;
/* Computing MAX   
   Writing concatenation */
	    i__3[0] = 1, a__1[0] = side;
	    i__3[1] = 1, a__1[1] = trans;
	    s_cat(ch__1, a__1, i__3, &c__2, 2L);
	    i__1 = 2, i__2 = ilaenv_(&c__2, "DORMQR", ch__1, m, n, k, &c_n1, 
		    6L, 2L);
	    nbmin = max(i__1,i__2);
	}
    } else {
	iws = nw;
    }

    if (nb < nbmin || nb >= *k) {

/*        Use unblocked code */

	dorm2r_(side, trans, m, n, k, &A(1,1), lda, &TAU(1), &C(1,1)
		, ldc, &WORK(1), &iinfo);
    } else {

/*        Use blocked code */

	if (left && ! notran || ! left && notran) {
	    i1 = 1;
	    i2 = *k;
	    i3 = nb;
	} else {
	    i1 = (*k - 1) / nb * nb + 1;
	    i2 = 1;
	    i3 = -nb;
	}

	if (left) {
	    ni = *n;
	    jc = 1;
	} else {
	    mi = *m;
	    ic = 1;
	}

	i__1 = i2;
	i__2 = i3;
	for (i = i1; i3 < 0 ? i >= i2 : i <= i2; i += i3) {
/* Computing MIN */
	    i__4 = nb, i__5 = *k - i + 1;
	    ib = min(i__4,i__5);

/*           Form the triangular factor of the block reflector   
             H = H(i) H(i+1) . . . H(i+ib-1) */

	    i__4 = nq - i + 1;
	    dlarft_("Forward", "Columnwise", &i__4, &ib, &A(i,i), 
		    lda, &TAU(i), t, &c__65);
	    if (left) {

/*              H or H' is applied to C(i:m,1:n) */

		mi = *m - i + 1;
		ic = i;
	    } else {

/*              H or H' is applied to C(1:m,i:n) */

		ni = *n - i + 1;
		jc = i;
	    }

/*           Apply H or H' */

	    dlarfb_(side, trans, "Forward", "Columnwise", &mi, &ni, &ib, &A(i,i), lda, t, &c__65, &C(ic,jc), ldc, 
		    &WORK(1), &ldwork);
/* L10: */
	}
    }
    WORK(1) = (doublereal) iws;
    return 0;

/*     End of DORMQR */

} /* dormqr_ */


/*  -- translated by f2c (version 19940927).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Subroutine */ int dtrmm_(char *side, char *uplo, char *transa, char *diag, 
	integer *m, integer *n, doublereal *alpha, doublereal *a, integer *
	lda, doublereal *b, integer *ldb)
{


    /* System generated locals */

    /* Local variables */
    static integer info;
    static doublereal temp;
    static integer i, j, k;
    static logical lside;
    extern logical lsame_(char *, char *);
    static integer nrowa;
    static logical upper;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    static logical nounit;


/*  Purpose   
    =======   

    DTRMM  performs one of the matrix-matrix operations   

       B := alpha*op( A )*B,   or   B := alpha*B*op( A ),   

    where  alpha  is a scalar,  B  is an m by n matrix,  A  is a unit, or 
  
    non-unit,  upper or lower triangular matrix  and  op( A )  is one  of 
  

       op( A ) = A   or   op( A ) = A'.   

    Parameters   
    ==========   

    SIDE   - CHARACTER*1.   
             On entry,  SIDE specifies whether  op( A ) multiplies B from 
  
             the left or right as follows:   

                SIDE = 'L' or 'l'   B := alpha*op( A )*B.   

                SIDE = 'R' or 'r'   B := alpha*B*op( A ).   

             Unchanged on exit.   

    UPLO   - CHARACTER*1.   
             On entry, UPLO specifies whether the matrix A is an upper or 
  
             lower triangular matrix as follows:   

                UPLO = 'U' or 'u'   A is an upper triangular matrix.   

                UPLO = 'L' or 'l'   A is a lower triangular matrix.   

             Unchanged on exit.   

    TRANSA - CHARACTER*1.   
             On entry, TRANSA specifies the form of op( A ) to be used in 
  
             the matrix multiplication as follows:   

                TRANSA = 'N' or 'n'   op( A ) = A.   

                TRANSA = 'T' or 't'   op( A ) = A'.   

                TRANSA = 'C' or 'c'   op( A ) = A'.   

             Unchanged on exit.   

    DIAG   - CHARACTER*1.   
             On entry, DIAG specifies whether or not A is unit triangular 
  
             as follows:   

                DIAG = 'U' or 'u'   A is assumed to be unit triangular.   

                DIAG = 'N' or 'n'   A is not assumed to be unit   
                                    triangular.   

             Unchanged on exit.   

    M      - INTEGER.   
             On entry, M specifies the number of rows of B. M must be at 
  
             least zero.   
             Unchanged on exit.   

    N      - INTEGER.   
             On entry, N specifies the number of columns of B.  N must be 
  
             at least zero.   
             Unchanged on exit.   

    ALPHA  - DOUBLE PRECISION.   
             On entry,  ALPHA specifies the scalar  alpha. When  alpha is 
  
             zero then  A is not referenced and  B need not be set before 
  
             entry.   
             Unchanged on exit.   

    A      - DOUBLE PRECISION array of DIMENSION ( LDA, k ), where k is m 
  
             when  SIDE = 'L' or 'l'  and is  n  when  SIDE = 'R' or 'r'. 
  
             Before entry  with  UPLO = 'U' or 'u',  the  leading  k by k 
  
             upper triangular part of the array  A must contain the upper 
  
             triangular matrix  and the strictly lower triangular part of 
  
             A is not referenced.   
             Before entry  with  UPLO = 'L' or 'l',  the  leading  k by k 
  
             lower triangular part of the array  A must contain the lower 
  
             triangular matrix  and the strictly upper triangular part of 
  
             A is not referenced.   
             Note that when  DIAG = 'U' or 'u',  the diagonal elements of 
  
             A  are not referenced either,  but are assumed to be  unity. 
  
             Unchanged on exit.   

    LDA    - INTEGER.   
             On entry, LDA specifies the first dimension of A as declared 
  
             in the calling (sub) program.  When  SIDE = 'L' or 'l'  then 
  
             LDA  must be at least  max( 1, m ),  when  SIDE = 'R' or 'r' 
  
             then LDA must be at least max( 1, n ).   
             Unchanged on exit.   

    B      - DOUBLE PRECISION array of DIMENSION ( LDB, n ).   
             Before entry,  the leading  m by n part of the array  B must 
  
             contain the matrix  B,  and  on exit  is overwritten  by the 
  
             transformed matrix.   

    LDB    - INTEGER.   
             On entry, LDB specifies the first dimension of B as declared 
  
             in  the  calling  (sub)  program.   LDB  must  be  at  least 
  
             max( 1, m ).   
             Unchanged on exit.   


    Level 3 Blas routine.   

    -- Written on 8-February-1989.   
       Jack Dongarra, Argonne National Laboratory.   
       Iain Duff, AERE Harwell.   
       Jeremy Du Croz, Numerical Algorithms Group Ltd.   
       Sven Hammarling, Numerical Algorithms Group Ltd.   



       Test the input parameters.   

    
   Parameter adjustments   
       Function Body */

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]
#define B(I,J) b[(I)-1 + ((J)-1)* ( *ldb)]

    lside = lsame_(side, "L");
    if (lside) {
	nrowa = *m;
    } else {
	nrowa = *n;
    }
    nounit = lsame_(diag, "N");
    upper = lsame_(uplo, "U");

    info = 0;
    if (! lside && ! lsame_(side, "R")) {
	info = 1;
    } else if (! upper && ! lsame_(uplo, "L")) {
	info = 2;
    } else if (! lsame_(transa, "N") && ! lsame_(transa, "T") 
	    && ! lsame_(transa, "C")) {
	info = 3;
    } else if (! lsame_(diag, "U") && ! lsame_(diag, "N")) {
	info = 4;
    } else if (*m < 0) {
	info = 5;
    } else if (*n < 0) {
	info = 6;
    } else if (*lda < max(1,nrowa)) {
	info = 9;
    } else if (*ldb < max(1,*m)) {
	info = 11;
    }
    if (info != 0) {
	xerbla_("DTRMM ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*n == 0) {
	return 0;
    }

/*     And when  alpha.eq.zero. */

    if (*alpha == 0.) {
	for (j = 1; j <= *n; ++j) {
	    for (i = 1; i <= *m; ++i) {
		B(i,j) = 0.;
/* L10: */
	    }
/* L20: */
	}
	return 0;
    }

/*     Start the operations. */

    if (lside) {
	if (lsame_(transa, "N")) {

/*           Form  B := alpha*A*B. */

	    if (upper) {
		for (j = 1; j <= *n; ++j) {
		    for (k = 1; k <= *m; ++k) {
			if (B(k,j) != 0.) {
			    temp = *alpha * B(k,j);
			    for (i = 1; i <= k-1; ++i) {
				B(i,j) += temp * A(i,k);
/* L30: */
			    }
			    if (nounit) {
				temp *= A(k,k);
			    }
			    B(k,j) = temp;
			}
/* L40: */
		    }
/* L50: */
		}
	    } else {
		for (j = 1; j <= *n; ++j) {
		    for (k = *m; k >= 1; --k) {
			if (B(k,j) != 0.) {
			    temp = *alpha * B(k,j);
			    B(k,j) = temp;
			    if (nounit) {
				B(k,j) *= A(k,k);
			    }
			    for (i = k + 1; i <= *m; ++i) {
				B(i,j) += temp * A(i,k);
/* L60: */
			    }
			}
/* L70: */
		    }
/* L80: */
		}
	    }
	} else {

/*           Form  B := alpha*B*A'. */

	    if (upper) {
		for (j = 1; j <= *n; ++j) {
		    for (i = *m; i >= 1; --i) {
			temp = B(i,j);
			if (nounit) {
			    temp *= A(i,i);
			}
			for (k = 1; k <= i-1; ++k) {
			    temp += A(k,i) * B(k,j);
/* L90: */
			}
			B(i,j) = *alpha * temp;
/* L100: */
		    }
/* L110: */
		}
	    } else {
		for (j = 1; j <= *n; ++j) {
		    for (i = 1; i <= *m; ++i) {
			temp = B(i,j);
			if (nounit) {
			    temp *= A(i,i);
			}
			for (k = i + 1; k <= *m; ++k) {
			    temp += A(k,i) * B(k,j);
/* L120: */
			}
			B(i,j) = *alpha * temp;
/* L130: */
		    }
/* L140: */
		}
	    }
	}
    } else {
	if (lsame_(transa, "N")) {

/*           Form  B := alpha*B*A. */

	    if (upper) {
		for (j = *n; j >= 1; --j) {
		    temp = *alpha;
		    if (nounit) {
			temp *= A(j,j);
		    }
		    for (i = 1; i <= *m; ++i) {
			B(i,j) = temp * B(i,j);
/* L150: */
		    }
		    for (k = 1; k <= j-1; ++k) {
			if (A(k,j) != 0.) {
			    temp = *alpha * A(k,j);
			    for (i = 1; i <= *m; ++i) {
				B(i,j) += temp * B(i,k);
/* L160: */
			    }
			}
/* L170: */
		    }
/* L180: */
		}
	    } else {
		for (j = 1; j <= *n; ++j) {
		    temp = *alpha;
		    if (nounit) {
			temp *= A(j,j);
		    }
		    for (i = 1; i <= *m; ++i) {
			B(i,j) = temp * B(i,j);
/* L190: */
		    }
		    for (k = j + 1; k <= *n; ++k) {
			if (A(k,j) != 0.) {
			    temp = *alpha * A(k,j);
			    for (i = 1; i <= *m; ++i) {
				B(i,j) += temp * B(i,k);
/* L200: */
			    }
			}
/* L210: */
		    }
/* L220: */
		}
	    }
	} else {

/*           Form  B := alpha*B*A'. */

	    if (upper) {
		for (k = 1; k <= *n; ++k) {
		    for (j = 1; j <= k-1; ++j) {
			if (A(j,k) != 0.) {
			    temp = *alpha * A(j,k);
			    for (i = 1; i <= *m; ++i) {
				B(i,j) += temp * B(i,k);
/* L230: */
			    }
			}
/* L240: */
		    }
		    temp = *alpha;
		    if (nounit) {
			temp *= A(k,k);
		    }
		    if (temp != 1.) {
			for (i = 1; i <= *m; ++i) {
			    B(i,k) = temp * B(i,k);
/* L250: */
			}
		    }
/* L260: */
		}
	    } else {
		for (k = *n; k >= 1; --k) {
		    for (j = k + 1; j <= *n; ++j) {
			if (A(j,k) != 0.) {
			    temp = *alpha * A(j,k);
			    for (i = 1; i <= *m; ++i) {
				B(i,j) += temp * B(i,k);
/* L270: */
			    }
			}
/* L280: */
		    }
		    temp = *alpha;
		    if (nounit) {
			temp *= A(k,k);
		    }
		    if (temp != 1.) {
			for (i = 1; i <= *m; ++i) {
			    B(i,k) = temp * B(i,k);
/* L290: */
			}
		    }
/* L300: */
		}
	    }
	}
    }

    return 0;

/*     End of DTRMM . */

} /* dtrmm_ */


/*  -- translated by f2c (version 19940927).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"

/* Subroutine */ int dtrmv_(char *uplo, char *trans, char *diag, integer *n, 
	doublereal *a, integer *lda, doublereal *x, integer *incx)
{


    /* System generated locals */

    /* Local variables */
    static integer info;
    static doublereal temp;
    static integer i, j;
    extern logical lsame_(char *, char *);
    static integer ix, jx, kx;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    static logical nounit;


/*  Purpose   
    =======   

    DTRMV  performs one of the matrix-vector operations   

       x := A*x,   or   x := A'*x,   

    where x is an n element vector and  A is an n by n unit, or non-unit, 
  
    upper or lower triangular matrix.   

    Parameters   
    ==========   

    UPLO   - CHARACTER*1.   
             On entry, UPLO specifies whether the matrix is an upper or   
             lower triangular matrix as follows:   

                UPLO = 'U' or 'u'   A is an upper triangular matrix.   

                UPLO = 'L' or 'l'   A is a lower triangular matrix.   

             Unchanged on exit.   

    TRANS  - CHARACTER*1.   
             On entry, TRANS specifies the operation to be performed as   
             follows:   

                TRANS = 'N' or 'n'   x := A*x.   

                TRANS = 'T' or 't'   x := A'*x.   

                TRANS = 'C' or 'c'   x := A'*x.   

             Unchanged on exit.   

    DIAG   - CHARACTER*1.   
             On entry, DIAG specifies whether or not A is unit   
             triangular as follows:   

                DIAG = 'U' or 'u'   A is assumed to be unit triangular.   

                DIAG = 'N' or 'n'   A is not assumed to be unit   
                                    triangular.   

             Unchanged on exit.   

    N      - INTEGER.   
             On entry, N specifies the order of the matrix A.   
             N must be at least zero.   
             Unchanged on exit.   

    A      - DOUBLE PRECISION array of DIMENSION ( LDA, n ).   
             Before entry with  UPLO = 'U' or 'u', the leading n by n   
             upper triangular part of the array A must contain the upper 
  
             triangular matrix and the strictly lower triangular part of 
  
             A is not referenced.   
             Before entry with UPLO = 'L' or 'l', the leading n by n   
             lower triangular part of the array A must contain the lower 
  
             triangular matrix and the strictly upper triangular part of 
  
             A is not referenced.   
             Note that when  DIAG = 'U' or 'u', the diagonal elements of 
  
             A are not referenced either, but are assumed to be unity.   
             Unchanged on exit.   

    LDA    - INTEGER.   
             On entry, LDA specifies the first dimension of A as declared 
  
             in the calling (sub) program. LDA must be at least   
             max( 1, n ).   
             Unchanged on exit.   

    X      - DOUBLE PRECISION array of dimension at least   
             ( 1 + ( n - 1 )*abs( INCX ) ).   
             Before entry, the incremented array X must contain the n   
             element vector x. On exit, X is overwritten with the   
             tranformed vector x.   

    INCX   - INTEGER.   
             On entry, INCX specifies the increment for the elements of   
             X. INCX must not be zero.   
             Unchanged on exit.   


    Level 2 Blas routine.   

    -- Written on 22-October-1986.   
       Jack Dongarra, Argonne National Lab.   
       Jeremy Du Croz, Nag Central Office.   
       Sven Hammarling, Nag Central Office.   
       Richard Hanson, Sandia National Labs.   



       Test the input parameters.   

    
   Parameter adjustments   
       Function Body */
#define X(I) x[(I)-1]

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]

    info = 0;
    if (! lsame_(uplo, "U") && ! lsame_(uplo, "L")) {
	info = 1;
    } else if (! lsame_(trans, "N") && ! lsame_(trans, "T") &&
	     ! lsame_(trans, "C")) {
	info = 2;
    } else if (! lsame_(diag, "U") && ! lsame_(diag, "N")) {
	info = 3;
    } else if (*n < 0) {
	info = 4;
    } else if (*lda < max(1,*n)) {
	info = 6;
    } else if (*incx == 0) {
	info = 8;
    }
    if (info != 0) {
	xerbla_("DTRMV ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*n == 0) {
	return 0;
    }

    nounit = lsame_(diag, "N");

/*     Set up the start point in X if the increment is not unity. This   
       will be  ( N - 1 )*INCX  too small for descending loops. */

    if (*incx <= 0) {
	kx = 1 - (*n - 1) * *incx;
    } else if (*incx != 1) {
	kx = 1;
    }

/*     Start the operations. In this version the elements of A are   
       accessed sequentially with one pass through A. */

    if (lsame_(trans, "N")) {

/*        Form  x := A*x. */

	if (lsame_(uplo, "U")) {
	    if (*incx == 1) {
		for (j = 1; j <= *n; ++j) {
		    if (X(j) != 0.) {
			temp = X(j);
			for (i = 1; i <= j-1; ++i) {
			    X(i) += temp * A(i,j);
/* L10: */
			}
			if (nounit) {
			    X(j) *= A(j,j);
			}
		    }
/* L20: */
		}
	    } else {
		jx = kx;
		for (j = 1; j <= *n; ++j) {
		    if (X(jx) != 0.) {
			temp = X(jx);
			ix = kx;
			for (i = 1; i <= j-1; ++i) {
			    X(ix) += temp * A(i,j);
			    ix += *incx;
/* L30: */
			}
			if (nounit) {
			    X(jx) *= A(j,j);
			}
		    }
		    jx += *incx;
/* L40: */
		}
	    }
	} else {
	    if (*incx == 1) {
		for (j = *n; j >= 1; --j) {
		    if (X(j) != 0.) {
			temp = X(j);
			for (i = *n; i >= j+1; --i) {
			    X(i) += temp * A(i,j);
/* L50: */
			}
			if (nounit) {
			    X(j) *= A(j,j);
			}
		    }
/* L60: */
		}
	    } else {
		kx += (*n - 1) * *incx;
		jx = kx;
		for (j = *n; j >= 1; --j) {
		    if (X(jx) != 0.) {
			temp = X(jx);
			ix = kx;
			for (i = *n; i >= j+1; --i) {
			    X(ix) += temp * A(i,j);
			    ix -= *incx;
/* L70: */
			}
			if (nounit) {
			    X(jx) *= A(j,j);
			}
		    }
		    jx -= *incx;
/* L80: */
		}
	    }
	}
    } else {

/*        Form  x := A'*x. */

	if (lsame_(uplo, "U")) {
	    if (*incx == 1) {
		for (j = *n; j >= 1; --j) {
		    temp = X(j);
		    if (nounit) {
			temp *= A(j,j);
		    }
		    for (i = j - 1; i >= 1; --i) {
			temp += A(i,j) * X(i);
/* L90: */
		    }
		    X(j) = temp;
/* L100: */
		}
	    } else {
		jx = kx + (*n - 1) * *incx;
		for (j = *n; j >= 1; --j) {
		    temp = X(jx);
		    ix = jx;
		    if (nounit) {
			temp *= A(j,j);
		    }
		    for (i = j - 1; i >= 1; --i) {
			ix -= *incx;
			temp += A(i,j) * X(ix);
/* L110: */
		    }
		    X(jx) = temp;
		    jx -= *incx;
/* L120: */
		}
	    }
	} else {
	    if (*incx == 1) {
		for (j = 1; j <= *n; ++j) {
		    temp = X(j);
		    if (nounit) {
			temp *= A(j,j);
		    }
		    for (i = j + 1; i <= *n; ++i) {
			temp += A(i,j) * X(i);
/* L130: */
		    }
		    X(j) = temp;
/* L140: */
		}
	    } else {
		jx = kx;
		for (j = 1; j <= *n; ++j) {
		    temp = X(jx);
		    ix = jx;
		    if (nounit) {
			temp *= A(j,j);
		    }
		    for (i = j + 1; i <= *n; ++i) {
			ix += *incx;
			temp += A(i,j) * X(ix);
/* L150: */
		    }
		    X(jx) = temp;
		    jx += *incx;
/* L160: */
		}
	    }
	}
    }

    return 0;

/*     End of DTRMV . */

} /* dtrmv_ */

#include "f2c.h"

#ifdef KR_headers
double pow_di(ap, bp) doublereal *ap; integer *bp;
#else
double pow_di(doublereal *ap, integer *bp)
#endif
{
double pow, x;
integer n;

pow = 1;
x = *ap;
n = *bp;

if(n != 0)
	{
	if(n < 0)
		{
		n = -n;
		x = 1/x;
		}
	for( ; ; )
		{
		if(n & 01)
			pow *= x;
		if(n >>= 1)
			x *= x;
		else
			break;
		}
	}
return(pow);
}
#include "f2c.h"

#ifdef KR_headers
int s_cat(lp, rpp, rnp, np, ll) char *lp, *rpp[]; ftnlen rnp[], *np, ll;
#else
int s_cat(char *lp, char *rpp[], ftnlen rnp[], ftnlen *np, ftnlen ll)
#endif
{
ftnlen i, n, nc;
char *f__rp;

n = (int)*np;
for(i = 0 ; i < n ; ++i)
	{
	nc = ll;
	if(rnp[i] < nc)
		nc = rnp[i];
	ll -= nc;
	f__rp = rpp[i];
	while(--nc >= 0)
		*lp++ = *f__rp++;
	}
while(--ll >= 0)
	*lp++ = ' ';
return 0;
}
