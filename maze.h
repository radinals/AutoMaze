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

	const unsigned int WEIGHT_WALL = 10;

	Vector2D m_start;
	Vector2D m_end;

	std::vector<std::vector<bool>> m_adjacency_matrix;
	std::vector<std::vector<unsigned int>> m_matrix;

	std::vector<unsigned int> m_wall;

	size_t m_vertex_amount = 0;
	size_t m_matrix_size = 0;

	bool hasAdjacentVertex(int collumn, int line, size_t limit,
			       Direction direction);

	unsigned int randomRange(unsigned int min, unsigned int max);

      public:
        Maze(size_t size) { generateMatrix(size); }

        void generateMatrix(size_t size);

        void setWall(unsigned int label) { m_wall.push_back(label); }

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

	inline void unsetWall(unsigned int label)
	{
		m_wall.erase(std::remove(m_wall.begin(), m_wall.end(), label),
			     m_wall.end());
	}

	inline void clearWall() { m_wall.clear(); }

	inline void setStartCoordinate(const Vector2D& coordinate)
	{
		m_start = coordinate;
	}

	inline void setEndCoordinate(const Vector2D& coordinate)
	{
		m_end = coordinate;
	}

	inline Vector2D getEndCoordinate() const { return m_end; }

	inline Vector2D getStartCoordinate() const { return m_start; }

	inline std::vector<std::vector<bool>> getAdjacencyMatrix() const
	{
		return m_adjacency_matrix;
	}

	bool findMatrixLabelCoordinate(unsigned int label,
				       Vector2D& ret_coordinate) const;

	std::list<unsigned int> getMatrixNeighbours(unsigned int label) const;

	inline unsigned int getMatrixLabel(const Vector2D& coordinate) const
	{
		return m_matrix[coordinate.getY()][coordinate.getX()];
	}

	inline bool isWall(unsigned int label) const
	{
		if (m_wall.empty())
			return false;
		return std::find(m_wall.begin(), m_wall.end(), label) !=
		       m_wall.end();
	}

	inline std::vector<std::vector<unsigned int>> getMatrix() const
	{
		return m_matrix;
	}

	inline size_t getVertexAmount() const { return m_vertex_amount; }
	inline size_t getMatrixSize() const { return m_matrix_size; }
};

#endif // !MAZE_H
