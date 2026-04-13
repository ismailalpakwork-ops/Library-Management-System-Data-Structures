// StackNode.h

#ifndef STACKNODE_H // Eger bu dosya daha once cagirildiysa tekrar cagirma diye bu komutlari ekliyorum.
#define STACKNODE_H

#include "Kitap.h" // Kitap bilgilerini tutacagim icin Kitap sinifimi buraya dahil ettim.

// Yigin (Stack) veri yapim icin kullanacagim Dugum (StackNode) yapisi.
// Her bir dugumde bir kitap ve yigindaki bir sonraki (altindaki) dugume baglanti olacak.
struct StackNode {
    Kitap kitap;          // Bu dugumde saklayacagim Kitap bilgisi.
    StackNode* sonraki;   // Yigindaki bir sonraki (altimdaki) dugumu gosterecek.

    // Yeni bir StackNode olusturdugumda calisacak olan kurucu fonksiyonum.
    // Bir Kitap nesnesi aliyor ve dugumun icine koyuyor.
    StackNode(Kitap ktp) {
        kitap = ktp;        // Aldigim kitabi kendi kitabim olarak ayarladim.
        sonraki = nullptr;  // Ilk basta, bu dugumun bir sonrakisi (alti) yok.
        // Yigina ekleme yaptigimda bu 'sonraki'yi guncelleyecegim.
    }
};

#endif //STACKNODE_H