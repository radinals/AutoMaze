#ifndef VECTOR2D_H
#define VECTOR2D_H

#include <cstdint>

class Vector2D
{
      private:
        long long int m_x = 0;
        long long int m_y = 0;

      public:
        Vector2D(){};
        Vector2D(long long int x, long long int y) : m_x(x), m_y(y){};
        Vector2D(const Vector2D& v) : m_x(v.getX()), m_y(v.getY()){};

	long long int getX() const { return m_x; };
	long long int getY() const { return m_y; };

	void setX(long long int x) { m_x = x; };
	void setY(long long int y) { m_y = y; };

	inline void operator=(const Vector2D& obj)
	{
		m_y = obj.getY();
		m_x = obj.getX();
	}

	inline Vector2D operator+(const Vector2D& obj)
	{
		return Vector2D(m_x + obj.getX(), m_y + obj.getY());
	}

	inline Vector2D operator-(const Vector2D& obj)
	{
		return Vector2D(m_x - obj.getX(), m_y - obj.getY());
	}

	inline bool operator<(const Vector2D& obj)
	{
		return ((m_x < obj.getX()) && (m_y < obj.getY()));
	}

	inline bool operator<=(const Vector2D& obj)
	{
		return ((m_x <= obj.getX()) && (m_y <= obj.getY()));
	}

	inline bool operator>(const Vector2D& obj)
	{
		return ((m_x > obj.getX()) && (m_y > obj.getY()));
	}

	inline bool operator>=(const Vector2D& obj)
	{
		return ((m_x >= obj.getX()) && (m_y >= obj.getY()));
	}
};

#endif // VECTOR2D_H
