#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MovieMock.h"
#include "Rental.h"
#include <memory>

TEST(RentalTest, test) {
    std::shared_ptr<MovieMock> mm(new MovieMock());

    EXPECT_CALL(*mm, getPriceCode()).WillRepeatedly(testing::Return(Movie::CHILDRENS));
    EXPECT_CALL(*mm, getTitle()).WillRepeatedly(testing::ReturnRef("Oui-Oui"));

    Rental rental(mm, 1);

    EXPECT_EQ(rental.getMovie(), mm);
}
