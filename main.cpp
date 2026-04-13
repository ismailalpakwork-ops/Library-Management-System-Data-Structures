// main.cpp (Tum Moduller Entegre Edilmis Hali - Turkce Karakter Yok)
#include <iostream>
#include <string>
#include <limits>    // Sayisal limitler icin (std::numeric_limits)
#include <stdexcept> // Hata firlatma icin (std::runtime_error)
#include <vector>    // Gecici listeler icin
#include <chrono>    // Tarih ve zaman islemleri icin
#include <ctime>     // Tarih ve zaman islemleri icin
#include <iomanip>   // std::put_time ve std::get_time icin
#include <sstream>   // std::stringstream icin
#include <algorithm> // std::sort, std::min (SLL enEskiBesKitabiListele icin)

#include "Kitap.h"
#include "Node.h"                     // SLL icin
#include "SinglyLinkedList.h"
#include "NodeCD.h"                   // DCLL icin
#include "DoublyCircularLinkedList.h"
#include "StackNode.h"                // Stack icin
#include "Stack.h"
#include "QueueNode.h"                // Queue icin
#include "Queue.h"
#include "TreeNode.h"                 // BST icin
#include "BinarySearchTree.h"
#include "HashNode.h"                 // HashTable icin
#include "HashTable.h"
#include "SinglyCircularLinkedList.h" // Personel Modul 2 raporlari

// Kullanicidan duzgun bir sayi almak icin yazdigim fonksiyon.
int getIntegerInput(const std::string& prompt) {
    int input;
    while (true) {
        std::cout << prompt;
        std::cin >> input;
        if (std::cin.good()) {
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            return input;
        }
        else {
            std::cout << "Gecersiz giris. Lutfen bir sayi giriniz." << std::endl;
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}

// Kullanicidan yazi (string) almak icin yazdigim fonksiyon.
std::string getStringInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    return input;
}

// Bugunun tarihini "GG-AA-YYYY" formatinda string olarak almak icin yazdigim fonksiyon.
std::string getBugununTarihi() {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
    std::tm now_tm_buf;
    localtime_s(&now_tm_buf, &now_time_t);
    std::ostringstream oss;
    oss << std::put_time(&now_tm_buf, "%d-%m-%Y");
    return oss.str();
}

// Stack'teki kitaplari gecici bir vektore kopyalayan yardimci fonksiyon.
// Orijinal Stack'i bozmaz (pop edip geri pushlar).
std::vector<Kitap> stackToVectorNonDestructive(Stack& kaynakStack) {
    std::vector<Kitap> kitapVektoru;
    Stack geciciYedek;

    while (!kaynakStack.isEmpty()) {
        try {
            Kitap k = kaynakStack.pop();
            kitapVektoru.push_back(k);
            geciciYedek.push(k);
        }
        catch (const std::runtime_error& /* e_kullanilmiyor_sv1 */) {
            // std::cerr << "Uyari (stackToVector pop): " << e.what() << std::endl;
            break;
        }
    }
    while (!geciciYedek.isEmpty()) {
        try {
            kaynakStack.push(geciciYedek.pop());
        }
        catch (const std::runtime_error& /* e_kullanilmiyor_sv2 */) {
            // std::cerr << "Uyari (stackToVector push): " << e.what() << std::endl;
            break;
        }
    }
    // Vektordeki sira, stack'ten pop edilme sirasi olacak (yani stack'in tersi).
    // Eger stack'in orijinal (LIFO) sirasiyla (tepeden asagiya) isteniyorsa, vektoru ters cevirmek gerekir.
    // std::reverse(kitapVektoru.begin(), kitapVektoru.end()); 
    return kitapVektoru;
}


// --- Personel Menusu ---
void personelMenu(SinglyLinkedList& anaKitapListesi,
    Stack& oduncStack,
    Stack& iadeStack,
    Queue& talepKuyrugu,
    HashTable& kitapHashTablosu) {
    int secim;
    do {
        std::cout << "\n--- PERSONEL MENU ---" << std::endl;
        std::cout << "--- Modul 1: Kitap Yonetimi ---" << std::endl;
        std::cout << "1. Kitap Ekle (Manuel)" << std::endl;
        std::cout << "2. Ismine Gore Kitabi Duzenle" << std::endl;
        std::cout << "3. ID Bilgisine Gore Kitabi Sil" << std::endl;
        std::cout << "4. Tum Kitaplari Listele (Ana Liste)" << std::endl;
        std::cout << "5. ID Bilgisine Gore Kitap Ara (Ana Liste)" << std::endl;
        std::cout << "6. Toplam Kitap Sayisi (Ana Liste)" << std::endl;
        std::cout << "7. Sayfa Sayisina Gore Kitaplari Sirala" << std::endl; // Bu madde burada olmali
        std::cout << "8. Basim Yilina Gore En Eski 5 Kitabi Listele" << std::endl; // Bu madde de
        std::cout << "9. Kitaba Hasar Notu Ekle (Ana Liste)" << std::endl;
        std::cout << "10. Hasarli Kitaplari Yazdir (Ana Liste)" << std::endl;
        std::cout << "--- Modul 2: Raporlama ---" << std::endl;
        std::cout << "11. Odunc Alinan Kitaplar Raporu" << std::endl;
        std::cout << "12. Iade Edilen Kitaplar Raporu" << std::endl;
        std::cout << "13. Erisilebilir Kitaplar Listesi" << std::endl;
        std::cout << "--- Modul 3: Kitap Talepleri ---" << std::endl;
        std::cout << "14. Gelen Kitap Taleplerini Goruntule" << std::endl;
        std::cout << "15. Tedarik Edilen Talebi Kutuphaneye Ekle" << std::endl;
        std::cout << "--- Modul 4: Odunc Kitap Analizi (Agac) ---" << std::endl;
        std::cout << "16. Odunc Kitaplar Sure Raporu (30 Gun)" << std::endl;
        std::cout << "17. Odunc Kitaplar Basim Yili Raporu (1950)" << std::endl;
        std::cout << "18. Rapor: 1950 Oncesi & 30 Gun Ustu Odunc" << std::endl;
        std::cout << "--- Modul 5: Puanlama Raporu (Hash Tablosu) ---" << std::endl;
        std::cout << "19. Odunc Alinan Kitap Puanlarini Guncelle/Ekle (Stack'ten Hash'e)" << std::endl;
        std::cout << "20. Ortalama Puani 4 ve Uzeri Olan Kitaplari Listele (Hash'ten)" << std::endl;
        std::cout << "0. Ana Menu'ye Don" << std::endl;
        secim = getIntegerInput("Seciminizi yapiniz: ");

        try {
            switch (secim) {
            case 1: {
                std::cout << "\n--- Kitap Ekleme (Ana Listeye Manuel) ---" << std::endl;
                int id = getIntegerInput("Kitap ID: ");
                if (anaKitapListesi.idGoreKitapAra(id) != nullptr) { std::cout << "Bu ID zaten var." << std::endl; break; }
                std::string ad = getStringInput("Kitap Adi: ");
                std::string yazar = getStringInput("Yazar Adi: ");
                int basimYili = getIntegerInput("Basim Yili: ");
                int sayfaSayisi = getIntegerInput("Sayfa Sayisi: ");
                Kitap yeniKitap(id, ad, yazar, basimYili, sayfaSayisi);
                yeniKitap.eklenmeZamani = getBugununTarihi();
                yeniKitap.kategori = getStringInput("Kategori: ");
                yeniKitap.dil = getStringInput("Dil (Turkce/Ingilizce): ");
                yeniKitap.yayineviTuru = getStringInput("Yayinevi Turu (Yerli/Yabanci): ");
                anaKitapListesi.kitapEkle(yeniKitap);
                std::cout << "'" << ad << "' adli kitap ana listeye eklendi." << std::endl;
                break;
            }
            case 2: {
                std::cout << "\n--- Ismine Gore Kitap Duzenleme ---" << std::endl;
                std::string ad = getStringInput("Duzenlenecek kitabin adi: ");
                Kitap* mevcutKitap = anaKitapListesi.ismineGoreKitapBul(ad); // Bu fonksiyon SLL.cpp'de olmali
                if (!mevcutKitap) { std::cout << "'" << ad << "' adli kitap bulunamadi." << std::endl; break; }
                std::cout << "Mevcut Bilgiler:" << std::endl;
                mevcutKitap->bilgileriYazdir();
                std::cout << "Yeni bilgileri girin (degisiklik yoksa enter'a basin):" << std::endl;
                std::string yazar = getStringInput("Yeni Yazar (" + mevcutKitap->yazar + "): ");
                std::string yilStr = getStringInput("Yeni Basim Yili (" + std::to_string(mevcutKitap->basimYili) + "): ");
                std::string sayfaStr = getStringInput("Yeni Sayfa Sayisi (" + std::to_string(mevcutKitap->sayfaSayisi) + "): ");

                Kitap guncelBilgiler = *mevcutKitap; // Kopyasini al
                if (!yazar.empty()) guncelBilgiler.yazar = yazar;
                if (!yilStr.empty()) guncelBilgiler.basimYili = std::stoi(yilStr);
                if (!sayfaStr.empty()) guncelBilgiler.sayfaSayisi = std::stoi(sayfaStr);
                // Diger alanlar da benzer sekilde guncellenebilir
                anaKitapListesi.ismineGoreKitapDuzenle(ad, guncelBilgiler);
                break;
            }
            case 3: { std::cout << "\n--- ID Ile Kitap Silme ---" << std::endl; int id = getIntegerInput("Silinecek ID: "); anaKitapListesi.idGoreKitapSil(id); break; }
            case 4: std::cout << "\n--- Tum Kitaplar (Ana Liste) ---" << std::endl; anaKitapListesi.kitaplariListele(); break;
            case 5: { std::cout << "\n--- ID Ile Kitap Arama ---" << std::endl; int id = getIntegerInput("Aranacak ID: "); Kitap* b = anaKitapListesi.idGoreKitapAra(id); if (b) b->bilgileriYazdir(); else std::cout << "Bulunamadi." << std::endl; break; }
            case 6: std::cout << "\nAna listedeki toplam kitap: " << anaKitapListesi.toplamKitapSayisi() << std::endl; break;
            case 7: // Sayfa Sayisina Gore Kitaplari Sirala
                std::cout << "\n--- Sayfa Sayisina Gore Siralama ---" << std::endl;
                anaKitapListesi.sayfaSayisinaGoreSirala(); // Bu fonksiyon SLL.cpp'de olmali
                // Siralama fonksiyonu kendi icinde "siralandi" mesaji verip listeyi yazdirabilir.
                break;
            case 8: // Basim Yilina Gore En Eski 5 Kitabi Listele
                std::cout << "\n--- En Eski 5 Kitap (Basim Yili) ---" << std::endl;
                anaKitapListesi.enEskiBesKitabiListele(); // Bu fonksiyon SLL.cpp'de olmali
                break;
            case 9: { std::cout << "\n--- Hasar Notu Ekleme ---" << std::endl; int id = getIntegerInput("Kitap ID: "); std::string notu = getStringInput("Hasar Notu: "); anaKitapListesi.idGoreHasarNotuEkle(id, notu); break; }
            case 10: std::cout << "\n--- Hasarli Kitaplar ---" << std::endl; anaKitapListesi.hasarliKitaplariYazdir(); break;
            case 11: {
                std::cout << "\n--- Odunc Alinan Kitaplar Raporu ---" << std::endl;
                if (oduncStack.isEmpty()) { std::cout << "Odunc kitap yok." << std::endl; }
                else { SinglyCircularLinkedList rL; std::vector<Kitap> kV = stackToVectorNonDestructive(oduncStack); for (const auto& k : kV)rL.ekle(k); rL.listele(); }
                break;
            }
            case 12: {
                std::cout << "\n--- Iade Edilen Kitaplar Raporu ---" << std::endl;
                if (iadeStack.isEmpty()) { std::cout << "Iade edilmis kitap yok." << std::endl; }
                else { SinglyCircularLinkedList rL; std::vector<Kitap> kV = stackToVectorNonDestructive(iadeStack); for (const auto& k : kV)rL.ekle(k); rL.listele(); }
                break;
            }
            case 13: {
                std::cout << "\n--- Erisilebilir Kitaplar ---" << std::endl;
                if (anaKitapListesi.isEmpty()) { std::cout << "Kutuphane bos." << std::endl; }
                else { SinglyCircularLinkedList eKL; Node* curr = anaKitapListesi.getHeadGecici(); while (curr) { if (!curr->kitap.oduncAlindiMi) eKL.ekle(curr->kitap); curr = curr->sonraki; } if (eKL.isEmpty())std::cout << "Erisilebilir kitap yok." << std::endl; else eKL.listele(); }
                break;
            }
            case 14: {
                std::cout << "\n--- Gelen Talepler ---" << std::endl;
                if (talepKuyrugu.isEmpty())std::cout << "Talep yok." << std::endl; else talepKuyrugu.listele();
                break;
            }
            case 15: {
                std::cout << "\n--- Talepten Kitap Ekleme ---" << std::endl;
                if (talepKuyrugu.isEmpty()) { std::cout << "Talep yok." << std::endl;break; }
                KitapTalepDetayi t = talepKuyrugu.dequeue();
                std::cout << "Islenen talep: '" << t.kitapAdi << "' (Oncelik: " << t.oncelik << ")" << std::endl;
                int id = getIntegerInput("Kitap ID: ");
                if (anaKitapListesi.idGoreKitapAra(id)) { std::cout << "Bu ID zaten var." << std::endl;break; }
                std::string yazar = getStringInput("Yazar: ");
                int yil = getIntegerInput("Basim Yili: ");
                int sayfa = getIntegerInput("Sayfa Sayisi: ");
                Kitap k(id, t.kitapAdi, yazar, yil, sayfa);
                k.eklenmeZamani = getBugununTarihi();
                k.kategori = getStringInput("Kategori: ");
                k.dil = getStringInput("Dil: ");
                k.yayineviTuru = getStringInput("Yayinevi Turu: ");
                anaKitapListesi.kitapEkle(k);
                std::cout << "'" << k.ad << "' adli kitap kutuphaneye eklendi." << std::endl;
                break;
            }
            case 16: {
                std::cout << "\n--- Odunc Sure Raporu (Agac) ---" << std::endl;
                if (oduncStack.isEmpty()) { std::cout << "Odunc kitap yok." << std::endl;break; }
                BinarySearchTree agac; std::vector<Kitap> kV = stackToVectorNonDestructive(oduncStack); for (const auto& k : kV)agac.ekle(k);
                std::cout << "Odunc alinan kitaplar agaca eklendi." << std::endl; agac.oduncAlmaSuresiRaporu(getBugununTarihi());
                break;
            }
            case 17: {
                std::cout << "\n--- Odunc Basim Yili Raporu (Agac) ---" << std::endl;
                if (oduncStack.isEmpty()) { std::cout << "Odunc kitap yok." << std::endl;break; }
                BinarySearchTree agac; std::vector<Kitap> kV = stackToVectorNonDestructive(oduncStack); for (const auto& k : kV)agac.ekle(k);
                std::cout << "Odunc alinan kitaplar agaca eklendi." << std::endl; agac.basimYiliRaporu1950();
                break;
            }
            case 18: {
                std::cout << "\n--- Rapor: 1950 Oncesi & 30 Gun Ustu (Agac) ---" << std::endl;
                if (oduncStack.isEmpty()) { std::cout << "Odunc kitap yok." << std::endl;break; }
                BinarySearchTree agac; std::vector<Kitap> kV = stackToVectorNonDestructive(oduncStack); for (const auto& k : kV)agac.ekle(k);
                std::cout << "Odunc alinan kitaplar agaca eklendi." << std::endl; agac.rapor1950OncesiVe30GunUstu(getBugununTarihi());
                break;
            }
            case 19: {
                std::cout << "\n--- Odunc Kitap Puanlarini Hash Tablosuna Aktarma/Guncelleme ---" << std::endl;
                if (oduncStack.isEmpty() && iadeStack.isEmpty()) { std::cout << "Puanlanacak kitap yok." << std::endl; break; }
                std::cout << "(Odunc ve Iade Stacklerindeki kitaplar puanlariyla Hash Tablosuna aktariliyor...)" << std::endl;
                std::vector<Kitap> oduncV = stackToVectorNonDestructive(oduncStack); for (const auto& k : oduncV) kitapHashTablosu.ekle(k);
                std::vector<Kitap> iadeV = stackToVectorNonDestructive(iadeStack); for (const auto& k : iadeV) kitapHashTablosu.ekle(k);
                std::cout << "Kitaplarin guncel puan durumlari Hash Tablosuna aktarildi." << std::endl;
                kitapHashTablosu.tumunuYazdir();
                break;
            }
            case 20: {
                std::cout << "\n--- Ortalama Puani 4.0 ve Uzeri Kitaplar (Hash) ---" << std::endl;
                if (kitapHashTablosu.isEmpty()) { std::cout << "Hash tablosu bos. Once 19. secenek ile aktarin." << std::endl; break; }
                kitapHashTablosu.yuksekPuanlilariListele(4.0);
                break;
            }
            case 0: std::cout << "Ana Menu'ye donuluyor..." << std::endl; break;
            default: std::cout << "Gecersiz secim." << std::endl;
            }
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Hata: " << e.what() << std::endl;
        }
    } while (secim != 0);
}

// --- Kullanici Menusu ---
// (Bu fonksiyonun içeriği bir önceki mesajdakiyle aynı kalabilir, sadece parametre listesine dikkat edin)
void kullaniciMenu(SinglyLinkedList& anaKitapListesi,
    DoublyCircularLinkedList& kullaniciKoleksiyonu,
    Stack& oduncAlinanStack,
    Stack& iadeEdilenLogStack,
    Queue& talepKuyrugu,
    HashTable& kitapHashTablosu) {
    int secim;
    do {
        std::cout << "\n--- KULLANICI MENU ---" << std::endl;
        std::cout << "--- Modul 1 & 2 ---" << std::endl;
        std::cout << "1. Kitaba Yorum Yap" << std::endl;
        std::cout << "2. Yorumlari Listele" << std::endl;
        std::cout << "3. Koleksiyonuma Ekle" << std::endl;
        std::cout << "4. Koleksiyonumu Goruntule" << std::endl;
        std::cout << "5. Koleksiyonumdan Sil" << std::endl;
        std::cout << "6. Okundu/Okunmadi Isaretle" << std::endl;
        std::cout << "7. Odunc Kitap Al" << std::endl;
        std::cout << "8. Odunc Aldiklarimi Listele" << std::endl;
        std::cout << "9. Kitap Iade Et" << std::endl;
        std::cout << "10. Iade Ettiklerimi Listele" << std::endl;
        std::cout << "--- Modul 3 ---" << std::endl;
        std::cout << "11. Kitap Talep Et" << std::endl;
        std::cout << "12. Akademik Talep Et" << std::endl;
        std::cout << "13. Taleplerimi Goruntule" << std::endl;
        std::cout << "--- Modul 4: Odunc Kitap Filtreleme (Agac) ---" << std::endl;
        std::cout << "14. Oduncleri Yayinevine Gore Filtrele" << std::endl;
        std::cout << "15. Oduncleri Dile Gore Filtrele" << std::endl;
        std::cout << "16. Oduncleri Sayfa Uzunluguna Gore Filtrele" << std::endl;
        std::cout << "--- Modul 5: Kitap Puanlama ve Oneri (Hash) ---" << std::endl;
        std::cout << "17. Kitap Puanla (Odunc/Iade Edilenlerden)" << std::endl;
        std::cout << "18. Benzer Kitap Onerileri Al (Kategoriye Gore)" << std::endl;
        std::cout << "0. Ana Menu'ye Don" << std::endl;
        secim = getIntegerInput("Seciminizi yapiniz: ");

        try {
            switch (secim) {
            case 1: { std::cout << "\n--- Yorum Yap ---" << std::endl; int id = getIntegerInput("ID (Ana Liste): "); Kitap* k = anaKitapListesi.idGoreKitapAra(id); if (k) { std::string y = getStringInput("Yorum: "); k->yorumEkle(y);std::cout << "Eklendi." << std::endl; } else std::cout << "Bulunamadi." << std::endl; break; }
            case 2: { std::cout << "\n--- Yorumlari Listele ---" << std::endl; int id = getIntegerInput("ID (Ana Liste): "); Kitap* k = anaKitapListesi.idGoreKitapAra(id); if (k) { if (k->yorumlarListesi.empty()) std::cout << "Yorum yok." << std::endl; else for (const auto& y : k->yorumlarListesi)std::cout << "- " << y << std::endl; } else std::cout << "Bulunamadi." << std::endl; break; }
            case 3: { std::cout << "\n--- Koleksiyona Ekle ---" << std::endl; int id = getIntegerInput("ID (Ana Liste): "); Kitap* k = anaKitapListesi.idGoreKitapAra(id); if (k) { if (kullaniciKoleksiyonu.kitapAra(id))std::cout << "Zaten var." << std::endl;else { kullaniciKoleksiyonu.koleksiyonaKitapEkle(*k); std::cout << "Eklendi." << std::endl; } } else std::cout << "Ana listede yok." << std::endl; break; }
            case 4: kullaniciKoleksiyonu.koleksiyonuYazdir(); break;
            case 5: { std::cout << "\n--- Koleksiyondan Sil ---" << std::endl; if (kullaniciKoleksiyonu.isEmpty()) { std::cout << "Koleksiyon bos." << std::endl;break; } int id = getIntegerInput("ID: "); if (kullaniciKoleksiyonu.koleksiyondanKitapSil(id))std::cout << "Silindi." << std::endl;else std::cout << "Bulunamadi." << std::endl; break; }
            case 6: { std::cout << "\n--- Okundu Isaretle ---" << std::endl; if (kullaniciKoleksiyonu.isEmpty()) { std::cout << "Koleksiyon bos." << std::endl;break; } int id = getIntegerInput("ID: "); NodeCD* d = kullaniciKoleksiyonu.kitapAra(id); if (!d) { std::cout << "Koleksiyonda yok." << std::endl;break; } std::cout << "Mevcut: " << (d->kitap.okunduMu ? "Okundu" : "Okunmadi") << std::endl; std::cout << "Yeni (e/h): "; char c; std::cin >> c; std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); bool s = (c == 'e' || c == 'E'); if (kullaniciKoleksiyonu.kitabiOkunduIsaretle(id, s))std::cout << "Guncellendi." << std::endl; else std::cout << "Hata." << std::endl; break; }
            case 7: { std::cout << "\n--- Odunc Al ---" << std::endl; anaKitapListesi.kitaplariListele(); int id = getIntegerInput("ID: "); Kitap* k = anaKitapListesi.idGoreKitapAra(id); if (!k)std::cout << "Sistemde yok." << std::endl; else if (k->oduncAlindiMi)std::cout << "Baskasinda." << std::endl; else { k->oduncAlindiMi = true;Kitap kopya = *k; kopya.eklenmeZamani = getBugununTarihi(); oduncAlinanStack.push(kopya); std::cout << "Odunc alindi." << std::endl; } break; }
            case 8: std::cout << "\n--- Odunc Alinanlar ---" << std::endl; if (oduncAlinanStack.isEmpty())std::cout << "Odunc kitap yok." << std::endl; else oduncAlinanStack.listele(); break;
            case 9: { std::cout << "\n--- Iade Et ---" << std::endl; if (oduncAlinanStack.isEmpty()) { std::cout << "Iade edilecek kitap yok." << std::endl;break; } Kitap iade = oduncAlinanStack.pop(); Kitap* k_ana = anaKitapListesi.idGoreKitapAra(iade.id); if (k_ana)k_ana->oduncAlindiMi = false; iade.eklenmeZamani = getBugununTarihi(); iadeEdilenLogStack.push(iade); std::cout << "'" << iade.ad << "' iade edildi." << std::endl; break; }
            case 10: std::cout << "\n--- Iade Edilenler ---" << std::endl; if (iadeEdilenLogStack.isEmpty())std::cout << "Iade logu bos." << std::endl; else iadeEdilenLogStack.listele(); break;
            case 11: { std::cout << "\n--- Kitap Talep Et ---" << std::endl; std::string ad = getStringInput("Kitap adi: "); talepKuyrugu.enqueue(ad, 0); std::cout << "Talep alindi." << std::endl; break; }
            case 12: { std::cout << "\n--- Akademik Talep ---" << std::endl; std::string ad = getStringInput("Kitap adi: "); talepKuyrugu.enqueue(ad, 1); std::cout << "Oncelikli talep alindi." << std::endl; talepKuyrugu.listele(); break; }
            case 13: std::cout << "\n--- Taleplerim ---" << std::endl; if (talepKuyrugu.isEmpty())std::cout << "Talep yok." << std::endl; else talepKuyrugu.listele(); break;
            case 14: {
                std::cout << "\n--- Odunc Kitaplarimi Yayinevine Gore Filtrele (Agac) ---" << std::endl;
                if (oduncAlinanStack.isEmpty()) { std::cout << "Odunc kitap yok." << std::endl; break; }
                BinarySearchTree agac; std::vector<Kitap> kV = stackToVectorNonDestructive(oduncAlinanStack); for (const auto& k : kV)agac.ekle(k);
                std::string tur = getStringInput("Filtrele (Yerli/Yabanci): "); agac.filtreleYerliYabanciYayinevi(tur);
                break;
            }
            case 15: {
                std::cout << "\n--- Odunc Kitaplarimi Dile Gore Filtrele (Agac) ---" << std::endl;
                if (oduncAlinanStack.isEmpty()) { std::cout << "Odunc kitap yok." << std::endl; break; }
                BinarySearchTree agac; std::vector<Kitap> kV = stackToVectorNonDestructive(oduncAlinanStack); for (const auto& k : kV)agac.ekle(k);
                std::string dil = getStringInput("Filtrele (Turkce/Ingilizce): "); agac.filtreleDil(dil);
                break;
            }
            case 16: {
                std::cout << "\n--- Odunc Kitaplarimi Sayfa Uzunluguna Gore Filtrele (Agac) ---" << std::endl;
                if (oduncAlinanStack.isEmpty()) { std::cout << "Odunc kitap yok." << std::endl; break; }
                BinarySearchTree agac; std::vector<Kitap> kV = stackToVectorNonDestructive(oduncAlinanStack); for (const auto& k : kV)agac.ekle(k);
                int limit = getIntegerInput("Limit (orn: 1000): ");
                std::string azCok = getStringInput("'az' mi, 'cok' mu? (az/cok): ");
                bool azMi = (azCok == "az" || azCok == "AZ");
                agac.filtreleSayfaUzunlugu(limit, azMi);
                break;
            }
                   // --- YENI Modul 5 Kullanici Kisimlari ---
            case 17: {
                std::cout << "\n--- Kitap Puanlama ---" << std::endl;
                bool puanlanacakKitapVar = false;
                if (!oduncAlinanStack.isEmpty()) { std::cout << "Su an odunc aldiklariniz (Puanlamak icin ID secin):" << std::endl; oduncAlinanStack.listele(); puanlanacakKitapVar = true; }
                if (!iadeEdilenLogStack.isEmpty()) { std::cout << "Daha once iade ettikleriniz (Puanlamak icin ID secin):" << std::endl; iadeEdilenLogStack.listele(); puanlanacakKitapVar = true; }
                if (!puanlanacakKitapVar) { std::cout << "Puanlanacak kitap yok." << std::endl; break; }
                int puanlanacakID = getIntegerInput("Puanlamak istediginiz kitabin ID'si: ");
                Kitap* anaKitap = anaKitapListesi.idGoreKitapAra(puanlanacakID); // Ana kitabi buluyorum
                Kitap* hashKitap = kitapHashTablosu.ara(puanlanacakID); // Hash'teki kopyasini buluyorum (veya ana kitabi da hash'e ekleyebiliriz)

                if (anaKitap != nullptr) {
                    int puan = getIntegerInput("Puaniniz (1-5): ");
                    if (puan >= 1 && puan <= 5) {
                        anaKitap->puanEkle(puan); // Ana kitabin puanini guncelliyorum
                        kitapHashTablosu.ekle(*anaKitap); // Hash tablosundaki kaydi da guncelliyorum
                        std::cout << "Puaniniz kaydedildi ve Hash Tablosu guncellendi." << std::endl;
                    }
                    else { std::cout << "Gecersiz puan." << std::endl; }
                }
                else { std::cout << "ID: " << puanlanacakID << " olan kitap sistemde bulunamadi." << std::endl; }
                break;
            }
            case 18: {
                std::cout << "\n--- Benzer Kitap Onerileri (Kategoriye Gore - Hash) ---" << std::endl;
                if (kitapHashTablosu.isEmpty()) { std::cout << "Oneri icin Hash tablosunda kitap yok." << std::endl; break; }
                std::string kategori = getStringInput("Hangi kategoride oneriler istersiniz?: ");
                kitapHashTablosu.kategoriyeGoreListele(kategori);
                break;
            }
            case 0: std::cout << "Ana Menu'ye donuluyor..." << std::endl; break;
            default: std::cout << "Gecersiz secim." << std::endl;
            }
        }
        catch (const std::runtime_error& e) {
            std::cerr << "Hata: " << e.what() << std::endl;
        }
    } while (secim != 0);
}

// Programim buradan basliyor!
int main() {
    SinglyLinkedList anaKitapListesi;
    DoublyCircularLinkedList kullanicininKisiselKoleksiyonu;
    Stack oduncAlinanKitaplarStack;
    Stack iadeEdilenKitaplarLogStack;
    Queue kitapTalepleriKuyrugu;
    HashTable kitapHashTablosu(101);

    std::string ortakEklenmeZamani = "12-05-2025";
    std::string ortakDil = "Turkce";
    std::string ortakYayineviTuru = "Yerli";
    Kitap k1(1, "Bilinaltinin Gucu", "Joseph Murphy", 1963, 276); k1.eklenmeZamani = ortakEklenmeZamani;k1.kategori = "Kisisel Gelisim";k1.dil = ortakDil;k1.yayineviTuru = ortakYayineviTuru; anaKitapListesi.kitapEkle(k1); kitapHashTablosu.ekle(k1);
    Kitap k2(2, "Osmancik", "Tarik Bugra", 1983, 250); k2.eklenmeZamani = ortakEklenmeZamani;k2.kategori = "Turk Edebiyati";k2.dil = ortakDil;k2.yayineviTuru = ortakYayineviTuru; anaKitapListesi.kitapEkle(k2); kitapHashTablosu.ekle(k2);
    Kitap k3(3, "Kucuk Prens", "Antoine de Saint-Exupery", 1943, 90); k3.eklenmeZamani = ortakEklenmeZamani;k3.kategori = "Cocuk Edebiyati";k3.dil = ortakDil;k3.yayineviTuru = ortakYayineviTuru; anaKitapListesi.kitapEkle(k3); kitapHashTablosu.ekle(k3);
    Kitap k4(4, "Kurk Mantolu Madonna", "Sabahattin Ali", 1943, 180); k4.eklenmeZamani = ortakEklenmeZamani;k4.kategori = "Turk Edebiyati";k4.dil = ortakDil;k4.yayineviTuru = ortakYayineviTuru; anaKitapListesi.kitapEkle(k4); kitapHashTablosu.ekle(k4);
    Kitap k5(5, "Satranc", "Stefan Zweig", 1942, 80); k5.eklenmeZamani = ortakEklenmeZamani;k5.kategori = "Dunya Klasikleri";k5.dil = ortakDil;k5.yayineviTuru = ortakYayineviTuru; anaKitapListesi.kitapEkle(k5); kitapHashTablosu.ekle(k5);
    Kitap k6(6, "Donusum", "Franz Kafka", 1915, 96); k6.eklenmeZamani = ortakEklenmeZamani;k6.kategori = "Dunya Klasikleri";k6.dil = ortakDil;k6.yayineviTuru = ortakYayineviTuru; anaKitapListesi.kitapEkle(k6); kitapHashTablosu.ekle(k6);
    Kitap k7(7, "1984", "George Orwell", 1949, 325); k7.eklenmeZamani = ortakEklenmeZamani;k7.kategori = "Distopya";k7.dil = ortakDil;k7.yayineviTuru = ortakYayineviTuru; anaKitapListesi.kitapEkle(k7); kitapHashTablosu.ekle(k7);

    int anaSecim;
    do {
        std::cout << "\n--- ANA MENU ---" << std::endl;
        std::cout << "1. Personel Girisi" << std::endl;
        std::cout << "2. Kullanici Girisi" << std::endl;
        std::cout << "0. Cikis" << std::endl;
        anaSecim = getIntegerInput("Seciminizi yapiniz: ");
        switch (anaSecim) {
        case 1: personelMenu(anaKitapListesi, oduncAlinanKitaplarStack, iadeEdilenKitaplarLogStack, kitapTalepleriKuyrugu, kitapHashTablosu); break;
        case 2: kullaniciMenu(anaKitapListesi, kullanicininKisiselKoleksiyonu, oduncAlinanKitaplarStack, iadeEdilenKitaplarLogStack, kitapTalepleriKuyrugu, kitapHashTablosu); break;
        case 0: std::cout << "Programdan cikiliyor..." << std::endl; break;
        default: std::cout << "Gecersiz secim." << std::endl;
        }
    } while (anaSecim != 0);
    return 0;
}