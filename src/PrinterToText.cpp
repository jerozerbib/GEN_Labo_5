//
// Created by Baptiste on 16/06/2019.
//

#include "PrinterToText.h"

#include <sstream>

std::string PrinterToText::printName(Customer& customer) const{
    ostringstream result;
    result << "Rental Record for " << customer.getName() << "\n";
    return result.str();
}

std::string PrinterToText::printAmountForMovie(Movie& movie, double amount) const{
    ostringstream result;
    result << "\t" << movie.getTitle() << "\t"
           << amount << "\n";
    return result.str();
}

std::string PrinterToText::printAmount(double totalAmount) const{
    ostringstream result;
    result << "Amount owed is " << totalAmount << "\n";
    return result.str();
}

std::string PrinterToText::printFrequentPoints(int frequentRenterPoints) const{
    ostringstream result;
    result << "You earned " << frequentRenterPoints
           << " frequent renter points";
    return result.str();
}