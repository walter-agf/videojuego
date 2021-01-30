#include "jefe_uno.h"

jefe_uno::jefe_uno(QObject *parent)
{
    timer = new QTimer();
    filas = 0;
    columnas = 0;

    pixmap = new QPixmap(":/pictures/wizard idle__reboot.png");

    timer->start(120);
    connect(timer,&QTimer::timeout,this,&jefe_uno::actualizacion_sprites_jefe_uno);
}

QRectF jefe_uno::boundingRect() const
{
    return QRectF(-ancho/2,-alto/2,ancho,alto);
}

void jefe_uno::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-ancho/2,-alto/2,*pixmap,columnas,filas,ancho,alto);
}

void jefe_uno::actualizar_jefe_uno()
{
    setPos(posx,posy);
    actualizacion_sprites_jefe_uno();
}

void jefe_uno::actualizacion_sprites_jefe_uno()
{
    columnas += 320;
    if(columnas >= 3200){
        columnas =0;
    }
    this->update(-ancho/2, -alto/2, ancho, alto);
}
