#ifndef VEC3H
#define VEC3H

#include<math.h>
#include<stdlib.h>
#include<iostream>

class Vec3 {
public:
    Vec3() {}
    Vec3(float x, float y, float z) { v[0] = x; v[1] = y; v[2] = z; }

    // Geometric getters
    inline float x() const { return v[0]; }
    inline float y() const { return v[1]; }
    inline float z() const { return v[2]; }

    // RGB getters
    inline float r() const { return v[0]; }
    inline float g() const { return v[1]; }
    inline float b() const { return v[2]; }

    // arithmetic/indexing operators
    inline const Vec3& operator+() const { return *this; }
    inline Vec3 operator-() const { return Vec3(-v[0], -v[1], -v[2]); }
    inline float operator[](int i) const { return v[i]; }
    inline float& operator[](int i) { return v[i]; }

    // I/O
    friend std::istream& operator>>(std::istream &is, Vec3 &t) {
        is >> t.v[0] >> t.v[1] >> t.v[2];
        return is;
    }

    friend std::ostream& operator<<(std::ostream &os, const Vec3 &t) {
        os << t.v[0] << " " <<  t.v[1] << " " << t.v[2];
        return os;
    }

    // Arithmetic operators
    friend Vec3 operator+(const Vec3 &v1, const Vec3 &v2) {
        return Vec3(
            v1.v[0] + v2.v[0],
            v1.v[1] + v2.v[1],
            v1.v[2] + v2.v[2]
        );
    }

    friend Vec3 operator-(const Vec3 &v1, const Vec3 &v2) {
        return Vec3(
            v1.v[0] - v2.v[0],
            v1.v[1] - v2.v[1],
            v1.v[2] - v2.v[2]
        );
    }

    friend Vec3 operator*(const Vec3 &v1, const Vec3 &v2) {
        return Vec3(
            v1.v[0] * v2.v[0],
            v1.v[1] * v2.v[1],
            v1.v[2] * v2.v[2]
        );
    }

    friend Vec3 operator/(const Vec3 &v1, const Vec3 &v2) {
        return Vec3(
            v1.v[0] / v2.v[0],
            v1.v[1] / v2.v[1],
            v1.v[2] / v2.v[2]
        );
    }

    friend Vec3 operator*(float f, const Vec3 &v) {
        return Vec3(f * v.v[0], f * v.v[1], f * v.v[2]);
    }

    friend Vec3 operator/(const Vec3 v, float f) {
        return Vec3(v.v[0] / f, v.v[1] / f, v.v[2] / f);
    }

    friend Vec3 operator*(const Vec3 &v, float f) {
        return Vec3(f * v.v[0], f * v.v[1], f * v.v[2]);
    }

    inline Vec3& operator+=(const Vec3 &v1) {
        v[0] += v1.v[0];
        v[1] += v1.v[1];
        v[2] += v1.v[2];
        return *this;
    }

    inline Vec3& operator-=(const Vec3 &v1) {
        v[0] -= v1.v[0];
        v[1] -= v1.v[1];
        v[2] -= v1.v[2];
        return *this;
    }

    inline Vec3& operator*=(const Vec3 &v1) {
        v[0] *= v1.v[0];
        v[1] *= v1.v[1];
        v[2] *= v1.v[2];
        return *this;
    }

    inline Vec3& operator/=(const Vec3 &v1) {
        v[0] /= v1.v[0];
        v[1] /= v1.v[1];
        v[2] /= v1.v[2];
        return *this;
    }
    
    inline Vec3& operator*=(float f) {
        v[0] *= f;
        v[1] *= f;
        v[2] *= f;
        return *this;
    }

    inline Vec3& operator/=(float f) {
        float k = 1.0/f;
        
        v[0] *= k;
        v[1] *= k;
        v[2] *= k;
        return *this;
    }

    // Vector-specific operations
    inline float length() const {
        return sqrt(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
    }

    inline float length_squared() const {
        return v[0]*v[0] + v[1]*v[1] + v[2]*v[2];
    }

    inline void normalize() {
        float k = 1.0 / length();
        v[0] *= k;
        v[1] *= k;
        v[2] *= k;
    }

    inline Vec3 normalized() {
        float k = 1.0 / length();
        return Vec3(v[0] *= k, v[1] *= k, v[2] *= k);
    }

    static Vec3 normalized(const Vec3& v1) {
        return v1 / v1.length();
    }

    static float dot(const Vec3 &v1, const Vec3 &v2) {
        return v1.v[0] * v2.v[0] + v1.v[1] * v2.v[1] + v1.v[2] * v2.v[2];
    }

    static Vec3 cross(const Vec3 &v1, const Vec3 &v2) {
        return Vec3(
            (v1.v[1] * v2.v[2] - v1.v[2] * v2.v[1]),
            (-(v1.v[0] * v2.v[2] - v1.v[2] * v2.v[0])),
            (v1.v[0] * v2.v[1] - v1.v[1] * v2.v[0])
        );
    }

private:
    float v[3];
};

#endif