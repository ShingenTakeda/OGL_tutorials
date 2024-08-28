#pragma once

template <typename T>
struct TVec2
{
  union
  {
    struct
    {
      T x;
      T y;
    };

    T v[2];
  };

  inline TVec2() : x(T(0)), y(T(0)) {}
  inline TVec2(T _x, T _y) : x(_x), y(_y) {}
  inline TVec2(T *fv) : x(fv[0]), y(fv[1]) {}
};

template <typename T>
struct TVec3
{
  union
  {
    struct
    {
      T x;
      T y;
      T z;
    };

    T v[3];
  };

  inline TVec3() : x(T(0)), y(T(0)), z(T(0)) {}
  inline TVec3(T _x, T _y, T _z) : x(_x), y(_y), z(_z) {}
  inline TVec3(T *fv) : x(fv[0]), y(fv[1]), z(fv[2]) {}
};

template <typename T>
struct TVec4
{
  union
  {
    struct
    {
      T x;
      T y;
      T z;
      T w;
    };

    T v[4];
  };

  inline TVec4() : x(T(0)), y(T(0)), z(T(0)), w(T(0)) {}
  inline TVec4(T _x, T _y, T _z, T _w) : x(_x), y(_y), z(_z), w(_w) {}
  inline TVec4(T *fv) : x(fv[0]), y(fv[1]), z(fv[2]), w(fv[3]) {}
};

//Definition of Vectors
typedef TVec2<int> IVector2;
typedef TVec2<float> Vector2;
typedef TVec3<int> IVector3;
typedef TVec3<float> Vector3;
typedef TVec4<int> IVector4;
typedef TVec4<float> Vector4;

//Vector functions

//Vector2
void add(Vector2 &a, const Vector2 &b);
void sub(Vector2 &a, const Vector2 &b);
void scale(Vector2 &v, const float n);
void rotate(Vector2 &v ,const float angle);

float angle(const Vector2 &a, const Vector2 &b);

float magnitude(const Vector2 &v);
float magnitude_sqr(const Vector2 &v);

void normalize(Vector2 &v);
Vector2 normal(const Vector2 &v);
Vector2 unit_vector(const Vector2 &v);

float dot(const Vector2 &a, const Vector2 &b);
float cross(const Vector2 &a, const Vector2 &b);

Vector2 project(const Vector2 &length, const Vector2 &direction);
Vector2 perpendicular(const Vector2 &lenth, const Vector2 &direction);

Vector2 reflection(const Vector2 &v, const Vector2 &normal);

bool operator == (const Vector2 &a, const Vector2 &b);
bool operator != (const Vector2 &a, const Vector2 &b);

Vector2 operator + (const Vector2 &a, const Vector2 &b);
Vector2 operator - (const Vector2 &a, const Vector2 &b);
Vector2 operator * (const Vector2 &a, const Vector2 &b);
Vector2 operator * (const Vector2 &v, float r);
Vector2 operator / (const Vector2 &a, const Vector2 &b);
Vector2 operator / (const Vector2 &a, float r);
Vector2 operator - (const Vector2 &v);

Vector2& operator += (const Vector2 &a, const Vector2 &b);
Vector2& operator -= (const Vector2 &a, const Vector2 &b);
Vector2& operator *= (const Vector2 &a, const Vector2 &b);
Vector2& operator /= (const Vector2 &a, const Vector2 &b);

//Vector3
void add(Vector3 &a, const Vector3 &b);
void sub(Vector3 &a, const Vector3 &b);
void scale(Vector3 &v, const float n);
void rotate(Vector3 &v ,const float angle);

float angle(const Vector3 &a, const Vector3 &b);

float magnitude(const Vector3 &v);
float magnitude_sqr(const Vector3 &v);

void normalize(Vector3 &v);
Vector3 normal(const Vector3 &v);
Vector3 unit_vector(const Vector3 &v);

float dot(const Vector3 &a, const Vector3 &b);
Vector3 cross(const Vector3 &a, const Vector3 &b);

Vector3 project(const Vector3 &length, const Vector3 &direction);
Vector3 perpendicular(const Vector3 &length, const Vector3 &direction);

Vector3 reflection(const Vector3 &v, const Vector3 &normal);

bool operator == (const Vector3 &a, const Vector3 &b);
bool operator != (const Vector3 &a, const Vector3 &b);

Vector3 operator + (const Vector3 &a, const Vector3 &b);
Vector3 operator - (const Vector3 &a, const Vector3 &b);
Vector3 operator * (const Vector3 &a, const Vector3 &b);
Vector3 operator * (const Vector3 &v, float r);
Vector3 operator / (const Vector3 &a, const Vector3 &b);
Vector3 operator / (const Vector3 &a, float r);
Vector3 operator - (const Vector3 &v);

Vector3& operator += (const Vector3 &a, const Vector3 &b);
Vector3& operator -= (const Vector3 &a, const Vector3 &b);
Vector3& operator *= (const Vector3 &a, const Vector3 &b);
Vector3& operator /= (const Vector3 &a, const Vector3 &b);
