#ifndef MARKET_H
#define MARKET_H
#define BUCKET_SIZE 5
#define MAX_VENDORS 100
#define MAX_PRODUCTS 100
#define MAX_TREE_HT 100
#define MAX_KEYS 3
#define MIN_KEYS (MAX_KEYS / 2)
#include <iostream>
#include "../../utility/header/commonTypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct User {
    char username[50];  // Kullanıcı adı (en fazla 50 karakter)
    char password[50];  // Şifre (en fazla 50 karakter)
};

struct Vendor {
    int id;                // Benzersiz ID (int)
    char name[50];         // Satıcının ismi (string - max 50 karakter)
};

struct Product {
    int vendorId;          
    char productName[50]; 
    float price;         
    int quantity;
    char season[20];
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

struct MarketHoursAndLocation {
    int vendorId;
    char location[100];
    char workingHours[50];
    char workingDays[20];
};

//For DFS
struct Node {
    char* info;   
    Node** neighbors;     
    int neighborCount;   
};

typedef struct {
    int vendorId;
    int productId;
    float price;
} SparseMatrixEntry;

// B+ Tree Node Structure
typedef struct BPlusTreeNode {
    bool isLeaf;
    int keys[MAX_KEYS];
    struct BPlusTreeNode* children[MAX_KEYS + 1];
    int keyCount;
    struct BPlusTreeNode* next;
} BPlusTreeNode;

// Huffman node definition
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode* left, * right;
};

// Min-Heap Definition
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

// Market Hours structure definition
typedef struct {
    int id;
    char day[20];
    char hours[20];
    char location[50];
} MarketHours;

typedef struct MarketHoursNode {
    MarketHours data;
    struct MarketHoursNode* xorPtr; // XOR of previous and next nodes
} MarketHoursNode;

// Two-way connected list node
typedef struct DoublyLinkedListNode {
    Vendor vendor;
    struct DoublyLinkedListNode* next;
    struct DoublyLinkedListNode* prev;
} DoublyLinkedListNode;

int getInput();
bool mainMenu();

bool listingOfLocalProducts();
bool priceComparison();
bool searchProductsOrEnterKeyword();
int comparePricesByName();
int selectProduct();
bool marketHoursAndLocations();

bool userAuthentication();
bool registerUser();
struct MinHeapNode* newNode(char data, unsigned freq);
struct MinHeap* createMinHeap(unsigned capacity);
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);
void minHeapify(struct MinHeap* minHeap, int idx);
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode);
void buildMinHeap(struct MinHeap* minHeap);
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size);
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size);
void printCodes(struct MinHeapNode* root, int arr[], int top);
void HuffmanCodes(char data[], int freq[], int size);
bool saveUserToHuffFile(const char* username, const char* password);
bool loginUser();
bool loginUserFromHuffFile(const char* username, const char* password);

bool listingOfLocalVendors();
bool addVendor();
bool updateVendor();
bool deleteVendor();
bool listVendors();


bool addProduct();
bool updateProduct();
bool deleteProduct();
bool listingOfLocalVendorsandProducts();
void initializeHashTable();
int hashFunction(int key);
int linearProbing(int key, int i);
int quadraticProbing(int key, int i);
int doubleHashing(int key, int i);
int linearQuotient(int key, int i);
int progressiveOverflowSearch(int key);
int useOfBucketsSearch(int key);
int brentsMethodSearch(int key);
void addVendorProductRelation(int vendorId, int productId, float price);
void listProductsByVendor(int vendorId);

bool enterSearchProducts();
bool enterKeywords();
int priceComparis();
bool comparePricesByName(const char* productName); 
bool selectProduct(char* selectedProductName);
bool validateDay(const char* day);
bool validateWorkingHours(const char* hours);
int getDayIndex(const char* day);
char* generateWorkingDays(const char* startDay, int duration);
bool validateWorkingHours(const char* hours);

// Fixed array defining the days of the week
extern const char* daysOfWeek[7];
extern SparseMatrixEntry sparseMatrix[MAX_VENDORS * MAX_PRODUCTS];
extern int sparseMatrixSize;

void addMarketHoursAndLocation();
void updateMarketHoursAndLocation();
void displayMarketHoursAndLocations();
MarketHoursNode* xor (MarketHoursNode* a, MarketHoursNode* b);
MarketHoursNode* insertXORList(MarketHoursNode* head, MarketHours data);
void traverseXORList(MarketHoursNode* head);
void traverseXORList(MarketHoursNode* head);
void findSCC(struct Node* nodes[], int nodeCount);




#endif // MARKET_H