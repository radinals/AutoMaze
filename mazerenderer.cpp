#include "mazerenderer.h"

#include "vector2d.h"

#include <QBrush>
#include <QPainter>
#include <QRect>

void
MazeRenderer::setVertexStatus(std::list<unsigned int> labels,
			      BitmapStatus status)
{
	for (unsigned int label : labels) {
		Vector2D coordinate;
		m_maze->findMatrixLabelCoordinate(label, coordinate);

		m_bitmap[coordinate.getY()][coordinate.getX()] = status;
	}
}

void
MazeRenderer::setVertexStatus(unsigned int label, BitmapStatus status)
{
	Vector2D coordinate;
	m_maze->findMatrixLabelCoordinate(label, coordinate);
	m_bitmap[coordinate.getY()][coordinate.getX()] = status;
}

void
MazeRenderer::generateBitmap()
{
	m_bitmap = std::vector(
	    m_maze->getMatrixSize(),
	    std::vector(m_maze->getMatrixSize(), BitmapStatus::BM_NORMAL));

	size_t y = 0;
	for (std::vector<unsigned int> line : m_maze->getMatrix()) {
		size_t x = 0;
		for (unsigned int vertex : line) {
			if (m_maze->isWall(vertex)) {
				m_bitmap[y][x] = BitmapStatus::BM_WALL;
			}
			x++;
		}
		y++;
	}
}

void
MazeRenderer::resetBitmap()
{
	m_bitmap = std::vector(
	    m_maze->getMatrixSize(),
	    std::vector(m_maze->getMatrixSize(), BitmapStatus::BM_NORMAL));
}

void
MazeRenderer::generateScene(QGraphicsScene*& scene)
{
	Vector2D placement;

	size_t rect_h = m_view->geometry().height() / m_maze->getMatrixSize();
	size_t rect_w = m_view->geometry().width() / m_maze->getMatrixSize();

	QPainter painter;
	QPen pen;

	QBrush normal(Qt::white, Qt::SolidPattern);
	QBrush wall(Qt::black, Qt::SolidPattern);
	QBrush path(Qt::blue, Qt::SolidPattern);
	QBrush source(Qt::green, Qt::SolidPattern);
	QBrush end(Qt::yellow, Qt::SolidPattern);

	for (std::vector<BitmapStatus> line : m_bitmap) {
		for (BitmapStatus cell : line) {
			placement = placement + Vector2D(rect_h, 0);

			switch (cell) {
			case BitmapStatus::BM_END:
				scene->addRect(placement.getX(),
					       placement.getY(), rect_w, rect_h,
					       pen, end);
				break;
			case BitmapStatus::BM_SOURCE:
				scene->addRect(placement.getX(),
					       placement.getY(), rect_w, rect_h,
					       pen, source);
				break;
			case BitmapStatus::BM_PATH:
				scene->addRect(placement.getX(),
					       placement.getY(), rect_w, rect_h,
					       pen, path);
				break;
			case BitmapStatus::BM_WALL:
				scene->addRect(placement.getX(),
					       placement.getY(), rect_w, rect_h,
					       pen, wall);
				break;
			default:
				scene->addRect(placement.getX(),
					       placement.getY(), rect_w, rect_h,
					       pen, normal);
				break;
			}
		}
		placement = placement + Vector2D(0, rect_w);
		placement.setX(0);
	}
}

void
MazeRenderer::update()
{
	generateScene(m_scene);
	m_view->setScene(m_scene);
}
