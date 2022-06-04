#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
#include <bitset>

std::string insertSpaces(const std::string& str){
    std::string newstr = str;
    int i = str.length();
    int j = 1;
    while(i--){
        newstr.insert(j, 1, ' ');
        j += 2;
    }
    return newstr;
}

std::string readHiddenMsg(const char* filename){ 
    std::ifstream file;
    file.open(filename, std::ios::in);
    if(!file){
        std::cout << "File can't be opened\n";
        exit(EXIT_FAILURE);
    }
    int i = 0;

    std::string linestring;
    std::string complete;

    while(!file.eof()){
        std::getline(file, linestring);
        if(i >= 3){
            linestring.erase(std::remove(linestring.begin(), linestring.end(), ' '), linestring.end()); //remove whitespaces
            complete += linestring;
            std::cout << "linestring: " << linestring << '\n';
        }
        ++i;
    }

    std::string message;

    for(int i = 0; i < complete.size()/8; ++i){
        message += static_cast<char>(std::bitset<8>(complete.substr(i * 8, 8)).to_ulong());
    }

    return message;
}

void writeHiddenMsg(const char* filename, std::string msg, unsigned int pixelWidth){
    std::ofstream file;
    unsigned int pixelHeight = msg.length()/(pixelWidth*(static_cast<float>(3)/8)) + 1;

    file.open(filename, std::ios::out);

    if(!file){
        std::cout << "Failed opening the file " << "\""  << filename << "\"\n";
        exit(EXIT_FAILURE);
    }

    std::string bitstring;

    file << "P3\n";
    file << pixelWidth << ' ' << pixelHeight << '\n';
    file << "1\n";
    for(char& i: msg){
        bitstring += std::bitset<8>(i).to_string();
    }

    std::string tempstring;
    for(int y = 0; y < pixelHeight; ++y){
        for(int x = 0; x < pixelWidth; ++x){
            if((y*pixelWidth+x)*3 < bitstring.length()){
                tempstring = bitstring.substr((y*pixelWidth+x)*3, 3);
                if(tempstring.length() == 3){
                    file << insertSpaces(bitstring.substr((y*pixelWidth+x)*3, 3)) << "  ";
                } 
                else if(tempstring.length() == 2){
                    file << insertSpaces(bitstring.substr((y*pixelWidth+x)*3, 3) + "0") << "  ";
                }
                else{
                    file << insertSpaces(bitstring.substr((y*pixelWidth+x)*3, 3) + "00") << "  ";
                }
            }
            else{
                file << "0 0 0   ";
            }
        }
        file << '\n';
    }
}