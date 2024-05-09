#include "mazesolver.h"

#include "maze.h"

#include <climits>
#include <list>
#include <map>
#include <queue>

void
MazeSolver::dijkstra(const Maze& maze, std::list<unsigned int>& result)
{
	// destination and source
	const unsigned int source =
	    maze.getMatrixLabel(maze.getStartCoordinate());
	const unsigned int destination =
	    maze.getMatrixLabel(maze.getEndCoordinate());

	const unsigned int INF = UINT_MAX;

	// all distance is set to infinite
	std::vector<unsigned int> distance(maze.getVertexAmount(), INF);

	// map of a labels predecessor
	std::map<unsigned int, unsigned int> predecessor;

	// set all label predecessor to 0
	for (unsigned int label = 0; label < maze.getVertexAmount(); label++) {
		predecessor[label] = 0;
	}

	// set distance of the source (start) to 0
	distance[source] = 0;

	// queue of vertexis that's being processed
	std::queue<unsigned int> vertex_queue;

	// push the source vertex to the queue
	vertex_queue.push(source);

	while (!vertex_queue.empty()) {

		// get the vertex in the front
		unsigned int current_vertex = vertex_queue.front();
		vertex_queue.pop();

		// if current vertex is the destination, exit the loop
		if (current_vertex == destination) {
			break;
		}

		// for every neighbour of the current vertex
		for (unsigned int neighbour :
		     maze.getMatrixNeighbours(current_vertex)) {

			// if the current neigbour is a wall, skip it
			if (maze.isWall(neighbour)) {
				continue;
			}

			// if distance of the neighbour is infinite
			if (distance[neighbour] == INF) {
				// set the neighbour distance from the start to
				// be the current vertex + 1 (the graph is
				// unweighted)
				distance[neighbour] =
				    distance[current_vertex] + 1;

				// set the predecessor of the neigbour to be
				// the current vertex
				predecessor[neighbour] = current_vertex;

				// push the neighbour to the queue
				vertex_queue.push(neighbour);
			}
		}
	}

	unsigned int current = destination;

	// backtrack from the end (destination)
	while (current != 0) {
		// idk.. this somehow gives back the shortest path?
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
