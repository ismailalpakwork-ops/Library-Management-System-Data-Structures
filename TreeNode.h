// TreeNode.h

#ifndef TREENODE_H // Eger bu dosya daha once cagirildiysa tekrar cagirma.
#define TREENODE_H

#include "Kitap.h" // Kitap bilgilerini tutacagim icin Kitap sinifimi buraya dahil ettim.

// Ikili Arama Agacim (BST) icin kullanacagim Dugum (TreeNode) yapisi.
// Her bir dugumde bir kitap ve bu dugumun solunda ve saginda olabilecek
// diger dugumlere baglantilar olacak.
struct TreeNode {
    Kitap kitap;      // Bu dugumde saklayacagim Kitap bilgisi.
    TreeNode* sol;    // Bu dugumun sol cocugunu (daha kucuk degerli) gosterecek isaretcim.
    TreeNode* sag;    // Bu dugumun sag cocugunu (daha buyuk degerli) gosterecek isaretcim.

    // Yeni bir TreeNode olusturdugumda calisacak olan kurucu fonksiyonum.
    // Bir Kitap nesnesi aliyor ve dugumun icine koyuyor.
    // Baslangicta sol ve sag cocuklari olmasin diye onlari nullptr yapiyorum.
    TreeNode(Kitap ktp) {
        kitap = ktp;        // Aldigim kitabi kendi kitabim olarak ayarladim.
        sol = nullptr;      // Ilk basta sol cocugum yok.
        sag = nullptr;      // Ilk basta sag cocugum da yok.
    }
};

#endif //TREENODE_H