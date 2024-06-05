
#include "Control.h"
#include "View.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <limits>
#include <vector>

using namespace std;

Control::Control(){
    filter = new Filter;
}

Control::~Control(){
    delete filter;
}

void Control::launch(){
    cout<<"Launching..."<<endl;
    initFromFile();
    searchListings();
    cout<<"Done initializing"<<endl;
    int choice = -1;


    while (true){
        choice = -1;
        vector<string> menu ={
            "No filter",
            "Filter by category",
            "Filter by price range",
            "Filter by price range and category",
            "Print current listings",
            "Expand listing"
        };

        view.menu(menu, choice, *filter);
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
        if (choice == 0)break;
        switch (choice)
        {
        case 1:
            resetFilter(); break;
        case 2:
            filterByCategory(); break;
        case 3:
            filterByPriceRange(); break;
        case 4:
            filterByPriceRangeAndCategory(); break;
        case 5:
            printCurrentListings(); break;
        case 6:
            expandListing(); break;
        default:
            break;
        }
        
    }

    cout << "Good-bye!"<<endl;
}

/* *Sigh* Windows embeds a carriage return that is not picked up by getline.
*  This function removes the carriage return from a string.
*/
void stripCR(string& str){
    str.erase(remove(str.begin(), str.end(), '\r'), str.end());
}

void Control::initFromFile(){
    ifstream listingFile;
    listingFile.open("listings/listings.txt");
    string user, title, description, category, price;


    while( true ){
        cout<<"Reading..."<<endl;
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

        stringstream ss(price);
        Price p;
        ss >> p;
        market.addListing(user, title, cat::stringToCategory(category), description, p);
    }

    listingFile.close();
    
}

void Control::resetFilter(){
    delete filter;
    filter = new Filter;
    searchListings();
}

void Control::filterByCategory(){
    cat::Category category;
    view.promptCategory(category);
    delete filter;
    filter = new Cat_Filter(category);
    searchListings();
}

void Control::filterByPriceRange(){
    Price min, max;
    view.promptPriceRange(min, max);
    delete filter;
    filter = new Price_Filter(min, max);
    searchListings();
}

void Control::filterByPriceRangeAndCategory(){
    cat::Category category;
    view.promptCategory(category);
    Price min, max;
    view.promptPriceRange(min, max);
    delete filter;
    filter = new PriceAndCat_Filter(min, max, category);
    searchListings();
}

void Control::searchListings(){
    searchResults.clear();
    market.searchListings(*filter, searchResults);
}

void Control::printCurrentListings(){
    view.printListings(searchResults);
}

void Control::expandListing(){
    int choice = -1;
    view.listingMenu(searchResults, choice);
    if (choice != 0){
        view.printListing(*searchResults[choice-1]);
    }
}
