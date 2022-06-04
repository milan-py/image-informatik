#include "imgui.h"
#include "imgui-SFML.h"

#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

unsigned int pixelcountx = 10;
unsigned int pixelcounty = 10;

typedef struct simpleColor{
    bool r = false, g = false, b = false; 
}simpleColor;

void drawScalePixel(sf::RectangleShape& shape, sf::RenderWindow& window, sf::Vector2i pixelcount, sf::Vector2i position, const sf::Color& color){
    sf::Vector2f size{window.getSize().x/pixelcount.x, window.getSize().y/pixelcount.y};
    shape.setFillColor(color);
    shape.setSize(size);
    shape.setPosition(position.x * size.x, position.y * size.y);
    window.draw(shape);
}

void applyValuesFromFile(const char* filename, std::vector<std::vector<simpleColor>>& pixelarr){
    std::ifstream file;
    file.open(filename, std::ios::in);
    if(!file){
        std::cout << "File can't be opened\n";
        exit(EXIT_FAILURE);
    }

    std::string linestring;

    if(file.eof()){
        std::cout << "Wrong format\n";
        exit(EXIT_FAILURE);
    }

    std::getline(file, linestring);
    if(linestring != "P3"){
        std::cout << "Wrong format\n";
        exit(EXIT_FAILURE);
    }

    if(file.eof()){
        std::cout << "Wrong format\n";
        exit(EXIT_FAILURE);
    }
    std::getline(file, linestring);

    pixelcountx = std::atoi(linestring.substr(0, linestring.find(' ')).c_str()); 
    pixelcounty = std::atoi(linestring.substr(linestring.find(' ')).c_str()); 
    
    if(file.eof()){
        std::cout << "Wrong format\n";
        exit(EXIT_FAILURE);
    }
    std::getline(file, linestring);

    int Yindex = 0;
    
    std::string colorstring;
    while(!file.eof()){
        std::getline(file, linestring);
        linestring.erase(std::remove(linestring.begin(), linestring.end(), ' '), linestring.end()); //remove whitespaces
        for(int i = 0; i < pixelcountx; ++i){
            if(i * 3 + 3 > linestring.size()){
                break;
            }
            colorstring = linestring.substr(i * 3, 3);
            std::cout << colorstring << ' ';
            pixelarr[Yindex][i].r = colorstring[0] == '1';
            pixelarr[Yindex][i].g = colorstring[1] == '1';
            pixelarr[Yindex][i].b = colorstring[2] == '1';
        }
        std::cout << '\n';
        ++Yindex;
    }
    std::cout << "reloaded\n";
    file.close();
}

int main(int argc, char* argv[]){
    sf::RenderWindow window(sf::VideoMode(640, 480), "image");
    window.setFramerateLimit(60);
    ImGui::SFML::Init(window);

    // IMPORTANT first y, then x
    std::vector<std::vector<simpleColor>> pixelarr(pixelcounty , std::vector<simpleColor> (pixelcountx)); // two dimensional vector
    applyValuesFromFile("test.txt", pixelarr);    

    sf::Color pixelcol = sf::Color::White;

    sf::RectangleShape shape{sf::Vector2f(100, 100)};
    shape.setPosition(100, 100);

    sf::Clock deltaClock;
    while(window.isOpen()){
        sf::Event event;
        while(window.pollEvent(event)){
            ImGui::SFML::ProcessEvent(window, event);

            if(event.type == sf::Event::Closed or (event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Key::Escape)){
                window.close();
            }
            if(event.type == sf::Event::KeyPressed and event.key.code == sf::Keyboard::Key::F5){
                std::cout << "reloading...\n";
                applyValuesFromFile("test.txt", pixelarr);
            }

            if(event.type == sf::Event::Resized){ // proper behaviour when the window is resized
                sf::FloatRect visibleArea(0, 0, event.size.width, event.size.height);
                window.setView(sf::View(visibleArea));
            }
        }

        ImGui::SFML::Update(window, deltaClock.restart());

        window.clear();
        for(int y = 0; y < pixelarr.size(); y++){
            for(int x = 0; x < pixelarr[0].size(); x++){
                pixelcol = sf::Color(pixelarr[y][x].r * 255, pixelarr[y][x].g * 255, pixelarr[y][x].b * 255, 255);
                drawScalePixel(shape, window, sf::Vector2i(pixelcountx, pixelcounty), sf::Vector2i(x, y), pixelcol);
            }
        }

        ImGui::Begin("info");
            ImGui::Text("width: %u height: %u", pixelcountx, pixelcounty);
        ImGui::End();

        

        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();

    return EXIT_SUCCESS;
}