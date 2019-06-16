#include <gmock/gmock.h>
#include "Rental.h"

class RentalMock : public Rental {

public:
    MOCK_METHOD0(getDaysRented, int());
    MOCK_CONST_METHOD0(getMovie, Rental::Member());
};