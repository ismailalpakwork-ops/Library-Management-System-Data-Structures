// QueueNode.h
#ifndef QUEUENODE_H
#define QUEUENODE_H
#include <string> // std::string kullanacagim icin bunu ekledim.

// Kuyrukta tutacagim kitap taleplerinin bilgilerini bu yapida saklayacagim.
// Simdilik sadece kitabin adi ve bir oncelik degeri tutuyorum.
struct KitapTalepDetayi {
    std::string kitapAdi; // Talep edilen kitabin adi
    int oncelik;          // Talebin onceligi (0: normal, 1: akademik gibi dusunebilirim)
    // Ileride baska bilgiler de ekleyebilirim (talep eden kullanici ID'si gibi).

    // Bu kurucu fonksiyon, yeni bir KitapTalepDetayi olustururken kolaylik saglar.
    KitapTalepDetayi(std::string ad = "", int prio = 0) {
        kitapAdi = ad;
        oncelik = prio;
    }
};

// Kuyruk (Queue) veri yapim icin kullanacagim Dugum (QueueNode) yapisi.
// Her bir dugumde bir kitap talep detayi ve kuyruktaki bir sonraki dugume baglanti olacak.
struct QueueNode {
    KitapTalepDetayi talep; // Bu dugumde saklayacagim kitap talep bilgisi.
    QueueNode* sonraki;     // Kuyruktaki bir sonraki dugumu gosterecek isaretcim.

    // Yeni bir QueueNode olusturdugumda calisacak olan kurucu fonksiyonum.
    // Bir KitapTalepDetayi nesnesi aliyor ve dugumun icine koyuyor.
    QueueNode(KitapTalepDetayi talepDetayi) {
        talep = talepDetayi;        // Aldigim talep bilgisini kendi talep bilgim olarak ayarladim.
        sonraki = nullptr;  // Ilk basta, bu dugumun bir sonrakisi yok. Kuyruga eklerken bunu ayarlayacagim.
    }
};
#endif //QUEUENODE_H