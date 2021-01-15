#include "oneplayer.h"
#include "ui_oneplayer.h"

oneplayer::oneplayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::oneplayer)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->start(6);


    scene = new QGraphicsScene(this);
    scene->setSceneRect(0,0,1280,720);
    scene->setBackgroundBrush(QPixmap(":/pictures/nivel_1.png"));
    ui->graphicsView->setScene(scene);

    //EN MODO JUGADOR UNICO
    bars.push_back(new grafica);
    bars.back()->actualizar_grafica();
    scene->addItem(bars.back());

    contras.push_back(new muros(0, 0)); scene->addItem(contras.back());

    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

}

oneplayer::~oneplayer()
{
    delete ui;
}

bool oneplayer::nivel1()
{
    dato = ":/niveles/nivel_1/1_1.txt";
    fstream archivo_nivel (dato.c_str(), fstream :: in);

//    while (!archivo_nivel.eof()){
//        archivo_nivel.getline(dato);
//    }



}

void oneplayer::actualizar()
{
    for (int i = 0;i< bars.size() ;i++ ) {
        bars.at(i)->actualizar_grafica();
        borderCollision(bars.at(i)->getEsf());
    }
}

void oneplayer::borderCollision(elemento *b)
{
    if(b->getPX()<b->getR()){
        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getR(),b->getPY());
    }
    if(b->getPX()>1280-b->getR()){
        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),1280-b->getR(),b->getPY());
    }
    if(b->getPY()<b->getR()){
        b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),b->getR());
    }
    if(b->getPY()>720-b->getR()){
        b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),720-b->getR());
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
    else if(event->key() == Qt::Key_W && bars.at(0)->getEsf()->getVY() <= 1 && bars.at(0)->getEsf()->getVY() >= -1){

        if (bars.at(0)->moment == 2  || bars.at(0)->moment == 0 ) bars.at(0)->moment = 4;
        else if (bars.at(0)->moment == 3 || bars.at(0)->moment == 1) bars.at(0)->moment = 5;

        b->set_vel(b->getVX(),60,b->getPX(),b->getPY());

    }
}

void oneplayer::on_actionVolver_triggered()
{
    close();
}
