#include "Dvostruki_Heap.h"

#include <iostream>
#include <vector>
#include <algorithm>

// Odredjuje na kom je nivou element ( 0 za paran(min) nivo, 1 za neparan(maks) nivo )
template <typename Tip>
int DoubleHeap<Tip>::nivo(int indeks){
    int level;
    if(indeks == 0)
        level = 0;
    else{
        level = 1;
        while(Roditelj(indeks) != 0){
            level++;
            indeks = Roditelj(indeks);
        }
    }
    if(level % 2 == 0)
        return 0;
    else return 1;
}

// Ispituje ima li element djecu
template <typename Tip>
bool DoubleHeap<Tip>::imaDjecu(int indeks){
    if(LijevoDijete(indeks) < niz.size())
        return true;
    return false;
}

// Vraca indeks najmanjeg elementa koji je dijete(ili unuk) elementa na proslijedjenom indeksu
template <typename Tip>
int DoubleHeap<Tip>::indeksNajmanjeg(int indeks){
    // Elemente na trazenim pozicijama, kao i njihove indexe cuvamo u vektorima
    vector<Tip>pomElementi;
    vector<Tip>pomIndeksi;
    if(LijevoDijete(indeks) < niz.size()){
        pomElementi.push_back(niz[LijevoDijete(indeks)]);
        pomIndeksi.push_back(LijevoDijete(indeks));
    }
    if(DesnoDijete(indeks) < niz.size()){
        pomElementi.push_back(niz[DesnoDijete(indeks)]);
        pomIndeksi.push_back(DesnoDijete(indeks));
    }
    if(LijevoDijete(LijevoDijete(indeks)) < niz.size()){
        pomElementi.push_back(niz[LijevoDijete(LijevoDijete(indeks))]);
        pomIndeksi.push_back(LijevoDijete(LijevoDijete(indeks)));
    }
    if(LijevoDijete(DesnoDijete(indeks)) < niz.size()){
        pomElementi.push_back(niz[LijevoDijete(DesnoDijete(indeks))]);
        pomIndeksi.push_back(LijevoDijete(DesnoDijete(indeks)));
    }
    if(DesnoDijete(LijevoDijete(indeks)) < niz.size()){
        pomElementi.push_back(niz[DesnoDijete(LijevoDijete(indeks))]);
        pomIndeksi.push_back(DesnoDijete(LijevoDijete(indeks)));
    }
    if(DesnoDijete(DesnoDijete(indeks)) < niz.size()){
        pomElementi.push_back(niz[DesnoDijete(DesnoDijete(indeks))]);
        pomIndeksi.push_back(DesnoDijete(DesnoDijete(indeks)));
    }
    // Kad dodjemo do min. elementa, njegov index ce biti na istoj poziciji u svom vektoru
    for(int i = 0; i < pomElementi.size(); i++){
        if (pomElementi[i] == *min_element(pomElementi.begin(),pomElementi.end()))
            return pomIndeksi[i];
    }
}

// Vraca indeks najveceg elementa koji je dijete(ili unuk) elementa na proslijedjenom indeksu
// Analogna implementacija kao 'indeksNajmanjeg'
template <typename Tip>
int DoubleHeap<Tip>::indeksNajveceg(int indeks){
    vector<Tip>pomElementi;
    vector<Tip>pomIndeksi;
    if(LijevoDijete(indeks) < niz.size()){
        pomElementi.push_back(niz[LijevoDijete(indeks)]);
        pomIndeksi.push_back(LijevoDijete(indeks));
    }
    if(DesnoDijete(indeks) < niz.size()){
        pomElementi.push_back(niz[DesnoDijete(indeks)]);
        pomIndeksi.push_back(DesnoDijete(indeks));
    }
    if(LijevoDijete(LijevoDijete(indeks)) < niz.size()){
        pomElementi.push_back(niz[LijevoDijete(LijevoDijete(indeks))]);
        pomIndeksi.push_back(LijevoDijete(LijevoDijete(indeks)));
    }
    if(LijevoDijete(DesnoDijete(indeks)) < niz.size()){
        pomElementi.push_back(niz[LijevoDijete(DesnoDijete(indeks))]);
        pomIndeksi.push_back(LijevoDijete(DesnoDijete(indeks)));
    }
    if(DesnoDijete(LijevoDijete(indeks)) < niz.size()){
        pomElementi.push_back(niz[DesnoDijete(LijevoDijete(indeks))]);
        pomIndeksi.push_back(DesnoDijete(LijevoDijete(indeks)));
    }
    if(DesnoDijete(DesnoDijete(indeks)) < niz.size()){
        pomElementi.push_back(niz[DesnoDijete(DesnoDijete(indeks))]);
        pomIndeksi.push_back(DesnoDijete(DesnoDijete(indeks)));
    }
    for(int i = 0; i < pomElementi.size(); i++){
        if (pomElementi[i] == *max_element(pomElementi.begin(),pomElementi.end()))
            return pomIndeksi[i];
    }
}

// Salje element niz Heap
template <typename Tip>
void DoubleHeap<Tip>::DownHeap(int indeks){
    if(nivo(indeks) == 0) // min level
        DownHeapMin(indeks);
    else // max level
        DownHeapMax(indeks);
}

template <typename Tip>
void DoubleHeap<Tip>::DownHeapMin(int i){
    if(imaDjecu(i)){ // Ako cvor nema djecu, nista ne radimo
        int m = indeksNajmanjeg(i);
        if(Roditelj(Roditelj(m)) == i && Roditelj(m) != 0){ // Ako je m unuk od i, oba su na min nivou
            if(niz[m] < niz[i]){ // Ako je unuk manji, mijenjamo ga sa ciljem da manji element bude visocije
                swap(niz[m],niz[i]); // na min nivoima u stablu
                if(niz[m] > niz[Roditelj(m)]) // Ako je element na min nivou veci od roditelja, mijenjamo ih
                    swap(niz[m],niz[Roditelj(m)]);
                DownHeapMin(m); // Nastavljamo postupak sa elementom na min nivou
            }
        }
        else if(niz[m] < niz[i]) // Ako m nije unuk od i, provjerimo da li su na dobrom mjestu
            swap(niz[m],niz[i]);
    }
}

template <typename Tip>
void DoubleHeap<Tip>::DownHeapMax(int i){ // Analogno kao DownHeapMin
    if(imaDjecu(i)){
        int m = indeksNajveceg(i);
        if(Roditelj(Roditelj(m)) == i){
            if(niz[m] > niz[i]){
                swap(niz[m],niz[i]);
                if(niz[m] < niz[Roditelj(m)])
                    swap(niz[m],niz[Roditelj(m)]);
                DownHeapMax(m);
            }
        }
        else if(niz[m] > niz[i])
            swap(niz[m],niz[i]);
    }
}

// Salje element uz Heap
template <typename Tip>
void DoubleHeap<Tip>::UpHeap(int i){
    if(i != 0){ // Ako nije korijen
        if(nivo(i) == 0){ // Ako je Min nivo
            if(niz[i] > niz[Roditelj(i)]){ // Ako je veci od roditelja, pripada max nivou
                swap(niz[i],niz[Roditelj(i)]);
                UpHeapMax(Roditelj(i)); // Saljemo ga uz heap po Max nivoima
            }
            else
                UpHeapMin(i); // Ako nije veci od roditelja, saljemo ga uz heap po Min nivoima
        }
        else{ // Ako je Max nivo, analogno prvom dijelu metode
            if(niz[i] < niz[Roditelj(i)]){
                swap(niz[i],niz[Roditelj(i)]);
                UpHeapMin(Roditelj(i));
            }
            else
                UpHeapMax(i);
        }
    }
}

template <typename Tip>
void DoubleHeap<Tip>::UpHeapMin(int i){ // Dok god je el. manji od roditelja svog roditelja, mijenjamo ih
    if(Roditelj(Roditelj(i)) >= 0 && Roditelj(i) != 0 && niz[i] < niz[Roditelj(Roditelj(i))]){
        swap(niz[i],niz[Roditelj(Roditelj(i))]);
        UpHeapMin(Roditelj(Roditelj(i)));
    }
}

template <typename Tip>
void DoubleHeap<Tip>::UpHeapMax(int i){ // Dok god je el. veci od roditelja svog roditelja, mijenjamo ih
    if(Roditelj(Roditelj(i)) >= 0 && Roditelj(i) != 0 && niz[i] > niz[Roditelj(Roditelj(i))]){
        swap(niz[i],niz[Roditelj(Roditelj(i))]);
        UpHeapMax(Roditelj(Roditelj(i)));
    }
}

// Sljedece metode su jasne i slicne su metodama 'obicnog' Heapa

template<typename Tip>
void DoubleHeap<Tip>::Push(const Tip& element){
    niz.push_back(element);
    UpHeap(niz.size()-1);
}

template <typename Tip>
void DoubleHeap<Tip>::PopMin() {
    swap(niz[0],niz[niz.size()-1]);
    niz.pop_back();
    DownHeap(0);
}

template <typename Tip>
void DoubleHeap<Tip>::PopMax() {
    int imax;
    if(niz[1] > niz[2])
        imax = 1;
    else
        imax = 2;
    swap(niz[imax],niz[niz.size()-1]);
    niz.pop_back();
    DownHeap(imax);
}

template <typename Tip>
void DoubleHeap<Tip>::MakeHeap(){
    for(int i = niz.size()/2; i >= 0; i--)
        DownHeap(i);
}

template <typename PomTip>
ostream& operator<<(ostream &out,const DoubleHeap<PomTip>&dh){
    out << "Double Heap: ";
    for(int i = 0; i < dh.niz.size(); i++)
        out << dh.niz[i] << " ";
    return out;
}

template <typename PomTip>
istream& operator>>(istream &in,DoubleHeap<PomTip>&dh){
    cout << "Broj elemenata Heapa: ";
    int n;
    in >> n;
    cout << endl << "Unesite elemente: ";
    PomTip element;
    for(int i = 0; i < n; i++){
        in >> element;
        dh.niz.push_back(element);
    }
    dh.MakeHeap();
    return in;
}
