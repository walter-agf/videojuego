#include "oneplayer.h"
#include "ui_oneplayer.h"

oneplayer::oneplayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::oneplayer)
{
    ui->setupUi(this);

    timer = new QTimer(this);
    timer->start(7);

    h_limit = 720;
    w_limit = 0;
    num = "3"; //Selecciona el nivel a comenzar

    scene = new QGraphicsScene(this);
    scene->setSceneRect(w_limit,0,1280,720);
    ui->graphicsView->setScene(scene);

    //EN MODO JUGADOR UNICO
    bars.push_back(new grafica);
    bars.back()->actualizar_grafica();
    scene->addItem(bars.back());
    nivel(num);
    connect(timer,SIGNAL(timeout()),this,SLOT(actualizar()));

}
oneplayer::~oneplayer()
{  delete ui;}
void oneplayer::nivel(string num_)
{   
    vector<string> estacion;

    if (num_ == "1"){
        scene->setBackgroundBrush(QPixmap(":/pictures/nivel_1.png"));
        estacion = uno();
        vida_one = 100;
        ui->vida->setText(QString::number(vida_one));
        ui->vida->setStyleSheet("font: 75 18pt 'Verdana';color: rgb(0, 255, 0);");
        jefe = new jefe_uno(this);
        jefe->posx = 4960;
        jefe->posy = 400;
        jefe->actualizar_jefe_uno();
        scene->addItem(jefe);
    }
    else if (num_ == "2"){
        scene->setBackgroundBrush(QPixmap(":/pictures/nivel_2.png"));
        estacion = dos();
        for (int i = 0; i < contras.size(); i++){scene->removeItem(contras[i]);}
        contras.clear();
        for (int i = 0; i < magos.size(); i++){scene->removeItem(magos[i]);}
        magos.clear();
        for (int i = 0; i < tauros.size(); i++){scene->removeItem(tauros[i]);}
        tauros.clear();
        jefe = new jefe_uno(this);
        jefe->posx = 4960;
        jefe->posy = 400;
        jefe->actualizar_jefe_uno();
        scene->addItem(jefe);
    }
    else if (num_ == "3"){
        scene->setBackgroundBrush(QPixmap(":/pictures/nivel_3.png"));
        estacion = tres();
        for (int i = 0; i < contras.size(); i++){scene->removeItem(contras[i]);}
        contras.clear();
        for (int i = 0; i < magos.size(); i++){scene->removeItem(magos[i]);}
        magos.clear();
        for (int i = 0; i < tauros.size(); i++){scene->removeItem(tauros[i]);}
        tauros.clear();
        jefe = new jefe_uno(this);
        jefe->posx = 4960;
        jefe->posy = 480;
        jefe->actualizar_jefe_uno();
        scene->addItem(jefe);
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

        if (cantidad_x >= 200){
            if (enemigo == 1 || enemigo == 2){
                    //Prueba agregar un minotauro
                    tauros.push_back(new minotauro);
                    tauros.back()->posx = (cantidad_x/2) + numero_x;
                    tauros.back()->posy = numero_y-18;
                    tauros.back()->actualizar_minotauro();
                    scene->addItem(tauros.back());
                    enemigo++;
                }
            else if (enemigo == 3){
                    //Prueba agregar un mago
                    magos.push_back(new mago);
                    magos.back()->posx = (cantidad_x/2) + numero_x;
                    magos.back()->posy = numero_y-30;
                    magos.back()->actualizar_mago();
                    scene->addItem(magos.back());
                    enemigo = 1;
                }
        }
    }
}

void oneplayer::actualizar()
{   
    if ( estado != 0){
        estado -= 1;
    }
    if ( con_cad != 0){
        con_cad -= 1;
    }
    if ( est_mago != 0){
        est_mago -= 1;
    }

    for (int i = 0;i< bars.size() ;i++ ) {
        elemento *b = bars.at(i)->getEsf();
        bars.at(i)->actualizar_grafica();
        borderCollision(b);
        //----------------Disparo___________

        for (int o = 0; o < discab.size(); o++){
            if (discab[o]->moment == 0 || discab[o]->moment == 2 || discab[o]->moment == 4 || discab[o]->moment == 8){discab[o]->posx += 2;}
            else {discab[o]->posx -= 2;}
            discab[o]->setPos(discab[o]->posx,discab[o]->posy);
            eliminar = false;
            discab[o]->rango -=2;
            //Minotarua
            for (int t = 0;t < tauros.size();t++){
                if (tauros[t]->collidesWithItem(discab[o])){
                    scene->removeItem(tauros[t]);
                    tauros.removeAt(t);
                    eliminar = true;
                    break;
                }
            }
            //Mago
            for (int m = 0;m < magos.size() && eliminar != true;m++){
                if (magos[m]->collidesWithItem(discab[o])){
                    scene->removeItem(magos[m]);
                    magos.removeAt(m);
                    eliminar = true;
                    break;
                }
            }
            //Bala
            for (int e = 0;e < dismag.size() && eliminar!= true;e++){
                if (dismag[e]->collidesWithItem(discab[o])){
                    scene->removeItem(dismag[e]);
                    dismag.removeAt(e);
                    eliminar = true;
                    break;
                }
            }

            if (eliminar == true){
                scene->removeItem(discab[o]);
                discab.removeAt(o);
            }
            else if (discab[o]->rango <= 0){
                scene->removeItem(discab[o]);
                discab.removeAt(o);
            }
        }

        //__________________________________
        for (int a = 0;a < contras.size();a++) {

            if (bars[i]->collidesWithItem(contras[a])){

                //PISO
                if (b->getVY() < 1 && b->getPX() > contras[a]->getposx()-10 && b->getPX() < contras[a]->getposx() + contras[a]->getw()+10 && 730 - b->getPY()< contras[a]->getposy()){
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


                //Enemigos__________________________________________________________________________________

                for (int t = 0;t < tauros.size();t++){
                    if (tauros[t]->collidesWithItem(contras[a])){
                        if (b->getPX() < tauros[t]->posx){
                            tauros[t]->moment = 3;
                            tauros[t]->posx -= 0.8;
                            tauros[t]->setPos(tauros[t]->posx,tauros[t]->posy);
                        }
                        else if (b->getPX() > tauros[t]->posx){
                            tauros[t]->moment = 2;
                            tauros[t]->posx += 0.8;
                            tauros[t]->setPos(tauros[t]->posx,tauros[t]->posy);
                        }


                        if (tauros[t]->collidesWithItem(bars[i]) && estado == 0 && vida_one > 0){
                            vida_one -= 4;
                            ui->vida->setText(QString::number(vida_one));
                            if (b->getPX() < tauros[t]->posx){b->set_vel(-20,10,b->getPX()-10,b->getPY()+0.0171);}
                            else {b->set_vel(20,10,b->getPX()+10,b->getPY()+0.0171);}
                            estado = 300;
                        }
                    }
                }

                for (int m = 0;m < magos.size();m++){

                    distancia = pow(b->getPX() - magos[m]->posx,2);
                    distancia += pow((720 - b->getPY()) - magos[m]->posy,2);
                    distancia = pow (distancia,0.5);

                    if (distancia < magos[m]->rango && estado == 0  && vida_one > 0){

                        if (magos[m]->collidesWithItem(bars[i]) && estado == 0 && vida_one > 0){
                            vida_one -= 4;
                            ui->vida->setText(QString::number(vida_one));
                            if (b->getPX() < magos[m]->posx){b->set_vel(-20,10,b->getPX()-10,b->getPY()+0.0171);}
                            else {b->set_vel(20,10,b->getPX()+10,b->getPY()+0.0171);}
                        }
                        estado = 200;
                        //Prueba agregar un disparo_mago
                        dismag.push_back(new disparo_m);
                        dismag.back()->posx = magos[m]->posx;
                        dismag.back()->posy = magos[m]->posy;
                        dismag.back()->setPos(dismag.back()->posx,dismag.back()->posy);
                        scene->addItem(dismag.back());
                        est_mago = 1200;
                    }
                }

                if (bars[i]->collidesWithItem(jefe)){
                    if (estado == 0 && vida_one > 0){
                        vida_one -= 10;
                        if (vida_one < 0){vida_one=0;}
                        ui->vida->setText(QString::number(vida_one));
                        estado = 200;
                    }
                    b->set_vel(-30,b->getVY()+10,b->getPX()-20,b->getPY()+0.0171);
                }
                //__________________________________________________________________________________________
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
            if (b->getPX() -22 > 3800){
                b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX() + 10,b->getPY());
            }
            else{
                w_limit -= 1280;
                b->set_vel(b->getVX(),b->getVY(),b->getPX()-60,b->getPY());
                scene->setSceneRect(w_limit,0,1280,720);
            }
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
            vida_one = 0;
        }
        else if (vida_one <= 0){
            if (bars[i]->moment == 0 || bars[i]->moment == 2 || bars[i]->moment == 4 || bars[i]->moment == 8){bars[i]->moment = 6;}
            else {bars[i]->moment = 7;}
            b->set_vel(0,0,b->getPX(),b->getPY());
        }
        if (bars[i]->moment == 6 || bars[i]->moment == 7){
            if (bars[i]->columnas == 396 && vida_one <= 0){
                QString val;
                val = "";
                val += "Jugador 1 Elimindo :_(\n\nDerrotado";
                QMessageBox::about (this,"ContraCruzada", val);
                conti = false;
                bars[i]->moment = 10;
                bars[i]->columnas = 440;
            }
        }
        if (conti == false){
            close();
        }
        for (int e=0; e < dismag.size(); e++){

            if (b->getPX() < dismag[e]->posx){
                dismag[e]->posx -= 0.6;
                dismag[e]->setPos(dismag[e]->posx,dismag[e]->posy);
            }
            else if (b->getPX() > dismag[e]->posx){
                dismag[e]->posx += 0.6;
                dismag[e]->setPos(dismag[e]->posx,dismag[e]->posy);
            }


            if (720 - b->getPY() < dismag[e]->posy){
                dismag[e]->posy -= 0.6;
                dismag[e]->setPos(dismag[e]->posx,dismag[e]->posy);
            }

            else if (720 - b->getPY() > dismag[e]->posy){
                dismag[e]->posy += 0.6;
                dismag[e]->setPos(dismag[e]->posx,dismag[e]->posy);
            }

            if (dismag[e]->collidesWithItem(bars[i])){
                vida_one -= 6;
                ui->vida->setText(QString::number(vida_one));
                scene->removeItem(dismag[e]);
                dismag.removeAt(e);
            }
            else if (est_mago <= 0){
                scene->removeItem(dismag[0]);
                dismag.removeAt(0);
            }
        }
    }
}

void oneplayer::borderCollision(elemento *b)
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

void oneplayer::keyPressEvent(QKeyEvent *event)
{
    elemento *b = bars.at(0)->getEsf();

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
        if(event->key() == Qt::Key_A){

            bars.at(0)->moment = 3;

            b->set_vel(-12,b->getVY(),b->getPX(),b->getPY());

            for (int a = 0;a < contras.size();a++) {

                if (bars[0]->collidesWithItem(contras[a]) && b->getPX() - b->getR() >= contras[a]->getposx() + contras[a]->getw()){
                    b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX(),b->getPY()+0.0171);
                }
            }


        }
        if(event->key() == Qt::Key_W && bars.at(0)->getEsf()->getVY() <= 1 && bars.at(0)->getEsf()->getVY() >= -1){

            if (bars.at(0)->moment == 2  || bars.at(0)->moment == 0 ) {
                bars.at(0)->moment = 4;
                if (b->getVX()<=1){b->set_vel(b->getVX(),70,b->getPX(),b->getPY());}
                else {b->set_vel(b->getVX()+12 ,70,b->getPX(),b->getPY());}

            }
            else if (bars.at(0)->moment == 3 || bars.at(0)->moment == 1) {
                bars.at(0)->moment = 5;
                if (b->getVX()>=-1){b->set_vel(b->getVX(),70,b->getPX(),b->getPY());}
                else {b->set_vel(b->getVX()-12 ,70,b->getPX(),b->getPY());}
            }

        }
        if (event->key() == Qt::Key_S){
            for (int a = 0;a < contras.size();a++) {
                if (bars[0]->collidesWithItem(contras[a]) && b->getPX() + 10 >= contras[a]->getposx() + contras[a]->getw()){
                    b->set_vel(0,b->getVY(),b->getPX(),b->getPY()+0.0171);
                }
            }
            if (bars[0]->moment == 4){
                bars[0]->moment = 8;
                b->set_vel(b->getVX(),b->getVY() - 16,b->getPX(),b->getPY());
            }
            else if (bars[0]->moment == 5){
                bars[0]->moment = 9;
                b->set_vel(b->getVX(),b->getVY() - 16,b->getPX(),b->getPY());
            }
            else if (bars[0]->moment == 2 && b->getVX() > 0){
                bars[0]->moment = 8;
                b->set_vel(b->getVX() + 16,b->getVY(),b->getPX(),b->getPY());
            }
            else if (bars[0]->moment == 3 && b->getVX() < 0){
                bars[0]->moment = 9;
                b->set_vel(b->getVX() - 16,b->getVY(),b->getPX(),b->getPY());
            }
        }

        //_____________Disparo____________________________________________

        if(event->key() == Qt::Key_E && con_cad == 0){
            //Prueba agregar un disparo_mago
            discab.push_back(new disparo_c);
            discab.back()->posx = bars[0]->getEsf()->getPX();
            discab.back()->posy = 720 - bars[0]->getEsf()->getPY();
            discab.back()->moment = bars[0]->moment;
            discab.back()->setPos(discab.back()->posx,discab.back()->posy);
            scene->addItem(discab.back());
            con_cad = 100;
        }

    }
}
void oneplayer::on_actionVolver_triggered(){close();}

void oneplayer::on_actionReiniciar_triggered()
{
    close();
    one = new oneplayer(this);
    one->show();
}

void oneplayer::on_actionPausa_triggered()
{
    if (timer->isActive()){
        timer->stop();
    }
    else {
        timer->start(7);
    }

}
