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
#define TABLE_SIZE 100
#define OVERFLOW_SIZE 20
#define BUCKET_SIZE 5
#define MAX_VENDORS 100
#define MAX_PRODUCTS 100



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

int marketHoursAndLocations() {
    int choice;

    do {
        printf("\n--- Market Hours and Locations ---\n");
        printf("1. Add Working Hours and Location\n");
        printf("2. View Market Hours and Locations\n");
        printf("0. Return to Main Menu\n");
        printf("Choose an option: ");

        // Geçerli bir sayı girilmediğinde tekrar sormak için kontrol ekleyelim
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a valid option.\n");
            while (getchar() != '\n'); // Tamponu temizle
            choice = -1; // Geçersiz bir değer atayarak döngünün devam etmesini sağla
            continue;
        }

        switch (choice) {
        case 1:
            addMarketHoursAndLocation();
            break;
        case 2:
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


// Kullanıcı giriş fonksiyonu
bool loginUser() {
    clearScreen();
    FILE* file;
    User user;
    char username[50], password[50];
    int found = 0;

    // Kullanıcıdan giriş bilgileri alınıyor
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    // Dosya açılıyor ve kullanıcı bilgileri okunuyor
    file = fopen("users.bin", "rb");
    if (file == NULL) {
        printf("The file is not opened.\n");
        exit(1);
    }

    // Dosyadaki kullanıcılar tek tek okunup kontrol ediliyor
    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            printf("The entry is successfull. Welcome! %s.\n", username);
            getchar();
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Incorrect username or password. \n");
        return false;
        
    }
    
    return true;
}

bool registerUser() {
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

    printf("Register is successfull!\n");
    getchar();
    return true;
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



// Haftanın günlerini doğrulayan fonksiyon
bool validateDay(const char* day) {
    const char* validDays[] = {
        "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
    };

    for (int i = 0; i < 7; ++i) {
        if (strcmp(day, validDays[i]) == 0) {
            return true;
        }
    }
    return false;
}


// Çalışma saatlerini doğrulayan fonksiyon
bool validateWorkingHours(const char* hours) {
    if (strlen(hours) != 13) return false;
    if (hours[0] < '0' || hours[0] > '2') return false;
    if (hours[1] < '0' || hours[1] > '9') return false;
    if (hours[2] != ':') return false;
    if (hours[3] < '0' || hours[3] > '5') return false;
    if (hours[4] < '0' || hours[4] > '9') return false;
    if (hours[5] != ' ') return false;
    if (hours[6] != '-') return false;
    if (hours[7] != ' ') return false;
    if (hours[8] < '0' || hours[8] > '2') return false;
    if (hours[9] < '0' || hours[9] > '9') return false;
    if (hours[10] != ':') return false;
    if (hours[11] < '0' || hours[11] > '5') return false;
    if (hours[12] < '0' || hours[12] > '9') return false;
    return true;
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



//CSS (Circular Scheduling Selection) algoritması, genellikle belirli gün ve saatlerde çalışması gereken görevleri veya iş süreçlerini döngüsel olarak planlamak için kullanılır.
// bir marketin çalışma günlerini haftalık olarak belirlemek için CSS algoritmasından yararlanabiliriz.



// Haftanın günlerini belirten sabit dizi
const char* daysOfWeek[7] = { "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday" };

// Günlerin indeksini döndüren fonksiyon
#include <ctype.h> // tolower() fonksiyonu için gerekli

int getDayIndex(const char* day) {
    char lowerDay[20];
    int i;

    // Kullanıcıdan alınan günü küçük harfe çeviriyoruz
    for (i = 0; day[i] != '\0' && i < sizeof(lowerDay) - 1; ++i) {
        lowerDay[i] = tolower(day[i]);
    }
    lowerDay[i] = '\0'; // Dizinin sonuna null karakteri ekliyoruz

    // Haftanın günlerini tanımlayan sabit dizi
    const char* daysOfWeek[7] = { "monday", "tuesday", "wednesday", "thursday", "friday", "saturday", "sunday" };

    for (int i = 0; i < 7; ++i) {
        if (strcmp(lowerDay, daysOfWeek[i]) == 0) {
            return i;
        }
    }
    return -1; // Geçersiz gün
}


// Döngüsel çalışma günlerini oluşturan fonksiyon
char* generateWorkingDays(const char* startDay, int duration) {
    static char workingDays[200]; // Çıktı dizisi, döngüsel bir dizide saklanır
    int startIndex = getDayIndex(startDay);
    if (startIndex == -1) {
        printf("Invalid starting day.\n");
        return NULL; // Geçersiz gün ismi durumunda NULL döndür
    }

    workingDays[0] = '\0'; // Çıktı dizisini sıfırla

    // Döngüsel olarak gün ekleme
    for (int i = 0; i < duration; i++) {
        int currentIndex = (startIndex + i) % 7;
        if (i > 0) {
            strcat(workingDays, ", ");
        }
        strcat(workingDays, daysOfWeek[currentIndex]);
    }
    return workingDays; // Gün dizisini döndür
}

// Market saatleri ve lokasyon bilgisi ekleyen fonksiyon
int addMarketHoursAndLocation() {
    FILE* vendorFile;
    MarketHoursAndLocation marketInfo;
    int vendorId;
    int found = 0;

    vendorFile = fopen("vendor.bin", "rb");
    if (vendorFile == NULL) {
        printf("Vendor file not found.\n");
        return 1;
    }

    // Kullanıcıdan Vendor ID'yi alma
    printf("Enter Vendor ID to add working hours and location: ");
    if (scanf("%d", &vendorId) != 1) {
        printf("Invalid input for Vendor ID. Exiting function.\n");
        fclose(vendorFile);
        while (getchar() != '\n');  // Tamponu temizle
        return 1;
    }
    while (getchar() != '\n');  // Tamponu temizle

    // Vendor dosyasından ID'yi kontrol etme
    Vendor vendor;
    while (fread(&vendor, sizeof(Vendor), 1, vendorFile)) {
        if (vendor.id == vendorId) {
            found = 1;
            break;
        }
    }
    fclose(vendorFile);

    if (!found) {
        printf("Vendor with ID %d not found.\n", vendorId);
        return 1;
    }

    // MarketInfo yapısının vendorId kısmını doldurma
    marketInfo.vendorId = vendorId;

    // Kullanıcıdan Lokasyon ve Çalışma Saatleri bilgilerini alma
    printf("Enter Location: ");
    if (scanf(" %[^\n]s", marketInfo.location) != 1) {
        printf("Invalid input for Location. Exiting function.\n");
        return 1;
    }
    while (getchar() != '\n');  // Tamponu temizle

    do {
        printf("Enter Working Hours (e.g., 09:00 - 18:00): ");
        if (scanf(" %[^\n]s", marketInfo.workingHours) != 1) {
            printf("Invalid input for Working Hours. Exiting function.\n");
            return 1;
        }
        if (!validateWorkingHours(marketInfo.workingHours)) {
            printf("Invalid working hours format. Please use HH:MM - HH:MM format.\n");
        }
    } while (!validateWorkingHours(marketInfo.workingHours));
    while (getchar() != '\n');  // Tamponu temizle

    // CSS Algoritması kullanarak döngüsel çalışma günlerini ekle
    char startDay[20];
    int duration;
    printf("Enter the starting day for working days (e.g., Monday): ");
    scanf(" %[^\n]s", startDay);
    printf("Enter the number of working days: ");
    scanf("%d", &duration);

    // Çalışma günlerini döngüsel olarak oluştur ve kaydet
    const char* workingDays = generateWorkingDays(startDay, duration);
    if (workingDays == NULL) {
        printf("Failed to generate working days.\n");
        return 1;
    }
    strcpy(marketInfo.workingDays, workingDays);

    // Market hours dosyasını açma ve marketInfo'yu dosyaya yazma
    FILE* file = fopen("market_hours.bin", "ab");
    if (file == NULL) {
        printf("Error opening market hours file.\n");
        return 1;
    }

    // Dosyaya yazma ve hata kontrolü
    if (fwrite(&marketInfo, sizeof(MarketHoursAndLocation), 1, file) != 1) {
        printf("Error writing to market hours file.\n");
        fclose(file);
        return 1; // Eğer yazma işlemi başarısız olursa burada işlem durdurulacak
    }
    else {
        printf("Market hours and location added successfully!\n");
    }

    fclose(file);
    getchar();  // Kullanıcının bir tuşa basmasını bekleyin
    return 0;
}


int displayMarketHoursAndLocations() {
    FILE* file;
    MarketHoursAndLocation marketInfo;

    file = fopen("market_hours.bin", "rb");
    if (file == NULL) {
        printf("No market hours and locations found.\n");
        return 1;
    }

    printf("\n--- Market Hours and Locations ---\n");

    // Dosyadaki her market verisini tek tek okuyup ekrana yazdırma
    while (fread(&marketInfo, sizeof(MarketHoursAndLocation), 1, file)) {
        printf("Vendor ID: %d\n", marketInfo.vendorId);
        printf("Location: %s\n", marketInfo.location);
        printf("Working Hours: %s\n", marketInfo.workingHours);
        printf("Working Days: %s\n", marketInfo.workingDays);
        printf("-------------------------\n");
    }

    fclose(file);
    printf("Press Enter to return to menu...");
    getchar();
    return 0;

}

