#ifndef ELEMENTO_H
#define ELEMENTO_H

class elemento
{
private:
    float PX; //pos en x
    float PY; //pos en y
    float mass; // masa del elemento
    float R; //radio del elemento
    float VX; //vel en x
    float VY; //vel en y
    float angulo; //angulo en el que va el elemento
    float AX; //acel en x
    float AY; //acel en y
    float G; //gravedad
    float K; //Resistencia del aire
    float e; //Coeficiente de restitucion
    float V; //vector de velocidad
    float dt; //delta tiempo
    float ancho;
    float alto;
public:
    elemento(float posX_,float posY_,float velX_,float velY_,float masa_,float radio_,float K_,float e_, float ancho_, float alto_);
    ~elemento();


    void actualizar_elemento();

    float getV() const;
    float getAX() const;
    float getAY() const;
    float getPX() const;
    float getPY() const;
    float getMass() const;
    float getR() const;
    float getVX() const;
    float getVY() const;
    float getE() const;
    void set_vel(float vx, float vy, float px, float py);
    float getAncho() const;
    float getAlto() const;
};

#endif // ELEMENTO_H
