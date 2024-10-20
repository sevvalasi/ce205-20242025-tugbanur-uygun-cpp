/*Functions*/

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

// Fonksiyon bildirimleri


int mainMenu() {
    int choice;

    do {
        // Ana menüyü yazdýr
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

int userAuthentication() {
    int choice;

    printf("\n--- User Authentication ---\n");
    printf("1. Login\n");
    printf("2. Register\n");
    printf("3. Guest Mode\n");
    printf("Choose an option: ");
    scanf("%d", &choice);

    switch (choice) {
    case 1:
       // printf("Login selected.\n");
        loginUser();
        break;
    case 2:
        registerUser();
        //printf("Register selected.\n");
        break;
    case 3:
        printf("Guest Mode selected.\n");
        break;
    default:
        printf("Invalid option. Returning to main menu.\n");
    }
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

bool registerUser() {
    FILE* file;
    User user;

    // Kullanıcıdan bilgiler alınıyor
    printf("Kullanıcı Adı: ");
    scanf("%s", user.username);
    printf("Şifre: ");
    scanf("%s", user.password);

    // Kullanıcı bilgileri binary formatta dosyaya yazılıyor
    file = fopen("users.bin", "ab"); // "ab" ile dosyaya ekleme modunda açıyoruz
    if (file == NULL) {
        printf("Dosya açılamadı.\n");
        exit(1);
    }
    fwrite(&user, sizeof(User), 1, file);
    fclose(file);

    printf("Kayıt başarılı!\n");
    return true;
}

// Kullanıcı giriş fonksiyonu
bool loginUser() {
    FILE* file;
    User user;
    char username[50], password[50];
    int found = 0;

    // Kullanıcıdan giriş bilgileri alınıyor
    printf("Kullanıcı Adı: ");
    scanf("%s", username);
    printf("Şifre: ");
    scanf("%s", password);

    // Dosya açılıyor ve kullanıcı bilgileri okunuyor
    file = fopen("users.bin", "rb");
    if (file == NULL) {
        printf("Dosya açılamadı.\n");
        exit(1);
    }

    // Dosyadaki kullanıcılar tek tek okunup kontrol ediliyor
    while (fread(&user, sizeof(User), 1, file)) {
        if (strcmp(user.username, username) == 0 && strcmp(user.password, password) == 0) {
            printf("Giriş başarılı! Hoş geldin %s.\n", username);
            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found) {
        printf("Hatalı kullanıcı adı veya şifre.\n");
    }
    return true;
}