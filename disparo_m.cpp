#include "disparo_m.h"

disparo_m::disparo_m(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    filas = 0;
    columnas = 0;

    pixmap = new QPixmap(":/pictures/ataque_mago.png");

    timer->start(50);
    connect(timer,&QTimer::timeout,this,&disparo_m::actualizar_disparo_mago);
}

QRectF disparo_m::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void disparo_m::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columnas,filas,ancho,alto);
}

void disparo_m::disparo_mago()
{
    setPos(posx,posy);
    actualizar_disparo_mago();
}

void disparo_m::actualizar_disparo_mago()
{
    columnas += 68;
    if(columnas >= 544){
        columnas =0;
    }
    this->update(-ancho/2, -alto/2, ancho, alto);
}
