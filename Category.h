#ifndef CATEGORY_H
#define CATEGORY_H

#include <iostream>
#include <string>
#include <vector>


namespace cat{
    
    enum Category {computers, cars, books, music, clothing, furniture, misc, size};

    std::string categoryToString(Category category);
    Category stringToCategory(const std::string& category);
    

}
#endif