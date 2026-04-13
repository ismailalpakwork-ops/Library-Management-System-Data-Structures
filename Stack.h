// Stack.h
#ifndef STACK_H
#define STACK_H

#include "StackNode.h" // StackNode yapimi burada kullanacagim.
#include "Kitap.h"     // Kitap nesneleriyle calisacagim.
#include <iostream>    // Hata durumlarinda mesaj yazdirmak icin.
#include <stdexcept>   // std::runtime_error icin

class Stack {
private:
    StackNode* top;
    int boyut;

public:
    Stack();
    ~Stack();
    void push(Kitap eklenecekKitap);
    Kitap pop();
    Kitap peek() const;
    bool isEmpty() const;
    int getBoyut() const;
    void listele() const;
};

#endif //STACK_H