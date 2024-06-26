#ifndef MAZESOLVER_H
#define MAZESOLVER_H

#include "maze.h"

#include <exception>
#include <list>

class MazeSolver
{
      public:
        enum class Algorithm {
                BFS,
                DIJKSTRA,
                // BELLMANFORD,
                // ASTAR,
                // FLOYDWARSHALL,
                // JOHNSONS,
                // VITERBI,
        };

      private:
        void spBFS(const Maze& maze, std::list<unsigned int>& result);
        void spDijkstra(const Maze& maze, std::list<unsigned int>& result);

      public:
        MazeSolver(){};

        std::list<unsigned int> solve(const Maze& maze, Algorithm algorithm);
};

namespace MazeSolverException
{
	class NoSolutionFound : public std::exception
	{
		const char* what = "NoSolutionFound";
	};

} // namespace MazeSolverException

#endif // !MAZESOLVER_H
