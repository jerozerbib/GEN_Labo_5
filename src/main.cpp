#include <iostream>
#include <limits.h>
#include "gtest/gtest.h"
#include "gmock/gmock.h"

#include "Customer.h"

// Run this main if you want run the tests

int main(int argc, char **argv) {
    ::testing::InitGoogleMock(&argc, argv);
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

// Run this main if you want to run the programm

//int main() {
//
//    Customer customer("Olivier");
//    customer.addRental( Rental( Movie("Karate Kid"), 7));
//    customer.addRental( Rental( Movie( "Avengers: Endgame", Movie::NEW_RELEASE ), 5));
//    customer.addRental( Rental( Movie("Snow White", Movie::CHILDRENS), 3 ));
//
//    std::cout << customer.statement() << std::endl;
//
//    return 0;
//}