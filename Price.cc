#include "Price.h"

Price::Price(double price){
    this->price=price;
}

Price::Price(){
    this->price=0;
}

double Price::getPrice()const{
    return this->price;
}

bool Price::equals(Price& p)const{

    if(p.price==this->price){
        return true;       
    }
    else{
        return false;
    }
}

bool Price::lessThan(Price& p)const{
    if(p.price<this->price){
        return true;
    } else{
    return false;
    }
}

bool Price::inRange(const Price& min, const Price& max)const{
    if(this->price>=min.price && this->price<=max.price){
        return true;
    } else{
        return false;
    }
}

 void Price::print(){
        cout<<"$"<<setprecision(2)<<this->price<<endl;
    }


