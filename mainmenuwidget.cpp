#include "mainmenuwidget.h"

MainMenuWidget::MainMenuWidget(QWidget *parent): QWidget(parent) {
    createMainMenu();
}

void MainMenuWidget::createMainMenu() {
    setWindowTitle("Adventure game");
    setGeometry(300, 200, 1000, 600);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->setSpacing(20);

    newGameButton = new QPushButton("New game");
    newGameButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: #ffffff; padding: 10px 20px; border-radius: 5px; }"
                                 "QPushButton:hover { background-color: #45a049; }");
    newGameButton->setMinimumHeight(60);
    newGameButton->setMinimumWidth(300);
    newGameButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    exitButton = new QPushButton("Exit");
    exitButton->setStyleSheet("QPushButton { background-color: #f44336; color: #ffffff; padding: 10px 20px; border-radius: 5px; }"
                              "QPushButton:hover { background-color: #d32f2f; }");
    exitButton->setMinimumHeight(60);
    exitButton->setMinimumWidth(300);
    exitButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    resultsButton = new QPushButton("Results");
    resultsButton->setStyleSheet("QPushButton { background-color: #2196F3; color: #ffffff; padding: 10px 20px; border-radius: 5px; }"
                                 "QPushButton:hover { background-color: #1976D2; }");
    resultsButton->setMinimumHeight(60);
    resultsButton->setMinimumWidth(300);
    resultsButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    settingsButton = new QPushButton("Settings");
    settingsButton->setStyleSheet("QPushButton { background-color: #9C27B0; color: #ffffff; padding: 10px 20px; border-radius: 5px; }"
                                  "QPushButton:hover { background-color: #7B1FA2; }");
    settingsButton->setMinimumHeight(60);
    settingsButton->setMinimumWidth(300);
    settingsButton->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    titleLabel = new QLabel("Adventure Game");
    titleLabel->setStyleSheet("font-size: 36px; font-weight: bold; color: #f2f2f2;");

    mainLayout->addSpacing(50);
    mainLayout->addWidget(titleLabel, 0, Qt::AlignCenter);
    mainLayout->addWidget(newGameButton, 1, Qt::AlignCenter);
    mainLayout->addWidget(resultsButton, 1, Qt::AlignCenter);
    mainLayout->addWidget(settingsButton, 1, Qt::AlignCenter);
    mainLayout->addWidget(exitButton, 1, Qt::AlignCenter);

    setLayout(mainLayout);

    QPixmap backgroundImage(":/images/background.png");
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Window, backgroundImage);
    this->setPalette(palette);

    connect(newGameButton, &QPushButton::clicked, this, &MainMenuWidget::startNewGame);
    connect(resultsButton, &QPushButton::clicked, this, &MainMenuWidget::results);
    connect(settingsButton, &QPushButton::clicked, this, &MainMenuWidget::settings);
    connect(exitButton, &QPushButton::clicked, this, &MainMenuWidget::exitGame);
}

void MainMenuWidget::results() {
    QString fileName = "results.txt";
    QFile file(fileName);

    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        QString contents = in.readAll();
        file.close();

        QMessageBox::information(this, "Results", contents);
    } else {
        QMessageBox::warning(this, "Error", "Failed to open the results file.");
    }
}

void MainMenuWidget::settings() {
    SettingsWindow settingsWindow(this);
    settingsWindow.exec();
}

void MainMenuWidget::exitGame() {
    QMessageBox::StandardButton result = QMessageBox::question(this, "Save settings", "Are you sure you want to save the settings?",
                                                               QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::Yes) {
        QApplication::quit();
    }
}
