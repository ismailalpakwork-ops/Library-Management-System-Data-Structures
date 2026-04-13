// SinglyCircularLinkedList.cpp

#include "SinglyCircularLinkedList.h" // Kendi yazdigim .h dosyasini dahil ediyorum.
#include "Node.h"                     // Bu sinif Node.h'deki Node yapisini kullaniyor.
#include "Kitap.h"                    // Node'lar Kitap nesnesi tutuyor.
#include <iostream>                   // Ekrana yazi yazdirmak (cout) icin.

// --- Kurucu Fonksiyonum ---
// Yeni bir dairesel liste olusturdugumda, baslangicta 'tail'im olmayacak ve boyutum 0 olacak.
SinglyCircularLinkedList::SinglyCircularLinkedList() {
    tail = nullptr; // Listem ilk olustugunda sonu yok (yani bos).
    boyut = 0;
}

// --- Yikici Fonksiyonum ---
// Bu liste nesnesi silinirken, icindeki tum dugumleri temizleyecegim.
SinglyCircularLinkedList::~SinglyCircularLinkedList() {
    temizle(); // Temizle fonksiyonum zaten tum dugumleri siliyor.
}

// --- Listemin Bos Olup Olmadigini Kontrol Ediyorum ---
bool SinglyCircularLinkedList::isEmpty() const {
    return tail == nullptr; // Eger 'tail' bossa, listem de bostur.
}

// --- Listemdeki Eleman Sayisini Aliyorum ---
int SinglyCircularLinkedList::getBoyut() const {
    return boyut;
}

// --- Listemin Sonuna Yeni Bir Kitap Ekliyorum ---
// Dairesel oldugu icin, ekledigim yeni dugum yeni 'tail' olacak
// ve bu yeni 'tail'in 'sonraki'si eski listenin basini gosterecek.
void SinglyCircularLinkedList::ekle(Kitap eklenecekKitap) {
    Node* yeniDugum = new Node(eklenecekKitap); // Yeni kitabim icin bir dugum yarattim (Node.h'deki Node'u kullaniyorum).

    if (isEmpty()) { // Eger listem bossa...
        tail = yeniDugum;        // Yeni dugum benim hem basim hem de sonum oluyor.
        tail->sonraki = tail;    // Dairesel yapiyi kuruyorum: son dugum (ayni zamanda bas dugum) kendine isaret ediyor.
    }
    else { // Eger listemde zaten elemanlar varsa...
        yeniDugum->sonraki = tail->sonraki; // Yeni dugumun 'sonraki'si, eski 'tail'in gosterdigi basi (head) gosterecek.
        tail->sonraki = yeniDugum;        // Eski 'tail'in 'sonraki'si artik yeni dugumu gosterecek.
        tail = yeniDugum;                 // Artik yeni 'tail'im bu yeni ekledigim dugum.
    }
    boyut++; // Eleman sayimi bir arttirdim.
}

// --- Listemdeki Tum Kitaplari Yazdiriyorum ---
void SinglyCircularLinkedList::listele() const {
    if (isEmpty()) {
        std::cout << "Rapor listesi (Dairesel) bostur." << std::endl;
        return;
    }
    std::cout << "\n--- RAPOR LISTESI (Tek Yonlu Dairesel) ---" << std::endl;
    Node* temp = tail->sonraki; // Listenin basindan (head) basliyorum.

    // Dairesel listeyi dogru yazdirmak icin boyut kadar veya basa donene kadar gitmek gerek.
    // En saglam yontem boyut kullanmak.
    for (int i = 0; i < boyut; ++i) {
        if (temp == nullptr) { // Beklenmedik bir durum, liste bozulmus olabilir.
            std::cout << "Hata: Liste beklenenden erken sonlandi (nullptr)!" << std::endl;
            break;
        }
        std::cout << "\nRapor Elemani " << (i + 1) << ":" << std::endl;
        temp->kitap.bilgileriYazdir();
        temp = temp->sonraki;
    }
    std::cout << "--- RAPOR LISTESI SONU ---" << std::endl;
}

// --- Listeyi Temizleme Fonksiyonum ---
// Listedeki tum dugumleri silip, listeyi bosaltiyorum.
void SinglyCircularLinkedList::temizle() {
    if (isEmpty()) {
        return; // Zaten bossa bir sey yapma.
    }

    Node* current = tail->sonraki; // Listenin gercek basi (head).
    Node* silinecek = nullptr;

    // tail->sonraki'yi nullptr yaparak daireselligi kiriyorum ki dongu sonlansin
    // ve current dogru ilerlesin.
    tail->sonraki = nullptr;

    while (current != nullptr) {
        silinecek = current;
        current = current->sonraki;
        //std::cout << "SCLL Temizle: Siliniyor - " << silinecek->kitap.ad << std::endl; // Test icin
        delete silinecek;
    }

    tail = nullptr; // Liste artik bos.
    boyut = 0;
}