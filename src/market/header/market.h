/**
 * @file market.h
 *
 * @brief Provides functions for math. utilities
 */

#ifndef MARKET_H
#define MARKET_H
#define MAX_KEYS 3 // B+ ağacı için maksimum anahtar sayısı
#define MIN_KEYS (MAX_KEYS / 2)

#include <iostream>
#include "../../utility/header/commonTypes.h"

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


// DFS için kullanıldı 
struct Node {
    char* info;           // Ürün veya satıcı bilgisi
    Node** neighbors;     // Bağlı komşu düğümler
    int neighborCount;    // Komşu sayısı
};


// B+ Tree Node yapısı
typedef struct BPlusTreeNode {
    bool isLeaf;
    int keys[MAX_KEYS];
    struct BPlusTreeNode* children[MAX_KEYS + 1];
    int keyCount;
    struct BPlusTreeNode* next; // Yaprak düğümler arasındaki bağlantı
} BPlusTreeNode;



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
int listingOfLocalVendorsandProducts();

int addMarketHoursAndLocation();
int displayMarketHoursAndLocations();


int searchProductsOrEnterKeyword();
int enterSearchProducts();
int enterKeywords();
int priceComparis();
BPlusTreeNode* insertInternal(BPlusTreeNode* root, int key, BPlusTreeNode* child);


// Diğer gerekli kütüphaneler ve yapı tanımları
int comparePricesByName(const char* productName);  // comparePricesByName için prototip
int selectProduct(char* selectedProductName);      // selectProduct için prototip




#endif // MARKET_H