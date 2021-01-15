#include "inicio.h"

inicio::inicio(QObject *parent) : QObject(parent)
{
    timer_inicio = new QTimer();
    filas = 0;
    columnas = 0;

    pixmap_inicio = new QPixmap(":/pictures/fondo.png");

    //dimensiones de cada imagen
    ancho = 1280;
    alto = 720;

    //Configuracion de la musica
    //Creacion de playlist
    playlist = new QMediaPlaylist();
    playlist->addMedia(QUrl("qrc:/sonidos/Spring_Village.mp3"));
    playlist->addMedia(QUrl("qrc:/sonidos/Shinrin-Yoku.mp3"));
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    //configuracion del reproductor
    musica = new QMediaPlayer();
    musica->setPlaylist(playlist);
    musica->play();

    timer_inicio->start(64);
    connect(timer_inicio,&QTimer::timeout,this,&inicio::Actualizacion_Inicio);

}

void inicio::Actualizacion_Inicio()
{
    columnas += 1280;
    if(columnas >= 5120){
        columnas = 0;
        filas += 720;

        if (filas >= 3600){
            columnas = 0;
            filas = 0;
        }
    }
    this->update(-ancho/2,-alto/2,ancho,alto);
}

QRectF inicio::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void inicio::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap_inicio,columnas,filas,ancho,alto);
}
