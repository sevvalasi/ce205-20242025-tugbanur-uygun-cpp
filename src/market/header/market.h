/**
 * @file market.h
 * @brief Market Management System Header File
 *
 * This file contains all necessary definitions, structs, constants, and function prototypes
 * for managing a local market system. The system involves vendors, products, pricing comparisons,
 * market hours, B+ trees, Huffman coding, linked lists, hash table operations, and XOR linked lists.
 */


#ifndef MARKET_H
#define MARKET_H

 /** @brief Bucket size for storing products */
#define BUCKET_SIZE 5
/** @brief Maximum number of vendors allowed */
#define MAX_VENDORS 100
/** @brief Maximum number of products allowed */
#define MAX_PRODUCTS 100
/** @brief Maximum height of Huffman tree */
#define MAX_TREE_HT 100
/** @brief Maximum number of keys in B+ Tree nodes */
#define MAX_KEYS 3
/** @brief Minimum number of keys in B+ Tree nodes */
#define MIN_KEYS (MAX_KEYS / 2)
#define OVERFLOW__SIZE 10
#define BUCKET_COUNT 10

#include <iostream>
#include "../../utility/header/commonTypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


/**
 * @struct User
 * @brief Stores user information for authentication.
 */
struct User {
    char username[50];  // Kullanıcı adı (en fazla 50 karakter)
    char password[50];  // Şifre (en fazla 50 karakter)
};

/**
 * @struct Vendor
 * @brief Represents a vendor with an ID and name.
 */
struct Vendor {
    int id;                // Benzersiz ID (int)
    char name[50];         // Satıcının ismi (string - max 50 karakter)
};


/**
 * @struct Product
 * @brief Stores product information including vendor association.
 */
struct Product {
    int vendorId;          
    char productName[50]; 
    float price;         
    int quantity;
    char season[20];
};

/**
 * @struct HashTableEntry
 * @brief Represents an entry in the hash table for product storage.
 */
typedef struct {
    int key;
    Product product;
    int isOccupied;
} HashTableEntry;

typedef struct {
    bool isOccupied;
    int key;
} OverflowEntry;




/**
 * @struct Bucket
 * @brief Represents a bucket for storing products in the hash table.
 */
typedef struct {
    Product products[BUCKET_SIZE];
    int productCount;
} Bucket;


/**
 * @struct MarketHoursAndLocation
 * @brief Stores the market hours and location information for a vendor.
 */
struct MarketHoursAndLocation {
    int vendorId;
    char location[100];
    char workingHours[50];
    char workingDays[20];
};

/**
 * @struct Node
 * @brief Represents a graph node for DFS and SCC algorithms.
 */
struct Node {
    char* info;   
    Node** neighbors;     
    int neighborCount;   
};


/**
 * @struct SparseMatrixEntry
 * @brief Represents an entry in a sparse matrix used for price storage.
 */
typedef struct {
    int vendorId;
    int productId;
    float price;
} SparseMatrixEntry;

/**
 * @struct BPlusTreeNode
 * @brief Represents a node in a B+ tree.
 */
typedef struct BPlusTreeNode {
    bool isLeaf;                                      /**< Indicates if the node is a leaf */
    int keys[MAX_KEYS];                               /**< Indicates if the node is a leaf */
    struct BPlusTreeNode* children[MAX_KEYS + 1];     /**< Child pointers */
    int keyCount;                                     /**< Number of keys in the node */
    struct BPlusTreeNode* next;                       /**< Pointer to next leaf node (used for linked leaf nodes) */
} BPlusTreeNode;


/**
 * @struct MinHeapNode
 * @brief Represents a node in the Huffman tree.
 */
struct MinHeapNode {
    char data;
    unsigned freq;
    struct MinHeapNode* left, * right;
};

/**
 * @struct MinHeap
 * @brief Represents a min-heap for building the Huffman tree.
 */
struct MinHeap {
    unsigned size;
    unsigned capacity;
    struct MinHeapNode** array;
};

/**
 * @struct MarketHours
 * @brief Represents the market hours for a vendor.
 */
typedef struct {
    int id;
    char day[20];
    char hours[20];
    char location[50];
} MarketHours;


/**
 * @struct MarketHoursNode
 * @brief Represents a node in an XOR linked list for market hours.
 */
typedef struct MarketHoursNode {
    MarketHours data;
    struct MarketHoursNode* xorPtr; // XOR of previous and next nodes
} MarketHoursNode;

/**
 * @struct DoublyLinkedListNode
 * @brief Represents a node in a doubly linked list of vendors.
 */
typedef struct DoublyLinkedListNode {
    Vendor vendor;
    struct DoublyLinkedListNode* next;
    struct DoublyLinkedListNode* prev;
} DoublyLinkedListNode;



typedef struct StackNode {
    Vendor vendor;
    struct StackNode* next;
} StackNode;

typedef struct Stack {
    StackNode* top;
} Stack;

typedef struct QueueNode {
    Vendor vendor;
    struct QueueNode* next;
} QueueNode;

typedef struct Queue {
    QueueNode* front;
    QueueNode* rear;
} Queue;

// Function prototypes and detailed descriptions for market system management
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

/**
 * @brief Creates a new Huffman node.
 * @param data Character data.
 * @param freq Frequency of the character.
 * @return Pointer to the new MinHeapNode.
 */
struct MinHeapNode* newNode(char data, unsigned freq);

/**
 * @brief Creates a min-heap with given capacity.
 * @param capacity Capacity of the min-heap.
 * @return Pointer to the created MinHeap.
 */
struct MinHeap* createMinHeap(unsigned capacity);

void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b);
bool minHeapify(struct MinHeap* minHeap, int idx);
struct MinHeapNode* extractMin(struct MinHeap* minHeap);
bool insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode);
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
bool isDuplicate(Queue* queue, Vendor vendor);


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
bool progressiveOverflowSearch(int key);
bool useOfBucketsSearch(int key);
int brentsMethodSearch(int key);
void addVendorProductRelation(int vendorId, int productId, float price);
bool listProductsByVendor(int vendorId);

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

/** @brief Fixed array defining the days of the week */
extern const char* daysOfWeek[7];
extern SparseMatrixEntry sparseMatrix[MAX_VENDORS * MAX_PRODUCTS];
extern int sparseMatrixSize;

bool addMarketHoursAndLocation();
bool updateMarketHoursAndLocation();
bool displayMarketHoursAndLocations();
MarketHoursNode* xor_function (MarketHoursNode* a, MarketHoursNode* b);
MarketHoursNode* insertXORList(MarketHoursNode* head, MarketHours data);
void traverseXORList(MarketHoursNode* head);
void traverseXORList(MarketHoursNode* head);
void findSCC(Node* nodes[], int nodeCount);
void tarjanDFS(Node* nodes[], int at, int* id, int* ids, int* low, Node** stack, int* stackTop, bool* onStack, int nodeCount);
int findNodeIndex(Node* nodes[], Node* node, int nodeCount);
bool heapify(Product arr[], int n, int i);



#endif // MARKET_H