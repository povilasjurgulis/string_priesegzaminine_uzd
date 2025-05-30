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

#ifdef _WIN32               // tik Windows
#  include <windows.h>
#endif

bool is_letter(unsigned char c) // Patikrina, ar simbolis yra raidė
{
    // Visi simboliai, kurių kodas > 127, laikomi raidėmis.
    return std::isalpha(c) || c >= 128;
}

int main()
{
    #ifdef _WIN32
        // Windows: konsolę perjungiame į UTF-8 (65001)
        SetConsoleOutputCP(CP_UTF8);
        SetConsoleCP(CP_UTF8);
    #endif
    std::setlocale(LC_ALL, ".UTF-8");     // srautuose – UTF-8

    ifstream fin("duomenys.txt");
    if (!fin) {
        cerr << "Nepavyko atidaryti įvesties duomenys.txt failo. \n";
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

    // atrenkame tik tuos, kurie pasikartojo daugiau nei 1 kartą
    vector<pair<string, size_t>> many; // Vektorius, kuriame saugosime žodžius su dažniu > 1
    many.reserve(freq.size()); // Rezervuojame atmintį, kad išvengtume daugybės alokacijų
    for (auto& kv : freq) // Iteruojame per žodžių dažnių map
    {
        if (kv.second > 1) 
            {
            many.emplace_back(kv); // Perkeliame į vektorių
            }
    }
    many.shrink_to_fit(); // Atlaisviname nebereikalingą atmintį

    sort(many.begin(), many.end(), [](auto& a, auto& b) { return a.second > b.second; }); // Rūšiuojame pagal dažnį

    ofstream fout("rezultatai.txt", std::ios::binary);
    for (auto& kv : many) fout << kv.first << ' ' << kv.second << '\n';

    cout << "Baigta! (" << many.size() << " žodžių >1 k.)\n";
    
    fin.close();
    return 0;
}
