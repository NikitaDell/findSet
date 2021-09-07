
#include "productsList.h"

int main()
{
    ProductsList *document = new ProductsList;
    ProductsList *set = new ProductsList;
 
    std::cout << "Документ: " << std::endl;
    document->loadDocument();
    document->printDocument();

    std::cout << "\nНабор: " << std::endl;
    set->loadSet();
    set->printSet();

    std::cout << "\nОтвет: " << std::endl;
    document->findSet(*set);

    delete document;
    delete set;
    
    return 0;
}
