#include "Solver.h"

#include "Stack.hpp"
#include "Queue.hpp"

#include <iostream>
#include <iostream>
#include <array>

Solver* Solver::_pSolver = nullptr;
bool Solver::_instantiated = false;

Solver* Solver::makeSolver(Maze *pmaze, const bool DFS) {
    if (!_instantiated) {
        _instantiated = true;
        _pSolver = new Solver();
        //depending on the search type, use a stack or a queue.

        _pSolver->_pStor = (DFS) ? 
            static_cast<IContainer<std::array<int, 2>>*>(new Stack<std::array<int, 2>>) : 
            static_cast<IContainer<std::array<int, 2>>*>(new Queue<std::array<int, 2>>);

        _pSolver->_pNStor = (DFS) ? 
        static_cast<IContainer<Node*>*>(new Stack<Node*>) : 
        static_cast<IContainer<Node*>*>(new Queue<Node*>);

        _pSolver->_pMaze = pmaze;
        _pSolver->_pStor->push(pmaze->getMazeStart());
        _nodes.push_back(new Node(pmaze->getMazeStart()));
        _pSolver->_pNStor->push(_nodes.back());

        _pSolver->_visited.resize(pmaze->getYDim(), std::vector<bool>(pmaze->getXDim(), false));

    }
    return _pSolver;
}

bool Solver::solveMaze() {
    if (_pStor->size() > 0) {
        std::array<int, 2> currentLoc = _pStor->pop();
        Node* currentNode = _pNStor->pop();
        //check if current tile is the end
        if (_pMaze->getMazeChar(currentLoc) == 'E') {
            std::cout << "The maze has been solved!" << std::endl;
            Node* pParent = _nodes.back()->parent;
            while (pParent->parent != nullptr) {
                _pMaze->setMazeChar(pParent->Loc, 'y');
                pParent = pParent->parent;
            }
            return true;
        }

        if (_visited[currentLoc[0]][currentLoc[1]]) {
            return false;
        }

        _visited[currentLoc[0]][currentLoc[1]] = true;
        if (_pMaze->getMazeChar(currentLoc) == '.') {
            _pMaze->setMazeChar(currentLoc, '%');
        }

        std::array<std::array<int, 2>, 4> directions = {{
            {0, -1}, // west (3)
            {1, 0},   // south (2)
            {0, 1},   // east (1)
            {-1, 0}  // north (0

        }};

        for (int i = 0; i < 4; i++) {
            std::array<int, 2> dir = directions[i];
            std::array<int, 2> newLoc = {currentLoc[0] + dir[0], currentLoc[1] + dir[1]};

            if (newLoc[0] >= 0 && newLoc[0] < _pMaze->getYDim() && newLoc[1] >= 0 && newLoc[1] < _pMaze->getXDim()) {
                char nextChar = _pMaze->getMazeChar(newLoc);

                if ((nextChar == '.' || nextChar == 'E') && 
                    !_visited[newLoc[0]][newLoc[1]]) {
                    _pStor->push(newLoc);
                    _nodes.push_back(new Node(newLoc, *currentNode));
                    _pNStor->push(_nodes.back());
                }
            }
        }
    }
    return false;
}

void Solver::drawSolve(sf::RenderWindow &window) {
    for (int i = 0; i < _pStor->size(); i ++) {
        std::array<int, 2> tile = _pStor->at(i);
        sf::RectangleShape rect({15, 15});
        rect.setFillColor(sf::Color::Blue);
        rect.setPosition(tile[1] * 15.f, tile[0] * 15.f);
        window.draw(rect);
    }
}

Solver::Solver() {
    _pStor = nullptr;
    _pMaze = nullptr;
}