// Stack.cpp

#include "Stack.h"     // Kendi yazdigim Stack.h dosyasini dahil ediyorum.
#include "Kitap.h"     // Stack'im Kitap nesneleri tutacak (StackNode.h bunu zaten include ediyor).
#include "StackNode.h" // StackNode.h'yi Stack.h zaten include ediyor ama burada da acikca belirtmek iyi olabilir.
#include <iostream>   // Ekrana yazi yazdirmak (cout) icin.
#include <stdexcept>  // pop() ve peek() bos yigindan cagrilirsa hata firlatmak icin (runtime_error).

// Kurucu Fonksiyonum
Stack::Stack() {
    top = nullptr;
    boyut = 0;
}

// Yikici Fonksiyonum
Stack::~Stack() {
    while (!isEmpty()) {
        pop();
    }
}

// Yiginimin Bos Olup Olmadigini Kontrol Eden Fonksiyonum
bool Stack::isEmpty() const {
    return top == nullptr;
}

// Yiginimin Mevcut Boyutunu Alan Fonksiyonum
int Stack::getBoyut() const {
    return boyut;
}

// Yiginimin Tepesine Yeni Bir Kitap Ekleyen Fonksiyonum (push)
void Stack::push(Kitap eklenecekKitap) {
    StackNode* yeniDugum = new StackNode(eklenecekKitap);

    yeniDugum->sonraki = top;
    top = yeniDugum;
    boyut++;
}

// Yiginimin Tepesinden Bir Kitap Cikaran Fonksiyonum (pop)
Kitap Stack::pop() {
    if (isEmpty()) {
        throw std::runtime_error("Hata: Bos yigindan pop() islemi yapilamaz!");
    }

    StackNode* silinecekDugum = top;
    Kitap cikarilanKitap = top->kitap;

    top = top->sonraki;

    delete silinecekDugum;
    boyut--;

    return cikarilanKitap;
}

// Yiginimin Tepesindeki Kitaba Bakan Fonksiyonum (peek)
Kitap Stack::peek() const {
    if (isEmpty()) {
        throw std::runtime_error("Hata: Bos yigindan peek() islemi yapilamaz!");
    }
    return top->kitap;
}

// Yiginimin Icindeki Tum Kitaplari Listeleyen Fonksiyonum
void Stack::listele() const {
    if (isEmpty()) {
        std::cout << "Yigin (Stack) bostur." << std::endl;
        return;
    }
    std::cout << "\n--- YIGINDAKI KITAPLAR (Tepeden Asagiya) ---" << std::endl;
    StackNode* temp = top;
    int sayac = 1;
    while (temp != nullptr) {
        std::cout << "\nYigin Elemani " << sayac++ << ":" << std::endl;
        temp->kitap.bilgileriYazdir();
        temp = temp->sonraki;
    }
    std::cout << "--- YIGIN SONU ---" << std::endl;
}