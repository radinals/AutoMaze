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

      public:
        MainWindow(QWidget *parent = nullptr);
        ~MainWindow();

      private slots:
        void on_ResetBtn_clicked();

        void on_SetSourceBtn_clicked();

        void on_SetDestinationBtn_clicked();

        void on_ToggleWalBtn_clicked();

        void on_SolveBtn_clicked();

      private:
        Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
