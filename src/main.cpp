#include <SFML/Graphics.hpp>
#include "../include/grid.h"

#define PROGRAM_NAME "Life"
#define CELL_SIZE 15
#define CELL_SIZE_VEC sf::Vector2f{CELL_SIZE, CELL_SIZE}

#define WHITE sf::Color::White
#define BLACK sf::Color::Black
#define GRAY sf::Color{160, 160, 160}

void life();
void draw_grid(sf::RenderWindow &window, Grid &grid);
int main();

void life(){
    unsigned int gw = 50;
    unsigned int gh = 40;

    Grid grid{gw, gh};
    grid.init_rand();

    sf::RenderWindow window{sf::VideoMode{CELL_SIZE * gw, CELL_SIZE * gh}, PROGRAM_NAME};
    window.setPosition(sf::Vector2i{100, 100});

    while (window.isOpen()){
        // Process events
        sf::Event event;
        while (window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        window.clear(WHITE);
        draw_grid(window, grid);

        window.display();
    }
}

void draw_grid(sf::RenderWindow &window, Grid &grid){
    int w = grid.get_width();
    int h = grid.get_height();

    for (int i = 0; i < w * h; ++i){
        unsigned int x = i % w;
        unsigned int y = i / w;

        bool active{grid.is_active(x, y)};
        sf::Color cell_color = active ? BLACK : WHITE;

        sf::RectangleShape rect;
        rect.setPosition(x * CELL_SIZE, y * CELL_SIZE);
        rect.setSize(CELL_SIZE_VEC);
        rect.setFillColor(cell_color);
        rect.setOutlineColor(GRAY);
        rect.setOutlineThickness(1);

        window.draw(rect);
    }
}

int main(){
    life();
    return 0;
}