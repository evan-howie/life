#include "../include/grid.h"
#include <random>

Grid::Grid(unsigned int w, unsigned int h)
        : w_{w}, h_{h} {
    length_ = w * h;
    cells_ = new unsigned char[length_] {};
}

Grid::~Grid(){
    delete[] cells_;
}

unsigned int Grid::get_width(){ return w_; }
unsigned int Grid::get_height(){ return h_; }
unsigned int Grid::get_length(){ return length_; }
unsigned char Grid::get_cell(unsigned int x, unsigned int y){ return cells_[x + y * w_]; }
bool Grid::is_active(unsigned int x, unsigned int y){ return cells_[x + y * w_] && 1; }

void Grid::toggle(unsigned int x, unsigned int y){
    cells_[x + y * w_] ^= 0b00000001;
}

void Grid::init_rand(){
    std::random_device dev;
    std::mt19937 rng{dev()};
    std::bernoulli_distribution dist{0.5};

    for (int i = 0; i < length_; ++i){
        cells_[i] = dist(rng);
    }
}
