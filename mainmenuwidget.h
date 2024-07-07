#ifndef MAINMENUWIDGET_H
#define MAINMENUWIDGET_H

#include <QFile>
#include <QLabel>
#include <QMessageBox>
#include <QPushButton>
#include <QTextStream>
#include <QVBoxLayout>
#include <QWidget>

#include "settingswindow.h"

class MainMenuWidget : public QWidget {
    Q_OBJECT

public:
    MainMenuWidget(QWidget* parent = nullptr);
    void createMainMenu();

signals:
    void startNewGame();

private slots:
    void results();
    void settings();
    void exitGame();

private:
    QPushButton* newGameButton;
    QPushButton* exitButton;
    QPushButton* resultsButton;
    QPushButton* settingsButton;
    QLabel* titleLabel;
};

#endif // MAINMENUWIDGET_H
