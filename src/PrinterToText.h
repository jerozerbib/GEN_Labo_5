//
// Created by Baptiste on 16/06/2019.
//

#ifndef GEN_LABO5_PRINTERTOTEXT_H
#define GEN_LABO5_PRINTERTOTEXT_H


#include "PrinterInterface.h"
#include "Movie.h"

class PrinterToText : PrinterInterface {
public:
    std::string printName(Customer& customer) const;
    std::string printAmountForMovie(Movie& movie, double amount) const;
    std::string printAmount(double totalAmount) const;
    std::string printFrequentPoints(int frequentRenterPoints) const;
};


#endif //GEN_LABO5_PRINTERTOTEXT_H
