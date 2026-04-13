// BinarySearchTree.cpp

#include "BinarySearchTree.h" // Kendi yazdigim BinarySearchTree.h dosyasini dahil ediyorum.
#include "Kitap.h"            // BinarySearchTree icinde Kitap nesneleriyle calisacagim.
#include <iostream>           // Ekrana yazi yazdirmak (cout) icin.
#include <vector>             // Raporlama fonksiyonlarinda kitaplari gecici bir vektorde toplamak icin.
#include <string>             // String kullanimi icin.
#include <algorithm>          // std::sort, std::min gibi algoritmalar icin.
#include <stdexcept>          // Hata firlatmak icin.
#include <chrono>             // Tarih ve zaman islemleri icin.
#include <ctime>              // Tarih ve zaman islemleri icin.
#include <iomanip>            // std::get_time ve std::put_time icin (tarih formatlama/ayristirma).
#include <sstream>            // std::istringstream (tarih stringini ayristirmak) icin.
#include <functional>         // std::function icin (lambda fonksiyonunu saklamak icin).

// --- YARDIMCI FONKSIYON: Iki tarih string'i arasindaki gun farkini hesaplamak icin ---
// Bu fonksiyon sinifin disinda, global bir yardimci olarak tanimlandi.
// "GG-AA-YYYY" formatindaki iki tarihi alir.
// tarihStr2 daha sonraki bir tarihse pozitif, daha onceyse negatif deger dondurur.
// Eger tarih formatlari yanlissa veya cevirme basarisiz olursa -9999 gibi ozel bir deger dondurur.
long long hesaplaGunFarki(const std::string& tarihStr1, const std::string& tarihStr2) {
    std::tm tm1 = {};
    std::tm tm2 = {};

    if (tarihStr1.length() != 10 || tarihStr2.length() != 10) { // Temel format kontrolu
        //std::cerr << "Uyari: Tarih string uzunluklari gecersiz." << std::endl;
        return -9999;
    }

    // String'den std::tm'ye donusturme islemleri
    // std::get_time, C++11'den itibaren standartlastirildi.
    if (!(std::istringstream(tarihStr1) >> std::get_time(&tm1, "%d-%m-%Y"))) {
        //std::cerr << "Uyari: Tarih 1 formati ('" << tarihStr1 << "') gecersiz." << std::endl;
        return -9999;
    }
    if (!(std::istringstream(tarihStr2) >> std::get_time(&tm2, "%d-%m-%Y"))) {
        //std::cerr << "Uyari: Tarih 2 formati ('" << tarihStr2 << "') gecersiz." << std::endl;
        return -9999;
    }

    // Tarihlerin geçerli olup olmadýðýný basitçe kontrol edelim (örn: gün 1-31, ay 1-12)
    // mktime bunu bir ölçüde yapar ama biz de temel bir kontrol ekleyebiliriz.
    // tm_year yildan 1900 çýkarýlmýþ halidir, tm_mon 0-11 arasýdýr.
    tm1.tm_year += 0; // Sadece Visual Studio'nun C4244 uyarýsýný engellemek için (tm_year'i kullanmak)
    tm2.tm_year += 0;


    std::time_t time1 = std::mktime(&tm1);
    std::time_t time2 = std::mktime(&tm2);

    if (time1 == -1 || time2 == -1) {
        //std::cerr << "Uyari: Tarihler time_t'ye cevirilemedi." << std::endl;
        return -9999;
    }

    auto tp1 = std::chrono::system_clock::from_time_t(time1);
    auto tp2 = std::chrono::system_clock::from_time_t(time2);

    // Iki zaman noktasi arasindaki farki saat olarak alip 24'e bolerek gunu buluyorum.
    auto farkSaat = std::chrono::duration_cast<std::chrono::hours>(tp2 - tp1);

    return farkSaat.count() / 24;
}


// --- Kurucu Fonksiyonum (Constructor) ---
BinarySearchTree::BinarySearchTree() {
    root = nullptr;
}

// --- Yikici Fonksiyonum (Destructor) ---
BinarySearchTree::~BinarySearchTree() {
    destroyRecursive(root);
}

// Agactaki tum dugumleri ozyineli olarak silen yardimci fonksiyonum.
void BinarySearchTree::destroyRecursive(TreeNode* dugum) {
    if (dugum != nullptr) {
        destroyRecursive(dugum->sol);
        destroyRecursive(dugum->sag);
        delete dugum;
    }
}

// --- Agacimin Bos Olup Olmadigini Kontrol Eden Fonksiyonum ---
bool BinarySearchTree::isEmpty() const {
    return root == nullptr;
}

// --- Agacima Yeni Bir Kitap Eklemek Icin Kullanicinin Cagiracagi Fonksiyon ---
void BinarySearchTree::ekle(Kitap eklenecekKitap) {
    root = ekleRecursive(root, eklenecekKitap);
}

// --- Agaca Yeni Bir Kitap Eklemek Icin Ozyineli Yardimci Fonksiyonum ---
TreeNode* BinarySearchTree::ekleRecursive(TreeNode* dugum, Kitap eklenecekKitap) {
    if (dugum == nullptr) {
        return new TreeNode(eklenecekKitap);
    }
    // Kitap.id'nin public oldugunu varsayiyorum.
    if (eklenecekKitap.id < dugum->kitap.id) {
        dugum->sol = ekleRecursive(dugum->sol, eklenecekKitap);
    }
    else if (eklenecekKitap.id > dugum->kitap.id) {
        dugum->sag = ekleRecursive(dugum->sag, eklenecekKitap);
    }
    return dugum;
}

// --- Agaci InOrder Sirasinda Gezip Kitaplari Yazdiran Fonksiyonum ---
void BinarySearchTree::inOrderDolas() const {
    if (isEmpty()) {
        std::cout << "Agac (BST) bostur." << std::endl;
        return;
    }
    std::cout << "\n--- AGAC DOLASIMI (InOrder - ID'ye Gore Sirali) ---" << std::endl;
    inOrderRecursive(root);
    std::cout << "\n--- AGAC DOLASIMI SONU ---" << std::endl;
}

void BinarySearchTree::inOrderRecursive(TreeNode* dugum) const {
    if (dugum != nullptr) {
        inOrderRecursive(dugum->sol);
        dugum->kitap.bilgileriYazdir();
        inOrderRecursive(dugum->sag);
    }
}

// --- Agaci PreOrder Sirasinda Gezip Kitaplari Yazdiran Fonksiyonum ---
void BinarySearchTree::preOrderDolas() const {
    if (isEmpty()) {
        std::cout << "Agac (BST) bostur." << std::endl;
        return;
    }
    std::cout << "\n--- AGAC DOLASIMI (PreOrder) ---" << std::endl;
    preOrderRecursive(root);
    std::cout << "\n--- AGAC DOLASIMI SONU ---" << std::endl;
}

void BinarySearchTree::preOrderRecursive(TreeNode* dugum) const {
    if (dugum != nullptr) {
        dugum->kitap.bilgileriYazdir();
        preOrderRecursive(dugum->sol);
        preOrderRecursive(dugum->sag);
    }
}

// --- Agaci PostOrder Sirasinda Gezip Kitaplari Yazdiran Fonksiyonum ---
void BinarySearchTree::postOrderDolas() const {
    if (isEmpty()) {
        std::cout << "Agac (BST) bostur." << std::endl;
        return;
    }
    std::cout << "\n--- AGAC DOLASIMI (PostOrder) ---" << std::endl;
    postOrderRecursive(root);
    std::cout << "\n--- AGAC DOLASIMI SONU ---" << std::endl;
}

void BinarySearchTree::postOrderRecursive(TreeNode* dugum) const {
    if (dugum != nullptr) {
        postOrderRecursive(dugum->sol);
        postOrderRecursive(dugum->sag);
        dugum->kitap.bilgileriYazdir();
    }
}

// --- ID'ye Gore Bir Kitabi Agacta Aramak Icin Fonksiyonum ---
Kitap* BinarySearchTree::ara(int arananID) const {
    TreeNode* bulunanDugum = araRecursive(root, arananID);
    if (bulunanDugum != nullptr) {
        return &(bulunanDugum->kitap);
    }
    else {
        return nullptr;
    }
}

TreeNode* BinarySearchTree::araRecursive(TreeNode* dugum, int arananID) const {
    if (dugum == nullptr || dugum->kitap.id == arananID) {
        return dugum;
    }
    if (arananID < dugum->kitap.id) {
        return araRecursive(dugum->sol, arananID);
    }
    else {
        return araRecursive(dugum->sag, arananID);
    }
}

// --- Odunc Alma Suresi Raporu Icin Ozyineli Yardimci Fonksiyonum ---
void BinarySearchTree::oduncSuresiRaporuRecursive(TreeNode* dugum, std::vector<Kitap>& altindaListe, std::vector<Kitap>& ustundeListe, const std::string& bugununTarihi) const {
    if (dugum == nullptr) return;

    if (!dugum->kitap.eklenmeZamani.empty() && dugum->kitap.eklenmeZamani != "Belirtilmedi") {
        long long gunFarki = hesaplaGunFarki(dugum->kitap.eklenmeZamani, bugununTarihi);

        if (gunFarki == -9999) {
            // std::cout << "Uyari: ID " << dugum->kitap.id << " (" << dugum->kitap.ad 
            //           << ") icin tarih farki hesaplanamadi. Odunc tarihi: " << dugum->kitap.eklenmeZamani << std::endl;
        }
        else if (gunFarki >= 0 && gunFarki < 30) {
            altindaListe.push_back(dugum->kitap);
        }
        else if (gunFarki >= 30) {
            ustundeListe.push_back(dugum->kitap);
        }
    }

    oduncSuresiRaporuRecursive(dugum->sol, altindaListe, ustundeListe, bugununTarihi);
    oduncSuresiRaporuRecursive(dugum->sag, altindaListe, ustundeListe, bugununTarihi);
}

// --- Odunc Alma Suresi Raporunu Olusturan Public Fonksiyonum ---
void BinarySearchTree::oduncAlmaSuresiRaporu(const std::string& bugununTarihi) const {
    std::vector<Kitap> altinda30Gun;
    std::vector<Kitap> ustunde30Gun;
    oduncSuresiRaporuRecursive(root, altinda30Gun, ustunde30Gun, bugununTarihi);

    std::cout << "\n--- Odunc Alma Suresi Raporu (Kriter: 30 Gun) ---" << std::endl;

    std::cout << "\n** 30 Gunden AZ Sureyle Odunc Alinanlar: **" << std::endl;
    if (altinda30Gun.empty()) {
        std::cout << "Bu kategoride kitap bulunamadi." << std::endl;
    }
    else {
        for (const auto& kitap : altinda30Gun) kitap.bilgileriYazdir();
    }

    std::cout << "\n** 30 Gun ve DAHA FAZLA Sureyle Odunc Alinanlar: **" << std::endl;
    if (ustunde30Gun.empty()) {
        std::cout << "Bu kategoride kitap bulunamadi." << std::endl;
    }
    else {
        for (const auto& kitap : ustunde30Gun) kitap.bilgileriYazdir();
    }
}

// Basim yili raporu icin ozyineli yardimci fonksiyonum
void BinarySearchTree::basimYiliRaporuRecursive(TreeNode* dugum, std::vector<Kitap>& onceListe, std::vector<Kitap>& sonraListe) const {
    if (dugum == nullptr) return;
    if (dugum->kitap.basimYili < 1950) {
        onceListe.push_back(dugum->kitap);
    }
    else {
        sonraListe.push_back(dugum->kitap);
    }
    basimYiliRaporuRecursive(dugum->sol, onceListe, sonraListe);
    basimYiliRaporuRecursive(dugum->sag, onceListe, sonraListe);
}

// Basim yili raporunu olusturan public fonksiyonum
void BinarySearchTree::basimYiliRaporu1950() const {
    std::vector<Kitap> once1950;
    std::vector<Kitap> sonra1950;
    basimYiliRaporuRecursive(root, once1950, sonra1950);

    std::cout << "\n--- Basim Yili Raporu (Odunc Alinan Kitaplar - Kriter: 1950) ---" << std::endl;
    std::cout << "** 1950 Oncesi Basilan Odunc Kitaplar: **" << std::endl;
    if (once1950.empty()) {
        std::cout << "Bu kategoride kitap bulunamadi." << std::endl;
    }
    else {
        for (const auto& kitap : once1950) kitap.bilgileriYazdir();
    }

    std::cout << "\n** 1950 ve Sonrasinda Basilan Odunc Kitaplar: **" << std::endl;
    if (sonra1950.empty()) {
        std::cout << "Bu kategoride kitap bulunamadi." << std::endl;
    }
    else {
        for (const auto& kitap : sonra1950) kitap.bilgileriYazdir();
    }
}

// --- 1950 Oncesi Basilan VE 30 Gunden Fazla Odunc Alinanlar Raporu ---
void BinarySearchTree::rapor1950OncesiVe30GunUstu(const std::string& bugununTarihi) const {
    std::cout << "\n--- Rapor: 1950 Oncesi Basilan VE 30 Gunden Fazla Odunc Alinanlar ---" << std::endl;
    if (isEmpty()) {
        std::cout << "Odunc kitap agaci bostur." << std::endl;
        return;
    }
    std::vector<Kitap> sonucListesi;

    // Agaci gezip kosullara uyanlari bulmak icin bir std::function (lambda) tanimliyorum.
    // Bu, recursive bir fonksiyon olacak ve dis degiskenlere ([&] ile) erisebilecek.
    std::function<void(TreeNode*)> gezinVeIkiKosuluKontrolEt; // Once sadece bildiriyorum.
    gezinVeIkiKosuluKontrolEt =
        [&](TreeNode* dugum) { // Lambda fonksiyonumun tanimi burada basliyor.
        if (dugum == nullptr) return;

        gezinVeIkiKosuluKontrolEt(dugum->sol); // Once solu gez.

        // Kosullari kontrol ediyorum.
        if (dugum->kitap.basimYili < 1950) {
            if (!dugum->kitap.eklenmeZamani.empty() && dugum->kitap.eklenmeZamani != "Belirtilmedi") {
                long long gunFarki = hesaplaGunFarki(dugum->kitap.eklenmeZamani, bugununTarihi);
                if (gunFarki != -9999 && gunFarki >= 30) {
                    sonucListesi.push_back(dugum->kitap);
                }
            }
        }
        gezinVeIkiKosuluKontrolEt(dugum->sag); // Sonra sagi gez.
        }; // Lambda fonksiyonumun tanimi burada bitiyor (noktali virgul onemli).

    gezinVeIkiKosuluKontrolEt(root); // Lambda fonksiyonumu agacin kokunden baslatarak cagiriyorum.

    if (sonucListesi.empty()) {
        std::cout << "Bu kriterlere uyan kitap bulunamadi." << std::endl;
    }
    else {
        for (const auto& kitap : sonucListesi) {
            kitap.bilgileriYazdir();
        }
    }
}

// Filtreleme fonksiyonlari
void BinarySearchTree::yayineviFiltreleRecursive(TreeNode* dugum, const std::string& yayineviTuru, std::vector<Kitap>& sonucListesi) const {
    if (dugum == nullptr) return;
    if (dugum->kitap.yayineviTuru == yayineviTuru) {
        sonucListesi.push_back(dugum->kitap);
    }
    yayineviFiltreleRecursive(dugum->sol, yayineviTuru, sonucListesi);
    yayineviFiltreleRecursive(dugum->sag, yayineviTuru, sonucListesi);
}

void BinarySearchTree::filtreleYerliYabanciYayinevi(const std::string& yayineviTuru) const {
    std::vector<Kitap> sonuc;
    yayineviFiltreleRecursive(root, yayineviTuru, sonuc);
    std::cout << "\n--- Filtre Sonucu: Yayinevi Turu '" << yayineviTuru << "' Olan Odunc Kitaplar ---" << std::endl;
    if (sonuc.empty()) {
        std::cout << "Bu kriterlere uyan kitap bulunamadi." << std::endl;
    }
    else {
        for (const auto& kitap : sonuc) kitap.bilgileriYazdir();
    }
}

void BinarySearchTree::dilFiltreleRecursive(TreeNode* dugum, const std::string& dil, std::vector<Kitap>& sonucListesi) const {
    if (dugum == nullptr) return;
    if (dugum->kitap.dil == dil) {
        sonucListesi.push_back(dugum->kitap);
    }
    dilFiltreleRecursive(dugum->sol, dil, sonucListesi);
    dilFiltreleRecursive(dugum->sag, dil, sonucListesi);
}

void BinarySearchTree::filtreleDil(const std::string& dil) const {
    std::vector<Kitap> sonuc;
    dilFiltreleRecursive(root, dil, sonuc);
    std::cout << "\n--- Filtre Sonucu: Dili '" << dil << "' Olan Odunc Kitaplar ---" << std::endl;
    if (sonuc.empty()) {
        std::cout << "Bu kriterlere uyan kitap bulunamadi." << std::endl;
    }
    else {
        for (const auto& kitap : sonuc) kitap.bilgileriYazdir();
    }
}

void BinarySearchTree::sayfaUzunluguFiltreleRecursive(TreeNode* dugum, int sayfaLimiti, bool azMi, std::vector<Kitap>& sonucListesi) const {
    if (dugum == nullptr) return;
    bool kosulSaglandi = false;
    if (azMi) {
        if (dugum->kitap.sayfaSayisi < sayfaLimiti) kosulSaglandi = true;
    }
    else {
        if (dugum->kitap.sayfaSayisi >= sayfaLimiti) kosulSaglandi = true;
    }
    if (kosulSaglandi) {
        sonucListesi.push_back(dugum->kitap);
    }
    sayfaUzunluguFiltreleRecursive(dugum->sol, sayfaLimiti, azMi, sonucListesi);
    sayfaUzunluguFiltreleRecursive(dugum->sag, sayfaLimiti, azMi, sonucListesi);
}

void BinarySearchTree::filtreleSayfaUzunlugu(int sayfaLimiti, bool azMi) const {
    std::vector<Kitap> sonuc;
    sayfaUzunluguFiltreleRecursive(root, sayfaLimiti, azMi, sonuc);
    std::cout << "\n--- Filtre Sonucu: Sayfa Sayisi " << sayfaLimiti << (azMi ? "'den Az" : "'den Cok veya Esit") << " Olan Odunc Kitaplar ---" << std::endl;
    if (sonuc.empty()) {
        std::cout << "Bu kriterlere uyan kitap bulunamadi." << std::endl;
    }
    else {
        for (const auto& kitap : sonuc) kitap.bilgileriYazdir();
    }
}