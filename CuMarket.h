#ifndef CUMARKET_H
#define CUMARKET_H

#include "List.h" 
#include "Listing.h"
#include "Filter.h"
#include <iostream>
#include <string>

class CuMarket {
private:
    List<Listing*> listings; 

public:
    CuMarket() {} 
    ~CuMarket(); 

    void addListing(const string& userName, const string& title, const cat::Category& category, const string& description, const Price& price);
    void removeListing(const string& title);
    void searchListings(const Filter& filter, List<Listing*>& searchList) const;
};

#endif 
