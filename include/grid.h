// Written by: Evan Howie
// Date: January 1st, 2024
// Description: This class represents a grid of cells. It is used to store
//              the state of life and to update its state.


class Grid {
private:
    unsigned char *cells_;
    unsigned char *temp_;
    unsigned int w_;
    unsigned int h_;
    unsigned int length_;

    /**
     * Sets the cell at position
     * 
     * @param x: x position of cell
     * @param y: y position of cell
    */
    void set_cell_(unsigned int x, unsigned int y);

    /**
     * clears the cell at position
     * 
     * @param x: x position of cell
     * @param y: y position of cell
    */
    void clear_cell_(unsigned int x, unsigned int y);
public:
    /**
     * Constructor
     * 
     * @param width: width of grid
     * @param height: height of grid
    */
    Grid(unsigned int width, unsigned int height);

    /**
     * Destructor
    */
    ~Grid();

    /**
     * Returns the width of the grid
     * 
     * @return width of grid
    */
    unsigned int get_width();

    /**
     * Returns the height of the grid
     * 
     * @return height of grid
    */
    unsigned int get_height();

    /**
     * Returns the length of the grid array
     * 
     * @return length of grid
    */
    unsigned int get_length();

    /**
     * Returns the cell byte at position
     * 
     * @param x: x position of cell
     * @param y: y position of cell
     * @return cell value
    */
    unsigned char get_cell(unsigned int x, unsigned int y);

    /**
     * Returns the LSB of cell at position
     * 
     * @param x: x position of cell
     * @param y: y position of cell
     * @return LSB of cell
    */
    bool is_active(unsigned int x, unsigned int y);

    /**
     * Toggles cell value at given position
     * 
     * @param x: x position of cell
     * @param y: y position of cell
    */
    void toggle(unsigned int x, unsigned int y);

    /**
     * Initializes grid cells to random values
    */
    void init_rand();

    /**
     * Initializes grid cells from a file
     * 
     * @param path: path to file
    */
    void init_file(char* path);

    /**
     * Moves the grid to the next iteration of life
    */
    void step();

    /**
     * Saves grid state to file
     * @param path: path to file
    */
    void save(char* path);
};
