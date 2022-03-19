#include "Vec3.h"

vec3::vec3(float x,float y, float z)
: x(x),y(y),z(z) {}

vec3::vec3(float n)
: vec3(n,n,n) {}

vec3::vec3()
: vec3(0) {}

void vec3::set(float newX, float newY, float newZ) {
x = newX;
y = newY;
z = newZ;
}

String vec3::toString() {
    const int DECIMAL_PLACES = 3;
    
    return 
        String(x, DECIMAL_PLACES) + ", " 
        + String(y, DECIMAL_PLACES) + ", " 
        + String(z, DECIMAL_PLACES);
}
