#include "Listing.h"
Listing::Listing(const string& user, const string& title, const cat::Category& category, const string& desc, const Price& price){
    this->user=user;
    this->title=title;
    this->category=category;
    this->desc=desc;
    this->price=price;
}

string Listing::getName()const{
    return this->user;
}

string Listing::getTitle()const{
    return this->title;
}

Price Listing::getPrice2()const{
    return this->price;
}

cat::Category Listing::getCategory()const{
    return this->category;
}

bool Listing::lessThan(Listing& listing)const{
    if(this->title<listing.title){
        return true;
    }
    else{
        return false;
    }
}

void Listing::print()const{
    cout<<"User:\t"<<this->user<<"\nTitle:\t"<<this->title<<"\nCategory:\t"<<categoryToString(this->category)<<"\nDescription:\t"<<this->desc<<"\nPrice:\t$"<<fixed<<setprecision(2)<<this->price.getPrice()<<endl;
}
