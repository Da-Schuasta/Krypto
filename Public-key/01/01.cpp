
#include <iostream>
#include <gmpxx.h>
#include "dbghelp.h"

int main(const int argc, const char * const argv [])
{
  if (argc !=4)
  {
    std::cerr << "Description: en/decrypts text" << std::endl;
    std::cerr << "Usage: " << argv [0] << " <m> <e> <N>" << std::endl;
    std::cerr << "  m: message" << std::endl;
    std::cerr << "  e: exponent" << std::endl;
    std::cerr << "  N: Modulo" << std::endl;
    return 1;
  }
	mpz_class m(argv[1]), e(argv[2]), N(argv[3]),out;
  mpz_powm(out.get_mpz_t(), m.get_mpz_t(),e.get_mpz_t(),N.get_mpz_t());//gmplib.org/manual/Integer-Exponentiation#index-mpz_005fpowm
  std::cout << out << std::endl;
  return 0;
}
