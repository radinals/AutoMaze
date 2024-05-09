#include "mazesolver.h"

#include "maze.h"

#include <climits>
#include <list>
#include <map>
#include <queue>

void
MazeSolver::dijkstra(const Maze& maze, std::list<unsigned int>& result)
{
	const unsigned int source =
	    maze.getMatrixLabel(maze.getStartCoordinate());
	const unsigned int destination =
	    maze.getMatrixLabel(maze.getEndCoordinate());

	const unsigned int INF = UINT_MAX;

	std::vector<unsigned int> distance(maze.getVertexAmount(), INF);
	std::map<unsigned int, unsigned int> predecessor;
	for (unsigned int label = 0; label < maze.getVertexAmount(); label++) {
		predecessor[label] = 0;
	}
	distance[source] = 0;

	std::queue<unsigned int> vertex_queue;
	vertex_queue.push(source);

	while (!vertex_queue.empty()) {

		unsigned int current_vertex = vertex_queue.front();
		vertex_queue.pop();

		if (current_vertex == destination) {
			break;
		}

		for (unsigned int neighbour :
		     maze.getMatrixNeighbours(current_vertex)) {
			if (maze.isWall(neighbour)) {
				continue;
			}

			if (distance[neighbour] == INF) {
				distance[neighbour] =
				    distance[current_vertex] + 1;
				predecessor[neighbour] = current_vertex;
				vertex_queue.push(neighbour);
			}
		}
	}

	unsigned int current = destination;

	while (current != 0) {
		result.push_back(current);
		current = predecessor[current];
	}
	result.push_back(source);
}

std::list<unsigned int>
MazeSolver::solve(const Maze& maze, Algorithm algorithm)
{
	std::list<unsigned int> solution;
	switch (algorithm) {
	case Algorithm::DIJKSTRA:
		dijkstra(maze, solution);
	}
	return solution;
}
