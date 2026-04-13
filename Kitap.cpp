// Kitap.cpp

#include "Kitap.h"     // Kendi yazdigim Kitap.h dosyasini dahil ediyorum.
#include <iostream>   // Ekrana yazi yazdirmak (cout) icin.
#include <iomanip>    // Ortalama puani duzgun yazdirmak icin (std::fixed, std::setprecision).
#include <vector>     // yorumlarListesi icin.
#include <string>     // Stringler icin.

// Parametreli Kurucu Fonksiyonum: Yeni bir kitap nesnesi olustururken cagiriyorum.
Kitap::Kitap(int _id, std::string _ad, std::string _yazar, int _basimYili, int _sayfaSayisi) {
    id = _id;
    ad = _ad;
    yazar = _yazar;
    basimYili = _basimYili;
    sayfaSayisi = _sayfaSayisi;

    eklenmeZamani = "Belirtilmedi";
    hasarNotu = "Yok";
    kategori = "Genel";
    dil = "Turkce";
    yayineviTuru = "Yerli";
    ortalamaPuan = 0.0;
    puanlayanSayisi = 0;
    oduncAlindiMi = false;
    okunduMu = false;
}

// Varsayilan Kurucu Fonksiyonum: Bos bir kitap nesnesi olusturmak icin.
Kitap::Kitap() {
    id = 0;
    ad = "Bilinmiyor";
    yazar = "Bilinmiyor";
    basimYili = 0;
    sayfaSayisi = 0;
    eklenmeZamani = "Belirtilmedi";
    hasarNotu = "Yok";
    kategori = "Genel";
    dil = "Turkce";
    yayineviTuru = "Yerli";
    ortalamaPuan = 0.0;
    puanlayanSayisi = 0;
    oduncAlindiMi = false;
    okunduMu = false;
}

// Kitabin Bilgilerini Ekrana Yazdiran Fonksiyonum.
void Kitap::bilgileriYazdir() const {
    std::cout << "------------------------------" << std::endl;
    std::cout << "ID: " << id << std::endl;
    std::cout << "Ad: " << ad << std::endl;
    std::cout << "Yazar: " << yazar << std::endl;
    std::cout << "Basim Yili: " << basimYili << std::endl;
    std::cout << "Sayfa Sayisi: " << sayfaSayisi << std::endl;
    std::cout << "Eklenme Zamani/Odunc Tarihi: " << eklenmeZamani << std::endl;
    std::cout << "Hasar Notu: " << hasarNotu << std::endl;
    std::cout << "Kategori: " << kategori << std::endl;
    std::cout << "Dil: " << dil << std::endl;
    std::cout << "Yayinevi Turu: " << yayineviTuru << std::endl;
    std::cout << "Ortalama Puan: " << std::fixed << std::setprecision(1) << ortalamaPuan
        << " (" << puanlayanSayisi << " kisi puanladi)" << std::endl;
    std::cout << "Odunc Durumu: " << (oduncAlindiMi ? "Odunc Verildi" : "Mevcut") << std::endl;
    std::cout << "Okunma Durumu: " << (okunduMu ? "Okundu" : "Okunmadi") << std::endl;

    if (!yorumlarListesi.empty()) {
        std::cout << "Yorumlar:" << std::endl;
        for (const std::string& yorum : yorumlarListesi) {
            std::cout << "- " << yorum << std::endl;
        }
    }
    std::cout << "------------------------------" << std::endl;
}

// Kitaba Yeni Bir Yorum Eklemek Icin Fonksiyonum.
void Kitap::yorumEkle(const std::string& yorum) {
    yorumlarListesi.push_back(yorum);
}

// Kitaba Hasar Notu Eklemek Icin Fonksiyonum.
void Kitap::hasarNotuEkle(const std::string& notu) {
    hasarNotu = notu;
}

// Kitaba Yeni Bir Puan Eklemek Icin Fonksiyonum.
void Kitap::puanEkle(int verilenPuan) {
    if (verilenPuan < 1 || verilenPuan > 5) {
        std::cout << "Gecersiz puan! Puan 1 ile 5 arasinda olmalidir." << std::endl;
        return;
    }
    double eskiToplamPuan = ortalamaPuan * puanlayanSayisi;
    puanlayanSayisi++;
    ortalamaPuan = (eskiToplamPuan + verilenPuan) / puanlayanSayisi;

    // Kullaniciya bilgi veren cout satirini main.cpp'ye tasidim, burada sadece hesaplama yapiyorum.
    // std::cout << "'" << ad << "' adli kitaba " << verilenPuan << " puan verildi. Yeni ortalama: " 
    //           << std::fixed << std::setprecision(1) << ortalamaPuan 
    //           << " (" << puanlayanSayisi << " kisi puanladi)" << std::endl;
}