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

    
    // Kullanıcı test verileri oluşturma
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

    // Vendor test verileri oluşturma
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

    // Product test verileri oluşturma
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

    // Market hours and locations test verileri oluşturma
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

     // Hash table test verilerini başlatma
    void initializeTestHashTable() {
        initializeHashTable();
        // Örnek ürün ve vendor ilişkilerini ekle
        addVendorProductRelation(1, 101, 10.5); // Vendor 1 için ürün 101
        addVendorProductRelation(2, 102, 15.0); // Vendor 2 için ürün 102
    }

    // Huffman kodlama test verileri
    void createHuffmanTestData() {
        char data[] = { 'a', 'b', 'c', 'd', 'e', 'f' };
        int freq[] = { 5, 9, 12, 13, 16, 45 };
        int size = sizeof(data) / sizeof(data[0]);

        struct MinHeapNode* huffmanTreeRoot = buildHuffmanTree(data, freq, size);
        HuffmanCodes(data, freq, size);
    }

    // Test ortamını başlatma
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
    simulateUserInput("3\n0\n0\n0\n0\n4\n");

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



TEST_F(MarketTest, MainMenuTestInvalid) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("787\n0\n");

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


TEST_F(MarketTest, listingOfLocalVendorsTEST2) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("1\ntugba\n0\n0\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalVendors();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


TEST_F(MarketTest, listingOfLocalVendorsTEST3) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("2\n123456\ntugba\n0\n0\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalVendors();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, listingOfLocalVendorsTEST4) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("3\n123456\n0\n0\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalVendors();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}



TEST_F(MarketTest, listingOfLocalVendorsTEST5) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("4\nq\nx\n0\n0\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalVendors();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, listingOfLocalVendorsInvalidTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("5\n0\n0\n0\n0\n");

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
    simulateUserInput("q\nx\n");

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


TEST_F(MarketTest, ListingOfLocalProductsTEST2) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("1\n123456\ntomato\n15\n150\nwinter\n0\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalProducts();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


TEST_F(MarketTest, ListingOfLocalProductsTEST3) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("2\n123456\ntomato\n15\n150\nwinter\n0\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalProducts();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}





TEST_F(MarketTest, ListingOfLocalProductsTEST4) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("3\n123456\ntomato\n0\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalProducts();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}

TEST_F(MarketTest, ListingOfLocalProductsTEST5) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("4\n8\n0\n0\n4\n");

    // getInput fonksiyonunu çağır
    bool result = listingOfLocalProducts();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Girişin doğru şekilde alındığını kontrol et
    EXPECT_TRUE(result);
}


TEST_F(MarketTest, ListingOfLocalProductsInvalidTEST) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("5\n0\n0\n4\n");

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
    // Önce test ortamını hazırlıyoruz
    createTestVendorFile(); // Vendor dosyasını oluştur
    createTestProductFile(); // Ürün dosyasını oluştur

    // Simüle edilmiş geçerli giriş (Vendor ID: 1, Ürün adı: Tomato, Fiyat: 15, Miktar: 150, Sezon: Winter)
    simulateUserInput("1\ntomato\n15\n150\nwinter\n");

    // addProduct fonksiyonunu çağır
    bool result = addProduct();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Fonksiyonun doğru şekilde çalıştığını kontrol et
    EXPECT_TRUE(result);

    // Ürün dosyasını aç ve doğru ürünün eklenip eklenmediğini kontrol et
    FILE* productFile = fopen("products.bin", "rb");
    ASSERT_NE(productFile, nullptr); // Dosya başarıyla açıldı mı kontrol et

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

    // Ürünün başarıyla eklendiğini kontrol et
    EXPECT_TRUE(found);
}



/**
 * @test UpdateProductTEST
 * @brief Test case for updating a product.
 */
//

TEST_F(MarketTest, UpdateProductTEST) {
    // Test dosyasını hazırlıyoruz
    createTestProductFile(); // products.bin oluştur

    // Simüle edilmiş geçerli giriş: "tomato" adlı ürün güncellenecek
    simulateUserInput("tomato\nupdated_tomato\n20\n200\nsummer\n");

    // updateProduct fonksiyonunu çağır
    bool result = updateProduct();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Fonksiyonun başarılı olduğunu kontrol et
    EXPECT_TRUE(result);

    // Dosyadan kontrol et: Güncellenmiş ürün var mı?
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

    EXPECT_TRUE(updated);
}


TEST_F(MarketTest, UpdateProductNotFoundTEST) {
    // Test dosyasını hazırlıyoruz
    createTestProductFile(); // products.bin oluştur

    // Simüle edilmiş geçerli giriş: Olmayan ürün adı giriliyor
    simulateUserInput("nonexistent_product\n");

    // updateProduct fonksiyonunu çağır
    testing::internal::CaptureStdout(); // Çıktıyı yakala
    bool result = updateProduct();
    std::string output = testing::internal::GetCapturedStdout(); // Yakalanan çıktıyı al

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Fonksiyon başarılı çalışmalı ancak ürün bulunmamalı
    EXPECT_TRUE(result);

  
}



/**
 * @test DeleteProductTEST
 * @brief Test case for deleting a product.
 */
//TEST_F(MarketTest, DeleteProductTEST) {
//    // Simüle edilmiş geçerli giriş (örneğin, 5)
//    simulateUserInput("123456\ntomato\n");
//
//    // getInput fonksiyonunu çağır
//    bool result = deleteProduct();
//
//    // Standart giriş ve çıkışı sıfırla
//    resetStdinStdout();
//
//    // Girişin doğru şekilde alındığını kontrol et
//    EXPECT_TRUE(result);
//}


TEST_F(MarketTest, DeleteProductTEST) {
    // Test dosyasını hazırla
    createTestProductFile(); // Test için products.bin dosyasını oluştur

    // Simüle edilmiş geçerli giriş: "tomato" adlı ürün silinecek
    simulateUserInput("tomato\n");

    // deleteProduct fonksiyonunu çağır
    bool result = deleteProduct();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Fonksiyonun başarılı olduğunu kontrol et
    EXPECT_TRUE(result);

    // Dosyadan kontrol et: Silinen ürünün hala var olup olmadığını doğrula
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

    // Ürünün dosyada bulunmadığını doğrula
    EXPECT_FALSE(found);
}

TEST_F(MarketTest, DeleteProductNotFoundTEST) {
    // Test dosyasını hazırla
    createTestProductFile(); // Test için products.bin dosyasını oluştur

    // Simüle edilmiş giriş: Olmayan ürün adı "nonexistent_product"
    simulateUserInput("nonexistent_product\n");

    // deleteProduct fonksiyonunu çağır
    testing::internal::CaptureStdout(); // Çıktıyı yakala
    bool result = deleteProduct();
    std::string output = testing::internal::GetCapturedStdout(); // Yakalanan çıktıyı al

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Fonksiyonun başarılı çalıştığını kontrol et
    EXPECT_TRUE(result);

   
}





TEST_F(MarketTest, listingOfLocalVendorsandProductsTEST1) {
    // Simüle edilmiş geçerli giriş (örneğin, 5)
    simulateUserInput("1\n\n0\n0\n4\n");

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

TEST_F(MarketTest, ListingOfLocalVendorsAndProductsInvalidStrategyTEST) {
    // Önce test ortamını hazırlıyoruz
    createTestVendorFile();  // Vendor dosyasını oluştur
    createTestProductFile(); // Ürün dosyasını oluştur

    // Simüle edilmiş giriş:
    // Geçersiz strateji (örneğin 9) seçiliyor ve ardından çıkılıyor.
    simulateUserInput("11\n");

    // listingOfLocalVendorsandProducts fonksiyonunu çağır
    bool result = listingOfLocalVendorsandProducts();

    // Standart giriş ve çıkışı sıfırla
    resetStdinStdout();

    // Fonksiyonun doğru şekilde çalışmadığını kontrol et
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