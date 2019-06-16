#include "PrinterToText.h"

#include <sstream>

std::string PrinterToText::printName(Customer& customer) const{
    std::ostringstream result;
    result << "Rental Record for " << customer.getName() << "\n";
    return result.str();
}

std::string PrinterToText::printAmountForMovie(Movie& movie, double amount) const{
    std::ostringstream result;
    result << "\t" << movie.getTitle() << "\t"
           << amount << "\n";
    return result.str();
}

std::string PrinterToText::printAmount(double totalAmount) const{
    std::ostringstream result;
    result << "Amount owed is " << totalAmount << "\n";
    return result.str();
}

std::string PrinterToText::printFrequentPoints(int frequentRenterPoints) const{
    std::ostringstream result;
    result << "You earned " << frequentRenterPoints
           << " frequent renter points";
    return result.str();
}