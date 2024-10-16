#include "../header/market.h"
#include <stdexcept>

using namespace Coruh::Market;

double Market::add(double a, double b) {
    return a + b;
}

double Market::subtract(double a, double b) {
    return a - b;
}

double Market::multiply(double a, double b) {
    return a * b;
}

double Market::divide(double a, double b) {
    if (b == 0) {
        throw std::invalid_argument("Division by zero is not allowed.");
    }
    return a / b;
}