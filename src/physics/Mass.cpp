#ifndef MASS_H
#define MASS_H 

#include "../core/Vec2.h" 

class Mass {
private: 
    Vec2 mPosition; 
    Vec2 mVelocity; // la vitesse
    Vec2 mAcceleration; 
    Vec2 mForceAccumulator; 
    
    float mMass; 
    float mRadius; //rayon 
    bool mIsFixed; // la mobilité d'un objet prend la valeur vraie ou fausse 
    int mId; // pour distinguer les masses 

public: 
    Mass(float mass = 1.0f, float radius = 20.0f, int id = 0) {
        
        mId(id),
        mMass(mass),
        mRadius(radius),
        mIsFixed(false),
        mPosition{0, 0},
        mVelocity{0, 0},
        mForceAccumulator{0, 0}
    {}
};


    // Getters 
    // Vec2 GetPosition() const { return mPosition; } 
        vec2 Mass::Getposition(){  // permet d'accéder à la position de l'objet 
            return mPosition;
        }

    // Vec2 GetVelocity() const { return mVelocity; } 
        vec2 Mass::GetVelocity() const{
            return mVelocity;
        }

    //float GetMass() const { return mMass; } 
        float Mass::GetMass() const {
            return mMass;
        }

    //float GetRadius() const { return mRadius; } 
        float  Mass::GetRadius() const {
            return mRadius;
        }

    //bool IsFixed() const { return mIsFixed; } 
        bool Mass:: IsFixed () const{
            return mIsFixed;
        }

   // int GetId() const { return mId; } 
        int Mass::GetId() const{
            return mId;
        }
    // Setters 
    //void SetPosition(const Vec2& position); permet de modifier la position de la masse
        void Mass::SetPosition ( const vec2& position) {
            mPosition=position;
        }

    //void SetVelocity(const Vec2& velocity); pour modifier la vitesse 
        void Mass::SetVelocity ( const vec2& velocity) {
            mVelocity= velocity;
        }
    //void SetMass(float mass); 
        void Mass::SetMass ( const vec2& Mass){ // on s'assure que la masse est positive pour eviter la division par zero 
            mMass= std::mass( mass, o.0001f);
        }
    //void SetFixed(bool fixed);
        void Mass::SetFixed( bool fixed) {
            mIsFixed= fixed;
        }

    // Physique 
   
   // void ApplyForce(const Vec2& force); 
        void Mass::ApplyForce( const Vec2& force) {
            if ( ! mIsFixed){       //on n'applique pas de force si la masse est fixe
                mForceAccumulator.Add( force);      // ajoute la force à l'accumulateur
            } 
        }

    //void Integrate(float deltaTime);  pour mettre à jours la vitesse et la position de l'objet en utilisant toutes les forces accumulées
        void Mass::Integrate ( float deltaTime){
            
            if( mIsFixed) return;           //si la masse est fixe on ne fait rien
            vec2 acceleration =mForceAccumulator/mMass;   // calcul de l'accélération a=F/m
            mVelocity.Add (acceleration*deltaTime) ;        // mis à jour de la vitesse 
            mPosition.Add (mVelocity*deltaTime) ;           // mis à jour de la position
            mForceAccumulator= vec2 ( 0.0f, 0.0f);          // réinitialiser l'accumulateur
            
        }
    
    //void ClearForces();  remet toutres les forces à zéro
        void Mass::ClearForces() {
            mForceAccumulator = Vec2 ( 0.0f, 0.0f) ;
        }

    // Utilitaires 
    //bool ContainsPoint(const Vec2& point, float tolerance = 5.0f) const; 
        bool Mass::containsPoint ( const Vec2& point, float tolerance) const{
            float distance = mPosition.Distance (point);      //  calcule la distance entre le point et la position de la masse 
            ruturn distance <= ( mRadius + tolerance);          // pour verifier que le point est danbs le cercle
        }

};

#endif // MASS_H