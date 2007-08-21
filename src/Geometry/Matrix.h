// - ------------------------------------------------------------------------------------------ - //
// Matrix //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Matrix_H__
#define __Geometry_Matrix_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "Matrix/Matrix1x2.h"
#include "Matrix/Matrix2x1.h"
#include "Matrix/Matrix2x2.h"
#include "Matrix/Matrix3x3.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// The rule for matrix multiplication is the Width of A must be equal to the Height of B!! //
// The book lists this as the other way around, since they read co-ordinates differently!! //
// [ 0 1 ] //
// [ 2 3 ] //
// - ------------------------------------------------------------------------------------------ - //
inline const Matrix1x2 operator * ( const Matrix2x2& _a, const Matrix1x2& _b ) {
	Matrix1x2 Temp;
	Temp.x = (_a.Array[ 0 ] * _b.x) + (_a.Array[ 1 ] * _b.y);
	Temp.y = (_a.Array[ 2 ] * _b.x) + (_a.Array[ 3 ] * _b.y);
	return Temp;	
}
// - ------------------------------------------------------------------------------------------ - //
inline const Matrix2x1 operator * ( const Matrix2x1& _a, const Matrix2x2& _b ) {
	Matrix2x1 Temp;
	Temp.x = (_a.x * _b.Array[ 0 ]) + (_a.y * _b.Array[ 2 ]);
	Temp.y = (_a.x * _b.Array[ 1 ]) + (_a.y * _b.Array[ 3 ]);
	return Temp;		
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Apply a matrix transformation to a vector //
// - ------------------------------------------------------------------------------------------ - //
inline const Vector2D Vector2D::ApplyMatrix( const Matrix2x2& _Vs ) {
	Vector2D Temp;
	Temp = (this->ToMatrix2x1() * _Vs).ToVector2D();
	return Temp;
}
// - ------------------------------------------------------------------------------------------ - //
//inline const Vector2D Vector2D::ApplyMatrix( const Matrix3x3& _Vs ) {
//	Vector2D Temp;
//	Temp = (this->ToMatrix3x1() * _Vs).ToVector2D();
//	return Temp;
//}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Matrix_H__ //
// - ------------------------------------------------------------------------------------------ - //
