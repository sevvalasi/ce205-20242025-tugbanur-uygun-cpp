/**
 * @file market.h
 * 
 * @brief Provides functions for math. utilities
 */

#ifndef MARKET_H
#define MARKET_H

#include "../../utility/header/commonTypes.h"

typedef struct {
    char username[50];
    char password[50];
} User;

bool registerUser();

bool loginUser();

int userAuthentication();

int listingOfLocalVendorsAndProducts();

int seasonalProduceGuide();

int priceComparison();

int marketHoursAndLocations();

#endif // MARKET_H