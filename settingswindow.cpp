#include "settingswindow.h"

SettingsWindow::SettingsWindow(QWidget *parent) : QDialog(parent) {
    setWindowTitle("Settings");
    setGeometry(300, 200, 400, 300);

    playersComboBox = new QComboBox;
    playersComboBox->addItems({"1", "2", "3", "4"});
    playersComboBox->setStyleSheet("QComboBox { background-color: #ffffff; color: #333333; padding: 5px; border-radius: 5px; }");

    nextButton = new QPushButton("Next");
    nextButton->setStyleSheet("QPushButton { background-color: #4CAF50; color: #ffffff; padding: 10px 20px; border-radius: 5px; }"
                              "QPushButton:hover { background-color: #45a049; }");

    cancelButton = new QPushButton("Cancel");
    cancelButton->setStyleSheet("QPushButton { background-color: #f44336; color: #ffffff; padding: 10px 20px; border-radius: 5px; }"
                                "QPushButton:hover { background-color: #d32f2f; }");

    QPixmap backgroundImage(":/images/background.png");
    QPalette palette(this->palette());
    palette.setBrush(QPalette::Window, backgroundImage);
    this->setPalette(palette);

    QVBoxLayout* mainLayout = new QVBoxLayout;
    QLabel* playerLabel = new QLabel("Number of players:");
    playerLabel->setStyleSheet("QLabel { font-size: 16px; font-weight: bold; color: #ffffff; padding: 10px; border-radius: 5px; }");
    playerLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(playerLabel);
    mainLayout->addWidget(playersComboBox);
    mainLayout->addWidget(nextButton);
    mainLayout->addWidget(cancelButton);

    setLayout(mainLayout);

    connect(nextButton, &QPushButton::clicked, [this]() {
        numPlayers = playersComboBox->currentText().toInt();
        showPlayerNamesDialog();
        close();
        emit startNewGame(numPlayers, playerNames);
    });

    connect(cancelButton, &QPushButton::clicked, this, &SettingsWindow::exitButton);
    connect(this, &SettingsWindow::playerNamesEntered, this, &SettingsWindow::saveSettings);

    numPlayers = 2;
}

void SettingsWindow::saveSettings(int numPlayers, const QVector<QString>& playerNames) {
    this->numPlayers = numPlayers;
    this->playerNames = playerNames;
}

void SettingsWindow::exitButton() {
    QMessageBox::StandardButton result = QMessageBox::question(this, "Save settings", "Are you sure you want to save the settings?",
                                                               QMessageBox::Yes | QMessageBox::No);
    if (result == QMessageBox::Yes) {
        close();
    }
}

void SettingsWindow::showPlayerNamesDialog() {
    QDialog dialog(this);
    dialog.setWindowTitle("Settings");

    QVBoxLayout* dialogLayout = new QVBoxLayout;

    QLabel* stringLabel = new QLabel("Enter player names");
    dialogLayout->addWidget(stringLabel);

    for (int i = 0; i < numPlayers; ++i) {
        QHBoxLayout* playerLayout = new QHBoxLayout;
        QLabel* label = new QLabel(QString("Player %1:").arg(i + 1));
        QLineEdit* lineEdit = new QLineEdit;
        playerLayout->addWidget(label);
        playerLayout->addWidget(lineEdit);
        dialogLayout->addLayout(playerLayout);
        playerNameInputs.append(lineEdit);
    }

    saveButton = new QPushButton("Save");
    dialogLayout->addWidget(saveButton);
    dialog.setLayout(dialogLayout);

    connect(saveButton, &QPushButton::clicked, [this, &dialog]() {
        QVector<QString> playerNames;
        for (QLineEdit* input : playerNameInputs) {
            playerNames.append(input->text());
        }
        emit playerNamesEntered(playerNames.size(), playerNames);
        dialog.accept();
    });

    dialog.exec();
}
