/**
 * @file market.h
 *
 * @brief Provides functions for math. utilities
 */

#ifndef MARKET_H
#define MARKET_H
#define BUCKET_SIZE 5
#define MAX_VENDORS 100
#define MAX_PRODUCTS 100


#include <iostream>
#include "../../utility/header/commonTypes.h"


 


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

typedef struct {
    int vendorId;
    int productId;
    float price;
} SparseMatrixEntry;

extern SparseMatrixEntry sparseMatrix[MAX_VENDORS * MAX_PRODUCTS];
extern int sparseMatrixSize;


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
void addVendorProductRelation(int vendorId, int productId, float price);
void listProductsByVendor(int vendorId);


int searchProductsOrEnterKeyword();
int enterSearchProducts();
int enterKeywords();
int priceComparis();

// Diğer gerekli kütüphaneler ve yapı tanımları
int comparePricesByName(const char* productName);  // comparePricesByName için prototip
int selectProduct(char* selectedProductName);      // selectProduct için prototip


// Market Hours structure definition
typedef struct {
    int id;
    char day[20];
    char hours[20];
    char location[50];
} MarketHours;


// Function declarations
bool validateDay(const char* day);
bool validateWorkingHours(const char* hours);

void addMarketHoursAndLocation();
void updateMarketHoursAndLocation();
void displayMarketHoursAndLocations();


typedef struct MarketHoursNode {
    MarketHours data;
    struct MarketHoursNode* xorPtr; // XOR of previous and next nodes
} MarketHoursNode;

// Function prototypes
MarketHoursNode* xor (MarketHoursNode* a, MarketHoursNode* b);
MarketHoursNode* insertXORList(MarketHoursNode* head, MarketHours data);
void traverseXORList(MarketHoursNode* head);


void traverseXORList(MarketHoursNode* head);




#endif // MARKET_H