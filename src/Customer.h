// Customer.h
#ifndef CUSTOMER_H
#define CUSTOMER_H
#include <string>
#include <vector>
#include "Rental.h"
#include "PrinterInterface.h"

class Customer : PrinterInterface {
public:
    Customer();
    explicit Customer( const std::string& name );

    void addRental( const Rental& arg );
    std::string getName() const;
    std::string statement();

    double computeRentalPrice(const Rental &rental) const;

    int computeFrequentPoint(const Rental &rental) const;

private:
    std::string _name;
    std::vector< Rental > _rentals;
};

inline Customer::
Customer() {}

inline Customer::
Customer( const std::string& name )
        : _name( name ) {}

inline void Customer::
addRental( const Rental& arg ) { _rentals.push_back( arg ); }

inline std::string Customer::
getName() const { return _name; }

#endif // CUSTOMER_H