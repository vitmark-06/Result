#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setWindowTitle("Adventure game");
    setGeometry(300, 200, 1000, 600);

    QPixmap backgroundImage(":/images/background.png");
    backgroundImage = backgroundImage.scaled(1920, 1080, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Window, backgroundImage);
    this->setPalette(palette);


    mainMenu = new MainMenuWidget(this);
    setCentralWidget(mainMenu);
    connect(mainMenu, &MainMenuWidget::startNewGame, this, &MainWindow::startNewGame);
}

MainWindow::~MainWindow() {}

void MainWindow::drawPath(QGraphicsScene *scene, const std::vector<std::vector<int>> &path) {
    QPixmap roadTile(":/images/road_tile.png");
    QPixmap startTile(":/images/start_tile.png");
    QPixmap finishTile(":/images/finish_tile.png");
    QPixmap trapTile(":/images/trap_tile.png");
    QPixmap boostTile(":/images/boost_tile.png");
    QPixmap extraTurnTile(":/images/extra_turn_tile.png");

    roadTile = roadTile.scaled(TILE_SIZE, TILE_SIZE);
    startTile = startTile.scaled(TILE_SIZE, TILE_SIZE);
    finishTile = finishTile.scaled(TILE_SIZE, TILE_SIZE);
    trapTile = trapTile.scaled(TILE_SIZE, TILE_SIZE);
    boostTile = boostTile.scaled(TILE_SIZE, TILE_SIZE);
    extraTurnTile = extraTurnTile.scaled(TILE_SIZE, TILE_SIZE);

    int tileNumber = 0;

    for (int row = 0; row < path.size(); ++row)
    {
        for (int col = 0; col < path[row].size(); ++col)
        {
            QGraphicsPixmapItem *item = nullptr;
            if (path[row][col] == 2)
            {
                item = scene->addPixmap(startTile);
            }
            else if (path[row][col] == 3)
            {
                item = scene->addPixmap(finishTile);
            }
            else if (path[row][col] >= 4 && path[row][col] <= 6)
            {
                if (path[row][col] == 4)
                    item = scene->addPixmap(trapTile);
                else if (path[row][col] == 5)
                    item = scene->addPixmap(boostTile);
                else if (path[row][col] == 6)
                    item = scene->addPixmap(extraTurnTile);
            }
            else if (path[row][col] != 0)
            {
                item = scene->addPixmap(roadTile);
            }

            if (item)
            {
                item->setPos(col * TILE_SIZE, row * TILE_SIZE);
            }
        }
    }
}

void MainWindow::startNewGame() {
    mainMenu->hide();

    setWindowTitle("Adventure game");
    showFullScreen();

    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    createMenu();

    scene = new QGraphicsScene(this);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    view = new QGraphicsView(scene, centralWidget);
    mainLayout->addWidget(view, 1);

    QHBoxLayout* labels = new QHBoxLayout(centralWidget);

    diceLabel = new QLabel(centralWidget);
    diceLabel->setText(QString("Dice Roll: %1").arg(diceRoll));
    diceLabel->setStyleSheet("color: white;");
    labels->addWidget(diceLabel, 0, Qt::AlignHCenter);

    currentPlayerLabel = new QLabel(centralWidget);
    currentPlayerLabel->setText("Current Player: Player 1");
    currentPlayerLabel->setStyleSheet("color: white;");
    labels->addWidget(currentPlayerLabel, 0, Qt::AlignHCenter);

    mainLayout->addLayout(labels);

    QPushButton* rollButton = new QPushButton("Roll Dice", centralWidget);
    rollButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 10px 20px; border: none; border-radius: 4px; }");
    mainLayout->addWidget(rollButton, 0, Qt::AlignTop);
    connect(rollButton, &QPushButton::clicked, this, &MainWindow::rollDice);

    exitButton = new QPushButton("Exit Game", centralWidget);
    exitButton->setStyleSheet("QPushButton { background-color: #f44336; color: white; padding: 10px 20px; border: none; border-radius: 4px; }");
    mainLayout->addWidget(exitButton);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::exitGame);

    QPixmap background(":/images/background.png");
    background = background.scaled(TILE_SIZE * COLS, TILE_SIZE * ROWS);
    scene->setSceneRect(0, 0, background.width(), background.height());
    scene->addPixmap(background);

    std::vector<std::vector<int>> path = {
        {2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 5, 4, 1, 0, 0, 1, 0, 4, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 6, 0, 1, 0, 0, 0},
        {1, 4, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 5, 0, 1, 0, 0, 0},
        {5, 0, 0, 0, 1, 4, 1, 0, 6, 0, 0, 1, 0, 0, 1, 0, 5, 1, 6, 0},
        {6, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 5, 1, 1, 4, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    drawPath(scene, path);

    startX = 0;
    startY = 0;

    QPixmap figureImage1(":/images/player1.png");
    figureImage1 = figureImage1.scaled(TILE_SIZE, TILE_SIZE);
    figureItem1 = scene->addPixmap(figureImage1);
    figureItem1->setPos(TILE_SIZE * startX, TILE_SIZE * startY);

    QPixmap figureImage2(":/images/player2.png");
    figureImage2 = figureImage2.scaled(TILE_SIZE, TILE_SIZE);
    figureItem2 = scene->addPixmap(figureImage2);
    figureItem2->setPos(TILE_SIZE * startX, TILE_SIZE * startY);
}

void MainWindow::newGame() {
    setWindowTitle("Adventure game");
    showFullScreen();

    menuBar = new QMenuBar(this);
    setMenuBar(menuBar);
    createMenu();

    scene = new QGraphicsScene(this);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);

    view = new QGraphicsView(scene, centralWidget);
    mainLayout->addWidget(view, 1);

    QHBoxLayout* labels = new QHBoxLayout(centralWidget);

    diceLabel = new QLabel(centralWidget);
    diceLabel->setText(QString("Dice Roll: %1").arg(diceRoll));
    diceLabel->setStyleSheet("color: white;");
    labels->addWidget(diceLabel, 0, Qt::AlignHCenter);

    currentPlayerLabel = new QLabel(centralWidget);
    currentPlayerLabel->setText("Current Player: Player 1");
    currentPlayerLabel->setStyleSheet("color: white;");
    labels->addWidget(currentPlayerLabel, 0, Qt::AlignHCenter);

    mainLayout->addLayout(labels);

    QPushButton* rollButton = new QPushButton("Roll Dice", centralWidget);
    rollButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: white; padding: 10px 20px; border: none; border-radius: 4px; }");
    mainLayout->addWidget(rollButton, 0, Qt::AlignTop);
    connect(rollButton, &QPushButton::clicked, this, &MainWindow::rollDice);

    exitButton = new QPushButton("Exit Game", centralWidget);
    exitButton->setStyleSheet("QPushButton { background-color: #f44336; color: white; padding: 10px 20px; border: none; border-radius: 4px; }");
    mainLayout->addWidget(exitButton);
    connect(exitButton, &QPushButton::clicked, this, &MainWindow::exitGame);

    QPixmap background(":/images/background.png");
    background = background.scaled(TILE_SIZE * COLS, TILE_SIZE * ROWS);
    scene->setSceneRect(0, 0, background.width(), background.height());
    scene->addPixmap(background);

    std::vector<std::vector<int>> path = {
        {2, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 5, 4, 1, 0, 0, 1, 0, 4, 0, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 6, 0, 1, 0, 0, 0},
        {1, 4, 1, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 5, 0, 1, 0, 0, 0},
        {5, 0, 0, 0, 1, 4, 1, 0, 6, 0, 0, 1, 0, 0, 1, 0, 5, 1, 6, 0},
        {6, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0},
        {1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 5, 1, 1, 4, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 3},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    };

    drawPath(scene, path);

    startX = 0;
    startY = 0;

    QPixmap figureImage1(":/images/player1.png");
    figureImage1 = figureImage1.scaled(TILE_SIZE, TILE_SIZE);
    figureItem1 = scene->addPixmap(figureImage1);
    figureItem1->setPos(TILE_SIZE * startX, TILE_SIZE * startY);

    QPixmap figureImage2(":/images/player2.png");
    figureImage2 = figureImage2.scaled(TILE_SIZE, TILE_SIZE);
    figureItem2 = scene->addPixmap(figureImage2);
    figureItem2->setPos(TILE_SIZE * startX, TILE_SIZE * startY);
}

void MainWindow::mousePressEvent(QMouseEvent* event) {
    if (event->button() == Qt::LeftButton) {
        QPointF scenePos = view->mapToScene(event->pos());

        int tileX = static_cast<int>(scenePos.x()) / TILE_SIZE;
        int tileY = static_cast<int>(scenePos.y()) / TILE_SIZE;

        bool isOnLuckyTile = luckyTiles.contains(QPoint(tileX, tileY));

        bool isOnUnluckyTile = unluckyTiles.contains(QPoint(tileX, tileY));

        if (isOnLuckyTile) {
            if (currentPlayer == 1) {
                figureItem1->setPos((tileX + 3) * TILE_SIZE, tileY * TILE_SIZE);
            } else {
                figureItem2->setPos((tileX + 3) * TILE_SIZE, tileY * TILE_SIZE);
            }
        } else if (isOnUnluckyTile) {
            if (currentPlayer == 1) {
                figureItem1->setPos((tileX - 3) * TILE_SIZE, tileY * TILE_SIZE);
            } else {
                figureItem2->setPos((tileX - 3) * TILE_SIZE, tileY * TILE_SIZE);
            }
        } else if (canMove) {
            if (currentPlayer == 1) {
                figureItem1->setPos(tileX * TILE_SIZE, tileY * TILE_SIZE);
            } else {
                figureItem2->setPos(tileX * TILE_SIZE, tileY * TILE_SIZE);
            }
        }

        currentPlayer = (currentPlayer == 1) ? 2 : 1;
        currentPlayerLabel->setText(QString("Current Player: Player %1").arg(currentPlayer));

        canMove = false;
    }
}

void MainWindow::gameRules() {
    QMessageBox::information(this, "Game Rules", "We have several figures. The figures take turns moving across the playing field. Each figure takes steps depending on the generated number. There may be obstacles and help along the way: a comet - take three steps forward, a satellite - take three steps back, a canister - one extra move. The winner is the one who reaches the finish line (blue planet) faster.");
}

void MainWindow::aboutGame() {
    QMessageBox::information(this, "About Game",  "The game was created as part of educational practice by students of the Faculty of Applied Mathematics and Informatics of BSU. Github project: https://github.com/vitmark-06/Result.git");
}

void MainWindow::saveResults() {
    QDateTime endTime = QDateTime::currentDateTime();

    QString filePath = QFileDialog::getSaveFileName(this, "Save Results", QDir::homePath(), "Text Files (*.txt)");

    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
            QTextStream out(&file);

            out << "Game ended at: " << endTime.toString("yyyy-MM-dd hh:mm:ss") << Qt::endl;
            out << "Winner: " << winnerName << Qt::endl;

            file.close();
            QMessageBox::information(this, "Save Results", "Results saved successfully.");
        } else {
            QMessageBox::critical(this, "Save Results", "Failed to save results.");
        }
    }
}

void MainWindow::help() {
    QMessageBox::information(this, "Game Rules", "There may be obstacles and help along the way: a comet - take three steps forward, a satellite - take three steps back, a canister - one extra move.");
}

void MainWindow::exitGame() {
    QMessageBox::StandardButton result = QMessageBox::question(this, "Exit Game", "Are you sure you want to exit the game?",
                                                               QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::Yes) {
        QApplication::exit();
    }
}

void MainWindow::rollDice() {
    diceRoll = QRandomGenerator::global()->bounded(1, 7);
    canMove = true;

    diceLabel->setText(QString("Dice Roll: %1").arg(diceRoll));
}

void MainWindow::createMenu() {
    gameMenu = menuBar->addMenu("Game");

    newGameAction = new QAction("New Game", this);
    newGameAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_N));
    gameMenu->addAction(newGameAction);

    rulesAction = new QAction("Rules", this);
    rulesAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    gameMenu->addAction(rulesAction);

    aboutAction = new QAction("About", this);
    aboutAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_A));
    gameMenu->addAction(aboutAction);

    saveResultsAction = new QAction("Save Results", this);
    saveResultsAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_S));
    gameMenu->addAction(saveResultsAction);

    helpAction = new QAction("Help", this);
    helpAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_H));
    gameMenu->addAction(helpAction);

    exitAction = new QAction("Exit", this);
    exitAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Q));
    gameMenu->addAction(exitAction);

    connect(newGameAction, &QAction::triggered, this, &MainWindow::newGame);
    connect(rulesAction, &QAction::triggered, this, &MainWindow::gameRules);
    connect(aboutAction, &QAction::triggered, this, &MainWindow::aboutGame);
    connect(saveResultsAction, &QAction::triggered, this, &MainWindow::saveResults);
    connect(helpAction, &QAction::triggered, this, &MainWindow::help);
    connect(exitAction, &QAction::triggered, this, &MainWindow::exitGame);
}

void MainWindow::setCurrentPlayer(const QString& playerName) {
    currentPlayerLabel->setText("Current Player: " + playerName);
}
