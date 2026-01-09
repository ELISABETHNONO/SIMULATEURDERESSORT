#ifndef SPRING_H
#define SPRING_H 

#include "../core/Vec2.h" 

class Mass; 
class Spring {
private: 
    Mass* mMass1; 
    Mass* mMass2;

    float mStiffness;    // k [N/m]   
    float mRestLength;    // L0 [m]  
    float mDamping;      // c [N·s/m]   
    int mId; 

public: 
    Spring(Mass* mass1, Mass* mass2, float stiffness = 100.0f,
        float restLength = 100.0f, float damping = 0.5f, int id = 0); 

        // Getters 
    Mass* GetMass1() const { return mMass1; } 
    Mass* GetMass2() const { return mMass2; } 
    float GetStiffness() const { return mStiffness; } 
    float GetRestLength() const { return mRestLength; } 
    float GetDamping() const { return mDamping; } 
    int GetId() const { return mId; } 

    // Setters 
    void SetStiffness(float stiffness); 
    void SetRestLength(float length); 
    void SetDamping(float damping); 

    // Physique 
    Vec2 ComputeForceOnMass1() const; 
    Vec2 ComputeForceOnMass2() const; 
    float GetCurrentLength() const; 
    float GetTensionRatio() const; // -1 (compressé) à 1 (étiré) 
};
 
#endif // SPRING_H