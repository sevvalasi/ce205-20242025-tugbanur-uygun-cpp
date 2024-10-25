/**
 * @file market.h
 *
 * @brief Provides functions for math. utilities
 */

#ifndef MARKET_H
#define MARKET_H

#include <iostream>
#include "../../utility/header/commonTypes.h"

 // Kullanıcı bilgilerini tutacak yapı (struct)
struct User {
    char username[50];  // Kullanıcı adı (en fazla 50 karakter)
    char password[50];  // Şifre (en fazla 50 karakter)
};


struct Vendor {
    int id;                // Benzersiz ID (int)
    char name[50];         // Satıcının ismi (string - max 50 karakter)
};

struct Product {
    int vendorId;          // Satıcı ID'si
    char productName[50];  // Ürünün adı
    float price;           // Ürünün fiyatı
    int quantity;          // Ürünün adedi
    char season[20];       // Ürünün mevsimi
};


int getInput();
int mainMenu();

int listingOfLocalVendors();
int listingOfLocalProducts();
int seasonalProduceGuide();
int priceComparison();
int marketHoursAndLocations();

bool userAuthentication();
bool loginUser();
bool registerUser();

int addVendor();
int updateVendor();
int deleteVendor();
int listVendors();

int addProduct();
int listingOfLocalVendorsandProducts();


int searchProductsOrEnterKeyword();
int enterFavoriteProducts();
int enterKeywords();






#endif // MARKET_H