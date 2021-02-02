#include "disparo_c.h"

disparo_c::disparo_c(QObject *parent) : QObject(parent)
{
    timer = new QTimer();
    filas = 0;
    columnas = 0;

    pixmap = new QPixmap(":/pictures/disparo_jugador.png");

    timer->start(30);
    connect(timer,&QTimer::timeout,this,&disparo_c::actualizar_disparo_caballero);
}

QRectF disparo_c::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void disparo_c::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columnas,filas,ancho,alto);
}

void disparo_c::disparo_caballero()
{
    setPos(posx,posy);
    actualizar_disparo_caballero();
}

void disparo_c::actualizar_disparo_caballero()
{
    columnas += 25;
    if(columnas >= 775){
        columnas =0;
    }
    this->update(-ancho/2, -alto/2, ancho, alto);
}

