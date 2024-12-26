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
    int found = 0;

    while (fread(&product, sizeof(Product), 1, file)) {
        if (strcmp(product.productName, "tomato") == 0) {
            found = 1;
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
 */
TEST_F(MarketTest, marketHoursAndLocationsTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("0\n");
    // getInput fonksiyonunu çağır
    bool result = marketHoursAndLocations;

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}





/**
 * @brief Test case for searching products or entering a keyword.
 *
 * This test simulates user input to trigger the searchProductsOrEnterKeyword function.
 * It verifies that the function returns true after the simulated input, indicating
 * a successful keyword or product search.
 */
TEST_F(MarketTest, SearchProductsOrEnterKeywordTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("0\n");
    // getInput fonksiyonunu çağır
    bool result = searchProductsOrEnterKeyword();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


/**
 * @brief Test case for entering search products.
 *
 * This test simulates user input for entering a product name to search.
 * After simulating the input, it calls the enterSearchProducts function and verifies
 * that the function returns true, indicating a successful product search.
 */
TEST_F(MarketTest, EnterSearchProductsTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("tomato\n");
    // getInput fonksiyonunu çağır
    bool result = enterSearchProducts;

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


/**
 * @brief Test case for entering keywords.
 *
 * This test simulates user input for entering a keyword.
 * After simulating the input, it calls the enterKeywords function and verifies
 * that the function returns true, indicating a successful keyword entry.
 */
TEST_F(MarketTest, EnterKeywordsTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("winter\n");
    // getInput fonksiyonunu çağır
    bool result = enterKeywords;

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


/**
 * @test SaveUserToHuffFileTEST
 * @brief Test case for saving a user to the Huffman file.
 */
TEST_F(MarketTest, SaveUserToHuffFileTEST) {
    // Kullanıcı adı ve şifreyi kaydet
    const char* username = "testUser";
    const char* password = "password123";
    bool result = saveUserToHuffFile(username, password);

    // Kaydetme işleminin başarılı olduğunu kontrol et
    EXPECT_TRUE(result);
}








TEST_F(MarketTest, userAuthenticationTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, doğru kullanıcı adı ve şifre)
    simulateUserInput("1\ntestUser\npassword123\n0\n0\n4\n");

    // loginUser fonksiyonunu çağır
    bool result = userAuthentication();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde işlenip işlenmediğini kontrol et
    EXPECT_TRUE(result);
}



TEST_F(MarketTest, userAuthenticationTEST2) {
    // Simüle edilmiş geçerli giriş (örneğin, doğru kullanıcı adı ve şifre)
    simulateUserInput("2\nnewUser\nnewpassword\n0\n0\n4\n");

    // loginUser fonksiyonunu çağır
    bool result = userAuthentication();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde işlenip işlenmediğini kontrol et
    EXPECT_TRUE(result);
}





/**
 * @test LoginUserUpdatedTEST
 * @brief Test case for logging in a user.
 */
TEST_F(MarketTest, LoginUserTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, doğru kullanıcı adı ve şifre)
    simulateUserInput("testUser\npassword123\n");

    // loginUser fonksiyonunu çağır
    bool result = loginUser();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde işlenip işlenmediğini kontrol et
    EXPECT_TRUE(result);
}


/**
 * @test RegisterUserTEST
 * @brief Test case for registering a new user.
 */
TEST_F(MarketTest, RegisterUserTEST) {
    // Simüle edilmiş kullanıcı kaydı girişleri (kullanıcı adı ve şifre)
    simulateUserInput("newUser\nnewPassword\n");

    // registerUser fonksiyonunu çağır
    bool result = registerUser();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Kaydın başarılı olup olmadığını kontrol et
    EXPECT_TRUE(result);
}


/**
 * @test PriceComparisonTEST
 * @brief Test case for comparing product prices.
 */
TEST_F(MarketTest, PriceComparisonTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("0\n");

    // getInput fonksiyonunu çağır
    bool result = priceComparison();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, PriceComparisonTEST2) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("1\ntomato\n0\n0\n4\n");

    // getInput fonksiyonunu çağır
    bool result = priceComparison();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, PriceComparisonTEST3) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("2\n\n0\n0\n4\n");

    // getInput fonksiyonunu çağır
    bool result = priceComparison();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, PriceComparisonInvalidTEST4) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("675768\n0\n0\n4\n");

    // getInput fonksiyonunu çağır
    bool result = priceComparison();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

/**
 * @test SelectProductTEST
 * @brief Test case for selecting a product by name.
 */
TEST_F(MarketTest, SelectProductTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("tomato\n");
    char selectedProductName[100] = "";

    // getInput fonksiyonunu çağır
    bool result = selectProduct(selectedProductName);

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


/**
 * @test ComparePriceByNameTEST
 * @brief Test case for comparing product prices by name.
 */
TEST_F(MarketTest, ComparePriceByNameTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("tomato\n");
    char selectedProductName[100] = "";
    // getInput fonksiyonunu çağır
    bool result = comparePricesByName(selectedProductName);

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, enterSearchProductsTEST) {
    // Simüle edilmiş kullanıcı kaydı girişleri (kullanıcı adı ve şifre)
    simulateUserInput("banana\n0\n0\n4\n");

    // registerUser fonksiyonunu çağır
    bool result = enterSearchProducts();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Kaydın başarılı olup olmadığını kontrol et
    EXPECT_TRUE(result);
}



TEST_F(MarketTest, enterKeywordsTEST) {
    // Simüle edilmiş kullanıcı kaydı girişleri (kullanıcı adı ve şifre)
    simulateUserInput("banana\n0\n0\n4\n");

    // registerUser fonksiyonunu çağır
    bool result = enterKeywords();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Kaydın başarılı olup olmadığını kontrol et
    EXPECT_TRUE(result);
}


TEST_F(MarketTest, searchProductsOrEnterKeywordInvalidTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("5\n0\n0\n0\n4\n");

    // getInput fonksiyonunu çağır
    bool result = searchProductsOrEnterKeyword();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, enterSearchProductsTEST2) {
    // Simüle edilmiş kullanıcı kaydı girişleri (kullanıcı adı ve şifre)
    simulateUserInput("1\nbanana\n0\n0\n4\n");

    // registerUser fonksiyonunu çağır
    bool result = searchProductsOrEnterKeyword();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Kaydın başarılı olup olmadığını kontrol et
    EXPECT_TRUE(result);
}



TEST_F(MarketTest, enterKeywordsTEST2) {
    // Simüle edilmiş kullanıcı kaydı girişleri (kullanıcı adı ve şifre)
    simulateUserInput("2\nbanana\n0\n0\n4\n");

    // registerUser fonksiyonunu çağır
    bool result = searchProductsOrEnterKeyword();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Kaydın başarılı olup olmadığını kontrol et
    EXPECT_TRUE(result);
}


TEST_F(MarketTest, minheapfyTEST) {
    // Simüle edilmiş kullanıcı kaydı girişleri (kullanıcı adı ve şifre)
    simulateUserInput("\n");
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 5; // Test için 5 düğümlü bir heap
    minHeap->capacity = 5;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));

    // Düğümleri ekle
    for (int i = 0; i < minHeap->size; i++) {
        struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
        node->freq = (minHeap->size - i) * 10; // Frekans değerleri: 50, 40, 30, 20, 10
        minHeap->array[i] = node;
    }
    int smallest = 0;
    // registerUser fonksiyonunu çağır
    bool result = minHeapify(minHeap, 0);

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Kaydın başarılı olup olmadığını kontrol et
    EXPECT_TRUE(result);
}


TEST_F(MarketTest, insertMinheapifyTEST) {
    // Simüle edilmiş kullanıcı kaydı girişleri (kullanıcı adı ve şifre)
    simulateUserInput("\n");
    struct MinHeap* minHeap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    minHeap->size = 0; // Başlangıçta heap boş
    minHeap->capacity = 5;
    minHeap->array = (struct MinHeapNode**)malloc(minHeap->capacity * sizeof(struct MinHeapNode*));

    // Yeni bir MinHeapNode oluştur
    struct MinHeapNode* minHeapNode = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    minHeapNode->freq = 15; // Yeni düğümün frekansı

    for (int i = 0; i < minHeap->size; i++) {
        struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
        node->freq = (minHeap->size - i) * 10; // Frekans değerleri: 50, 40, 30, 20, 10
        minHeap->array[i] = node;
    }
    
    // registerUser fonksiyonunu çağır
    bool result = insertMinHeap(minHeap,minHeapNode);

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Kaydın başarılı olup olmadığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, buildHuffmanTreeTEST) {
    // Test verilerini tanımla
    char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(data) / sizeof(data[0]);

    // buildHuffmanTree fonksiyonunu çağır
    struct MinHeapNode* huffmanTreeRoot = buildHuffmanTree(data, freq, size);

    // Huffman ağacının doğru oluşturulduğunu kontrol et
    EXPECT_NE(huffmanTreeRoot, nullptr); // Kök düğüm boş olmamalı
    EXPECT_EQ(huffmanTreeRoot->freq, 100); // Frekansların toplamı kökte olmalı

    // Sol ve sağ alt ağaçların doğru olup olmadığını kontrol et
    EXPECT_NE(huffmanTreeRoot->left, nullptr);
    EXPECT_NE(huffmanTreeRoot->right, nullptr);

}


TEST_F(MarketTest, DebugHuffmanCodesTest) {
    char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
    int freq[] = { 5, 9, 12, 13, 16, 45 };
    int size = sizeof(data) / sizeof(data[0]);

    // Huffman kodlarını üret ve doğrudan yazdır
    HuffmanCodes(data, freq, size);
}



TEST_F(MarketTest, listProductsByVendorTEST) {
    // Simulate the vendor ID input
    int testVendorId = 1;

    // Redirect standard output to a buffer for capturing results
    testing::internal::CaptureStdout();

    // Act: Call the function to list products by vendor
    bool result = listProductsByVendor(testVendorId);

    // Assert: Verify the result is true and the correct products are printed
    EXPECT_TRUE(result);

}


TEST_F(MarketTest, heapifyTEST) {
    // Simüle edilmiş kullanıcı kaydı girişleri (kullanıcı adı ve şifre)
    simulateUserInput("\n");
    // We initialize the largest element as root
    struct Product arr[5] = {
        
    };

    int i = 0; // Root elemanın başlangıç indeksi
    int n = 5; // Dizinin boyutu
    // Largest kısmını doğrula
    int largest = 0; // Başlangıç değeri
    int left = 2 * i + 1; // Sol çocuk
    int right = 2 * i + 2; // Sağ çocuk

    if (left < n && arr[left].price > arr[largest].price)
        largest = left;

    if (right < n && arr[right].price > arr[largest].price)
        largest = right;


    // registerUser fonksiyonunu çağırarr
    bool result = heapify(arr,1,1);

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Kaydın başarılı olup olmadığını kontrol et
    EXPECT_TRUE(result);
}


TEST_F(MarketTest, ProgressiveOverflowSearchTEST) {
    // Test için overflowArea'yi simüle et
    for (int i = 0; i < OVERFLOW__SIZE; i++) {
        overflowAreaa[i].isOccupied = false;
        overflowAreaa[i].key = 0;
    }

    // Örnek verileri ekle
    overflowAreaa[3].isOccupied = true;
    overflowAreaa[3].key = 42;

    overflowAreaa[7].isOccupied = true;
    overflowAreaa[7].key = 99;


    // Anahtar bulunmayan bir durumda false dönmesini bekliyoruz
    EXPECT_FALSE(progressiveOverflowSearch(100));

    // İşgal edilmemiş bir alandaki anahtar testi
    EXPECT_FALSE(progressiveOverflowSearch(50));
}




TEST_F(MarketTest, LoginUserInvalidCredentialsTEST) {
    // Simüle edilmiş geçersiz giriş (örneğin, yanlış kullanıcı adı ve şifre)
    simulateUserInput("wrongUser\nwrongPassword\n");

    // loginUser fonksiyonunu çağır
    bool result = loginUser();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin başarısız olup olmadığını kontrol et
    EXPECT_FALSE(result);
}


TEST_F(MarketTest, ListVendorsElseCasesTEST) {
    // Test için vendor.bin dosyasını oluştur ve örnek veriler ekle
    FILE* file = fopen("vendor.bin", "wb");

    // Test için örnek vendor verileri ekle
    Vendor v1 = { 1, "Vendor1" };
    fwrite(&v1, sizeof(Vendor), 1, file);
    fclose(file);

    // Simüle edilmiş giriş: Geçersiz giriş ('z'), sonra 'n' komutu (liste sonunda else durumu)
    simulateUserInput("z\nn\nx\n");

    // listVendors fonksiyonunu çağır
    bool result = listVendors();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Fonksiyonun başarılı şekilde çalışıp çalışmadığını kontrol et
    EXPECT_TRUE(result);

}

TEST_F(MarketTest, AddMarketHoursAndLocationTEST) {
    // Test dosyalarını hazırla: vendor.bin dosyasını oluştur
    createTestVendorFile(); // Geçerli vendor kayıtlarını ekle

    // Simüle edilmiş giriş:
    // Vendor ID: 1, Day: Monday, Hours: "09:00 - 18:00", Location: "MainStreet"
    simulateUserInput("1\nmonday\n09:00 - 18:00\nMainStreet\n");

    // addMarketHoursAndLocation fonksiyonunu çağır
    bool result = addMarketHoursAndLocation();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Fonksiyonun başarılı olduğunu kontrol et
    EXPECT_TRUE(result);

    // marketHours.bin dosyasını aç ve eklenen veriyi kontrol et
    FILE* file = fopen("marketHours.bin", "rb");
    ASSERT_NE(file, nullptr); // Dosyanın açıldığından emin ol

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

    // Eklenen kaydın bulunduğunu doğrula
    EXPECT_TRUE(found);
}


TEST_F(MarketTest, AddMarketHoursAndLocationInvalidTEST) {
    // Test dosyasını hazırla: vendor.bin oluştur ama ID'si 1 olmayan bir veri ekle
    createTestVendorFile(); // Örneğin vendor ID: 1 ekleniyor, ama kullanıcı 999 giriyor.

    // Simüle edilmiş geçersiz giriş: ID: 999
    simulateUserInput("999\n");

    // addMarketHoursAndLocation fonksiyonunu çağır
    bool result = addMarketHoursAndLocation();

    // Giriş/çıkışı sıfırla
    resetStdinStdout();

    // Fonksiyonun başarısız olduğunu doğrula
    EXPECT_FALSE(result);


}


TEST_F(MarketTest, UpdateMarketHoursAndLocationTEST) {
    // Test için gerekli dosyayı oluştur: marketHours.bin
    FILE* file = fopen("marketHours.bin", "wb");
    ASSERT_NE(file, nullptr) << "Failed to create test marketHours.bin file";

    // Başlangıç verilerini ekle
    MarketHours initialData[] = {
        {1, "monday", "09:00 - 18:00", "OldStreet"},
        {2, "tuesday", "10:00 - 19:00", "NewStreet"}
    };
    fwrite(initialData, sizeof(MarketHours), 2, file);
    fclose(file);

    // Simüle edilmiş giriş: Market ID: 1, Yeni Day: Wednesday, Yeni Hours: "08:00 - 17:00", Yeni Location: "UpdatedStreet"
    simulateUserInput("1\nwednesday\n08:00 - 17:00\nUpdatedStreet\n");

    // Fonksiyonu çağır
    bool result = updateMarketHoursAndLocation();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Fonksiyonun başarılı olduğunu kontrol et
    EXPECT_TRUE(result);

    // Güncellenen dosyayı aç ve veriyi kontrol et
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

    // Güncellenmiş verinin bulunduğunu doğrula
    EXPECT_TRUE(found) << "Updated MarketHours record not found in file";
}

TEST_F(MarketTest, UpdateMarketHoursAndLocationInvalidID) {
    // Test dosyasını oluştur ve geçerli bir Market ID ekle
    createTestMarketHoursFile();

    // Simüle edilmiş geçersiz Market ID: 999
    simulateUserInput("999\n");

    bool result = updateMarketHoursAndLocation();

    // Standart giriş/çıkışı sıfırla
    resetStdinStdout();

    // Test: Fonksiyon false döner ve doğru hata mesajını yazdırır
    EXPECT_TRUE(result);
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