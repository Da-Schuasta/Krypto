#include <iostream>
#include <gmpxx.h>
#include "dbghelp.h"
#include <string>
#include <fstream>

int main(const int argc, const char * const argv [])
{
    if (argc !=5)
    {
        std::cerr << "Description: en/decrypts text" << std::endl;
        std::cerr << "Usage: " << argv [0] << " <m> <e> <N>" << std::endl;
        std::cerr << "  i: infile" << std::endl;
        std::cerr << "  o: outfile" << std::endl;
        std::cerr << "  e: exponent" << std::endl;
        std::cerr << "  N: Modulo" << std::endl;
        return 1;
    }
    std::ifstream m_file(argv[1],std::ios::binary);  //std::ios::binary quelle:https://stackoverflow.com/questions/43950649/stdifstream-in-binary-mode-and-locale-in-c
    std::ofstream out_file(argv[2],std::ios::binary);//std::ios::binary quelle:https://stackoverflow.com/questions/43950649/stdifstream-in-binar
    mpz_class e(argv[3]), N(argv[4]);
    mpz_class m=0;

//Vorschlag von Leon das x= lenth of file-1 ist
//{
/*Methóde die vorher versucht wurde aber nicht funktuionierte
 std::string line;
    std::string text;
     while (getline(m_file, line))
     {
        text+=line+"\n";
    }
    m_file.clear();
    m_file.seekg(0);
    Funktioniert nicht da getline das \n zeichen bei jeder zeile entfernt und bei manueller hinzufügung von +\n hat man einzeichen inkosistent mehr
    Da beim manuellen erstellen der plain datei bei mir Geany das \n automatisch beim txt file ende hinzufügt und bei erstellen von crypt.txt per diesen
    Programmn nicht
    */

//methode gefunden https://cplusplus.com/forum/beginner/73096/
	m_file.seekg(0, std::ios::end); // erklärung von seekg: https://www.geeksforgeeks.org/cpp/set-position-with-seekg-in-cpp-language-file-handling/
	unsigned int x = (int)m_file.tellg() - 1; //erklärung https://www.geeksforgeeks.org/cpp/tellg-function-c-example/
	m_file.seekg(0,std::ios::beg);
//}
	char letter;
	//berechnung wie in der Angabe durchführen
    while (m_file.get(letter))
    {
    	mpz_class letterpow;
    	mpz_ui_pow_ui(letterpow.get_mpz_t(),256,x); //https://gmplib.org/manual/Integer-Exponentiation#index-mpz_005fpowm
    	m+=(unsigned char)letter*letterpow;
        x--;

    }

    mpz_powm(m.get_mpz_t(), m.get_mpz_t(),e.get_mpz_t(),N.get_mpz_t());


    //theory von Claude Sonnet 5.5 berechnung umkehren zuerst modulu ausrechnen, gibt den letzten buchstaben, dann mit 256 dividieren um
    // für die berechnung des nächsten buchstabens wenn m=0 dann ende
	std::string result;
    while(m>0)
    {
		mpz_class rest=m%256;
		result+=(char)rest.get_ui();
		m=m/256;

    }
    std::reverse(result.begin(), result.end()); //reverse von KI (Claude Sonnet5.5 wusste nicht das es existiert und bei fehler behandlung wurde es autm. hinzugefügt
    out_file<<result;
    return 0;
}
