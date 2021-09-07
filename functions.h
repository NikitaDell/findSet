#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>

std::string removeSigns(const std::string& str)
{
    std::string strNoSigns;
    for(auto& sign: str){
        if(!(sign == '\t' || sign == '\"' || sign == ',' || sign == ' '))
            strNoSigns += sign;
    }
    return strNoSigns;
}

#endif