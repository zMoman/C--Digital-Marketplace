
#include "View.h"
#include <limits>
#include <vector>



void View::menu(vector<string>& menu, int& choice, const Filter& filter)
{
  cout << endl;
  cout << "Current filter: " << filter << endl;
  cout << "Please make a selection:"<< endl<<endl;
  for (int i = 0; i < menu.size(); ++i){
    cout<<"  ("<<i+1<<") "<<menu[i]<<endl;
  }
  cout << "  (0) Exit" << endl<<endl;

  cout << "Enter your selection: ";
  cin >> choice;
  if (choice == 0)
    return;

  while (choice < 0 || choice > menu.size()) {
    cout << "Enter your selection: ";
    cin >> choice;
  }
}

void View::menu(vector<string>& menu, int& choice)
{
  cout << endl;
  cout << "Please make a selection:"<< endl<<endl;
  for (int i = 0; i < menu.size(); ++i){
    cout<<"  ("<<i+1<<") "<<menu[i]<<endl;
  }
  cout << "  (0) Exit" << endl<<endl;

  cout << "Enter your selection: ";
  cin >> choice;
  if (choice == 0)
    return;

  while (choice < 0 || choice > menu.size()) {
    cout << "Enter your selection: ";
    cin >> choice;
  }
}

void View::printListings(const List<Listing*>& listings)
{
  for (int i = 0; i < listings.getSize(); ++i){
    cout  << i+1 << ")\n" << *listings[i] << endl;
  }
}

void View::listingMenu(const List<Listing*>& listings, int& choice)
{
  cout << endl;
  cout << "Please make a selection:"<< endl<<endl;
  for (int i = 0; i < listings.getSize(); ++i){
    cout << i+1 << ")\n" << *listings[i] << endl;
  }
  cout << "  (0) Exit" << endl<<endl;

  cout << "Enter your selection: ";
  cin >> choice;
  if (choice == 0)
    return;

  while (choice < 0 || choice > listings.getSize()) {
    cout << "Enter your selection: ";
    cin >> choice;
  }
}

void View::printListing(const Listing& listing)
{
    listing.print();
}

void View::promptPriceRange(Price& min, Price& max)
{
  cout << "Enter the minimum price: ";
  cin >> min;
  cout << "Enter the maximum price: ";
  cin >> max;
}

void View::promptCategory(cat::Category& category)
{
  int choice;
  cout << "Please select a category:"<< endl<<endl;
  for (int i = 0; i < cat::size; ++i){
    cout << "  (" << i+1 << ") " << cat::categoryToString(static_cast<cat::Category>(i)) << endl;
  }
  cout << "Enter your selection: ";
  cin >> choice;
  while (choice < 1 || choice > cat::size) {
    cout << "Enter your selection: ";
    cin >> choice;
  }
  category = static_cast<cat::Category>(choice-1);
}