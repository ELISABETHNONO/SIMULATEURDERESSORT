#include <stdexcept>
#include < cmath>

#ifndef VEC2_H

#define VEC2_H 

class Vec2 {
public: 
    float x; 
    float y; 

        // Constructeurs 
        Vec2(); 
        Vec2(float x, float y); 
        
            // Opérateurs 
        Vec2 operator+(const Vec2& other) const{  // l'addition de 2 vecteurs 
            return vec2( x+= other.x ; y+= other.y) ; 
         }
        Vec2 operator-(const Vec2& other) const{ 
            return vec2( x-= other.x ; y-= other.y); // other.x et other.y sont les cordonnées d'un autre vecteur
         }
        Vec2 operator*(float scalar) const { 
            return vec2( x*scalar; y*scalar);
         }
        Vec2 operator/(float scalar) const{ 
            if ( scalar == 0.0f) { 
                throw std::runtime_error(" la division par zèro dans vec2 est impossible")
            }
   
            return( x/scalar; y/scalar) ;
         }
            // Méthodes

        float Length() const{ 
            return std::sqrt( x*x + y*y) ; // pour calculer la norme d'un vecteur
        } 
        
        float Distance(const Vec2& other) const; { // distance entre deux vecteurs 
            float dx= x-other.x; // sachant de x et other.x sont respectivement les abscisses de A et B
            float dy= y-other.y; // sachant de y et other.y sont respectivement les ordonées de A et B
            return sqrt ( dx*dx + dy*dy) ; // la distance de A et B est le racine carré de la somme des différences des coordonnées 
        }
        
        Vec2 Normalized() const { // v^=v^ diviser par la norme du vecteur 
​
            float len = Length( ); // norme du vecteur 
            
            cont float EPSILON = 1e-6f; 
            if ( len < EPSILON){ 
                throw std::runtime_error("impossible de normaliser un vecteur de longueur quasi nulle "); 
                // on fait normalized pour avoir un vecteur de longueur 1 cad vecteur unitaire ceci afin de faciliter les deplacements des vecteurs en gardant la meme directiion
            }
                return vec2 ( x/len, y/len);
        }
        
    
        float Dot(const Vec2& other) const{ 
            // pour le produit scalaire de deux vecteurs a.b= x1.x2 + y1.y2
            return( x*other.x + y*other.y); // pour le produit scalaire on multiple les abscisses et les ordonnees entre eux et on additionne 
        } 

        void Set(float x, float y){ 
            // permet de modifier les valeurs de façon propre,claire et controlée 
            this->x = x;
            this->y = y;
        }
        void Add(const Vec2& other){
            x+= other.x; // equivaut à x=x+other.x
            y+= other.y; // equivaut à y=y+other.y
        }
        
        void Scale(float scalar){ 
            // scalar est un facteur de multiplication 
            x*= other.x ;
            y*= other.y;
        }
}; 
#endif // VEC2_H