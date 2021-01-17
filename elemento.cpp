#include "elemento.h"
#include <math.h>
#include <cmath>

float elemento::getAncho() const
{
    return ancho;
}

float elemento::getAlto() const
{
    return alto;
}

elemento::elemento(float posX_, float posY_, float velX_, float velY_, float masa_, float radio_, float K_, float e_, float ancho_, float alto_)
{
    PX = posX_; //pos en x
    PY = posY_; //pos en y
    mass = masa_; // masa del elemento
    R = radio_; //radio del elemento
    VX = velX_; //vel en x
    VY = velY_; //vel en y
    AX = 0; //acel en x
    AY = 0; //acel en y
    G = 9.81; //gravedad
    K = K_; //Resistencia del aire
    e = e_; //Coeficiente de restitucion
    V = 0; //vector de velocidad
    dt = 0.1; //delta tiempo
    ancho = ancho_;
    alto = alto_;
}

elemento::~elemento()
{

}

void elemento::actualizar_elemento()
{
    V = pow(((VX*VX)+(VY*VY)),(1/2));
    angulo = atan2(VY,VX);
    AX = -((K*(V*V)*(R*R))/mass)*cos(angulo);
    AY = (-((K*(V*V)*(R*R))/mass)*sin(angulo))-G;
    PX = PX + ((VX*(dt)))+(((AX*(dt*dt)))/2);
    PY = PY + ((VY*(dt)))+(((AY*(dt*dt)))/2);
    VX = VX + AX*dt;
    VY = VY + AY*dt;
}

float elemento::getV() const
{
    return V;
}

float elemento::getAX() const
{
    return AX;
}

float elemento::getAY() const
{
    return AY;
}


float elemento::getPY() const
{
    return PY;
}

float elemento::getMass() const
{
    return mass;
}

float elemento::getR() const
{
    return R;
}

float elemento::getVX() const
{
    return VX;
}

float elemento::getVY() const
{
    return VY;
}

float elemento::getE() const
{
    return e;
}

float elemento::getPX() const
{
    return PX;
}

void elemento::set_vel(float vx, float vy, float px, float py)
{
    VX = vx;
    VY = vy;
    PX = px;
    PY = py;
}
