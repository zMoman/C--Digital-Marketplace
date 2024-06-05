#ifndef LISTING_H
#define LISTING_H

#include <iomanip>
#include <iostream>
#include <string>
#include "Price.h"
#include "Category.h"
using namespace std;

class Listing {
    private:
    string user,title,desc;
    cat::Category category;
    Price price;

    public:
    Listing(const string& user, const string& title, const cat::Category& category, const string& desc, const Price& price);

    string getName()const;
    string getTitle()const;
    Price getPrice2()const;
    cat::Category getCategory()const;
    bool lessThan(Listing& listing)const;
    void print()const;
    friend ostream& operator<<(ostream& o, Listing& l){
        o<<"User:\t"<<l.user<<"\nTitle:\t"<<l.title<<"\nCategory:\t"<<categoryToString(l.category)<<"\nDescription:\t"<<l.desc<<"\nPrice:\t$"<<fixed<<setprecision(2)<<l.price.getPrice()<<endl;
        return o;
    }
};

#endif