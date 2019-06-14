#include <gmock/gmock.h>
#include "Movie.h"

class MovieMock : public Movie {

public:
    MOCK_METHOD0(getPriceCode, int());
    MOCK_CONST_METHOD0(getTitle, const std::string&());
};