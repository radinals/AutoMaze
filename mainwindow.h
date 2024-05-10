#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "maze.h"
#include "mazerenderer.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui
{
	class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
	Q_OBJECT

	MazeRenderer *m_renderer;
	Maze *m_maze;
	const unsigned int m_def_maze_size = 10;

      public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

      private slots:
        void on_ResetBtn_clicked();

        void on_SolveBtn_clicked();

        void on_SetSourceRadio_clicked();

        void on_SetDestRadio_clicked();

        void on_SetWallRadio_clicked();

        void on_ExitBtn_clicked();

      private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
