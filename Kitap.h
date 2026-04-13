// Kitap.h
#ifndef KITAP_H
#define KITAP_H

#include <string>   // std::string kullanacagim.
#include <vector>   // Yorumlar icin std::vector kullanacagim.
#include <iostream> // Ekrana bir seyler yazdirmak icin (bilgileriYazdir).

// Kitaplarimin bilgilerini tutacagim sinifim bu.
class Kitap {
public: // Herkesin erisebilmesi icin public yaptim.
    int id;                 // Kitabimin benzersiz numarasi.
    std::string ad;         // Kitabimin adi.
    std::string yazar;      // Kitabimin yazari.
    int basimYili;          // Kitabimin basilma yili.
    int sayfaSayisi;        // Kitabimin kac sayfa oldugu.
    std::string eklenmeZamani;  // Kutuphaneye ne zaman eklendigi veya odunc alindigi tarih.
    std::string hasarNotu;      // Eger kitap hasarliysa buraya not dusecegim.
    std::string kategori;       // Kitabimin turu (Roman, Tarih gibi).
    std::string dil;            // Kitabimin dili (Turkce, Ingilizce gibi).
    std::string yayineviTuru;   // Yayýnevinin yerli mi yabanci mi oldugu.
    double ortalamaPuan;        // Kullanicilarin verdigi puanlarin ortalamasi.
    int puanlayanSayisi;        // Bu kitaba kac kisinin puan verdigini burada tutacagim.
    bool oduncAlindiMi;         // Kitap su an odunc verilmis mi? (true/false).
    bool okunduMu;              // Kullanici bu kitabi okudu mu? (true/false).
    std::vector<std::string> yorumlarListesi; // Kitaba yapilan yorumlari bu listede tutacagim.

    // Yeni bir Kitap nesnesi olustururken bu kurucu fonksiyonlar calisacak.
    Kitap(int _id, std::string _ad, std::string _yazar, int _basimYili, int _sayfaSayisi); // Bilgileri alarak olusturma.
    Kitap(); // Hic bilgi vermeden bos bir kitap olusturma.

    // Kitabimin yapabilecegi seyler (fonksiyonlar).
    void bilgileriYazdir() const;           // Kitabin tum bilgilerini ekrana yazdiracak.
    void yorumEkle(const std::string& yorum); // Kitaba yeni bir yorum ekleyecek.
    void hasarNotuEkle(const std::string& notu); // Kitaba hasar notu ekleyecek.
    void puanEkle(int verilenPuan);         // Kitaba yeni bir puan (1-5 arasi) ekleyip ortalamayi guncelleyecek.
};

#endif //KITAP_H