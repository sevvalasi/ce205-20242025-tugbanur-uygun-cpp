#define _CRT_SECURE_NO_WARNINGS
#include "../header/market.h"
#include <stdexcept>
#include <iostream>
#include <string.h>
#include <string>
#include <fstream>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <algorithm>
#include <stdio.h>
#include <stack>
#include <sstream>
#include <conio.h>
#include <time.h>
#include <ctype.h>


// Kullanıcının giriş yapıp yapmadığını tutan değişken
bool isAuthenticated = false;


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
        printf("2. Listening of Local Products\n");
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

    printf("\n--- Listing of Local Vendors and Products ---\n");
    printf("1. Browse Vendors\n");
    printf("2. Search Products\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("Browse Vendors selected.\n");
        break;
    case 2:
        printf("Search Products selected.\n");
        break;
    default:
        printf("Invalid option. Returning to main menu.\n");
    }
    return 0;
}

int listingOfLocalProducts()
{
    printf("\n--- Seasonal Produce Guide ---\n");
    printf("View Seasonal Availability selected.\n");
    return 0;
}


int priceComparison() {
    int choice;

    printf("\n--- Price Comparison ---\n");
    printf("1. Select Product\n");
    printf("2. Compare Prices\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("Select Product selected.\n");
        break;
    case 2:
        printf("Compare Prices selected.\n");
        break;
    default:
        printf("Invalid option. Returning to main menu.\n");
    }
    return 0;
}

int marketHoursAndLocations() {
    int choice;

    printf("\n--- Market Hours and Locations ---\n");
    printf("1. View Markets\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
        printf("View Markets selected.\n");
        break;
    default:
        printf("Invalid option. Returning to main menu.\n");
    }
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


