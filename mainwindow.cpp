#include "mainwindow.h"
#include "gameboard.h"
#include <QtWidgets>
#include <QStyle>
MainWindow::MainWindow()
{
    gameboard = new GameBoard;

    turnLabel = new QLabel;

    xScoreLcd = new QLCDNumber(3);
    xScoreLcd->setSegmentStyle(QLCDNumber::Filled);

    oScoreLcd = new QLCDNumber(3);
    oScoreLcd->setSegmentStyle(QLCDNumber::Filled);

    quitButton = new QPushButton(tr("&Quit"));
    quitButton->setFocusPolicy(Qt::NoFocus);

    connect(quitButton , SIGNAL(clicked()), qApp, SLOT(quit()));
    connect(gameboard, SIGNAL(xScoreChanged(int)), xScoreLcd, SLOT(display(int)));
    connect(gameboard, SIGNAL(oScoreChanged(int)), oScoreLcd, SLOT(display(int)));
    connect(gameboard, SIGNAL(turnChanged(bool)), this, SLOT(setTurn(bool)));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(gameboard, 0, 0, 6, 1);
    layout->addWidget(turnLabel,0,1);
    layout->addWidget(createLabel(tr("X SCORE")), 1, 1);
    layout->addWidget(xScoreLcd, 2, 1);
    layout->addWidget(createLabel(tr("O SCORE")), 3, 1);
    layout->addWidget(oScoreLcd, 4, 1);
    layout->addWidget(quitButton, 5, 1);
    setLayout(layout);

    setWindowTitle(tr("Tic-tac-toe"));
    resize(650, 350);

}

QLabel *MainWindow::createLabel(const QString &text)
{
    QLabel *lbl = new QLabel(text);
    lbl->setAlignment(Qt::AlignHCenter | Qt::AlignBottom);
    return lbl;
}

void MainWindow::setTurn(bool turn)
{
    qDebug() << "setTurn = " << turn;
    QPainter painter(this->turnLabel);
    QRect rect = turnLabel->contentsRect();

    if (turn)
    {
        turnLabel->setText(tr("O turn"));
        painter.drawText(rect, Qt::AlignTop, tr("O turn"));
        return;
    }
    else
    {
        turnLabel->setText(tr("X turn"));
        painter.drawText(rect, Qt::AlignTop, tr("X turn"));
        return;
    }
}
