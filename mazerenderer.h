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

	void generateScene(QGraphicsScene*& scene);
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

	void setVertexStatus(std::list<unsigned int> labels,
			     BitmapStatus status);
	void setVertexStatus(unsigned int labels, BitmapStatus status);
	void resetBitmap();

	void update();
};

#endif // MAZERENDERER_H
