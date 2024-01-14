#include <SFML/Graphics.hpp>
#include <iostream>
#include <set>
#include "../include/grid.h"

#define PROGRAM_NAME "Life Editor"
#define CELL_SIZE sf::Vector2f{15, 15}
#define WHITE sf::Color::White
#define BLACK sf::Color::Black
#define GRAY sf::Color{160, 160, 160}

void draw_grid(sf::RenderWindow &window, Grid &grid, sf::Vector2f cell_size){
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

int main(int argc, char* argv[]){
  if (argc != 3){
    std::cout << "Insufficient arguments." << std::endl;
    std::cout << "Usage: ./life_editor grid_width grid_height" << std::endl;
    exit(1);
  }
  unsigned int gw{(unsigned int) std::stoi(argv[1])};
  unsigned int gh{(unsigned int) std::stoi(argv[2])};

  Grid grid{gw, gh};

  sf::RenderWindow window{sf::VideoMode{(int) CELL_SIZE.x * gw, (int) CELL_SIZE.y * gh}, PROGRAM_NAME};
  window.setFramerateLimit(60);
  std::pair<int, int> point{};

  std::set<std::pair<int, int>> visited{};
  while (window.isOpen()){
        sf::Event event;
        while (window.pollEvent(event)){
            switch (event.type) {
                case sf::Event::Closed:
                    window.close();
                    break;
                case sf::Event::MouseButtonPressed:
                    if (event.mouseButton.button != sf::Mouse::Left) break;
                    point.first = event.mouseButton.x / CELL_SIZE.x;
                    point.second = event.mouseButton.y / CELL_SIZE.y;
                    if (grid.get_cell(point.first, point.second) == 0b10000000) break;

                    grid.toggle(point.first, point.second);
                    visited.insert(point);
                    break;
                case sf::Event::MouseMoved:
                    if (!sf::Mouse::isButtonPressed(sf::Mouse::Left)) break;
                    point.first = event.mouseMove.x / CELL_SIZE.x;
                    point.second = event.mouseMove.y / CELL_SIZE.y;
                    if (grid.get_cell(point.first, point.second) == 0b10000000) break;

                    if (visited.find(point) == visited.end()){
                        grid.toggle(point.first, point.second);
                        visited.insert(point);
                    }
                    break;
                case sf::Event::MouseButtonReleased:
                    if (event.mouseButton.button != sf::Mouse::Left) break;
                    visited.clear();
                    break;
            }
        }

        window.clear(WHITE);
        draw_grid(window, grid, CELL_SIZE);

        window.display();
    }
    return 0;
}
