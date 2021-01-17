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


    nivel1("1");

    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

}

oneplayer::~oneplayer()
{
    delete ui;
}

void oneplayer::nivel1(string num)
{
    dato = "../videojuego/niveles/"+num+".txt";
    fstream archivo_nivel (dato.c_str(), fstream :: in);

    while (!archivo_nivel.eof()){

        dato = "";

        while (dato.back() != '\n' ){
            if (archivo_nivel.eof()) break;
            else dato.push_back(archivo_nivel.get());
        }

        //Averigua Dato de posicion en x
        x_pix = dato.substr(0,dato.find(' '));

        dato = dato.substr(dato.find(' ')+1,dato.find('\n'));

        //Averigua dato de posicion en y
        y_pix = dato.substr(0,dato.find(' '));

        dato = dato.substr(dato.find(' ')+1,dato.find('\n'));

        //Averigua dato de tamaño en x
        x_tam = dato.substr(0,dato.find(' '));

        dato = dato.substr(dato.find(' ')+1,dato.find('\n'));

        //A-verigua dato de tamaño en y
        y_tam = dato.substr(dato.find(' ')+1,dato.find('\n'));

        //Elimina datos de ultimo valor por si puedan existir
        y_tam = y_tam.substr(0,y_tam.find('\n'));

        y_tam = y_tam.substr(0,y_tam.find(char(-1)));

        //CONVERSOR A ENTERO
        //Convierte a entero el valor de cadena de poscion en x
        largo = x_pix.size();
        numero_x = 0;
        for(int i = 0; i<largo; i++){
            numero_x += (int (x_pix[i])-48) * pow(10,largo - i -1);
        }

        //Convierte a entero el valor de cadena de poscion en y
        largo = y_pix.size();
        numero_y = 0;
        for(int i = 0; i<largo; i++){
            numero_y += (int (y_pix[i])-48) * pow(10,largo - i -1);
        }

        //Convierte a entero el valor de cadena de tamaño en x
        largo = x_tam.size();
        cantidad_x = 0;
        for(int i = 0; i<largo; i++){
            cantidad_x += (int (x_tam[i])-48) * pow(10,largo - i -1);
        }

        //Convierte a entero el valor de cadena de tamaño en y
        largo = y_tam.size();
        cantidad_y = 0;
        for(int i = 0; i<largo; i++){
            cantidad_y += (int (y_tam[i])-48) * pow(10,largo - i -1);
        }

        //Lo agrega a la scena
        contras.push_back(new muros(numero_x, numero_y, cantidad_x, cantidad_y)); scene->addItem(contras.back());

    }
    archivo_nivel.close();
}

void oneplayer::actualizar()
{   

    for (int i = 0;i< bars.size() ;i++ ) {

        elemento *b = bars.at(i)->getEsf();

        bars.at(i)->actualizar_grafica();
        borderCollision(b);


        for (int a = 0;a < contras.size();a++) {

            if (bars[i]->collidesWithItem(contras[a])){

                //PISO
                if (b->getVY() < 1 && b->getPX() > contras[a]->getposx() && b->getPX() < contras[a]->getposx() + contras[a]->getw()){
                    b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),b->getPY()+0.0225);
                }

                //DERECHA
                if (b->getPX()+b->getR() <= contras[a]->getposx()){
                    b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX(),b->getPY()+0.0171);
                }

                //IZQUIERDA
                if (b->getPX() - b->getR() >= contras[a]->getposx() + contras[a]->getw()){
                    b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX(),b->getPY()+0.0171);
                }

                //CIELO
                if (720 - b->getPY() > contras[a]->getposy() + contras[a]->geth()){
                    b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),b->getPY());
                }
            }
        }
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
    elemento *b = bars.at(0)->getEsf();


    if(event->key() == Qt::Key_D){

        bars.at(0)->moment = 2;

        b->set_vel(12,b->getVY(),b->getPX(),b->getPY());

        for (int a = 0;a < contras.size();a++) {

            if (bars[0]->collidesWithItem(contras[a]) && b->getPX() + b->getR() <= contras[a]->getposx()){
                b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX()-0.1,b->getPY()+0.0171);
            }
        }
    }
    else if(event->key() == Qt::Key_A){

        bars.at(0)->moment = 3;

        b->set_vel(-12,b->getVY(),b->getPX(),b->getPY());

        for (int a = 0;a < contras.size();a++) {

            if (bars[0]->collidesWithItem(contras[a]) && b->getPX() - b->getR() >= contras[a]->getposx() + contras[a]->getw()){
                b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX()+0.1,b->getPY()+0.0171);
            }
        }


    }
    else if(event->key() == Qt::Key_W && bars.at(0)->getEsf()->getVY() <= 1 && bars.at(0)->getEsf()->getVY() >= -1){

        if (bars.at(0)->moment == 2  || bars.at(0)->moment == 0 ) {
            bars.at(0)->moment = 4;
            b->set_vel(b->getVX()+ 6 ,60,b->getPX(),b->getPY());
        }
        else if (bars.at(0)->moment == 3 || bars.at(0)->moment == 1) {
            bars.at(0)->moment = 5;
            b->set_vel(b->getVX()- 6 ,60,b->getPX(),b->getPY());
        }



        for (int a = 0;a < contras.size();a++) {

            if (bars[0]->collidesWithItem(contras[a]) && 720 - b->getPY() > contras[a]->getposy() + contras[a]->geth()){
                b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),b->getPY());
            }
        }

    }
}

void oneplayer::on_actionVolver_triggered()
{
    close();
}
