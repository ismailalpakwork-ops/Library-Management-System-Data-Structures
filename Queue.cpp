// Queue.cpp

#include "Queue.h"     // Kendi yazdigim Queue.h dosyasini dahil ediyorum.
#include "QueueNode.h" // QueueNode.h'yi Queue.h zaten include ediyor.
#include <iostream>   // Ekrana yazi yazdirmak (cout) icin.
#include <stdexcept>  // dequeue() ve getFront() bos kuyruktan cagrilirsa hata firlatmak icin (runtime_error).
#include <string>     // KitapTalepDetayi icindeki std::string icin.

// Kurucu Fonksiyonum
Queue::Queue() {
    front = nullptr;
    rear = nullptr;
    boyut = 0;
}

// Yikici Fonksiyonum
Queue::~Queue() {
    while (!isEmpty()) {
        dequeue();
    }
}

// Kuyrugumun Bos Olup Olmadigini Kontrol Eden Fonksiyonum
bool Queue::isEmpty() const {
    return front == nullptr;
}

// Kuyrugumun Mevcut Boyutunu Alan Fonksiyonum
int Queue::getBoyut() const {
    return boyut;
}

// Kuyrugumun Sonuna Yeni Bir Kitap Talebi Ekleyen Fonksiyonum (enqueue)
void Queue::enqueue(std::string kitapAdi, int oncelik) {
    KitapTalepDetayi talepDetayi(kitapAdi, oncelik);
    QueueNode* yeniDugum = new QueueNode(talepDetayi);

    if (isEmpty()) {
        front = yeniDugum;
        rear = yeniDugum;
    }
    else {
        rear->sonraki = yeniDugum;
        rear = yeniDugum;
    }
    boyut++;
}

// Kuyrugumun Basindan Bir Kitap Talebini Cikaran Fonksiyonum (dequeue)
KitapTalepDetayi Queue::dequeue() {
    if (isEmpty()) {
        throw std::runtime_error("Hata: Bos kuyruktan dequeue islemi yapilamaz!");
    }

    QueueNode* silinecekDugum = front;
    KitapTalepDetayi cikarilanTalep = front->talep;

    front = front->sonraki;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete silinecekDugum;
    boyut--;

    return cikarilanTalep;
}

// Kuyrugumun Basindaki Kitap Talebine Bakan Fonksiyonum (getFront)
KitapTalepDetayi Queue::getFront() const {
    if (isEmpty()) {
        throw std::runtime_error("Hata: Bos kuyruktan getFront() islemi yapilamaz!");
    }
    return front->talep;
}

// Kuyrugumun Icindeki Tum Kitap Taleplerini Listeleyen Fonksiyonum
void Queue::listele() const {
    if (isEmpty()) {
        std::cout << "Kitap talep kuyrugu bostur." << std::endl;
        return;
    }
    std::cout << "\n--- KITAP TALEP KUYRUGU (Bastan Sona) ---" << std::endl;
    QueueNode* temp = front;
    int sayac = 1;
    while (temp != nullptr) {
        std::cout << sayac++ << ". Talep: '" << temp->talep.kitapAdi
            << "' (Oncelik: " << temp->talep.oncelik << ")" << std::endl;
        temp = temp->sonraki;
    }
    std::cout << "--- KUYRUK SONU ---" << std::endl;
}