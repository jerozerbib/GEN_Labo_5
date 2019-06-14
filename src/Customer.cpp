// Customer.cpp
#include <sstream>
#include <vector>
#include "Customer.h"

using std::ostringstream;
using std::vector;

using namespace std;

string Customer::statement(){
    double totalAmount = 0;
    int frequentRenterPoints = 0;
    vector< Rental >::iterator iter = _rentals.begin();
    vector< Rental >::iterator iter_end = _rentals.end();
    ostringstream result;
    result << "Rental Record for " << getName() << "\n";
    for ( ; iter != iter_end; ++iter ) {
        double thisAmount = 0;
        Rental each = *iter;

        // determine amounts for each line
        thisAmount = computeRentalPrice(each);

        // determine frequent points for a rental
        frequentRenterPoints += computeFrequentPoint(each);

        // show figures for this rental
        result << "\t" << each.getMovie().getTitle() << "\t"
               << thisAmount << "\n";
        totalAmount += thisAmount;
    }
    // add footer lines
    result << "Amount owed is " << totalAmount << "\n";
    result << "You earned " << frequentRenterPoints
           << " frequent renter points";
    return result.str();
}

int Customer::computeFrequentPoint(const Rental &rental) const {// add frequent renter points
    return ((rental.getMovie().getPriceCode() == Movie::NEW_RELEASE) && rental.getDaysRented() > 1) ? 2 : 1;
}

double Customer::computeRentalPrice(const Rental &rental) const {
    double amount = 0;
    switch (rental.getMovie().getPriceCode()) {
        case Movie::REGULAR:
            amount += 2;
            if (rental.getDaysRented() > 2)
                amount += (rental.getDaysRented() - 2) * 1.5;
            break;
        case Movie::NEW_RELEASE:
            amount += rental.getDaysRented() * 3;
            break;
        case Movie::CHILDRENS:
            amount += 1.5;
            if (rental.getDaysRented() > 3)
                amount += (rental.getDaysRented() - 3) * 1.5;
            break;
    }
    return amount;
}