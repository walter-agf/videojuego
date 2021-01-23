#include "minotauro.h"

minotauro::minotauro(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    filas = 0;
    columnas = 0;

    pixmap = new QPixmap(":/pictures/Minotaur_-_Sprite_Sheet.png");

    timer->start(120);
    connect(timer,&QTimer::timeout,this,&minotauro::actualizacion_sprites_minotauro);
}

QRectF minotauro::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void minotauro::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columnas,filas,ancho,alto);
}

void minotauro::actualizar_minotauro()
{
    setPos(posx,posy);
    actualizacion_sprites_minotauro();
}

void minotauro::actualizacion_sprites_minotauro()
{
    columnas += 96;
    if(columnas >= 480){
        columnas =0;
    }
    this->update(-ancho/2, -alto/2, ancho, alto);
}
