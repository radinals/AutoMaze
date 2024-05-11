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

	e_useBFSAlgorithm = new QAction("Use BFS", this);
	e_useDijkstraAlgorithm = new QAction("Use Dijkstra", this);

	e_useHighWeight = new QAction("High: 50", this);
	e_useMedWeight = new QAction("Medium: 20", this);
	e_useLowWeight = new QAction("Low: 10", this);
	e_useNoWeight = new QAction("None: 0");

	ui->WeightSelMenu->addAction(e_useHighWeight);
	ui->WeightSelMenu->addAction(e_useMedWeight);
	ui->WeightSelMenu->addAction(e_useLowWeight);
	ui->WeightSelMenu->addAction(e_useNoWeight);
	ui->WeightSelMenu->setText("Select Weight");

	ui->AlgorithmSelMenu->addAction(e_useBFSAlgorithm);
	ui->AlgorithmSelMenu->addAction(e_useDijkstraAlgorithm);
	ui->AlgorithmSelMenu->setText("BFS");

	ui->WeightSelMenu->hide();
	ui->SetWeightRadio->hide();
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
	    m_maze->getEndCoordinate() < Vector2D(0, 0)) {
		return;
	}

	m_renderer->setVertexStatus(solver.solve(*m_maze, m_solver_algorithm),
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

void
MainWindow::on_SetWeightRadio_clicked()
{
	m_renderer->setUiMode(MazeUiMode::UM_DrawWeight);
}

void
MainWindow::on_WeightSelMenu_triggered(QAction *arg1)
{
	if (arg1 == e_useHighWeight) {
		m_draw_weight = Maze::WeightLevel::High;
		ui->WeightSelMenu->setText("HIGH");
	} else if (arg1 == e_useMedWeight) {
		m_draw_weight = Maze::WeightLevel::Medium;
		ui->WeightSelMenu->setText("MEDIUM");
	} else if (arg1 == e_useLowWeight) {
		m_draw_weight = Maze::WeightLevel::Low;
		ui->WeightSelMenu->setText("LOW");
	} else {
		m_draw_weight = Maze::WeightLevel::None;
		ui->WeightSelMenu->setText("NONE");
	}
	m_renderer->setWeightDrawLevel(m_draw_weight);
}

void
MainWindow::on_AlgorithmSelMenu_triggered(QAction *arg1)
{
	if (arg1 == e_useBFSAlgorithm) {
		m_solver_algorithm = MazeSolver::Algorithm::BFS;
		ui->AlgorithmSelMenu->setText("BFS");

		ui->WeightSelMenu->hide();
		ui->SetWeightRadio->hide();
	} else {
		m_solver_algorithm = MazeSolver::Algorithm::DIJKSTRA;
		ui->AlgorithmSelMenu->setText("DIJKSTRA");

		ui->WeightSelMenu->show();
		ui->SetWeightRadio->show();
	}
}
