
#ifndef PRICE_H
#define PRICE_H

#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

class Price{
    private:
    double price;

    public:
    Price(double price);
    Price();

    double getPrice()const;

    bool equals(Price& p)const;
    bool lessThan(Price& p)const;

    bool inRange(const Price& min, const Price& max)const;
    void print();
    
    bool operator<(const Price& other) const {
        return price < other.price;
    }

    bool operator==(const Price& other) const {
        return (price == other.price);
    }

    friend ostream& operator<<(ostream& o, Price& p){
       o<<"$"<<fixed<<setprecision(2)<<p.price<<endl;
       return o;
    }

    friend istream& operator>>(istream& i, Price& p){
        string input;
        i>>input; 
        try {
        p.price = std::stod(input);
        } catch (const invalid_argument& e) {
        cerr << "Invalid argument: " << input << endl;
        } catch (const out_of_range& e) {
        cerr << "Out of range: " << input << endl;
        }
        return i;
     }


};
#endif