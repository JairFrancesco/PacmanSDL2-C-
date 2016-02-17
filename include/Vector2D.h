#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <math.h>

class Vector2D
{
    public:
        Vector2D(float x, float y):x(x), y(y){};
        Vector2D();
        float getX(){return x;}
        float getY(){return y;}
        void setX(float _x) {x=_x;}
        void setY(float _y) {y=_y;}
        float longitud() { return sqrt(x * x + y * y); }
        ~Vector2D();

        //Sobrecarga de operadores
        /*
        Vector2D v1(10, 11);
        Vector2D v2(35,25);
        v1 += v2;
        Vector2D v3 = v1 + v2;
        */

        //Adicion de dos vectores
        Vector2D operator+(const Vector2D& v2) const
        {
            return Vector2D(x+v2.x, y+v2.y);
        }

        friend Vector2D& operator+=(Vector2D& v1, const Vector2D& v2)
        {
            v1.x += v2.x;
            v1.y += v2.y;

            return v1;
        }

        //Vector por un escalar
        Vector2D operator*(float escalar)
        {
            return Vector2D(x*escalar, y*escalar);
        }

        Vector2D operator*=(float escalar)
        {
                x*=escalar;
                y*=escalar;

                return *this;
        }

        //Resta de dos vectores
        Vector2D operator-(const Vector2D& v2) const
        {
            return Vector2D(x-v2.x, y-v2.y);
        }

        friend Vector2D& operator-=(Vector2D& v1, const Vector2D& v2)
        {
            v1.x -= v2.x;
            v1.y -= v2.y;

            return v1;
        }

        //División por un escalar
        Vector2D operator/(float escalar)
        {
            return Vector2D(x/escalar, y/escalar);
        }

        Vector2D& operator/=(float escalar)
        {
            x /= escalar;
            y /= escalar;

            return *this;
        }

        void normalizar()
        {
            float l = longitud();
            if ( l > 0) // Nunca intentaremos dividir por 0
            {
            (*this) *= 1 / l;
            }
        }
    protected:
    private:
        float x;
        float y;
};

#endif // VECTOR2D_H
