#include <QApplication>
#include <mainwindow.h>
int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    MainWindow game;
    game.show();
    return app.exec();
}

