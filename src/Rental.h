#include <utility>

// Rental.h
#ifndef RENTAL_H
#define RENTAL_H
#include "Movie.h"
#include <memory>

class Rental {
public:
    using Member = std::shared_ptr<Movie>;
    Rental( Member movie, int daysRented );
    Rental();

    virtual int getDaysRented() const;
    virtual Member getMovie() const;

private:
    Member _movie;
    int _daysRented;
};

inline Rental::
Rental( Member movie, int daysRented ):
        _movie(std::move(movie)), _daysRented( daysRented ) {
}

inline int Rental::
getDaysRented() const { return _daysRented; }

inline Rental::Member Rental::
getMovie() const { return _movie; }

inline Rental::Rental() {

}

#endif // RENTAL_H