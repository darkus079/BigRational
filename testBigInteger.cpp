#include "BigInteger.h"
#include <fstream>

using std::cin;
using std::cout;

int main() {
    std::ifstream fin;
    fin.open("inputBigInteger.txt");
    std::ofstream fout;
    fout.open("outputBigInteger.txt");
    int cnt = 1;

    while (!fin.eof()) {
        BigInteger a, b;
        fin >> a >> b;
        
        fout << "Test ¹" << cnt++ << '\n';
        fout << "a = " << a << '\n';
        fout << "b = " << b << '\n';
        fout << "-a = " << -a << '\n';
        fout << "-b = " << -b << '\n';

        BigInteger tmp = a;
        fout << "a++ = " << a++ << '\n';
        fout << "++a = " << ++a << '\n';
        a = tmp;
        fout << "a-- = " << a-- << '\n';
        fout << "--a = " << --a << '\n';
        a = tmp;
        fout << "a + b = " << a + b << '\n';
        fout << "a - b = " << a - b << '\n';
        fout << "a * b = " << a * b << '\n';
        fout << "a * 13 = " << a * 13 << '\n';

        try {
            fout << "a / b = " << a / b << '\n';
        }
        catch (const char* errorMessage) {
            fout << errorMessage << '\n';
        }

        try {
            fout << "a % b = " << a % b << '\n';
        }
        catch (const char* errorMessage) {
            fout << errorMessage << '\n';
        }

        fout << "a == b --> " << ((a == b) ? "true" : "false") << '\n';
        fout << "a != b --> " << ((a != b) ? "true" : "false") << '\n';
        fout << "a < b --> " << ((a < b) ? "true" : "false") << '\n';
        fout << "a <= b --> " << ((a <= b) ? "true" : "false") << '\n';
        fout << "a > b --> " << ((a > b) ? "true" : "false") << '\n';
        fout << "a >= b --> " << ((a >= b) ? "true" : "false") << '\n';
        a += b;
        fout << "a += 19: " << a << '\n';

        fout << '\n';
    }

    fin.close();
    fout.close();
}