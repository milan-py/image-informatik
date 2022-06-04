#include <iostream>
#include <limits>
#include "hidden.hpp"

int main(){ 
    std::string filename;
    std::string message;
    int width;

    std::cout << "filename: ";
    std::cin >> filename;
    if(std::cin.fail()){
        std::cout << "input failed\n";
        return EXIT_FAILURE;
    }
    
    std::cout << "message: ";
    std::cin >> message;
    if(std::cin.fail()){
        std::cout << "input failed\n";
        return EXIT_FAILURE;
    }

    std::cin.clear();
    std::cin.ignore(INT_MAX, '\n');
    std::cout << "width: ";
    std::cin >> width;
    if(std::cin.fail()){
        std::cout << "input failed\n";
        return EXIT_FAILURE;
    }



    writeHiddenMsg(filename.c_str(), message, width);
}