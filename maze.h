#ifndef MAZE_H
#define MAZE_H

#include "vector2d.h"

#include <algorithm>
#include <cstdlib>
#include <list>
#include <vector>

class Maze
{
      public:
        enum class WeightLevel {
                None,
                Low,
                Medium,
                High
        };

      private:
        enum Direction {
                UP,
                DOWN,
                LEFT,
                RIGHT
        };

	// start end end of the maze
	Vector2D m_start = {-1, -1};
	Vector2D m_end = {-1, -1};

	// adjacency matrix of the graph
	std::vector<std::vector<bool>> m_adjacency_matrix;

	// literal graph matrix
	std::vector<std::vector<unsigned int>> m_matrix;

	// list of vertex set to be a wall
	std::vector<unsigned int> m_wall;

	std::vector<unsigned int> m_weight_matrix;
	std::vector<std::vector<unsigned int>> m_distance_matrix;

	// amount of vertex in the maze
	size_t m_vertex_amount = 0;

	// literal graph matrix size
	size_t m_matrix_size = 0;

	// check if a vertex has a neighbour
	bool hasAdjacentVertex(int collumn, int line, size_t limit,
			       Direction direction);

	std::vector<std::vector<unsigned int>> generateWeight(
	    unsigned int start_vertex) const;

      public:
        Maze(size_t size)
        {
                generateMatrix(size);
                m_weight_matrix =
                    std::vector<unsigned int>(getVertexAmount(), 0);
        };

	// generate an empty square maze of (size x size)
	void generateMatrix(size_t size);

	unsigned int getWeight(unsigned int label) const
	{
		Vector2D coord;
		findMatrixLabelCoordinate(label, coord);
		return m_weight_matrix[label];
	}

	unsigned int calculateDistance(unsigned int source,
				       unsigned int destination) const
	{
		Vector2D dest_coord;
		Vector2D source_coord;

		findMatrixLabelCoordinate(source, source_coord);
		findMatrixLabelCoordinate(destination, dest_coord);

		unsigned int source_weight =
		    m_distance_matrix[source_coord.getY()][source_coord.getX()];
		unsigned int dest_weight =
		    m_distance_matrix[dest_coord.getY()][dest_coord.getX()];

		return (source_weight < dest_weight)
			   ? dest_weight - source_weight
			   : source_weight - dest_weight;
	}

	void setVertexWeight(unsigned int label, WeightLevel level);

	// add the label to the wall list
	inline void setWall(unsigned int label) { m_wall.push_back(label); }

	// remove the label from the wall list
	inline void unsetWall(unsigned int label)
	{
		m_wall.erase(std::remove(m_wall.begin(), m_wall.end(), label),
			     m_wall.end());
	}

	// remove all wall stored in the wall list
	inline void clearWall() { m_wall.clear(); }

	inline void setStartEndCoordinates(const Vector2D& start,
					   const Vector2D end)
	{
		m_start = start;
		m_end = end;
		if (m_start < Vector2D(0, 0))
			return;
		m_distance_matrix = generateWeight(getMatrixLabel(start));
	}

	// return the end coordinates of the maze
	inline Vector2D getEndCoordinate() const { return m_end; }

	// return the start coordinates of the maze
	inline Vector2D getStartCoordinate() const { return m_start; }

	// return the adjacency matrix
	inline std::vector<std::vector<bool>> getAdjacencyMatrix() const
	{
		return m_adjacency_matrix;
	}

	// look for a label in the literal matrix, if found return true.
	// the coordinate of the label is set to ret_coordinate
	bool findMatrixLabelCoordinate(unsigned int label,
				       Vector2D& ret_coordinate) const;

	// return a vertex's neighbours
	std::list<unsigned int> getMatrixNeighbours(unsigned int label) const;

	// get the label from the literal graph matrix
	inline unsigned int getMatrixLabel(const Vector2D& coordinate) const
	{
		return m_matrix[coordinate.getY()][coordinate.getX()];
	}

	// check if the label is in the wall vertex list
	inline bool isWall(unsigned int label) const
	{
		if (m_wall.empty())
			return false;
		return std::find(m_wall.begin(), m_wall.end(), label) !=
		       m_wall.end();
	}

	// return the literal graph matrix
	inline std::vector<std::vector<unsigned int>> getMatrix() const
	{
		return m_matrix;
	}

	inline void resetWeights()
	{
		m_weight_matrix =
		    std::vector<unsigned int>(getVertexAmount(), 0);
	}

	inline size_t getVertexAmount() const { return m_vertex_amount; }
	inline size_t getMatrixSize() const { return m_matrix_size; }
};

#endif // !MAZE_H
