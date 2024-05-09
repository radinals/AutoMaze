#ifndef MAZE_H
#define MAZE_H

#include "vector2d.h"

#include <algorithm>
#include <cstdlib>
#include <list>
#include <vector>

class Maze
{
	enum Direction {
		UP,
		DOWN,
		LEFT,
		RIGHT
	};

	// start end end of the maze
	Vector2D m_start;
	Vector2D m_end;

	// adjacency matrix of the graph
	std::vector<std::vector<bool>> m_adjacency_matrix;

	// literal graph matrix
	std::vector<std::vector<unsigned int>> m_matrix;

	// list of vertex set to be a wall
	std::vector<unsigned int> m_wall;

	// amount of vertex in the maze
	size_t m_vertex_amount = 0;

	// literal graph matrix size
	size_t m_matrix_size = 0;

	// check if a vertex has a neighbour
	bool hasAdjacentVertex(int collumn, int line, size_t limit,
			       Direction direction);

      public:
        Maze(size_t size) { generateMatrix(size); }

	// generate an empty square maze of (size x size)
	void generateMatrix(size_t size);

	// UNUSED
	static Vector2D getDistance(const Vector2D& source,
				    const Vector2D& destination)
	{
		return {(source.getX() > destination.getX())
			    ? source.getX() - destination.getX()
			    : destination.getX() - source.getX()

			    ,
			(source.getY() > destination.getY())
			    ? source.getY() - destination.getY()
			    : destination.getY() - source.getY()};
	}

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

	// set the start coordinates of the maze
	inline void setStartCoordinate(const Vector2D& coordinate)
	{
		m_start = coordinate;
	}

	// set the end coordinates of the maze
	inline void setEndCoordinate(const Vector2D& coordinate)
	{
		m_end = coordinate;
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

	inline size_t getVertexAmount() const { return m_vertex_amount; }
	inline size_t getMatrixSize() const { return m_matrix_size; }
};

#endif // !MAZE_H
