#ifndef MAZERENDERER_H
#define MAZERENDERER_H

#include "maze.h"

#include <QGraphicsScene>
#include <QGraphicsView>

class MazeRenderer
{
      public:
        enum BitmapStatus {
                BM_NORMAL,
                BM_SOURCE,
                BM_END,
                BM_WALL,
                BM_PATH,
        };

      private:
        QGraphicsView* m_view;
        Maze* m_maze;
        QGraphicsScene* m_scene;
        std::vector<std::vector<BitmapStatus>> m_bitmap;

	// create the scene
	void generateScene(QGraphicsScene*& scene);

	// generate the basic bitmap
	void generateBitmap();

      public:
        MazeRenderer(QGraphicsView*& view, Maze*& maze)
            : m_view(view), m_maze(maze)
        {
                m_scene = new QGraphicsScene;
                generateBitmap();
                update();
        };

        ~MazeRenderer() { delete m_scene; }

	// set multiple cell type
	void setVertexStatus(std::list<unsigned int> labels,
			     BitmapStatus status);

	// set a vertex cell type
	void setVertexStatus(unsigned int labels, BitmapStatus status);

	// reset the bitmap, all cell is set to normal.
	void resetBitmap();

	// load the scene
	void update();
};

#endif // MAZERENDERER_H
