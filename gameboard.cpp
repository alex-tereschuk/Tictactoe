#include "gameboard.h"
#include "QEvent"
GameBoard::GameBoard(QWidget *parent) :
    QFrame(parent)
{
    // review notes: Вам знаком список инициализации членов класса? Стоит его здесь применять или нет?
    turn = true;
    xScore = 0;
    oScore = 0;
    setFrameStyle(QFrame::Panel | QFrame::Sunken);
    //   this->
    QGridLayout *layout = new QGridLayout;
    for (int i = 0; i < BoardSize; i++)
        for (int j = 0; j < BoardSize; j++)
            layout->addWidget(board[i][j].frame,i,j);
    setLayout(layout);
}

bool GameBoard::GetTurn()
{
    return turn;
}

void GameBoard::mousePressEvent(QMouseEvent *e)
{
    if ((e->button()) == Qt::LeftButton)
        for (int i = 0; i < BoardSize; i++)
            for (int j = 0; j < BoardSize; j++)
            {
                if (board[i][j].frame->frameGeometry().contains(e->pos()))
                {
                    if (board[i][j].cell == Nothing)
                    {
                        if(turn)
                        {
                            board[i][j].SetO();
                            turn = !turn;
                            if (Victory() == O)
                            {
                                oScore++;
                                emit oScoreChanged(oScore);
                            }
                        }
                        else
                        {
                            board[i][j].SetX();
                            turn = !turn;
                            if (Victory() == X)
                            {
                                xScore++;
                                emit xScoreChanged(xScore);
                            }
                        }
                    }
                }
            }
}

// review notes: Как вы считаете, не является ли данный метод очень большим по размеру?
Symbol GameBoard::Victory()
{
    //Horizontal lines
    Symbol winner;
    for (int i = 0; i < BoardSize; i++)
        for (int j = 1; j < BoardSize; j++)
        {
            if (board[i][j].cell != board[i][j-1].cell ||
                    board[i][j].cell == Nothing)
                break;
            if (j == BoardSize - 1)
            {
                qDebug() << "Horizontal " << i << " WINS";
                winner = board[i][j].cell;
                BoardReset();
                return winner;
            }
        }

    //Vertical lines
    for (int j = 0; j < BoardSize; j++)
        for (int i = 1; i < BoardSize; i++)
        {
            if (board[i][j].cell != board[i-1][j].cell ||
                    board[i][j].cell == Nothing)
                break;
            if (i == BoardSize - 1)
            {
                qDebug() << "Vertical " << j << " WINS";
                winner = board[i][j].cell;
                BoardReset();
                return winner;
            }
        }

    //Diagonal lines
    for (int i = 1; i < BoardSize; i++)
    {
        if (board[i][i].cell != board[i-1][i-1].cell ||
                board[i][i].cell == Nothing)
            break;
        if (i == BoardSize - 1)
        {
            qDebug() << "Diagonal WINS";
            winner = board[i][i].cell;
            BoardReset();
            return winner;
        }
    }
    for (int i = 1; i < BoardSize; i++)
    {
        if (board[i][BoardSize-i-1].cell != board[i-1][BoardSize-i].cell ||
                board[i][BoardSize-i-1].cell == Nothing)
            break;
        if (i == BoardSize - 1)
        {
            qDebug() << "ReverseDiagonal WINS";
            winner = board[i][BoardSize-i-1].cell;
            BoardReset();
            return winner;
        }
    }
    int draw = 0;
    for (int i = 0; i < BoardSize; i++)
        for (int j = 0; j < BoardSize; j++)
            if (board[i][j].cell == Nothing)
                draw++;
    if(draw == 0)
    {
        BoardReset();
        qDebug() << "Draw";
    }

    return Nothing;
}

void GameBoard::BoardReset()
{
    for (int i = 0; i < BoardSize; i++)
        for (int j = 0; j < BoardSize; j++)
            board[i][j].Reset();
}


