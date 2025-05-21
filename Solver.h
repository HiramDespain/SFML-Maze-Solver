#ifndef SOLVER_H
#define SOLVER_H

#include "Maze.h"
#include "IContainer.hpp"

class Solver { //singlton;
public:
     /**
      * @brief singleton constuction wrapper, only allows a single instance of the maze Solver.
      * 
      * @param maze 
      */
    static Solver* makeSolver(Maze *pmaze, const bool DFS);

    /**
     * @brief Solves the maze and draws the solution to the window
     * @brief and as the assignment ask that the solving not be instantaneous, this is going to run a single time every loop
     * 
     * @return true 
     * @return false 
     */
    bool solveMaze();

    /**
     * @brief employed in solveMaze to animate the solution;
     *
     */
    void drawSolve(sf::RenderWindow &window);

private:

    //stored a pointer to the solver
    static Solver* _pSolver;

    //contains a 2d vector of bools to keep track of the visited locations
    std::vector<std::vector<bool>> _visited;

    //a pointer to the stack or queue

    //pointer to maze object
    Maze* _pMaze;

    //for singleton functionality
    static bool _instantiated; //is true if a Solver exists

    struct Node {
        Node() = delete;
        inline Node(std::array<int, 2> tLoc, Node &n) {
            this->Loc = tLoc;
            this->parent = &n;
        }

        inline Node(std::array<int, 2> tLoc) {
            this->Loc = tLoc;
            this->parent = nullptr;
        }

        std::array<int, 2> Loc;
        Node* parent;
    };

    static inline std::vector<Node*> _nodes = {};

    IContainer<std::array<int, 2>>* _pStor;
    IContainer<Node*>* _pNStor;

    Solver();
};

#endif