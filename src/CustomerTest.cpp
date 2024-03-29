#include "gtest/gtest.h"

#include "Customer.h"
#include "RentalMock.h"
#include "MovieMock.h"
#include <memory>

TEST(CustomerTest, statementForNoMovie) {
    Customer customer("Baptiste");

    ASSERT_EQ(customer.statement(),
              "Rental Record for Baptiste\nAmount owed is 0\nYou earned 0 frequent renter points");
}

TEST(CustomerTest, statementForOneChildMovie) {
    Customer customer("Florian");
    customer.addRental(Rental(std::make_shared<Movie>("Oui-Oui", Movie::CHILDRENS), 1));

    ASSERT_EQ(customer.statement(),
              "Rental Record for Florian\n\tOui-Oui\t1.5\nAmount owed is 1.5\nYou earned 1 frequent renter points");
}

TEST(CustomerTest, statementForOneNewReleaseMovie) {
    Customer customer("Florian");
    customer.addRental(Rental(std::make_shared<Movie>("Avengers: Empire Strikes Back", Movie::NEW_RELEASE), 2));

    ASSERT_EQ(customer.statement(),
              "Rental Record for Florian\n\tAvengers: Empire Strikes Back\t6\nAmount owed is 6\nYou earned 2 frequent renter points");
}


TEST(CustomerTest, statementForOneMovieWithoutTag) {
    Customer customer("Florian");
    customer.addRental(Rental(std::make_shared<Movie>("Sharknado"), 14));

    ASSERT_EQ(customer.statement(),
              "Rental Record for Florian\n\tSharknado\t20\nAmount owed is 20\nYou earned 1 frequent renter points");
}

TEST(CustomerTest, statementForTwoMovies) {
    Customer customer("Jeremy");
    customer.addRental(Rental(std::make_shared<Movie>("L'etroit Mousquetaire"), 1));
    customer.addRental(Rental(std::make_shared<Movie>("Tous les trous sont permis", Movie::CHILDRENS), 2));

    ASSERT_EQ(customer.statement(),
              "Rental Record for Jeremy\n\tL'etroit Mousquetaire\t2\n\tTous les trous sont permis\t1.5\nAmount owed is 3.5\nYou earned 2 frequent renter points");
}

TEST(CustomerTest, statementForThreeMovies) {
    Customer customer("Olivier");
    customer.addRental(Rental(std::make_shared<Movie>("Karate Kid"), 7));
    customer.addRental(Rental(std::make_shared<Movie>("Avengers: Endgame", Movie::NEW_RELEASE), 5));
    customer.addRental(Rental(std::make_shared<Movie>("Snow White", Movie::CHILDRENS), 3));

    ASSERT_EQ(customer.statement(),
              "Rental Record for Olivier\n\tKarate Kid\t9.5\n\tAvengers: Endgame\t15\n\tSnow White\t1.5\nAmount owed is 26\nYou earned 4 frequent renter points");
}

TEST(CustomerTest, frequentPointsWithANewReleaseMovieForOnlyOneDay) {
    Customer customer("Olivier");
    int frequentPoints = customer.computeFrequentPoint(
            Rental(std::make_shared<Movie>("Avengers: Endgame", Movie::NEW_RELEASE), 1));

    ASSERT_EQ(frequentPoints, 1);
}

TEST(CustomerTest, frequentPointsWithAChildrenMovieForTwoDays) {
    Customer customer("Olivier");
    int frequentPoints = customer.computeFrequentPoint(Rental(std::make_shared<Movie>("Oui-Oui", Movie::CHILDRENS), 2));

    ASSERT_EQ(frequentPoints, 1);
}

TEST(CustomerTest, frequentPointsWithAChildrenMovieForOneDay) {
    Customer customer("Olivier");
    int frequentPoints = customer.computeFrequentPoint(Rental(std::make_shared<Movie>("Non-Non", Movie::CHILDRENS), 1));

    ASSERT_EQ(frequentPoints, 1);
}

TEST(CustomerTest, frequentPointsWithANewReleaseMovieForTwoDays) {
    Customer customer("Olivier");
    int frequentPoints = customer.computeFrequentPoint(
            Rental(std::make_shared<Movie>("Avengers: Endgame", Movie::NEW_RELEASE), 2));

    ASSERT_EQ(frequentPoints, 2);
}

TEST(CustomerTest, rentalPriceWithARegularMovieForTwoDays) {
    Customer customer("Olivier");
    double price = customer.computeRentalPrice(
            Rental(std::make_shared<Movie>("James Bond : Casino Royale", Movie::REGULAR), 2));

    ASSERT_EQ(price, 2);
}

TEST(CustomerTest, rentalPriceWithARegularMovieForThreeDays) {
    Customer customer("Olivier");
    double price = customer.computeRentalPrice(
            Rental(std::make_shared<Movie>("James Bond : Casino Royale", Movie::REGULAR), 3));

    ASSERT_EQ(price, 3.5);
}

TEST(CustomerTest, rentalPriceWithANewReleaseForOneDay) {
    Customer customer("Olivier");
    double price = customer.computeRentalPrice(
            Rental(std::make_shared<Movie>("Avengers : Endgame", Movie::NEW_RELEASE), 1));

    ASSERT_EQ(price, 3);
}

TEST(CustomerTest, rentalPriceWithAChildrensMovieForThreeDays) {
    Customer customer("Olivier");
    double price = customer.computeRentalPrice(Rental(std::make_shared<Movie>("Oui-Oui", Movie::CHILDRENS), 3));

    ASSERT_EQ(price, 1.5);
}

TEST(CustomerTest, rentalPriceWithAChildrensMovieForFourDays) {
    Customer customer("Olivier");
    double price = customer.computeRentalPrice(Rental(std::make_shared<Movie>("Oui-Oui", Movie::CHILDRENS), 4));

    ASSERT_EQ(price, 3);
}


TEST(CustomerTest, statementForOneChildMovieMocked) {
    RentalMock *rm = new RentalMock();

    EXPECT_CALL(*rm, getDaysRented()).WillRepeatedly(testing::Return(1));
    EXPECT_CALL(*rm, getMovie()).WillRepeatedly(
            testing::Return(std::shared_ptr<Movie>(new Movie("Oui-Oui", Movie::CHILDRENS))));

    Customer customer("Florian");
    customer.addRental(Rental(rm->getMovie(), rm->getDaysRented()));

    EXPECT_EQ(customer.statement(),
              "Rental Record for Florian\n\tOui-Oui\t1.5\nAmount owed is 1.5\nYou earned 1 frequent renter points");
    delete rm;
}

TEST(CustomerTest, statementForOneNewReleaseMovieMocked) {
    RentalMock *rm = new RentalMock();

    EXPECT_CALL(*rm, getDaysRented()).WillRepeatedly(testing::Return(2));
    EXPECT_CALL(*rm, getMovie()).WillRepeatedly(
            testing::Return(std::shared_ptr<Movie>(new Movie("Avengers: Empire Strikes Back", Movie::NEW_RELEASE))));


    Customer customer("Florian");
    customer.addRental(Rental(rm->getMovie(), rm->getDaysRented()));

    ASSERT_EQ(customer.statement(),
              "Rental Record for Florian\n\tAvengers: Empire Strikes Back\t6\nAmount owed is 6\nYou earned 2 frequent renter points");
    delete rm;
}


TEST(CustomerTest, statementForOneMovieWithoutTagMocked) {
    RentalMock *rm = new RentalMock();

    EXPECT_CALL(*rm, getDaysRented()).WillRepeatedly(testing::Return(14));
    EXPECT_CALL(*rm, getMovie()).WillRepeatedly(testing::Return(std::shared_ptr<Movie>(new Movie("Sharknado"))));

    Customer customer("Florian");
    customer.addRental(Rental(rm->getMovie(), rm->getDaysRented()));

    ASSERT_EQ(customer.statement(),
              "Rental Record for Florian\n\tSharknado\t20\nAmount owed is 20\nYou earned 1 frequent renter points");
    delete rm;
}

TEST(CustomerTest, statementForTwoMoviesMocked) {
    RentalMock *rm = new RentalMock();

    EXPECT_CALL(*rm, getDaysRented()).WillOnce(testing::Return(1)).WillOnce(testing::Return(2));
    EXPECT_CALL(*rm, getMovie())
            .WillOnce(testing::Return(std::shared_ptr<Movie>(new Movie("L'etroit Mousquetaire"))))
            .WillOnce(
                    testing::Return(std::shared_ptr<Movie>(new Movie("Tous les trous sont permis", Movie::CHILDRENS))));

    Customer customer("Jeremy");
    customer.addRental(Rental(rm->getMovie(), rm->getDaysRented()));
    customer.addRental(Rental(rm->getMovie(), rm->getDaysRented()));

    ASSERT_EQ(customer.statement(),
              "Rental Record for Jeremy\n\tL'etroit Mousquetaire\t2\n\tTous les trous sont permis\t1.5\nAmount owed is 3.5\nYou earned 2 frequent renter points");
    delete rm;
}

TEST(CustomerTest, statementForThreeMoviesMocked) {
    RentalMock *rm = new RentalMock();

    EXPECT_CALL(*rm, getDaysRented()).WillOnce(testing::Return(7)).WillOnce(testing::Return(5)).WillOnce(
            testing::Return(3));
    EXPECT_CALL(*rm, getMovie())
            .WillOnce(testing::Return(std::shared_ptr<Movie>(new Movie("Karate Kid"))))
            .WillOnce(
                    testing::Return(std::shared_ptr<Movie>(new Movie("Avengers: Endgame", Movie::NEW_RELEASE))))
            .WillOnce(testing::Return(std::shared_ptr<Movie>(new Movie("Snow White", Movie::CHILDRENS))));

    Customer customer("Olivier");
    customer.addRental(Rental(rm->getMovie(), rm->getDaysRented()));
    customer.addRental(Rental(rm->getMovie(), rm->getDaysRented()));
    customer.addRental(Rental(rm->getMovie(), rm->getDaysRented()));

    ASSERT_EQ(customer.statement(),
              "Rental Record for Olivier\n\tKarate Kid\t9.5\n\tAvengers: Endgame\t15\n\tSnow White\t1.5\nAmount owed is 26\nYou earned 4 frequent renter points");
    delete rm;
}

TEST(CustomerTest, frequentPointsWithANewReleaseMovieForOnlyOneDayMocked) {
    RentalMock *rm = new RentalMock();

    EXPECT_CALL(*rm, getDaysRented()).WillOnce(testing::Return(1));
    EXPECT_CALL(*rm, getMovie())
            .WillOnce(testing::Return(std::shared_ptr<Movie>(new Movie("Avengers: Endgame", Movie::NEW_RELEASE))));

    Customer customer("Olivier");

    int frequentPoints = customer.computeFrequentPoint(Rental(rm->getMovie(), rm->getDaysRented()));

    ASSERT_EQ(frequentPoints, 1);
    delete rm;
}

TEST(CustomerTest, frequentPointsWithAChildrenMovieForTwoDaysMocked) {
    RentalMock *rm = new RentalMock();

    EXPECT_CALL(*rm, getDaysRented()).WillOnce(testing::Return(2));
    EXPECT_CALL(*rm, getMovie())
            .WillOnce(testing::Return(std::shared_ptr<Movie>(new Movie("Oui-Oui", Movie::CHILDRENS))));
    Customer customer("Olivier");
    int frequentPoints = customer.computeFrequentPoint(Rental(rm->getMovie(), rm->getDaysRented()));

    ASSERT_EQ(frequentPoints, 1);
    delete rm;
}

TEST(CustomerTest, frequentPointsWithAChildrenMovieForOneDayMocked) {
    RentalMock *rm = new RentalMock();

    EXPECT_CALL(*rm, getDaysRented()).WillOnce(testing::Return(1));
    EXPECT_CALL(*rm, getMovie())
            .WillOnce(testing::Return(std::shared_ptr<Movie>(new Movie("Non-Non", Movie::CHILDRENS))));
    Customer customer("Olivier");
    int frequentPoints = customer.computeFrequentPoint(Rental(rm->getMovie(), rm->getDaysRented()));

    ASSERT_EQ(frequentPoints, 1);
    delete rm;
}

TEST(CustomerTest, frequentPointsWithANewReleaseMovieForTwoDaysMocked) {
    RentalMock *rm = new RentalMock();

    EXPECT_CALL(*rm, getDaysRented()).WillOnce(testing::Return(2));
    EXPECT_CALL(*rm, getMovie())
            .WillOnce(testing::Return(std::shared_ptr<Movie>(new Movie("Avengers: Endgame", Movie::NEW_RELEASE))));
    Customer customer("Olivier");
    int frequentPoints = customer.computeFrequentPoint(Rental(rm->getMovie(), rm->getDaysRented()));

    ASSERT_EQ(frequentPoints, 2);
    delete rm;
}

TEST(CustomerTest, rentalPriceWithARegularMovieForTwoDaysMocked) {
    RentalMock *rm = new RentalMock();

    EXPECT_CALL(*rm, getDaysRented()).WillOnce(testing::Return(2));
    EXPECT_CALL(*rm, getMovie())
            .WillOnce(testing::Return(std::shared_ptr<Movie>(new Movie("James Bond : Casino Royale", Movie::REGULAR))));
    Customer customer("Olivier");
    double price = customer.computeRentalPrice(Rental(rm->getMovie(), rm->getDaysRented()));

    ASSERT_EQ(price, 2);
    delete rm;
}

TEST(CustomerTest, rentalPriceWithARegularMovieForThreeDaysMocked) {
    RentalMock *rm = new RentalMock();

    EXPECT_CALL(*rm, getDaysRented()).WillOnce(testing::Return(3));
    EXPECT_CALL(*rm, getMovie())
            .WillOnce(testing::Return(std::shared_ptr<Movie>(new Movie("James Bond : Casino Royale", Movie::REGULAR))));
    Customer customer("Olivier");
    double price = customer.computeRentalPrice(Rental(rm->getMovie(), rm->getDaysRented()));

    ASSERT_EQ(price, 3.5);
    delete rm;
}

TEST(CustomerTest, rentalPriceWithANewReleaseForOneDayMocked) {
    RentalMock *rm = new RentalMock();

    EXPECT_CALL(*rm, getDaysRented()).WillOnce(testing::Return(1));
    EXPECT_CALL(*rm, getMovie())
            .WillOnce(testing::Return(std::shared_ptr<Movie>(new Movie("Avengers : Endgame", Movie::NEW_RELEASE))));
    Customer customer("Olivier");
    double price = customer.computeRentalPrice(Rental(rm->getMovie(), rm->getDaysRented()));

    ASSERT_EQ(price, 3);
    delete rm;
}

TEST(CustomerTest, rentalPriceWithAChildrensMovieForThreeDaysMocked) {
    RentalMock *rm = new RentalMock();

    EXPECT_CALL(*rm, getDaysRented()).WillOnce(testing::Return(3));
    EXPECT_CALL(*rm, getMovie())
            .WillOnce(testing::Return(std::shared_ptr<Movie>(new Movie("Oui-Oui", Movie::CHILDRENS))));
    Customer customer("Olivier");
    double price = customer.computeRentalPrice(Rental(rm->getMovie(), rm->getDaysRented()));

    ASSERT_EQ(price, 1.5);
    delete rm;
}

TEST(CustomerTest, rentalPriceWithAChildrensMovieForFourDaysMocked) {
    RentalMock *rm = new RentalMock();

    EXPECT_CALL(*rm, getDaysRented()).WillOnce(testing::Return(4));
    EXPECT_CALL(*rm, getMovie())
            .WillOnce(testing::Return(std::shared_ptr<Movie>(new Movie("Oui-Oui", Movie::CHILDRENS))));
    Customer customer("Olivier");
    double price = customer.computeRentalPrice(Rental(rm->getMovie(), rm->getDaysRented()));

    ASSERT_EQ(price, 3);
    delete rm;
}

