#include "maze.h"

#include <climits>
#include <cstddef>
#include <queue>
#include <vector>

// look in a set direction in the literal graph matrix.
// if the resulting index is invalid, there is no adjacent vertex
bool
Maze::hasAdjacentVertex(int collumn, int line, size_t limit,
			Direction direction)
{
	switch (direction) {
	case Direction::UP:
		return (line - 1) >= 0;
	case Direction::DOWN:
		return (line + 1) < limit;
	case Direction::LEFT:
		return (collumn - 1) >= 0;
	case Direction::RIGHT:
		return (collumn + 1) < limit;
	default:
		return false;
	}
}

// return the x and y coordinates of a vertex in the literal
// graph matrix.
bool
Maze::findMatrixLabelCoordinate(unsigned int label,
				Vector2D& ret_coordinate) const
{
	for (size_t i = 0; i < m_matrix.size(); i++) {
		for (size_t j = 0; j < m_matrix.at(i).size(); j++) {
			if (m_matrix[i][j] == label) {
				ret_coordinate = Vector2D(j, i);
				return true;
			}
		}
	}
	return false;
}

// search in the vertex's adjacency matrix, look for
// the vertex neighbour based of the 1's in the vertex line.
std::list<unsigned int>
Maze::getMatrixNeighbours(unsigned int label) const
{
	size_t i = 0;
	std::list<unsigned int> neighbours;
	for (bool v : m_adjacency_matrix[label]) {
		if (v) {
			neighbours.push_back(i);
		}
		i++;
	}
	return neighbours;
};

std::vector<std::vector<unsigned int>>
Maze::generateWeight(unsigned int start_vertex) const
{
	std::vector<std::vector<unsigned int>> weight_matrix = std::vector(
	    m_matrix_size, std::vector<unsigned int>(m_matrix_size));

	std::vector<bool> visited(m_vertex_amount, false);

	unsigned int INF = UINT_MAX;

	std::queue<unsigned int> vertex_queue;
	std::vector<unsigned int> distance(m_vertex_amount, INF);

	distance[start_vertex] = 0;
	vertex_queue.push(start_vertex);

	while (!vertex_queue.empty()) {
		unsigned int current_vertex = vertex_queue.front();
		vertex_queue.pop();

		for (unsigned int neighbour :
		     getMatrixNeighbours(current_vertex)) {

			if (isWall(neighbour)) {
				continue;
			}

			if (distance[neighbour] == INF) {
				distance[neighbour] =
				    distance[current_vertex] + 1;
				vertex_queue.push(neighbour);
			}
		}
	}

	for (size_t y = 0; y < m_matrix_size; y++) {
		for (size_t x = 0; x < m_matrix_size; x++) {
			weight_matrix[y][x] = distance[m_matrix[y][x]];
		}
	}

	return weight_matrix;
}

// generate the the literal grid of the graph matrix
// and also create the adjacency matrix of that graph
void
Maze::generateMatrix(size_t size)
{
	m_matrix_size = size;
	m_vertex_amount = size * size;

	m_matrix = std::vector(size, std::vector<unsigned int>(size));

	m_adjacency_matrix =
	    std::vector(m_vertex_amount, std::vector<bool>(m_vertex_amount));

	unsigned int label = 0;
	for (size_t line = 0; line < size; line++) {
		for (size_t collumn = 0; collumn < size; collumn++) {
			m_matrix[line][collumn] = label++;
		}
	}

	for (int line = 0; line < size; line++) {
		for (int collumn = 0; collumn < size; collumn++) {

			unsigned int vertex_label = m_matrix[line][collumn];

			if (hasAdjacentVertex(collumn, line, size,
					      Direction::UP)) {
				unsigned int adj_up =
				    m_matrix[line - 1][collumn];
				m_adjacency_matrix[vertex_label][adj_up] = true;
			}

			if (hasAdjacentVertex(collumn, line, size,
					      Direction::DOWN)) {
				unsigned int adj_down =
				    m_matrix[line + 1][collumn];
				m_adjacency_matrix[vertex_label][adj_down] =
				    true;
			}

			if (hasAdjacentVertex(collumn, line, size,
					      Direction::LEFT)) {
				unsigned int adj_left =
				    m_matrix[line][collumn - 1];
				m_adjacency_matrix[vertex_label][adj_left] =
				    true;
			}

			if (hasAdjacentVertex(collumn, line, size,
					      Direction::RIGHT)) {
				unsigned int adj_right =
				    m_matrix[line][collumn + 1];
				m_adjacency_matrix[vertex_label][adj_right] =
				    true;
			}
		}
	}
}

void
Maze::setVertexWeight(unsigned int label, WeightLevel level)
{
	Vector2D coord;
	findMatrixLabelCoordinate(label, coord);

	unsigned int weight = 0;

	switch (level) {
	case WeightLevel::High:
		weight = 50;
		break;
	case WeightLevel::Medium:
		weight = 20;
		break;
	case WeightLevel::Low:
		weight = 10;
		break;
	default:
		weight = 1;
		break;
	}

	m_weight_matrix[coord.getY()][coord.getX()] = weight;
}
