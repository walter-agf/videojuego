#include "oneplayer.h"
#include "ui_oneplayer.h"

oneplayer::oneplayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::oneplayer)
{
    ui->setupUi(this);

    h_limit = 1280;
    v_limit = 720;

    timer = new QTimer(this);
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,h_limit,v_limit);
    scene->setBackgroundBrush(QPixmap(":/pictures/nivel_1.png"));

    ui->graphicsView->setScene(scene);



    //EN MODO JUGADOR UNICO
    timer->start(6);
    bars.push_back(new grafica);
    bars.back()->actualizar_grafica(v_limit);
    scene->addItem(bars.back());


    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

}

oneplayer::~oneplayer()
{
    delete ui;
}

void oneplayer::actualizar()
{
    for (int i = 0;i< bars.size() ;i++ ) {
        bars.at(i)->actualizar_grafica(v_limit);
        borderCollision(bars.at(i)->getEsf());
    }
}

void oneplayer::borderCollision(elemento *b)
{
    if(b->getPX()<b->getR()){
        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getR(),b->getPY());
    }
    if(b->getPX()>h_limit-b->getR()){
        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),h_limit-b->getR(),b->getPY());
    }
    if(b->getPY()<b->getR()){
        b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),b->getR());
    }
    if(b->getPY()>v_limit-b->getR()){
        b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),v_limit-b->getR());
    }
}

void oneplayer::keyPressEvent(QKeyEvent *event)
{
    elemento * b = bars.at(0)->getEsf();


    if(event->key() == Qt::Key_D){

        bars.at(0)->moment = 2;

        b->set_vel(12,b->getVY(),b->getPX(),b->getPY());


    }
    else if(event->key() == Qt::Key_A){

        bars.at(0)->moment = 3;

        b->set_vel(-12,b->getVY(),b->getPX(),b->getPY());


    }
    else if(event->key() == Qt::Key_W){

        b->set_vel(b->getVX(),60,b->getPX(),b->getPY());

    }
}

void oneplayer::on_actionVolver_triggered()
{
    close();
}
