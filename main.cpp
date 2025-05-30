#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <locale>
#include <cctype>

using std::ifstream; using std::ofstream; 

int main()
{
    ifstream fin("duomenys.txt");
    if (!fin) {
        std::cerr << "Nepavyko atidaryti įvesties duomenys.txt failo. \n";
        return 1;
    }

    return 0;
}
