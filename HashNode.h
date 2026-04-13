// HashNode.h
#ifndef HASHNODE_H
#define HASHNODE_H

#include "Kitap.h" // Kitap bilgilerini saklayacagim.
#include <string>  // Anahtar belki string de olabilirdi ama ID int oldugu icin int kullanacagim.

// Hash Tablomdaki her bir gozun (bucket) icindeki bagli listenin dugumleri icin bu yapiyi kullanacagim.
// Her dugum bir anahtar (Kitap ID) ve o anahtara karsilik gelen degeri (Kitap nesnesi) tutacak.
struct HashNode {
    int anahtar;      // Kitap ID'sini anahtar olarak kullanacagim.
    Kitap kitap;      // Saklayacagim Kitap bilgisi (kopyasi).
    HashNode* sonraki; // Ayni hash degerine sahip bir sonraki HashNode'u gosterecek (zincirleme icin).

    // Yeni bir HashNode olusturdugumda calisacak kurucu fonksiyonum.
    HashNode(int key, Kitap value) {
        anahtar = key;
        kitap = value; // Kitap nesnesinin kopyasini aliyorum.
        sonraki = nullptr; // Ilk basta bu dugumun bir sonrakisi yok.
    }
};

#endif //HASHNODE_H