#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <iostream>
#include <string>
#include "Filter.h"
#include "View.h"
#include "CuMarket.h"

using namespace std;

class Control {
		
	public:
		Control();
		~Control();		
		void launch();
	
	private:
		void initFromFile();
		void resetFilter();
		void filterByCategory();
		void filterByPriceRange(); 
		void filterByPriceRangeAndCategory();
		void searchListings(); 
		void printCurrentListings();
		void expandListing();
		
		View view;
		List<Listing*> searchResults;
		Filter* filter;
		CuMarket market;	

	
};
#endif