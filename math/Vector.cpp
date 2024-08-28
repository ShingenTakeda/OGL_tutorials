#include <cfloat>
#include <cmath>
#include "LMDefs.hpp"
#include "Vector.hpp"

//Vector2
void add( Vector2 &a, const Vector2 &b)
{
  a.x += b.x;
  a.y += b.y;
}

void sub(Vector2 &a, const Vector2 &b)
{
  a.x -= b.x;
  a.y -= b.y;
}

void scale(Vector2 &v, const float n)
{
  v.x *= n;
  v.y *= n;
}

void rotate(Vector2 &v ,const float angle)
{
  v.x = v.x * cos(angle) - v.y * sin(angle);
  v.y = v.y * cos(angle) + v.x * sin(angle);
}

float angle(const Vector2 &a, const Vector2 &b)
{
  float m = sqrtf(magnitude_sqr(a) * magnitude_sqr(b));
  return acos(dot(a, b) / m);
}

float magnitude(const Vector2 &v)
{
  float len_sqr = v.x * v.x + v.y * v.y;
  if(len_sqr < FLT_EPSILON)
  {
    return 0.0f;
  }

  return sqrtf(len_sqr);
}

float magnitude_sqr(const Vector2 &v)
{
  return v.x * v.x + v.y * v.y;
}

void normalize(Vector2 &v)
{
  v = v * (1.0f / magnitude(v));
}

Vector2 normal(const Vector2 &v)
{
  return v * (1.0f / magnitude(v));
}

Vector2 unit_vector(const Vector2 &v)
{
  Vector2 result;
  float mag = magnitude(v);

  if(mag != 0.0f)
  {
    result = v / mag;
  }
  
  return result;
}

float dot(const Vector2 &a, const Vector2 &b)
{
  return a.x * b.x + a.y * b.y;
}

float cross(const Vector2 &a , const Vector2 &b)
{
  return ((a.x * b.x) - (a.y * b.y));
}

Vector2 project(const Vector2 &length, const Vector2 &direction)
{
  float magBsq = magnitude(direction);
  if(magBsq < FLT_EPSILON)
  {
    return Vector2();
  }

  float scale = dot(length, direction) / magBsq;
  return direction * scale;
}

Vector2 perpendicular(const Vector2 &length, const Vector2 &direction)
{
  return length - project(length, direction);
}

Vector2 reflection(const Vector2 &v, const Vector2 &normal)
{
  float magBsq = magnitude(normal);
  if(magBsq < FLT_EPSILON)
  {
    return 0;
  }

  float scale = dot(v, normal) / magBsq;
  Vector2 proj = normal * (scale * 2);
  return  v - normal;
}

bool operator == (const Vector2 &a, const Vector2 &b)
{
  Vector2 v(a - b);
  return magnitude_sqr(v);
}

bool operator != (const Vector2 &a, const Vector2 &b)
{
  return !(a == b);
}

Vector2 operator + (const Vector2 &a, const Vector2 &b)
{
  return {a.x + b.x, a.y + b.y};
}

Vector2 operator - (const Vector2 &a, const Vector2 &b)
{
  return {a.x - b.x, a.y - b.y};
}

Vector2 operator * (const Vector2 &a, const Vector2 &b)
{
  return {a.x * b.x, a.y * b.y};
}

Vector2 operator * (const Vector2 &v, float r)
{
  return {v.x * r, v.y *r};
}

Vector2 operator / (const Vector2 &a, const Vector2 &b)
{
  return {a.x / b.x, a.y / b.y};
}

Vector2 operator / (const Vector2 &a, float r)
{
  return {a.x / r, a.y / r};
}

Vector2 operator - (const Vector2 &v)
{
  return {v.x * -1, v.y * -1};
}

//Vector3
void add(Vector3 &a, const Vector3 &b)
{
  a.x += b.x;
  a.y += b.y;
  a.z += b.z;
}

void sub(Vector3 &a, const Vector3 &b)
{
  a.x -= b.x;
  a.y -= b.y;
  a.z -= b.z;
}

void scale(Vector3 &v, const float n)
{
  v.x *= n;
  v.y *= n;
  v.z *= n;
}


//TODO: rotate it with a matrix(quaternions and the such)
/*
void rotate(Vector3 &v ,const float angle)
{
  
}
*/

float angle(const Vector3 &a, const Vector3 &b)
{
  float sqMagL = a.x * a.x + a.y * a.y + a.z * a.z;
  float sqMagR = b.x * b.x + b.y * b.y + b.z * b.z;
  if (sqMagL < FLT_EPSILON || sqMagR < FLT_EPSILON) 
  {
    return 0.0f;
  }
  float dot = a.x * b.x + a.y * b.y + a.z * b.z;
  float len = sqrtf(sqMagL) * sqrtf(sqMagR);
  return acosf(dot / len);
}
float magnitude(const Vector3 &v)
{
  float len_sqr = v.x * v.x + v.y * v.y + v.z * v.z;
  if(len_sqr < FLT_EPSILON)
  {
    return 0.0f;
  }

  return sqrtf(len_sqr);
}

float magnitude_sqr(const Vector3 &v)
{
  return v.x * v.x + v.y * v.y + v.z * v.z;
}

void normalize(Vector3 &v)
{
  float len_sqr = v.x * v.x + v.y * v.y + v.z * v.z;
  if(len_sqr < FLT_EPSILON)
  {
    return ;
  }
  
  float inv_len = 1.0f / sqrtf(len_sqr);

  v.x *= inv_len;
  v.y *= inv_len;
  v.z *= inv_len;
}

Vector3 normal(const Vector3 &v)
{
  float len_sqr = v.x * v.x + v.y * v.y + v.z * v.z;
  if(len_sqr < FLT_EPSILON)
  {
    return v;
  }
  
  float inv_len = 1.0f / sqrtf(len_sqr);
  
  return Vector3(
  v.x * inv_len,
  v.y * inv_len,
  v.z * inv_len);
}

Vector3 unit_vector(const Vector3 &v)
{
  Vector3 result;
  float mag = magnitude(v);

  if(mag != 0.0f)
  {
    result = v / mag;
  }
  
  return result;
}

float dot(const Vector3 &a, const Vector3 &b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector3 cross(const Vector3 &a, const Vector3 &b)
{
  return Vector3(
      a.y * b.z - a.z * b.y,
      a.z * b.x - a.x * b.z,
      a.x * b.y - a.y * b.x
);
}

Vector3 project(const Vector3 &length, const Vector3 &direction)
{
  
}

Vector3 perpendicular(const Vector3 &lenth, const Vector3 &direction)
{

}

Vector3 reflection(const Vector3 &v, const Vector3 &normal)
{

}

bool operator == (const Vector3 &a, const Vector3 &b)
{
  Vector3 v(a - b);
  return magnitude_sqr(v);
}

bool operator != (const Vector3 &a, const Vector3 &b)
{
  return !(a == b);
}

Vector3 operator + (const Vector3 &a, const Vector3 &b)
{
  return {a.x + b.x, a.y + b.y, a.z + b.z};
}

Vector3 operator - (const Vector3 &a, const Vector3 &b)
{
  return {a.x - b.x, a.y - b.y, a.z - b.z};
}

Vector3 operator * (const Vector3 &a, const Vector3 &b)
{
  return {a.x * b.x, a.y * b.y, a.z * b.z};
}

Vector3 operator * (const Vector3 &v, float r)
{
  return {v.x * r, v.y * r, v.z * r};
}

Vector3 operator / (const Vector3 &a, const Vector3 &b)
{
  return {a.x / b.x, a.y / b.y, a.z / b.z};
}

Vector3 operator / (const Vector3 &a, float r)
{
  return {a.x / r, a.y / r, a.z / r};
}

Vector3 operator - (const Vector3 &v)
{
  return {v.x * -1.0f, v.y * -1.0f, v.z * -1.0f};
}
