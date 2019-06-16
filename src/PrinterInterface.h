//
// Created by Baptiste on 16/06/2019.
//

#ifndef GEN_LABO5_PRINTERINTERFACE_H
#define GEN_LABO5_PRINTERINTERFACE_H

#include <string>

class Customer;

/**
 * Cette classe permet de rendre modulaire l'affichage des statement rendant ainsi
 * facile la portabilité vers de nouveaux formats
 */
class PrinterInterface {

public:
    virtual std::string printName(Customer& customer) const = 0;
    virtual std::string printAmountForMovie(Movie& movie, double amount) const = 0;
    virtual std::string printAmount(double totalAmount) const = 0;
    virtual std::string printFrequentPoints(int frequentRenterPoints) const = 0;
};


#endif //GEN_LABO5_PRINTERINTERFACE_H
