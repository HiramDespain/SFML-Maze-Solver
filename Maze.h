#ifndef MAZE_H
#define MAZE_H

#include <SFML/Graphics.hpp>
#include <array>


class Maze {
public:
    /**
     * @brief singleton constuction wrapper, only allows a single instance of the maze.
     * 
     * @param fileName 
     */
    static Maze* makeMaze(std::ifstream*);

    /**
     * @brief deletes the maze
     * 
     */
    static void deleteMaze();

    /**
     * @brief draws the maze to the window
     * 
     * @param window 
     */
    void drawMaze(sf::RenderWindow &window) const;

    /**
     * @brief Get the Maze Array 
     * 
     * @return char* 
     */
    char** getMazeArray() const;

    /**
     * @brief get the char a a specific loc
     * 
     * @param loc 
     * @return char 
     */
    char getMazeChar(std::array<int, 2> &loc) const;

    /**
     * @brief Set the Mazechar at a location
     * 
     * @param Loc 
     */
    void setMazeChar(std::array<int, 2> &Loc, char c);

    /**
     * @brief get the xDim of the maze
     * 
     * @return int 
     */
    int getXDim() const;

    /**
     * @brief get the y dim of the maze
     * 
     * @return int 
     */
    int getYDim() const;

    /**
     * @brief get mazeStart
     * 
     */
    std::array<int, 2> getMazeStart() const;

private:
    /**
     * @brief employed in the constuctor to create _mazeArray
     * 
     */
    void processFile();

    //the maze array
    char** _mazeArray;

    //Maze start
    std::array<int, 2> _arrayStart;

    //pointer to the input file
    std::ifstream* _pInputFile;

    int _xDim, _yDim; // array size

    //used to make the maze a singleton
    static inline bool _instantiated = false; //is true if a maze exists

    static inline Maze* _pMaze = nullptr; //pointer to the maze object

    Maze(); //the constructor
    ~Maze(); //destructor
    Maze operator=(const Maze&) = delete; //disallow copying
};

#endif