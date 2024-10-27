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
#include <stack>
#include <sstream>
#include <conio.h>
#include <time.h>
#include <ctype.h>

#include "market.h"  // Bu satır her .cpp dosyasının başına eklenmeli

// Kullanıcının giriş yapıp yapmadığını tutan değişken
bool isAuthenticated = false;


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
    printf("2. Listing of Local Products\n");
    printf("0. Return to Main Menu\n");
    printf("Choose an option: ");
    choice = getInput();

    switch (choice) {
    case 1:
        addProduct();
        break;
    case 2:
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



// Diğer gerekli kütüphaneler ve yapı tanımları

int comparePricesByName(const char* productName);  // comparePricesByName için prototip
int selectProduct(char* selectedProductName);      // selectProduct için prototip

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
        printf("1. Enter Favorite Products\n");
        printf("2. Enter Keywords\n");
        printf("0. Return to Main Menu\n");
        printf("Choose an option: ");
        choice = getInput();

        switch (choice) {
        case 1:
            enterFavoriteProducts();
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

int enterFavoriteProducts() {
    char favoriteProduct[100];
    printf("\nEnter your favorite product: ");
    scanf("%s", favoriteProduct);
    printf("Favorite product '%s' has been saved.\n", favoriteProduct);

    return 0;
}

int enterKeywords() {
    char keyword[100];
    printf("\nEnter a keyword to search: ");
    scanf("%s", keyword);
    printf("Searching for products with keyword '%s'...\n", keyword);

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

// Satıcıları listeleme
int listVendors() {
    FILE* file;
    Vendor vendor;
    file = fopen("vendor.bin", "rb"); // Dosyayı okuma modunda açıyoruz

    if (file == NULL) {
        printf("Error opening vendor file.\n");
        return 1;
    }

    printf("\n--- List of Vendors ---\n");
    int vendorCount = 0; // Listelediğimiz satıcı sayısını takip etmek için


    while (fread(&vendor, sizeof(Vendor), 1, file)) {
        printf("ID: %d, Name: %s \n", vendor.id, vendor.name);
        vendorCount++;
    }
    if (vendorCount == 0) {
        printf("No vendors found.\n");
    }

    fclose(file);
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

        // Her satıcı için ürünleri bulmak için ürün dosyasını baştan okuyalım
        rewind(productFile);
        int productFound = 0;

        while (fread(&product, sizeof(Product), 1, productFile)) {
            if (product.vendorId == vendor.id) {
                printf("Product: %s, Price: %.2f, Quantity: %d, Season: %s\n",
                    product.productName, product.price, product.quantity, product.season);
                found = 1;
                productFound = 1;
            }
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


int addMarketHoursAndLocation() {
    FILE* file;
    MarketHoursAndLocation marketInfo;
    int vendorId;
    int found = 0;

    FILE* vendorFile = fopen("vendor.bin", "rb");
    if (vendorFile == NULL) {
        printf("Vendor file not found.\n");
        return 1;
    }

    printf("Enter Vendor ID to add working hours and location: ");
    if (scanf("%d", &vendorId) != 1) {
        printf("Invalid input for Vendor ID. Exiting function.\n");
        fclose(vendorFile);
        while (getchar() != '\n');  // Tamponu temizle
        return 1;
    }
    while (getchar() != '\n');  // Tamponu temizle

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

    marketInfo.vendorId = vendorId;

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

    char day[20];
    char allDays[200] = "";  // Tüm günleri birleştirip kaydedeceğiz
    do {
        printf("Enter a Working Day (e.g., Monday): ");
        scanf(" %[^\n]s", day);
        getchar();  // Tamponu temizler

        if (validateDay(day)) {
            if (strlen(allDays) > 0) {
                strcat(allDays, ", ");  // Günleri virgülle ayırmak için
            }
            strcat(allDays, day);  // Günü listeye ekle
            printf("Day added. Do you want to add another day? (Press Enter to skip, or type 'y' to continue): ");
            if (getchar() == '\n') {
                break;  // Enter basıldığında döngüden çık
            }
        }
        else {
            printf("Invalid day format. Please enter a full day name (e.g., Monday).\n");
        }
    } while (1);  // Sonsuz döngü; Enter basıldığında kırılacak

    strcpy(marketInfo.workingDays, allDays);  // Tüm günleri marketInfo içine kaydediyoruz

    file = fopen("market_hours.bin", "ab");
    if (file == NULL) {
        printf("Error opening market hours file.\n");
        return 1;
    }

    fwrite(&marketInfo, sizeof(MarketHoursAndLocation), 1, file);
    fclose(file);

    printf("Market hours and location added successfully!\n");
    getchar();
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

// Diğer fonksiyonlarınız burada

int priceComparis() {
    // Burada yapacağınız işlemleri tanımlayın
    printf("Price comparison functionality.\n");
    return 0; // Fonksiyonun başarılı bir şekilde çalıştığını belirtmek için 0 döndürüyoruz.
}

// Diğer fonksiyonlar burada devam ediyor

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



int comparePricesByName(const char* productName) {
    FILE* productFile;
    Product product;
    bool found = false;

    productFile = fopen("products.bin", "rb");
    if (productFile == NULL) {
        printf("Error opening product file.\n");
        return 1;  // Hata durumunda 1 döndür
    }

    float minPrice = FLT_MAX; // En düşük fiyat için başlangıç değeri
    float maxPrice = FLT_MIN; // En yüksek fiyat için başlangıç değeri

    printf("\n--- Price Comparison for Product Name '%s' ---\n", productName);
    while (fread(&product, sizeof(Product), 1, productFile)) {
        if (strcmp(product.productName, productName) == 0) {
            printf("Vendor ID: %d, Price: %.2f\n", product.vendorId, product.price);

            if (product.price < minPrice) {
                minPrice = product.price;
            }
            if (product.price > maxPrice) {
                maxPrice = product.price;
            }
            found = true;
        }
    }

    fclose(productFile);

    if (found) {
        printf("\nLowest Price: %.2f\n", minPrice);
        printf("Highest Price: %.2f\n", maxPrice);
        return 0;  // Başarılı işlem için 0 döndür
    }
    else {
        printf("No prices found for Product Name '%s'.\n", productName);
        return 1;  // Ürün bulunamazsa 1 döndür
    }
}

