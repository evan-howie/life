#include "../include/grid.h"
#include <cstring>
#include <random>
#include <iostream>
#include <fstream>

Grid::Grid(unsigned int w, unsigned int h)
        : w_{w}, h_{h} {
    length_ = w * h;
    cells_ = new unsigned char[length_] {};
    temp_ = new unsigned char[length_] {};
}

Grid::~Grid(){
    delete[] cells_;
    delete[] temp_;
}

void Grid::set_cell_(unsigned int x, unsigned int y){
    // calculate offsets
    int left = x == 0 ? w_ - 1 : -1;
    int right = x == w_ - 1 ? 1 - w_ : 1;
    int top = y == 0 ? length_ - w_ : -w_; // wraps around since limited grid
    int bot = y == h_ - 1 ? w_ - length_ : w_;

    // recalculate cell values to include new neighbour
    unsigned char *cell = cells_ + x + y * w_;
    *(cell) |= 0x01;
    *(cell + top + left) += 2;
    *(cell + top) += 2;
    *(cell + top + right) += 2;
    *(cell + left) += 2;
    *(cell + right) += 2;
    *(cell + bot + left) += 2;
    *(cell + bot) += 2;
    *(cell + bot + right) += 2;
}

void Grid::clear_cell_(unsigned int x, unsigned int y){
    // calculate offsets
    int left = x == 0 ? w_ - 1 : -1;
    int right = x == w_ - 1 ? 1 - w_ : 1;
    int top = y == 0 ? length_ - w_ : -w_; // wraps around since limited grid
    int bot = y == h_ - 1 ? w_ - length_ : w_;

    // recalculate cell values to include new neighbour
    unsigned char *cell = cells_ + x +  y * w_;
    *(cell) &= ~0x01;
    *(cell + top + left) -= 2;
    *(cell + top) -= 2;
    *(cell + top + right) -= 2;
    *(cell + left) -= 2;
    *(cell + right) -= 2;
    *(cell + bot + left) -= 2;
    *(cell + bot) -= 2;
    *(cell + bot + right) -= 2;
}

unsigned int Grid::get_width(){ return w_; }
unsigned int Grid::get_height(){ return h_; }
unsigned int Grid::get_length(){ return length_; }
unsigned char Grid::get_cell(unsigned int x, unsigned int y){ 
    if (x < 0 || x >= w_) return 0b10000000;
    if (y < 0 || y >= h_) return 0b10000000;
    return cells_[x + y * w_];
}
bool Grid::is_active(unsigned int x, unsigned int y){ return cells_[x + y * w_] & 1; }

void Grid::toggle(unsigned int x, unsigned int y){
    is_active(x, y) ? clear_cell_(x, y) : set_cell_(x, y);
}

void Grid::init_rand(){
    std::random_device dev;
    std::mt19937 rng{dev()};
    std::bernoulli_distribution dist{0.5};

    for (int i = 0; i < length_; ++i){
        unsigned int x = i % w_;
        unsigned int y = i / w_;
        if (dist(rng)) set_cell_(x, y);
    }
}

void Grid::init_bitmap(char *path){
    std::ifstream bitmap_file;
    bitmap_file.open(path);
    unsigned char *bitmap = new unsigned char[w_ * h_];

    bitmap_file >> bitmap;
    std::cout << bitmap << std::endl;
    bitmap_file.close();
    delete[] bitmap;
}

void Grid::step(){
    memcpy(temp_, cells_, length_);
    for (int i = 0; i < length_; ++i){
        if (temp_[i] == 0) continue;

        unsigned int x = i % w_;
        unsigned int y = i / w_;

        unsigned char *cell = temp_ + i;

        unsigned char count = *cell >> 1;
        if (*cell & 0x01){
            if (count != 2 && count != 3)
                clear_cell_(x, y);
        }
        else if (count == 3) set_cell_(x, y);
    }
}
