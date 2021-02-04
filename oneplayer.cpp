#include "oneplayer.h"
#include "ui_oneplayer.h"

oneplayer::oneplayer(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::oneplayer)
{
    ui->setupUi(this);
    timer = new QTimer(this);
    timer->start(7);
    //se dan limites de ubicacion de la scena que deseamos
    h_limit = 720;
    w_limit = 0;
    //se contrulle diche scena
    scene = new QGraphicsScene(this);
    scene->setSceneRect(w_limit,0,1280,720);
    ui->graphicsView->setScene(scene);

    //EN MODO JUGADOR UNICO
    jug = new grafica(this);
    jug->actualizar_grafica();
    scene->addItem(jug);

    //Se construye el nivel seleccionado
    num = "1"; //Selecciona el nivel a comenzar
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
        //Vida
        vida_one = 100;
        ui->vida->setText(QString::number(vida_one));
        ui->vida->setStyleSheet("font: 75 18pt 'Verdana';color: rgb(0, 255, 0);");
        //Puntuacion
        puntuacion_one = 0;
        ui->puntuacion->setText(QString::number(puntuacion_one));
        ui->puntuacion->setStyleSheet("font: 75 18pt 'Verdana';color: rgb(255, 220, 44);");
        for (int i = 0; i < contras.size(); i++){scene->removeItem(contras[i]);}
        contras.clear();
        for (int i = 0; i < magos.size(); i++){scene->removeItem(magos[i]);}
        magos.clear();
        for (int i = 0; i < tauros.size(); i++){scene->removeItem(tauros[i]);}
        jefe = new jefe_uno(this);
        jefe->posx = 4960;
        jefe->posy = 400;
        jefe->actualizar_jefe_uno();
        scene->addItem(jefe);
        //vida del jefe
        vida_j = 1000;
        ui->vida_jefe->setText(QString::number(vida_j));
        ui->vida_jefe->setStyleSheet("font: 75 18pt 'Verdana';color: rgb(255, 0, 4);");
        enemigo = 1;
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
        //vida del jefe
        vida_j = 1000;
        ui->vida_jefe->setText(QString::number(vida_j));
        ui->vida_jefe->setStyleSheet("font: 75 18pt 'Verdana';color: rgb(255, 0, 4);");
        enemigo = 1;
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
        //vida del jefe
        vida_j = 1000;
        ui->vida_jefe->setText(QString::number(vida_j));
        ui->vida_jefe->setStyleSheet("font: 75 18pt 'Verdana';color: rgb(255, 0, 4);");
        enemigo = 1;
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
        for(int i = 0; i<largo; i++){numero_x += (int (x_pix[i])-48) * pow(10,largo - i -1);}
        //Convierte a entero el valor de cadena de poscion en y
        largo = y_pix.size();
        numero_y = 0;
        for(int i = 0; i<largo; i++){numero_y += (int (y_pix[i])-48) * pow(10,largo - i -1);}
        //Convierte a entero el valor de cadena de tamaño en x
        largo = x_tam.size();
        cantidad_x = 0;
        for(int i = 0; i<largo; i++){cantidad_x += (int (x_tam[i])-48) * pow(10,largo - i -1);}
        //Convierte a entero el valor de cadena de tamaño en y
        largo = y_tam.size();
        cantidad_y = 0;
        for(int i = 0; i<largo; i++){cantidad_y += (int (y_tam[i])-48) * pow(10,largo - i -1);}
        //Lo agrega a la scena
        contras.push_back(new muros(numero_x, numero_y, cantidad_x, cantidad_y)); scene->addItem(contras.back());
        //Se agregan los enemigos, segun el tamaño de la base
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
    if ( estado != 0){estado -= 1;}//contador de tiempo de star cuando es atacado
    if ( con_cad != 0){con_cad -= 1;}//contador de tiempo de disparo
    if ( est_mago != 0){est_mago -= 1;}//contador de disparo de los magos
    if ( disparo_jefe != 0){disparo_jefe -= 1;}//contador de disparo del jefe

    elemento *b = jug->getEsf();
    jug->actualizar_grafica();
    borderCollision(b);
    //----------------Disparo____del__jugador_______
    for (int o = 0; o < discab.size(); o++){
        if (discab[o]->moment == 0 || discab[o]->moment == 2 || discab[o]->moment == 4 || discab[o]->moment == 8){discab[o]->posx += 2;}
        else {discab[o]->posx -= 2;}
        discab[o]->setPos(discab[o]->posx,discab[o]->posy);
        eliminar = false;
        discab[o]->rango -=2;//eliminar disparo del jugador
        //Minotarua
        for (int t = 0;t < tauros.size();t++){
            if (tauros[t]->collidesWithItem(discab[o])){
                scene->removeItem(tauros[t]);
                tauros.removeAt(t);
                puntuacion_one += 400 * dificultad;
                ui->puntuacion->setText(QString::number(puntuacion_one));
                eliminar = true;
                break;
            }
        }
        //Mago
        for (int m = 0;m < magos.size() && eliminar != true;m++){
            if (magos[m]->collidesWithItem(discab[o])){
                scene->removeItem(magos[m]);
                magos.removeAt(m);
                puntuacion_one += 600 * dificultad;
                ui->puntuacion->setText(QString::number(puntuacion_one));
                eliminar = true;
                break;
            }
        }
        //Bala
        for (int e = 0;e < dismag.size() && eliminar!= true;e++){
            if (dismag[e]->collidesWithItem(discab[o])){
                scene->removeItem(dismag[e]);
                dismag.removeAt(e);
                puntuacion_one += 100 * dificultad;
                ui->puntuacion->setText(QString::number(puntuacion_one));
                eliminar = true;
                break;
            }
        }
        if (jefe != NULL){
            if (jefe->collidesWithItem(discab[o])){
                puntuacion_one += 100 * dificultad;
                ui->puntuacion->setText(QString::number(puntuacion_one));
                vida_j -= 50 / dificultad;//resta del jefe
                if (vida_j < 0) {vida_j = 0;}
                ui->vida_jefe->setText(QString::number(vida_j));
                eliminar = true;
            }
            if (vida_j <= 0){
                puntuacion_one += 700 * dificultad;
                ui->puntuacion->setText(QString::number(puntuacion_one));
                scene->removeItem(jefe);
                jefe = NULL;
            }
        }
        //eliminar disparo
        if (eliminar == true){
            scene->removeItem(discab[o]);
            discab.removeAt(o);
        }//rango de disparo que no coliciona
        else if (discab[o]->rango <= 0){
            scene->removeItem(discab[o]);
            discab.removeAt(o);
        }
    }
    //______________________________________________

    for (int j = 0; j < dis_j1.size(); j++){ // disparo uno de jefe
        dis_j1[j]->posx -= 2 *dificultad;
        dis_j1[j]->setPos(dis_j1[j]->posx,dis_j1[j]->posy);
        if (dis_j1[j]->collidesWithItem(jug)){
            vida_one -= 4;//resta del jefe
            ui->vida->setText(QString::number(vida_one));
            scene->removeItem(dis_j1[j]);
            dis_j1.removeAt(j);
        }
    }
    if (dis_j1.size() > 0){
        if (dis_j1[0]->posx < 3840){
            scene->removeItem(dis_j1[0]);
            dis_j1.removeAt(0);
        }
    }
    for (int u = 0; u < dis_j2.size(); u++){ // disparo dos del jefe
        dis_j2[u]->posy += 2 * dificultad;
        dis_j2[u]->setPos(dis_j2[u]->posx,dis_j2[u]->posy);

        if (dis_j2[u]->collidesWithItem(jug)){
            vida_one -= 6;//resta del jefe
            ui->vida->setText(QString::number(vida_one));
            scene->removeItem(dis_j2[u]);
            dis_j2.removeAt(u);
        }

        for (int y = 0; y < contras.size(); y++){
            if (dis_j2[u]->collidesWithItem(contras[y])){
                scene->removeItem(dis_j2[u]);
                dis_j2.removeAt(u);
            }
        }
    }
    //______________________________________________
    for (int a = 0;a < contras.size();a++) {
        if (jug->collidesWithItem(contras[a])){
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
            //Enemigos__________________________Fisica_Logicas___________________________________________________
            for (int t = 0;t < tauros.size();t++){
                if (tauros[t]->collidesWithItem(contras[a])){ //movimiento
                    if (b->getPX() < tauros[t]->posx){ // derecha
                        tauros[t]->moment = 3;
                        tauros[t]->posx -= 0.8 * dificultad; //Vel_Derecha
                        tauros[t]->setPos(tauros[t]->posx,tauros[t]->posy);
                    }
                    else if (b->getPX() > tauros[t]->posx){ //izquierda
                        tauros[t]->moment = 2;
                        tauros[t]->posx += 0.8 *  dificultad; // Vel_ Izquierda
                        tauros[t]->setPos(tauros[t]->posx,tauros[t]->posy);
                    }
                    if (tauros[t]->collidesWithItem(jug) && estado == 0 && vida_one > 0){ //colicion con el jugador
                        vida_one -= 4;
                        ui->vida->setText(QString::number(vida_one));
                        if (b->getPX() < tauros[t]->posx){b->set_vel(-20,10,b->getPX()-10,b->getPY()+0.0171);}
                        else {b->set_vel(20,10,b->getPX()+10,b->getPY()+0.0171);}
                        estado = 300;
                    }
                }
            }
            for (int m = 0;m < magos.size();m++){ // fisica de magos
                distancia = pow(b->getPX() - magos[m]->posx,2);
                distancia += pow((720 - b->getPY()) - magos[m]->posy,2);
                distancia = pow (distancia,0.5);//calculo del rango
                if (distancia < (magos[m]->rango * dificultad) && estado == 0  && vida_one > 0){
                    if (magos[m]->collidesWithItem(jug) && estado == 0 && vida_one > 0){
                        vida_one -= 4;
                        ui->vida->setText(QString::number(vida_one));
                        if (b->getPX() < magos[m]->posx){b->set_vel(-20,10,b->getPX()-10,b->getPY()+0.0171);}
                        else {b->set_vel(20,10,b->getPX()+10,b->getPY()+0.0171);}
                    }
                    estado = 500 / dificultad; //velocidad de disparo del mago
                    //disparo_mago
                    dismag.push_back(new disparo_m);
                    dismag.back()->posx = magos[m]->posx;
                    dismag.back()->posy = magos[m]->posy;
                    dismag.back()->setPos(dismag.back()->posx,dismag.back()->posy);
                    scene->addItem(dismag.back());
                    est_mago = 800; //tiempo_disparo_del_mago
                }
            }
            //_________________Disparo__Jefe________________

            if (b->getPX() > 3840 && vida_j > 0 && disparo_jefe == 0){ //disparo recto
                tipo_dis=1+rand()%(10);
                if ( tipo_dis <= 5){
                    dis_j1.push_back(new dis_jefe_1);
                    dis_j1.back()->posx = jefe->posx;
                    dis_j1.back()->posy = 720 - jug->getEsf()->getPY();
                    dis_j1.back()->setPos(dis_j1.back()->posx,dis_j1.back()->posy);
                    scene->addItem(dis_j1.back());
                }
                else if (tipo_dis > 5 && tipo_dis <= 8) { // disparo alto
                    tipo_dis=3840+rand()%(100);
                    while (tipo_dis < 5120){
                        dis_j2.push_back(new dis_jefe_2);
                        dis_j2.back()->posx = tipo_dis;
                        dis_j2.back()->posy = 24;
                        dis_j2.back()->setPos(dis_j2.back()->posx,dis_j2.back()->posy);
                        scene->addItem(dis_j2.back());
                        tipo_dis += 150 / dificultad;
                    }
                }
                else { //invocacion
                    for (int n = 0; n < contras.size(); n++){
                        if (contras[n]->posx >= 3840){
                            if ( num == "3" && tauros.size() < enemigo + 3){
                                tauros.push_back(new minotauro);
                                tauros.back()->posx = (cantidad_x/2) + numero_x;
                                tauros.back()->posy = numero_y-18;
                                tauros.back()->actualizar_minotauro();
                                scene->addItem(tauros.back());
                            }
                            else {
                                tipo_dis=1+rand()%(3);
                                if (tipo_dis == 2 && magos.size() < enemigo + 3){
                                    magos.push_back(new mago);
                                    magos.back()->posx = (contras[n]->w/2) + contras[n]->posx;
                                    magos.back()->posy = contras[n]->posy-30;
                                    magos.back()->actualizar_mago();
                                    scene->addItem(magos.back());
                                }
                            }
                        }
                    }
                }
                disparo_jefe = 420 / dificultad;
            }
            //______________________________________________
            if (jug->collidesWithItem(jefe)){ //colicion con el jefe
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
        if (b->getPX() -22 > 3800){
            if (num == "3"){enemigo = tauros.size();}
            else {enemigo = magos.size();}
        }
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
        //_______________________________________
        string name = "guardar.txt", data = "";
        fstream k(name, fstream::out | fstream::ate);
        data += to_string(puntuacion_one) + "\n";
        data += to_string(vida_one) + "\n";
        data += to_string(dificultad) +"\n";
        data += num;
        k.write(data.c_str(), data.length());
        k.close();
        //_______________________________________
        w_limit = 0;
        scene->setSceneRect(w_limit,0,1280,720);
        b->set_vel(0,0,50,300);
        nivel(num);
    }
    else if (700 + b->getPY() <= 720 && jug->moment != 6 && jug->moment != 7){
        if (jug->moment == 0 || jug->moment == 2 || jug->moment == 4 || jug->moment == 8){jug->moment = 6;}
        else {jug->moment = 7;}
        b->set_vel(0,0,b->getPX(),b->getPY());
        vida_one = 0;
    }
    else if (vida_one <= 0){
        if (jug->moment == 0 || jug->moment == 2 || jug->moment == 4 || jug->moment == 8){jug->moment = 6;}
        else {jug->moment = 7;}
        b->set_vel(0,0,b->getPX(),b->getPY());
    }
    if (jug->moment == 6 || jug->moment == 7){
        if (jug->columnas == 396 && vida_one <= 0){
            //___________________________________________



            //___________________________________________
            QString val;
            val = "";
            val += "Jugador 1 Elimindo :_(\n\nDerrotado";
            QMessageBox::about (this,"ContraCruzada", val);
            conti = false;
            jug->moment = 10;
            jug->columnas = 440;
        }
    }
    if (conti == false){
        close();
    }
    for (int e=0; e < dismag.size(); e++){ // disparos del mago

        if (b->getPX() < dismag[e]->posx){
            dismag[e]->posx -= 0.6 * dificultad;
            dismag[e]->setPos(dismag[e]->posx,dismag[e]->posy);
        }
        else if (b->getPX() > dismag[e]->posx){
            dismag[e]->posx += 0.6 * dificultad;
            dismag[e]->setPos(dismag[e]->posx,dismag[e]->posy);
        }


        if (720 - b->getPY() < dismag[e]->posy){
            dismag[e]->posy -= 0.6 * dificultad;
            dismag[e]->setPos(dismag[e]->posx,dismag[e]->posy);
        }

        else if (720 - b->getPY() > dismag[e]->posy){
            dismag[e]->posy += 0.6 * dificultad;
            dismag[e]->setPos(dismag[e]->posx,dismag[e]->posy);
        }

        if (dismag[e]->collidesWithItem(jug)){
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
    elemento *b = jug->getEsf();

    if (conti == true){

        if(event->key() == Qt::Key_D){

            jug->moment = 2;

            b->set_vel(12,b->getVY(),b->getPX(),b->getPY());

            for (int a = 0;a < contras.size();a++) {

                if (jug->collidesWithItem(contras[a]) && b->getPX() + b->getR() <= contras[a]->getposx()){
                    b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX(),b->getPY()+0.0171);
                }
            }
        }
        if(event->key() == Qt::Key_A){

            jug->moment = 3;

            b->set_vel(-12,b->getVY(),b->getPX(),b->getPY());

            for (int a = 0;a < contras.size();a++) {

                if (jug->collidesWithItem(contras[a]) && b->getPX() - b->getR() >= contras[a]->getposx() + contras[a]->getw()){
                    b->set_vel(-1*b->getE()*b->getVX(),b->getVY(),b->getPX(),b->getPY()+0.0171);
                }
            }


        }
        if(event->key() == Qt::Key_W && jug->getEsf()->getVY() <= 1 && jug->getEsf()->getVY() >= -1){

            if (jug->moment == 2  || jug->moment == 0 ) {
                jug->moment = 4;
                if (b->getVX()<=1){b->set_vel(b->getVX(),70,b->getPX(),b->getPY());}
                else {b->set_vel(b->getVX()+12 ,70,b->getPX(),b->getPY());}

            }
            else if (jug->moment == 3 || jug->moment == 1) {
                jug->moment = 5;
                if (b->getVX()>=-1){b->set_vel(b->getVX(),70,b->getPX(),b->getPY());}
                else {b->set_vel(b->getVX()-12 ,70,b->getPX(),b->getPY());}
            }

        }
        if (event->key() == Qt::Key_S){
            for (int a = 0;a < contras.size();a++) {
                if (jug->collidesWithItem(contras[a]) && b->getPX() + 10 >= contras[a]->getposx() + contras[a]->getw()){
                    b->set_vel(0,b->getVY(),b->getPX(),b->getPY()+0.0171);
                }
            }
            if (jug->moment == 4){
                jug->moment = 8;
                b->set_vel(b->getVX(),b->getVY() - 16,b->getPX(),b->getPY());
            }
            else if (jug->moment == 5){
                jug->moment = 9;
                b->set_vel(b->getVX(),b->getVY() - 16,b->getPX(),b->getPY());
            }
            else if (jug->moment == 2 && b->getVX() > 0){
                jug->moment = 8;
                b->set_vel(b->getVX() + 16,b->getVY(),b->getPX(),b->getPY());
            }
            else if (jug->moment == 3 && b->getVX() < 0){
                jug->moment = 9;
                b->set_vel(b->getVX() - 16,b->getVY(),b->getPX(),b->getPY());
            }
        }
        //_____________Disparo____________________________________________
        if(event->key() == Qt::Key_Space && con_cad == 0){
            //Prueba agregar un disparo_mago
            discab.push_back(new disparo_c);
            discab.back()->posx = jug->getEsf()->getPX();
            discab.back()->posy = 720 - jug->getEsf()->getPY();
            discab.back()->moment = jug->moment;
            discab.back()->setPos(discab.back()->posx,discab.back()->posy);
            discab.back()->rango /= dificultad;
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

void oneplayer::on_actionComo_Jugar_triggered()
{

}

void oneplayer::on_actionCargar_partida_triggered()
{
    if (jefe != NULL){
        scene->removeItem(jefe);
        jefe = NULL;
    }
    long long int tam;
    string name, aux;
    int i;
    name = "guardar.txt";
    string data;
    fstream k(name, fstream::in | fstream::ate);
    if(k.is_open()){
        tam=k.tellg();
        k.seekg(0);
        for(long long int e=0;e<tam; e++) data.push_back(k.get());
        for(i=0; i<= data.find('\n'); i++){
          aux.push_back(data[i]);
        }
        puntuacion_one = atoi(aux.c_str());
        ui->puntuacion->setText(QString::number(puntuacion_one));
        aux = "";
        for ( ; data[i]!='\n'; i++){
            aux.push_back(data[i]);
        }
        vida_one = atoi(aux.c_str());
        ui->vida->setText(QString::number(vida_one));

        aux = "";
        i++;
        for ( ; data[i]!='\n'; i++){
            aux.push_back(data[i]);
        }
        dificultad = stof(aux);
        num = data[i+1];
        w_limit = 0;
        scene->setSceneRect(w_limit,0,1280,720);
        jug->getEsf()->set_vel(0,0,50,300);
        nivel(num);
  }
  else {
      QString val;
      val = "";
      val += "La partida no existe";
      QMessageBox::about (this,"ContraCruzada", val);
  }
  k.close();
}

void oneplayer::on_actionGuardar_partida_triggered(){}
