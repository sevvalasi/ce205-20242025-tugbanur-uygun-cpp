/**
 * @file market_test.cpp
 * @brief Unit tests for the Market application functions using Google Test framework.
 *
 * This file contains unit tests for the main menu, vendor, product management, market hours,
 * and search functionalities of the Market application. It utilizes Google Test to simulate user
 * inputs and verify the expected results of the functions.
 */
#include "gtest/gtest.h"
#include "../../market/header/market.h"
#include "../../market/src/market.cpp"

 // Global test dosyaları
const char* userFile = "test_users.bin";
const char* taskFile = "test_tasks.bin";
const char* deadlineFile = "test_deadlines.bin";
const char* vendorFile = "test_vendors.bin";
const char* productFile = "test_products.bin";
const char* marketHoursFile = "test_market_hours.bin";




 
 /**
  * @class MarketTest
  * @brief Test fixture class for Market application unit tests.
  *
  * This class sets up and tears down the test environment, simulating user inputs and redirecting
  * input and output streams as necessary. It is used for testing different functionalities
  * related to vendors, products, market hours, and user interactions.
  */
class MarketTest : public ::testing::Test {
protected:
    const char* inputTest = "inputTest.txt";
    const char* outputTest = "outputTest.txt";


    /**
     * @brief Set up the test environment by initializing the hash table.
     */
    void SetUp() override {
        // Test verileri ayarlanabilir.
        initializeHashTable();
    }


    /**
    * @brief Tear down the test environment by removing temporary input and output files.
    */
    void TearDown() override {
        remove(inputTest);
        remove(outputTest);
    }

    /**
     * @brief Simulate user input by writing to a file and redirecting stdin to that file.
     * @param userInput The simulated user input.
     */
    void simulateUserInput(const char* userInput) {
        FILE* fileinput = fopen(inputTest, "wb");
        fputs(userInput, fileinput);
        fclose(fileinput);
        freopen(inputTest, "rb", stdin);
        freopen(outputTest, "wb", stdout);
    }

    /**
     * @brief Reset stdin and stdout to the console.
     */
    void resetStdinStdout() {
        fclose(stdin);
        fflush(stdout);
#ifdef _WIN32
        freopen("CON", "a", stdout);
        freopen("CON", "r", stdin);
#else
        freopen("/dev/tty", "a", stdout);
        freopen("/dev/tty", "r", stdin);
#endif // _WIN32
    }

    
 /**
 * @brief Creates a test user file with predefined users.
 *
 * Writes a static array of users to a binary file named defined by `userFile`. This function is typically used
 * to populate a test environment with predictable user data for testing purposes.
 */
    void createTestUserFile() {
        User users[] = {
            {"tugba", "password123"},
            {"naz", "password456"},
        };

        FILE* file = fopen(userFile, "wb");
        if (file) {
            fwrite(users, sizeof(User), 2, file);
            fclose(file);
        }
    }

 /**
 * @brief Creates a test vendor file with predefined vendors.
 *
 * Writes a static array of vendors to a binary file named defined by `vendorFile`. This function is typically used
 * to populate a test environment with predictable vendor data for testing purposes.
 */
    void createTestVendorFile() {
        Vendor vendors[] = {
            {1, "Vendor1"},
            {2, "Vendor2"},
        };

        FILE* file = fopen(vendorFile, "wb");
        if (file) {
            fwrite(vendors, sizeof(Vendor), 2, file);
            fclose(file);
        }
    }

 /**
 * @brief Creates a test product file with predefined products.
 *
 * Writes a static array of products to a binary file named defined by `productFile`. This function is typically used
 * to populate a test environment with predictable product data for testing purposes.
 */
    void createTestProductFile() {
        Product products[] = {
            {1, "Tomato", 25, 100, "Winter"},
            {2, "Apple", 30, 50, "Fall"},
        };

        FILE* file = fopen(productFile, "wb");
        if (file) {
            fwrite(products, sizeof(Product), 2, file);
            fclose(file);
        }
    }

 /**
 * @brief Creates a test file for market hours and locations with predefined data.
 *
 * Writes a static array of market hours and locations to a binary file named defined by `marketHoursFile`.
 * This function is typically used to populate a test environment with predictable market hours data for testing purposes.
 */
    void createTestMarketHoursFile() {
        MarketHours marketHours[] = {
            {1, "monday", "9:00 - 5:00", "Main Street"},
            {2, "tuesday", "10:00 - 6:00", "Market Square"},
        };

        FILE* file = fopen(marketHoursFile, "wb");
        if (file) {
            fwrite(marketHours, sizeof(MarketHours), 2, file);
            fclose(file);
        }
    }

 /**
* @brief Initializes test hash table by adding sample vendor-product relations.
*
* Calls `initializeHashTable` to set up a new hash table and then populates it with predefined vendor-product relations.
* This setup is used to mimic typical application state in a controlled test environment.
*/
    void initializeTestHashTable() {
        initializeHashTable();
        // Örnek ürün ve vendor ilişkilerini ekle
        addVendorProductRelation(1, 101, 10.5); // Vendor 1 için ürün 101
        addVendorProductRelation(2, 102, 15.0); // Vendor 2 için ürün 102
    }

 /**
 * @brief Generates test data for Huffman encoding and builds a Huffman tree.
 *
 * Creates sample data and frequency arrays, then constructs a Huffman tree and generates Huffman codes.
 * This is typically used to test the Huffman coding algorithm's implementation and functionality.
 */
    void createHuffmanTestData() {
        char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
        int freq[] = { 5, 9, 12, 13, 16, 45 };
        int size = sizeof(data) / sizeof(data[0]);

        struct MinHeapNode* huffmanTreeRoot = buildHuffmanTree(data, freq, size);
        HuffmanCodes(data, freq, size);
    }

 /**
* @brief Initializes the test environment by calling all individual test data creation functions.
*
* This function orchestrates the creation of test data files for users, vendors, products, and market hours,
* initializes a test hash table, and generates test data for Huffman encoding. It provides a comprehensive
* setup for system testing.
 */
    void initializeTestEnvironment() {
        createTestUserFile();
        createTestVendorFile();
        createTestProductFile();
        createTestMarketHoursFile();
        initializeTestHashTable();
        createHuffmanTestData();
    }
};





/**
 * @test MainMenuTest
 * @brief Test case to verify that selecting option 0 in the main menu functions correctly.
 *
 * This test simulates the user selecting the exit option '0' from the main menu.
 * It ensures that the function processes the input correctly and concludes the program flow appropriately.
 * The expected result is that the function completes successfully, indicated by returning `true`.
 */
TEST_F(MarketTest, MainMenuTest) {
    // Simulate the user input for option '0'
    simulateUserInput("0\n");

    // Call the main menu function
    bool result = mainMenu();

    // Reset standard input and output streams to their original state
    resetStdinStdout();

    // Verify that the result is true
    EXPECT_TRUE(result);
}

/**
 * @test MainMenuTest1
 * @brief Test case for the main menu function with option 1.
 *
 * This test simulates a user navigating to the first menu option and then exiting.
 * It checks that the mainMenu function can handle a sequence of valid inputs ending with the exit command.
 * The function should return true, indicating successful handling and completion of the command sequence.
 */
TEST_F(MarketTest, MainMenuTest1) {
    // Simulate valid user inputs for navigating the menu and exiting
    simulateUserInput("1\n0\n0\n");

    // Call the main menu function
    bool result = mainMenu();

    // Reset standard input and output streams
    resetStdinStdout();

    // Assert that the result is true
    EXPECT_TRUE(result);
}

/**
 * @test MainMenuTest2
 * @brief Test case for the main menu function with option 2.
 *
 * This test checks the functionality of the second menu option followed by exiting.
 * The expected behavior is for the function to process the inputs correctly and return true, demonstrating
 * that it has successfully handled the user's command to navigate and then exit.
 */
TEST_F(MarketTest, MainMenuTest2) {
    // Simulate valid user inputs for navigating the menu and exiting
    simulateUserInput("2\n0\n0\n");

    // Call the main menu function
    bool result = mainMenu();

    // Reset the streams
    resetStdinStdout();

    // Check that the result is true
    EXPECT_TRUE(result);
}


/**
 * @test MainMenuTest3
 * @brief Test case for more complex interaction with the main menu using option 3.
 *
 * This test simulates a sequence of commands that includes multiple levels of menu navigation,
 * followed by an exit command. It ensures that the function can handle a more complex sequence of
 * user inputs correctly and returns true, which signifies successful execution.
 */
TEST_F(MarketTest, MainMenuTest3) {
    // Simulate complex user input sequences for option 3 and exiting
    simulateUserInput("3\n0\n0\n0\n0\n4\n");

    // Call the main menu function
    bool result = mainMenu();

    // Reset input/output streams
    resetStdinStdout();

    // Validate that the function executed successfully
    EXPECT_TRUE(result);
}


/**
 * @test MainMenuTest4
 * @brief Test case to evaluate the main menu function with option 4.
 *
 * This test simulates the user selecting option 4 from the main menu and then exiting.
 * The purpose is to verify that the function can handle this specific path through the menu
 * and conclude correctly by returning true.
 */
TEST_F(MarketTest, MainMenuTest4) {
   // Simulate user input for option 4 and exiting
    simulateUserInput("4\n0\n0\n");

    // Execute the main menu function
    bool result = mainMenu();

    // Reset streams to default
    resetStdinStdout();

    // Confirm that the result is as expected
    EXPECT_TRUE(result);
}


/**
 * @test MainMenuTest5
 * @brief Test case to confirm correct handling of option 5 in the main menu.
 *
 * This test checks if the main menu correctly processes the user selecting option 5 and then exiting.
 * The expected outcome is that the function returns true, indicating that it successfully managed the input sequence.
 */
TEST_F(MarketTest, MainMenuTest5) {
    // Simulate user input for option 5 and exiting scenarios
    simulateUserInput("5\n0\n0\n");

    // Run the main menu function
    bool result = mainMenu();

    // Clean up changes to streams
    resetStdinStdout();

    // Assert successful execution
    EXPECT_TRUE(result);
}


/**
 * @test MainMenuTestInvalid
 * @brief Test case for handling an invalid option input in the main menu.
 *
 * This test simulates the user entering an invalid menu option and then selecting to exit.
 * It validates that the mainMenu function can handle unexpected or invalid inputs gracefully
 * and still concludes by returning true, demonstrating robustness to user input errors.
 */
TEST_F(MarketTest, MainMenuTestInvalid) {
    // Simulate invalid user input and the subsequent exit command
    simulateUserInput("787\n0\n");

    // Execute the main menu function
    bool result = mainMenu();

    // Reset standard streams
    resetStdinStdout();
    // Verify that the function handled the input correctly
    EXPECT_TRUE(result);
}

/**
 * @test listingOfLocalVendorsTEST
 * @brief Test case for listing local vendors with an option to exit.
 *
 * This test simulates the simplest interaction: the user selects to exit the vendor listing immediately.
 * The function is expected to process this input correctly and return true, demonstrating the ability to handle an exit command.
 */
TEST_F(MarketTest, listingOfLocalVendorsTEST) {
    // Simulate the user input for exiting the listing
    simulateUserInput("0\n");

    // Call the function to list local vendors
    bool result = listingOfLocalVendors();

    // Reset standard input and output streams
    resetStdinStdout();

    // Assert the function returns true, indicating successful handling
    EXPECT_TRUE(result);
}

/**
 * @test listingOfLocalVendorsTEST2
 * @brief Test case for listing local vendors and performing a specific action (e.g., select vendor).
 *
 * This test simulates selecting a vendor and then exiting. It checks that the function can handle a sequence of valid inputs,
 * including making a selection and then choosing to exit, and concludes by returning true.
 */
TEST_F(MarketTest, listingOfLocalVendorsTEST2) {
    // Simulate user input for selecting a vendor named 'tugba' and then exiting
    simulateUserInput("1\ntugba\n0\n0\n");

    // Execute the vendor listing function
    bool result = listingOfLocalVendors();

    // Reset the streams
    resetStdinStdout();

    // Verify that the function handles the input correctly and returns true
    EXPECT_TRUE(result);
}


/**
 * @test listingOfLocalVendorsTEST3
 * @brief Test case for more complex interactions with the local vendors listing function.
 *
 * This test simulates deeper interaction such as selecting a vendor by ID, performing an operation (e.g., viewing details),
 * and then exiting. It validates that the function handles multiple user inputs effectively and returns true.
 */
TEST_F(MarketTest, listingOfLocalVendorsTEST3) {
    // Simulate user inputs for various operations and exiting
    simulateUserInput("2\n123456\ntugba\n0\n0\n");

    // Call the vendor listing function
    bool result = listingOfLocalVendors();

    // Reset input/output streams
    resetStdinStdout();

    // Check that the function successfully processes the input sequence
    EXPECT_TRUE(result);
}


/**
 * @test listingOfLocalVendorsTEST4
 * @brief Test case for testing the local vendors listing with a specific filter or search criteria.
 *
 * This test simulates using a specific search or filter option (like a location-based filter) and then exiting.
 * It ensures that the function can handle filtered searches and user exits properly, returning true.
 */
TEST_F(MarketTest, listingOfLocalVendorsTEST4) {
    // Simulate user input for filtering and exiting
    simulateUserInput("3\n123456\n0\n0\n");

    // Perform the listing operation
    bool result = listingOfLocalVendors();

    // Clean up changes to streams
    resetStdinStdout();

    // Assert successful execution
    EXPECT_TRUE(result);
}


/**
 * @test listingOfLocalVendorsTEST5
 * @brief Test case for navigating through multiple menu options in the local vendors listing before exiting.
 *
 * This test challenges the function's ability to handle a sequence of navigation commands (e.g., paging through results)
 * and then exiting. The test simulates complex navigation and checks for correct function completion by returning true.
 */
TEST_F(MarketTest, listingOfLocalVendorsTEST5) {
    // Simulate user input for advanced navigation and exiting
    simulateUserInput("4\nq\nx\n0\n0\n");

    // Call the function
    bool result = listingOfLocalVendors();

    // Reset streams
    resetStdinStdout();

    // Validate that the function managed the inputs correctly
    EXPECT_TRUE(result);
}


/**
 * @test listingOfLocalVendorsInvalidTEST
 * @brief Test case for handling invalid inputs in the local vendors listing.
 *
 * This test simulates the user entering an invalid option and then handling subsequent valid commands to exit.
 * It verifies that the function is robust against invalid inputs and can still process subsequent commands effectively,
 * returning true as expected.
 */
TEST_F(MarketTest, listingOfLocalVendorsInvalidTEST) {
    // Simulate invalid and then valid exit inputs
    simulateUserInput("5\n0\n0\n0\n0\n");

    // Execute the listing function
    bool result = listingOfLocalVendors();

    // Clean up the environment
    resetStdinStdout();

    // Confirm that the function handled the situation correctly
    EXPECT_TRUE(result);
}




/**
 * @test AddVendorTEST
 * @brief Test case for adding a vendor.
 *
 * This test simulates user input for adding a new vendor named 'tugba'. It checks that the addVendor function
 * can handle and process the input correctly, leading to a successful addition. The test verifies that the
 * function returns true, which indicates that the vendor was added without errors.
 */
TEST_F(MarketTest, AddvendorTEST) {
    // Simulate user input for adding a new vendor
    simulateUserInput("tugba\n\n");

    // Call the function to add a vendor
    bool result = addVendor();

    // Reset standard input and output streams
    resetStdinStdout();

    // Assert that the function returns true, indicating success
    EXPECT_TRUE(result);
}

/**
 * @test UpdateVendorTEST
 * @brief Test case for updating a vendor.
 *
 * This test simulates updating an existing vendor with ID '123456' to have the name 'tugba'. It ensures
 * that the updateVendor function correctly processes the user input and updates the vendor's details.
 * The expected outcome is that the function returns true, signaling that the update operation was successful.
 */
TEST_F(MarketTest, UpdatevendorTEST) {
    // Simulate user input for updating a vendor
    simulateUserInput("123456\ntugba\n");

    // Call the function to update a vendor
    bool result = updateVendor();

    // Reset the streams
    resetStdinStdout();

    // Verify that the function successfully processes the update
    EXPECT_TRUE(result);
}


/**
 * @test DeleteVendorTEST
 * @brief Test case for deleting a vendor.
 *
 * This test checks the functionality of the deleteVendor function by simulating the deletion of a vendor
 * with ID '123456'. It tests the function's ability to handle user input for a deletion and to execute
 * the operation correctly. The test expects a return value of true, indicating the vendor was successfully deleted.
 */
TEST_F(MarketTest, DeletevendorTEST) {
    // Simulate user input for deleting a vendor
    simulateUserInput("123456\n\n");

    // Call the function to delete a vendor
    bool result = deleteVendor();

    // Clean up the environment
    resetStdinStdout();

    // Confirm that the function handled the deletion properly
    EXPECT_TRUE(result);
}


/**
 * @test ListVendorsTEST
 * @brief Test case for listing all vendors.
 *
 * This test verifies the functionality of the listVendors function. It simulates a user initiating
 * a vendor list operation and then exiting. The test ensures that the function can display the list
 * and handle an exit command effectively. The function should return true to indicate that it
 * completed successfully without any issues.
 */
TEST_F(MarketTest, ListVendorsTEST) {
    // Simulate user input for listing vendors and then exiting
    simulateUserInput("q\nx\n");

    // Execute the function to list all vendors
    bool result = listVendors();

    // Reset standard input and output
    resetStdinStdout();

    // Check that the function successfully completed the listing and handled the exit
    EXPECT_TRUE(result);
}


/**
 * @test ListingOfLocalProductsTEST
 * @brief Test case for listing all local products with an exit option.
 *
 * This test simulates the user selecting to exit immediately from the product listing menu.
 * It verifies that the listingOfLocalProducts function handles this input correctly and
 * returns true, indicating a successful exit without errors.
 */
TEST_F(MarketTest, ListingOfLocalProductsTEST) {
    // Simulate user input for exiting the listing
    simulateUserInput("0\n");

    // Execute the function to list local products
    bool result = listingOfLocalProducts();

    // Reset standard input and output streams
    resetStdinStdout();

    // Assert the function returns true, indicating success
    EXPECT_TRUE(result);
}



/**
 * @test ListingOfLocalProductsTEST2
 * @brief Test case for adding a product and then exiting the listing.
 *
 * This test simulates the user input to add a new product with specific details and then exit.
 * It ensures that the function can handle user input for adding a product followed by an exit command
 * and checks if the function completes successfully by returning true.
 */
TEST_F(MarketTest, ListingOfLocalProductsTEST2) {
    // Simulate user input for adding a product and exiting
    simulateUserInput("1\n123456\ntomato\n15\n150\nwinter\n0\n");

    // Execute the function to handle the input
    bool result = listingOfLocalProducts();

    // Reset the streams
    resetStdinStdout();

    // Verify that the function successfully handles the input and exits
    EXPECT_TRUE(result);
}


/**
 * @test ListingOfLocalProductsTEST3
 * @brief Test case for modifying a product and then exiting the listing.
 *
 * This test simulates user interactions for modifying an existing product's details and then exiting.
 * The function is expected to process these inputs properly and conclude by returning true, demonstrating
 * effective input handling and process completion.
 */
TEST_F(MarketTest, ListingOfLocalProductsTEST3) {
    // Simulate user input for modifying a product
    simulateUserInput("2\n123456\ntomato\n15\n150\nwinter\n0\n");

    // Execute the product listing function
    bool result = listingOfLocalProducts();

    // Clean up the environment
    resetStdinStdout();

    // Confirm the function handled the operation correctly
    EXPECT_TRUE(result);
}


/**
 * @test ListingOfLocalProductsTEST4
 * @brief Test case for filtering products and then exiting the listing.
 *
 * This test simulates applying a filter on the products (such as by type or location) and then exiting.
 * It tests the functionality to handle a filtered view and user exit properly by expecting a return value of true.
 */
TEST_F(MarketTest, ListingOfLocalProductsTEST4) {
    // Simulate user input for filtering products
    simulateUserInput("3\n123456\ntomato\n0\n");

    // Perform the listing operation
    bool result = listingOfLocalProducts();

    // Reset standard input and output
    resetStdinStdout();

    // Check that the function successfully completed the listing and handled the exit
    EXPECT_TRUE(result);
}


/**
 * @test ListingOfLocalProductsTEST5
 * @brief Test case for navigating through multiple menu options in the local products listing before exiting.
 *
 * This test challenges the function's ability to handle a sequence of navigation commands (e.g., paging through results)
 * and then exiting. It checks for correct function completion by expecting the return of true, which indicates successful execution.
 */
TEST_F(MarketTest, ListingOfLocalProductsTEST5) {
    // Simulate user input for advanced navigation and exiting
    simulateUserInput("4\n8\n0\n0\n4\n");

    // Call the function
    bool result = listingOfLocalProducts();

    // Reset streams
    resetStdinStdout();

    // Validate that the function managed the inputs correctly
    EXPECT_TRUE(result);
}

/**
 * @test ListingOfLocalProductsInvalidTEST
 * @brief Test case for handling invalid inputs in the local products listing.
 *
 * This test simulates the user entering an invalid option and then handling subsequent valid commands to exit.
 * It verifies that the listingOfLocalProducts function can handle unexpected or invalid inputs gracefully
 * and still process subsequent commands effectively, returning true as expected.
 */
TEST_F(MarketTest, ListingOfLocalProductsInvalidTEST) {
    // Simulate invalid and then valid exit inputs
    simulateUserInput("5\n0\n0\n4\n");

    // Execute the listing function
    bool result = listingOfLocalProducts();

    // Clean up the environment
    resetStdinStdout();

    // Confirm that the function handled the situation correctly
    EXPECT_TRUE(result);
}

/**
 * @test AddProductTEST
 * @brief Test case for adding a product to the system.
 *
 * This test prepares the environment by creating necessary vendor and product files, simulates the user input to add a new product,
 * and then checks that the product was correctly added to the product file. It verifies both the return value of the function and
 * the actual presence and correctness of the product data in the file, ensuring the add operation was successful.
 */
TEST_F(MarketTest, AddProductTEST) {
    // Setup test environment
    createTestVendorFile();
    createTestProductFile(); 

    // Simulate user input for adding a new product
    simulateUserInput("1\ntomato\n15\n150\nwinter\n");

    // Execute the addProduct function
    bool result = addProduct();

    // Reset standard I/O to clear any states
    resetStdinStdout();

    // Check the function return success
    EXPECT_TRUE(result);

    // Open the product file and check if the new product was added
    FILE* productFile = fopen("products.bin", "rb");
    ASSERT_NE(productFile, nullptr); 

    Product product;
    bool found = false;

    while (fread(&product, sizeof(Product), 1, productFile)) {
        // Eklenen ürünün özelliklerini kontrol et
        if (product.vendorId == 1 &&
            strcmp(product.productName, "tomato") == 0 &&
            product.price == 15.0f &&
            product.quantity == 150 &&
            strcmp(product.season, "winter") == 0) {
            found = true;
            break;
        }
    }

    fclose(productFile);

    // Confirm the product was added correctly
    EXPECT_TRUE(found);
}


/**
 * @test UpdateProductTEST
 * @brief Test case for updating a product's details.
 *
 * This test prepares by creating a product file, simulates user input to update an existing product, and then checks
 * that the product data was correctly updated in the product file. It ensures that the update operation modifies the
 * product details as expected and that these changes are reflected in the file.
 */
TEST_F(MarketTest, UpdateProductTEST) {
    createTestProductFile(); // Setup initial product data

    // Simulate user input for updating a product
    simulateUserInput("tomato\nupdated_tomato\n20\n200\nsummer\n");

    // updateProduct fonksiyonunu çağır
    bool result = updateProduct();

    // Clean up environment
    resetStdinStdout();

    // Verify function succeeded
    EXPECT_TRUE(result);

    // Check the product file for the updated data
    FILE* file = fopen("products.bin", "rb");
    Product product;
    int updated = 0;

    while (fread(&product, sizeof(Product), 1, file)) {
        if (strcmp(product.productName, "updated_tomato") == 0 &&
            product.price == 20.0f &&
            product.quantity == 200 &&
            strcmp(product.season, "summer") == 0) {
            updated = 1;
            break;
        }
    }
    fclose(file);

    // Confirm that the product was updated correctly
    EXPECT_TRUE(updated);
}


/**
 * @test UpdateProductNotFoundTEST
 * @brief Test case for attempting to update a non-existent product.
 *
 * This test verifies that when an attempt is made to update a product that does not exist, the system
 * handles it gracefully by not making any changes and still returning a success status, indicating
 * that the operation did not cause any errors.
 */
TEST_F(MarketTest, UpdateProductNotFoundTEST) {
    
    createTestProductFile(); // Setup initial product data

    // Simulate user input for a non-existent product
    simulateUserInput("nonexistent_product\n");

    // Capture standard output for any feedback messages
    testing::internal::CaptureStdout(); 
    bool result = updateProduct();
    std::string output = testing::internal::GetCapturedStdout(); 

    // Clean up environment
    resetStdinStdout();

    // Verify function handled non-existent product gracefully
    EXPECT_TRUE(result);

  
}

/**
 * @test DeleteProductTEST
 * @brief Test case for deleting a product from the system.
 *
 * This test creates a test environment with a product file, simulates user input to delete a specific product,
 * and then verifies that the product is no longer present in the file. It ensures that the delete operation
 * effectively removes the product data from the system.
 */
TEST_F(MarketTest, DeleteProductTEST) {
    
    createTestProductFile(); // Setup initial product data

    // Simulate user input for deleting a product
    simulateUserInput("tomato\n");

    // Execute the deleteProduct function
    bool result = deleteProduct();

    // Clean up environment
    resetStdinStdout();

    // Verify function succeeded
    EXPECT_TRUE(result);
    // Check the product file to ensure the product was deleted
    FILE* file = fopen("products.bin", "rb");
    Product product;
    int found = false;

    while (fread(&product, sizeof(Product), 1, file)) {
        if (strcmp(product.productName, "tomato") == 0) {
            found = true;
            break;
        }
    }
    fclose(file);
    // Confirm that the product was successfully deleted
    EXPECT_FALSE(found);
}


/**
 * @test DeleteProductNotFoundTEST
 * @brief Test case for attempting to delete a non-existent product.
 *
 * This test confirms that when a deletion is attempted for a product that does not exist,
 * the system does not crash or produce errors, and it properly indicates that no harmful
 * operations were performed.
 */
TEST_F(MarketTest, DeleteProductNotFoundTEST) {
   
    createTestProductFile();  // Setup initial product data

    // Simulate user input for a non-existent product
    simulateUserInput("nonexistent_product\n");

    // Capture standard output for any feedback messages
    testing::internal::CaptureStdout(); 
    bool result = deleteProduct();
    std::string output = testing::internal::GetCapturedStdout(); 

    // Clean up environment
    resetStdinStdout();

    // Verify function handled non-existent product gracefully
    EXPECT_TRUE(result);

   
}

/**
 * @test listingOfLocalVendorsandProductsTEST1
 * @brief Test case for interacting with the listing of local vendors and products with a specific menu option.
 *
 * This test simulates selecting a specific option in the listing menu, followed by an exit sequence. It checks if
 * the listingOfLocalVendorsandProducts function can handle a menu navigation followed by an exit, returning true
 * as a successful outcome.
 */
TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST1) {
    // Simulate selecting an option and exiting
    simulateUserInput("1\n\n0\n0\n4\n");

    bool result = listingOfLocalVendorsandProducts();

    resetStdinStdout();

    EXPECT_TRUE(result);
}


/**
 * @test listingOfLocalVendorsandProductsTEST2 to TEST8
 * @brief Test cases for interacting with the listing of local vendors and products using different menu options.
 *
 * These tests simulate the selection of various options in the menu for listing local vendors and products. They
 * aim to verify that the function can process each input correctly and return true, indicating that no errors occurred.
 */
TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST2) {
    // Simulate selecting an option and exiting
    simulateUserInput("2\n\n");

    bool result = listingOfLocalVendorsandProducts();

    resetStdinStdout();

    EXPECT_TRUE(result);
}

/**
 * @test listingOfLocalVendorsandProductsTEST3
 * @brief Test case for the third menu option in the listing of local vendors and products.
 *
 * This test simulates user interaction with the third menu option of the function. It verifies that
 * the listingOfLocalVendorsandProducts function can process the user input correctly and return true,
 * indicating successful handling and execution.
 */
TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST3) {
    // Simulate user input for selecting the third menu option and exiting
    simulateUserInput("3\n\n");

    bool result = listingOfLocalVendorsandProducts();

    resetStdinStdout();

    EXPECT_TRUE(result);
}


/**
 * @test listingOfLocalVendorsandProductsTEST4
 * @brief Test case for the fourth menu option in the listing of local vendors and products.
 *
 * This test evaluates the function's ability to handle the fourth option, checking whether it can process
 * this input correctly and confirm that the operation was completed successfully by returning true.
 */
TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST4) {
    // Simulate user input for the fourth option and subsequent exit
    simulateUserInput("4\n\n");

    bool result = listingOfLocalVendorsandProducts();

    resetStdinStdout();

    EXPECT_TRUE(result);
}

/**
 * @test listingOfLocalVendorsandProductsTEST5
 * @brief Test case for the fifth menu option in the listing of local vendors and products.
 *
 * This test checks the function's response to the fifth menu option. It ensures that the system can
 * handle this input appropriately and returns true, indicating a flawless operation without any errors.
 */
TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST5) {
    // Simulate user interaction with the fifth menu option
    simulateUserInput("5\n\n");

    bool result = listingOfLocalVendorsandProducts();

    resetStdinStdout();

    EXPECT_TRUE(result);
}

/**
 * @test listingOfLocalVendorsandProductsTEST6
 * @brief Test case for the sixth menu option in the listing of local vendors and products.
 *
 * This test simulates the selection of the sixth menu option, aiming to confirm that the function
 * processes the input effectively and returns true, thus managing the user interaction successfully.
 */
TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST6) {
    // Simulate user selecting the sixth option and exiting
    simulateUserInput("6\n\n");

    bool result = listingOfLocalVendorsandProducts();

    resetStdinStdout();

    EXPECT_TRUE(result);
}

/**
 * @test listingOfLocalVendorsandProductsTEST7
 * @brief Test case for the seventh menu option in the listing of local vendors and products.
 *
 * This test verifies that the function handles the seventh option correctly, processing the input
 * without errors and returning true, which would indicate successful user input handling.
 */
TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST7) {
    // Simulate the selection of the seventh menu option and exiting
    simulateUserInput("7\n\n");
    
    bool result = listingOfLocalVendorsandProducts();

    resetStdinStdout();

    EXPECT_TRUE(result);
}


/**
 * @test listingOfLocalVendorsandProductsTEST8
 * @brief Test case for the eighth menu option in the listing of local vendors and products.
 *
 * This test assesses the function's ability to manage the eighth menu option. It checks for the correct handling
 * of the input and expects a true return value, signaling successful execution.
 */
TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST8) {
    // Simulate user interaction with the eighth menu option
    simulateUserInput("8\n\n");

    bool result = listingOfLocalVendorsandProducts();

    resetStdinStdout();

    EXPECT_TRUE(result);
}


/**
 * @test ListingOfLocalVendorsAndProductsInvalidStrategyTEST
 * @brief Test case for attempting to use an invalid strategy in the listing of local vendors and products.
 *
 * This test sets up necessary vendor and product files, then simulates an invalid input scenario
 * where a non-existent menu option is selected. It checks if the listingOfLocalVendorsandProducts function
 * handles this invalid input by returning false, indicating an unsuccessful or erroneous execution.
 */
TEST_F(MarketTest, ListingOfLocalVendorsAndProductsInvalidStrategyTEST) {
    createTestVendorFile();  // Prepare vendor data for the test
    createTestProductFile(); // Prepare product data for the test

    // Simulate selecting a non-existent menu option
    simulateUserInput("11\n");

    bool result = listingOfLocalVendorsandProducts();

    resetStdinStdout();

    // Verify that the function correctly handles the error by returning false
    EXPECT_FALSE(result);
}



/**
 * @test marketHoursAndLocationsTEST
 * @brief Test case for displaying market hours and locations.
 *
 * This test checks the functionality of the marketHoursAndLocations function by simulating an immediate exit.
 * It verifies whether the function can handle a simple user input to exit without performing any action and return true,
 * indicating successful handling of the input.
 */
TEST_F(MarketTest, marketHoursAndLocationsTEST) {
    // Simulate immediate exit input
    simulateUserInput("0\n");
    // Call the function to display market hours and locations
    bool result = marketHoursAndLocations;

    // Clean up the environment
    resetStdinStdout();

    // Check if the function returns true as expected
    EXPECT_TRUE(result);
}

/**
 * @test marketHoursAndLocationTest1
 * @brief Test case for adding or updating market hours and locations.
 *
 * This test simulates the addition or update of market hours and location details by the user.
 * It verifies that the marketHoursAndLocations function can correctly process valid inputs to add
 * or update a market's details and concludes successfully by returning true.
 */
TEST_F(MarketTest, marketHoursAndLocationTest1) {
    // Simulate user input for adding/updating a market
    simulateUserInput("1\n108750\nmonday\n09:00 - 18:00\ntrabzon\n0\n");

    // Call the function
    bool result = marketHoursAndLocations();

    // Reset the environment
    resetStdinStdout();

    // Ensure the function handles the input correctly
    EXPECT_TRUE(result);
}


/**
 * @test marketHoursAndLocationTest2
 * @brief Test case for updating specific market hours and location.
 *
 * This test simulates updating market hours and location details for a specific market.
 * It aims to confirm that the function can accept detailed modifications and effectively update the market's
 * information, returning true to indicate that the process was executed without errors.
 */
TEST_F(MarketTest, marketHoursAndLocationTest2) {
    // Simulate detailed input for updating market hours
    simulateUserInput("2\n108750\ntuesday\n09:00 - 17:00\nrize\n0\n");

    // Invoke the function
    bool result = marketHoursAndLocations();

    // Clean up input/output states
    resetStdinStdout();

    // Validate successful input handling and function execution
    EXPECT_TRUE(result);
}


/**
 * @test marketHoursAndLocationTest3
 * @brief Test case for exiting from the market hours and location menu.
 *
 * This test ensures that the marketHoursAndLocations function can handle an exit command without
 * any user modifications to market data, and return true to signify a clean and error-free exit.
 */
TEST_F(MarketTest, marketHoursAndLocationTest3) {
    // Simulate user selecting to exit the function
    simulateUserInput("3\n0\n");

    // Execute the function
    bool result = marketHoursAndLocations();

    // Reset system states
    resetStdinStdout();

    // Check for a successful function outcome
    EXPECT_TRUE(result);
}

/**
 * @test marketHoursAndLocationTestInvalid
 * @brief Test case for handling invalid input in the market hours and location menu.
 *
 * This test simulates an invalid menu option selection to verify that the marketHoursAndLocations function
 * can gracefully handle unexpected or incorrect inputs by returning true, thereby maintaining robustness
 * and preventing crashes or unexpected behavior.
 */
TEST_F(MarketTest, marketHoursAndLocationTestInvalid) {
    // Simulate an invalid menu option selection
    simulateUserInput("787\n0\n");

    // Call the function to test its robustness
    bool result = marketHoursAndLocations();

    // Clear any changes to standard input/output
    resetStdinStdout();

    // Confirm the function successfully managed the incorrect input
    EXPECT_TRUE(result);
}


/**
 * @test SearchProductsOrEnterKeywordTEST
 * @brief Test case for initiating a search for products or entering a keyword.
 *
 * This test simulates user interaction with the searchProductsOrEnterKeyword function by providing
 * an exit command as input. It verifies that the function handles the input correctly and concludes
 * the process without issues, indicated by returning true.
 */ 
TEST_F(MarketTest, SearchProductsOrEnterKeywordTEST) {
    // Simulate user input for exiting the search function
    simulateUserInput("0\n");
    // Execute the function
    bool result = searchProductsOrEnterKeyword();

    // Reset standard input and output streams
    resetStdinStdout();

    // Validate that the function returns true, indicating a successful interaction
    EXPECT_TRUE(result);
}


/**
 * @test EnterSearchProductsTEST
 * @brief Test case for searching products by entering a specific product name.
 *
 * This test simulates user input for a product search by entering the name of a product ("tomato").
 * It aims to verify that the enterSearchProducts function processes this input and successfully
 * completes the search, which is confirmed by the function returning true.
 */
TEST_F(MarketTest, EnterSearchProductsTEST) {
    // Simulate user input for searching a specific product
    simulateUserInput("tomato\n");
    // Call the function to search for products
    bool result = enterSearchProducts;

    // Reset the environment to its original state
    resetStdinStdout();

    // Ensure the function handles the search correctly and returns true
    EXPECT_TRUE(result);
}


/**
 * @test EnterKeywordsTEST
 * @brief Test case for entering keywords to filter or search for related content.
 *
 * This test simulates user input for entering a keyword ("winter") to filter or search content.
 * It checks that the enterKeywords function can handle the keyword entry properly and returns true,
 * indicating the successful acceptance and processing of the keyword.
 */
TEST_F(MarketTest, EnterKeywordsTEST) {
    // Simulate user input for entering a keyword
    simulateUserInput("winter\n");
    // Call the function to process the keyword
    bool result = enterKeywords;

    // Clear any input/output residue
    resetStdinStdout();

    // Confirm that the function returns true, signaling successful keyword processing
    EXPECT_TRUE(result);
}


/**
 * @test SaveUserToHuffFileTEST
 * @brief Test case for saving a user's details to a Huffman-encoded file.
 *
 * This test verifies the functionality of the saveUserToHuffFile function by attempting to save
 * a user's username and password. It ensures that the user's details are encoded and saved correctly,
 * as indicated by the function's return value of true, denoting a successful save operation.
 */
TEST_F(MarketTest, SaveUserToHuffFileTEST) {
    // Define a username
    const char* username = "testUser";
    // Define a password
    const char* password = "password123";
    // Execute the function to save the user details
    bool result = saveUserToHuffFile(username, password);

    // Check if the save operation was successful
    EXPECT_TRUE(result);
}

/**
 * @test userAuthenticationTEST
 * @brief Test case for user authentication.
 *
 * This test simulates a user entering correct login credentials (username and password) to verify
 * that the userAuthentication function correctly handles valid inputs and successfully authenticates the user.
 * It confirms that the function returns true, indicating successful authentication.
 */
TEST_F(MarketTest, userAuthenticationTEST) {
    // Simulate valid login credentials and exit inputs
    simulateUserInput("1\ntestUser\npassword123\n0\n0\n4\n");

    // Call the function to authenticate the user
    bool result = userAuthentication();

    // Reset standard input and output streams
    resetStdinStdout();

    // Assert that authentication was successful
    EXPECT_TRUE(result);
}


/**
 * @test userAuthenticationTEST2
 * @brief Test case for user authentication with different credentials.
 *
 * This test checks the user authentication system with a different set of credentials, simulating a scenario where a user
 * logs in using a different username and password. It aims to verify that the userAuthentication function
 * can correctly process varying inputs and still return true, denoting successful authentication.
 */
TEST_F(MarketTest, userAuthenticationTEST2) {
    // Simulate a different user's credentials and exit sequence
    simulateUserInput("2\nnewUser\nnewpassword\n0\n0\n4\n");

    // Call the authentication function
    bool result = userAuthentication();

    // Clear any changes to the I/O streams
    resetStdinStdout();

    // Check that the function correctly processes the input and authenticates the user
    EXPECT_TRUE(result);
}

/**
 * @test LoginUserTEST
 * @brief Test case for logging in a user with correct credentials.
 *
 * This test simulates the login process by providing the username and password for an existing user.
 * It tests whether the loginUser function can successfully authenticate a user and return true, thus verifying
 * that the user's login information is correctly processed and validated.
 */
TEST_F(MarketTest, LoginUserTEST) {
    // Simulate entering valid user credentials
    simulateUserInput("testUser\npassword123\n");

    // Invoke the login function
    bool result = loginUser();

    // Reset the environment to its original state
    resetStdinStdout();

    // Ensure the function validates the credentials correctly
    EXPECT_TRUE(result);
}


/**
 * @test RegisterUserTEST
 * @brief Test case for registering a new user.
 *
 * This test simulates the registration of a new user by entering a username and password.
 * It verifies that the registerUser function can handle the registration process properly, adding the new user
 * to the system, and returning true, indicating that the registration was successful.
 */
TEST_F(MarketTest, RegisterUserTEST) {
    // Simulate entering new user registration details
    simulateUserInput("newUser\nnewPassword\n");

    // Call the function to register a new user
    bool result = registerUser();

    // Clean up the input/output states
    resetStdinStdout();

    // Confirm that the registration process was successfully completed
    EXPECT_TRUE(result);
}

/**
 * @test PriceComparisonTEST
 * @brief Test case for verifying basic price comparison functionality.
 *
 * This test simulates a user choosing to exit the price comparison menu immediately.
 * It checks if the priceComparison function handles the exit input correctly and terminates
 * the operation successfully, returning true as an indicator of proper function execution.
 */
TEST_F(MarketTest, PriceComparisonTEST) {
    // Simulate immediate exit input
    simulateUserInput("0\n");

    // Call the function to perform price comparison
    bool result = priceComparison();

    // Clear changes to the I/O streams
    resetStdinStdout();

    // Assert that the function handled the input correctly
    EXPECT_TRUE(result);
}

/**
 * @test PriceComparisonTEST2
 * @brief Test case for executing a specific product price comparison.
 *
 * This test simulates the user input for comparing the price of a specific product ('tomato').
 * It validates that the priceComparison function can process this input and successfully complete
 * the comparison process, returning true to indicate no errors during execution.
 */
TEST_F(MarketTest, PriceComparisonTEST2) {
    // Simulate user input for price comparison of 'tomato'
    simulateUserInput("1\ntomato\n0\n0\n4\n");

    // Execute the price comparison
    bool result = priceComparison();

    // Reset standard input and output
    resetStdinStdout();

    // Check that the function successfully processes the input
    EXPECT_TRUE(result);
}

/**
 * @test PriceComparisonTEST3
 * @brief Test case for performing a price comparison using another set of inputs.
 *
 * This test simulates a user performing a price comparison without specifying a particular product,
 * possibly indicating a general comparison across categories. The function is expected to handle this input
 * effectively and return true, signaling successful operation.
 */
TEST_F(MarketTest, PriceComparisonTEST3) {
    // Simulate a general input for price comparison
    simulateUserInput("2\n\n0\n0\n4\n");

    // Invoke the price comparison functionality
    bool result = priceComparison();

    // Clean up the input/output states
    resetStdinStdout();

    // Verify successful handling of the input
    EXPECT_TRUE(result);
}

/**
 * @test PriceComparisonInvalidTEST4
 * @brief Test case for price comparison with invalid product or category ID.
 *
 * This test simulates user input of an invalid product or category ID to test how the priceComparison
 * function handles incorrect or non-existent data. It aims to verify that even with invalid inputs,
 * the function manages to conclude gracefully and returns true, maintaining robustness against user errors.
 */
TEST_F(MarketTest, PriceComparisonInvalidTEST4) {
    // Simulate input of an invalid product/category ID
    simulateUserInput("675768\n0\n0\n4\n");

    // Call the price comparison function
    bool result = priceComparison();

    // Reset the environment to its original state
    resetStdinStdout();

    // Confirm the function handles invalid inputs gracefully
    EXPECT_TRUE(result);
}

/**
 * @test SelectProductTEST
 * @brief Test case for selecting a product by name.
 *
 * This test simulates user input to select a product by its name ("tomato"). It checks if the selectProduct
 * function can correctly identify and select the product based on the input provided. The function should
 * return true, indicating that the product was successfully selected.
 */
TEST_F(MarketTest, SelectProductTEST) {
    // Simulate user input for product selection
    simulateUserInput("tomato\n");

    // Buffer to store selected product name
    char selectedProductName[100] = "";

    // Call the function to select the product
    bool result = selectProduct(selectedProductName);

    // Clear any changes to the input/output streams
    resetStdinStdout();

    // Validate the selection was successful
    EXPECT_TRUE(result);
}

/**
 * @test ComparePricesByNameTest
 * @brief Test case for comparing the prices of a specific product across different vendors.
 *
 * This test first sets up a product file with predefined products, including multiple entries for "Tomato"
 * with different prices and quantities. It simulates user input to select "Tomato" for a price comparison and
 * invokes the comparePricesByName function to perform the operation. The test verifies that the function
 * successfully retrieves and compares prices for all "Tomato" entries in the product file, and it checks
 * that the prices are sorted correctly in ascending order, confirming that the function operates as expected.
 *
 * The test ensures that:
 * - The function handles the input correctly and returns true, indicating a successful comparison.
 * - The prices are sorted as expected, validating the correctness of the sorting algorithm within the function.
 */
TEST_F(MarketTest, ComparePricesByNameTest) {
    // Prepare the product file with predefined data
    createTestProductFile();

    // Simulate user input to select "Tomato" for price comparisone
    simulateUserInput("Tomato\n");

    // Execute the price comparison function
    bool result = comparePricesByName("Tomato");

    // Clean up the environment
    resetStdinStdout();

    // Verify that the function returned true, indicating success
    EXPECT_TRUE(result);

    // Check the sorted product prices against expected values
    Product expectedProducts[] = {
        // Expected first result with the lowest price
        {1, "Tomato", 20, 200, "Winter"},
        // Expected second result with a higher price
        {2, "Tomato", 25, 100, "Winter"},
    };

    // Verify the correct order and price of the products returned
    EXPECT_EQ(expectedProducts[0].price, 20); // Check if the first product's price is as expected
    EXPECT_EQ(expectedProducts[1].price, 25); // Check if the second product's price is as expected
}

/**
 * @test enterSearchProductsTEST
 * @brief Test case for entering search terms to find products.
 *
 * This test simulates user input for a product search by name ("banana"). It validates that the enterSearchProducts
 * function can handle the input correctly and return true, indicating a successful search process.
 */
TEST_F(MarketTest, enterSearchProductsTEST) {
    // Simulate user input for searching a product
    simulateUserInput("banana\n0\n0\n4\n");

    // Call the function to perform product search
    bool result = enterSearchProducts();

    // Reset standard input and output
    resetStdinStdout();

    // Confirm the search was handled correctly
    EXPECT_TRUE(result);
}

/**
 * @test enterKeywordsTEST
 * @brief Test case for entering keywords to filter search results.
 *
 * This test simulates user input for entering a keyword ("banana"). It checks if the enterKeywords
 * function processes this input properly and returns true, indicating successful keyword entry and handling.
 */
TEST_F(MarketTest, enterKeywordsTEST) {
    // Simulate user input for keyword entry
    simulateUserInput("banana\n0\n0\n4\n");

    // Call the function to handle keyword entry
    bool result = enterKeywords();

    // Clear any changes to input/output
    resetStdinStdout();

    // Ensure the keyword entry was successful
    EXPECT_TRUE(result);
}

/**
 * @test searchProductsOrEnterKeywordInvalidTEST
 * @brief Test case for handling invalid input in product search or keyword entry.
 *
 * This test simulates invalid user input scenarios for searching products or entering keywords. It aims to test
 * the robustness of the searchProductsOrEnterKeyword function in handling incorrect inputs and still returning true,
 * indicating that no system errors occurred.
 */
TEST_F(MarketTest, searchProductsOrEnterKeywordInvalidTEST) {
    // Simulate invalid input scenario
    simulateUserInput("5\n0\n0\n0\n4\n");

    // Call the function
    bool result = searchProductsOrEnterKeyword();

    // Reset input/output
    resetStdinStdout();

    // Verify the function handles invalid input correctly
    EXPECT_TRUE(result);
}

/**
 * @test enterSearchProductsTEST2
 * @brief Test case for entering a product name in the search function.
 *
 * This test simulates user input to search for a specific product ("banana") using the
 * searchProductsOrEnterKeyword function. It checks whether the function can handle the
 * simulated input correctly and return true, indicating a successful search operation.
 * The purpose is to verify that the product search functionality processes the input
 * as expected and identifies relevant product data accurately.
 */
TEST_F(MarketTest, enterSearchProductsTEST2) {
    // Simulate user input for searching a product
    simulateUserInput("1\nbanana\n0\n0\n4\n");

    // Call the function to perform the search
    bool result = searchProductsOrEnterKeyword();

    // Reset the environment to clear any input/output residues
    resetStdinStdout();

    // Assert the function returns true, indicating the search was successful
    EXPECT_TRUE(result);
}

/**
 * @test enterKeywordsTEST2
 * @brief Test case for entering a keyword to filter or search for related products.
 *
 * This test simulates user input for entering a keyword ("banana") in the searchProductsOrEnterKeyword
 * function. It evaluates the function's ability to handle keyword entry effectively and return true,
 * confirming that the keyword was accepted and processed correctly. The test aims to ensure that the
 * keyword search functionality is robust and can accurately filter or locate products based on the keyword provided.
 */
TEST_F(MarketTest, enterKeywordsTEST2) {
    // Simulate user input for entering a keyword
    simulateUserInput("2\nbanana\n0\n0\n4\n");

    // Call the function to handle the keyword entry
    bool result = searchProductsOrEnterKeyword();

    // Clear changes to the input/output state
    resetStdinStdout();

    // Validate that the function processed the keyword correctly
    EXPECT_TRUE(result);
}

/**
 * @test minheapfyTEST
 * @brief Test case for verifying the minHeapify function's correctness.
 *
 * This test initializes a MinHeap structure with a set of nodes, each assigned descending frequency values.
 * The test then calls minHeapify to ensure the function properly organizes the heap according to the min-heap property.
 * It verifies that the root node has the smallest frequency, indicating a successful heapification.
 */
TEST_F(MarketTest, minheapfyTEST) {
    // Placeholder for user interaction
    simulateUserInput("\n");
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 5;
    minHeap->capacity = 5;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));

    
    for (int i = 0; i < minHeap->size; i++) {
        struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
        node->freq = (minHeap->size - i) * 10; 
        minHeap->array[i] = node;
    }
    int smallest = 0;
    
    bool result = minHeapify(minHeap, 0);

    // Clear changes to the input/output state
    resetStdinStdout();

    // Validate that the function processed the keyword correctly
    EXPECT_TRUE(result);
}

/**
 * @test insertMinheapifyTEST
 * @brief Test case for verifying the insert function in a MinHeap.
 *
 * This test initializes an empty MinHeap and inserts a new node with a specific frequency.
 * It checks if the insertMinHeap function correctly adds the node while maintaining the heap property.
 */
TEST_F(MarketTest, insertMinheapifyTEST) {
    
    simulateUserInput("\n");
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0; 
    minHeap->capacity = 5;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));

    
    struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    minHeapNode->freq = 15; 

    for (int i = 0; i < minHeap->size; i++) {
        struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
        node->freq = (minHeap->size - i) * 10; 
        minHeap->array[i] = node;
    }
    
    bool result = insertMinHeap(minHeap,minHeapNode);

    resetStdinStdout();

    EXPECT_TRUE(result);
}

/**
 * @test buildHuffmanTreeTEST
 * @brief Test case for building a Huffman Tree from given frequencies.
 *
 * This test uses a set of characters and their frequencies to build a Huffman Tree.
 * It verifies that the Huffman Tree is correctly constructed by checking that the root node
 * has a frequency equal to the sum of all frequencies and that it has valid left and right children.
 */
TEST_F(MarketTest, buildHuffmanTreeTEST) {
    
    char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(data) / sizeof(data[0]);

    struct MinHeapNode* huffmanTreeRoot = buildHuffmanTree(data, freq, size);

    EXPECT_NE(huffmanTreeRoot, nullptr);
    EXPECT_EQ(huffmanTreeRoot->freq, 100); 

    EXPECT_NE(huffmanTreeRoot->left, nullptr);
    EXPECT_NE(huffmanTreeRoot->right, nullptr);

}

/**
 * @test DebugHuffmanCodesTest
 * @brief Test case for generating and printing Huffman Codes.
 *
 * This test uses a set of characters and their frequencies to generate Huffman Codes.
 * It aims to verify that HuffmanCodes function can process the data and output the correct Huffman codes.
 */
TEST_F(MarketTest, DebugHuffmanCodesTest) {
    char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(data) / sizeof(data[0]);

    HuffmanCodes(data, freq, size);
}


/**
 * @test listProductsByVendorTEST
 * @brief Test case for listing products associated with a specific vendor ID.
 *
 * This test simulates a scenario where a specific vendor's products are listed.
 * It verifies that the listProductsByVendor function correctly identifies and lists all products for the given vendor ID.
 */
TEST_F(MarketTest, listProductsByVendorTEST) {
    int testVendorId = 1;

    testing::internal::CaptureStdout();

    bool result = listProductsByVendor(testVendorId);

    EXPECT_TRUE(result);

}

/**
 * @test heapifyTEST
 * @brief Test case for verifying the heapify function on a custom array of products.
 *
 * This test initializes an array of Product structures and performs a heapify operation.
 * It checks if the heapify function can rearrange the elements correctly according to the heap property
 * based on product prices.
 */
TEST_F(MarketTest, heapifyTEST) {

    simulateUserInput("\n");

    struct Product arr[5] = {
        
    };

    int i = 0; 
    int n = 5; 
    
    int largest = 0; 
    int left = 2 * i + 1;
    int right = 2 * i + 2; 

    if (left < n && arr[left].price > arr[largest].price)
        largest = left;

    if (right < n && arr[right].price > arr[largest].price)
        largest = right;

    bool result = heapify(arr,1,1);

    resetStdinStdout();

    EXPECT_TRUE(result);
}

/**
 * @test ProgressiveOverflowSearchTEST
 * @brief Test case for checking the search functionality within an overflow area.
 *
 * This test simulates a scenario where specific entries in an overflow area are set to be occupied with certain keys.
 * It then tests the search functionality to ensure that it correctly identifies when keys are not present.
 * The test verifies that:
 * - A search for a non-existent key returns false, indicating the key is not found.
 * - A search in an unoccupied area also returns false, confirming the absence of the key.
 */
TEST_F(MarketTest, ProgressiveOverflowSearchTEST) {
    // Prepare the overflow area with default settings: unoccupied.
    for (int i = 0; i < OVERFLOW__SIZE; i++) {
        overflowAreaa[i].isOccupied = false;
        overflowAreaa[i].key = 0;
    }

    // Set specific entries as occupied to simulate existing data.
    overflowAreaa[3].isOccupied = true;
    overflowAreaa[3].key = 42;

    overflowAreaa[7].isOccupied = true;
    overflowAreaa[7].key = 99;


    // Expect that searching for a non-existing key returns false.
    EXPECT_FALSE(progressiveOverflowSearch(100));

    // Test that searching for a key in an unoccupied index returns false.
    EXPECT_FALSE(progressiveOverflowSearch(50));
}

/**
 * @test LoginUserInvalidCredentialsTEST
 * @brief Test case for attempting to login with incorrect credentials.
 *
 * This test simulates an attempt to login with a wrong username and password.
 * It checks if the loginUser function appropriately handles incorrect credentials by returning false,
 * indicating the authentication failure.
 */
TEST_F(MarketTest, LoginUserInvalidCredentialsTEST) {
    // Simulate user input for wrong credentials
    simulateUserInput("wrongUser\nwrongPassword\n");

    // Attempt to login with the provided credentials
    bool result = loginUser();

    // Reset standard I/O to clear any residual data
    resetStdinStdout();

    // Verify the login attempt was unsuccessful
    EXPECT_FALSE(result);
}

/**
 * @test ListVendorsElseCasesTEST
 * @brief Test case for the vendor listing functionality, focusing on edge cases.
 *
 * This test checks the listVendors function's behavior when faced with invalid navigation commands.
 * It simulates incorrect inputs and ensures that the function still operates correctly without crashing
 * and can handle erroneous user inputs gracefully, continuing to process further valid commands.
 */
TEST_F(MarketTest, ListVendorsElseCasesTEST) {
    // Open a file for writing vendor data
    FILE* file = fopen("vendor.bin", "wb");

    // Define a sample vendor
    Vendor v1 = { 1, "Vendor1" };

    // Write the vendor data to file
    fwrite(&v1, sizeof(Vendor), 1, file);

    // Close the file
    fclose(file);

    // Simulate invalid input followed by 'next' and 'exit' commands.
    simulateUserInput("z\nn\nx\n");

    // Call the function to list vendors.
    bool result = listVendors();

    // Reset standard input/output to clear any buffered data.
    resetStdinStdout();

    // Check that the function still returns true despite incorrect inputs.
    EXPECT_TRUE(result);

}

/**
 * @test AddMarketHoursAndLocationTEST
 * @brief Tests adding market hours and location for a valid vendor ID.
 *
 * This test prepares a scenario where the vendor file is pre-populated with valid entries. It simulates user input for
 * adding market hours and location details, including a specific vendor ID, day, working hours, and location name.
 * The test verifies that the addMarketHoursAndLocation function successfully adds these details to the 'marketHours.bin' file
 * and checks if the new entry exists as expected.
 */
TEST_F(MarketTest, AddMarketHoursAndLocationTEST) {
    // Setup test vendor file with valid entries.
    createTestVendorFile();

    // Simulate user input for adding market hours.
    simulateUserInput("1\nmonday\n09:00 - 18:00\nMainStreet\n");

    // Invoke function to add market hours.
    bool result = addMarketHoursAndLocation();

    // Cleanup standard input and output.
    resetStdinStdout();

    // Ensure function succeeded.
    EXPECT_TRUE(result);

    // Verify the newly added market hours in the file.
    FILE* file = fopen("marketHours.bin", "rb");
    ASSERT_NE(file, nullptr); // Ensure the file opened successfully.

    MarketHours market;
    int found = 0;

    while (fread(&market, sizeof(MarketHours), 1, file)) {
        if (market.id == 1 &&
            strcmp(market.day, "monday") == 0 &&
            strcmp(market.hours, "09:00 - 18:00") == 0 &&
            strcmp(market.location, "MainStreet") == 0) {
            found = 1;
            break;
        }
    }
    fclose(file);

    // Confirm the correct entry was added.
    EXPECT_TRUE(found);
}

/**
 * @test AddMarketHoursAndLocationInvalidTEST
 * @brief Tests adding market hours and location with an invalid vendor ID.
 *
 * This test prepares a vendor file without the vendor ID that will be tested, simulates input for an invalid vendor ID,
 * and checks if the addMarketHoursAndLocation function correctly rejects the entry, returning false.
 */
TEST_F(MarketTest, AddMarketHoursAndLocationInvalidTEST) {
    
    // Setup a vendor file without the ID to be tested.
    createTestVendorFile(); 

    // Simulate input for an invalid vendor ID.
    simulateUserInput("999\n");

    // Attempt to add market hours with invalid ID.
    bool result = addMarketHoursAndLocation();

    // Cleanup input and output.
    resetStdinStdout();

    // Check that the function correctly rejected the invalid ID.
    EXPECT_FALSE(result);

}

/**
 * @test UpdateMarketHoursAndLocationTEST
 * @brief Tests updating existing market hours and location.
 *
 * This test initializes a file with market hours, simulates user input to update one entry, and checks
 * if the updateMarketHoursAndLocation function successfully updates the entry. It verifies the contents
 * of the updated entry to ensure the update was applied correctly.
 */
TEST_F(MarketTest, UpdateMarketHoursAndLocationTEST) {
    // Create and populate initial data.
    FILE* file = fopen("marketHours.bin", "wb");
    ASSERT_NE(file, nullptr) << "Failed to create test marketHours.bin file";

    MarketHours initialData[] = {
        {1, "monday", "09:00 - 18:00", "OldStreet"},
        {2, "tuesday", "10:00 - 19:00", "NewStreet"}
    };
    fwrite(initialData, sizeof(MarketHours), 2, file);
    fclose(file);

    // Simulate updating market hours.
    simulateUserInput("1\nwednesday\n08:00 - 17:00\nUpdatedStreet\n");

    // Call update function
    bool result = updateMarketHoursAndLocation();

    // Cleanup.
    resetStdinStdout();

    EXPECT_TRUE(result);

    // Reopen file to verify update.
    file = fopen("marketHours.bin", "rb");
    ASSERT_NE(file, nullptr) << "Failed to open marketHours.bin file for verification";

    MarketHours updatedData;
    int found = 0;

    while (fread(&updatedData, sizeof(MarketHours), 1, file)) {
        if (updatedData.id == 1) {
            EXPECT_STREQ(updatedData.day, "wednesday") << "Day field did not update correctly";
            EXPECT_STREQ(updatedData.hours, "08:00 - 17:00") << "Hours field did not update correctly";
            EXPECT_STREQ(updatedData.location, "UpdatedStreet") << "Location field did not update correctly";
            found = 1;
            break;
        }
    }
    fclose(file);

    // Ensure the correct record was updated.
    EXPECT_TRUE(found) << "Updated MarketHours record not found in file";
}

/**
 * @test UpdateMarketHoursAndLocationInvalidID
 * @brief Tests attempting to update market hours for a non-existent vendor ID.
 *
 * Initializes the necessary files, simulates user input for a non-existent vendor ID, and checks if the
 * updateMarketHoursAndLocation function fails gracefully, returning false and not altering any data.
 */
TEST_F(MarketTest, UpdateMarketHoursAndLocationInvalidID) {
    // Setup a file with valid entries.
    createTestMarketHoursFile();

    // Simulate input for a non-existent vendor ID.
    simulateUserInput("999\n");

    // Attempt to update market hours for invalid ID.
    bool result = updateMarketHoursAndLocation();

    // Cleanup.
    resetStdinStdout();

    // Ensure the function returns false.
    EXPECT_TRUE(result);
}



/**
 * @test HashFunctionTest
 * @brief Tests the correctness of a hash function by ensuring it returns the expected hash index.
 *
 * This test verifies that the hash function computes the correct hash value based on the modulo operation
 * with the TABLE_SIZE. The expected outcome is that the actual hash matches the expected hash, confirming
 * the hash function's reliability.
 */
TEST_F(MarketTest, HashFunctionTest) {
    // The input key for the hash function.
    int key = 42;
    // The expected hash value computed using modulo.
    int expectedHash = key % TABLE_SIZE;

    // Execute the hash function.
    int actualHash = hashFunction(key);

    // Verify if the computed hash is as expected.
    EXPECT_EQ(actualHash, expectedHash);
}

/**
 * @test InitializeHashTableTest
 * @brief Tests the initialization of a hash table to ensure all entries are set to unoccupied.
 *
 * This test checks that each slot in the hash table and overflow area is initialized correctly to unoccupied,
 * ensuring the hash table is correctly set up for further operations like insertions and searches.
 */
TEST_F(MarketTest, InitializeHashTableTest) {
    // Call the initialization function.
    initializeHashTable();

    for (int i = 0; i < TABLE_SIZE; i++) {
        // Check each main table slot is unoccupied.
        EXPECT_EQ(hashTable[i].isOccupied, 0);
        // Ensure product count in buckets is zero.
        EXPECT_EQ(hashTableBuckets[i].productCount, 0);
    }

    // Verify each overflow area slot is unoccupied.
    for (int i = 0; i < OVERFLOW_SIZE; i++) {
        EXPECT_EQ(overflowArea[i].isOccupied, 0);
    }
}

/**
 * @test LinearProbingTest
 * @brief Tests linear probing function to ensure it calculates the correct index for collision resolution.
 *
 * This test inputs a key and a probe increment to calculate the expected new index using linear probing
 * method. It checks whether the calculated index matches the expected, validating the linear probing mechanism.
 */
TEST_F(MarketTest, LinearProbingTest) {
    // Test key value.
    int key = 42;
    // Probe increment.
    int probe = 1;
    // Expected index after probing.
    int expectedIndex = (key + probe) % TABLE_SIZE;

    // Execute linear probing.
    int actualIndex = linearProbing(key, probe);

    // Verify the resulting index is correct.
    EXPECT_EQ(actualIndex, expectedIndex);
}

/**
 * @test QuadraticProbingTest
 * @brief Tests quadratic probing function to ensure it correctly calculates the new index based on quadratic increments.
 *
 * Quadratic probing is tested by providing a key and a probe value, then calculating the expected index using
 * a quadratic formula. This verifies that quadratic probing can handle collisions by checking the index calculation.
 */
TEST_F(MarketTest, QuadraticProbingTest) {
    int key = 42; // Test key value.
    int probe = 2; // Probe increment, squared in the index calculation.
    // Expected index after quadratic probing.
    int expectedIndex = (key + probe * probe) % TABLE_SIZE;

    // Execute quadratic probing.
    int actualIndex = quadraticProbing(key, probe);

    // Verify the resulting index is as expected.
    EXPECT_EQ(actualIndex, expectedIndex);
}

/**
 * @test DoubleHashingTest
 * @brief Validates the double hashing technique used for handling collisions in a hash table.
 *
 * Double hashing uses two hash functions to compute the index for a key, especially under collision scenarios.
 * This test ensures that the computed index from the double hashing method is correct and matches the expected value.
 */
TEST_F(MarketTest, DoubleHashingTest) {
    int key = 42; // Test key value.
    int probe = 3; // Number of probes.
    int h1 = key % TABLE_SIZE; // First hash function.
    // Second hash function, ensuring it never returns zero.
    int h2 = 1 + (key % (TABLE_SIZE - 1));
    // Expected index using double hashing.
    int expectedIndex = (h1 + probe * h2) % TABLE_SIZE;

    // Execute double hashing.
    int actualIndex = doubleHashing(key, probe);

    // Check that the calculated index is correct.
    EXPECT_EQ(actualIndex, expectedIndex);
}

/**
 * @test LinearQuotientTest
 * @brief Tests the linear quotient function to verify the computation of indexes under collision using a linear probing variant.
 *
 * This function tests the linear quotient method which modifies the basic linear probing by incorporating a multiplication factor,
 * improving the distribution of hashed values. The test verifies if the calculated index by the linearQuotient function
 * matches the expected result calculated manually within the test.
 */
TEST_F(MarketTest, LinearQuotientTest) {
    // Sample key to hash.
    int key = 42;
    // Probe count used in the linear quotient calculation.
    int probe = 2;
    // Manually calculate expected index using a specific formula.
    int expectedIndex = (key + probe * 7) % TABLE_SIZE;

    // Call the linear quotient function.
    int actualIndex = linearQuotient(key, probe);

    // Assert that the actual index matches the expected index.
    EXPECT_EQ(actualIndex, expectedIndex);
}

/**
 * @test ProgressiveOverflowSearchTest
 * @brief Tests the progressive overflow search algorithm in a simulated overflow scenario.
 *
 * This test initializes a hash table and specifically sets an entry in the overflow area to simulate a condition
 * where a key is stored outside the main area of the hash table. It tests both the presence of a known key and
 * the absence of a non-existent key to ensure the search function accurately identifies both scenarios.
 */
TEST_F(MarketTest, ProgressiveOverflowSearchTest) {
    // Initialize the hash table and overflow areas.
    initializeHashTable();

    // Mark the first slot of the overflow area as occupied.
    overflowArea[0].isOccupied = 1;
    // Set a specific key in the overflow area.
    overflowArea[0].key = 42;

    // Expect the search to succeed for an existing key.
    EXPECT_TRUE(progressiveOverflowSearch(42));

    // Expect the search to fail for a non-existing key.
    EXPECT_FALSE(progressiveOverflowSearch(99));
}

/**
 * @test UseOfBucketsSearchTest
 * @brief Tests the functionality of bucket-based search within a hash table structure.
 *
 * This test initializes a hash table and adds a single product to a specific bucket. It verifies that the
 * search function correctly identifies the presence of a product by its vendor ID and fails when searching
 * for a non-existent vendor ID.
 */
TEST_F(MarketTest, UseOfBucketsSearchTest) {
    // Prepare the hash table for testing.
    initializeHashTable();

    // Calculate the hash index for a sample key.
    int index = hashFunction(42);
    // Add a product with vendor ID 42 to the calculated bucket.
    hashTableBuckets[index].products[0].vendorId = 42;
    // Increment the product count for the bucket.
    hashTableBuckets[index].productCount = 1;

    // Verify that the product can be found.
    EXPECT_TRUE(useOfBucketsSearch(42));

    // Verify that a non-existent product cannot be found.
    EXPECT_FALSE(useOfBucketsSearch(99));
}

/**
 * @test BrentsMethodSearchTest
 * @brief Tests Brent's method for hash collision resolution and search functionality.
 *
 * This test initializes a hash table, inserts a key using a hashing function, and then uses Brent's method
 * to verify that the key can be correctly retrieved. It also checks the behavior when searching for a key
 * that does not exist in the table.
 */
TEST_F(MarketTest, BrentsMethodSearchTest) {
    // Setup the hash table.
    initializeHashTable();

    // Add a key to the hash table
    int index = hashFunction(42);
    hashTable[index].isOccupied = 1;
    hashTable[index].key = 42;

    // Verify the key is found
    EXPECT_EQ(brentsMethodSearch(42), index);

    // Verify a non-existent key is not found
    EXPECT_EQ(brentsMethodSearch(99), -1);
}


/**
 * @test HeapSortTest
 * @brief Tests the heap sort algorithm to ensure it correctly sorts an array of products based on price.
 *
 * This test populates an array with several products each having different prices and then applies a heap sort
 * to order them by price in ascending order. It verifies that the products are sorted correctly by comparing
 * the order of product prices and names after sorting to expected values.
 */
TEST_F(MarketTest, HeapSortTest) {

    Product testProducts[] = {
        {1, "Banana", 30, 50, "Summer"},
        {2, "Apple", 25, 100, "Fall"},
        {3, "Tomato", 20, 200, "Winter"},
        {4, "Orange", 35, 75, "Spring"}
    };

    // Determine the number of products.
    int n = sizeof(testProducts) / sizeof(testProducts[0]);

    // Apply heap sort to the array.
    heapSort(testProducts, n);

    EXPECT_EQ(testProducts[0].price, 20); // Expect the lowest price product to be first.
    EXPECT_EQ(testProducts[1].price, 25); // Second lowest price.
    EXPECT_EQ(testProducts[2].price, 30); // Third.
    EXPECT_EQ(testProducts[3].price, 35); // Highest price last.

    // Names should match the sorted order by price.
    EXPECT_STREQ(testProducts[0].productName, "Tomato");
    EXPECT_STREQ(testProducts[1].productName, "Apple");
    EXPECT_STREQ(testProducts[2].productName, "Banana");
    EXPECT_STREQ(testProducts[3].productName, "Orange");
}

/**
 * @test TraverseXORListGroupedByIDTest
 * @brief Tests the traversal of an XOR linked list grouped by ID using the traverseXORListGroupedByID function.
 *
 * This unit test is designed to verify that the traverseXORListGroupedByID function can correctly navigate
 * through an XOR linked list, group entries by ID, and display them as specified. It involves creating a small
 * XOR linked list with entries grouped by two different IDs, simulating user interaction to traverse through these
 * groups, and capturing the output to ensure it meets the expected criteria.
 *
 * Steps:
 * 1. Initialize an XOR linked list with four nodes, two belonging to each of two different IDs.
 * 2. Simulate user input to step through the linked list and quit the traversal.
 * 3. Capture the output to verify that the grouping by ID works as expected, ensuring that:
 *    - Entries are grouped by ID.
 *    - Correct days and locations are displayed for each ID.
 * 4. Check output using assertions to ensure that each group is correctly formatted and displayed.
 *
 * Expected Outcome:
 * - The output captured from the console will correctly reflect the entries grouped by ID with accurate
 *   days and locations as per the test data. Each ID and its associated details should appear as expected
 *   based on the simulated user interaction.
 */
TEST_F(MarketTest, TraverseXORListGroupedByIDTest) {
    // Set up test data in an XOR linked list.
    MarketHoursNode* head = NULL;

    MarketHours data1 = { 1, "Monday", "09:00 - 17:00", "Main Street" };
    MarketHours data2 = { 1, "Tuesday", "10:00 - 18:00", "Market Square" };
    MarketHours data3 = { 2, "Wednesday", "08:00 - 16:00", "Central Plaza" };
    MarketHours data4 = { 2, "Thursday", "09:30 - 17:30", "West End" };

    head = insertXORList(head, data1);
    head = insertXORList(head, data2);
    head = insertXORList(head, data3);
    head = insertXORList(head, data4);

    // Simulate user interaction to traverse through the grouped list.
    simulateUserInput("n\nq\n"); // Navigate through the list and then quit.

    // Redirect stdout to capture output for verification.
    freopen(outputTest, "wb", stdout);

    // Call the function under test
    traverseXORListGroupedByID(head);

    // Clean up and reset the environment after output capture.
    resetStdinStdout();

    // Open the output file and verify the contents.
    FILE* file = fopen(outputTest, "rb");
    // Ensure file opened successfully for reading.
    ASSERT_NE(file, nullptr);
    char buffer[1024] = { 0 };
    // Read the output into the buffer.
    fread(buffer, sizeof(char), sizeof(buffer) - 1, file);
    fclose(file);

    // Validate the output against expected results.
    EXPECT_TRUE(strstr(buffer, "ID: 1") != nullptr); // Check for group ID 1 presence.
    EXPECT_NE(strstr(buffer, "Day: Monday"), nullptr); // Verify details for ID 1.
    EXPECT_NE(strstr(buffer, "Day: Tuesday"), nullptr); // Verify details for ID 1.
    EXPECT_NE(strstr(buffer, "ID: 2"), nullptr); // Check for group ID 2 presence.
    EXPECT_NE(strstr(buffer, "Day: Wednesday"), nullptr); // Verify details for ID 2.
    EXPECT_NE(strstr(buffer, "Day: Thursday"), nullptr); // Verify details for ID 2.
}







/**
 * @brief Main entry point for running all unit tests.
 *
 * @param argc Argument count.
 * @param argv Argument vector.
 * @return int Exit status.
 */

int main(int argc, char** argv) {
#ifdef ENABLE_MARKET_TEST
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    return 0;
#endif
}