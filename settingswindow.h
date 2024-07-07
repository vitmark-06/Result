#ifndef SETTINGSWINDOW_H
#define SETTINGSWINDOW_H

#include <QApplication>
#include <QDebug>
#include <QDialog>
#include <QComboBox>
#include <QMessageBox>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QString>
#include <QVector>

class SettingsWindow : public QDialog {
    Q_OBJECT

public:
    SettingsWindow(QWidget *parent = nullptr);

signals:
    void startNewGame(int numPlayers, const QVector<QString>& playerNames);
    void playerNamesEntered(int numPlayers, const QVector<QString>& playerNames);
    void settingsSaved(int numPlayers, const QVector<QString>& playerNames);

private slots:
    void showPlayerNamesDialog();
    void exitButton();
    void saveSettings(int numPlayers, const QVector<QString>& playerNames);

private:
    QComboBox* playersComboBox;
    QPushButton* nextButton;
    QPushButton* cancelButton;

    QPushButton* saveButton;
    QVector<QLineEdit*> playerNameInputs;
    int numPlayers;
    QVector<QString> playerNames;
};

#endif // SETTINGSWINDOW_H
