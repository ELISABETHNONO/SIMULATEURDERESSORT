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
        Vec2 operator+(const Vec2& other) const; 
        Vec2 operator-(const Vec2& other) const; 
        Vec2 operator*(float scalar) const; 
        Vec2 operator/(float scalar) const; 
    
        // Méthodes 
    float Length() const; 
    float Distance(const Vec2& other) const; 
    Vec2 Normalized() const; 
    float Dot(const Vec2& other) const; 

    void Set(float x, float y); 
    void Add(const Vec2& other); 
    void Scale(float scalar); 
}; 
#endif // VEC2_H