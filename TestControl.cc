
#include "TestControl.h"
#include <limits>
#include <vector>
#include <algorithm>
#include <fstream>
#include "Filter.h"

using namespace std;

void TestControl::launch(){

    vector<string> menu ={
        "Test add and search Listings - no filter, test for proper printing of Listings",
        "Test add and search Listings - filter by category",
        "Test add and search Listings - filter by price range",
        "Test add and search Listings - filter by price range and category",
        "Test all and get mark"
    };

    int choice = -1;

    // For test purposes
    // CuMarket* market = new CuMarket;
    // vector<string> users;
    // vector<string> titles;
    // vector<string> categories;
    // vector<string> descriptions;
    // vector<string> prices;
    // initMarket(*market, users, titles, categories, descriptions, prices);
    // delete market;
    
    while (choice!= 0){
        view.menu(menu, choice);
        tester.clearInputBuffer();
        switch(choice){
            case 0: break;
            case 1: tester.recordMark(1, testNoFilter(),8); break;
            case 2: tester.recordMark(2, testFilterByCategory(),8); break;
            case 3: tester.recordMark(3, testFilterByPriceRange(),8); break;
            case 4: tester.recordMark(4, testFilterByPriceRangeAndCategory(),8); break;
            case 5: tester.recordMark(5, testAllAndMark(), 32); break;
        }
    }
    std::cout<<"exiting program!!!"<<endl;
}

/* *Sigh* Windows embeds a carriage return that is not picked up by getline.
*  This function removes the carriage return from a string.
*/
void stripCR(string& str){
    str.erase(remove(str.begin(), str.end(), '\r'), str.end());
}

void TestControl::initMarket(CuMarket& market, 
                        vector<string>& users, 
                        vector<string>& titles, 
                        vector<string>& categories, 
                        vector<string>& descriptions, 
                        vector<string>& prices){
    ifstream listingFile;
    listingFile.open("listings/listings.txt");
    string user, title, description, category, price;


    while( true ){
        std::cout<<"Reading..."<<endl;
        if(!getline(listingFile, user))break;
        getline(listingFile, title);
        getline(listingFile, category);
        getline(listingFile, description);
        getline(listingFile, price);

        // Remove carriage return
        stripCR(user);
        stripCR(title);
        stripCR(category);
        stripCR(description);
        stripCR(price);


        users.push_back(user);
        titles.push_back(title);
        categories.push_back(category);
        descriptions.push_back(description);
        prices.push_back(price);

        Price p;

        stringstream ss(price);
        ss >> p;
        market.addListing(user, title, cat::stringToCategory(category), description, p);
    }

    listingFile.close();
}

void TestControl::initMarketTitlesOnly(CuMarket& market, 
                        vector<string>& titles){
    ifstream listingFile;
    listingFile.open("listings/listings.txt");
    string user, title, description, category, price;


    while( true ){
        std::cout<<"Reading..."<<endl;
        if(!getline(listingFile, user))break;
        getline(listingFile, title);
        getline(listingFile, category);
        getline(listingFile, description);
        getline(listingFile, price);

        titles.push_back(title);

        market.addListing(user, title, cat::stringToCategory(category), description, Price(stod(price)));
    }

    listingFile.close();
}

int TestControl::testNoFilter(){
    cout<<"Testing add and search Listings - no filter"<<endl;
    CuMarket market;
    vector<string> users;
    vector<string> titles;
    vector<string> categories;
    vector<string> descriptions;
    vector<string> prices;
    initMarket(market, users, titles, categories, descriptions, prices);
    Filter filter;
    List<Listing*> results;
    market.searchListings(filter, results);
    cout<<"Printing all listings"<<endl;
    tester.initCapture();
    view.printListings(results);
    tester.endCapture();

    int errors = 0;
    int mark = 0;
    tester.find(titles, errors);
    if (errors>0){
        cout<<"Error: "<<errors<<" titles not found"<<endl;
    }else{
        cout<<"All titles found, 2 marks"<<endl;
        mark += 2;
    }

    tester.find(categories, errors);
    if (errors>0){
        cout<<"Error: "<<errors<<" categories not found"<<endl;
    }else{
        cout<<"All categories found, 2 marks"<<endl;
        mark += 2;
    }

    tester.find(descriptions, errors);
    if (errors>0){
        cout<<"Error: "<<errors<<" descriptions not found"<<endl;
    }else{
        cout<<"All descriptions found, 2 marks"<<endl;
        mark += 2;
    }

    tester.find(prices, errors);
    if (errors>0){
        cout<<"Error: "<<errors<<" prices not found"<<endl;
    }else{
        cout<<"All prices found, 2 marks"<<endl;
        mark += 2;
    }

    cout<<"Test complete, mark: "<<mark<<"/8"<<endl;
    return mark;

}

int TestControl::testFilterByCategory(){
    cout<<"Testing add and search Listings - filter by category"<<endl;
    CuMarket market;
    vector<string> users;
    vector<string> titles;
    vector<string> categories;
    vector<string> descriptions;
    vector<string> prices;
    initMarket(market, users, titles, categories, descriptions, prices);
    Cat_Filter filter(cat::books);
    List<Listing*> results;
    market.searchListings(filter, results);
    cout<<"Printing all listings in category books"<<endl;
    tester.initCapture();
    view.printListings(results);
    tester.endCapture();

    int errors = 0;
    int mark = 0;
    vector<int> bookIndices;
    vector<int> absentIndices;
    for (int i = 0; i < categories.size(); ++i){
        if (categories[i] == "books"){
            bookIndices.push_back(i);
        }else{
            absentIndices.push_back(i);
        }
    }
    tester.find(bookIndices, titles, errors);
    if (errors>0){
        cout<<"Error: "<<errors<<" titles not found"<<endl;
    }else{
        cout<<"All titles found, 2 marks"<<endl;
        mark += 2;
    }

    tester.confirmAbsent(absentIndices, titles, errors);
    if (errors>0){
        cout<<"Error: "<<errors<<" titles found for absent categories"<<endl;
    }else{
        cout<<"No titles found for absent categories, 2 marks"<<endl;
        mark += 2;
    }

    results.clear();
    filter = Cat_Filter(cat::misc);
    market.searchListings(filter, results);
    cout<<"Printing all listings in category misc"<<endl;
    tester.initCapture();
    view.printListings(results);
    tester.endCapture();

    errors = 0;
    vector<int> miscIndices;
    absentIndices.clear();
    for (int i = 0; i < categories.size(); ++i){
        if (categories[i] == "misc"){
            miscIndices.push_back(i);
        }else{
            absentIndices.push_back(i);
        }
    }

    tester.find(miscIndices, titles, errors);
    if (errors>0){
        cout<<"Error: "<<errors<<" titles not found"<<endl;
    }else{
        cout<<"All titles found, 2 marks"<<endl;
        mark += 2;
    }

    tester.confirmAbsent(absentIndices, titles, errors);
    if (errors>0){
        cout<<"Error: "<<errors<<" titles found for absent categories"<<endl;
    }else{
        cout<<"No titles found for absent categories, 2 marks"<<endl;
        mark += 2;
    }


    cout<<"Test complete, mark: "<<mark<<"/8"<<endl;
    return mark;

}


int TestControl::testFilterByPriceRange(){
    cout<<"Testing add and search Listings - filter by price range"<<endl;
    CuMarket market;
    vector<string> users;
    vector<string> titles;
    vector<string> categories;
    vector<string> descriptions;
    vector<string> prices;
    initMarket(market, users, titles, categories, descriptions, prices);
    Price_Filter filter(Price(0), Price(10));
    List<Listing*> results;
    market.searchListings(filter, results);
    cout<<"Printing all listings in price range 0-10"<<endl;
    tester.initCapture();
    view.printListings(results);
    tester.endCapture();

    cout<<"Done printing..."<<endl;

    int errors = 0;
    int mark = 0;
    vector<int> cheapIndices;
    vector<int> absentIndices;
    for (int i = 0; i < prices.size(); ++i){
        if (stod(prices[i]) <= 10){
            cheapIndices.push_back(i);
        }else{
            absentIndices.push_back(i);
        }
    }
    tester.find(cheapIndices, titles, errors);
    if (errors>0){
        cout<<"Error: "<<errors<<" titles not found"<<endl;
    }else{
        cout<<"All titles found, 2 marks"<<endl;
        mark += 2;
    }

    tester.confirmAbsent(absentIndices, titles, errors);
    if (errors>0){
        cout<<"Error: "<<errors<<" titles found for absent prices"<<endl;
    }else{
        cout<<"No titles found for absent prices, 2 marks"<<endl;
        mark += 2;
    }

    results.clear();
    filter = Price_Filter(Price(100), Price(1000));
    market.searchListings(filter, results);
    cout<<"Printing all listings in price range 100-1000"<<endl;
    tester.initCapture();
    view.printListings(results);
    tester.endCapture();

    errors = 0;
    vector<int> midIndices;
    absentIndices.clear();
    for (int i = 0; i < prices.size(); ++i){
        if (stod(prices[i]) >=100 && stod(prices[i]) <= 1000){
            midIndices.push_back(i);
        }else{
            absentIndices.push_back(i);
        }
    }

    tester.find(midIndices, titles, errors);
    if (errors>0){
        cout<<"Error: "<<errors<<" titles not found"<<endl;
    }else{
        cout<<"All titles found, 2 marks"<<endl;
        mark += 2;
    }

    tester.confirmAbsent(absentIndices, titles, errors);
    if (errors>0){
        cout<<"Error: "<<errors<<" titles found for absent prices"<<endl;
    }else{
        cout<<"No titles found for absent prices, 2 marks"<<endl;
        mark += 2;
    }

    cout<<"Test complete, mark: "<<mark<<"/8"<<endl;
    return mark;
}

int TestControl::testFilterByPriceRangeAndCategory(){
    cout<<"Testing add and search Listings - filter by price range and category"<<endl;
    CuMarket market;
    vector<string> users;
    vector<string> titles;
    vector<string> categories;
    vector<string> descriptions;
    vector<string> prices;
    initMarket(market, users, titles, categories, descriptions, prices);
    PriceAndCat_Filter filter(Price(0), Price(10), cat::books);
    List<Listing*> results;
    market.searchListings(filter, results);
    cout<<"Printing all listings in price range 0-10 and category books"<<endl;
    tester.initCapture();
    view.printListings(results);
    tester.endCapture();

    int errors = 0;
    int mark = 0;
    vector<int> cheapBookIndices;
    vector<int> absentIndices;
    for (int i = 0; i < prices.size(); ++i){
        if (stod(prices[i]) <= 10 && categories[i] == "books"){
            cheapBookIndices.push_back(i);
        }else{
            absentIndices.push_back(i);
        }
    }
    tester.find(cheapBookIndices, titles, errors);
    if (errors>0){
        cout<<"Error: "<<errors<<" titles not found"<<endl;
    }else{
        cout<<"All titles found, 2 marks"<<endl;
        mark += 2;
    }

    tester.confirmAbsent(absentIndices, titles, errors);
    if (errors>0){
        cout<<"Error: "<<errors<<" titles found for absent prices and categories"<<endl;
    }else{
        cout<<"No titles found for absent prices and categories, 2 marks"<<endl;
        mark += 2;
    }

    results.clear();
    filter = PriceAndCat_Filter(Price(100), Price(1000), cat::misc);
    market.searchListings(filter, results);
    cout<<"Printing all listings in price range 100-1000 and category misc"<<endl;
    tester.initCapture();
    view.printListings(results);
    tester.endCapture();

    errors = 0;
    vector<int> midMiscIndices;
    absentIndices.clear();
    for (int i = 0; i < prices.size(); ++i){
        if (stod(prices[i]) >=100 && stod(prices[i]) <= 1000 && categories[i] == "misc"){
            midMiscIndices.push_back(i);
        }else{
            absentIndices.push_back(i);
        }
    }

    tester.find(midMiscIndices, titles, errors);
    if (errors>0){
        cout<<"Error: "<<errors<<" titles not found"<<endl;
    }else{
        cout<<"All titles found, 2 marks"<<endl;
        mark += 2;
    }

    tester.confirmAbsent(absentIndices, titles, errors);
    if (errors>0){
        cout<<"Error: "<<errors<<" titles found for absent prices and categories"<<endl;
    }else{
        cout<<"No titles found for absent prices and categories, 2 marks"<<endl;
        mark += 2;
    }

    cout<<"Test complete, mark: "<<mark<<"/8"<<endl;
    return mark;
}


int TestControl::testAllAndMark(){
    int mark = 0;
    mark += testNoFilter();
    mark += testFilterByCategory();
    mark += testFilterByPriceRange();
    mark += testFilterByPriceRangeAndCategory();
    return mark;
}