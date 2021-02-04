#include "grafica.h"

grafica::grafica(QObject *parent) : QObject(parent)
{
    esf = new elemento(posx,posy,velx,vely,mass,r,K,e,ancho,alto);

    timer = new QTimer();
    filas = 0;
    columnas = 0;

    pixmap = new QPixmap(":/pictures/personaje_1.png");

    timer->start(48);
    connect(timer,&QTimer::timeout,this,&grafica::actualizacion_sprites);
}

grafica::~grafica()
{
    delete esf;
}


QRectF grafica::boundingRect() const
{
    return QRectF(-esf->getAncho()/2,-esf->getAlto()/2,esf->getAncho(),esf->getAlto());
}

void grafica::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawPixmap(-esf->getAncho()/2,-esf->getAlto()/2,*pixmap,columnas,filas,esf->getAncho(),esf->getAlto());
}

void grafica::actualizar_grafica()
{
    esf->actualizar_elemento();
    setPos(esf->getPX(),720-esf->getPY());
}

elemento *grafica::getEsf()
{
    return esf;
}

void grafica::actualizacion_sprites()
{
    if (moment == 0){

        filas = 0;
        columnas += 44;
        if(columnas >= 352){
            columnas =0;
        }

    }

    else if (moment == 1){

        filas = 40;
        columnas += 44;
        if(columnas >= 352){
            columnas =0;
        }

    }

    else if (moment == 2){

        filas = 80;
        columnas += 44;
        if(columnas >= 440){
            columnas =0;
        }

    }

    else if (moment == 3){

        filas = 120;
        columnas += 44;
        if(columnas >= 440){
            columnas =0;
        }

    }

    else if (moment == 4){

        filas = 160;
        columnas += 44;
        if(columnas >= 132){
            columnas =0;
        }

    }

    else if (moment == 5){

        filas = 200;
        columnas += 44;
        if(columnas >= 132){
            columnas =0;
        }

    }

    else if (moment == 6){
        timer->start(100);
        filas = 240;
        if(columnas < 396){
            columnas += 44;
        }
    }

    else if (moment == 7){
        timer->start(100);
        filas = 280;
        if(columnas < 396){
            columnas += 44;
        }
    }
    else if (moment == 8){

        filas = 320;
        columnas += 44;
        if(columnas >= 396){
            columnas =0;
        }

    }
    else if (moment == 9){

        filas = 360;
        columnas += 44;
        if(columnas >= 396){
            columnas =0;
        }

    }

    this->update(-esf->getAncho()/2,-esf->getAlto()/2,esf->getAncho(),esf->getAlto());


    if (moment == 2)moment = 0;
    else if (moment == 3 )moment = 1;

    if (esf->getVY() <= 1 && esf->getVY() >= -1){
        if (moment == 4)moment = 0;
        else if (moment == 5)moment = 1;
    }
    if (esf->getVX() <= 3 && esf->getVX() >= -3 && esf->getVY() < 1 && esf->getVY() > 0){
        if (moment == 8)moment = 0;
        else if (moment == 9)moment = 1 ;
    }
}
