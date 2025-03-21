/**
 * @file market.c
 * @brief Market Management System Utilities
 *
 * @details This source file contains essential utilities for managing a market system, including vendor and product management,
 * market hours, and user authentication mechanisms. The code is configured to prevent warnings from unsafe functions by defining
 * _CRT_SECURE_NO_WARNINGS. It extensively uses various STL containers and data structures to simulate real-world functionalities
 * such as hash tables for fast access and retrieval, and a stack for depth-first search implementations.
 *
 * This file also sets up several constants for system limits like table sizes and maximum values to ensure robust handling
 * of data within the system constraints. Error handling is facilitated through standard exceptions.
 *
 * Global variables are defined to track user authentication status and manage memory efficiently using hash tables and overflow
 * areas for excess data.
 *
 * @note Ensure that the library paths are correctly configured as the file includes headers from a relative path "../header/market.h".
 *
 * @warning This file uses several advanced C++ features and STL containers requiring good understanding of data structures.
 *
 * @author Tugba Nur Uygun - Sevval Asi - Durdane Naz Babaoglu - Irem Acinan
 * @date 2024-11-08
 */


// Includes necessary for functionality
#include "../header/market.h"    // Main definitions and prototypes for the market application.
#include <stdexcept>             // Standard exception class for handling exceptions.
#include <iostream>              // Standard I/O stream objects.
#include <string.h>              // String class for operations on strings.
#include <string>                // Input/output stream class to operate on files.
#include <fstream>               // Macro for boolean type.
#include <fstream>               // General purpose standard library.
#include <stdbool.h>             // Standard algorithms like sort, max, etc.
#include <stdlib.h>              // Standard Input Output library.
#include <algorithm>             // String stream.
#include <stdio.h>               // Standard Input Output library.
#include <sstream>               // String stream.
#include <time.h>                // Time functions.
#include <ctype.h>               // Character handling functions.
#include <stack>                 // Stack container for the C standard library.
#include <stdint.h>              // Standard types with specified widths.
#include <float.h>               // Limits of float types.
#include <unordered_map>         // Standard hash table container.
#include <queue>                 // Standard queue container.
#include <functional>            // Function objects, designed for use with standard algorithms.
#include <limits.h>              // Defines constants with the limits of fundamental types.
#include <cmath>
/** @brief TABLE_SIZE The number of slots in the hash table. */
#define TABLE_SIZE 100

/** @brief OVERFLOW_SIZE The number of slots in the overflow area of the hash table. */
#define OVERFLOW_SIZE 20

/** @brief BUCKET_SIZE The number of entries each bucket in the bucketized hash table can contain. */
#define BUCKET_SIZE 5

/** @brief MAX_VENDORS The maximum number of vendor records the application can handle. */
#define MAX_VENDORS 100

/** @brief MAX_PRODUCTS The maximum number of product records the application can manage. */
#define MAX_PRODUCTS 100

/** @brief MAX_TREE_HT The maximum height of any tree structure used in the application. */
#define MAX_TREE_HT 100

/** @brief MAX_KEYS The maximum number of keys a B-tree node can hold. */
#define MAX_KEYS 3

/** @brief MIN_KEYS The minimum number of keys a B-tree node must hold. */
#define MIN_KEYS (MAX_KEYS / 2)

/** @brief _CRT_SECURE_NO_WARNINGS Disables deprecation warnings in Visual Studio. */
#define _CRT_SECURE_NO_WARNINGS

// Global variables for application state.
bool isAuthenticated = false;    ///< Tracks whether a user is currently authenticated.

/**
 * @var hashTable
 * @brief Main hash table array storing entries up to TABLE_SIZE.
 *
 * This array serves as the primary storage for hash table entries within the application,
 * facilitating efficient data retrieval based on hashed keys.
 */
HashTableEntry hashTable[TABLE_SIZE];  

/**
 * @var overflowArea
 * @brief Overflow area for the main hash table to handle collisions, with a capacity of OVERFLOW_SIZE.
 *
 * When the main hash table entries experience collisions, this overflow area provides additional
 * storage to handle excess entries.
 */
HashTableEntry overflowArea[OVERFLOW_SIZE];  

/**
 * @var hashTableBuckets
 * @brief Array of buckets in the hash table, each bucket can hold multiple entries to manage collisions.
 *
 * This structure allows the hash table to handle collisions using chaining, where each bucket can
 * store multiple entries. Each bucket can expand dynamically to accommodate the entries that hash to the same bucket.
 */
Bucket hashTableBuckets[TABLE_SIZE];      

/**
 * @var overflowAreaa
 * @brief Secondary overflow area to manage additional overflow from the main hash table or buckets.
 *
 * Similar to the primary overflow area, but typically used when additional overflow handling is needed
 * beyond what is provided by the primary overflow area. This is particularly useful in high-collision scenarios.
 */
OverflowEntry overflowAreaa[OVERFLOW__SIZE];  

/**
 * @var hashTableBucketss
 * @brief Additional set of buckets, potentially used for a different or parallel hash table structure.
 *
 * This array may serve as a secondary or specialized bucket array in scenarios where multiple hash table
 * instances are needed, or different types of data are handled separately.
 */
Bucket hashTableBucketss[BUCKET_COUNT];         

/**
 * @brief Clears the terminal screen.
 *
 * Clears the screen for different operating systems.
 */
void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}


/**
 * @brief Handles user input for menu selections.
 *
 * @return An integer representing the user's choice.
 */
int getInput()
{
    int choice;
    int result = scanf("%d", &choice);

    if (result != 1) {printf("Invalid choice! Please try again.\n");while (fgetc(stdin) != '\n'); return getInput(); 
    }

    return choice;
}


/**
 * @brief Handles user authentication.
 *
 * This function provides an interface for user authentication by allowing login, registration,
 * guest mode, or exiting the system.
 *
 * @return Boolean indicating whether the program should continue running.
 */
bool userAuthentication() {

    char data[] = { 'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z' };
    int freq[] = { 5, 9, 12, 13, 16, 45, 7, 8, 5, 5, 7, 3, 10, 15, 20, 25, 12, 18, 23, 30, 10, 5, 7, 8, 9, 11 }; // Frekans örneği
    int size = sizeof(data) / sizeof(data[0]);
    HuffNode* root = buildHuffmanTree(data, freq, size);
    char code[MAX_CHAR];
    buildCodes(root, code, 0);


    int choice;
    char username[50];
    char password[50];
    do
    {
        clearScreen();
        printf("==========================================\n");
        printf("|           User Authentication          |\n");
        printf("==========================================\n");
        printf("| 1. Login                               |\n");
        printf("| 2. Register                            |\n");
        printf("| 3. Guest Mode                          |\n");
        printf("| 4. Exit                                |\n");
        printf("==========================================\n");
        printf("Choose an option: ");
        choice = getInput();

        switch (choice) {
        case 1:
            if (loginUser(root))
            {
                mainMenu();
            };
            break;
        case 2:
            registerUser(root);
            isAuthenticated = true;
            break;
        case 3:
            mainMenu();
            break;
        case 4:
            printf("Exiting the program...\n");
            return true;
        default:
            printf("Invalid option. Please try again.\n");
            getchar(); 
            break;
        }

    } while (choice != 4);return true;
}

/**
 * @brief Displays the main menu.
 *
 * This function displays the main menu of the system, allowing users to select options such as
 * viewing local vendors, products, price comparison, market hours, or keyword searches.
 *
 * @return Boolean indicating whether the main menu is still active.
 */
bool mainMenu() {
    int choice;

    do {
        clearScreen();
        printf("==========================================\n");
        printf("|               Main Menu                |\n");
        printf("==========================================\n");
        printf("| 1. Listing of Local Vendors            |\n");
        printf("| 2. Listing of Local Products           |\n");
        printf("| 3. Price Comparison                    |\n");
        printf("| 4. Market Hours and Locations          |\n");
        printf("| 5. Search Products or Enter Keywords   |\n");
        printf("| 0. Exit                                |\n");
        printf("==========================================\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            listingOfLocalVendors();
            break;
        case 2:
            listingOfLocalProducts();
            break;
        case 3:
            priceComparison();
            break;
        case 4:
            marketHoursAndLocations();
            break;
        case 5:
            searchProductsOrEnterKeyword();
            break;
        case 0:
            printf("Exiting the program...\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (choice != 0);

    return true;
}

/**
 * @brief Lists local vendors and provides operations on them.
 *
 * This function allows users to list local vendors, add, update, delete vendors, or view the vendor list.
 *
 * @return Boolean indicating whether the vendor listing menu is still active.
 */
bool listingOfLocalVendors() {
    int choice;

    do {
        clearScreen();
        printf("==========================================\n");
        printf("|     Listing of Local Vendors           |\n");
        printf("==========================================\n");
        printf("| 1. Add Vendor                          |\n");
        printf("| 2. Update Vendor                       |\n");
        printf("| 3. Delete Vendor                       |\n");
        printf("| 4. List Vendors                        |\n");
        printf("| 0. Return to Main Menu                 |\n");
        printf("==========================================\n");
        printf("Choose an option: ");
        choice = getInput();

        switch (choice) {
        case 1:
            addVendor();
            break;
        case 2:
            updateVendor();
            break;
        case 3:
            deleteVendor();
            break;
        case 4:
            listVendors();
            break;
        case 0:
            printf("Returning to main menu...\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
        }
    } while (choice != 0);

    return true;
}


/**
 * @brief Lists products available locally.
 *
 * This function allows users to list local products, add, update, delete products, or view the product list.
 *
 * @return Boolean indicating whether the product listing menu is still active.
 */
bool listingOfLocalProducts() {
int choice;

do {
    clearScreen();
    printf("==========================================\n");
    printf("|           List All Products            |\n");
    printf("==========================================\n");
    printf("| 1. Add Product                         |\n");
    printf("| 2. Update Product                      |\n");
    printf("| 3. Delete Product                      |\n");
    printf("| 4. Listing of Local Products           |\n");
    printf("| 0. Return to Main Menu                 |\n");
    printf("==========================================\n");
    printf("Choose an option: ");
    choice = getInput();

    switch (choice) {
    case 1:
        addProduct();
        break;
    case 2:
        updateProduct();
        break;
    case 3:
        deleteProduct();
        break;
    case 4:
        listingOfLocalVendorsandProducts();
        break;
    case 0:
        printf("Returning to main menu...\n");
        break;
    default:
        printf("Invalid option. Please try again.\n");
        break;
    }

} while (choice != 0);

return true;
}


/**
 * @brief Allows price comparison for products.
 *
 * This function provides an interface for selecting a product and comparing its prices among different vendors.
 *
 * @return Boolean indicating whether the price comparison menu is still active.
 */
bool priceComparison() {
    int choice;
    char selectedProductName[100] = "";  // We will keep the selected product name here

    do {
        clearScreen();
        printf("==========================================\n");
        printf("|            Price Comparison            |\n");
        printf("==========================================\n");
        printf("| 1. Select Product                      |\n");
        printf("| 2. Compare Prices                      |\n");
        printf("| 0. Return to Main Menu                 |\n");
        printf("==========================================\n");
        printf("Choose an option: ");
        choice = getInput();

        switch (choice) {
        case 1:
            // We pass the selectedProductName variable to the selectProduct function
            if (selectProduct(selectedProductName) == 0) { printf("Product '%s' selected.\n", selectedProductName);}
            else {
                printf("Product selection failed.\n");
            }
            break;
        case 2:
            if (strlen(selectedProductName) > 0) { comparePricesByName(selectedProductName);}
            else {
                printf("No product selected. Please select a product first.\n");
            }
            break;
        case 0:
            printf("Returning to main menu...\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
            break;
        }

        printf("Press Enter to continue...");
        getchar();  // Wait for the user to press Enter
      /*  getchar(); */ // To clean the tampon

    } while (choice != 0);

    return true;
}


/**
 * @brief Manages market hours and locations.
 *
 * This function allows users to add, update, or view market hours and locations.
 *
 * @return Boolean indicating whether the market hours menu is still active.
 */
bool marketHoursAndLocations() {
    int choice;

    do {
        printf("==========================================\n");
        printf("|      Market Hours and Locations        |\n");
        printf("==========================================\n");
        printf("| 1. Add Working Hours and Location      |\n");
        printf("| 2. Update Market Hours and Location    |\n");
        printf("| 3. View Market Hours and Locations     |\n");
        printf("| 0. Return to Main Menu                 |\n");
        printf("==========================================\n");
        printf("Choose an option: ");

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid option.\n");
            while (getchar() != '\n');
            choice = -1;
            continue;
        }

        switch (choice) {
        case 1:
            addMarketHoursAndLocation();
            break;
        case 2:
            updateMarketHoursAndLocation();
            break;
        case 3:
            displayMarketHoursAndLocations();
            break;
        case 0:
            printf("Returning to main menu...\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
            break;
        }
    } while (choice != 0);

    return true;
}

/**
 * @brief Searches for products or keywords in the database.
 *
 * This function allows users to either search for products by their name or enter specific keywords for search.
 *
 * @return Boolean indicating whether the search menu is still active.
 */
bool searchProductsOrEnterKeyword() {
    int choice;

    do {
        clearScreen();
        printf("==========================================\n");
        printf("|   Search Products or Enter Keyword     |\n");
        printf("==========================================\n");
        printf("| 1. Enter Search Products               |\n");
        printf("| 2. Enter Keywords                      |\n");
        printf("| 0. Return to Main Menu                 |\n");
        printf("==========================================\n");
        printf("Choose an option: ");
        choice = getInput();

        switch (choice) {
        case 1:
            enterSearchProducts();
            break;
        case 2:
            enterKeywords();
            break;
        case 0:
            printf("Returning to main menu...\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
            break;
        }

    } while (choice != 0);

    return true;
}

User userList[MAX_USERS];
int userCount = 0;

char huffmanCodes[MAX_CHAR][MAX_CHAR] = { "" };

/**
 * @brief Creates a new Huffman tree node.
 *
 * Allocates memory for a new Huffman tree node with given character data and frequency,
 * initializing left and right child pointers to NULL.
 *
 * @param data The character data of the node.
 * @param freq The frequency of the character data.
 * @return HuffNode* Pointer to the newly created Huffman tree node.
 */
HuffNode* createNodeHuff(char data, unsigned freq) {
    HuffNode* node = (HuffNode*)malloc(sizeof(HuffNode));
    node->dataHuff = data;
    node->freqHuff = freq;
    node->leftHuff = node->rightHuff = NULL;
    return node;
}

/**
 * @brief Creates a MinHeap with a specified capacity.
 *
 * Allocates memory for a MinHeap structure and initializes its size to zero and its capacity
 * to the provided value. It also allocates memory for the array of pointers to HuffNode.
 *
 * @param capacity The maximum capacity of the MinHeap.
 * @return MinHeap* Pointer to the newly created MinHeap.
 */
MinHeap* createMinHeap(unsigned capacity) {
    MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (HuffNode**)malloc(minHeap->capacity * sizeof(HuffNode*));  
    return minHeap;
}

/**
 * @brief Maintains the heap property of a MinHeap starting from a given index.
 *
 * Reorders the elements of the MinHeap starting from a given index to maintain the min-heap property.
 * This function is used internally by other heap operations like insertions and deletions.
 *
 * @param minHeap Pointer to the MinHeap.
 * @param idx The starting index to perform heapify.
 */
void minHeapify(MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freqHuff < minHeap->array[smallest]->freqHuff)
        smallest = left;

    if (right < minHeap->size && minHeap->array[right]->freqHuff < minHeap->array[smallest]->freqHuff)
        smallest = right;

    if (smallest != idx) {
        HuffNode* temp = minHeap->array[smallest];
        minHeap->array[smallest] = minHeap->array[idx];
        minHeap->array[idx] = temp;
        minHeapify(minHeap, smallest);
    }
}

/**
 * @brief Extracts the node with the minimum frequency from the MinHeap.
 *
 * Removes and returns the root of the MinHeap, which contains the minimum frequency. The heap
 * property is maintained after removal.
 *
 * @param minHeap Pointer to the MinHeap.
 * @return HuffNode* Pointer to the node with the minimum frequency.
 */
HuffNode* extractMin(MinHeap* minHeap) {
    HuffNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    minHeap->size--;
    minHeapify(minHeap, 0);
    return temp;
}

/**
 * @brief Inserts a new node into the MinHeap.
 *
 * Inserts a new Huffman tree node into the MinHeap and rearranges it to maintain the heap property.
 *
 * @param minHeap Pointer to the MinHeap.
 * @param node Pointer to the HuffNode to be inserted.
 */
void insertMinHeap(MinHeap* minHeap, HuffNode* node) {
    int i = minHeap->size++;
    while (i && node->freqHuff < minHeap->array[(i - 1) / 2]->freqHuff) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }
    minHeap->array[i] = node;
}

/**
 * @brief Builds the Huffman Tree from given character data and frequencies.
 *
 * Constructs a Huffman Tree for the purpose of Huffman encoding, using specified character data
 * and their respective frequencies. The function uses a MinHeap to facilitate the construction
 * of the tree.
 *
 * @param data Array of characters.
 * @param freq Array of frequencies corresponding to the characters.
 * @param size The number of elements in the data and freq arrays.
 * @return HuffNode* Pointer to the root of the constructed Huffman Tree.
 */
HuffNode* buildHuffmanTree(char data[], int freq[], int size) {
    HuffNode* left, * right, * top;

    MinHeap* minHeap = createMinHeap(size);
    for (int i = 0; i < size; i++)
        minHeap->array[i] = createNodeHuff(data[i], freq[i]);
    minHeap->size = size;

    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = createNodeHuff('$', left->freqHuff + right->freqHuff);
        top->leftHuff = left;
        top->rightHuff = right;

        insertMinHeap(minHeap, top);
    }
    return extractMin(minHeap);
}

/**
 * @brief Builds Huffman codes for characters in the Huffman Tree.
 *
 * Recursively generates Huffman codes for the leaf nodes of the Huffman Tree and stores them.
 * The function traverses the tree from the root to every leaf, assigning '0' for left and '1'
 * for right moves.
 *
 * @param root Pointer to the root node of the Huffman Tree.
 * @param code Array to store the current path as a code.
 * @param top The current length of the code path.
 */
void buildCodes(HuffNode* root, char* code, int top) {
    if (root->leftHuff) {
        code[top] = '0';
        buildCodes(root->leftHuff, code, top + 1);
    }
    if (root->rightHuff) {
        code[top] = '1';
        buildCodes(root->rightHuff, code, top + 1);
    }
    if (!root->leftHuff && !root->rightHuff) {
        code[top] = '\0';
        int index = (int)root->dataHuff;  
        if (index >= 0 && index < MAX_CHAR) {
            strcpy(huffmanCodes[index], code);
        }
    }
}

/**
 * @brief Encodes a string using Huffman codes.
 *
 * Encodes the input string using previously built Huffman codes and stores the result in the output string.
 *
 * @param input The input string to be encoded.
 * @param output The output string where the encoded data will be stored.
 */
void huffmanEncode(char* input, char* output) {
    for (int i = 0; input[i] != '\0'; i++) {
        int index = (int)input[i]; 
        if (strlen(huffmanCodes[index]) > 0) {
            strcat(output, huffmanCodes[index]);  
        }
    }
}

/**
 * @brief Decodes a string using the Huffman Tree.
 *
 * Decodes the input encoded string using the Huffman Tree and stores the decoded result in the output string.
 *
 * @param root Pointer to the root node of the Huffman Tree used for decoding.
 * @param encoded The encoded string to be decoded.
 * @param output The output string where the decoded data will be stored.
 */
void huffmanDecode(HuffNode* root, char* encoded, char* output) {
    HuffNode* current = root;
    int index = 0;
    for (int i = 0; encoded[i] != '\0'; i++) {
        if (encoded[i] == '0')
            current = current->leftHuff;
        else
            current = current->rightHuff;

        if (!current->leftHuff && !current->rightHuff) {
            output[index++] = current->dataHuff;
            current = root;
        }
    }
    output[index] = '\0';
}

/**
 * @brief Registers a new user by encoding their username and password using Huffman coding.
 *
 * Prompts the user for a username and password, encodes these credentials using Huffman coding,
 * and stores them in a file. This function provides user feedback and handles basic input/output operations.
 *
 * @param root Pointer to the root of the Huffman Tree used for encoding.
 * @return bool Returns true if the user registration is successful, false otherwise.
 */
bool registerUser(HuffNode* root) {
    char username[50], password[50];
    char encoded[1000] = "";

    clearScreen();
    
    printf("===== Register User Menu =====\n");
    
    printf("Enter username: ");
    scanf("%s", username);
    
    printf("Enter password: ");
    scanf("%s", password);

    huffmanEncode(username, encoded);
    strcat(encoded, ":");
    huffmanEncode(password, encoded + strlen(encoded));

    FILE* file = fopen("user_data.huff", "a");
    fprintf(file, "%s\n", encoded);
    fclose(file);

    
    printf("User registered successfully!\n");
    while (getchar() != '\n');
    getchar();
    return true;
}

/**
 * @brief Authenticates a user by comparing encoded credentials against stored Huffman encoded data.
 *
 * Prompts for username and password, encodes them, and checks against previously stored encoded credentials.
 * This function also handles file operations for reading user data and provides user feedback.
 *
 * @param root Pointer to the root of the Huffman Tree used for encoding and decoding.
 * @return bool Returns true if login is successful (credentials match), false otherwise.
 */
bool loginUser(HuffNode* root) {
    char username[50], password[50];
    char encodedUsername[1000] = "", encodedPassword[1000] = "";
    char line[1000], decoded[1000];

    clearScreen();
    
    printf("===== Login User Menu =====\n");
    
    printf("Enter username: ");
    scanf("%s", username);
    
    printf("Enter password: ");
    scanf("%s", password);

    huffmanEncode(username, encodedUsername);
    huffmanEncode(password, encodedPassword);

    FILE* file = fopen("user_data.huff", "r");
    if (!file) {
        printf("Error: Unable to open user data file.\n");
        return false;
    }

    while (fgets(line, sizeof(line), file)) {
        char* encoded = strtok(line, ":");
        char* encodedPass = strtok(NULL, "\n");

        if (encoded == NULL || encodedPass == NULL) continue;

        huffmanDecode(root, encoded, decoded);
        if (strcmp(decoded, username) == 0) {
            huffmanDecode(root, encodedPass, decoded);
            if (strcmp(decoded, password) == 0) {
                
                printf("Login successful!\n");
                
                fclose(file);
                return true;
            }
        }
    }

    fclose(file);
    
    printf("Login failed. Username or password is incorrect.\n");
    while (getchar() != '\n');
    getchar();
    return false;
}

/**
 * @brief Adds a vendor to the system.
 *
 * This function is used to add a vendor to the system. It assigns a random 6-digit ID, takes the vendor's name, and stores the information in a binary file.
 *
 * @return Boolean indicating whether the vendor was successfully added.
 */
bool addVendor() {
    FILE* file;
    Vendor vendor;

    file = fopen("vendor.bin", "ab"); // We open the file in insert mode
    if (file == NULL) {printf("Error opening vendor file.\n");return false;}

    printf("\n--- List of Vendors ---\n");
    int vendorCount = 0; // To track the number of vendors we have listed

    // Generate a random 6-digit ID
    srand(time(NULL));  // Initialize the random number generator
    vendor.id = (rand() % 900000) + 100000;  // Generate a random number between 100000 and 999999

    printf("Assigned Vendor ID: %d\n", vendor.id);  // We show the assigned ID

    // Retrieving only the name from the user
    printf("Enter Vendor Name: ");
    scanf("%49s", vendor.name);  // We prevent overflows by using 49%49s
    while (getchar() != '\n');  // Clean the tampon

    // Write to file (ID and name)
    fwrite(&vendor, sizeof(Vendor), 1, file);
    fclose(file);

    printf("Vendor added successfully!\n");

    // Wait for the user to press a key to continue
    printf("Press Enter to continue...");
    getchar();  // Wait for the user to press a key to continue

    return true;
}


/**
 * @brief Updates an existing vendor's information.
 *
 * This function allows users to update the details of an existing vendor in the system.
 * The user is prompted to enter a vendor ID, and if found, the vendor's information is updated.
 *
 * @return Boolean indicating whether the vendor was successfully updated.
 */
bool updateVendor() {
    FILE* file;
    Vendor vendor;
    int id, found = 0;
    file = fopen("vendor.bin", "rb+"); // We open the file in read and write mode

    if (file == NULL) {printf("Error opening vendor file.\n");return 1;}

    printf("Enter Vendor ID to update: ");
    scanf("%d", &id);
    // To remove the excess from the tampon:
    while (getchar() != '\n');  // Clear extra newline character


    while (fread(&vendor, sizeof(Vendor), 1, file)) {
        if (vendor.id == id) {printf("Enter new Vendor Name: ");scanf("%s", vendor.name);fseek(file, -sizeof(Vendor), SEEK_CUR);fwrite(&vendor, sizeof(Vendor), 1, file);found = 1;printf("Vendor updated successfully!\n");break;}}

    if (!found) {
        printf("Vendor with ID %d not found.\n", id);
    }
    fclose(file); // Remember to close the file
    // Buffer clearing and waiting for key press to continue
    while (getchar() != '\n');  // Clear extra newline character
    printf("Press Enter to continue...");
    getchar();  // Wait for the user to press Enter

    return true;
}

/**
 * @brief Deletes a vendor from the system.
 *
 * This function deletes a vendor identified by their unique ID from the system.
 * The data is read from the original file and rewritten, excluding the deleted vendor.
 *
 * @return Boolean indicating whether the vendor was successfully deleted.
 */
bool deleteVendor() {
    FILE* file, * tempFile;
    Vendor vendor;
    int id, found = 0;

    file = fopen("vendor.bin", "rb");
    tempFile = fopen("temp.bin", "wb");

    if (file == NULL || tempFile == NULL) {printf("Error opening file.\n");return 1;}

    printf("Enter Vendor ID to delete: ");
    scanf("%d", &id);
    while (getchar() != '\n');  // Clear input buffer

    while (fread(&vendor, sizeof(Vendor), 1, file)) {
        if (vendor.id != id) {
            fwrite(&vendor, sizeof(Vendor), 1, tempFile);}else { found = 1;}}

    fclose(file);
    fclose(tempFile);

    remove("vendor.bin");
    rename("temp.bin", "vendor.bin");

    if (found) {printf("Vendor deleted successfully!\n");}
    else {
        printf("Vendor with ID %d not found.\n", id);
    }
    printf("Press Enter to continue...");
    getchar();

    return true;
}

/**
 * @brief Initializes the head of a doubly linked list.
 *
 * This line sets up the starting point for a doubly linked list used to sort vendors by their IDs.
 * The 'head' pointer is initialized to NULL, indicating that the list is initially empty.
 * This setup is crucial before any operations like insertion, deletion, or traversal can be performed on the list.
 * The list is intended to be populated with vendor nodes, sorted by their IDs using a combination of a hash table
 * and a min-heap for efficient sorting and access.
 */
DoublyLinkedListNode* head = NULL;


/**
 * @brief Inserts a new vendor into a sorted doubly linked list by vendor ID.
 *
 * This function creates a new node for a given vendor and inserts it into
 * the linked list in a position that maintains order by vendor ID.
 *
 * @param newVendor The vendor to be inserted.
 */
void insertVendor(Vendor newVendor) {
    DoublyLinkedListNode* newNode = (DoublyLinkedListNode*)malloc(sizeof(DoublyLinkedListNode));
    newNode->vendor = newVendor;
    newNode->next = NULL;
    newNode->prev = NULL;

    // If the list is currently empty, insert as the first element
    if (head == NULL) { // If the list is empty
        head = newNode;
    }
    else {
        DoublyLinkedListNode* current = head;
        DoublyLinkedListNode* previous = NULL;

        // Traverse the list to find the insertion point
        while (current != NULL && current->vendor.id < newVendor.id) {
            previous = current;
            current = current->next;
        }

        if (previous == NULL) { newNode->next = head;head->prev = newNode;head = newNode;}
        else { // Insert in the middle or at the end
            newNode->next = current;
            newNode->prev = previous;
            previous->next = newNode;
            if (current != NULL) {
                current->prev = newNode;
            }
        }
    }
}

/**
 * @brief Creates and initializes a stack.
 *
 * Allocates memory for a new stack and sets its top pointer to NULL.
 *
 * @return A pointer to the newly created stack.
 */
Stack* createStack() {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    stack->top = NULL;
    return stack;
}


/**
 * @brief Checks if a stack is empty.
 *
 * @param stack The stack to check.
 * @return True if the stack is empty, false otherwise.
 */
bool isStackEmpty(Stack* stack) {
    return stack->top == NULL;
}


/**
 * @brief Pushes a vendor onto the stack.
 *
 * Adds a new vendor to the top of the stack.
 *
 * @param stack The stack where the vendor will be added.
 * @param vendor The vendor to add to the stack.
 */
void push(Stack* stack, Vendor vendor) {
    StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
    newNode->vendor = vendor;
    newNode->next = stack->top;
    stack->top = newNode;
}


/**
 * @brief Pops a vendor from the stack.
 *
 * Removes the vendor at the top of the stack and returns it. If the stack is empty,
 * an empty vendor struct is returned and a message is printed.
 *
 * @param stack The stack from which the vendor will be popped.
 * @return The vendor at the top of the stack or an empty vendor if the stack is empty.
 */
Vendor pop(Stack* stack) {
    if (isStackEmpty(stack)) {printf("Stack is empty.\n");Vendor emptyVendor = { 0 };return emptyVendor;}
    StackNode* temp = stack->top;
    Vendor vendor = temp->vendor;
    stack->top = stack->top->next;
    free(temp);
    return vendor;
}


/**
 * @brief Frees all memory allocated for the stack.
 *
 * Deallocates all nodes in the stack and the stack itself.
 *
 * @param stack The stack to be freed.
 */
void freeStack(Stack* stack) {
    while (!isStackEmpty(stack)) {
        pop(stack);
    }
    free(stack);
}


/**
 * @brief Creates and initializes a queue.
 *
 * Allocates memory for a new queue and initializes its front and rear pointers to NULL.
 *
 * @return A pointer to the newly created queue.
 */
Queue* createQueue() {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->front = NULL;
    queue->rear = NULL;
    return queue;
}


/**
 * @brief Checks if a queue is empty.
 *
 * @param queue The queue to check.
 * @return True if the queue is empty, false otherwise.
 */
bool isQueueEmpty(Queue* queue) {
    return queue->front == NULL;
}


/**
 * @brief Enqueues a vendor to the rear of the queue.
 *
 * Adds a new vendor to the end of the queue.
 *
 * @param queue The queue where the vendor will be added.
 * @param vendor The vendor to enqueue.
 */
void enqueue(Queue* queue, Vendor vendor) {
    QueueNode* newNode = (QueueNode*)malloc(sizeof(QueueNode));
    newNode->vendor = vendor;
    newNode->next = NULL;
    if (queue->rear == NULL) {
        queue->front = newNode;
        queue->rear = newNode;
    }
    else {
        queue->rear->next = newNode;
        queue->rear = newNode;
    }
}


/**
 * @brief Dequeues a vendor from the front of the queue.
 *
 * Removes the vendor at the front of the queue and returns it. If the queue is empty,
 * an empty vendor struct is returned.
 *
 * @param queue The queue from which the vendor will be dequeued.
 * @return The vendor at the front of the queue or an empty vendor if the queue is empty.
 */
Vendor dequeue(Queue* queue) {
    if (queue->front == NULL) {Vendor emptyVendor = { 0 }; return emptyVendor;}

    QueueNode* temp = queue->front;
    Vendor vendor = temp->vendor;
    queue->front = queue->front->next;

    if (queue->front == NULL) {
        queue->rear = NULL; // Kuyrukta hiçbir eleman kalmadıysa, rear'i de NULL yap
    }

    free(temp);
    return vendor;
}


/**
 * @brief Frees all memory allocated for the queue.
 *
 * Deallocates all nodes in the queue and the queue itself.
 *
 * @param queue The queue to be freed.
 */
void freeQueue(Queue* queue) {
    while (!isQueueEmpty(queue)) {dequeue(queue);}
    free(queue);
}

/**
 * @brief Lists all vendors from a binary file and manages navigation through them.
 *
 * Opens a binary file to read vendor data, loads vendors into a stack and a queue,
 * and allows user interaction for navigating through vendors in a doubly linked list.
 * The user can traverse through the vendors in different orders and exit when desired.
 * This function also demonstrates the usage of stacks, queues, and doubly linked lists
 * for handling data in memory.
 *
 * @return True if the function executes successfully, False if the file cannot be opened.
 */
bool listVendors() {
    FILE* file;
    Vendor vendor;
    file = fopen("vendor.bin", "rb"); // Dosyayı okuma modunda açıyoruz

    if (file == NULL) {printf("Error opening vendor file.\n");return false;}

    // Initialize data structures for handling vendors
    Stack* vendorStack = createStack();
    Queue* vendorQueue = createQueue();

    // Read vendors from file and store in data structures
    while (fread(&vendor, sizeof(Vendor), 1, file)) {
        if (!isDuplicate(vendorQueue, vendor)) {
            enqueue(vendorQueue, vendor); // Enqueue non-duplicate vendors
        }
        push(vendorStack, vendor); // Push all vendors onto the stack
        insertVendor(vendor); // Insert vendors into the doubly linked list sorted by ID
    }


    fclose(file); // Close the file after reading

    // Interactive vendor listing
    printf("\n--- List of Vendors ---\n");
    char choice;
    DoublyLinkedListNode* current = head;

    while (current != NULL) {
        printf("ID: %d, Name: %s\n", current->vendor.id, current->vendor.name);
        printf("\n'n' for Next, 'p' for Previous, 's' for Stack traversal, 'q' for Queue traversal, 'x' to Quit: ");
        scanf(" %c", &choice);
        clearScreen();

        if (choice == 'n') {if (current->next != NULL) {current = current->next;}
            else {
                printf("No more vendors in this direction.\n");
            }
        }
        else if (choice == 'p') {if (current->prev != NULL) {current = current->prev;}else {printf("No more vendors in this direction.\n");}}
        else if (choice == 's') {printf("\n--- Stack Traversal (Last In, First Out) ---\n");while (!isStackEmpty(vendorStack)) {Vendor v = pop(vendorStack);printf("ID: %d, Name: %s\n", v.id, v.name);}}
        else if (choice == 'q') {
            printf("\n--- Queue Traversal (First In, First Out) ---\n");
            while (!isQueueEmpty(vendorQueue)) {
                Vendor v = dequeue(vendorQueue);
                printf("ID: %d, Name: %s\n", v.id, v.name);
            }
        }
        else if (choice == 'x') {
            break;}
        else {
            printf("Invalid input. Please use 'n', 'p', 's', 'q', or 'x'.\n");
        }
    }

    // Clean up memory
    current = head;
    while (current != NULL) {
        DoublyLinkedListNode* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;

    freeStack(vendorStack);
    freeQueue(vendorQueue);

    printf("Returning to menu...\n");
    return true;
}


/**
 * @brief Checks for duplicate vendor IDs in a queue.
 *
 * Iterates through a queue to find if a vendor with the same ID already exists in it.
 * Used to avoid adding duplicate entries to the queue when reading from the file.
 *
 * @param queue The queue to check for duplicates.
 * @param vendor The vendor whose ID to check for duplicates.
 * @return True if a duplicate is found, false otherwise.
 */
bool isDuplicate(Queue* queue, Vendor vendor) {
    QueueNode* current = queue->front;

    while (current != NULL) {
        if (current->vendor.id == vendor.id) {
            // Vendor ID zaten kuyrukta varsa, tekrarlama var demektir
            return true;
        }
        current = current->next;
    }

    return false; // Eğer kuyruğun sonuna kadar aynı ID bulunmadıysa, tekrarlama yok demektir
}



/**
 * @brief Adds a new product to the products file.
 *
 * This function allows the user to add a product to the "products.bin" file.
 * It first verifies whether the vendor ID exists in the "vendor.bin" file before adding the product.
 *
 * @return Returns true (1) if the product is added successfully, false (0) otherwise.
 */
bool addProduct() {
    FILE* productFile;
    FILE* vendorFile;
    Product product;
    Vendor vendor;
    int found = 0;

    productFile = fopen("products.bin", "ab"); 
    if (productFile == NULL) {printf("Error opening product file.\n");return false;}

    vendorFile = fopen("vendor.bin", "rb"); 
    if (vendorFile == NULL) {printf("Error opening vendor file.\n");fclose(productFile);return false;}

    printf("Enter Vendor ID for the product: ");
    scanf("%d", &product.vendorId);

    // Check the vendor ID
    while (fread(&vendor, sizeof(Vendor), 1, vendorFile)) {
        if (vendor.id == product.vendorId) {found = 1; break;}
    }

    fclose(vendorFile);  // Close the vendor file

    if (!found) {
        printf("Error: Vendor with ID %d does not exist.\n", product.vendorId);
        fclose(productFile);
        printf("Press Enter to continue...");
        getchar(); // Once again getchar() because we are clearing the buffer
        return false; }printf("Enter Product Name: ");scanf("%s", product.productName);printf("Enter Product Price: ");
    scanf("%f", &product.price);

    printf("Enter Product Quantity: ");
    scanf("%d", &product.quantity);

    printf("Enter Product Season: ");
    scanf("%s", product.season);

    //We write the product information in the file
    fwrite(&product, sizeof(Product), 1, productFile);
    fclose(productFile);

    printf("Product added successfully!\n");

    printf("Press Enter to continue...");
    getchar();
    getchar();  // Clean the buffer and continue


    return true;
}


/**
 * @brief Updates an existing product in the products file.
 *
 * This function updates a product's details in the "products.bin" file by asking for the product name.
 * If the product is found, it allows the user to modify the details of that product.
 *
 * @return Returns true (1) if the product is updated successfully, false (0) otherwise.
 */
bool updateProduct() {
    FILE* productFile, * tempFile;
    Product product;
    char productName[50];
    int found = 0;

    productFile = fopen("products.bin", "rb"); 
    if (productFile == NULL) {printf("Error opening product file.\n");return 1;}

    tempFile = fopen("temp.bin", "wb");
    if (tempFile == NULL) {printf("Error creating temporary file.\n");fclose(productFile);return 1;}

    printf("Enter Product Name to update: ");
    scanf("%s", productName);

    // Read all products from the file and check the name
    while (fread(&product, sizeof(Product), 1, productFile)) {if (strcmp(product.productName, productName) == 0) {found = 1;printf("Enter new Product Name: ");scanf("%s", product.productName);printf("Enter new Product Price: ");scanf("%f", &product.price);printf("Enter new Product Quantity: ");scanf("%d", &product.quantity);printf("Enter new Product Season: ");scanf("%s", product.season);}fwrite(&product, sizeof(Product), 1, tempFile);}

    fclose(productFile);
    fclose(tempFile);

    if (!found) {
        printf("Product with name %s not found.\n", productName);
        remove("temp.bin"); // Delete temporary file
    }
    else {
        remove("products.bin"); // Delete original file
        rename("temp.bin", "products.bin"); // Rename temporary file as original file
        printf("Product updated successfully!\n");
    }

    printf("Press Enter to continue...");
    getchar();
    getchar();

    return true;
}


/**
 * @brief Deletes an existing product from the products file.
 *
 * This function deletes a product from the "products.bin" file by asking for the product name.
 * If the product is found, it is removed from the file.
 *
 * @return Returns true (1) if the product is deleted successfully, false (0) otherwise.
 */
bool deleteProduct() {
    FILE* productFile, * tempFile;
    Product product;
    char productName[50];
    int found = 0;

    productFile = fopen("products.bin", "rb");
    if (productFile == NULL) {printf("Error opening product file.\n");return 1;}

    tempFile = fopen("temp.bin", "wb"); 
    if (tempFile == NULL) {printf("Error creating temporary file.\n");fclose(productFile);return 1;}

    printf("Enter Product Name to delete: ");
    scanf("%s", productName);

    // Read all products from the file and check the name
    while (fread(&product, sizeof(Product), 1, productFile)) {if (strcmp(product.productName, productName) == 0) {found = 1;printf("Product with name %s deleted successfully!\n", productName);continue; }fwrite(&product, sizeof(Product), 1, tempFile); }

    fclose(productFile);
    fclose(tempFile);

    if (!found) {
        printf("Product with name %s not found.\n", productName);
        remove("temp.bin"); // Delete temporary file
    }
    else {
        remove("products.bin"); // Delete original file
        rename("temp.bin", "products.bin"); // Rename temporary file as original file
    }

    printf("Press Enter to continue...");
    getchar();
    getchar();

    return true;
}


/**
 * @brief Lists all vendors and their respective products.
 *
 * This function reads the "vendor.bin" file to list all vendors, and for each vendor, lists the products associated with them from "products.bin".
 * It provides the user an option to select a collision resolution strategy for vendor products.
 *
 * @return Returns true (1) when listing is complete.
 */
bool listingOfLocalVendorsandProducts() {
    FILE* productFile;
    FILE* vendorFile;
    Product product;
    Vendor vendor;
    int found = 0;

    productFile = fopen("products.bin", "rb");
    if (productFile == NULL) {printf("Error opening product file.\n");return false;}

    vendorFile = fopen("vendor.bin", "rb");
    if (vendorFile == NULL) {printf("Error opening vendor file.\n");fclose(productFile);return false;}

    printf("\n--- Listing All Vendors and Their Products ---\n");

    // Make the user select a search method
    int strategy;
    printf("Select Collision Resolution Strategy for All Vendors:\n");
    printf("1. Linear Probing\n");
    printf("2. Quadratic Probing\n");
    printf("3. Double Hashing\n");
    printf("4. Linear Quotient\n");
    printf("5. Progressive Overflow\n");
    printf("6. Use of Buckets\n");
    printf("7. Brent's Method\n");
    printf("8. Exit\n");
    scanf("%d", &strategy);

    if (strategy == 8) {
        printf("Exiting the product list\n");
        fclose(vendorFile);
        fclose(productFile);
        return true;
    }

    rewind(productFile); // Reset file pointer for products

    // Loop through all vendors
    while (fread(&vendor, sizeof(Vendor), 1, vendorFile)) {
        printf("\nVendor: %s (ID: %d)\n", vendor.name, vendor.id);
        printf("--------------------------\n");

        // Loop through all products for the current vendor
        rewind(productFile); // Reset product file pointer for each vendor
        int productFound = 0;

        while (fread(&product, sizeof(Product), 1, productFile)) {
            if (product.vendorId == vendor.id && product.price != 0 && product.quantity != 0) {
                switch (strategy) {
                case 1: // Linear Probing
                    printf("Using Linear Probing for Product: %s\n", product.productName);
                    break;
                case 2: // Quadratic Probing
                    printf("Using Quadratic Probing for Product: %s\n", product.productName);
                    break;
                case 3: // Double Hashing
                    printf("Using Double Hashing for Product: %s\n", product.productName);
                    break;
                case 4: // Linear Quotient
                    printf("Using Linear Quotient for Product: %s\n", product.productName);
                    break;
                case 5: // Progressive Overflow
                    printf("Using Progressive Overflow for Product: %s\n", product.productName);
                    break;
                case 6: // Use of Buckets
                    printf("Using Use of Buckets for Product: %s\n", product.productName);
                    break;
                case 7: // Brent's Method
                    printf("Using Brent's Method for Product: %s\n", product.productName);
                    break;
                default:
                    printf("Invalid strategy selected.\n");
                    fclose(vendorFile);
                    fclose(productFile);
                    return false;
                }
                printf("Product: %s, Price: %.2f, Quantity: %d, Season: %s\n",
                    product.productName, product.price, product.quantity, product.season);
                productFound = 1;
                found = 1;
            }
        }

        if (!productFound) {
            printf("No products available for this vendor.\n");
        }
    }

    if (!found) {printf("No products found for any vendor.\n");}

    fclose(vendorFile);
    fclose(productFile);

    printf("\nPress Enter to return to menu...");
    getchar();
    getchar();

    return true;
}


/**
 * @brief Represents a sparse matrix entry for vendor-product relationships.
 * @details Used to store non-zero relationships between vendors and products, including prices.
 */
SparseMatrixEntry sparseMatrix[MAX_VENDORS * MAX_PRODUCTS];

/**
 * @brief The current size of the sparse matrix containing vendor-product relationships.
 */
int sparseMatrixSize = 0;



/**
 * @brief Adds a relationship between a vendor and a product.
 *
 * @param vendorId The ID of the vendor.
 * @param productId The ID of the product.
 * @param price The price of the product from the vendor.
 *
 * @note The function ignores the relation if the price is zero.
 */
void addVendorProductRelation(int vendorId, int productId, float price) {

    if (price == 0) {return;
    }
    // We add a new relation to the sparse matrix
    sparseMatrix[sparseMatrixSize].vendorId = vendorId;
    sparseMatrix[sparseMatrixSize].productId = productId;
    sparseMatrix[sparseMatrixSize].price = price;
    sparseMatrixSize++;
}

/**
 * @brief Lists all products offered by a specific vendor.
 *
 * @param vendorId The ID of the vendor whose products are to be listed.
 *
 * @note If no products are found for the vendor, a corresponding message is displayed.
 */
bool listProductsByVendor(int vendorId) {
    printf("\n--- Products offered by Vendor %d ---\n", vendorId);
    int found = 0;
    for (int i = 0; i < sparseMatrixSize; i++) { if (sparseMatrix[i].vendorId == vendorId) {  printf("Product ID: %d, Price: %.2f\n", sparseMatrix[i].productId, sparseMatrix[i].price); found = 1;}}
    if (!found) {
        printf("No products found for Vendor %d.\n", vendorId);
    }
    return true;
}

/**
 * @brief Hash function to determine the index for a given key.
 *
 * @param key The key to be hashed.
 * @return The hashed index for the key.
 */
int hashFunction(int key) {
    return key % TABLE_SIZE;
}


/**
 * @brief Initializes the hash table and overflow areas.
 *
 * @details Sets up the hash table and overflow area by marking all entries as unoccupied.
 */
void initializeHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].isOccupied = 0;
        hashTableBuckets[i].productCount = 0;
    }
    for (int i = 0; i < OVERFLOW_SIZE; i++) {
        overflowArea[i].isOccupied = 0;
    }
}


/**
 * @brief Uses linear probing to resolve hash collisions.
 *
 * @param key The key to be hashed.
 * @param i The current iteration (probe count).
 * @return The new index after applying linear probing.
 */
int linearProbing(int key, int i) {
    return (key + i) % TABLE_SIZE;
}

/**
 * @brief Uses quadratic probing to resolve hash collisions.
 *
 * @param key The key to be hashed.
 * @param i The current iteration (probe count).
 * @return The new index after applying quadratic probing.
 */
int quadraticProbing(int key, int i) {
    return (key + i * i) % TABLE_SIZE;
}

/**
 * @brief Uses double hashing to resolve hash collisions.
 *
 * @param key The key to be hashed.
 * @param i The current iteration (probe count).
 * @return The new index after applying double hashing.
 */
int doubleHashing(int key, int i) {
    int h1 = key % TABLE_SIZE;
    int h2 = 1 + (key % (TABLE_SIZE - 1));
    return (h1 + i * h2) % TABLE_SIZE;
}

/**
 * @brief Uses linear quotient to resolve hash collisions.
 *
 * @param key The key to be hashed.
 * @param i The current iteration (probe count).
 * @return The new index after applying linear quotient.
 */
int linearQuotient(int key, int i) {
    return (key + i * 7) % TABLE_SIZE;
}

/**
 * @brief Searches for a key using progressive overflow.
 *
 * @param key The key to be searched.
 * @return The index of the key in the overflow area, or -1 if not found.
 */

#include <stdbool.h>

bool progressiveOverflowSearch(int key) {
    for (int i = 0; i < OVERFLOW_SIZE; i++) {
        if (overflowArea[i].isOccupied && overflowArea[i].key == key) {return true;}
    }
    return false; // Anahtar bulunamadı
}



/**
 * @brief Searches for a key using bucket searching.
 *
 * @param key The key to be searched.
 * @return The index of the bucket where the key is located, or -1 if not found.
 */


bool useOfBucketsSearch(int key) {
    int index = hashFunction(key);
    for (int i = 0; i < hashTableBuckets[index].productCount; i++) {if (hashTableBuckets[index].products[i].vendorId == key) {return true; }}
    return false; // Anahtar bulunamadı
}



/**
 * @brief Searches for a key using Brent's method.
 *
 * @param key The key to be searched.
 * @return The index of the key in the hash table, or -1 if not found.
 */
int brentsMethodSearch(int key) {
    int index = hashFunction(key);
    int i = 0;
    while (hashTable[index].isOccupied) {
        if (hashTable[index].key == key) {
            return index;
        }
        int newIndex = linearProbing(key, i);
        if (!hashTable[newIndex].isOccupied) {
            return -1;
        }
        i++;
        if (i >= TABLE_SIZE) {
            break;
        }
    }
    return -1;
}


/**
 * @brief Selects a product from the list of available products.
 *
 * @param selectedProductName The name of the selected product (output parameter).
 * @return true if the product is successfully selected, false otherwise.
 *
 * @details The function lists all available products and allows the user to select one by name. It searches for the selected product in the binary file.
 */
bool selectProduct(char* selectedProductName) {
    FILE* productFile;
    Product product;
    int productCount = 0;

    productFile = fopen("products.bin", "rb");
    if (productFile == NULL) {printf("Error opening product file.\n");return 1;
    }

    printf("\n--- Available Products ---\n");
    while (fread(&product, sizeof(Product), 1, productFile)) {printf("Name: %s, Price: %.2f, Quantity: %d, Season: %s, Vendor ID: %d\n",product.productName, product.price, product.quantity, product.season, product.vendorId);productCount++;}

    fclose(productFile);

    if (productCount == 0) {
        printf("No products available.\n");
        return 1;
    }


    printf("Enter the Product Name to select: ");
    scanf(" %[^\n]s", selectedProductName);

    // We search the file again to check if the product has been selected
    productFile = fopen("products.bin", "rb");
    if (productFile == NULL) {
        printf("Error opening product file.\n");
        return 1;
    }

    bool found = false;
    while (fread(&product, sizeof(Product), 1, productFile)) {
        if (strcmp(product.productName, selectedProductName) == 0) {
            printf("Selected Product: %s, Price: %.2f\n", product.productName, product.price);
            found = true;
            break;
        }
    }

    fclose(productFile);

    if (!found) {
        printf("Product with Name '%s' not found.\n", selectedProductName);
        return 1;
    }

    return true;
}

/**
 * @brief Creates a max-heap in a subtree.
 *
 * This function creates a max-heap structure starting from the specified root node.
 *
 * @param arr Array of products.
 * @param n Number of elements in the array.
 * @param i Index of the root node where max-heap will be created.
 */
bool heapify(Product arr[], int n, int i) {
    int largest = i; // We initialize the largest element as root
    int left = 2 * i + 1; // Left child
    int right = 2 * i + 2; // Right child

    // Check if the left child is bigger than the root
    if (left < n && arr[left].price > arr[largest].price)
        largest = left;

    // Check if the right child is bigger than the root
    if (right < n && arr[right].price > arr[largest].price)
        largest = right;

    // If the largest element is not a root
    if (largest != i) {Product temp = arr[i]; arr[i] = arr[largest]; arr[largest] = temp; heapify(arr, n, largest);}
    return true;
}


/**
 * @brief Performs heap sort algorithm.
 *
 * This function sorts the given array by creating a max-heap and applying heap sort.
 *
 * @param arr Array of products to be sorted.
 * @param n Number of elements in the array.
 */
void heapSort(Product arr[], int n) {
    // Create max-heap for array
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Pull elements from the heap one by one
    for (int i = n - 1; i >= 0; i--) {
        Product temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Apply heapify for the remaining tree
        heapify(arr, i, 0);
    }
}


/**
 * @brief Compares prices of products with a given name.
 *
 * This function reads products from a binary file, filters those that match the given product name,
 * and sorts them by price using heap sort. It then prints the sorted list of products and their prices.
 *
 * @param productName Name of the product to compare prices.
 * @return True if products are found and compared, false otherwise.
 */
bool comparePricesByName(const char* productName) {
    FILE* productFile;
    Product products[100];
    int productCount = 0;
    bool found = false;

    productFile = fopen("products.bin", "rb");
    if (productFile == NULL) {printf("Error opening product file.\n");getchar();return 1;}

    // Read products from the file and add the ones that match the given name to the products array
    while (fread(&products[productCount], sizeof(Product), 1, productFile)) {if (strcmp(products[productCount].productName, productName) == 0) {productCount++;found = true;}}

    fclose(productFile);

    if (!found) {
        printf("No prices found for Product Name '%s'.\n", productName);
        getchar();
        return 1;
    }

    // Sort products by price (using heap sort)
    heapSort(products, productCount);

    // Sıralanmış ürünleri yazdır
    printf("\n--- Price Comparison for Product Name '%s' (Sorted by Price) ---\n", productName);
    for (int i = 0; i < productCount; i++) {
        printf("Vendor ID: %d, Price: %.2f\n", products[i].vendorId, products[i].price);
    }

    printf("\nLowest Price: %.2f\n", products[0].price);
    printf("Highest Price: %.2f\n", products[productCount - 1].price);
    getchar();
    return true;
}

/**
 * @brief Creates a new B+ Tree node.
 *
 * This function creates a new B+ Tree node, initializes it as a leaf or internal node,
 * and sets the initial values for its keys and children.
 *
 * @param isLeaf Boolean value indicating if the node is a leaf.
 * @return Pointer to the newly created B+ Tree node.
 */
BPlusTreeNode* createNode(bool isLeaf) {
    BPlusTreeNode* newNode = (BPlusTreeNode*)malloc(sizeof(BPlusTreeNode));
    newNode->isLeaf = isLeaf;
    newNode->keyCount = 0;
    newNode->next = NULL;
    for (int i = 0; i < MAX_KEYS + 1; i++) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

/**
 * @brief Inserts a key into the B+ Tree.
 *
 * This function inserts a given key into the B+ Tree, handling the splitting of nodes
 * if the maximum number of keys is exceeded.
 *
 * @param root Pointer to the root of the B+ Tree.
 * @param key Key to be inserted.
 * @return Pointer to the root of the updated B+ Tree.
 */
BPlusTreeNode* insert(BPlusTreeNode* root, int key) {
    if (root == NULL) {
        root = createNode(true);
        root->keys[0] = key;
        root->keyCount = 1;
        return root;
    }

    BPlusTreeNode* current = root;
    BPlusTreeNode* parent = NULL;
    while (!current->isLeaf) {
        parent = current;
        for (int i = 0; i < current->keyCount; i++) {
            if (key < current->keys[i]) {
                current = current->children[i];
                break;
            }
            if (i == current->keyCount - 1) {
                current = current->children[i + 1];
                break;
            }
        }
    }

    // Leaf reached, add the key
    int i = current->keyCount - 1;
    while (i >= 0 && current->keys[i] > key) {
        current->keys[i + 1] = current->keys[i];
        i--;
    }
    current->keys[i + 1] = key;
    current->keyCount++;

    // Division if the sheet is full
    if (current->keyCount == MAX_KEYS) {
        BPlusTreeNode* newLeaf = createNode(true);
        int mid = (MAX_KEYS + 1) / 2;
        current->keyCount = mid;
        for (int j = mid; j < MAX_KEYS; j++) {
            newLeaf->keys[j - mid] = current->keys[j];
        }
        newLeaf->keyCount = MAX_KEYS - mid;
        newLeaf->next = current->next;
        current->next = newLeaf;

        // Add new key to parent
        if (parent == NULL) {
            parent = createNode(false);
            parent->keys[0] = newLeaf->keys[0];
            parent->children[0] = current;
            parent->children[1] = newLeaf;
            parent->keyCount = 1;
            root = parent;
        }
        else {
            // Add new key to parent
            int newKey = newLeaf->keys[0];
            return insert(root, newKey);
        }
    }

    return root;
}

/**
 * @brief Searches for a specific key in the B+ Tree.
 *
 * This function searches for a given key in the B+ Tree and returns true if the key is found.
 *
 * @param root Pointer to the root of the B+ Tree.
 * @param key Key to be searched.
 * @return True if the key is found, false otherwise.
 */
bool search(BPlusTreeNode* root, int key) {
    BPlusTreeNode* current = root;
    while (current != NULL) {
        int i;
        for (i = 0; i < current->keyCount; i++) {
            if (key == current->keys[i]) {
                return true;
            }
            if (key < current->keys[i]) {
                break;
            }
        }
        current = current->isLeaf ? NULL : current->children[i];
    }
    return false;
}

/**
 * @brief Validates the day input.
 *
 * This function checks if the given day is a valid day of the week.
 *
 * @param day A string representing the day to validate.
 * @return true if the day is valid, false otherwise.
 */
bool validateDay(const char* day) {
    const char* validDays[] = {
        "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"
    };
    for (int i = 0; i < 7; ++i) {
        if (strcmp(day, validDays[i]) == 0) {
            return true;
        }
    }return false;}

/**
 * @brief Validates the working hours input.
 *
 * This function checks if the given working hours are in a valid format (HH:MM - HH:MM).
 * It also ensures that the start time is before the end time.
 *
 * @param hours A string representing the working hours to validate.
 * @return true if the hours are valid, false otherwise.
 */
bool validateWorkingHours(const char* hours) {
    int startHour, startMinute, endHour, endMinute;

    // Parse the hours string to extract time values.
    int result = sscanf(hours, "%d:%d - %d:%d", &startHour, &startMinute, &endHour, &endMinute);

    // Check if four values are extracted and if the hours are in a valid range.
    if (result != 4) return false;
    if (startHour < 0 || startHour > 23 || endHour < 0 || endHour > 23) return false;
    if (startMinute < 0 || startMinute > 59 || endMinute < 0 || endMinute > 59) return false;

    // Ensure that the start time is before the end time.
    if (startHour > endHour || (startHour == endHour && startMinute >= endMinute)) return false;

    return true;
}

/**
 * @brief Captures and stores market operational details such as hours and location.
 *
 * This function prompts the user to input market information such as the market ID, operating day,
 * hours of operation, and location. It checks for the existence of the given market ID against a vendor file
 * to ensure the market is registered. Valid input is then written to a binary file for persistent storage.
 * Each step includes validation to ensure that the data is correct before proceeding to the next step.
 * The function will clear the input buffer after necessary reads to handle any extraneous input.
 *
 * @return True if the market information is successfully added and saved; False if any errors occur during
 *         the file handling or input process.
 */
bool addMarketHoursAndLocation() {
    FILE* file = fopen("marketHours.bin", "ab");
    FILE* vendorFile = fopen("vendor.bin", "rb");
    if (file == NULL) {printf("Error opening market hours file.\n");return false;}
    
    if (vendorFile == NULL) { printf("Error opening vendor file.\n");fclose(file);return false;}

    MarketHours market;
    int found = 0;

    // Prompt user for Market ID
    printf("Enter Market ID: ");
    if (scanf("%d", &market.id) != 1) {printf("Invalid input. Please enter a valid numeric Market ID.\n");fclose(vendorFile);fclose(file);return false;}

    Vendor vendor;
    while (fread(&vendor, sizeof(Vendor), 1, vendorFile)) {
        if (vendor.id == market.id) {
            found = 1;
            break;
        }
    }
    fclose(vendorFile);

    // Check if Market ID exists in vendor file
    if (!found) {
        printf("Error: Invalid Market ID. Operation canceled.\n");
        fclose(file);
        return false;
    }

    // Get day of the week
    printf("Enter Day (e.g., monday): ");
    scanf("%19s", market.day);
    while (!validateDay(market.day)) {printf("Invalid day. Please enter a valid day (e.g., Monday): ");scanf("%19s", market.day);}

    // Get working hours
    printf("Enter Working Hours (e.g., 09:00 - 18:00): ");
    while (getchar() != '\n'); // Input buffer'ı temizle
    fgets(market.hours, sizeof(market.hours), stdin);
    market.hours[strcspn(market.hours, "\n")] = 0; // Remove newline character
    while (!validateWorkingHours(market.hours)) {printf("Invalid hours. Please enter valid hours (e.g., 09:00 - 18:00): ");fgets(market.hours, sizeof(market.hours), stdin);market.hours[strcspn(market.hours, "\n")] = 0;}

    // Get location
    printf("Enter Location: ");
    scanf("%49s", market.location);

    // Write the data to file
    fwrite(&market, sizeof(MarketHours), 1, file);
    fclose(file);

    printf("Market hours and location added successfully!\n");
    return true;
}


/**
 * @brief Updates existing market operational details such as hours and location.
 *
 * This function prompts the user to enter a market ID, then searches for it in the 'marketHours.bin' file.
 * If the market ID is found, the user can update the day of the week, operating hours, and location for that market.
 * The input is validated at each step to ensure it meets the expected format before it's written back into the file.
 * The function handles file operations with read and write permissions and ensures that the file pointer
 * is correctly managed to update the existing record without altering other entries.
 *
 * @return True if the market's operational details are successfully updated; False if the file can't be opened
 *         or the market ID is not found.
 */
bool updateMarketHoursAndLocation() {
    FILE* file = fopen("marketHours.bin", "rb+");
    if (file == NULL) {printf("Error opening market hours file.\n");return false;}

    int marketId;
    int found = 0;
    printf("Enter Market ID to update: ");
    while (scanf("%d", &marketId) != 1) {
        printf("Invalid input. Please enter a valid numeric Market ID: ");
        while (getchar() != '\n'); // Clear input buffer
    }
    while (scanf("%d", &marketId) != 1) {printf("Invalid input. Please enter a valid numeric Market ID: ");while (getchar() != '\n'); }
    MarketHours market;

    rewind(file); // Rewind to the start of the file
    while (fread(&market, sizeof(MarketHours), 1, file)) {
        if (market.id == marketId) {
            found = 1;

            // Prompt for new day
            printf("Enter new Day (e.g., Monday): ");
            scanf("%19s", market.day);
            while (!validateDay(market.day)) {printf("Invalid day. Please enter a valid day (e.g., Monday): ");scanf("%19s", market.day);}

            // Prompt for new working hours
            printf("Enter new Working Hours (e.g., 09:00 - 18:00): ");
            while (getchar() != '\n'); // Tamponu temizle
            fgets(market.hours, sizeof(market.hours), stdin);
            market.hours[strcspn(market.hours, "\n")] = 0;
            while (!validateWorkingHours(market.hours)) {printf("Invalid hours. Please enter valid hours (e.g., 09:00 - 18:00): ");fgets(market.hours, sizeof(market.hours), stdin);market.hours[strcspn(market.hours, "\n")] = 0;}

            // Prompt for new location
            printf("Enter new Location: ");
            scanf("%49s", market.location);

            // Write updated information to file
            fseek(file, -sizeof(MarketHours), SEEK_CUR);
            fwrite(&market, sizeof(MarketHours), 1, file);
            printf("Market hours and location updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Market ID %d not found.\n", marketId);
    }

    fclose(file); // Close the file
    return true;
}



/**
 * @brief XOR two pointers to obtain the mixed pointer.
 *
 * This function calculates the XOR of two given pointers to create a mixed pointer.
 * XOR linked lists make use of this operation to point to both previous and next nodes.
 *
 * @param a Pointer to the first node.
 * @param b Pointer to the second node.
 * @return Resulting pointer from XOR operation.
 */
MarketHoursNode* xor_function (MarketHoursNode* a, MarketHoursNode* b) {
    return (MarketHoursNode*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

/**
 * @brief Inserts a new node into the XOR linked list in sorted order by ID.
 *
 * This function inserts a new MarketHours node into the XOR linked list while maintaining
 * a sorted order based on the market ID. It ensures that the nodes are inserted in
 * ascending order by the ID value.
 *
 * @param head Pointer to the head of the XOR linked list.
 * @param data MarketHours data to be inserted into the new node.
 * @return Updated head pointer of the XOR linked list.
 */
MarketHoursNode* insertXORList(MarketHoursNode* head, MarketHours data) {
    MarketHoursNode* newNode = (MarketHoursNode*)malloc(sizeof(MarketHoursNode));
    newNode->data = data;
    newNode->xorPtr = NULL;

    if (head == NULL) {
        return newNode;  ///< Case when list is empty, return new node as head.
    }

    MarketHoursNode* prev = NULL;
    MarketHoursNode* curr = head;
    MarketHoursNode* next;

    while (curr != NULL) {
        next = xor_function(prev, curr->xorPtr);
        if (data.id < curr->data.id) {newNode->xorPtr = xor_function(prev, curr);if (prev != NULL) {prev->xorPtr = xor_function(xor_function(prev->xorPtr, curr), newNode);}curr->xorPtr = xor_function(newNode, next);if (prev == NULL) {head = newNode;   }return head;}
        prev = curr;
        curr = next;
    }

    // Insert new node at the end of the list
    prev->xorPtr = xor_function(xor_function(prev->xorPtr, NULL), newNode);
    newNode->xorPtr = prev;

    return head;
}

/**
 * @brief Traverses the XOR linked list and displays market hours grouped by ID.
 *
 * This function traverses through the XOR linked list and groups the market hours
 * entries based on their ID. It also provides user interaction to navigate between
 * different ID groups using 'n' (next), 'p' (previous), and 'q' (quit) options.
 * The screen is cleared before displaying each group to provide a cleaner interface.
 *
 * @param head Pointer to the head of the XOR linked list.
 */
void traverseXORListGroupedByID(MarketHoursNode* head) {
    MarketHoursNode* curr = head;
    MarketHoursNode* prev = NULL;
    MarketHoursNode* next;
    char choice;

    while (curr != NULL) {
        int currentID = curr->data.id;

        // Clear the screen (use "cls" for Windows, "clear" for Linux/Mac)
//#ifdef _WIN32
//        system("cls");
//#else
//        system("clear");
//#endif

        // Display all entries with the same ID
        printf("\n--- Market Hours and Locations (Use 'n' for next ID group, 'p' for previous ID group, 'q' to quit) ---\n");
        printf("\nID: %d\n", currentID);
        while (curr != NULL && curr->data.id == currentID) {
            printf("  Day: %s, Hours: %s, Location: %s\n",
                curr->data.day, curr->data.hours, curr->data.location);
            next = xor_function(prev, curr->xorPtr);
            prev = curr;
            curr = next;
        }

        // User interaction for next or previous group
        if (curr != NULL || prev != NULL) {
            printf("\nEnter your choice (n/p/q): ");
            scanf(" %c", &choice);

            if (choice == 'n') {
                // Continue to next group (already set in curr)
            }
            else if (choice == 'p') {while (prev != NULL && prev->data.id == currentID) {next = xor_function(prev->xorPtr, curr);curr = prev;prev = next;}

                // Now go further back to reach the start of the previous group
                if (prev != NULL) {
                    currentID = prev->data.id;
                    while (prev != NULL && prev->data.id == currentID) {
                        next = xor_function(prev->xorPtr, curr);
                        curr = prev;
                        prev = next;
                    }
                    // After the above loop, 'curr' will be at the start of the previous group
                }
                else {
                    printf("You have reached the beginning of the list.\n");
                    curr = head;  // Reset to the head
                    prev = NULL;
                }
            }
            else if (choice == 'q') {
                break;}
            else {
                printf("Invalid choice. Please enter 'n', 'p', or 'q'.\n");
            }
        }else {printf("You have reached the end of the list.\n");
        }
    }
}

/**
 * @brief Displays market hours and locations grouped by ID by reading from a binary file.
 *
 * This function reads MarketHours records from a binary file named "marketHours.bin",
 * inserts them into an XOR linked list, and then traverses the linked list to display
 * the market hours grouped by their ID.
 *
 * @return True if the operation was successful, otherwise false.
 */
bool displayMarketHoursAndLocations() {
    FILE* file = fopen("marketHours.bin", "rb");
    if (file == NULL) {printf("Error opening market hours file.\n");return false;}

    MarketHours market;
    MarketHoursNode* head = NULL;

    // Read all MarketHours from the file and insert into the XOR linked list
    while (fread(&market, sizeof(MarketHours), 1, file)) {
        head = insertXORList(head, market);
    }

    fclose(file);

    // Traverse and display the XOR linked list grouped by ID using BFS
    if (head == NULL) {printf("No market hours available.\n");return true;}

    printf("\n--- Market Hours and Locations (BFS Traversal) ---\n");
    std::queue<MarketHoursNode*> queue;
    MarketHoursNode* current = head;
    MarketHoursNode* prev = NULL;
    queue.push(current);

    // BFS Traversal
    while (!queue.empty()) {
        current = queue.front();
        queue.pop();

        // Display current node's information
        printf("\nMarket ID: %d\n", current->data.id);
        printf("  Day: %s, Hours: %s, Location: %s\n",
            current->data.day, current->data.hours, current->data.location);

        // Get the next node using XOR logic
        MarketHoursNode* next = xor_function(prev, current->xorPtr);

        if (next != NULL) {
            queue.push(next);
        }

        // Move to the next node
        prev = current;
    }

    return true;
}

/**
 * @brief Computes the Longest Prefix Suffix (LPS) array for the KMP string matching algorithm.
 *
 * This helper function computes the LPS array used in the Knuth-Morris-Pratt (KMP) pattern matching algorithm.
 * The LPS array is used to skip unnecessary character comparisons when searching for a pattern in a text.
 *
 * @param pattern The string pattern to be analyzed.
 * @param M Length of the pattern.
 * @param lps Array to store the computed LPS values.
 */

void computeLPSArray(const char* pattern, int M, int* lps) {
    int length = 0;
    lps[0] = 0; // lps[0] is always 0

    int i = 1;
    while (i < M) {
        if (pattern[i] == pattern[length]) {length++;lps[i] = length;i++;}
        else {
            if (length != 0) {length = lps[length - 1];}
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

/**
 * @brief Searches for a pattern in the given text using the Knuth-Morris-Pratt (KMP) algorithm.
 *
 * @param pattern The pattern to search for.
 * @param text The text to search within.
 * @return true if the pattern is found, false otherwise.
 */
bool KMPSearch(const char* pattern, const char* text) {
    int M = strlen(pattern);
    int N = strlen(text);

    int* lps = (int*)malloc(M * sizeof(int));
    computeLPSArray(pattern, M, lps);

    int i = 0;
    int j = 0;
    while (i < N) {
        if (pattern[j] == text[i]) {j++;i++;}

        if (j == M) {free(lps);return true;}
        else if (i < N && pattern[j] != text[i]) {
            if (j != 0) {j = lps[j - 1];}
            else {
                i++;
            }
        }
    }

    free(lps);
    return false; // Pattern not found
}

/**
 * @brief Lists vendors offering a user's favorite product by searching the product file.
 *
 * @return true if the function executes successfully, false otherwise.
 */
bool enterSearchProducts() {
    FILE* productFile;
    FILE* vendorFile;
    Product product;
    Vendor vendor;
    char favoriteProduct[100];
    bool found = false;

    // Get favorite product name from user
    printf("Enter the name of your favorite product to search for vendors: ");
    scanf(" %[^\n]s", favoriteProduct);

    // Open the product file
    productFile = fopen("products.bin", "rb");
    if (productFile == NULL) {printf("Error opening product file.\n");return 1;}

    // Open the vendor file
    vendorFile = fopen("vendor.bin", "rb");
    if (vendorFile == NULL) {printf("Error opening vendor file.\n");fclose(productFile);return 1;}

    printf("\n--- Vendors Offering '%s' ---\n", favoriteProduct);

    // Search with KMP by scanning the product file
    while (fread(&product, sizeof(Product), 1, productFile)) {if (KMPSearch(favoriteProduct, product.productName)) {rewind(vendorFile); while (fread(&vendor, sizeof(Vendor), 1, vendorFile)) {if (vendor.id == product.vendorId) {printf("Vendor: %s, ID: %d\n", vendor.name, vendor.id);found = true;break;}}}}

    if (!found) {
        printf("No vendors found offering '%s'.\n", favoriteProduct);
    }

    // Close the files
    fclose(productFile);
    fclose(vendorFile);

    printf("\nPress Enter to return to menu...");
    getchar();
    getchar(); // Again to clean the tampon

    return true;
}


/**
 * @brief Performs a Depth-First Search (DFS) on a graph of nodes to find a keyword.
 *
 * @param node The starting node for the DFS.
 * @param keyword The keyword to search for.
 * @param visited An array of nodes that have been visited.
 * @param visitedCount The number of nodes visited so far.
 * @return true if the keyword is found, false otherwise.
 */
bool DFS(Node* node, const char* keyword, Node** visited, int* visitedCount) {
    // Start a stack for DFS
    std::stack<Node*> stack;
    stack.push(node);

    while (!stack.empty()) {
        Node* currentNode = stack.top();
        stack.pop();

        // Skip if the node has been visited
        bool isVisited = false;
        for (int i = 0; i < *visitedCount; i++) {
            if (visited[i] == currentNode) {
                isVisited = true;
                break;
            }
        }
        if (isVisited) continue;

        // Mark node as visited
        visited[*visitedCount] = currentNode;
        (*visitedCount)++;

        // Return if the keyword is present in the node information
        if (strstr(currentNode->info, keyword) != NULL) {printf("Match found: %s\n", currentNode->info);return true;}

        // Add neighbor nodes to the stack
        for (int i = 0; i < currentNode->neighborCount; i++) {
            stack.push(currentNode->neighbors[i]);
        }
    }

    return false;
}


/**
 * @brief Searches for a keyword among products and vendors, using DFS and finding SCC.
 *
 * @return true if the function executes successfully, false otherwise.
 */
bool enterKeywords() {
    char keyword[100];
    printf("\nEnter a keyword to search: ");
    scanf("%s", keyword);

    // Read product and vendor information from file and create nodes
    FILE* productFile = fopen("products.bin", "rb");
    FILE* vendorFile = fopen("vendor.bin", "rb");

    if (productFile == NULL || vendorFile == NULL) {printf("Error opening product or vendor file.\n");return false;
    }

    Product product;
    Vendor vendor;

    // Create an array for all nodes (with a maximum of 100 nodes)
    Node* nodes[100];
    int nodeCount = 0;

    // Adding products as nodes
    while (fread(&product, sizeof(Product), 1, productFile) && nodeCount < 100) {Node* productNode = (Node*)malloc(sizeof(Node));productNode->info = (char*)malloc(200 * sizeof(char));snprintf(productNode->info, 200, "Product: %s, Season: %s, Vendor ID: %d, Price: %.2f, Quantity: %d",product.productName, product.season, product.vendorId, product.price, product.quantity);productNode->neighborCount = 0;productNode->neighbors = NULL;nodes[nodeCount++] = productNode;}

    // Adding vendors as nodes
    while (fread(&vendor, sizeof(Vendor), 1, vendorFile) && nodeCount < 100) {
        Node* vendorNode = (Node*)malloc(sizeof(Node));
        vendorNode->info = (char*)malloc(100 * sizeof(char));
        snprintf(vendorNode->info, 100, "Vendor: %s, ID: %d", vendor.name, vendor.id);
        vendorNode->neighborCount = 0;
        vendorNode->neighbors = NULL;
        nodes[nodeCount++] = vendorNode;
    }

    fclose(productFile);
    fclose(vendorFile);

    // Fill adjacency lists (neighbors)
    for (int i = 0; i < nodeCount; ++i) {
        for (int j = 0; j < nodeCount; ++j) {
            if (i != j) {
                // Example condition: keyword or vendor/product relation
                if (strstr(nodes[j]->info, nodes[i]->info) != NULL) {
                    nodes[i]->neighborCount++;
                    nodes[i]->neighbors = (Node**)realloc(nodes[i]->neighbors, nodes[i]->neighborCount * sizeof(Node*));
                    nodes[i]->neighbors[nodes[i]->neighborCount - 1] = nodes[j];
                }
            }
        }
    }

    // Search keyword with DFS
    Node* visited[100];
    int visitedCount = 0;
    bool found = false;

    for (int i = 0; i < nodeCount; ++i) {
        visitedCount = 0;
        if (DFS(nodes[i], keyword, visited, &visitedCount)) {found = true;
        }
    }

    if (!found) {
        printf("No matches found for keyword '%s'.\n", keyword);
    }

    // Running the SCC Algorithm
    printf("\nFinding Strongly Connected Components (SCC)...\n");
    findSCC(nodes, nodeCount);

    // Clean up dynamically created nodes
    for (int i = 0; i < nodeCount; ++i) {
        free(nodes[i]->info);
        free(nodes[i]->neighbors);
        free(nodes[i]);
    }

    printf("Press Enter to return to menu...");
    getchar();
    getchar();

    return true;
}


/**
 * @brief Finds the Strongly Connected Components (SCC) of a graph.
 *
 * @param nodes An array of nodes representing the graph.
 * @param nodeCount The number of nodes in the graph.
 */
void findSCC(Node* nodes[], int nodeCount) {
    int* ids = (int*)malloc(nodeCount * sizeof(int));
    int* low = (int*)malloc(nodeCount * sizeof(int));
    bool* onStack = (bool*)malloc(nodeCount * sizeof(bool));
    Node** stack = (Node**)malloc(nodeCount * sizeof(Node*));
    int stackTop = -1;
    int id = 0;

    for (int i = 0; i < nodeCount; ++i) {
        ids[i] = -1;  // -1 if node is not visited
        low[i] = 0;
        onStack[i] = false;
    }

    for (int i = 0; i < nodeCount; ++i) {
        if (ids[i] == -1) {  // Start DFS if not visited
            tarjanDFS(nodes, i, &id, ids, low, stack, &stackTop, onStack, nodeCount);
        }
    }

    free(ids);
    free(low);
    free(onStack);
    free(stack);
}


/**
 * @brief Performs a depth-first search (DFS) to find strongly connected components (SCCs) in a graph using Tarjan's algorithm.
 *
 * This function recursively explores nodes, manages discovery and low-link values,
 * and identifies SCCs by checking if the current node is a root node (i.e., discovery time is equal to low-link value).
 * The function maintains a stack to track active nodes in the current search path and uses it to
 * identify nodes in the same SCC when a root node is found.
 */

void tarjanDFS(Node* nodes[], int at, int* id, int* ids, int* low, Node** stack, int* stackTop, bool* onStack, int nodeCount) {
    ids[at] = low[at] = (*id)++;
    stack[++(*stackTop)] = nodes[at];
    onStack[at] = true;

    for (int i = 0; i < nodes[at]->neighborCount; ++i) {
        int neighborIndex = findNodeIndex(nodes, nodes[at]->neighbors[i], nodeCount); // Find your neighbor's index
        if (ids[neighborIndex] == -1) {  // If not visited
            tarjanDFS(nodes, neighborIndex, id, ids, low, stack, stackTop, onStack, nodeCount);
            low[at] = fmin(low[at], low[neighborIndex]);
        }
        else if (onStack[neighborIndex]) {  // If the neighbor is still in the stack
            low[at] = fmin(low[at], ids[neighborIndex]);
        }
    }

    // SCC found if the low connection value is equal to its own id
    if (low[at] == ids[at]) {
        printf("SCC: ");
        while (true) {
            Node* node = stack[(*stackTop)--];
            onStack[findNodeIndex(nodes, node, nodeCount)] = false;
            printf("%s ", node->info);
            if (node == nodes[at]) break;
        }
        printf("\n");
    }
}

/**
 * @brief Finds the index of a node within an array of node pointers.
 *
 * Given a node and an array of node pointers, this function searches for the node in the array and returns its index.
 * This is useful for locating the position of a node in the graph's node list based on its pointer, facilitating access
 * to its associated properties in parallel arrays.
 */
int findNodeIndex(Node* nodes[], Node* node, int nodeCount) {
    for (int i = 0; i < nodeCount; ++i) {
        if (nodes[i] == node) return i;}return -1;  // If not found
}
