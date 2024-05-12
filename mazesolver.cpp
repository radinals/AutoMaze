#include "mazesolver.h"

#include "maze.h"

#include <climits>
#include <list>
#include <map>
#include <queue>

void
MazeSolver::spBFS(const Maze& maze, std::list<unsigned int>& result)
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

	bool reached_destination = false;

	while (!vertex_queue.empty()) {

		// get the vertex in the front
		unsigned int current_vertex = vertex_queue.front();
		vertex_queue.pop();

		// if current vertex is the destination, exit the loop
		if (current_vertex == destination) {
			reached_destination = true;
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

	if (reached_destination) {
		unsigned int current = destination;

		// backtrack from the end (destination)
		while (current != source) {
			// idk.. this somehow gives back the shortest path?
			result.push_back(current);
			current = predecessor[current];
		}

		result.push_back(source);

	} else {
		throw MazeSolverException::NoSolutionFound();
	}
}

void
MazeSolver::spDijkstra(const Maze& maze, std::list<unsigned int>& result)
{
	const unsigned int source =
	    maze.getMatrixLabel(maze.getStartCoordinate());
	const unsigned int destination =
	    maze.getMatrixLabel(maze.getEndCoordinate());

	const unsigned int INF = UINT_MAX;

	std::vector<unsigned int> distance(maze.getVertexAmount(), INF);
	std::vector<bool> visited(maze.getVertexAmount(), false);

	std::map<unsigned int, unsigned int> predecessor;
	for (unsigned int label = 0; label < maze.getVertexAmount(); label++) {
		predecessor[label] = 0;
	}

	using pii = std::pair<unsigned int, unsigned int>;
	std::priority_queue<pii, std::vector<pii>, std::greater<pii>>
	    vertex_queue;

	distance[source] = 0;
	vertex_queue.push(std::make_pair(distance[source], source));

	bool reached_destination = false;

	while (!vertex_queue.empty()) {

		// get the vertex in the front
		unsigned int current_vertex = vertex_queue.top().second;
		vertex_queue.pop();

		if (current_vertex == destination) {
			reached_destination = true;
			break;
		}

		if (visited[current_vertex]) {
			continue;
		} else {
			visited[current_vertex] = true;
		}

		for (unsigned int neighbour :
		     maze.getMatrixNeighbours(current_vertex)) {
			unsigned int weight =
			    maze.getWeight(neighbour) +
			    maze.calculateDistance(current_vertex, neighbour);

			if (maze.isWall(neighbour)) {
				continue;
			}

			if (!visited[neighbour] &&
			    distance[current_vertex] + weight <
				distance[neighbour]) {
				distance[neighbour] =
				    distance[current_vertex] + weight;
				predecessor[neighbour] = current_vertex;
				vertex_queue.push(std::make_pair(
				    distance[neighbour], neighbour));
			}
		}
	}

	if (reached_destination) {
		unsigned int current = destination;

		// backtrack from the end (destination)
		while (current != source) {
			// idk.. this somehow gives back the shortest path?
			result.push_back(current);
			current = predecessor[current];
		}

		result.push_back(source);
	} else {
		throw MazeSolverException::NoSolutionFound();
	}
}

std::list<unsigned int>
MazeSolver::solve(const Maze& maze, Algorithm algorithm)
{
	std::list<unsigned int> solution;
	switch (algorithm) {
	case Algorithm::BFS:
		spBFS(maze, solution);
		break;
	case Algorithm::DIJKSTRA:
		spDijkstra(maze, solution);
		break;
	}
	return solution;
}
