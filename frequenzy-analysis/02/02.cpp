#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <string>

int main(const int argc, const char *const argv[])
{
  using namespace std;
  if (argc < 4)
  {
    std::cout << "Not enough input given";
    return 1;
  }

  ifstream in(argv[1]);
  ofstream out(argv[2]);
  string key = argv[3];


  char letter;
  int position = 0;
 // in >> noskipws; // lerrzeilen, Zeilenumbrüche werden auch gelesen und ins outputfile geschrieben //von Claude Sonnet 5.5
  //while (in >> letter)
  while (in.get(letter)) // in.get(letter) von jakob
  {
    if (letter >= 'A' && letter <= 'Z')
    {
      int shift = key[position % key.length()] - 'A'; // key[position%key.length()]-'A', nimmt position im text und überprüft welcher Key char genutzt wird. 2. -A da Ascii mehr als nur 26 zeichen hat rechnet man -A um den richtigen shigz zu beckommen
      letter = 'A' + (letter - 'A' + 26 - shift) % 26;
      position++;
    }
    out << letter;
  }
  out.close();
  in.close();

}
