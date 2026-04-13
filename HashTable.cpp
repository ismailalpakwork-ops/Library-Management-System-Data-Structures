// HashTable.cpp

#include "HashTable.h" // Kendi yazdigim HashTable.h dosyasini dahil ediyorum.
#include "Kitap.h"     // HashTable icinde Kitap nesneleriyle calisacagim.
#include <iostream>    // Ekrana yazi yazdirmak (cout) icin.
#include <string>      // Hata mesajlari veya baska seyler icin.
#include <vector>      // Tabloyu vektor olarak kullandigim icin.
#include <iomanip>     // std::fixed, std::setprecision (puanlari duzgun yazdirmak icin)

// --- Private Yardimci Fonksiyonum: Hash Fonksiyonu ---
int HashTable::hashFonksiyonu(int anahtar) const {
    if (tabloBoyutu == 0) {
        // Bu durum normalde kurucuda engellenmeli ama bir guvenlik onlemi.
        // std::cerr << "Hata: Hash tablosu boyutu 0!" << std::endl; // Test icin
        return 0;
    }
    return anahtar % tabloBoyutu;
}

// --- Kurucu Fonksiyonum (Constructor) ---
HashTable::HashTable(int boyut) {
    if (boyut <= 0) {
        tabloBoyutu = 101; // Varsayilan asal sayi
    }
    else {
        tabloBoyutu = boyut;
    }
    elemanSayisi = 0;
    tablo.resize(tabloBoyutu, nullptr);
}

// --- Yikici Fonksiyonum (Destructor) ---
HashTable::~HashTable() {
    for (int i = 0; i < tabloBoyutu; ++i) {
        HashNode* current = tablo[i];
        while (current != nullptr) {
            HashNode* silinecek = current;
            current = current->sonraki;
            delete silinecek;
        }
        tablo[i] = nullptr;
    }
}

// --- Hash Tablosunun Bos Olup Olmadigini Kontrol Ediyorum ---
bool HashTable::isEmpty() const {
    return elemanSayisi == 0;
}

// --- Hash Tablosundaki Toplam Eleman Sayisini Aliyorum ---
int HashTable::getElemanSayisi() const {
    return elemanSayisi;
}

// --- Hash Tablosuna Yeni Bir Kitap Eklemek Icin Fonksiyonum ---
void HashTable::ekle(Kitap eklenecekKitap) {
    int anahtar = eklenecekKitap.id;
    int hashIndex = hashFonksiyonu(anahtar);

    HashNode* current = tablo[hashIndex];
    while (current != nullptr) {
        if (current->anahtar == anahtar) {
            current->kitap = eklenecekKitap;
            return;
        }
        current = current->sonraki;
    }

    HashNode* yeniDugum = new HashNode(anahtar, eklenecekKitap);
    yeniDugum->sonraki = tablo[hashIndex];
    tablo[hashIndex] = yeniDugum;
    elemanSayisi++;
}

// --- ID'ye Gore Kitap Aramak Icin Fonksiyonum ---
Kitap* HashTable::ara(int kitapID) {
    int hashIndex = hashFonksiyonu(kitapID);
    HashNode* current = tablo[hashIndex];
    while (current != nullptr) {
        if (current->anahtar == kitapID) {
            return &(current->kitap);
        }
        current = current->sonraki;
    }
    return nullptr;
}

// --- ID'ye Gore Kitap Silmek Icin Fonksiyonum ---
bool HashTable::sil(int kitapID) {
    int hashIndex = hashFonksiyonu(kitapID);
    HashNode* current = tablo[hashIndex];
    HashNode* prev = nullptr;

    while (current != nullptr && current->anahtar != kitapID) {
        prev = current;
        current = current->sonraki;
    }

    if (current == nullptr) {
        return false;
    }

    if (prev == nullptr) {
        tablo[hashIndex] = current->sonraki;
    }
    else {
        prev->sonraki = current->sonraki;
    }

    delete current;
    elemanSayisi--;
    return true;
}

// --- Hash Tablosundaki Tum Kitaplari Yazdirmak Icin (Test Amaciyla) ---
void HashTable::tumunuYazdir() const {
    std::cout << "\n--- HASH TABLOSU ICERIGI ---" << std::endl;
    if (isEmpty()) {
        std::cout << "Hash Tablosu bostur." << std::endl;
        return;
    }
    for (int i = 0; i < tabloBoyutu; ++i) {
        if (tablo[i] != nullptr) {
            std::cout << "Bucket " << i << ":" << std::endl;
            HashNode* current = tablo[i];
            while (current != nullptr) {
                std::cout << "  -> ID: " << current->anahtar
                    << " - Ad: " << current->kitap.ad
                    << " (Ort Puan: " << std::fixed << std::setprecision(1) << current->kitap.ortalamaPuan
                    << ", Puanlayan: " << current->kitap.puanlayanSayisi << ")" << std::endl;
                current = current->sonraki;
            }
        }
    }
    std::cout << "Toplam Eleman Sayisi: " << elemanSayisi << std::endl;
    std::cout << "--- HASH TABLOSU SONU ---" << std::endl;
}

// Ortalama puani belirtilen minPuan'dan buyuk veya esit olan kitaplari listeler.
void HashTable::yuksekPuanlilariListele(double minPuan) const {
    std::cout << "\n--- Ortalama Puani " << std::fixed << std::setprecision(1) << minPuan << " ve Uzeri Olan Kitaplar ---" << std::endl;
    if (isEmpty()) {
        std::cout << "Hash tablosu bostur veya puanlanmis kitap yok." << std::endl;
        return;
    }
    bool bulundu = false;
    for (int i = 0; i < tabloBoyutu; ++i) {
        HashNode* current = tablo[i];
        while (current != nullptr) {
            if (current->kitap.puanlayanSayisi > 0 && current->kitap.ortalamaPuan >= minPuan) {
                current->kitap.bilgileriYazdir();
                bulundu = true;
            }
            current = current->sonraki;
        }
    }
    if (!bulundu) {
        std::cout << "Bu kriterlere uyan kitap bulunamadi." << std::endl;
    }
    std::cout << "--- Liste Sonu ---" << std::endl;
}

// Verilen kategorideki kitaplari hash tablosundan listeler.
void HashTable::kategoriyeGoreListele(const std::string& kategori) const {
    std::cout << "\n--- Kategori: '" << kategori << "' Olan Kitaplar (Hash Tablosundan) ---" << std::endl;
    if (isEmpty()) {
        std::cout << "Hash tablosu bostur." << std::endl;
        return;
    }
    bool bulundu = false;
    for (int i = 0; i < tabloBoyutu; ++i) {
        HashNode* current = tablo[i];
        while (current != nullptr) {
            if (current->kitap.kategori == kategori) {
                current->kitap.bilgileriYazdir();
                bulundu = true;
            }
            current = current->sonraki;
        }
    }
    if (!bulundu) {
        std::cout << "Bu kategoride kitap bulunamadi." << std::endl;
    }
    std::cout << "--- Liste Sonu ---" << std::endl;
}