/**
 * @file marketapp.cpp
 * @brief Main application file for the market management system.
 *
 * This file contains the main function of the application which serves as the entry point of the program.
 * It includes standard libraries for input/output operations, data structures, string manipulations,
 * and exception handling, as well as application-specific headers that integrate various components of
 * the market application.
 *
 * Current Test Coverage:
 * - This file currently has 0% line coverage, indicating that no executable lines of code in this file have been
 *   covered by the tests. This may imply that the main application flow tests are missing or incomplete.
 * - Coverage is crucial for ensuring that the main entry point and its integration with other modules
 *   are functioning correctly under different scenarios.
 *
 * Attention:
 * - It is recommended to develop and run functional tests that execute the main function to improve
 *   coverage and verify the integration of various components of the application.
 */

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <stdexcept>

// Application-specific headers for market functionalities.
#include "../../market/header/market.h"
#include "../../marketapp/header/marketapp.h"
#include "../../market/src/market.cpp"

/**
 * @brief Main function of the application which serves as the entry point of the program.
 *
 * The main function calls the userAuthentication to handle user login, and populates the system
 * with predefined vendor-product relationships. This serves as a setup example for managing market operations.
 *
 * @return int Returns 0 to indicate successful execution of the program.
 */
int main() {
    // Authenticate the user before proceeding.
    userAuthentication();

    // Adding relationships between vendors and products with specified vendor IDs, product IDs, and prices.
    addVendorProductRelation(1, 101, 10.5);    // Adds a relationship for vendor 1 with product 101 priced at $10.5.
    addVendorProductRelation(1, 102, 20.0);    // Adds a relationship for vendor 1 with product 102 priced at $20.0.
    addVendorProductRelation(2, 101, 11.0);    // Adds a relationship for vendor 2 with product 101 priced at $11.0.
    addVendorProductRelation(3, 103, 15.0);     // Adds a relationship for vendor 3 with product 103 priced at $15.0.


    
   
    // Return 0 to indicate successful completion of the program.
    return 0;
}