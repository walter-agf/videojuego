#include "mago.h"

mago::mago(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    filas = 0;
    columnas = 0;

    pixmap = new QPixmap(":/pictures/Mago-2.png");

    timer->start(120);
    connect(timer,&QTimer::timeout,this,&mago::actualizacion_sprites_mago);
}

QRectF mago::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void mago::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columnas,filas,ancho,alto);
}

void mago::actualizar_mago()
{
    setPos(posx,posy);
    actualizacion_sprites_mago();
}

void mago::actualizacion_sprites_mago()
{
    columnas += 40;
    if(columnas >= 320){
        columnas =0;
    }
    this->update(-ancho/2, -alto/2, ancho, alto);
}
