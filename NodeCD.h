#ifndef NODECD_H // Eðer bu dosya daha önce çaðrýldýysa tekrar çaðýrma diye bu komutlarý ekliyorum.
#define NODECD_H

#include "Kitap.h" // Kitap bilgilerini tutacaðým için Kitap sýnýfýmý buraya dahil ettim.

// Cift Yonlu Dairesel Bagli Listem icin Dugum (NodeCD) yapim.
// Her bir dugumde bir kitap ve listenin onceki/sonraki halkalarina baglantilar olacak.
struct NodeCD {
    Kitap kitap;      // Bu dugumde saklayacagim Kitap bilgisi.
    NodeCD* sonraki;  // Bu dugumden sonra gelen dugumu gosterecek.
    NodeCD* onceki;   // Bu dugumden once gelen dugumu gosterecek.

    // Yeni bir NodeCD olusturdugumda calisacak olan kurucu fonksiyonum.
    // Bir Kitap nesnesi aliyor ve dugumun icine koyuyor.
    NodeCD(Kitap ktp) {
        kitap = ktp; // Aldigim kitabi kendi kitabim olarak ayarladim.
        // Liste dairesel olacagi icin ve ilk basta tek elemanli olabilecegi icin,
        // 'sonraki' ve 'onceki' baslangicta kendisini gostersin dedim.
        // Liste bosken veya tek elemanliyken bu mantikli. Ekleme yaptikca bunlar degisecek.
        sonraki = this; // 'this' bu dugumun kendisi demek.
        onceki = this;
    }
};

#endif //NODECD_H