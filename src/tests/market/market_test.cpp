﻿#include "gtest/gtest.h"
#include "../../market/header/market.h"


class MarketTest : public ::testing::Test {
protected:
    const char* inputTest = "inputTest.txt";
    const char* outputTest = "outputTest.txt";

    void SetUp() override {
        // Test verileri ayarlanabilir.
        initializeHashTable();
    }

    void TearDown() override {
        remove(inputTest);
        remove(outputTest);
    }

    void simulateUserInput(const char* userInput) {
        FILE* fileinput = fopen(inputTest, "wb");
        fputs(userInput, fileinput);
        fclose(fileinput);
        freopen(inputTest, "rb", stdin);
        freopen(outputTest, "wb", stdout);
    }

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




int main(int argc, char** argv) {
#ifdef ENABLE_MARKET_TEST
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
#else
    return 0;
#endif
}