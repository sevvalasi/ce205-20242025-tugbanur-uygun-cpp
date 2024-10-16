//#define ENABLE_MARKET_TEST  // Uncomment this line to enable the Market tests

#include "gtest/gtest.h"
#include "../../market/header/market.h"  // Adjust this include path based on your project structure
#include "../../market/src/market.cpp"


using namespace Coruh::Market;

class MarketTest : public ::testing::Test {
protected:
	void SetUp() override {
		// Setup test data
	}

	void TearDown() override {
		// Clean up test data
	}
};

TEST_F(MarketTest, TestAdd) {
	double result = Market::add(5.0, 3.0);
	EXPECT_DOUBLE_EQ(result, 8.0);
}

TEST_F(MarketTest, TestSubtract) {
	double result = Market::subtract(5.0, 3.0);
	EXPECT_DOUBLE_EQ(result, 2.0);
}

TEST_F(MarketTest, TestMultiply) {
	double result = Market::multiply(5.0, 3.0);
	EXPECT_DOUBLE_EQ(result, 15.0);
}

TEST_F(MarketTest, TestDivide) {
	double result = Market::divide(6.0, 3.0);
	EXPECT_DOUBLE_EQ(result, 2.0);
}

TEST_F(MarketTest, TestDivideByZero) {
	EXPECT_THROW(Market::divide(5.0, 0.0), std::invalid_argument);
}

/**
 * @brief The main function of the test program.
 *
 * @param argc The number of command-line arguments.
 * @param argv An array of command-line argument strings.
 * @return int The exit status of the program.
 */
int main(int argc, char** argv) {
#ifdef ENABLE_MARKET_TEST
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
#else
	return 0;
#endif
}