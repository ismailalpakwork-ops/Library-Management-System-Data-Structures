// SinglyLinkedList.h

#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include "Node.h"    // Node.h Kitap.h'yi include ediyor olmali
#include "Kitap.h"   // Yine de acikca belirtmekte fayda var
#include <iostream> // std::cout icin
#include <string>   // std::string icin
#include <vector>   // enEskiBesKitabiListele icin
#include <algorithm>// std::sort, std::min icin

class SinglyLinkedList {
private:
    Node* head;  // Listenin basini gosteren isaretci
    int boyut;   // <-- BU SATIR COK ONEMLI! Private bolumde olmali.

public:
    SinglyLinkedList();  // Kurucu fonksiyon
    ~SinglyLinkedList(); // Yikici fonksiyon

    void kitapEkle(Kitap yeniKitap);
    bool ismineGoreKitapDuzenle(const std::string& kitapAdi, Kitap yeniBilgiler);
    Kitap* ismineGoreKitapBul(const std::string& kitapAdi);
    bool idGoreKitapSil(int kitapID);
    void kitaplariListele() const;
    Kitap* idGoreKitapAra(int kitapID);
    int toplamKitapSayisi() const;
    int getBoyut() const; // <-- BU FONKSIYONUN PROTOTIPININ BURADA OLDUGUNDAN EMIN OLUN
    bool idGoreHasarNotuEkle(int kitapID, const std::string& hasarNotu);
    void hasarliKitaplariYazdir() const;
    bool isEmpty() const;
    Node* getHeadGecici();

    void sayfaSayisinaGoreSirala();
    void enEskiBesKitabiListele();
};

#endif //SINGLYLINKEDLIST_H