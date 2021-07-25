#include "Dvostruki_Heap.h"
#include "Dvostruki_Heap.cpp"

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main()
{
    // Unos i Ispis DoubleHeapa
    DoubleHeap<int>dhPrvi;
    cin >> dhPrvi;
    cout << endl << dhPrvi << endl;

    // Testiranje PUSH metode
    int n; cout << endl << "Push element: "; cin >> n;
    dhPrvi.Push(n);
    cout << endl << "Nakon ubacivanja elementa " << n << ", imamo" << endl;
    cout << endl << dhPrvi << endl;

    // Testiranje POP-MIN metode
    dhPrvi.PopMin();
    cout << endl << "Nakon izbacivanja najmanjeg elementa, imamo" << endl;
    cout << endl << dhPrvi << endl;

    // Testiranje POP-MAX metode
    dhPrvi.PopMax();
    cout << endl << "Nakon izbacivanja najveceg elementa, imamo" << endl;
    cout << endl << dhPrvi << endl;

    // Testiranje TOP-MIN metode
    cout << endl << "Min Element: " << dhPrvi.TopMin() << endl;

    // Testiranje TOP-MAX metode
    cout << endl << "Max Element: " << dhPrvi.TopMax() << endl;

    return 0;
}
