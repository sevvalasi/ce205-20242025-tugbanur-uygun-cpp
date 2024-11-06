#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>
#include "../../market/header/market.h"
#include "../../marketapp/header/marketapp.h"
#include "../../market/src/market.cpp"


int main() {

    userAuthentication();

    // Vendor ve ürün ilişkilerini ekleme
    addVendorProductRelation(1, 101, 10.5);
    addVendorProductRelation(1, 102, 20.0);
    addVendorProductRelation(2, 101, 11.0);
    addVendorProductRelation(3, 103, 15.0);

    
   

    return 0;
}