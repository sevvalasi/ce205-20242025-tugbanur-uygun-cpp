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

// Kullanıcının giriş yapıp yapmadığını tutan değişken
bool isAuthenticated = false;

bool userAuthentication();
int mainMenu();
int listingOfLocalVendorsAndProducts();
int seasonalProduceGuide();
int priceComparison();
int marketHoursAndLocations();


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
            getch();
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
        printf("1. Listing of Local Vendors and Products\n");
        printf("2. Seasonal Produce Guide\n");
        printf("3. Price Comparison\n");
        printf("4. Market Hours and Locations\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            listingOfLocalVendorsAndProducts();
            break;
        case 2:
            seasonalProduceGuide();
            break;
        case 3:
            priceComparison();
            break;
        case 4:
            marketHoursAndLocations();
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

int listingOfLocalVendorsAndProducts() {
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

int seasonalProduceGuide() {
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
            getch();
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
    getch();
    return true;
}


