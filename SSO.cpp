#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>

#define MaxNsol  300
#define MaxNvar  150

#define Nrun   50
#define Ngen  1000
#define Nsol  100
#define Nvar   30

#define Cg    0.4
#define Cp    0.7
#define Cw    0.9

#define Xub    100
#define Xlb   -100

clock_t         start                                      ;
unsigned int    run, gen                                   ;
// ---------------------------------------------------------
double          FIT_cal(float*XX)                          ;
// ---------------------------------------------------------
void            SSO_init(void)                             ;
void            SSO_update(void)                           ;

unsigned int    gBest                                      ;
float           X [MaxNsol][MaxNvar]                       ;
float           P [MaxNsol][MaxNvar]                       ;
float           F [MaxNsol]                                ;
float           pF[MaxNsol]                                ;
//----------------------------------------------------------
void            OUTPUT(void)                               ;
float           run_time                                   ;
//----------------------------------------------------------

int main(void)
{
     srand((unsigned) time (NULL))  ;

     for (run=0; run<Nrun; run++) 
     {	
          SSO_init();
	      for (gen=1; gen<Ngen; gen++)   SSO_update();
		  OUTPUT();
	 }
}
/***************************************************************************/
void SSO_update(void)
{
     register int    sol               ;
     register int    var               ;
     float           rnd               ;

	 for (sol=0; sol<Nsol; sol++)
     {
		  for (var=0; var<Nvar; var++) 
     	  {
    	       rnd = (double)rand()/(float)(RAND_MAX+1);     	  
		       if      (rnd<Cg) X[sol][var] = P[gBest][var];
		       else if (rnd<Cp) X[sol][var] = P[sol]  [var];
		       else if (rnd>Cw) X[sol][var] = (Xub-Xlb) * (double)rand()/(float)(RAND_MAX+1) + Xlb;
	      }

		  F[sol]=FIT_cal(X[sol]); 
	      if (F[sol]<pF[sol])
		  {
              pF[sol]=F[sol];
		      memcpy(P[sol], X[sol], Nvar * sizeof(float));
		      if (F[sol]<pF[gBest])  gBest=sol; 
		  }
	 }
}
/***************************************************************************/
void SSO_init(void)
{
     register int    sol, var   ;
         
	 for (gBest=sol=0; sol<Nsol; sol++)
     {
	      for (var=0; var<Nvar; var++) 
			   P[sol][var] = X[sol][var] = (Xub-Xlb) * (double)rand()/(float)(RAND_MAX+1) + Xlb; 
	      
		  F[sol]=FIT_cal(X[sol]); 
		  if (F[sol]<F[gBest]) gBest=sol;
	 }
}
/***************************************************************************/
double FIT_cal(float*XX)
{
     register int  var  ;
     double        SUM  ;
       
	 for (SUM=var=0; var<Nvar; var++) SUM += XX[var]*XX[var] - XX[var] ;
	 return SUM;
}
/***************************************************************************/
void OUTPUT(void)
{
     register int  var  ;
	 
	 printf("SSO %d %f ", run, (float)(clock()-start)/CLOCKS_PER_SEC) ;
//	 for (var=0; var<Nvar; var++) printf("%f ", P[gBest][var]); 
	 printf("%f\n", pF[gBest]);	
}

