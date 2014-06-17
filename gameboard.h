#ifndef GAMEBOARD_H
#define GAMEBOARD_H

#include <QtWidgets>
#include <QFrame>
#include <QPointer>
#include <QLabel>
#include "qpainter.h"

enum Symbol { Nothing, X, O };
struct Board{
    Symbol cell;
    QFrame *frame;
    Board()
    {
        cell = Nothing;
        frame = new QFrame;
        frame->setStyleSheet("border-image: url(:/images/images/back.bmp);");
    }
    void SetX(){cell = X; frame->setStyleSheet("border-image: url(:/images/images/X.bmp);");}
    void SetO(){cell = O; frame->setStyleSheet("border-image: url(:/images/images/O.bmp);");}
    void Reset(){cell = Nothing; frame->setStyleSheet("border-image: url(:/images/images/back.bmp);");}
};
const int BoardSize = 3;


class GameBoard : public QFrame
{
    Q_OBJECT
public:
    explicit GameBoard(QWidget *parent = 0);
    bool GetTurn();

signals:
    void oScoreChanged(int oScore);
    void xScoreChanged(int xScore);
    void turnChanged(bool turn);
public slots:

protected:
    void mousePressEvent(QMouseEvent *e);

private:
    Symbol Victory();
    void BoardReset();

    Board board[BoardSize][BoardSize];
    bool turn;
    int oScore;
    int xScore;

};

#endif // GAMEBOARD_H
