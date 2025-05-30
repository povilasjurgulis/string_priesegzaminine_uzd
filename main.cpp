#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <locale>
#include <cctype>

using std::string; using std::size_t; using std::ifstream; using std::ofstream;
using std::unordered_map; using std::vector; using std::pair; using std::sort;
using std::cerr; using std::cout; using std::endl;

bool is_letter(unsigned char c) // Patikrina, ar simbolis yra raidė
{
    // Visi simboliai, kurių kodas > 127, laikomi raidėmis.
    return std::isalpha(c) || c >= 128;
}

int main()
{
    ifstream fin("duomenys.txt");
    if (!fin) {
        std::cerr << "Nepavyko atidaryti įvesties duomenys.txt failo. \n";
        return 1;
    }

    unordered_map<string, size_t> freq; // Žodžių dažnių map

    string word;
    char ch; // Vienas simbolis iš failo
    std::locale loc("");               // Sisteminė lokalė (kad tolower veiktų LT raidėms)

    while (fin.get(ch)) {
        unsigned char uc = static_cast<unsigned char>(ch);
        if (is_letter(uc)) {
            // Normalizuojame: verčiame į mažąsias, jei įmanoma
            word += std::tolower(uc, loc);
        } else {
            if (!word.empty()) {
                ++freq[word];
                word.clear();
            }
        }
    }
    if (!word.empty()) // paskutinis žodis, jei failas nesibaigė neskyriaus ženklu
        ++freq[word];

    fin.close();
    return 0;
}
