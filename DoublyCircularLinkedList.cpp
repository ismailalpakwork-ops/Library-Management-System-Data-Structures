// DoublyCircularLinkedList.cpp

#include "DoublyCircularLinkedList.h" // Kendi .h dosyamý çaðýrdým.
#include <iostream>                   // Ekrana yazý yazdýrmak için (cout).

// --- Kurucu Fonksiyonum ---
// Yeni bir liste oluþturduðumda ilk baþta boþ olsun diye 'head'i nullptr yaptým.
DoublyCircularLinkedList::DoublyCircularLinkedList() {
    head = nullptr;
}

// --- Yýkýcý Fonksiyonum ---
// Program kapanýrken veya listem silinirken, listedeki tüm düðümleri silerek hafýzayý temizleyeceðim.
DoublyCircularLinkedList::~DoublyCircularLinkedList() {
    if (head == nullptr) return; // Listem zaten boþsa yapacak bir þey yok.

    NodeCD* current = head->sonraki;
    while (current != head) {
        NodeCD* temp = current;
        current = current->sonraki;
        delete temp;
    }
    delete head; // En son head'i de siliyorum.
    head = nullptr;
}

// --- Listem Boþ mu Diye Kontrol Ediyorum ---
bool DoublyCircularLinkedList::isEmpty() const {
    return head == nullptr; // head bossa, liste de boþtur.
}

// --- Kullanýcýnýn Koleksiyonuna Kitap Eklemek Ýçin ---
void DoublyCircularLinkedList::koleksiyonaKitapEkle(Kitap eklenecekKitap) {
    NodeCD* yeniDugum = new NodeCD(eklenecekKitap); // Yeni kitabým için yeni bir düðüm yarattým.

    if (isEmpty()) { // Eðer koleksiyonum (listem) boþsa...
        head = yeniDugum; // Yeni düðüm benim ilk ve tek elemaným oluyor.
    }
    else { // Eðer koleksiyonda zaten kitaplar varsa...
        NodeCD* sonEskiDugum = head->onceki; // head'in bir öncesi, listenin eski sonuydu.

        sonEskiDugum->sonraki = yeniDugum;
        yeniDugum->onceki = sonEskiDugum;
        yeniDugum->sonraki = head;
        head->onceki = yeniDugum;
    }
    // Basari mesajini main.cpp icinde veriyorum.
}

// --- Kullanýcýnýn Kitap Koleksiyonunu Ekrana Yazdýrmak Ýçin ---
void DoublyCircularLinkedList::koleksiyonuYazdir() const {
    if (isEmpty()) {
        std::cout << "Kullanicinin kitap koleksiyonu su an bos." << std::endl;
        return;
    }
    std::cout << "\n--- KULLANICI KITAP KOLEKSIYONU ---" << std::endl;
    NodeCD* temp = head;
    int sayac = 1;
    do {
        std::cout << "\nKoleksiyon Kitap " << sayac++ << ":" << std::endl;
        // Kitap sinifindaki bilgileriYazdir() fonksiyonu okunduMu durumunu da gosterecek sekilde guncellenmisti.
        temp->kitap.bilgileriYazdir();
        temp = temp->sonraki;
    } while (temp != head);
    std::cout << "--- KOLEKSIYON SONU ---" << std::endl;
}

// --- ID'ye Göre Kitap Arýyorum ve Bulursam Düðümü Döndürüyorum ---
NodeCD* DoublyCircularLinkedList::kitapAra(int kitapID) {
    if (isEmpty()) {
        return nullptr;
    }
    NodeCD* temp = head;
    do {
        if (temp->kitap.id == kitapID) { // Kitap.h'de id public oldugunu varsayiyorum.
            return temp;
        }
        temp = temp->sonraki;
    } while (temp != head);

    return nullptr; // Kitabý bulamadým.
}

// --- Kullanýcýnýn Koleksiyonundan ID'ye Göre Kitap Silmek Ýçin ---
bool DoublyCircularLinkedList::koleksiyondanKitapSil(int kitapID) {
    if (isEmpty()) {
        return false; // Liste bossa silemem.
    }

    NodeCD* silinecek = kitapAra(kitapID);

    if (silinecek == nullptr) {
        return false; // Kitap bulunamadi.
    }

    if (silinecek == head && silinecek->sonraki == head) { // Listede sadece bu tek düðüm varsa...
        head = nullptr;
    }
    else {
        NodeCD* oncekiDugum = silinecek->onceki;
        NodeCD* sonrakiDugum = silinecek->sonraki;

        oncekiDugum->sonraki = sonrakiDugum;
        sonrakiDugum->onceki = oncekiDugum;

        if (silinecek == head) { // Eðer sildiðim düðüm head idiyse...
            head = sonrakiDugum;
        }
    }
    delete silinecek; // Düðümü hafýzadan siliyorum.
    return true; // Silme islemi basarili.
}

// --- ID'si Verilen Bir Kitaba Yorum Yapmak Ýçin ---
// Bu fonksiyon, bu koleksiyondaki (DoublyCircularLinkedList) bir kitaba yorum ekler.
bool DoublyCircularLinkedList::kitabaYorumYap(int kitapID, const std::string& yorum) {
    NodeCD* yorumYapilacakDugum = kitapAra(kitapID); // Yorum yapýlacak kitabý bu koleksiyonda arýyorum.
    if (yorumYapilacakDugum != nullptr) { // Eðer kitap varsa...
        yorumYapilacakDugum->kitap.yorumEkle(yorum); // Kitap sýnýfýmdaki yorumEkle fonksiyonunu çaðýrýyorum.
        return true;
    }
    return false; // Kitap bulunamadi.
}

// --- ID'si Verilen Bir Kitabýn Yorumlarýný Listelemek Ýçin ---
// Bu fonksiyon, bu koleksiyondaki bir kitabin yorumlarini listeler.
void DoublyCircularLinkedList::kitabinYorumlariniListele(int kitapID) const {
    if (isEmpty()) {
        std::cout << "Koleksiyon bos." << std::endl;
        return;
    }
    // kitapAra const olmadigi icin gecici bir arama yapiyorum.
    // Aslinda kitapAra'yi da const yapip, donen pointer'i const NodeCD* yapmak daha dogru olurdu.
    // Simdilik bu sekilde birakalim.
    NodeCD* temp = head;
    bool bulundu = false;
    do {
        if (temp->kitap.id == kitapID) {
            bulundu = true;
            if (temp->kitap.yorumlarListesi.empty()) {
                std::cout << "'" << temp->kitap.ad << "' adli kitaba henuz yorum yapilmamis." << std::endl;
            }
            else {
                std::cout << "\n--- '" << temp->kitap.ad << "' Adli Kitabin Yorumlari (Koleksiyondan) ---" << std::endl;
                for (const std::string& yorum : temp->kitap.yorumlarListesi) {
                    std::cout << "- " << yorum << std::endl;
                }
            }
            break;
        }
        temp = temp->sonraki;
    } while (temp != head);

    if (!bulundu) {
        std::cout << "ID: " << kitapID << " olan kitap koleksiyonda bulunamadi." << std::endl;
    }
}

// --- Kullanýcýnýn Koleksiyonundaki Bir Kitabý Okundu/Okunmadý Olarak Ýþaretlemesi Ýçin ---
// Bu fonksiyon, verilen ID'deki kitabi koleksiyonda bulup 'okunduMu' durumunu degistirecek.
bool DoublyCircularLinkedList::kitabiOkunduIsaretle(int kitapID, bool okunduDurumu) {
    NodeCD* isaretlenecekDugum = kitapAra(kitapID); // Once kitabi koleksiyonumda ariyorum.
    if (isaretlenecekDugum != nullptr) { // Eger kitabi bulduysam...
        isaretlenecekDugum->kitap.okunduMu = okunduDurumu; // Kitabin 'okunduMu' ozelligini guncelliyorum.
        // Kitap.h'de okunduMu'nun public oldugunu varsayiyorum.
        return true; // Islem basarili.
    }
    return false; // Kitap bulunamadi.
}