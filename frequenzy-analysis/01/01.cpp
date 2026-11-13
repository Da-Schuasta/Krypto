#include <iostream>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <iomanip>


struct LetterFreq // Idee von Susi übernommen
{
    char letter;
    double percent;
};

bool compareByPercent(const LetterFreq &a, const LetterFreq &b);

int main(const int argc, const char *const argv[])
{

    using namespace std;
    if (argc < 2)
    {
        std::cout<<"No input given";
        return 1;
    }

        ifstream in(argv[1]);

    char letter;
    int position = 0;
    int count[3][26] = {}; // welcher buchstabe wie oft in welcher keyposition vorkommt
    int totals[3] = {};    // wie viele buchstaben jede key position hat

    while (in >> letter)
    {
        if (letter >= 'A' && letter <= 'Z')
        {
            count[position % 3][letter - 'A']++; // postion%3 gibt key positon zurück (0%3=0, 1%3=2 2%3=1 ...)
            totals[position % 3]++;
            position++;
        }
    }

    LetterFreq col[3][26];
    for (int k = 0; k < 3; k++)//Spalte
    {
        for (int i = 0; i < 26; i++)//Zeile
        {
            col[k][i].letter = 'A' + i;
            col[k][i].percent = round(100.0 * count[k][i] / totals[k]);
        }
        // std::stable_sort(col[k], col[k] + 26, compareByPercent); 	//andere möglichkeit von der KI welche den fall mit gleicher warscheinlichkei auto. alphabetisch löst // Quelle wo zum ersten mal gesehen:https://en.cppreference.com/cpp/algorithm/sort
        std::sort(col[k], col[k] + 26, compareByPercent);
    }

    std::cout << std::fixed << std::setprecision(0); // macht die Prozent wahrscheinlichkeit auf 0, kommastellen exact
    // std::cout << "Pos 0     ; Pos 1     ; Pos 2\n";   // header wweil für mich leichter lesbar
    for (int row = 0; row < 26; row++)//Zeile
    {
        for (int k = 0; k < 3; k++)//Spalte
        {
            std::cout << col[k][row].letter << ": " << col[k][row].percent << "%";
            if (k < 2)
            {
                std::cout << " ; ";
            }
        }
        std::cout << "\n";
    }
    in.close();

    return 0;
}

bool compareByPercent(const LetterFreq &a, const LetterFreq &b)
{
    if (a.percent == b.percent)
    {
        return a.letter < b.letter; // bei gleicher Prozent alphabetisch
    }
    return a.percent > b.percent; // buchstaben mit höherer prozent zuerst zurück
}
