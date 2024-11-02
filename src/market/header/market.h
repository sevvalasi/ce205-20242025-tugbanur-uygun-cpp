/**
 * @file market.h
 *
 * @brief Provides functions for math. utilities
 */

#ifndef MARKET_H
#define MARKET_H
#define BUCKET_SIZE 5


#include <iostream>
#include "../../utility/header/commonTypes.h"


 

 // Haftanın günlerini tanımlayan sabit dizi
extern const char* daysOfWeek[7];
// Fonksiyon prototipleri
int getDayIndex(const char* day); // Günü dizideki sırasına göre döndürür
char* generateWorkingDays(const char* startDay, int duration); // Döngüsel çalışma günlerini oluşturur
bool validateWorkingHours(const char* hours); // Çalışma saatlerini doğrular
 // Kullanıcı bilgilerini tutacak yapı (struct)



struct User {
    char username[50];  // Kullanıcı adı (en fazla 50 karakter)
    char password[50];  // Şifre (en fazla 50 karakter)
};


struct Vendor {
    int id;                // Benzersiz ID (int)
    char name[50];         // Satıcının ismi (string - max 50 karakter)
};

struct Product {
    int vendorId;          // Satıcı ID'si
    char productName[50];  // Ürünün adı
    float price;           // Ürünün fiyatı
    int quantity;          // Ürünün adedi
    char season[20];       // Ürünün mevsimi
};

// Çalışma saatleri ve lokasyon bilgilerini içeren yapı
struct MarketHoursAndLocation {
    int vendorId;
    char location[100];
    char workingHours[50];
    char workingDays[20];
};

typedef struct {
    int key;
    Product product;
    int isOccupied;
} HashTableEntry;

typedef struct {
    Product products[BUCKET_SIZE];
    int productCount;
} Bucket;


// DFS için kullanıldı 
struct Node {
    char* info;           // Ürün veya satıcı bilgisi
    Node** neighbors;     // Bağlı komşu düğümler
    int neighborCount;    // Komşu sayısı
};


bool validateDay(const char* day);

int getInput();
int mainMenu();


int listingOfLocalProducts();
int priceComparison();
int comparePricesByName();
int selectProduct();
int marketHoursAndLocations();


bool userAuthentication();
bool loginUser();
bool registerUser();


int listingOfLocalVendors();
int addVendor();
int updateVendor();
int deleteVendor();
int listVendors();


int addProduct();
int updateProduct();
int deleteProduct();
int listingOfLocalVendorsandProducts();
void initializeHashTable();
int hashFunction(int key);
int linearProbing(int key, int i);
int quadraticProbing(int key, int i);
int doubleHashing(int key, int i);
int linearQuotient(int key, int i);
int progressiveOverflowSearch(int key);
int useOfBucketsSearch(int key);
int brentsMethodSearch(int key);
int listingOfLocalVendorsandProducts();

int addMarketHoursAndLocation();
int displayMarketHoursAndLocations();


int searchProductsOrEnterKeyword();
int enterSearchProducts();
int enterKeywords();
int priceComparis();

// Diğer gerekli kütüphaneler ve yapı tanımları
int comparePricesByName(const char* productName);  // comparePricesByName için prototip
int selectProduct(char* selectedProductName);      // selectProduct için prototip






#endif // MARKET_H