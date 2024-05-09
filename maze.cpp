#include "maze.h"

#include <cstddef>
#include <random>
#include <vector>

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

unsigned int
Maze::randomRange(unsigned int min, unsigned int max)
{
	std::random_device rd;  // obtain a random number from hardware
	std::mt19937 gen(rd()); // seed the generator
	std::uniform_int_distribution<unsigned int> distr(
	    min, max); // define the range
	return distr(gen);
}

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
