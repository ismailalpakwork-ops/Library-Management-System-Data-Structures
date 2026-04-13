// SinglyCircularLinkedList.h

#ifndef SINGLYCIRCULARLINKEDLIST_H // Bu dosyanin birden fazla cagrilmasini onlemek icin.
#define SINGLYCIRCULARLINKEDLIST_H

#include "Node.h"      // Mevcut Node.h yapimizi kullaniyorum, cunku dugum yapisi temelde ayni.
#include <iostream>    // Ekrana bir seyler yazdirmak icin (cout).

// Kitaplari Tek Yonlu Dairesel bir yapida saklayacak sinifim.
// Personel menusundeki raporlama islemleri icin kullanacagim.
class SinglyCircularLinkedList {
private:
    Node* tail; // Listenin sonunu (tail) gosteren bir isaretci tutacagim.
    // Dairesel listede 'tail' kullanmak, basa ve sona erisimi kolaylastirabilir.
    // Eger liste bossa 'tail' nullptr olacak.
    // 'tail->sonraki' her zaman listenin basini (head) gosterecek.
    int boyut;  // Listedeki eleman sayisini takip etmek icin.

public:
    // Yeni bir SinglyCircularLinkedList nesnesi olusturdugumda calisacak kurucu fonksiyonum.
    SinglyCircularLinkedList();

    // Bu liste nesnesi yok oldugunda calisacak yikici fonksiyonum.
    // Listedeki tum dugumleri silerek hafizayi temizleyecegim.
    ~SinglyCircularLinkedList();

    // --- Temel Liste Islemlerim ---

    // Listemin sonuna yeni bir kitap eklemek icin (add veya enqueue gibi).
    // Dairesel oldugu icin 'son' kavramindan sonra basa donuyor.
    void ekle(Kitap eklenecekKitap);

    // Listemdeki tum kitaplari yazdirmak icin.
    // Dairesel oldugu icin dikkatli dolasmam gerekecek.
    void listele() const; // 'const' cunku bu fonksiyon listeyi degistirmeyecek.

    // Listemin bos olup olmadigini anlamak icin.
    bool isEmpty() const;

    // Listemdeki eleman sayisini almak icin.
    int getBoyut() const;

    // Listeyi temizlemek icin (tum dugumleri silmek).
    // Yikici fonksiyon zaten bunu yapiyor ama bazen listeyi program calisirken de
    // temizlemek isteyebilirim.
    void temizle();
};

#endif //SINGLYCIRCULARLINKEDLIST_H