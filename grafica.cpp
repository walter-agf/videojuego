#include "grafica.h"

grafica::grafica(QObject *parent) : QObject(parent)
{
    float posx,posy,velx,vely,mass,r,K,e,ancho,alto;
    posx = 50;
    posy = 300;
    r = 20;
    mass = 50;
    velx = 0;
    vely = 0;
    K = 0.1;
    e = 0.2;
    ancho = 44;
    alto = 40;
    esf = new elemento(posx,posy,velx,vely,mass,r,K,e,ancho,alto);

    timer = new QTimer();
    filas = 0;
    columnas = 0;

    pixmap = new QPixmap(":/pictures/Escudero.png");

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

void grafica::actualizar_grafica(float v_lim)
{
    esf->actualizar_elemento();
    setPos(esf->getPX(),v_lim-esf->getPY());
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
    this->update(-esf->getAncho()/2,-esf->getAlto()/2,esf->getAncho(),esf->getAlto());


    if (moment == 2 )moment = 0;
    else if (moment == 3 )moment = 1;

}
