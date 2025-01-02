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
/** @brief OVERFLOW_SIZE The number of slots in the overflow area of the hash table. */
#define OVERFLOW__SIZE 10
/** @brief BUCKET_SIZE The number of entries each bucket in the bucketized hash table can contain. */
#define BUCKET_COUNT 10
/** @brief TABLE_SIZE The number of slots in the hash table. */
#define TABLE_SIZE 10
/** @brief OVERFLOW_SIZE The number of slots in the overflow area of the hash table. */
#define OVERFLOW_SIZE 5

#include <iostream>
#include "../../utility/header/commonTypes.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <cmath>
/**
 * @def MAX_USERS
 * @brief Maximum number of users that the system can handle.
 *
 * This constant defines the upper limit on the number of user entries that can be stored or managed
 * within the application's user-related data structures.
 */
#define MAX_USERS 100
 /**
  * @def MAX_CHAR
  * @brief Maximum number of characters for certain string operations.
  *
  * This constant specifies the limit on the length of strings in various parts of the application,
  * including buffers and arrays used for processing text data. It ensures that operations such as
  * encoding, decoding, and storage do not exceed this limit, thus preventing buffer overflows.
  */
#define MAX_CHAR 256

  /**
   * @struct User
   * @brief Structure to store user information for authentication purposes.
   *
   * This structure holds the necessary details for a user in the system,
   * including username and password, both stored as fixed-length character arrays.
   */
struct User {
    char username[50];   ///< User's username with a maximum length of 50 characters.
    char password[50];   ///< User's password with a maximum length of 50 characters.
};

/**
 * @struct Vendor
 * @brief Structure to represent vendor information within the market.
 *
 * This struct holds data about a vendor, including a unique identifier and a name,
 * facilitating easy identification and management of vendor records.
 */
struct Vendor {
    int id;                ///< Unique identifier for the vendor.
    char name[50];         ///< Vendor's name with a maximum length of 50 characters.
};


/**
 * @struct Product
 * @brief Structure to store information about products.
 *
 * Contains details relevant to products such as the associated vendor ID,
 * product name, price, quantity available, and season of availability.
 */
struct Product {
    int vendorId;             ///< Identifier linking the product to a specific vendor.
    char productName[50];     ///< Name of the product.
    float price;              ///< Price of the product.
    int quantity;             ///< Available quantity of the product.
    char season[20];          ///< Season during which the product is available.
};

/**
 * @struct HashTableEntry
 * @brief Represents an entry within a hash table used for product management.
 *
 * This entry stores product data and a key for hashing, with a flag to indicate
 * if the slot is occupied.
 */
typedef struct { 
    int key;             ///< Key used for hashing in the hash table.
    Product product;     ///< Product data stored in this hash table entry.
    int isOccupied;      ///< Flag indicating whether this hash table entry is occupied.
} HashTableEntry;


/**
 * @struct OverflowEntry
 * @brief Represents an overflow entry for handling hash table collisions.
 *
 * Used to manage additional entries that do not fit into the main hash table due to collisions.
 */
typedef struct {
    bool isOccupied;     ///< Indicates if this overflow slot is occupied.
    int key;             ///< The key associated with this overflow entry.
} OverflowEntry;




/**
 * @struct Bucket
 * @brief Represents a bucket in a bucketized hash table.
 *
 * Each bucket can hold multiple product entries, facilitating better collision management.
 */
typedef struct {
    Product products[BUCKET_SIZE];   ///< Array of products stored in this bucket.
    int productCount;                ///< Number of products currently stored in the bucket.
} Bucket;  


/**
 * @struct MarketHoursAndLocation
 * @brief Stores operational hours and location details for a vendor.
 *
 * This struct helps in managing and displaying the business hours and location
 * for vendors in the marketplace.
 */
struct MarketHoursAndLocation {
    int vendorId;             ///< Vendor identifier to link hours and location.
    char location[100];       ///< Location description.
    char workingHours[50];    ///< Operating hours.
    char workingDays[20];     ///< Days of operation.
};

/**
 * @struct Node
 * @brief Represents a node in a graph for traversal and algorithm applications.
 *
 * Nodes are used in graph-based algorithms, typically involving traversal and
 * analysis of connected components or paths.
 */
struct Node {
    char* info;            ///< Information or label of the node.
    Node** neighbors;      ///< Array of pointers to neighbor nodes.
    int neighborCount;      ///< Number of neighbors.
};


/**
 * @struct SparseMatrixEntry
 * @brief Entry in a sparse matrix, typically used for storing pricing information.
 *
 * This struct is utilized in data structures where only non-zero elements are stored,
 * such as in sparse matrices for vendor and product price relationships.
 */
typedef struct {
    int vendorId;       ///< Vendor identifier.
    int productId;      ///< Product identifier.
    float price;        ///< Price associated with this vendor-product pair.
} SparseMatrixEntry;

/**
 * @struct BPlusTreeNode
 * @brief Represents a node in a B+ tree data structure.
 *
 * B+ tree nodes are part of the B+ tree used for efficient data storage and retrieval
 * that allows for high-performance indexing and sequential access.
 */
typedef struct BPlusTreeNode {
    bool isLeaf;                                      /**< Indicates if the node is a leaf */
    int keys[MAX_KEYS];                               /**< Indicates if the node is a leaf */
    struct BPlusTreeNode* children[MAX_KEYS + 1];     /**< Child pointers */
    int keyCount;                                     /**< Number of keys in the node */
    struct BPlusTreeNode* next;                       /**< Pointer to next leaf node (used for linked leaf nodes) */
} BPlusTreeNode;



/**
 * @struct MarketHours
 * @brief Represents the specific operating hours for a vendor on a given day.
 *
 * Used to store and manage detailed operating hours for vendors, which can be queried or displayed
 * to users or other parts of the system.
 */
typedef struct {
    int id;                ///< Unique identifier for the market hours entry.
    char day[20];          ///< Day of operation.
    char hours[20];        ///< Operating hours during the specified day.
    char location[50];     ///< Location of operation.
} MarketHours;


/**
 * @struct MarketHoursNode
 * @brief Node for storing market hours in an XOR linked list.
 *
 * Each node stores market hours information and uses XOR linking to minimize memory usage
 * by encoding both the previous and next nodes in one address.
 */
typedef struct MarketHoursNode {
    MarketHours data;                 ///< Market hours data.
    struct MarketHoursNode* xorPtr;   ///< XOR of previous and next nodes for link management.
} MarketHoursNode;

/**
 * @struct DoublyLinkedListNode
 * @brief Node in a doubly linked list for vendor management.
 *
 * This node structure supports forward and backward traversal through next and previous pointers,
 * making it suitable for applications where reverse navigation through vendor lists is required.
 */
typedef struct DoublyLinkedListNode {
    Vendor vendor;                         ///< Vendor data.
    struct DoublyLinkedListNode* next;     ///< Pointer to the next node in the list.
    struct DoublyLinkedListNode* prev;      ///< Pointer to the previous node in the list.
} DoublyLinkedListNode;


/**
 * @struct StackNode
 * @brief Node structure for a stack, typically used in depth-first search (DFS) applications.
 */
typedef struct StackNode {
    Vendor vendor;              ///< Vendor data stored in the stack node.
    struct StackNode* next;     ///< Pointer to the next node in the stack.
} StackNode;

/**
 * @struct Stack
 * @brief Structure representing a stack, used to manage data in a last-in-first-out (LIFO) manner.
 */
typedef struct Stack {
    StackNode* top;         ///< Pointer to the top node in the stack.
} Stack;


/**
 * @struct QueueNode
 * @brief Node structure for a queue, typically used in breadth-first search (BFS) applications.
 */
typedef struct QueueNode {
    Vendor vendor;               ///< Vendor data stored in the queue node.
    struct QueueNode* next;       ///< Pointer to the next node in the queue.
} QueueNode;


/**
 * @struct Queue
 * @brief Structure representing a queue, used to manage data in a first-in-first-out (FIFO) manner.
 */
typedef struct Queue {
    QueueNode* front;     ///< Pointer to the front node in the queue.
    QueueNode* rear;      ///< Pointer to the rear node in the queue.
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
 // Fonksiyon Prototipleri


#ifndef HUFFMAN_H  // HUFFMAN_H adında bir makro tanımlanmamışsa
#define HUFFMAN_H  // HUFFMAN_H adında bir makro tanımla


/**
 * @struct HuffNode
 * @brief Node structure for Huffman Tree.
 *
 * This structure represents a node in the Huffman Tree, used for Huffman coding. Each node
 * contains a character and its frequency in the dataset, along with pointers to left and right
 * child nodes, enabling the construction of the binary tree needed for encoding and decoding processes.
 *
 * @param dataHuff Character data stored in this node, representing a unique symbol in the Huffman Tree.
 * @param freqHuff Frequency of the character, used to build the tree based on the frequency of occurrence.
 * @param leftHuff Pointer to the left child node in the Huffman Tree.
 * @param rightHuff Pointer to the right child node in the Huffman Tree.
 */
typedef struct HuffNode {
    char dataHuff;                               /**< Character represented by this node */
    unsigned freqHuff;                           /**< Frequency of the character */
    struct HuffNode* leftHuff, * rightHuff;      /**< Pointer to the left child node */
} HuffNode;                                      /**< Pointer to the right child node */

/**
 * @struct MinHeap
 * @brief Structure representing a minimum heap (or min-heap).
 *
 * This structure is used to build and manipulate a minimum heap containing nodes of a Huffman Tree.
 * A min-heap is a complete binary tree where the value of each node is less than or equal to the values
 * of its children. This property is essential for efficient Huffman Tree construction, where the node
 * with the lowest frequency is always needed quickly.
 *
 * @param size Current number of nodes in the heap.
 * @param capacity Maximum capacity of the heap.
 * @param array Dynamically allocated array of pointers to HuffNode, representing the heap.
 */
typedef struct MinHeap {
    unsigned size;               /**< Current size of the heap */
    unsigned capacity;           /**< Maximum capacity of the heap */
    HuffNode** array;            /**< Pointer to array of pointers to HuffNode, representing the heap's structure */
} MinHeap;

// Fonksiyon Prototipleri
HuffNode* createNodeHuff(char data, unsigned freq);
MinHeap* createMinHeap(unsigned capacity);
void minHeapify(MinHeap* minHeap, int idx);
HuffNode* extractMin(MinHeap* minHeap);
void insertMinHeap(MinHeap* minHeap, HuffNode* node);
HuffNode* buildHuffmanTree(char data[], int freq[], int size);
void buildCodes(HuffNode* root, char* code, int top);
void huffmanEncode(char* input, char* output);
void huffmanDecode(HuffNode* root, char* encoded, char* output);
bool registerUser(HuffNode* root);
bool loginUser(HuffNode* root);
void clearScreen();
void setCursorPosition(int x, int y);
void displayWelcomeMessage();
bool listingOfLocalVendors();
bool addVendor();
bool updateVendor();
bool deleteVendor();
bool listVendors();
bool isDuplicate(Queue* queue, Vendor vendor);
#endif // HUFFMAN_H

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