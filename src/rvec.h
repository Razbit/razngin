#ifndef RVEC
#define RVEC

#include <math.h>

/**
 * @file
 * @brief 2/3/4D vectors
 */

/**
 * @brief The rvec2 class defines a 2D vector
 */
class rvec2 {
public:
    double x;
    double y;

    rvec2(): x(0.0), y(0.0) {}
    rvec2(double _x, double _y): x(_x), y(_y) {}
    ~rvec2();

    /**
     * @brief Return the length of the vector
     */
    double len() {return sqrt(x*x + y*y);}

    /**
     * @brief Multiply the vector by n (scalar multiplication)
     */
    rvec2 mul(double n) {rvec2 ret; ret.x = n*x; ret.y = n*y; return ret;}

    /**
     * @brief Adds this vector to vector v
     */
    rvec2 add(rvec2 v) {rvec2 ret; ret.x = x + v.x; ret.y = y + v.y; return ret;}

    /**
     * @brief Dot product of this vector and the vector v
     */
    double dot(rvec2 v) {return x * v.x + y * v.y;}

    /**
     * @brief Set x,y
     */
    void set(double _x, double _y) {x = _x; y = _y;}
};

/**
 * @brief The rvec3 class defines a 3D vector
 */
class rvec3 {
public:
    double x;
    double y;
    double z;

    rvec3(): x(0.0), y(0.0), z(0.0) {}
    rvec3(double _x, double _y, double _z): x(_x), y(_y), z(_z) {}
    ~rvec3();

    /**
     * @brief Return the length of the vector
     */
    double len() {return sqrt(x*x + y*y + z*z);}

    /**
     * @brief Multiply the vector by n (scalar multiplication)
     */
    rvec3 mul(double n) {rvec3 ret; ret.x = n*x; ret.y = n*y; ret.z = n*z; return ret;}

    /**
     * @brief Adds this vector to vector v
     */
    rvec3 add(rvec3 v) {rvec3 ret; ret.x = x + v.x; ret.y = y + v.y; ret.z = z + v.z; return ret;}

    /**
     * @brief Dot product of this vector and the vector v
     */
    double dot(rvec3 v) {return x * v.x + y * v.y + z * v.z;}

    /**
     * @brief Cross product of this vector with the vector v
     */
    rvec3 cross(rvec3 v)
    {
        rvec3 ret;
        ret.x = y * v.z - z * v.y;
        ret.y = z * v.x - x * v.z;
        ret.z = x * v.y - y * v.x;
        return ret;
    }

    /**
     * @brief Set x,y,z
     */
    void set(double _x, double _y, double _z) {x = _x; y = _y; z = _z;}
};

/**
 * @brief The rvec4 class defines a 4D vector
 */
class rvec4 {
public:
    double x;
    double y;
    double z;
    double a;

    rvec4(): x(0.0), y(0.0), z(0.0), a(0.0) {}
    rvec4(double _x, double _y, double _z, double _a): x(_x), y(_y), z(_z), a(_a) {}
    ~rvec4();

    /**
     * @brief Return the length of the vector
     */
    double len() {return sqrt(x*x + y*y + z*z + a*a);}

    /**
     * @brief Multiply the vector by n (scalar multiplication)
     */
    rvec4 mul(double n) {rvec4 ret; ret.x = n*x; ret.y = n*y; ret.z = n*z; ret.a = n*a; return ret;}

    /**
     * @brief Adds this vector to vector v
     */
    rvec4 add(rvec4 v) {rvec4 ret; ret.x = x + v.x; ret.y = y + v.y; ret.z = z + v.z; ret.a = a + v.a; return ret;}

    /**
     * @brief Dot product of this vector and the vector v
     */
    double dot(rvec4 v) {return x * v.x + y * v.y + z * v.z + a * v.a;}

    /**
     * @brief Set x,y
     */
    void set(double _x, double _y, double _z, double _a) {x = _x; y = _y; z = _z, a = _a;}
};

#endif // RVEC

