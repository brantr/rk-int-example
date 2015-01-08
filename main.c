#include<stdio.h>
#include<math.h>
#include"rk_int.h"


//integrand in df/dln nu
double B_nu_integrand(double ln_nu, void *params);

int main(int argc, char **argv)
{

  double T = 1.0e4; //temp in K
  double h = 6.626068e-34;  // planck constant in J s^-1
  double c = 2.997925e8;    // speed of light in m / s
  double k = 1.380650e-23;  // boltzmann constant in J K^-1
  double B_int = 2*pow(M_PI*k*T,4)/(15.*c*c*pow(h,3));	//eqn 1.58a rl
  double B_int_calc; 
  double nu_min = log(1.0e-9);
  double nu_max = log(1.0e22);
  double dnu_init = 0.01*(nu_max-nu_min);
  double eps = 1.0e-6;

  double fp[1]; //parameter of the integrand

  //set the parameter value
  fp[0] = T;

  //do the integral
  B_int_calc = integrate(B_nu_integrand,fp,1,nu_min,nu_max,dnu_init,eps);

  printf("B_int      = %e\n",B_int);
  printf("B_int_calc = %e\n",B_int_calc);
  printf("Frac. Err. = %e\n",(B_int_calc-B_int)/B_int);

  return 0;
}

double B_nu_integrand(double ln_nu, void *params)
{
  double *fp = (double *) params;
  double T = fp[0];
  double h = 6.626068e-34;  // planck constant in J s^-1
  double c = 2.997925e8;    // speed of light in m / s
  double k = 1.380650e-23;  // boltzmann constant in J K^-1
  double nu = exp(ln_nu);   // freq in Hz.

  double B_nu;
  double B_nu_denom;
  double tol = 1.0e-32;

  //printf("nu %e\n",nu);
  //eqn 1.51 of rybicki and lightman
  B_nu  = 2 * h * pow(nu,3) / pow(c, 2);


 // printf("Bnu %e\n",B_nu);
  B_nu_denom = exp(h*nu/(k*T)) - 1.;

  //printf("Bnu %e\n",B_nu);

  if(B_nu_denom < tol)
    B_nu_denom = h*nu/(k*T);

  //return  B_nu / d ln nu
  return nu * B_nu / B_nu_denom;
  
}
