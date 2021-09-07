#ifndef PRODUCTSLIST_H
#define PRODUCTSLIST_H

#include "product.h"
#include <vector> // vector

class ProductsList
{
private:
    std::vector<Product> products;
public:
    ProductsList();
    ProductsList(const std::vector<Product>& vec);
    ProductsList(const ProductsList& pl);

    void loadDocument(const char* filename = "document.txt");
    void loadSet(const char* filename = "set.txt");
    void printDocument();
    void printSet();
    void findSet(const ProductsList& set, const char* resultFile = "result.txt");
};

#endif // PRODUCT_LIST_H
