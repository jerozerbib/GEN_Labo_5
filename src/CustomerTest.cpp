#include "gtest/gtest.h"

#include "Customer.h"


TEST(CustomerTest, statementForNoMovie) {
    Customer customer("Baptiste");

    ASSERT_EQ(customer.statement(), "Rental Record for Baptiste\nAmount owed is 0\nYou earned 0 frequent renter points");
}

TEST(CustomerTest, statementForOneChildMovie) {
    Customer customer("Florian");
    customer.addRental( Rental( Movie("Oui-Oui", Movie::CHILDRENS), 1));

    ASSERT_EQ(customer.statement(), "Rental Record for Florian\n\tOui-Oui\t1.5\nAmount owed is 1.5\nYou earned 1 frequent renter points");
}

TEST(CustomerTest, statementForOneNewReleaseMovie) {
    Customer customer("Florian");
    customer.addRental( Rental( Movie("Avengers: Empire Strikes Back", Movie::NEW_RELEASE), 2));

    ASSERT_EQ(customer.statement(), "Rental Record for Florian\n\tAvengers: Empire Strikes Back\t6\nAmount owed is 6\nYou earned 2 frequent renter points");
}


TEST(CustomerTest, statementForOneMovieWithoutTag) {
    Customer customer("Florian");
    customer.addRental(Rental(Movie("Sharknado"), 14));

    ASSERT_EQ(customer.statement(), "Rental Record for Florian\n\tSharknado\t20\nAmount owed is 20\nYou earned 1 frequent renter points");
}

TEST(CustomerTest, statementForTwoMovies) {
    Customer customer("Jeremy");
    customer.addRental(Rental(Movie("L'etroit Mousquetaire"), 1));
    customer.addRental(Rental(Movie("Tous les trous sont permis", Movie::CHILDRENS), 2));

    ASSERT_EQ(customer.statement(), "Rental Record for Jeremy\n\tL'etroit Mousquetaire\t2\n\tTous les trous sont permis\t1.5\nAmount owed is 3.5\nYou earned 2 frequent renter points");
}

TEST(CustomerTest, statementForThreeMovies) {
    Customer customer("Olivier");
    customer.addRental( Rental( Movie("Karate Kid"), 7));
    customer.addRental( Rental( Movie( "Avengers: Endgame", Movie::NEW_RELEASE ), 5));
    customer.addRental( Rental( Movie("Snow White", Movie::CHILDRENS), 3 ));

    ASSERT_EQ(customer.statement(), "Rental Record for Olivier\n\tKarate Kid\t9.5\n\tAvengers: Endgame\t15\n\tSnow White\t1.5\nAmount owed is 26\nYou earned 4 frequent renter points");
}

TEST(CustomerTest, frequentPointsWithANewReleaseMovieForOnlyOneDay) {
    Customer customer("Olivier");
    int frequentPoints = customer.computeFrequentPoint(Rental( Movie( "Avengers: Endgame", Movie::NEW_RELEASE ), 1));

    ASSERT_EQ(frequentPoints, 1);
}

TEST(CustomerTest, frequentPointsWithAChildrenMovieForTwoDays) {
    Customer customer("Olivier");
    int frequentPoints = customer.computeFrequentPoint(Rental( Movie( "Oui-Oui", Movie::CHILDRENS ), 2));

    ASSERT_EQ(frequentPoints, 1);
}

TEST(CustomerTest, frequentPointsWithAChildrenMovieForOneDay) {
    Customer customer("Olivier");
    int frequentPoints = customer.computeFrequentPoint(Rental( Movie( "Non-Non", Movie::CHILDRENS ), 1));

    ASSERT_EQ(frequentPoints, 1);
}

TEST(CustomerTest, frequentPointsWithANewReleaseMovieForTwoDays) {
    Customer customer("Olivier");
    int frequentPoints = customer.computeFrequentPoint(Rental( Movie( "Avengers: Endgame", Movie::NEW_RELEASE ), 2));

    ASSERT_EQ(frequentPoints, 2);
}

TEST(CustomerTest, rentalPriceWithARegularMovieForTwoDays) {
    Customer customer("Olivier");
    double price = customer.computeRentalPrice(Rental( Movie( "James Bond : Casino Royale", Movie::REGULAR ), 2));

    ASSERT_EQ(price, 2);
}

TEST(CustomerTest, rentalPriceWithARegularMovieForThreeDays) {
    Customer customer("Olivier");
    double price = customer.computeRentalPrice(Rental( Movie( "James Bond : Casino Royale", Movie::REGULAR ), 3));

    ASSERT_EQ(price, 3.5);
}

TEST(CustomerTest, rentalPriceWithANewReleaseForOneDay) {
    Customer customer("Olivier");
    double price = customer.computeRentalPrice(Rental( Movie( "Avengers : Endgame", Movie::NEW_RELEASE ), 1));

    ASSERT_EQ(price, 3);
}

TEST(CustomerTest, rentalPriceWithAChildrensMovieForThreeDays) {
    Customer customer("Olivier");
    double price = customer.computeRentalPrice(Rental( Movie( "Oui-Oui", Movie::CHILDRENS), 3));

    ASSERT_EQ(price, 1.5);
}

TEST(CustomerTest, rentalPriceWithAChildrensMovieForFourDays) {
    Customer customer("Olivier");
    double price = customer.computeRentalPrice(Rental( Movie( "Oui-Oui", Movie::CHILDRENS), 4));

    ASSERT_EQ(price, 3);
}

