#include <SFML/Graphics.hpp>
#include "../include/grid.h"

#define PROGRAM_NAME "Life"

#define WHITE sf::Color::White
#define BLACK sf::Color::Black
#define GRAY sf::Color{160, 160, 160}

/**
 * Initialize the game of life
 * 
 * @param gw: width of the grid in cells
 * @param gh: height of the grid in cells
 * @param cell_size: 2d vector of the cell dimensions
 * @param delay: delay in ms between game ticks
*/
void life(unsigned int gw, unsigned int gh, sf::Vector2f cell_size, unsigned int delay);

/**
 * Draw the grid on a specified window
 * 
 * @param window: window you would like to render on
 * @param grid: the game grid
 * @param cell_size: 2d vector of the cell dimensions
*/
void draw_grid(sf::RenderWindow &window, Grid &grid, sf::Vector2f &cell_size);

void life(unsigned int gw, unsigned int gh, sf::Vector2f cell_size, unsigned int delay){
    Grid grid{gw, gh};
    grid.init_rand();

    sf::RenderWindow window{sf::VideoMode{(int) cell_size.x * gw, (int) cell_size.y * gh}, PROGRAM_NAME};
    window.setPosition(sf::Vector2i{100, 100});

    while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
            }
        }

        window.clear(WHITE);
        draw_grid(window, grid, cell_size);
        grid.step();

        window.display();
        sf::sleep(sf::milliseconds(delay));
    }
}

void draw_grid(sf::RenderWindow &window, Grid &grid, sf::Vector2f &cell_size){
    int w = grid.get_width();
    int h = grid.get_height();

    sf::RectangleShape rect;
    rect.setSize(cell_size);
    rect.setOutlineColor(GRAY);
    rect.setOutlineThickness(1);

    for (int i = 0; i < w * h; ++i){
        unsigned int x = i % w;
        unsigned int y = i / w;

        bool active{grid.is_active(x, y)};
        sf::Color cell_color = active ? BLACK : WHITE;

        rect.setPosition(x * cell_size.x, y * cell_size.y);
        // rect.setFillColor(sf::Color{255 * grid.get_cell(x, y) >> 1, 255 * grid.get_cell(x, y) >> 1,255 * grid.get_cell(x, y) >> 1 });
        rect.setFillColor(cell_color);

        window.draw(rect);
    }
}

/**
 * GAME PARAMETERS
*/

#define GRID_WIDTH 50
#define GRID_HEIGHT 40
#define CELL_SIZE sf::Vector2f{15, 15}
#define DELAY 50


int main(){
    life(GRID_WIDTH, GRID_HEIGHT, CELL_SIZE, DELAY);
    return 0;
}