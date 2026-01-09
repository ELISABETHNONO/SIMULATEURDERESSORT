#ifndef MASS_H
#define MASS_H 

#include "../core/Vec2.h" 

class Mass {
private: 
    Vec2 mPosition; 
    Vec2 mVelocity; 
    Vec2 mAcceleration; 
    Vec2 mForceAccumulator; 
    
    float mMass; 
    float mRadius; 
    bool mIsFixed; 
    int mId;

public: 
    Mass(float mass = 1.0f, float radius = 20.0f, int id = 0); 

    // Getters 
    Vec2 GetPosition() const { return mPosition; } 
    Vec2 GetVelocity() const { return mVelocity; } 
    float GetMass() const { return mMass; } 
    float GetRadius() const { return mRadius; } 
    bool IsFixed() const { return mIsFixed; } 
    int GetId() const { return mId; } 

    // Setters 
    void SetPosition(const Vec2& position); 
    void SetVelocity(const Vec2& velocity); 
    void SetMass(float mass); 
    void SetFixed(bool fixed);

    // Physique 
    void ApplyForce(const Vec2& force); 
    void Integrate(float deltaTime); 
    void ClearForces(); 

    // Utilitaires 
    bool ContainsPoint(const Vec2& point, float tolerance = 5.0f) const; 
}; 

#endif // MASS_H