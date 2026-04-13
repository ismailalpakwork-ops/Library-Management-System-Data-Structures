// Queue.h

#ifndef QUEUE_H // Bu dosyanin birden fazla cagrilmasini onlemek icin bu komutlari ekliyorum.
#define QUEUE_H

#include "QueueNode.h" // Bir onceki adimda tanimladigim QueueNode yapimi burada kullanacagim.
#include <iostream>    // Ekrana bir seyler yazdirmak icin (cout), belki hata durumlarinda.
#include <string>      // dequeue ve front fonksiyonlarim string dondurecek.

// Kitap taleplerini FIFO (Ilk Giren Ilk Cikar) mantigiyla saklayacak Kuyruk (Queue) sinifim.
class Queue {
private: // Bu bilgiler disaridan dogrudan degistirilmesin diye private yaptim.
    QueueNode* front; // Kuyrugumun en onundeki (ilk giren) dugumu gosterecek isaretcim.
    QueueNode* rear;  // Kuyrugumun en sonundaki (en son giren) dugumu gosterecek isaretcim.
    int boyut;        // Kuyrugumda kac tane talep oldugunu bu degiskende tutacagim.

public:
    // Yeni bir Queue (Kuyruk) nesnesi olusturdugumda calisacak kurucu fonksiyonum.
    Queue();

    // Bu Queue nesnesi yok oldugunda calisacak yikici fonksiyonum.
    // Kuyruktaki tum dugumleri silerek hafizayi temizleyecegim.
    ~Queue();

    // --- Temel Kuyruk Islemlerim ---

    // Kuyrugumun sonuna yeni bir kitap talebi eklemek icin (enqueue).
    // Talep edilen kitabin adini ve onceligini alacak.
    void enqueue(std::string kitapAdi, int oncelik = 0); // Oncelige varsayilan deger olarak 0 verdim (normal talep).

    // Kuyrugumun basindan bir kitap talebini cikarmak icin (dequeue).
    // Cikardigim talebin KitapTalepDetayi nesnesini donduruyorum.
    // Eger kuyruk bossa ne yapacagimi dusunmem lazim (hata firlatmak gibi).
    KitapTalepDetayi dequeue();

    // Kuyrugumun basindaki kitap talebine bakmak icin (front veya peek).
    // Talebi kuyruktan cikarmayacak, sadece ne oldugunu gosterecek.
    // Eger kuyruk bossa ne yapacagimi dusunmem lazim.
    KitapTalepDetayi getFront() const; // 'const' cunku bu fonksiyon kuyrugu degistirmeyecek.

    // Kuyrugumun bos olup olmadigini anlamak icin.
    bool isEmpty() const;

    // Kuyrugumun mevcut boyutunu (talep sayisini) almak icin.
    int getBoyut() const;

    // Kuyrugumun icindeki tum kitap taleplerini (genellikle bastan sona dogru) listelemek icin.
    // Bu, kullanicinin "Talepleri yazdir" islevi icin kullanilabilir.
    void listele() const;
};

#endif //QUEUE_H