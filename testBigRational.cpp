#include "BigRational.h"
#include <fstream>
#include <iomanip>

using std::cin;
using std::cout;

int main() {
    BigRational rat;
    cin >> rat;
    cout << rat.asDecimal(5);
}