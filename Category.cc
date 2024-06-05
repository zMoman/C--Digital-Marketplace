#include "Category.h"


std::string cat::categoryToString(Category category){
    switch(category){
        case computers: return "computers";
        case cars: return "cars";
        case books: return "books";
        case music: return "music";
        case clothing: return "clothing";
        case furniture: return "furniture";
        case misc: return "misc";
    }
    return "misc";
}

cat::Category cat::stringToCategory(const std::string& category){
    if (category.find("computers")!=std::string::npos) return cat::computers;
    if (category.find("cars")!=std::string::npos) return cat::cars;
    if (category.find("books")!=std::string::npos) return cat::books;
    if (category.find("music")!=std::string::npos) return cat::music;
    if (category.find("clothing")!=std::string::npos) return cat::clothing;
    if (category.find("furniture")!=std::string::npos) return cat::furniture;

    return cat::misc;
}

