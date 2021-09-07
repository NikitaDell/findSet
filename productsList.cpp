#include "productsList.h"
#include "functions.h" // removeSigns

#include <fstream> // ifstream
#include <sstream> // isstream
#include <algorithm> // find


ProductsList::ProductsList() 
{
    products = std::vector<Product>();
};

ProductsList::ProductsList(const std::vector<Product> &v) : products(v.cbegin(), v.cend()) 
{
};

ProductsList::ProductsList(const ProductsList& pl) : products(pl.products.cbegin(), pl.products.cend()) 
{
};

void ProductsList::loadDocument(const char* filename)
{
    std::ifstream document(filename);

    if(!document.is_open()){
        std::cout << "File wasn't opened" << std::endl;
    }
    else{
        std::string line;
        getline(document, line); // Названия колонок

        while(getline(document, line)){
            
            Product product;
            std::istringstream iss(line);
            std::string token;
            int i = 0; // Индекс для порядка чтения

            while(getline(iss, token, '\t')){
                
                if (i == 0) product.index = atoi(token.c_str());
                else if (i == 1) product.number = atoi(token.c_str());
                else if(i == 2) product.labels = removeSigns(token);
                i++;
                
            }

            products.push_back(product);            
        }
    }
    document.close();
};

void ProductsList::loadSet(const char* filename)
{
    std::ifstream set(filename);

    if(!set.is_open()){
        std::cout << "File wasn't opened" << std::endl;
    }
    else{
        std::string line;
        getline(set, line);

        while(getline(set, line)){
            Product product;
            
            std::istringstream iss(line);
            std::string token;
            int i = 0;

            while(getline(iss, token, '\t')){
                
                if(i == 0) product.labels = removeSigns(token);
                else if (i == 1) product.number = atoi(token.c_str());
                product.index = 0;
                i++;
                
            }

            products.push_back(product);            
        }
    }
    set.close();
};

void ProductsList::printDocument()
{
    std::cout << "Поз." << "\tКол-во" << "\tМетки" << std::endl;
    for(auto& product: products){
        std::cout << product.index <<  "\t" << product.number << "\t" << (product.labels) << std::endl;
    }
};

void ProductsList::printSet()
{
    std::cout << "Метки\t" << "Кол-во" << std::endl;
    for(auto& product: products){
         std::cout << product.labels << '\t' << product.number << std::endl;
    }
};


void ProductsList::findSet(const ProductsList &set, const char* resultFile)
{
    //Алгоритм поиска редактирует некоторые поля. Для этого создаются копии контейнеров 
    std::vector<Product> cp_set(set.products);
    std::vector<Product> cp_document(this->products);

    //Алгоритм поиска предпочитает одинарные метки 
    int* lastNumberProduct = nullptr; //  Указатель захватывает индекс последней Двойной (или более) метки
    bool flag = false; // флаг отслеживает, была ли метка набора обнаружена в двойной метке списка документа

    for (auto itr_set = cp_set.begin(); itr_set != cp_set.end(); itr_set++){
        for(auto itr_doc = cp_document.begin(); itr_doc != cp_document.end(); itr_doc++){
            
            if (itr_set->number <= itr_doc->number){ // Проверка, достаточно ли меток в позиции документа для набора

                if((itr_set->labels == itr_doc->labels)){
                    itr_set->index = itr_doc->index;
                    itr_doc->number -= itr_set->number; // Разность между количеством меток набора и документа (при удачном сравнении)
                                                        // исключает возможность нескольким меткам набора указывать на одну позицию списка документа
                    flag = false;
                    break; // Если набор и список имеют по одной метке, то при удачном сравнении дальнейший поиск не нужен.
                }
                else {
                    auto itr = find(itr_doc->labels.begin(), itr_doc->labels.end(), *(itr_set->labels.begin()));
                    if(itr != itr_doc->labels.end()){
                        itr_set->index = itr_doc->index;
                        lastNumberProduct = &itr_doc->number;
                        flag = true;
                        continue; // Если метка набора обнаружена в двойной метке, то поиск продолжается
                    }
                }
            }
        }
        if(flag == true) 
            lastNumberProduct -= itr_set->number;
        flag = false;
    }

    std::sort(cp_set.begin(), cp_set.end(), [](Product& x, Product& y){return x.index < y.index;}); // Сортировка результата по номеру позиции в документе

    std::cout << "Поз\t" << "Кол-во" << std::endl;  
    for(auto& i_set: cp_set){
        std::cout << i_set.index << "\t" << i_set.number << std::endl;
    }   

    std::ofstream result(resultFile);
    result << "Поз\t" << "Кол-во\n";  
    for(auto& i_set: cp_set){
        result << i_set.index << "\t" << i_set.number << "\n";
    }    
    result.close();
};