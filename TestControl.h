#ifndef TESTCONTROL_H
#define TESTCONTROL_H

#include <iostream>
#include <string>
#include <random>
#include <unordered_set>
#include <sstream>
#include "Listing.h"
#include "View.h"
#include "Tester.h"
#include "CuMarket.h"

using namespace std;

class TestControl {
		
	public:
		void launch();
	
	private:
		void initMarket(CuMarket& market, 
						vector<string>& user, 
						vector<string>& title, 
						vector<string>& category, 
						vector<string>& description, 
						vector<string>& price);
		void initMarketTitlesOnly(CuMarket& market, 
                        vector<string>& titles);
		
		//  vector<string> menu ={
		// 	"Test add and search Listings - no filter",
		// 	"Test add and search Listings - filter by category",
		// 	"Test add and search Listings - filter by price range",
		// 	"Test add and search Listings - filter by price range and category",
		// 	"Test all and get mark"
    	// };
		int testNoFilter();
		int testFilterByCategory();
		int testFilterByPriceRange();
		int testFilterByPriceRangeAndCategory();
		int testAllAndMark();

		

		View view;
		Tester tester;

		
	
};
#endif