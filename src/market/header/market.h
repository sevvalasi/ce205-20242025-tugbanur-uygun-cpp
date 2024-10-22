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

int getInput();
bool userAuthentication();
bool loginUser();
bool registerUser();
int listingOfLocalVendorsAndProducts();
int seasonalProduceGuide();
int priceComparison();
int marketHoursAndLocations();




#endif // MARKET_H