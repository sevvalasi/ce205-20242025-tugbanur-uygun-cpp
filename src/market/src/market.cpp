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
int userAuthentication();
int listingOfLocalVendorsAndProducts();
int seasonalProduceGuide();
int priceComparison();
int marketHoursAndLocations();

int mainMenu() {
    int choice;

    do {
        // Ana menüyü yazdýr
        printf("\n--- Main Menu ---\n");
        printf("1. User Authentication\n");
        printf("2. Listing of Local Vendors and Products\n");
        printf("3. Seasonal Produce Guide\n");
        printf("4. Price Comparison\n");
        printf("5. Market Hours and Locations\n");
        printf("0. Exit\n");
        printf("Choose an option: ");
        scanf("%d", &choice);

        switch (choice) {
        case 1:
            userAuthentication();
            break;
        case 2:
            listingOfLocalVendorsAndProducts();
            break;
        case 3:
            seasonalProduceGuide();
            break;
        case 4:
            priceComparison();
            break;
        case 5:
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
        printf("Login selected.\n");
        break;
    case 2:
        printf("Register selected.\n");
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