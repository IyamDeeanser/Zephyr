// Class for storing 3-dimensional vectors
// todo convert vec3 to a template class
// ! if convert to template class, toString needs to be updated bc it expects input of float
// ! String lib may need to be included

#ifndef VEC3_h
#define VEC3_h

class vec3{
public:
  float x,y,z;

  vec3(float x,float y, float z);
  vec3(float n);
  vec3();

  void set(float newX, float newY, float newZ);

  String toString();
};

#endif
