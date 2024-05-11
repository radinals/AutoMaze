#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "maze.h"
#include "mazerenderer.h"
#include "mazesolver.h"

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

	MazeSolver::Algorithm m_solver_algorithm = MazeSolver::Algorithm::BFS;
	Maze::WeightLevel m_draw_weight = Maze::WeightLevel::None;

	MazeRenderer *m_renderer;
	Maze *m_maze;

	const unsigned int m_def_maze_size = 10;

	QAction *e_useBFSAlgorithm;
	QAction *e_useDijkstraAlgorithm;

	QAction *e_useHighWeight;
	QAction *e_useMedWeight;
	QAction *e_useLowWeight;
	QAction *e_useNoWeight;

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

        void on_SetWeightRadio_clicked();

        void on_WeightSelMenu_triggered(QAction *arg1);

        void on_AlgorithmSelMenu_triggered(QAction *arg1);

      private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
