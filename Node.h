#ifndef NODE_H
#define NODE_H

#include "Kitap.h" 


struct Node {
    Kitap kitap;      
    Node* sonraki;    

    
   
    Node(Kitap ktp) {
        kitap = ktp;
        sonraki = nullptr; 
    }

    
};

#endif 