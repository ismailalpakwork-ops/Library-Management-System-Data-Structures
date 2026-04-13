// SinglyLinkedList.cpp

#include "SinglyLinkedList.h" // Kendi yazdigim .h dosyasini dahil ediyorum.
#include "Node.h"             // Bu sinif Node.h'deki Node yapisini kullaniyor.
#include "Kitap.h"            // Node'lar Kitap nesnesi tutuyor.
#include <iostream>           // Ekrana yazi yazdirmak (cout) icin.
#include <string>             // String islemleri icin.
#include <vector>             // enEskiBesKitabiListele fonksiyonumda std::vector kullanacagim.
#include <algorithm>          // enEskiBesKitabiListele fonksiyonumda std::sort ve std::min kullanacagim.

// --- Kurucu Fonksiyonum (Constructor) ---
// Yeni bir Tek Yonlu Bagli Liste olusturdugumda bu calisacak.
// Baslangicta listem bos olacak, o yuzden 'head' isaretcimi nullptr ve 'boyut'u 0 yapiyorum.
SinglyLinkedList::SinglyLinkedList() {
    head = nullptr;
    boyut = 0;
}

// --- Yikici Fonksiyonum (Destructor) ---
// Bu liste nesnesi hafizadan silinirken calisacak.
// Listedeki tum dugumleri tek tek silerek hafizada bosuna yer kaplamalarini onleyecegim.
SinglyLinkedList::~SinglyLinkedList() {
    Node* mevcut = head;
    Node* sonrakiNode = nullptr;
    while (mevcut != nullptr) {
        sonrakiNode = mevcut->sonraki;
        delete mevcut;
        mevcut = sonrakiNode;
    }
    head = nullptr;
}

// --- Listemin Bos Olup Olmadigini Kontrol Eden Fonksiyonum ---
bool SinglyLinkedList::isEmpty() const {
    return head == nullptr;
}

// --- Listemin Mevcut Boyutunu (Eleman Sayisini) Alan Fonksiyonum ---
// SinglyLinkedList.h'de 'int boyut;' tanimli oldugu icin dogrudan onu donduruyorum.
int SinglyLinkedList::getBoyut() const {
    return boyut;
}

// --- Listemin Sonuna Yeni Bir Kitap Ekleyen Fonksiyonum ---
void SinglyLinkedList::kitapEkle(Kitap yeniKitap) {
    Node* yeniDugum = new Node(yeniKitap);

    if (isEmpty()) {
        head = yeniDugum;
    }
    else {
        Node* temp = head;
        while (temp->sonraki != nullptr) {
            temp = temp->sonraki;
        }
        temp->sonraki = yeniDugum;
    }
    boyut++; // Boyutu bir arttiriyorum.
}

// --- Listedeki Tum Kitaplari Yazdiran Fonksiyonum ---
void SinglyLinkedList::kitaplariListele() const {
    if (isEmpty()) {
        std::cout << "Kitap listesi (Ana Liste) bostur." << std::endl;
        return;
    }
    std::cout << "\n--- ANA KITAP LISTESI (Tek Yonlu) ---" << std::endl;
    Node* temp = head;
    int sayac = 1;
    while (temp != nullptr) {
        std::cout << "\nKitap " << sayac++ << ":" << std::endl;
        temp->kitap.bilgileriYazdir();
        temp = temp->sonraki;
    }
    std::cout << "--- LISTE SONU ---" << std::endl;
}

// --- ID Bilgisine Gore Kitap Arayan Fonksiyonum ---
// Bulursa Kitap nesnesinin adresini, bulamazsa nullptr dondurur.
Kitap* SinglyLinkedList::idGoreKitapAra(int kitapID) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->kitap.id == kitapID) { // Kitap.id'nin public oldugunu varsayiyorum.
            return &(temp->kitap);
        }
        temp = temp->sonraki;
    }
    return nullptr;
}

// --- Listedeki Toplam Kitap Sayisini Donduren Fonksiyonum ---
// Bu fonksiyon artik dogrudan 'boyut' uye degiskenimi donduruyor.
int SinglyLinkedList::toplamKitapSayisi() const {
    return boyut;
}

// --- ID Bilgisine Gore Kitabi Silen Fonksiyonum ---
bool SinglyLinkedList::idGoreKitapSil(int kitapID) {
    if (isEmpty()) {
        // Mesaj main.cpp'de verilebilir.
        return false;
    }

    Node* mevcut = head;
    Node* onceki = nullptr;

    if (mevcut != nullptr && mevcut->kitap.id == kitapID) {
        head = mevcut->sonraki;
        // Mesaj main.cpp'de verilebilir.
        delete mevcut;
        boyut--;
        return true;
    }

    while (mevcut != nullptr && mevcut->kitap.id != kitapID) {
        onceki = mevcut;
        mevcut = mevcut->sonraki;
    }

    if (mevcut == nullptr) {
        // Mesaj main.cpp'de verilebilir.
        return false;
    }

    onceki->sonraki = mevcut->sonraki;
    // Mesaj main.cpp'de verilebilir.
    delete mevcut;
    boyut--;
    return true;
}

// --- Ismine Gore Kitabi Duzenleyen Fonksiyonum ---
bool SinglyLinkedList::ismineGoreKitapDuzenle(const std::string& kitapAdi, Kitap yeniBilgiler) {
    Node* temp = head;
    while (temp != nullptr) {
        if (temp->kitap.ad == kitapAdi) { // Kitap.ad public olmali
            if (!yeniBilgiler.yazar.empty()) {
                temp->kitap.yazar = yeniBilgiler.yazar;
            }
            if (yeniBilgiler.basimYili != 0) {
                temp->kitap.basimYili = yeniBilgiler.basimYili;
            }
            if (yeniBilgiler.sayfaSayisi != 0) {
                temp->kitap.sayfaSayisi = yeniBilgiler.sayfaSayisi;
            }
            // Diger alanlar da benzer sekilde guncellenebilir.
            std::cout << "'" << kitapAdi << "' adli kitabin bilgileri guncellendi." << std::endl; // Bu mesaj kalabilir.
            return true;
        }
        temp = temp->sonraki;
    }
    std::cout << "'" << kitapAdi << "' adli kitap bulunamadi, duzenlenemedi." << std::endl; // Bu mesaj kalabilir.
    return false;
}

// --- Isme Gore Kitap Bulan Yardimci Fonksiyonum ---
Kitap* SinglyLinkedList::ismineGoreKitapBul(const std::string& kitapAdi) {
    Node* gezici = head;
    while (gezici != nullptr) {
        if (gezici->kitap.ad == kitapAdi) {
            return &(gezici->kitap);
        }
        gezici = gezici->sonraki;
    }
    return nullptr;
}

// --- ID Bilgisine Gore Hasar Notu Ekleyen Fonksiyonum ---
bool SinglyLinkedList::idGoreHasarNotuEkle(int kitapID, const std::string& hasarNotu) {
    Kitap* bulunanKitap = idGoreKitapAra(kitapID);
    if (bulunanKitap != nullptr) {
        bulunanKitap->hasarNotuEkle(hasarNotu);
        // Mesaj main.cpp'de veriliyor.
        return true;
    }
    // Mesaj main.cpp'de veriliyor.
    return false;
}

// --- Hasarli Kitaplari Yazdiran Fonksiyonum ---
void SinglyLinkedList::hasarliKitaplariYazdir() const {
    if (isEmpty()) {
        std::cout << "Kitap listesi bostur." << std::endl;
        return;
    }
    std::cout << "\n--- HASARLI KITAPLAR (Ana Liste) ---" << std::endl;
    Node* temp = head;
    bool hasarliKitapBulundu = false;
    int sayac = 1;
    while (temp != nullptr) {
        if (temp->kitap.hasarNotu != "Yok" && !temp->kitap.hasarNotu.empty()) {
            std::cout << "\nHasarli Kitap " << sayac++ << ":" << std::endl;
            temp->kitap.bilgileriYazdir();
            hasarliKitapBulundu = true;
        }
        temp = temp->sonraki;
    }
    if (!hasarliKitapBulundu) {
        std::cout << "Listede hasarli kitap bulunmamaktadir." << std::endl;
    }
    std::cout << "--- HASARLI KITAPLAR LISTE SONU ---" << std::endl;
}

// --- Ana Listenin Basini Donduren Gecici Fonksiyonum (Raporlama Icin) ---
Node* SinglyLinkedList::getHeadGecici() {
    return head;
}

// --- YENI FONKSIYONUM: Sayfa Sayisina Gore Kucukten Buyuge Sirala ---
void SinglyLinkedList::sayfaSayisinaGoreSirala() {
    if (isEmpty() || head->sonraki == nullptr) {
        // Mesaji main.cpp'de verelim veya burada da olabilir.
        std::cout << "Listede siralama yapmak icin yeterli kitap bulunmamaktadir." << std::endl;
        return;
    }
    bool takasOlduMu;
    Node* simdiki;
    Node* enSonSiralanan = nullptr;

    // std::cout << "Kitaplar sayfa sayisina gore siralaniyor..." << std::endl; // Mesaji main.cpp'de verelim.
    do {
        takasOlduMu = false;
        simdiki = head;
        while (simdiki->sonraki != enSonSiralanan) {
            if (simdiki->kitap.sayfaSayisi > simdiki->sonraki->kitap.sayfaSayisi) {
                Kitap gecici = simdiki->kitap;
                simdiki->kitap = simdiki->sonraki->kitap;
                simdiki->sonraki->kitap = gecici;
                takasOlduMu = true;
            }
            simdiki = simdiki->sonraki;
        }
        enSonSiralanan = simdiki;
    } while (takasOlduMu);
    // std::cout << "Kitaplar sayfa sayisina gore siralandi." << std::endl; // Mesaji main.cpp'de verelim.
}

// --- YENI FONKSIYONUM: En Eski 5 Kitabi Listele (Basim Yilina Gore) ---
void SinglyLinkedList::enEskiBesKitabiListele() {
    // Mesaji main.cpp'de verelim veya burada da olabilir.
    // std::cout << "\n--- En Eski 5 Kitap (Basim Yilina Gore) ---" << std::endl;
    if (isEmpty()) {
        std::cout << "Listede hic kitap bulunmamaktadir." << std::endl;
        return;
    }
    std::vector<Kitap> kitapVektoru;
    Node* gezici = head;
    while (gezici != nullptr) {
        kitapVektoru.push_back(gezici->kitap);
        gezici = gezici->sonraki;
    }

    if (kitapVektoru.empty()) {
        std::cout << "Listede hic kitap bulunmamaktadir." << std::endl;
        return;
    }

    std::sort(kitapVektoru.begin(), kitapVektoru.end(),
        [](const Kitap& a, const Kitap& b) {
            return a.basimYili < b.basimYili;
        }
    );

    // std::cout << "En eski kitaplar (basim yilina gore):" << std::endl; // Mesaji main.cpp'de verelim.
    int gosterilecekAdet = std::min(5, (int)kitapVektoru.size());

    if (gosterilecekAdet == 0) {
        std::cout << "Listede kitap yok." << std::endl; // Bu durum ustteki isEmpty ile yakalanmali.
    }
    else {
        for (int i = 0; i < gosterilecekAdet; ++i) {
            std::cout << "\nEski Kitap " << (i + 1) << ":" << std::endl;
            kitapVektoru[i].bilgileriYazdir();
        }
    }
    // std::cout << "--- En Eski Kitaplar Liste Sonu ---" << std::endl; // Mesaji main.cpp'de verelim.
}