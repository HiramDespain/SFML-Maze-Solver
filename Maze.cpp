#include "Maze.h"

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>


Maze* Maze::makeMaze(std::ifstream* pInputFile) {
    if (!_instantiated) {
        _instantiated = true;
    }
    if (_pMaze == nullptr) {
        _pMaze = new Maze();
        _pMaze->_pInputFile = pInputFile;
        _pMaze->processFile();
    }
    return _pMaze;
}

void Maze::deleteMaze() {
    if (_instantiated) {
        _instantiated = false;
    }
    delete _pMaze;
    _pMaze = nullptr;
}

Maze::Maze() {
    _mazeArray = nullptr;
}

Maze::~Maze() {
    if (_mazeArray != nullptr) {
        for (int i = 0; i < _yDim; ++i) {
            delete[] _mazeArray[i];
        }
        delete[] _mazeArray;
        _mazeArray = nullptr;
    }
}

char** Maze::getMazeArray() const {
    return _mazeArray;
}

char Maze::getMazeChar(std::array<int, 2> &loc) const {
    return _mazeArray[loc[0]][loc[1]];
}

void Maze::setMazeChar(std::array<int, 2> &loc, char c) {
    _mazeArray[loc[0]][loc[1]] = c;
}

int Maze::getXDim() const {
    return _xDim;
}

int Maze::getYDim() const {
    return _yDim;
}

std::array<int, 2> Maze::getMazeStart() const {
    return _arrayStart;
}

void Maze::processFile() {
    std::string inLine = "";
    std::string whitespace = " \t\n\r\f\v"; // Common whitespace characters
    

    getline(*_pInputFile, inLine);
    for (long unsigned i = 0; i < inLine.length(); i++) {
        if (inLine[i] == ' ') {
            _xDim = stoi(inLine.substr(i + 1, inLine.size()));
            _yDim = stoi(inLine.substr(0, i));
        }
    }

    if (_xDim > 102 || _xDim < 3 || _yDim < 4 || _yDim > 102) {
        std::cout << "The inputted maze appears to have dimensions outside of the given bounds." << std::endl;
        std::cout << "Unknown behavior may occur." << std::endl;
        std::cout << "Restart with a new file, or press enter to continue."; std::cin >> inLine;
    }
    //it is so very tempting to make an array class to make the below safe.
    
    _mazeArray = new char*[_yDim];
    for (int i = 0; i < _yDim; i++) {
        _mazeArray[i] = new char[_xDim];
    }
    //read in the rest of the array
    int i = 0;
    while (getline(*_pInputFile, inLine)) {
        int j = 0;
        for (char c : inLine) {
            _mazeArray[i][j] = c;
            if (tolower(c) == 's') {
                _arrayStart = {i, j};
            }
        j++;}
    i++;}
}

void Maze::drawMaze(sf::RenderWindow &window) const {
    for (int i = 0; i < _yDim; i++) {
        for (int j = 0; j < _xDim; j++) {
            sf::RectangleShape rect({15, 15});
            rect.setPosition({j * 15.f, i * 15.f});

            switch (_mazeArray[i][j]) {

            case '#':
                rect.setFillColor(sf::Color::Black);

            break;
            case '.' :
                rect.setFillColor(sf::Color::White);

            break;
            case 'S' :
                rect.setFillColor(sf::Color::Green);

            break;
            case 'E' :
                rect.setFillColor(sf::Color::Red);

            break;
            case '%' :
                rect.setFillColor(sf::Color::Magenta);

            break;
            case 'y' : 
                rect.setFillColor(sf::Color::Yellow);

            break;
            }
            window.draw(rect);
        }
    }
}
