#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setStyle("fusion");
    MainWindow w;
    w.show();

    QMediaPlayer *musica = new QMediaPlayer();
    musica->setMedia(QUrl("qrc:/sonidos/Spring Village.ogg"));
    musica->play();

    return a.exec();
}
