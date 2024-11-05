#define _CRT_SECURE_NO_WARNINGS
#include "../header/market.h"
#include <stdexcept>
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <fstream>
#include <stdbool.h>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include <sstream>
#include <conio.h>
#include <time.h>
#include <ctype.h>
#include <stack>  // Yığın yapısını kullanmak için gerekli (DFS)
#include <stdint.h>
#include <float.h> 
#include <unordered_map>  //hash table 
#include <queue>          //hash table
#include <functional>     //hash table

#include <limits.h> // Tarjan algoritması için INT_MAX kullanımı
#define TABLE_SIZE 100
#define OVERFLOW_SIZE 20
#define BUCKET_SIZE 5
#define MAX_VENDORS 100
#define MAX_PRODUCTS 100
#define MAX_TREE_HT 100



#include "market.h"  // Bu satır her .cpp dosyasının başına eklenmeli

// Kullanıcının giriş yapıp yapmadığını tutan değişken
bool isAuthenticated = false;

HashTableEntry hashTable[TABLE_SIZE];
HashTableEntry overflowArea[OVERFLOW_SIZE];
Bucket hashTableBuckets[TABLE_SIZE];



void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int getInput()
{
    int choice;
    int result = scanf("%d", &choice);

    if (result != 1) {
        printf("Invalid choice! Please try again.\n");
        // Gecersiz girisi temizle
        while (fgetc(stdin) != '\n'); // Yeni satir karakterine kadar oku
        return getInput(); // Fonksiyonu yeniden cagir
    }

    return choice;
}


bool userAuthentication() {
    int choice;
    char username[50];
    char password[50];
    do
    {
        clearScreen();
        printf("\n--- User Authentication ---\n");
        printf("1. Login\n");
        printf("2. Register\n");
        printf("3. Guest Mode\n");
        printf("4. Exit\n");
        printf("Choose an option: ");
        choice = getInput();

        switch (choice) {
        case 1:
            if (loginUser())
            {
                mainMenu();
            };
            break;
        case 2:
            registerUser();
            isAuthenticated = true;
            break;
        case 3:
            mainMenu();
            break;
        case 4:
            printf("Exiting the program...\n");
            break;
        default:
            printf("Invalid option. Please try again.\n");
            getchar(); 
            break;
        }

    } while (choice != 4);
   
    return true;
}

int mainMenu() {
    int choice;

    do {
        // Ana menüyü yazdır
        clearScreen();
        printf("\n--- Main Menu ---\n");
        printf("1. Listing of Local Vendors\n");
        printf("2. Listing of Local Products\n");
        printf("3. Price Comparison\n");
        printf("4. Market Hours and Locations\n");
        printf("5. Search Products or Enter Keywords\n");
        printf("0. Exit\n");
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

    return 0;
}


int listingOfLocalVendors() {
    int choice;

    do {
        clearScreen();
        printf("\n--- Listing of Local Vendors and Products ---\n");
        printf("1. Add Vendor\n");
        printf("2. Update Vendor\n");
        printf("3. Delete Vendor\n");
        printf("4. List Vendors\n");
        printf("0. Return to Main Menu\n");
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

    return 0;
}


int listingOfLocalProducts() {
int choice;

do {
    clearScreen();
    printf("\n--- List All Products ---\n");
    printf("1. Add Product \n");
    printf("2. Update Product \n");
    printf("3. Delete Product \n");
    printf("4. Listing of Local Products\n");
    printf("0. Return to Main Menu\n");
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

return 0;
}


int priceComparison() {
    int choice;
    char selectedProductName[100] = "";  // Seçilen ürün adını burada tutacağız

    do {
        clearScreen();
        printf("\n--- Price Comparison ---\n");
        printf("1. Select Product\n");
        printf("2. Compare Prices\n");
        printf("0. Return to Main Menu\n");
        printf("Choose an option: ");
        choice = getInput();

        switch (choice) {
        case 1:
            // selectProduct fonksiyonuna selectedProductName değişkenini geçiriyoruz
            if (selectProduct(selectedProductName) == 0) {  // Ürün seçildiyse
                printf("Product '%s' selected.\n", selectedProductName);
            }
            else {
                printf("Product selection failed.\n");
            }
            break;
        case 2:
            if (strlen(selectedProductName) > 0) {  // Bir ürün seçildiyse karşılaştırma yap
                comparePricesByName(selectedProductName);
            }
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
        getchar();  // Kullanıcıdan Enter tuşuna basmasını bekle
        getchar();  // Tamponu temizlemek için

    } while (choice != 0);

    return 0;
}

// Market Hours and Locations menu
int marketHoursAndLocations() {
    int choice;

    do {
        printf("\n--- Market Hours and Locations ---\n");
        printf("1. Add Working Hours and Location\n");
        printf("2. Update Market Hours and Location\n");
        printf("3. View Market Hours and Locations\n");
        printf("0. Return to Main Menu\n");
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

    return 0;
}



int searchProductsOrEnterKeyword() {
    int choice;

    do {
        clearScreen();
        printf("\n--- Search Products or Enter Keyword ---\n");
        printf("1. Enter Search Products\n");
        printf("2. Enter Keywords\n");
        printf("0. Return to Main Menu\n");
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

    return 0;
}


// KMP algoritması için LPS (Longest Prefix Suffix) dizisini hesaplayan yardımcı fonksiyon
void computeLPSArray(const char* pattern, int M, int* lps) {
    int length = 0;
    lps[0] = 0; // lps[0] her zaman 0'dır

    int i = 1;
    while (i < M) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        }
        else {
            if (length != 0) {
                length = lps[length - 1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

// KMP algoritmasını kullanarak metin içinde deseni arayan fonksiyon
bool KMPSearch(const char* pattern, const char* text) {
    int M = strlen(pattern);
    int N = strlen(text);

    int* lps = (int*)malloc(M * sizeof(int));
    computeLPSArray(pattern, M, lps);

    int i = 0;
    int j = 0;
    while (i < N) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == M) {
            free(lps);
            return true; // Desen bulundu
        }
        else if (i < N && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1];
            }
            else {
                i++;
            }
        }
    }

    free(lps);
    return false; // Desen bulunamadı
}

// Favori ürünü ve ilgili satıcıları listeleyen fonksiyon
int enterSearchProducts() {
    FILE* productFile;
    FILE* vendorFile;
    Product product;
    Vendor vendor;
    char favoriteProduct[100];
    bool found = false;

    // Kullanıcıdan favori ürün adını al
    printf("Enter the name of your favorite product to search for vendors: ");
    scanf(" %[^\n]s", favoriteProduct);

    // Ürün dosyasını aç
    productFile = fopen("products.bin", "rb");
    if (productFile == NULL) {
        printf("Error opening product file.\n");
        return 1;
    }

    // Satıcı dosyasını aç
    vendorFile = fopen("vendor.bin", "rb");
    if (vendorFile == NULL) {
        printf("Error opening vendor file.\n");
        fclose(productFile);
        return 1;
    }

    printf("\n--- Vendors Offering '%s' ---\n", favoriteProduct);

    // Ürün dosyasını tarayarak KMP ile arama yap
    while (fread(&product, sizeof(Product), 1, productFile)) {
        if (KMPSearch(favoriteProduct, product.productName)) {
            // Eşleşen ürün bulundu, satıcıyı göster
            rewind(vendorFile); // Satıcı dosyasını baştan okumak için geri al
            while (fread(&vendor, sizeof(Vendor), 1, vendorFile)) {
                if (vendor.id == product.vendorId) {
                    printf("Vendor: %s, ID: %d\n", vendor.name, vendor.id);
                    found = true;
                    break;
                }
            }
        }
    }

    if (!found) {
        printf("No vendors found offering '%s'.\n", favoriteProduct);
    }

    // Dosyaları kapat
    fclose(productFile);
    fclose(vendorFile);

    printf("\nPress Enter to return to menu...");
    getchar();
    getchar(); // Tamponu temizlemek için tekrar

    return 0;
}


bool DFS(Node* node, const char* keyword, Node** visited, int* visitedCount) {
    // DFS için bir yığın başlat
    std::stack<Node*> stack;
    stack.push(node);

    while (!stack.empty()) {
        Node* currentNode = stack.top();
        stack.pop();

        // Eğer düğüm ziyaret edilmişse atla
        bool isVisited = false;
        for (int i = 0; i < *visitedCount; i++) {
            if (visited[i] == currentNode) {
                isVisited = true;
                break;
            }
        }
        if (isVisited) continue;

        // Düğümü ziyaret edilmiş olarak işaretle
        visited[*visitedCount] = currentNode;
        (*visitedCount)++;

        // Anahtar kelime, düğüm bilgisinde varsa döndür
        if (strstr(currentNode->info, keyword) != NULL) {
            printf("Match found: %s\n", currentNode->info);
            return true;
        }

        // Komşu düğümleri yığına ekle
        for (int i = 0; i < currentNode->neighborCount; i++) {
            stack.push(currentNode->neighbors[i]);
        }
    }

    return false;
}

int enterKeywords() {
    char keyword[100];
    printf("\nEnter a keyword to search: ");
    scanf("%s", keyword);

    // Ürün ve satıcı bilgilerini dosyadan okuyup düğümler oluşturma
    FILE* productFile = fopen("products.bin", "rb");
    FILE* vendorFile = fopen("vendor.bin", "rb");

    if (productFile == NULL || vendorFile == NULL) {
        printf("Error opening product or vendor file.\n");
        return 1;
    }

    Product product;
    Vendor vendor;

    // Tüm düğümler için bir dizi oluştur (maksimum 100 düğüm kabulüyle)
    Node* nodes[100];
    int nodeCount = 0;

    // Ürünleri düğüm olarak ekleme
    while (fread(&product, sizeof(Product), 1, productFile) && nodeCount < 100) {
        Node* productNode = (Node*)malloc(sizeof(Node));
        productNode->info = (char*)malloc(200 * sizeof(char));
        snprintf(productNode->info, 200, "Product: %s, Season: %s, Vendor ID: %d, Price: %.2f, Quantity: %d",
            product.productName, product.season, product.vendorId, product.price, product.quantity);
        productNode->neighborCount = 0;
        productNode->neighbors = NULL;
        nodes[nodeCount++] = productNode;
    }

    // Satıcıları düğüm olarak ekleme
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

    // DFS ile anahtar kelimeyi arama
    Node* visited[100];  // Ziyaret edilen düğümleri izlemek için
    int visitedCount = 0;
    bool found = false;

    for (int i = 0; i < nodeCount; ++i) {
        visitedCount = 0;  // Her düğüm için ziyaret dizisini sıfırla
        if (DFS(nodes[i], keyword, visited, &visitedCount)) {
            found = true;
        }
    }

    if (!found) {
        printf("No matches found for keyword '%s'.\n", keyword);
    }
    // SCC Algoritmasını çalıştırma
   // SCC, Tarjan's veya Kosaraju'nun algoritmalarından biri kullanılarak bulunabilir
    printf("\nFinding Strongly Connected Components (SCC)...\n");
    findSCC(nodes, nodeCount);

    // Dinamik olarak oluşturulan düğümleri temizleme
    for (int i = 0; i < nodeCount; ++i) {
        free(nodes[i]->info);
        free(nodes[i]->neighbors);
        free(nodes[i]);
    }

    printf("Press Enter to return to menu...");
    getchar();
    getchar();  // Tamponu temizlemek için tekrar

    return 0;
}
void findSCC(Node* nodes[], int nodeCount) {
    // Bu kısımda Kosaraju veya Tarjan algoritmasını ekleyerek SCC bulabilirsiniz.
    // Örneğin: Tarjan's Algorithm
    // - Düğüm için discovery time, low value tutma ve stack kullanarak SCC bulunur.

    // Pseudo code placeholder for SCC:
    // - Tüm düğümler için discovery zamanını ve low value'yi takip et
    // - Stack kullanarak, SCC'leri tespit et ve ekrana yazdır
    // Bu kısımda detaylı bir SCC implementasyonu eklenmeli.
}

bool loginUserFromHuffFile(const char* username, const char* password) {
    FILE* file = fopen("users.huff", "rb");
    if (file == NULL) {
        perror("Error opening file");
        return false;
    }

    char fileUsername[100];
    char filePassword[100];
    size_t usernameLength, passwordLength;

    while (fread(&usernameLength, sizeof(size_t), 1, file) == 1) {
        if (usernameLength >= sizeof(fileUsername)) {
            printf("Username length too long, possible data corruption.\n");
            fclose(file);
            return false;
        }

        if (fread(fileUsername, sizeof(char), usernameLength, file) != usernameLength) {
            printf("Error reading username from file.\n");
            fclose(file);
            return false;
        }
        fileUsername[usernameLength] = '\0';  // Null karakter ekle

        if (fread(&passwordLength, sizeof(size_t), 1, file) != 1) {
            printf("Error reading password length from file.\n");
            fclose(file);
            return false;
        }

        if (passwordLength >= sizeof(filePassword)) {
            printf("Password length too long, possible data corruption.\n");
            fclose(file);
            return false;
        }

        if (fread(filePassword, sizeof(char), passwordLength, file) != passwordLength) {
            printf("Error reading password from file.\n");
            fclose(file);
            return false;
        }
        filePassword[passwordLength] = '\0';  // Null karakter ekle

        if (strcmp(username, fileUsername) == 0 && strcmp(password, filePassword) == 0) {
            fclose(file);
            return true;
        }
    }

    fclose(file);
    return false;
}



bool loginUser() {
    clearScreen();
    char username[50], password[50];
    int found = 0;

    // Kullanıcıdan giriş bilgileri alınıyor
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    // .huff dosyasını kullanarak kullanıcı bilgilerini kontrol et
    if (loginUserFromHuffFile(username, password)) {
        printf("Login successful. Welcome! %s.\n", username);
        found = 1;
    }
    else {
        printf("Incorrect username or password.\n");
        return false;
    }

    return found == 1;
}



bool saveUserToHuffFile(const char* username, const char* password) {
    FILE* file = fopen("users.huff", "ab");
    if (file == NULL) {
        perror("Error opening file");
        return false;
    }

    // Kullanıcı adını ve şifreyi binary formatta kaydetme
    size_t usernameLength = strlen(username);
    size_t passwordLength = strlen(password);

    fwrite(&usernameLength, sizeof(size_t), 1, file);
    fwrite(username, sizeof(char), usernameLength, file);
    fwrite(&passwordLength, sizeof(size_t), 1, file);
    fwrite(password, sizeof(char), passwordLength, file);

    fclose(file);
    return true;
}


    bool registerUser()
    {
        clearScreen();
        FILE* file;
        User user;

        // Kullanıcıdan bilgiler alınıyor
        printf("Username: ");
        scanf("%s", user.username);
        printf("Password: ");
        scanf("%s", user.password);

        // Kullanıcı bilgileri binary formatta dosyaya yazılıyor
        file = fopen("users.bin", "ab"); // "ab" ile dosyaya ekleme modunda açıyoruz
        if (file == NULL) {
            printf("The file is not opened.\n");
            exit(1);
        }
        fwrite(&user, sizeof(User), 1, file);
        fclose(file);

        // Kullanıcıyı .huff dosyasına kaydetme
        saveUserToHuffFile(user.username, user.password);

        printf("Register is successful!\n");
        getchar();
        return true;
    }

// Min-Heap oluşturma
struct MinHeap* createMinHeap(unsigned capacity) {
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0;
    minHeap->capacity = capacity;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));
    return minHeap;
}

// Min-Heap içindeki iki düğümü değiştirme
void swapMinHeapNode(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* t = *a;
    *a = *b;
    *b = t;
}

// Min-Heapify işlemi
void minHeapify(struct MinHeap* minHeap, int idx) {
    int smallest = idx;
    int left = 2 * idx + 1;
    int right = 2 * idx + 2;

    if (left < minHeap->size && minHeap->array[left]->freq < minHeap->array[smallest]->freq) {
        smallest = left;
    }

    if (right < minHeap->size && minHeap->array[right]->freq < minHeap->array[smallest]->freq) {
        smallest = right;
    }

    if (smallest != idx) {
        swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);
        minHeapify(minHeap, smallest);
    }
}

// Min-Heap'ten minimum değeri çıkarma
struct MinHeapNode* extractMin(struct MinHeap* minHeap) {
    struct MinHeapNode* temp = minHeap->array[0];
    minHeap->array[0] = minHeap->array[minHeap->size - 1];
    --minHeap->size;
    minHeapify(minHeap, 0);
    return temp;
}

// Yeni bir düğüm ekleme
void insertMinHeap(struct MinHeap* minHeap, struct MinHeapNode* minHeapNode) {
    ++minHeap->size;
    int i = minHeap->size - 1;

    while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {
        minHeap->array[i] = minHeap->array[(i - 1) / 2];
        i = (i - 1) / 2;
    }

    minHeap->array[i] = minHeapNode;
}

// Min-Heap oluşturma
void buildMinHeap(struct MinHeap* minHeap) {
    int n = minHeap->size - 1;
    for (int i = (n - 1) / 2; i >= 0; --i) {
        minHeapify(minHeap, i);
    }
}

// Karakterlerin frekansını sayarak Min-Heap oluşturma
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size) {
    struct MinHeap* minHeap = createMinHeap(size);

    for (int i = 0; i < size; ++i) {
        minHeap->array[i] = newNode(data[i], freq[i]);
    }

    minHeap->size = size;
    buildMinHeap(minHeap);

    return minHeap;
}

// Huffman ağacı oluşturma
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size) {
    struct MinHeapNode* left, * right, * top;

    struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

    while (minHeap->size != 1) {
        left = extractMin(minHeap);
        right = extractMin(minHeap);

        top = newNode('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        insertMinHeap(minHeap, top);
    }

    return extractMin(minHeap);
}

// Huffman kodlarını oluşturma
void printCodes(struct MinHeapNode* root, int arr[], int top) {
    if (root->left) {
        arr[top] = 0;
        printCodes(root->left, arr, top + 1);
    }

    if (root->right) {
        arr[top] = 1;
        printCodes(root->right, arr, top + 1);
    }

    if (!root->left && !root->right) {
        printf("%c: ", root->data);
        for (int i = 0; i < top; ++i) {
            printf("%d", arr[i]);
        }
        printf("\n");
    }
}

// Huffman kodlama işlemi
void HuffmanCodes(char data[], int freq[], int size) {
    struct MinHeapNode* root = buildHuffmanTree(data, freq, size);
    int arr[MAX_TREE_HT], top = 0;
    printCodes(root, arr, top);
}

struct MinHeapNode* newNode(char data, unsigned freq) {
    struct MinHeapNode* temp = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    temp->left = temp->right = NULL;
    temp->data = data;
    temp->freq = freq;
    return temp;
}

// Satıcı ekleme
int addVendor() {
    FILE* file;
    Vendor vendor;

    file = fopen("vendor.bin", "ab"); // Dosyayı ekleme modunda açıyoruz
    if (file == NULL) {
        printf("Error opening vendor file.\n");
        return 1;
    }

    printf("\n--- List of Vendors ---\n");
    int vendorCount = 0; // Listelediğimiz satıcı sayısını takip etmek için

    // Rastgele 6 haneli ID oluşturma
    srand(time(NULL));  // Rastgele sayı üreteciyi başlat
    vendor.id = (rand() % 900000) + 100000;  // 100000 ile 999999 arasında rastgele bir sayı üret

    printf("Assigned Vendor ID: %d\n", vendor.id);  // Atanan ID'yi gösteriyoruz

    // Kullanıcıdan sadece isim alınıyor
    printf("Enter Vendor Name: ");
    scanf("%49s", vendor.name);  // %49s kullanarak taşmaları önlüyoruz
    while (getchar() != '\n');  // Tamponu temizle

    // Dosyaya yazma işlemi (ID ve isim)
    fwrite(&vendor, sizeof(Vendor), 1, file);
    fclose(file);

    printf("Vendor added successfully!\n");

    // Devam etmek için kullanıcıdan bir tuşa basmasını bekle
    printf("Press Enter to continue...");
    getchar();  // Devam etmek için kullanıcıdan bir tuşa basmasını bekle

    return 0;
}


// Satıcı güncelleme
int updateVendor() {
    FILE* file;
    Vendor vendor;
    int id, found = 0;
    file = fopen("vendor.bin", "rb+"); // Dosyayı okuma ve yazma modunda açıyoruz

    if (file == NULL) {
        printf("Error opening vendor file.\n");
        return 1;
    }

    printf("Enter Vendor ID to update: ");
    scanf("%d", &id);
    // Tampondaki fazlalıkları temizlemek için:
    while (getchar() != '\n');  // Fazladan yeni satır karakterini temizle


    while (fread(&vendor, sizeof(Vendor), 1, file)) {
        if (vendor.id == id) {
            printf("Enter new Vendor Name: ");
            scanf("%s", vendor.name);

            fseek(file, -sizeof(Vendor), SEEK_CUR); // İmleci geri al
            fwrite(&vendor, sizeof(Vendor), 1, file);
            found = 1;
            printf("Vendor updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Vendor with ID %d not found.\n", id);
    }

    // Tampon temizleme ve devam etmek için tuşa basmayı bekleme
    while (getchar() != '\n');  // Fazladan yeni satır karakterini temizle
    printf("Press Enter to continue...");
    getchar();  // Kullanıcıdan Enter tuşuna basmasını bekle

    return 0;
}

// Satıcı silme
int deleteVendor() {
    FILE* file, * tempFile;
    Vendor vendor;
    int id, found = 0;

    file = fopen("vendor.bin", "rb");
    tempFile = fopen("temp.bin", "wb");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file.\n");
        return 1;
    }

    printf("Enter Vendor ID to delete: ");
    scanf("%d", &id);

    while (fread(&vendor, sizeof(Vendor), 1, file)) {
        if (vendor.id != id) {
            fwrite(&vendor, sizeof(Vendor), 1, tempFile);
        }
        else {
            found = 1;
        }
    }

    fclose(file);
    fclose(tempFile);

    remove("vendor.bin");
    rename("temp.bin", "vendor.bin");

    if (found) {
        printf("Vendor deleted successfully!\n");
    }
    else {
        printf("Vendor with ID %d not found.\n", id);
    }

    getchar(); // Devam etmek için tuşa basma
    return 0;
}

// Satıcıları ID'lerine göre sıralamak için hash tablosu ve min-heap kullanarak listeleme


int listVendors() {
    FILE* file;
    Vendor vendor;
    file = fopen("vendor.bin", "rb"); // Dosyayı okuma modunda açıyoruz

    if (file == NULL) {
        printf("Error opening vendor file.\n");
        return 1;
    }

    // Satıcı ID'lerini min-heap'te saklamak için priority_queue
    auto cmp = [](int left, int right) { return left > right; };
    std::priority_queue<int, std::vector<int>, decltype(cmp)> vendorHeap(cmp);
    std::vector<Vendor> vendorList;

    // Satıcı dosyasını okuma ve listeye ekleme
    while (fread(&vendor, sizeof(Vendor), 1, file)) {
        vendorList.push_back(vendor);
        vendorHeap.push(vendor.id);
    }

    fclose(file);

    // Sıralanmış ID'lere göre satıcıları yazdırma
    printf("\n--- List of Vendors Sorted by ID ---\n");
    while (!vendorHeap.empty()) {
        int id = vendorHeap.top();
        vendorHeap.pop();
        for (const Vendor& v : vendorList) {
            if (v.id == id) {
                printf("ID: %d, Name: %s \n", v.id, v.name);
                break;
            }
        }
    }

    while (getchar() != '\n');  // Fazladan satır sonunu temizle
    printf("Press Enter to return to menu...");
    getchar();  // Devam etmek için kullanıcıdan bir tuşa basmasını bekle
    return 0;
}



int addProduct() {
    FILE* productFile;
    FILE* vendorFile;
    Product product;
    Vendor vendor;
    int found = 0;

    productFile = fopen("products.bin", "ab"); // Ürün dosyasını ekleme modunda açıyoruz
    if (productFile == NULL) {
        printf("Error opening product file.\n");
        return 1;
    }

    vendorFile = fopen("vendor.bin", "rb"); // Satıcı dosyasını okuma modunda açıyoruz
    if (vendorFile == NULL) {
        printf("Error opening vendor file.\n");
        fclose(productFile);
        return 1;
    }

    // Satıcı ID'yi kullanıcıdan alıyoruz
    printf("Enter Vendor ID for the product: ");
    scanf("%d", &product.vendorId);

    // Satıcı ID'sini kontrol ediyoruz
    while (fread(&vendor, sizeof(Vendor), 1, vendorFile)) {
        if (vendor.id == product.vendorId) {
            found = 1;  // Satıcı bulundu
            break;
        }
    }

    fclose(vendorFile);  // Satıcı dosyasını kapatıyoruz

    if (!found) {
        printf("Error: Vendor with ID %d does not exist.\n", product.vendorId);
        fclose(productFile);
        printf("Press Enter to continue...");
        getchar();  // Devam etmek için kullanıcıdan bir tuşa basmasını bekle
        getchar();  // Bir kez daha getchar() çünkü tamponu temizliyoruz
        return 1;  // Ürün eklenmeden fonksiyondan çık
    }

    // Eğer satıcı ID mevcutsa, ürün ekleme işlemi devam eder
    printf("Enter Product Name: ");
    scanf("%s", product.productName);

    printf("Enter Product Price: ");
    scanf("%f", &product.price);

    printf("Enter Product Quantity: ");
    scanf("%d", &product.quantity);

    printf("Enter Product Season: ");
    scanf("%s", product.season);

    // Ürün bilgilerini dosyaya yazıyoruz
    fwrite(&product, sizeof(Product), 1, productFile);
    fclose(productFile);

    printf("Product added successfully!\n");

    // Devam etmek için kullanıcıdan bir tuşa basmasını bekle
    printf("Press Enter to continue...");
    getchar();
    getchar();  // Tamponu temizlemek ve devam etmek için

    return 0;
}

int updateProduct() {
    FILE* productFile, * tempFile;
    Product product;
    char productName[50];
    int found = 0;

    productFile = fopen("products.bin", "rb"); // Orijinal dosyayı okuma modunda aç
    if (productFile == NULL) {
        printf("Error opening product file.\n");
        return 1;
    }

    tempFile = fopen("temp.bin", "wb"); // Geçici dosyayı yazma modunda aç
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(productFile);
        return 1;
    }

    // Güncellemek istediğiniz ürünün adını alıyoruz
    printf("Enter Product Name to update: ");
    scanf("%s", productName);

    // Tüm ürünleri dosyadan okuyup, adı kontrol ediyoruz
    while (fread(&product, sizeof(Product), 1, productFile)) {
        if (strcmp(product.productName, productName) == 0) {
            found = 1;
            // Yeni ürün bilgilerini alıyoruz
            printf("Enter new Product Name: ");
            scanf("%s", product.productName);
            printf("Enter new Product Price: ");
            scanf("%f", &product.price);
            printf("Enter new Product Quantity: ");
            scanf("%d", &product.quantity);
            printf("Enter new Product Season: ");
            scanf("%s", product.season);
        }
        fwrite(&product, sizeof(Product), 1, tempFile); // Ürünü geçici dosyaya yaz
    }

    fclose(productFile);
    fclose(tempFile);

    if (!found) {
        printf("Product with name %s not found.\n", productName);
        remove("temp.bin"); // Geçici dosyayı sil
    }
    else {
        remove("products.bin"); // Orijinal dosyayı sil
        rename("temp.bin", "products.bin"); // Geçici dosyayı orijinal dosya olarak yeniden adlandır
        printf("Product updated successfully!\n");
    }

    printf("Press Enter to continue...");
    getchar();
    getchar();

    return 0;
}

int deleteProduct() {
    FILE* productFile, * tempFile;
    Product product;
    char productName[50];
    int found = 0;

    productFile = fopen("products.bin", "rb"); // Orijinal dosyayı okuma modunda aç
    if (productFile == NULL) {
        printf("Error opening product file.\n");
        return 1;
    }

    tempFile = fopen("temp.bin", "wb"); // Geçici dosyayı yazma modunda aç
    if (tempFile == NULL) {
        printf("Error creating temporary file.\n");
        fclose(productFile);
        return 1;
    }

    // Silmek istediğiniz ürünün adını alıyoruz
    printf("Enter Product Name to delete: ");
    scanf("%s", productName);

    // Tüm ürünleri dosyadan okuyup, adı kontrol ediyoruz
    while (fread(&product, sizeof(Product), 1, productFile)) {
        if (strcmp(product.productName, productName) == 0) {
            found = 1;
            printf("Product with name %s deleted successfully!\n", productName);
            continue; // Silinecek ürünü atla
        }
        fwrite(&product, sizeof(Product), 1, tempFile); // Diğer ürünleri geçici dosyaya yaz
    }

    fclose(productFile);
    fclose(tempFile);

    if (!found) {
        printf("Product with name %s not found.\n", productName);
        remove("temp.bin"); // Geçici dosyayı sil
    }
    else {
        remove("products.bin"); // Orijinal dosyayı sil
        rename("temp.bin", "products.bin"); // Geçici dosyayı orijinal dosya olarak yeniden adlandır
    }

    printf("Press Enter to continue...");
    getchar();
    getchar();

    return 0;
}


// Tüm satıcıların ürünlerini listeleyen fonksiyon
int listingOfLocalVendorsandProducts() {
    FILE* productFile;
    FILE* vendorFile;
    Product product;
    Vendor vendor;
    int found = 0;

    // Ürün dosyasını aç
    productFile = fopen("products.bin", "rb");
    if (productFile == NULL) {
        printf("Error opening product file.\n");
        return 1;
    }

    // Satıcı dosyasını aç
    vendorFile = fopen("vendor.bin", "rb");
    if (vendorFile == NULL) {
        printf("Error opening vendor file.\n");
        fclose(productFile);  // Ürün dosyasını kapat
        return 1;
    }

    printf("\n--- Listing All Vendors and Their Products ---\n");

    // Tüm satıcıları oku ve her satıcının ürünlerini listele
    while (fread(&vendor, sizeof(Vendor), 1, vendorFile)) {
        printf("\nVendor: %s (ID: %d)\n", vendor.name, vendor.id);
        printf("--------------------------\n");

        // Kullanıcıya arama yöntemi seçtir
        int strategy;
        printf("Select Collision Resolution Strategy for Vendor %d:\n", vendor.id);
        printf("1. Linear Probing\n");
        printf("2. Quadratic Probing\n");
        printf("3. Double Hashing\n");
        printf("4. Linear Quotient\n");
        printf("5. Progressive Overflow\n");
        printf("6. Use of Buckets\n");
        printf("7. Brent's Method\n");
        scanf("%d", &strategy);

        // Ürünleri bulmak için uygun çakışma çözümleme algoritmasını kullan
        // Ürün dosyasını baştan itibaren okumak için rewind kullanıyoruz
        rewind(productFile);
        int productFound = 0;


        // Ürün dosyasını baştan sona tarayarak ürünleri listeleme işlemi
        rewind(productFile);

        switch (strategy) {
        case 1: // Lineer Probing
            while (fread(&product, sizeof(Product), 1, productFile)) {
                if (product.vendorId == vendor.id && product.price != 0 && product.quantity != 0) {
                    printf("Product: %s, Price: %.2f, Quantity: %d, Season: %s\n",
                        product.productName, product.price, product.quantity, product.season);
                    productFound = 1;
                    found = 1;
                }
            }
            break;

        case 2: // Karesel Probing
            while (fread(&product, sizeof(Product), 1, productFile)) {
                if (product.vendorId == vendor.id && product.price != 0 && product.quantity != 0) {
                    printf("Product: %s, Price: %.2f, Quantity: %d, Season: %s\n",
                        product.productName, product.price, product.quantity, product.season);
                    productFound = 1;
                    found = 1;
                }
            }
            break;

        case 3: // Çift Hashing
            while (fread(&product, sizeof(Product), 1, productFile)) {
                if (product.vendorId == vendor.id && product.price != 0 && product.quantity != 0) {
                    printf("Product: %s, Price: %.2f, Quantity: %d, Season: %s\n",
                        product.productName, product.price, product.quantity, product.season);
                    productFound = 1;
                    found = 1;
                }
            }
            break;

        case 4: // Linear Quotient
            while (fread(&product, sizeof(Product), 1, productFile)) {
                if (product.vendorId == vendor.id && product.price != 0 && product.quantity != 0) {
                    printf("Product: %s, Price: %.2f, Quantity: %d, Season: %s\n",
                        product.productName, product.price, product.quantity, product.season);
                    productFound = 1;
                    found = 1;
                }
            }
            break;

        case 5: // Progressive Overflow
            while (fread(&product, sizeof(Product), 1, productFile)) {
                if (product.vendorId == vendor.id && product.price != 0 && product.quantity != 0) {
                    printf("Product: %s, Price: %.2f, Quantity: %d, Season: %s\n",
                        product.productName, product.price, product.quantity, product.season);
                    productFound = 1;
                    found = 1;
                }
            }
            break;

        case 6: // Use of Buckets
            while (fread(&product, sizeof(Product), 1, productFile)) {
                if (product.vendorId == vendor.id && product.price != 0 && product.quantity != 0) {
                    printf("Product: %s, Price: %.2f, Quantity: %d, Season: %s\n",
                        product.productName, product.price, product.quantity, product.season);
                    productFound = 1;
                    found = 1;
                }
            }
            break;

        case 7: // Brent's Method
            while (fread(&product, sizeof(Product), 1, productFile)) {
                if (product.vendorId == vendor.id && product.price != 0 && product.quantity != 0) {
                    printf("Product: %s, Price: %.2f, Quantity: %d, Season: %s\n",
                        product.productName, product.price, product.quantity, product.season);
                    productFound = 1;
                    found = 1;
                }
            }
            break;

        default:
            printf("Invalid strategy selected.\n");
            break;
        }

        if (!productFound) {
            printf("No products available for this vendor.\n");
        }
    }

    if (!found) {
        printf("No products found for any vendor.\n");
    }

    // Dosyaları kapat
    fclose(vendorFile);
    fclose(productFile);

    printf("\nPress Enter to return to menu...");
    getchar();  // Devam etmek için kullanıcıdan Enter tuşuna basmasını bekle
    getchar();  // Tamponu temizlemek için tekrar

    return 0;
}

// Bu iki satır asıl tanımlardır, hafızada yer kaplayacaklar.
SparseMatrixEntry sparseMatrix[MAX_VENDORS * MAX_PRODUCTS];
int sparseMatrixSize = 0;

// Vendor ve ürün arasındaki ilişkileri ekleyen fonksiyon
void addVendorProductRelation(int vendorId, int productId, float price) {

    if (price == 0) {
        return;
    }
    // Sparse matrise yeni bir ilişki ekliyoruz
    sparseMatrix[sparseMatrixSize].vendorId = vendorId;
    sparseMatrix[sparseMatrixSize].productId = productId;
    sparseMatrix[sparseMatrixSize].price = price;
    sparseMatrixSize++;
}

// Belirli bir vendor'un ürünlerini listeleyen fonksiyon
void listProductsByVendor(int vendorId) {
    printf("\n--- Products offered by Vendor %d ---\n", vendorId);
    int found = 0;
    for (int i = 0; i < sparseMatrixSize; i++) {
        if (sparseMatrix[i].vendorId == vendorId) {
            printf("Product ID: %d, Price: %.2f\n", sparseMatrix[i].productId, sparseMatrix[i].price);
            found = 1;
        }
    }
    if (!found) {
        printf("No products found for Vendor %d.\n", vendorId);
    }
}


// Hash Fonksiyonu
int hashFunction(int key) {
    return key % TABLE_SIZE;
}

// Progressive Overflow
void initializeHashTable() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        hashTable[i].isOccupied = 0;
        hashTableBuckets[i].productCount = 0;
    }
    for (int i = 0; i < OVERFLOW_SIZE; i++) {
        overflowArea[i].isOccupied = 0;
    }
}

// Lineer Probing
int linearProbing(int key, int i) {
    return (key + i) % TABLE_SIZE;
}

// Karesel Probing
int quadraticProbing(int key, int i) {
    return (key + i * i) % TABLE_SIZE;
}

// Çift Hashing
int doubleHashing(int key, int i) {
    int h1 = key % TABLE_SIZE;
    int h2 = 1 + (key % (TABLE_SIZE - 1));
    return (h1 + i * h2) % TABLE_SIZE;
}

// Linear Quotient
int linearQuotient(int key, int i) {
    return (key + i * 7) % TABLE_SIZE;
}

// Progressive Overflow Arama
int progressiveOverflowSearch(int key) {
    for (int i = 0; i < OVERFLOW_SIZE; i++) {
        if (overflowArea[i].isOccupied && overflowArea[i].key == key) {
            return i + TABLE_SIZE;
        }
    }
    return -1;
}

// Bucket Kullanımı Arama
int useOfBucketsSearch(int key) {
    int index = hashFunction(key);
    for (int i = 0; i < hashTableBuckets[index].productCount; i++) {
        if (hashTableBuckets[index].products[i].vendorId == key) {
            return index;
        }
    }
    return -1;
}

// Brent's Method
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





int selectProduct(char* selectedProductName) {
    FILE* productFile;
    Product product;
    int productCount = 0;

    productFile = fopen("products.bin", "rb"); // Ürün dosyasını okuma modunda açıyoruz
    if (productFile == NULL) {
        printf("Error opening product file.\n");
        return 1;
    }

    printf("\n--- Available Products ---\n");
    while (fread(&product, sizeof(Product), 1, productFile)) {
        printf("Name: %s, Price: %.2f, Quantity: %d, Season: %s, Vendor ID: %d\n",
            product.productName, product.price, product.quantity, product.season, product.vendorId);
        productCount++;
    }

    fclose(productFile);

    if (productCount == 0) {
        printf("No products available.\n");
        return 1;
    }


    printf("Enter the Product Name to select: ");
    scanf(" %[^\n]s", selectedProductName);

    // Ürünün seçilip seçilmediğini kontrol etmek için dosyada tekrar arama yapıyoruz
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

    return 0; // İşlem başarılıysa 0 döndür
}

// Heapify fonksiyonu
void heapify(Product arr[], int n, int i) {
    int largest = i; // En büyük elemanı kök olarak başlatıyoruz
    int left = 2 * i + 1; // Sol çocuk
    int right = 2 * i + 2; // Sağ çocuk

    // Sol çocuğun kökten büyük olup olmadığını kontrol et
    if (left < n && arr[left].price > arr[largest].price)
        largest = left;

    // Sağ çocuğun kökten büyük olup olmadığını kontrol et
    if (right < n && arr[right].price > arr[largest].price)
        largest = right;

    // Eğer en büyük eleman kök değilse
    if (largest != i) {
        Product temp = arr[i];
        arr[i] = arr[largest];
        arr[largest] = temp;

        // Alt ağaçta heapify uygula
        heapify(arr, n, largest);
    }
}

// Heap sort fonksiyonu
void heapSort(Product arr[], int n) {
    // Dizi için max-heap oluştur
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Elemanları teker teker heap'ten çek
    for (int i = n - 1; i >= 0; i--) {
        Product temp = arr[0];
        arr[0] = arr[i];
        arr[i] = temp;

        // Kalan ağaç için heapify uygula
        heapify(arr, i, 0);
    }
}

int comparePricesByName(const char* productName) {
    FILE* productFile;
    Product products[100]; // Maksimum 100 ürün kabul ediliyor
    int productCount = 0;
    bool found = false;

    productFile = fopen("products.bin", "rb");
    if (productFile == NULL) {
        printf("Error opening product file.\n");
        return 1;  // Hata durumunda 1 döndür
    }

    // Dosyadan ürünleri oku ve verilen isimle eşleşenleri products dizisine ekle
    while (fread(&products[productCount], sizeof(Product), 1, productFile)) {
        if (strcmp(products[productCount].productName, productName) == 0) {
            productCount++;
            found = true;
        }
    }

    fclose(productFile);

    if (!found) {
        printf("No prices found for Product Name '%s'.\n", productName);
        return 1;  // Ürün bulunamazsa 1 döndür
    }

    // Ürünleri fiyata göre sırala (heap sort kullanarak)
    heapSort(products, productCount);

    // Sıralanmış ürünleri yazdır
    printf("\n--- Price Comparison for Product Name '%s' (Sorted by Price) ---\n", productName);
    for (int i = 0; i < productCount; i++) {
        printf("Vendor ID: %d, Price: %.2f\n", products[i].vendorId, products[i].price);
    }

    printf("\nLowest Price: %.2f\n", products[0].price);
    printf("Highest Price: %.2f\n", products[productCount - 1].price);

    return 0;  // Başarılı işlem için 0 döndür
}



// Function to validate the day input
bool validateDay(const char* day) {
    const char* validDays[] = {
        "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday"
    };
    for (int i = 0; i < 7; ++i) {
        if (strcmp(day, validDays[i]) == 0) {
            return true;
        }
    }
    return false;
}

// Function to validate the working hours input
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

// Function to add market hours and location
void addMarketHoursAndLocation() {
    FILE* file = fopen("marketHours.bin", "ab");
    FILE* vendorFile = fopen("vendor.bin", "rb");
    if (file == NULL) {
        printf("Error opening market hours file.\n");
        return;
    }
    if (vendorFile == NULL) {
        printf("Error opening vendor file.\n");
        fclose(file);
        return;
    }

    MarketHours market;
    int found = 0;
    printf("Enter Market ID: ");
    while (scanf("%d", &market.id) != 1) {
        printf("Invalid input. Please enter a valid numeric Market ID: ");
        while (getchar() != '\n'); // Clear the input buffer
    }

    Vendor vendor;
    while (fread(&vendor, sizeof(Vendor), 1, vendorFile)) {
        if (vendor.id == market.id) {
            found = 1;
            break;
        }
    }

    fclose(vendorFile);

    if (!found) {
        printf("Invalid Market ID. Please enter a valid Market ID from vendor.bin: ");
        while (!found) {
            while (scanf("%d", &market.id) != 1) {
                printf("Invalid input. Please enter a valid numeric Market ID: ");
                while (getchar() != '\n'); // Clear the input buffer
            }
            vendorFile = fopen("vendor.bin", "rb");
            if (vendorFile == NULL) {
                printf("Error opening vendor file.\n");
                fclose(file);
                return;
            }
            while (fread(&vendor, sizeof(Vendor), 1, vendorFile)) {
                if (vendor.id == market.id) {
                    found = 1;
                    break;
                }
            }
            fclose(vendorFile);
            if (!found) {
                printf("Invalid Market ID. Please enter a valid Market ID from vendor.bin: ");
            }
        }
    }

    printf("Enter Day (e.g., Monday): ");
    scanf("%19s", market.day);
    while (!validateDay(market.day)) {
        printf("Invalid day. Please enter a valid day (e.g., Monday): ");
        scanf("%19s", market.day);
    }

    printf("Enter Working Hours (e.g., 09:00 - 18:00): ");
    while (getchar() != '\n');  // Tamponu temizle
    fgets(market.hours, sizeof(market.hours), stdin);  // fgets kullanarak saati al
    market.hours[strcspn(market.hours, "\n")] = 0;  // Satır sonu karakterini kaldır
    while (!validateWorkingHours(market.hours)) {
        printf("Invalid hours. Please enter valid hours (e.g., 09:00 - 18:00): ");
        fgets(market.hours, sizeof(market.hours), stdin);
        market.hours[strcspn(market.hours, "\n")] = 0;  // Satır sonu karakterini kaldır
    }


    printf("Enter Location: ");
    scanf("%49s", market.location);

    fwrite(&market, sizeof(MarketHours), 1, file);
    fclose(file);

    printf("Market hours and location added successfully!\n");
}

// Function to update market hours and location
void updateMarketHoursAndLocation() {
    FILE* file = fopen("marketHours.bin", "rb+");
    if (file == NULL) {
        printf("Error opening market hours file.\n");
        return;
    }

    int marketId;
    int found = 0;
    printf("Enter Market ID to update: ");
    while (scanf("%d", &marketId) != 1) {
        printf("Invalid input. Please enter a valid numeric Market ID: ");
        while (getchar() != '\n'); // Clear the input buffer
    }

    MarketHours market;

    while (fread(&market, sizeof(MarketHours), 1, file)) {
        if (market.id == marketId) {
            found = 1;
            printf("Enter new Day (e.g., Monday): ");
            scanf("%19s", market.day);
            while (!validateDay(market.day)) {
                printf("Invalid day. Please enter a valid day (e.g., Monday): ");
                scanf("%19s", market.day);
            }

            printf("Enter new Working Hours (e.g., 09:00 - 18:00): ");
            while (getchar() != '\n');  // Tamponu temizle
            fgets(market.hours, sizeof(market.hours), stdin);  // fgets kullanarak saati al
            market.hours[strcspn(market.hours, "\n")] = 0;  // Satır sonu karakterini kaldır
            while (!validateWorkingHours(market.hours)) {
                printf("Invalid hours. Please enter valid hours (e.g., 09:00 - 18:00): ");
                fgets(market.hours, sizeof(market.hours), stdin);
                market.hours[strcspn(market.hours, "\n")] = 0;  // Satır sonu karakterini kaldır
            }


            printf("Enter new Location: ");
            scanf("%49s", market.location);

            fseek(file, -sizeof(MarketHours), SEEK_CUR);
            fwrite(&market, sizeof(MarketHours), 1, file);
            printf("Market hours and location updated successfully!\n");
            break;
        }
    }

    if (!found) {
        printf("Market ID %d not found.\n", marketId);
    }

    fclose(file);
}








// XOR two pointers
MarketHoursNode* xor (MarketHoursNode* a, MarketHoursNode* b) {
    return (MarketHoursNode*)((uintptr_t)(a) ^ (uintptr_t)(b));
}

// Insert MarketHours into the XOR linked list in sorted order by ID
MarketHoursNode* insertXORList(MarketHoursNode* head, MarketHours data) {
    MarketHoursNode* newNode = (MarketHoursNode*)malloc(sizeof(MarketHoursNode));
    newNode->data = data;
    newNode->xorPtr = NULL;

    if (head == NULL) {
        return newNode;
    }

    MarketHoursNode* prev = NULL;
    MarketHoursNode* curr = head;
    MarketHoursNode* next;

    while (curr != NULL) {
        next = xor (prev, curr->xorPtr);
        if (data.id < curr->data.id) {
            // Insert before current node
            newNode->xorPtr = xor (prev, curr);
            if (prev != NULL) {
                prev->xorPtr = xor (xor (prev->xorPtr, curr), newNode);
            }
            curr->xorPtr = xor (newNode, next);
            if (prev == NULL) {
                head = newNode;
            }
            return head;
        }
        prev = curr;
        curr = next;
    }

    // Insert at the end
    prev->xorPtr = xor (xor (prev->xorPtr, NULL), newNode);
    newNode->xorPtr = prev;

    return head;
}

// Traverse XOR linked list and display records grouped by ID with screen clearing
void traverseXORListGroupedByID(MarketHoursNode* head) {
    MarketHoursNode* curr = head;
    MarketHoursNode* prev = NULL;
    MarketHoursNode* next;
    char choice;

    while (curr != NULL) {
        int currentID = curr->data.id;

        // Clear the screen (use "cls" for Windows, "clear" for Linux/Mac)
#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        // Display all entries with the same ID
        printf("\n--- Market Hours and Locations (Use 'n' for next ID group, 'p' for previous ID group, 'q' to quit) ---\n");
        printf("\nID: %d\n", currentID);
        while (curr != NULL && curr->data.id == currentID) {
            printf("  Day: %s, Hours: %s, Location: %s\n",
                curr->data.day, curr->data.hours, curr->data.location);
            next = xor (prev, curr->xorPtr);
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
            else if (choice == 'p') {
                // Traverse back to the start of the previous ID group
                while (prev != NULL && prev->data.id == currentID) {
                    next = xor (prev->xorPtr, curr);
                    curr = prev;
                    prev = next;
                }

                // Now go further back to reach the start of the previous group
                if (prev != NULL) {
                    currentID = prev->data.id;
                    while (prev != NULL && prev->data.id == currentID) {
                        next = xor (prev->xorPtr, curr);
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
                break;
            }
            else {
                printf("Invalid choice. Please enter 'n', 'p', or 'q'.\n");
            }
        }
        else {
            printf("You have reached the end of the list.\n");
        }
    }
}

// Function to display market hours and locations grouped by ID
void displayMarketHoursAndLocations() {
    FILE* file = fopen("marketHours.bin", "rb");
    if (file == NULL) {
        printf("Error opening market hours file.\n");
        return;
    }

    MarketHours market;
    MarketHoursNode* head = NULL;

    // Read all MarketHours from the file and insert into the XOR linked list
    while (fread(&market, sizeof(MarketHours), 1, file)) {
        head = insertXORList(head, market);
    }

    fclose(file);

    // Traverse and display the XOR linked list grouped by ID
    traverseXORListGroupedByID(head);
}

