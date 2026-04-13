# Makefile for Kitap Yonetim Sistemi Projesi

# Derleyici olarak g++ kullaniyorum
CXX = g++

# Derleme bayraklari:
# -std=c++11: C++11 standardini kullaniyorum.
# -Wall -Wextra: Mumkun olan tum uyarilari goster.
# -g: Hata ayiklama (debugging) sembollerini ekler.
CXXFLAGS = -std=c++11 -Wall -Wextra -g

# Olusturulacak calistirilabilir dosyanin adi
TARGET = KitapYonetimSistemi

# Derlenecek tum .cpp kaynak dosyalarimin listesi.
# Projenizdeki tum .cpp dosyalarinin burada dogru bir sekilde listelendiginden emin olun.
# Her dosya adi sadece bir kere yazilmali.
SRCS = \
	Kitap.cpp \
	SinglyLinkedList.cpp \
	DoublyCircularLinkedList.cpp \
	Stack.cpp \
	Queue.cpp \
	SinglyCircularLinkedList.cpp \
	BinarySearchTree.cpp \
	HashTable.cpp \
	main.cpp

# Kaynak dosyalarimdan (.cpp) olusturulacak obje dosyalarinin (.o) listesi.
OBJS = $(SRCS:.cpp=.o)

# Ana hedefim: Calistirilabilir dosyayi olusturmak.
all: $(TARGET)

# Calistirilabilir dosyamizin ($(TARGET)) nasil olusturulacagini anlatiyorum.
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

# Herhangi bir .cpp dosyasinin, kendi .o obje dosyasina nasil derlenecegini anlatiyorum.
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Temizleme hedefi: Olusturdugum tum .o dosyalarini ve calistirilabilir dosyam $(TARGET)'i siler.
clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe

.PHONY: all clean