/* CSCI 200: Lab A6 - Maze Runner
* Author: Hiram Despain
*
* Takes in a .maze file and outputs an sfml based maze 
* then it solves said maze using either a depth first search or a breadth first search
* depending on the user's preference.
*/


#include <iostream> 
#include <SFML/Graphics.hpp>
#include <fstream>

#include "Maze.h"
#include "Solver.h"
using namespace std;

int main(int argc, char* argv[]) {
    ifstream inputFile;
    std::string fileName;
    bool isMazeFile = false;
    
    do {
        if (argc > 1){
        //process command line arguments
        //argv[0] is the run command
            std::cout << "You included what may be filename as a commandline argument." << std::endl;
            std::cout << "Attempting to use it as such." << std::endl;
            fileName = argv[1];
            if (argc > 2) {
                std::cout << "Using only the first commandline argument given: " << argv[1] << std::endl;
            }    
            inputFile.open(fileName);
            if(inputFile.fail()) {
                std::cout << "That file could not be accessed, it may not ." << std::endl;
            }
        }

        //if no command line argument was given, ask for a file name
        if (!inputFile.is_open()) {
            std::cout << "Please enter the name of the maze file: "; cin >> fileName;
            inputFile.open(fileName);
            while (inputFile.fail()) {
                std::cout << '\n' << "It would appear that that file was not found." << std::endl;
                std::cout << "Please try again: "; cin >> fileName;
                inputFile.open(fileName);
            }
        }

        //check if the file is a maze file
        if (fileName.find(".maze") == std::string::npos) {
            char input;
                std::cout << "This file doesn't appear the be a .maze file, do you wish to continue? (Y/N)"; cin >> input;
                input = tolower(input);
            while (input != 'y' && input != 'n') {
                std::cout << "That input was not understood, make sure you enter \'N\n or \'Y\'!" << std::endl;
                std::cout << "Try again: "; cin >> input;
                input = tolower(input);
            }
            //override to allow none .maze files
            isMazeFile = (input == 'y');
        } else {
            isMazeFile = true;
        }
        if (!isMazeFile) {
            argc = 0;
            inputFile.close();
        }
    } while (!isMazeFile);

    //make maze
    Maze* pMaze = Maze::makeMaze(&inputFile);
    std::cout << "Maze generated correctly!" << std::endl;

    //get user input for search type
    char searchType;
    bool DFS = false;
    std::cout << "How do you wish the maze to be solved? (D)FS or (B)FS: "; cin >> searchType;
    searchType = tolower(searchType);
    while (searchType != 'd' && searchType != 'b') {
        std::cout << "That input was not understood, make sure you enter \'D\' or \'B\'!" << std::endl;
        std::cout << "Try again: "; cin >> searchType;
        searchType = tolower(searchType);
    }
    if (searchType == 'd') {
        DFS = true;
    } else {
        DFS = false;
    }
    
    Solver* pSolver = Solver::makeSolver(pMaze, DFS);

    //create a window
    sf::RenderWindow window(sf::VideoMode((15 * pMaze->getXDim()), (15*pMaze->getYDim())), "A-Maze-ing", sf::Style::Default);
    window.setFramerateLimit(20);
    window.setVerticalSyncEnabled(true);

    bool solved = false;
    //drawing loop
    while (window.isOpen()) {
        if(!solved) { 
            //if solved stop solving
            solved = pSolver->solveMaze();
        }

        //draw on window
        window.clear();
        pMaze->drawMaze(window);
        pSolver->drawSolve(window);
        window.display();


        //woo event handling!
        sf::Event event; 
        while( window.pollEvent(event) ) {
            // if event type corresponds to pressing window X
            if(event.type == sf::Event::Closed) {
                // tell the window to close
                window.close();
            }
            if(event.type == sf::Event::KeyReleased) {
                switch (event.key.code) {
                case sf::Keyboard::Escape:
                    window.close();
                    break;
                case sf::Keyboard::Q:
                    window.close();
                    break;
                default:
                    break;
                }
            }
        }
    }

return 0;}