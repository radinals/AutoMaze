#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "mazesolver.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
        ui->setupUi(this);

	m_maze = new Maze(10);
	m_renderer = new MazeRenderer(ui->RenderView, m_maze);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void
MainWindow::on_ResetBtn_clicked()
{
	m_maze->clearWall();
	m_maze->setEndCoordinate({0, 0});
	m_maze->setStartCoordinate({0, 0});
	m_renderer->resetBitmap();
	m_renderer->update();
}

void
MainWindow::on_SetSourceBtn_clicked()
{
	if (ui->SourceInX->text().isEmpty() || ui->SourceInY->text().isEmpty())
		return;

	long long int x, y;

	try {
		x = ui->SourceInX->text().toLongLong();
	} catch (...) {
		ui->SourceInX->clear();
		return;
	}

	try {
		y = ui->SourceInY->text().toLongLong();
	} catch (...) {
		ui->SourceInY->clear();
		return;
	}

	unsigned int label = m_maze->getMatrixLabel({x, y});
	m_renderer->setVertexStatus(label, m_renderer->BM_SOURCE);

	m_maze->setStartCoordinate({x, y});
	m_renderer->update();
}

void
MainWindow::on_SetDestinationBtn_clicked()
{
	if (ui->DestinationInX->text().isEmpty() ||
	    ui->DestinationInY->text().isEmpty())
		return;

	long long int x, y;

	try {
		x = ui->DestinationInX->text().toLongLong();
	} catch (...) {
		ui->DestinationInX->clear();
		return;
	}

	try {
		y = ui->DestinationInY->text().toLongLong();
	} catch (...) {
		ui->DestinationInY->clear();
		return;
	}

	unsigned int label = m_maze->getMatrixLabel({x, y});
	m_renderer->setVertexStatus(label, m_renderer->BM_END);

	m_maze->setEndCoordinate({x, y});
	m_renderer->update();
}

void
MainWindow::on_ToggleWalBtn_clicked()
{
	if (ui->ToggleWallInX->text().isEmpty() ||
	    ui->ToggleWallInY->text().isEmpty())
		return;

	long long int x, y;

	try {
		x = ui->ToggleWallInX->text().toLongLong();
	} catch (...) {
		ui->ToggleWallInX->clear();
		return;
	}

	try {
		y = ui->ToggleWallInY->text().toLongLong();
	} catch (...) {
		ui->ToggleWallInY->clear();
		return;
	}

	unsigned int label = m_maze->getMatrixLabel({x, y});

	if (m_maze->isWall(label)) {
		m_renderer->setVertexStatus(label, m_renderer->BM_NORMAL);
		m_maze->unsetWall(label);
	} else {
		m_renderer->setVertexStatus(label, m_renderer->BM_WALL);
		m_maze->setWall(label);
	}

	m_renderer->update();
}

void
MainWindow::on_SolveBtn_clicked()
{
	MazeSolver solver;
	m_renderer->setVertexStatus(
	    solver.solve(*m_maze, MazeSolver::Algorithm::DIJKSTRA),
	    MazeRenderer::BM_PATH);
	m_renderer->update();
}
