#include "mainwindow.h"

#include "./ui_mainwindow.h"
#include "mazesolver.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	ui->mazeSizeIn->setText(
	    QString::fromStdString(std::to_string(m_def_maze_size)));

	m_maze = new Maze(m_def_maze_size);
	m_renderer = new MazeRenderer(m_maze);
	ui->render->addWidget(m_renderer);
}

MainWindow::~MainWindow()
{
	delete ui;
	delete m_maze;
	delete m_renderer;
}

void
MainWindow::on_ResetBtn_clicked()
{
	m_maze->clearWall();
	m_maze->setStartEndCoordinates({0, 0}, {0, 0});
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
	m_renderer->setVertexStatus(label, BitmapStatus::BM_SOURCE);

	m_maze->setStartEndCoordinates({x, y}, m_maze->getEndCoordinate());
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
	m_renderer->setVertexStatus(label, BitmapStatus::BM_END);

	m_maze->setStartEndCoordinates(m_maze->getStartCoordinate(), {x, y});
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
		m_renderer->setVertexStatus(label, BitmapStatus::BM_NORMAL);
		m_maze->unsetWall(label);
	} else {
		m_renderer->setVertexStatus(label, BitmapStatus::BM_WALL);
		m_maze->setWall(label);
	}

	m_renderer->update();
}

void
MainWindow::on_SolveBtn_clicked()
{
	MazeSolver solver;
	m_renderer->setVertexStatus(
	    solver.solve(*m_maze, MazeSolver::Algorithm::BFS),
	    BitmapStatus::BM_PATH);
	m_renderer->update();
}

void
MainWindow::on_mazeSizeIn_editingFinished()
{
	unsigned int size = 0;
	try {
		size = ui->mazeSizeIn->text().toUInt();
	} catch (...) {
		ui->mazeSizeIn->setText(
		    QString::fromStdString(std::to_string(m_def_maze_size)));
		return;
	}

	m_maze->generateMatrix(size);
	m_renderer->resetBitmap();
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
