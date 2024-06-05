#include "Filter.h"

bool Filter::matches(const Listing& l) const{
    return true;
}

void Filter::print(ostream& ost) const{
    ost<<"This filter will select everything"<<endl;
}

Price_Filter::Price_Filter(const Price& min, const Price& max) : min(min), max(max) {}

bool Price_Filter::matches(const Listing& l) const {
    return l.getPrice2().inRange(min, max);
}

void Price_Filter::print(ostream &ost) const {
    ost << "This matches a listing in the given price range $" << min.getPrice() << " - $" << max.getPrice() << endl;
}

Cat_Filter::Cat_Filter(const cat::Category& c) : category(c) {}

bool Cat_Filter::matches(const Listing& l) const {
    return category == l.getCategory();
}

void Cat_Filter::print(ostream& ost) const {
    ost << "This matches a listing with the given category: " << categoryToString(category) << endl; // Assuming categoryToString exists
}

PriceAndCat_Filter::PriceAndCat_Filter(const Price& min, const Price& max, const cat::Category& c)
: Price_Filter(min, max), Cat_Filter(c) {}

bool PriceAndCat_Filter::matches(const Listing& l) const {
    return Price_Filter::matches(l) && Cat_Filter::matches(l);
}


void PriceAndCat_Filter::print(ostream& ost) const {
    ost << "This matches a listing with the given category: " << categoryToString(Cat_Filter::category)
        << " and in the price range $" << min.getPrice()
        << " - $" << max.getPrice() << endl;
}


