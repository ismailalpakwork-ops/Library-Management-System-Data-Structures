#ifndef DOUBLYCIRCULARLINKEDLIST_H // Bu dosyanin birden fazla cagrilmasini onlemek icin.
#define DOUBLYCIRCULARLINKEDLIST_H

#include "NodeCD.h"   // Yukarida tanimladigim NodeCD yapimi burada kullanacagim.
#include <iostream>   // Ekrana bir seyler yazdirmak icin (cout).
#include <string>     // Yazilarla (string) calismak icin.

// Cift Yonlu Dairesel Bagli Listemi temsil edecek sinifim.
class DoublyCircularLinkedList {
private: // Bu kisim disaridan dogrudan erisilemesin diye private yaptim.
    NodeCD* head; // Listemin bir nevi baslangic noktasini (veya herhangi bir dugumunu) tutacak.
    // Liste dairesel oldugu icin 'head' herhangi bir dugum olabilir.
    // Liste bossa bu nullptr olacak.

public:
    // Yeni bir DoublyCircularLinkedList nesnesi olusturdugumda calisacak kurucu fonksiyonum.
    DoublyCircularLinkedList();

    // Bu liste nesnesi yok oldugunda (program bitince vs.) calisacak yikici fonksiyonum.
    // Bellekte gereksiz yer kaplamamasi icin olusturdugum dugumleri burada silecegim.
    ~DoublyCircularLinkedList();

    // --- Modul 1: Kullanici Girisi Fonksiyonlarim ---
    // Bu fonksiyonlarin sadece bildirimlerini (prototiplerini) buraya yaziyorum.
    // Asil ne yapacaklarini .cpp dosyasinda anlatacagim.

    // Kullanicinin kendi kitap koleksiyonuna kitap eklemesi icin.
    void koleksiyonaKitapEkle(Kitap eklenecekKitap);

    // Kullanicinin kitap koleksiyonundan ID'ye gore kitap silmesi icin.
    bool koleksiyondanKitapSil(int kitapID);

    // Kullanicinin kitap koleksiyonundaki kitaplari yazdirmasi icin.
    void koleksiyonuYazdir() const; // 'const' cunku bu fonksiyon listeyi degistirmeyecek, sadece okuyacak.

    // ID'si verilen bir kitaba yorum yapmak icin.
    // Yorumlar Kitap sinifimin icindeki listede tutulacak.
    bool kitabaYorumYap(int kitapID, const std::string& yorum);

    // ID'si verilen bir kitabin yorumlarini listelemek icin.
    void kitabinYorumlariniListele(int kitapID) const;

    // Kullanicinin koleksiyonundaki bir kitabi okundu/okunmadi olarak isaretlemesi icin.
    // Bunun icin Kitap sinifima 'okunduMu' diye bir sey ekleyebilirim veya baska bir yontem dusunebilirim.
    bool kitabiOkunduIsaretle(int kitapID, bool okunduDurumu);


    // --- Diger Yardimci Fonksiyonlarim ---
    // Listemin bos olup olmadigini anlamak icin.
    bool isEmpty() const;

    // ID'ye gore bir kitabi listede arayip, bulursa o dugumu (NodeCD*) dondurmesi icin.
    // Bu, bircok islemde isime yarayacak.
    NodeCD* kitapAra(int kitapID);

    // Proje dokumaninda "Kullanicinin kendi kitap koleksiyonunu olusturmasi (Yalniz 1 koleksiyon)" diyor.
    // Bu sinifin kendisi zaten bir koleksiyonu temsil ediyor olacak.
    // Yani her kullanici icin bir tane DoublyCircularLinkedList nesnesi olusturabilirim.
};

#endif //DOUBLYCIRCULARLINKEDLIST_H