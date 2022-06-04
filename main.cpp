#include "imgui.h"
#include "imgui-SFML.h"

#include <iostream>
#include <string>
#include <fstream>


// #include <SFML/Graphics/CircleShape.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>

constexpr unsigned int pixelcountx = 5;
constexpr unsigned int pixelcounty = 5;

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

void applyValuesFromFile(const char* filename, std::vector<std::vector<int>>& pixelarr){
    std::ifstream file;
    file.open(filename, std::ios::in);
    if(!file){
        std::cout << "File can't be opened\n";
        exit(EXIT_FAILURE);
    }

    int Yindex = 0;
    std::string linestring;
    while(!file.eof()){
        std::getline(file, linestring);
        linestring.erase(std::remove(linestring.begin(), linestring.end(), ' '), linestring.end()); //remove whitespaces
        for(int i = 0; i < pixelcountx; ++i){
            pixelarr[Yindex][i] = linestring[i];
        }
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
    std::vector<std::vector<int>> pixelarr(pixelcounty , std::vector<int> (pixelcountx, 0)); // two dimensional vector
    applyValuesFromFile("test.txt", pixelarr);    

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
                drawScalePixel(shape, window, sf::Vector2i(pixelcountx, pixelcounty), sf::Vector2i(x, y), pixelarr[y][x] == '1' ? sf::Color::Blue : sf::Color::White);
            }
        }
        

        ImGui::SFML::Render(window);
        window.display();
    }

    ImGui::SFML::Shutdown();

    return EXIT_SUCCESS;
}