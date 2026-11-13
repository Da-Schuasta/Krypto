#include <iostream>
#include <gmpxx.h>
#include "dbghelp.h"

//Mit von susie wie angegeben
int main()
{

  gmp_randstate_t state; //https://gmplib.org/manual/Nomenclature-and-Types#index-gmp_005frandstate_005ft
  gmp_randinit_default(state); //https://gmplib.org/manual/Random-State-Initialization#index-gmp_005frandinit_005fdefault
  size_t len=2048;
  gmp_randseed_ui(state,42); //https://gmplib.org/manual/Random-State-Seeding#index-gmp_005frandseed_005fui
   mpz_class p, q,N;

//Schritt 1 primzahlen bekommen
do
{
  mpz_urandomb(p.get_mpz_t(),state,len/2); //https://gmplib.org/manual/Miscellaneous-Float-Functions#index-mpf_005furandomb
  mpz_nextprime(p.get_mpz_t(),p.get_mpz_t());//https://gmplib.org/manual/Number-Theoretic-Functions#index-mpz_005fnextprime

  mpz_urandomb(q.get_mpz_t(),state,len/2); //https://gmplib.org/manual/Miscellaneous-Float-Functions#index-mpf_005furandomb
  mpz_nextprime(q.get_mpz_t(),q.get_mpz_t());// https://gmplib.org/manual/Number-Theoretic-Functions#index-mpz_005fnextprime

  //schritt 2: N berechnen
	 N=p*q;
}

while(mpz_sizeinbase(N.get_mpz_t(),2)!=len); //while parameter von susie

//std::cout << N << std::endl;

//Schitt 3: phiN berechnen
   mpz_class phiN=(p-1)*(q-1);


   mpz_class gcd=0,e=1;

//Schritt 4:e berechnen so dass es zwischen 1 und phiN ist (exclusive 1 und PhiN) und dass es eine Primzahl ist
//von Susie übernommen
//{
do
{
	e++;
   mpz_gcd(gcd.get_mpz_t(),phiN.get_mpz_t(),e.get_mpz_t()); //https://gmplib.org/manual/Number-Theoretic-Functions#index-mpz_005fgcd
}
while(gcd!=1||e<=1||e>=phiN);
//}


//Schritt 5: private Key berechnen mit inverse von e mod PhiN
mpz_class d;
mpz_invert(d.get_mpz_t(),e.get_mpz_t(),phiN.get_mpz_t()); //https://gmplib.org/manual/Number-Theoretic-Functions#index-mpz_005finvert
std::cout<<"Public key: ("<<e<<", "<<N<<")"<<std::endl;
std::cout<<"Private key: ("<<d<<", "<<N<<")"<<std::endl;

  return 0;
}
