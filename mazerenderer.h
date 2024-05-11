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
	BM_WeightHigh,
	BM_WeightMedium,
	BM_WeightLow,
	BM_WeightNone,
};

enum class MazeUiMode {
	UM_None,
	UM_DrawWall,
	UM_DrawSource,
	UM_DrawEnd,
	UM_DrawWeight,
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

        Maze::WeightLevel m_weight_level = Maze::WeightLevel::None;

	// create the scene
	void generateScene();

	// generate the basic bitmap
	void generateBitmap();

	unsigned int calcVertexMouseClick(float x, float y);
	BitmapStatus vertexBitmapStatus(unsigned int label);

      protected:
        void mousePressEvent(QMouseEvent* event) override;

      public:
        MazeRenderer(Maze*& maze, QWidget* parent = nullptr);

	// set multiple cell type
	void setVertexStatus(std::list<unsigned int> labels,
			     BitmapStatus status);

	void setUiMode(MazeUiMode mode) { m_ui_mode = mode; };
	void setWeightDrawLevel(Maze::WeightLevel level)
	{
		m_weight_level = level;
	};

	// set a vertex cell type
	void setVertexStatus(unsigned int labels, BitmapStatus status);

	// reset the bitmap, all cell is set to normal.
	void resetBitmap();

	// load the scene
	void update();
};

#endif // MAZERENDERER_H
