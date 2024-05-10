#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "mazesolver.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	m_maze = new Maze(m_def_maze_size);
	m_renderer = new MazeRenderer(m_maze, this);
	ui->render->addWidget(m_renderer);
}

MainWindow::~MainWindow()
{
	delete ui;
	delete m_maze;
}

void
MainWindow::on_ResetBtn_clicked()
{
	m_maze->clearWall();
	m_maze->setStartEndCoordinates({-1, -1}, {-1, -1});
	m_renderer->resetBitmap();
	m_renderer->update();
}

void
MainWindow::on_SolveBtn_clicked()
{
	MazeSolver solver;

	if (m_maze->getEndCoordinate() == m_maze->getStartCoordinate() ||
	    m_maze->getStartCoordinate() < Vector2D(0, 0) ||
	    m_maze->getEndCoordinate() < Vector2D(0, 0))
		return;

	m_renderer->setVertexStatus(
	    solver.solve(*m_maze, MazeSolver::Algorithm::BFS),
	    BitmapStatus::BM_PATH);
	m_renderer->update();
}

void
MainWindow::on_SetSourceRadio_clicked()
{
	m_renderer->setUiMode(MazeUiMode::UM_DrawSource);
}

void
MainWindow::on_SetDestRadio_clicked()
{

	m_renderer->setUiMode(MazeUiMode::UM_DrawEnd);
}

void
MainWindow::on_SetWallRadio_clicked()
{
	m_renderer->setUiMode(MazeUiMode::UM_DrawWall);
}

void
MainWindow::on_ExitBtn_clicked()
{
	exit(0);
}
