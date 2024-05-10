#include "mazerenderer.h"

#include "vector2d.h"

#include <QBrush>
#include <QPainter>
#include <QRect>
#include <cmath>

// set vertex's cell status in the bitmap
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

// set mmultple vertex's cell status in the bitmap
void
MazeRenderer::setVertexStatus(unsigned int label, BitmapStatus status)
{
	Vector2D coordinate;
	m_maze->findMatrixLabelCoordinate(label, coordinate);
	m_bitmap[coordinate.getY()][coordinate.getX()] = status;
}

// generate the basic bitmap, only containing the empy cell and
// the walls if one exists
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

unsigned int
MazeRenderer::calcVertexMouseClick(float x, float y)
{
	Vector2D clicked_cell((unsigned int)std::floor(x / m_cell_width),
			      (unsigned int)std::floor(y / m_cell_height));

	return m_maze->getMatrixLabel(clicked_cell);
}

void
MazeRenderer::mousePressEvent(QMouseEvent* event)
{
	if (m_ui_mode == MazeUiMode::UM_None)
		return;

	QPointF position;
	switch (event->button()) {
	case Qt::LeftButton:
		position = mapToScene(event->pos());
		if (position.x() * position.y() >
			((m_cell_height * m_cell_width) *
			 m_maze->getVertexAmount()) ||
		    position.x() < 0 || position.x() < 0)
			return;
		break;
	default:
		return;
	}

	unsigned int clicked_vertex =
	    calcVertexMouseClick(position.x(), position.y());

	switch (m_ui_mode) {
	case MazeUiMode::UM_DrawWall: {

		if (m_maze->getStartCoordinate() >= Vector2D(0, 0) &&
		    m_maze->getMatrixLabel(m_maze->getStartCoordinate()) ==
			clicked_vertex) {
			return;
		}
		if (m_maze->getEndCoordinate() >= Vector2D(0, 0) &&
		    m_maze->getMatrixLabel(m_maze->getEndCoordinate()) ==
			clicked_vertex) {
			return;
		}
		if (m_maze->isWall(clicked_vertex)) {
			setVertexStatus(clicked_vertex,
					BitmapStatus::BM_NORMAL);
			m_maze->unsetWall(clicked_vertex);
		} else {
			setVertexStatus(clicked_vertex, BitmapStatus::BM_WALL);
			m_maze->setWall(clicked_vertex);
		}
	} break;
	case MazeUiMode::UM_DrawSource: {

		unsigned int old_start_vertex;
		if (m_maze->getStartCoordinate() >= Vector2D(0, 0)) {
			old_start_vertex = m_maze->getMatrixLabel(
			    m_maze->getStartCoordinate());
			setVertexStatus(old_start_vertex,
					BitmapStatus::BM_NORMAL);
		}

		unsigned int end_vertex;
		if (m_maze->getEndCoordinate() >= Vector2D(0, 0)) {
			end_vertex =
			    m_maze->getMatrixLabel(m_maze->getEndCoordinate());
		}

		if (m_maze->getStartCoordinate() >= Vector2D(0, 0) &&
		    m_maze->getEndCoordinate() >= Vector2D(0, 0)) {

			if (end_vertex == clicked_vertex ||
			    clicked_vertex == old_start_vertex)
				return;
		}

		Vector2D tmp;
		m_maze->findMatrixLabelCoordinate(clicked_vertex, tmp);

		setVertexStatus(clicked_vertex, BitmapStatus::BM_SOURCE);

		m_maze->setStartEndCoordinates(tmp, m_maze->getEndCoordinate());

		if (m_maze->isWall(clicked_vertex)) {
			m_maze->unsetWall(clicked_vertex);
		}

	} break;
	case MazeUiMode::UM_DrawEnd: {

		unsigned int start_vertex;
		if (m_maze->getStartCoordinate() >= Vector2D(0, 0)) {
			start_vertex = m_maze->getMatrixLabel(
			    m_maze->getStartCoordinate());
		}

		unsigned int old_end_vertex;
		if (m_maze->getEndCoordinate() >= Vector2D(0, 0)) {
			old_end_vertex =
			    m_maze->getMatrixLabel(m_maze->getEndCoordinate());
			setVertexStatus(old_end_vertex,
					BitmapStatus::BM_NORMAL);
		}

		if (m_maze->getStartCoordinate() >= Vector2D(0, 0) &&
		    m_maze->getEndCoordinate() >= Vector2D(0, 0)) {

			if (old_end_vertex == clicked_vertex ||
			    clicked_vertex == start_vertex)
				return;
		}

		Vector2D tmp;
		m_maze->findMatrixLabelCoordinate(clicked_vertex, tmp);

		setVertexStatus(clicked_vertex, BitmapStatus::BM_END);

		m_maze->setStartEndCoordinates(m_maze->getStartCoordinate(),
					       tmp);
		if (m_maze->isWall(clicked_vertex)) {
			m_maze->unsetWall(clicked_vertex);
		}
	} break;
	default:
		return;
	}

	update();
}

// reset the bitmap, all cell set to normal
void
MazeRenderer::resetBitmap()
{
	m_bitmap = std::vector(
	    m_maze->getMatrixSize(),
	    std::vector(m_maze->getMatrixSize(), BitmapStatus::BM_NORMAL));
}

// generate the scene based of the bitmap
void
MazeRenderer::generateScene()
{

	Vector2D placement;

	size_t x = 0, y = 0;
	for (std::vector<BitmapStatus> line : m_bitmap) {
		for (BitmapStatus cell : line) {

			QPen pen;
			QBrush color;

			switch (cell) {
			case BitmapStatus::BM_END:
				color = QBrush(Qt::yellow, Qt::SolidPattern);
				break;
			case BitmapStatus::BM_SOURCE:
				color = QBrush(Qt::green, Qt::SolidPattern);
				break;
			case BitmapStatus::BM_PATH:
				color = QBrush(Qt::blue, Qt::SolidPattern);
				break;
			case BitmapStatus::BM_WALL:
				color = QBrush(Qt::black, Qt::SolidPattern);
				break;
			default:
				color = QBrush(Qt::white, Qt::SolidPattern);
				break;
			}

			scene()->addRect(m_cell_width * x, m_cell_width * y,
					 m_cell_width, m_cell_height, pen,
					 color);
			x++;
		}
		y++;
		x = 0;
	}
}

// generate and load the scene
void
MazeRenderer::update()
{
	scene()->clear();
	generateScene();
	resetTransform();
	viewport()->update();
}
