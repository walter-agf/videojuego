#include "multiplayer.h"
#include "ui_multiplayer.h"

multiplayer::multiplayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::multiplayer)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->start(6);

    h_limit = 720;
    w_limit = 0;
    num = "1"; //Selecciona el nivel a comenzar

    scene = new QGraphicsScene(this);
    scene->setSceneRect(w_limit,0,1280,720);
    ui->graphicsView->setScene(scene);

    //EN MODO JUGADOR UNICO
    bars.push_back(new grafica);
    bars.back()->actualizar_grafica();
    scene->addItem(bars.back());

    //EN MODO DOS JUGADORES
    bars.push_back(new grafica);
    bars.back()->actualizar_grafica();
    scene->addItem(bars.back());
    nivel(num);
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

}
multiplayer::~multiplayer()
{  delete ui;}
void multiplayer::nivel(string num_)
{
    vector<string> estacion;
    contras.clear();

    if (num_ == "1"){
        scene->setBackgroundBrush(QPixmap(":/pictures/nivel_1.png"));
        estacion = uno();
    }
    else if (num_ == "2"){
        scene->setBackgroundBrush(QPixmap(":/pictures/nivel_2.png"));
        estacion = dos();
        for (int i = 0; i < magos.size(); i++){
            magos.pop_back();
        }
    }
    else if (num_ == "3"){
        scene->setBackgroundBrush(QPixmap(":/pictures/nivel_3.png"));
        estacion = tres();
        for (int i = 0; i < magos.size(); i++){
            magos.pop_back();
        }
    }

    for (int i = 0; i < estacion.size(); i++){

        //Averigua Dato de posicion en x
        x_pix = estacion[i].substr(0,estacion[i].find(' '));
        estacion[i] = estacion[i].substr(estacion[i].find(' ')+1,estacion[i].find('S'));

        //Averigua dato de posicion en y
        y_pix = estacion[i].substr(0,estacion[i].find(' '));
        estacion[i] = estacion[i].substr(estacion[i].find(' ')+1,estacion[i].find('S'));

        //Averigua dato de tamaño en x

        x_tam = estacion[i].substr(0,estacion[i].find(' '));
        estacion[i] = estacion[i].substr(estacion[i].find(' ')+1,estacion[i].find('S'));

        //A-verigua dato de tamaño en y

        y_tam = estacion[i].substr(0,estacion[i].find('S'));

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

        if (cantidad_x >= 160){
            //Prueba agregar un mago
            magos.push_back(new mago);
            magos.back()->posx = (cantidad_x/2) + numero_x;
            magos.back()->posy = numero_y-30;
            magos.back()->actualizar_mago();
            scene->addItem(magos.back());
        }
    }
}

void multiplayer::actualizar()
{
    for (int i = 0;i< bars.size() ;i++ ) {
        elemento *b = bars.at(i)->getEsf();
        bars.at(i)->actualizar_grafica();
        borderCollision(b);
        for (int a = 0;a < contras.size();a++) {

            if (bars[i]->collidesWithItem(contras[a])){

                //PISO
                if (b->getVY() < 1 && b->getPX() > contras[a]->getposx() && b->getPX() < contras[a]->getposx() + contras[a]->getw() && 730 - b->getPY() < contras[a]->getposy()){
                    b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),b->getPY()+0.047);
                }

                //DERECHA
                if (b->getPX()+20 <= contras[a]->getposx() && b->getVX() > -1){
                    b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX(),b->getPY()+0.0171);
                }

                //IZQUIERDA
                else if (b->getPX()-20 >= contras[a]->getposx() + contras[a]->getw() && b->getVX() < 1){
                    b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX(),b->getPY()+0.0171);
                }
            }
        }

        //Cambios de pantalla o nivel
        //Avanzar pantalla
        if (b->getPX() + 22 > w_limit + 1280 && b->getPX() < 4000){
            w_limit += 1280;
            b->set_vel(b->getVX(),b->getVY(),b->getPX()+60,b->getPY());
            scene->setSceneRect(w_limit,0,1280,720);
        }
        //Retroceder pantalla
        else if (b->getPX() - 22 < w_limit && b->getPX() > 200){
            w_limit -= 1280;
            b->set_vel(b->getVX(),b->getVY(),b->getPX()-60,b->getPY());
            scene->setSceneRect(w_limit,0,1280,720);
        }
        //Cambio de nivel
        else if (b->getPX() + 22 > 5070){
            if (num == "1"){num = "2";}
            else if (num == "2"){num = "3";}
            else if  (num == "3"){
                QString val;
                val = "";
                val += "Felicitaciones :D\n\nHas Ganado";
                QMessageBox::about (this,"ContraCruzada", val);
                close();
            }
            w_limit = 0;
            scene->setSceneRect(w_limit,0,1280,720);
            b->set_vel(0,0,50,300);
            nivel(num);
        }
        else if (700 + b->getPY() <= 720 && bars[i]->moment != 6 && bars[i]->moment != 7){
            if (bars[i]->moment == 0 || bars[i]->moment == 2 || bars[i]->moment == 4 || bars[i]->moment == 8){bars[i]->moment = 6;}
            else {bars[i]->moment = 7;}
            b->set_vel(0,0,b->getPX(),b->getPY());
        }
        else if (bars[i]->moment == 6 || bars[i]->moment == 7){
            if (bars[i]->columnas == 396){
                QString val;
                val = "";
                val += "Jugador 1 Elimindo :_(\n\nDerrotado";
                QMessageBox::about (this,"ContraCruzada", val);
                conti = false;
                bars[i]->columnas = 440;
            }
        }
        if (conti == false){
            close();
        }
    }
}

void multiplayer::borderCollision(elemento *b)
{
    if(b->getPX()<b->getR()){
        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getR(),b->getPY());
    }
    if(b->getPX()>5120-b->getR()){
        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),5120-b->getR(),b->getPY());
    }
    if(b->getPY()<b->getR()){
        b->set_vel(b->getVX(),-1*b->getE()*b->getVY(),b->getPX(),b->getR());
    }
}

void multiplayer::keyPressEvent(QKeyEvent *event)
{
    elemento *b = bars.at(0)->getEsf();
    elemento *z = bars.at(1)->getEsf();


    if (conti == true){

        if(event->key() == Qt::Key_D){

            bars.at(0)->moment = 2;

            b->set_vel(12,b->getVY(),b->getPX(),b->getPY());

            for (int a = 0;a < contras.size();a++) {

                if (bars[0]->collidesWithItem(contras[a]) && b->getPX() + b->getR() <= contras[a]->getposx()){
                    b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX(),b->getPY()+0.0171);
                }
            }
        }
        else if(event->key() == Qt::Key_A){

            bars.at(0)->moment = 3;

            b->set_vel(-12,b->getVY(),b->getPX(),b->getPY());

            for (int a = 0;a < contras.size();a++) {

                if (bars[0]->collidesWithItem(contras[a]) && b->getPX() - b->getR() >= contras[a]->getposx() + contras[a]->getw()){
                    b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX(),b->getPY()+0.0171);
                }
            }


        }
        else if(event->key() == Qt::Key_W && bars.at(0)->getEsf()->getVY() <= 1 && bars.at(0)->getEsf()->getVY() >= -1){

            if (bars.at(0)->moment == 2  || bars.at(0)->moment == 0 ) {
                bars.at(0)->moment = 4;
                if (b->getVX()<=1){b->set_vel(b->getVX(),64,b->getPX(),b->getPY());}
                else {b->set_vel(b->getVX()+12 ,64,b->getPX(),b->getPY());}

            }
            else if (bars.at(0)->moment == 3 || bars.at(0)->moment == 1) {
                bars.at(0)->moment = 5;
                if (b->getVX()>=-1){b->set_vel(b->getVX(),64,b->getPX(),b->getPY());}
                else {b->set_vel(b->getVX()-12 ,64,b->getPX(),b->getPY());}
            }

        }
        if (event->key() == Qt::Key_S){

            for (int a = 0;a < contras.size();a++) {

                if (bars[0]->collidesWithItem(contras[a]) && b->getV() > 0){
                    b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX(),b->getPY()+0.0171);
                }
            }

            if (bars[0]->moment == 0){
                bars[0]->moment = 8;
                b->set_vel(b->getVX() + 14,b->getVY(),b->getPX(),b->getPY());

                for (int a = 0;a < contras.size();a++) {

                    if (bars[0]->collidesWithItem(contras[a]) && b->getPX() - b->getR() >= contras[a]->getposx() + contras[a]->getw()){
                        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX(),b->getPY()+0.0171);
                    }
                }

            }
            else if (bars[0]->moment == 1){
                bars[0]->moment = 9;
                b->set_vel(b->getVX() - 14,b->getVY(),b->getPX(),b->getPY());

                for (int a = 0;a < contras.size();a++) {

                    if (bars[0]->collidesWithItem(contras[a]) && b->getPX() - b->getR() >= contras[a]->getposx() + contras[a]->getw()){
                        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX(),b->getPY()+0.0171);
                    }
                }
            }

            else if (bars[0]->moment == 2 ){
                bars[0]->moment = 8;
                b->set_vel(b->getVX() + 28,b->getVY(),b->getPX(),b->getPY());

                for (int a = 0;a < contras.size();a++) {

                    if (bars[0]->collidesWithItem(contras[a]) && b->getPX() - b->getR() >= contras[a]->getposx() + contras[a]->getw()){
                        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX(),b->getPY()+0.0171);
                    }
                }

            }
            else if (bars[0]->moment == 3 ){
                bars[0]->moment = 9;
                b->set_vel(b->getVX() - 28,b->getVY(),b->getPX(),b->getPY());

                for (int a = 0;a < contras.size();a++) {

                    if (bars[0]->collidesWithItem(contras[a]) && b->getPX() - b->getR() >= contras[a]->getposx() + contras[a]->getw()){
                        b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX(),b->getPY()+0.0171);
                    }
                }
            }
        }

    }


    //__________________________

    if(event->key() == Qt::Key_L){

        bars.at(1)->moment = 2;

        z->set_vel(12,z->getVY(),z->getPX(),z->getPY());

        for (int a = 0;a < contras.size();a++) {

            if (bars[1]->collidesWithItem(contras[a]) && z->getPX() + z->getR() <= contras[a]->getposx()){
                z->set_vel(-1*z->getE()*z->getVX(),z->getVY(),z->getPX(),z->getPY()+0.0171);
            }
        }
    }


    //___________________________-



}
void multiplayer::on_actionVolver_triggered(){close();}

void multiplayer::on_actionReiniciar_triggered()
{
    close();
    one = new multiplayer(this);
    one->show();
}
