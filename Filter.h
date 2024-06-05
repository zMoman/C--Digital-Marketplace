#ifndef FILTER_H
#define FILTER_H

#include "Category.h"
#include "Price.h"
#include "Listing.h"
#include <iostream>
#include <string>

using namespace std;

class Filter {
public:
    virtual bool matches(const Listing& l) const;
    virtual void print(ostream& ost) const;

    friend ostream& operator<<(ostream& o, const Filter& f) {
        f.print(o);
        return o;
    }
};



class Price_Filter : virtual public Filter {
protected:
    Price min, max;

public:
    Price_Filter(const Price& min, const Price& max);
    virtual bool matches(const Listing& l) const override;
    virtual void print(ostream& ost) const override;
};





class Cat_Filter : virtual public Filter {
protected:
    cat::Category category;

public:
    Cat_Filter(const cat::Category& c);
    virtual bool matches(const Listing& l) const override;
    virtual void print(ostream& ost) const override;
};





class PriceAndCat_Filter : public Price_Filter, public Cat_Filter {
public:
    PriceAndCat_Filter(const Price& min, const Price& max, const cat::Category& c);
    virtual bool matches(const Listing& l) const override;
    virtual void print(ostream& ost) const override;

};

#endif // FILTER_H
