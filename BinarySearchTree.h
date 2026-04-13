// BinarySearchTree.h

#ifndef BINARYSEARCHTREE_H // Bu dosyanin birden fazla cagrilmasini onlemek icin.
#define BINARYSEARCHTREE_H

#include "TreeNode.h"  // Yukarida tanimladigim TreeNode yapimi burada kullanacagim.
#include <iostream>    // Ekrana bir seyler yazdirmak icin (cout).
#include <vector>      // Bazi raporlama fonksiyonlarinda kitaplari gecici bir vektorde toplamak gerekebilir.
#include <string>      // String kullanimi icin.
#include <algorithm>   // std::sort gibi algoritmalar icin (belki ileride gerekir).

// Kitaplari Ikili Arama Agaci (BST) yapisinda saklayacak sinifim.
// Agaca eklemeyi genellikle Kitap ID'sine gore yapacagim.
class BinarySearchTree {
private:
    TreeNode* root; // Agacimin koku, yani en tepedeki dugumu gosterecek isaretcim.
    // Agac bossa bu nullptr olacak.

// --- Yardimci (Recursive - Ozyineli) Fonksiyonlarim ---
// Bu fonksiyonlar genellikle private olur ve public fonksiyonlar tarafindan cagrilir.
// Cunku ozyineli fonksiyonlar genellikle dugum isaretcisiyle calisir,
// kullanicinin dogrudan dugumlerle ugrasmasini istemem.

// Agaca yeni bir kitap eklemek icin ozyineli yardimci fonksiyonum.
    TreeNode* ekleRecursive(TreeNode* dugum, Kitap eklenecekKitap);

    // Agaci InOrder (LNR: Sol-Kok-Sag) sirasinda gezip kitaplari yazdirmak icin ozyineli yardimci fonksiyonum.
    // Bu gezinme sekli kitaplari genellikle ID'ye (veya neye gore siraladiysak ona) gore sirali verir.
    void inOrderRecursive(TreeNode* dugum) const;

    // Agaci PreOrder (NLR: Kok-Sol-Sag) sirasinda gezip kitaplari yazdirmak icin.
    void preOrderRecursive(TreeNode* dugum) const;

    // Agaci PostOrder (LRN: Sol-Sag-Kok) sirasinda gezip kitaplari yazdirmak icin.
    // Bu, agaci silerken (yikicida) kullanislidir.
    void postOrderRecursive(TreeNode* dugum) const;

    // Agactaki tum dugumleri silmek icin ozyineli yardimci fonksiyonum (yikici tarafindan kullanilacak).
    void destroyRecursive(TreeNode* dugum);

    // ID'ye gore kitap aramak icin ozyineli yardimci fonksiyonum.
    TreeNode* araRecursive(TreeNode* dugum, int arananID) const;

    // --- Raporlama Icin Ozyineli Yardimci Fonksiyonlar (Ornekler) ---
    // Bu fonksiyonlar, agaci gezerken belirli kosullara uyan kitaplari bir vektore ekleyecek.

    // Odunc alma suresi 30 gunun altinda/ustunde olanlari bulmak icin.
    // (Bu fonksiyonlarin icini doldururken tarih/sure hesaplamasi yapmam gerekecek)
    void oduncSuresiRaporuRecursive(TreeNode* dugum, std::vector<Kitap>& altindaListe, std::vector<Kitap>& ustundeListe, const std::string& bugununTarihi) const;

    // Basim yili 1950'den once/sonra olanlari bulmak icin.
    void basimYiliRaporuRecursive(TreeNode* dugum, std::vector<Kitap>& onceListe, std::vector<Kitap>& sonraListe) const;

    // Yerli/Yabanci yayinevine gore filtrelemek icin.
    void yayineviFiltreleRecursive(TreeNode* dugum, const std::string& yayineviTuru, std::vector<Kitap>& sonucListesi) const;

    // Kitap diline gore filtrelemek icin.
    void dilFiltreleRecursive(TreeNode* dugum, const std::string& dil, std::vector<Kitap>& sonucListesi) const;

    // Sayfa uzunluguna gore filtrelemek icin.
    void sayfaUzunluguFiltreleRecursive(TreeNode* dugum, int sayfaLimiti, bool azMi, std::vector<Kitap>& sonucListesi) const;


public:
    // Yeni bir BinarySearchTree nesnesi olusturdugumda calisacak kurucu fonksiyonum.
    BinarySearchTree();

    // Bu agac nesnesi yok oldugunda calisacak yikici fonksiyonum.
    // Agactaki tum dugumleri silerek hafizayi temizleyecegim.
    ~BinarySearchTree();

    // --- Temel Agac Islemlerim (Kullanicinin Cagiracagi Fonksiyonlar) ---

    // Agaca yeni bir kitap eklemek icin.
    void ekle(Kitap eklenecekKitap);

    // Agaci InOrder sirasinda gezip kitaplari yazdirmak icin.
    void inOrderDolas() const;

    // Agaci PreOrder sirasinda gezip kitaplari yazdirmak icin.
    void preOrderDolas() const;

    // Agaci PostOrder sirasinda gezip kitaplari yazdirmak icin.
    void postOrderDolas() const;

    // ID'ye gore bir kitabi agacta aramak icin. Bulursa Kitap nesnesinin adresini, bulamazsa nullptr dondurur.
    Kitap* ara(int arananID) const;

    // Agacin bos olup olmadigini kontrol etmek icin.
    bool isEmpty() const;

    // --- 4. Modul Personel Raporlari Icin Fonksiyonlar ---
    void oduncAlmaSuresiRaporu(const std::string& bugununTarihi) const; // Tarih hesaplamasi gerekecek
    void basimYiliRaporu1950() const;
    void rapor1950OncesiVe30GunUstu(const std::string& bugununTarihi) const; // Iki kosulu birlestirecek

    // --- 4. Modul Kullanici Filtreleme Islemleri Icin Fonksiyonlar ---
    void filtreleYerliYabanciYayinevi(const std::string& yayineviTuru) const;
    void filtreleDil(const std::string& dil) const;
    void filtreleSayfaUzunlugu(int sayfaLimiti, bool azMi) const; // azMi=true ise limitten az, false ise cok
};

#endif //BINARYSEARCHTREE_H