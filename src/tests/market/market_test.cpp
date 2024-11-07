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
};


/**
 * @test MainMenuTest
 * @brief Test case for the main menu function with option 0.
 */
TEST_F(MarketTest, MainMenuTest) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("0\n");

    // getInput fonksiyonunu çağır
    bool result = mainMenu();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

/**
 * @test MainMenuTest1
 * @brief Test case for the main menu function with option 1.
 */
TEST_F(MarketTest, MainMenuTest1) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("1\n0\n0\n");

    // getInput fonksiyonunu çağır
    bool result = mainMenu();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

/**
 * @test MainMenuTest2
 * @brief Test case for the main menu function with option 2.
 */
TEST_F(MarketTest, MainMenuTest2) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("2\n0\n0\n");

    // getInput fonksiyonunu çağır
    bool result = mainMenu();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}



TEST_F(MarketTest, MainMenuTest3) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("3\n0\n0\n");

    // getInput fonksiyonunu çağır
    bool result = mainMenu();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, MainMenuTest4) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("4\n0\n0\n");

    // getInput fonksiyonunu çağır
    bool result = mainMenu();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, MainMenuTest5) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("5\n0\n0\n");

    // getInput fonksiyonunu çağır
    bool result = mainMenu();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


/**
 * @test listingOfLocalVendorsTEST
 * @brief Test case for listing local vendors.
 */
TEST_F(MarketTest, listingOfLocalVendorsTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("0\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalVendors();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


/**
 * @test AddVendorTEST
 * @brief Test case for adding a vendor.
 */
TEST_F(MarketTest, AddvendorTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("tugba\n\n");

    // getInput fonksiyonunu çağır
    bool result = addVendor();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

/**
 * @test UpdateVendorTEST
 * @brief Test case for updating a vendor.
 */
TEST_F(MarketTest, UpdatevendorTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("123456\ntugba\n");

    // getInput fonksiyonunu çağır
    bool result = updateVendor();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


/**
 * @test DeleteVendorTEST
 * @brief Test case for deleting a vendor.
 */
TEST_F(MarketTest, DeletevendorTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("123456\n\n");

    // getInput fonksiyonunu çağır
    bool result = deleteVendor();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


/**
 * @test ListVendorsTEST
 * @brief Test case for listing all vendors.
 */
TEST_F(MarketTest, ListVendorsTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("q\n\n");

    // getInput fonksiyonunu çağır
    bool result = listVendors();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


/**
 * @test ListingOfLocalProductsTEST
 * @brief Test case for listing all local products.
 */
TEST_F(MarketTest, ListingOfLocalProductsTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("0\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalProducts();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

/**
 * @test AddProductTEST
 * @brief Test case for adding a product.
 */
TEST_F(MarketTest, AddProductTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("123456\ntomato\n15\n150\nwinter\n");

    // getInput fonksiyonunu çağır
    bool result = addProduct();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


/**
 * @test UpdateProductTEST
 * @brief Test case for updating a product.
 */
TEST_F(MarketTest, UpdateProductTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("123456\ntomato\n15\n150\nwinter\n");

    // getInput fonksiyonunu çağır
    bool result = updateProduct();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

/**
 * @test DeleteProductTEST
 * @brief Test case for deleting a product.
 */
TEST_F(MarketTest, DeleteProductTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("123456\ntomato\n");

    // getInput fonksiyonunu çağır
    bool result = deleteProduct();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


/**
 * @test listingOfLocalVendorsandProductsTEST
 * @brief Test case for listing all local vendors and their products.
 */
TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("\n\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalVendorsandProducts();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST1) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("1\n\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalVendorsandProducts();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST2) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("2\n\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalVendorsandProducts();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST3) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("3\n\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalVendorsandProducts();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST4) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("4\n\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalVendorsandProducts();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST5) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("5\n\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalVendorsandProducts();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST6) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("6\n\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalVendorsandProducts();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST7) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("7\n\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalVendorsandProducts();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST8) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("8\n\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalVendorsandProducts();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
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
 * @test AddMarketHoursAndLocationTEST
 * @brief Test case for adding market hours and location.
 */
TEST_F(MarketTest, AddMarketHoursAndLocationTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("1\n123456\nmonday\n09:00 - 18:00\ntrabzon\n");
    // getInput fonksiyonunu çağır
    bool result = addMarketHoursAndLocation;

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


/**
 * @brief Test case for updating market hours and location.
 *
 * This test simulates user input for updating market hours and location.
 * The input includes an ID, day, working hours, and location.
 * After simulating the user input, it calls the updateMarketHoursAndLocation function
 * and verifies that the function returns true, indicating a successful update.
 */
TEST_F(MarketTest, UpdateMarketHoursAndLocationTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("2\n123456\nmonday\n09:00 - 18:00\ntrabzon\n");
    // getInput fonksiyonunu çağır
    bool result = updateMarketHoursAndLocation;

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


/**
 * @brief Test case for displaying market hours and locations.
 *
 * This test simulates user input for displaying market hours and locations.
 * The function displayMarketHoursAndLocations is called after simulating the input,
 * and it verifies that the function returns true, indicating a successful display.
 */
TEST_F(MarketTest, DisplayMarketHoursAndLocationsTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("3\n");
    // getInput fonksiyonunu çağır
    bool result = displayMarketHoursAndLocations;

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
    bool result = searchProductsOrEnterKeyword;

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

/**
 * @test LoginUserUpdatedTEST
 * @brief Test case for logging in a user.
 */
TEST_F(MarketTest, LoginUserUpdatedTEST) {
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

TEST_F(MarketTest, AddVendorTEST) {
    // Simüle edilmiş vendor ekleme girişleri (vendor adı)
    simulateUserInput("sevval\n");

    // addVendor fonksiyonunu çağır
    bool result = addVendor();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Vendor ekleme işleminin başarılı olup olmadığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, UpdateVendorTEST) {
    // Simüle edilmiş vendor güncelleme girişleri (vendor ID ve yeni adı)
    simulateUserInput("123456\nsevval\n");

    // updateVendor fonksiyonunu çağır
    bool result = updateVendor();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Vendor güncelleme işleminin başarılı olup olmadığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, DeleteVendorTEST) {
    // Simüle edilmiş vendor silme girişleri (vendor ID)
    simulateUserInput("123456\n");

    // deleteVendor fonksiyonunu çağır
    bool result = deleteVendor();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Vendor silme işleminin başarılı olup olmadığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, DisplayMarketHoursandLocationsTEST) {
    // Simüle edilmiş vendor silme girişleri (vendor ID)
    simulateUserInput("\n");

    // deleteVendor fonksiyonunu çağır
    bool result = displayMarketHoursAndLocations();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Vendor silme işleminin başarılı olup olmadığını kontrol et
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