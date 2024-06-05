#include "CuMarket.h"

CuMarket::~CuMarket() {
    for (int i = 0; i < listings.getSize(); ++i) {
        delete listings[i]; 
    }
}

void CuMarket::addListing(const string& userName, const string& title, const cat::Category& category, const string& description, const Price& price) {
    if (listings.isFull()) {
        cout << "Error: The listings list is full. Cannot add more listings." << endl;
    } else {

        Listing* newListing = new Listing(userName, title, category, description, price);
        listings += newListing; 
    }
}

void CuMarket::removeListing(const string& title) {
    for (int i = 0; i < listings.getSize(); ++i) {
        if (listings[i]->getTitle() == title) {
            delete listings[i]; 
            listings -= listings[i]; 
            return;
        }
    }
    cout << "Error: No listing found with the title '" << title << "'." << endl;
}

void CuMarket::searchListings(const Filter& filter, List<Listing*>& searchList) const {
    for (int i = 0; i < listings.getSize(); ++i) {
        if (filter.matches(*listings[i])) {
            searchList += listings[i]; 
        }
    }
}
