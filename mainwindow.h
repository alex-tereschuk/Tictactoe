#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QLCDNumber>

class GameBoard;

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    explicit MainWindow();

private:
    QLabel *createLabel(const QString &text);

    QLabel *turnLabel;
    GameBoard *gameboard;
    QLCDNumber *xScoreLcd;
    QLCDNumber *oScoreLcd;
    QPushButton *quitButton;

public slots:
    void setTurn(bool turn);
};

#endif // MAINWINDOW_H
