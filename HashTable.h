// HashTable.h

#ifndef HASHTABLE_H // Bu dosyanin birden fazla cagrilmasini onlemek icin bu komutlari ekliyorum.
#define HASHTABLE_H

#include "HashNode.h" // Bir onceki adimda tanimladigim HashNode yapimi burada kullanacagim.
#include "Kitap.h"    // Kitap nesneleriyle calisacagim icin.
#include <vector>     // Hash tablosunun gozlerini (bucket) bir vektor olarak tutabilirim.
#include <string>     // Hata mesajlari veya baska seyler icin.
#include <list>       // Alternatif olarak, her bucket bir std::list<HashNode> tutabilir.
                      // Ama kendi HashNode listemizi yonetmek daha ogretici olur.

// Kitaplari Kitap ID'sine gore saklayacak ve hizlica bulmami saglayacak Hash Tablosu sinifim.
// Carpismalari (ayni hash degerine sahip farkli kitaplar) cozmek icin "zincirleme" yontemini kullanacagim.
// Yani tablomun her bir gozu (bucket), bir bagli liste (HashNode'lardan olusan) olacak.
class HashTable {
private:
    // Hash tablom aslinda bir HashNode isaretcileri dizisi (veya vektoru) olacak.
    // Her bir isaretci, o goze (bucket) ait bagli listenin basini gosterecek.
    std::vector<HashNode*> tablo; // Hash tablosunun kendisi. Her elemani bir HashNode listesinin basi.
    int tabloBoyutu;             // Hash tablomda kac tane goz (bucket) olacagini bu belirleyecek.
    int elemanSayisi;            // Hash tablomda toplam kac tane kitap oldugunu tutacagim.

    // --- Private Yardimci Fonksiyonlarim ---
    // Verilen bir anahtara (Kitap ID) gore hash degeri (tablo indeksi) hesaplayan fonksiyonum.
    // Basit bir mod alma islemi kullanacagim.
    int hashFonksiyonu(int anahtar) const;

public:
    // Yeni bir HashTable nesnesi olusturdugumda calisacak kurucu fonksiyonum.
    // Parametre olarak tablonun boyutunu (kac gozlu olacagini) alabilir.
    HashTable(int boyut = 101); // Varsayilan boyut 101 (asal sayi olmasi genellikle iyi bir pratiktir).
    
    void yuksekPuanlilariListele(double minPuan) const;
    void kategoriyeGoreListele(const std::string& kategori) const;



    // Bu HashTable nesnesi yok oldugunda calisacak yikici fonksiyonum.
    // Tablodaki tum bagli listeleri ve dugumleri silerek hafizayi temizleyecegim.
    ~HashTable();

    // --- Temel Hash Tablosu Islemlerim ---

    // Hash tablosuna yeni bir kitap eklemek icin.
    // Kitap ID'sini anahtar olarak kullanacagim.
    void ekle(Kitap eklenecekKitap);

    // Verilen bir Kitap ID'sine (anahtar) sahip kitabi hash tablosunda aramak icin.
    // Bulursa Kitap nesnesinin adresini, bulamazsa nullptr dondurecek.
    Kitap* ara(int kitapID);

    // Verilen bir Kitap ID'sine sahip kitabi hash tablosundan silmek icin (Gerekirse).
    // Proje isterlerinde silme olup olmadigina bakmam lazim. Simdilik prototipini ekliyorum.
    bool sil(int kitapID);

    // Hash tablosundaki tum kitaplari (veya belirli bir gozdeki) yazdirmak icin (Test amaciyla).
    void tumunuYazdir() const;

    // Hash tablosunun bos olup olmadigini anlamak icin.
    bool isEmpty() const;

    // Hash tablosundaki toplam eleman (kitap) sayisini almak icin.
    int getElemanSayisi() const;
};

#endif //HASHTABLE_H