#ifndef DVOSTRUKIHEAP_H
#define DVOSTRUKIHEAP_H

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

template <typename Tip>
class DoubleHeap {
  vector<Tip> niz;

  int Roditelj(int indeks) { return (indeks-1)/2; }
  int LijevoDijete(int indeks) { return 2*indeks+1;}
  int DesnoDijete(int indeks) { return 2*indeks+2;}
  int nivo(int indeks); // 0 za paran(min), 1 za neparan(maks)
  bool imaDjecu(int indeks);
  int indeksNajmanjeg(int indeks);
  int indeksNajveceg(int indeks);

  void UpHeap(int indeks); // Salje element uz heap ovisno od nivoa na kom se nalazi ( UpHeapMin ili UpHeapMax)
  void UpHeapMin(int indeks);
  void UpHeapMax(int indeks);

  void DownHeap(int indeks); // Salje element niz heap ovisno od nivoa na kom se nalazi ( DownHeapMin ili DownHeapMax)
  void DownHeapMin(int indeks);
  void DownHeapMax(int indeks);

  void MakeHeap(); // Kreira strukturu Dvostrukog Heapa

  public: // Konstruktori
  DoubleHeap() {}
  DoubleHeap(const vector<Tip>&niz):niz(niz) { MakeHeap(); }

  bool Empty() {return niz.size()==0;}
  void Push(const Tip& element); // Dodaje element u Dvostruki Heap
  void PopMin(); // Izbacuje Min element
  void PopMax(); // Izbacuje Max element
  Tip TopMin() { return niz[0]; } // Vraca Min element
  Tip TopMax() { return max(niz[1],niz[2]); } // Vraca Max element

  //Preklopljeni operatori za Ispis i Unos
  template<typename PomTip>
  friend ostream& operator<<(ostream&,const DoubleHeap<PomTip>&);
  template<typename PomTip>
  friend istream& operator>>(istream&,DoubleHeap<PomTip>&);
};


#endif // DVOSTRUKIHEAP_H
