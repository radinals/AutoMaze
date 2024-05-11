#ifndef MAZERENDERER_H
#define MAZERENDERER_H

#include "maze.h"

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMouseEvent>

enum class BitmapStatus {
	BM_NORMAL,
	BM_SOURCE,
	BM_END,
	BM_WALL,
	BM_PATH,
};

enum class MazeUiMode {
	UM_None,
	UM_DrawWall,
	UM_DrawSource,
	UM_DrawEnd,
};

class MazeRenderer : public QGraphicsView
{
      private:
        Maze* m_maze;
        QGraphicsScene* m_scene;
        std::vector<std::vector<BitmapStatus>> m_bitmap;
        MazeUiMode m_ui_mode = MazeUiMode::UM_None;
        size_t m_cell_width = 0;
        size_t m_cell_height = 0;

	// create the scene
	void generateScene();

	// generate the basic bitmap
	void generateBitmap();

	unsigned int calcVertexMouseClick(float x, float y);

      protected:
        void mousePressEvent(QMouseEvent* event) override;

      public:
	MazeRenderer(Maze*& maze, QWidget* parent = nullptr);

	// set multiple cell type
	void setVertexStatus(std::list<unsigned int> labels,
			     BitmapStatus status);

	void setUiMode(MazeUiMode mode) { m_ui_mode = mode; };

	// set a vertex cell type
	void setVertexStatus(unsigned int labels, BitmapStatus status);

	// reset the bitmap, all cell is set to normal.
	void resetBitmap();

	// load the scene
	void update();
};

#endif // MAZERENDERER_H
