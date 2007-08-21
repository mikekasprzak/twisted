// - ------------------------------------------------------------------------------------------ - //
// Vector4D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Vector4D_H__
#define __Geometry_Vector4D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <boost/operators.hpp>

#include "../Real.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_OPERATOR( _OP_ ) \
	inline const Vector4D& operator _OP_ ( const Vector4D& _Vs ) { \
		x _OP_ _Vs.x; \
		y _OP_ _Vs.y; \
		z _OP_ _Vs.z; \
		w _OP_ _Vs.w; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( _OP_ ) \
	inline const Vector4D& operator _OP_ ( const Real& _Vs ) { \
		x _OP_ _Vs; \
		y _OP_ _Vs; \
		z _OP_ _Vs; \
		w _OP_ _Vs; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// A two part Vector class //
// - ------------------------------------------------------------------------------------------ - //
class Vector4D : 
	boost::additive< Vector4D,
	boost::arithmetic2< Vector4D, Real
	> >
{
public:
	// - -------------------------------------------------------------------------------------- - //
	Real x, y, z, w;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular constants //
	// - -------------------------------------------------------------------------------------- - //
	static const Vector4D Identity;
	static const Vector4D Zero;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Constructors //
	// - -------------------------------------------------------------------------------------- - //
	inline Vector4D() {
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Vector4D( const Real& _x, const Real& _y, const Real& _z, const Real& _w ) :
		x( _x ),
		y( _y ),
		z( _z ),
		w( _w )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D& Set( const Real& _x, const Real& _y, const Real& _z, const Real& _w ) {
		x = _x;
		y = _y;
		z = _z;
		w = _w;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Overloaded Operators - The rest will be handled by Boost //
	// - -------------------------------------------------------------------------------------- - //
	// Vector //
	OVERLOAD_SYMBOLEQUALS_OPERATOR( += );
	OVERLOAD_SYMBOLEQUALS_OPERATOR( -= );
	// OVERLOAD_SYMBOLEQUALS_OPERATOR( *= );
	// OVERLOAD_SYMBOLEQUALS_OPERATOR( /= );
	// - -------------------------------------------------------------------------------------- - //
	// Dot Product //
	inline const Real operator * ( const Vector4D& _Vs ) const {
		return (x * _Vs.x) + (y * _Vs.y) + (z * _Vs.z) + (w * _Vs.w);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Cross product //
	// *note* this is the % sign because it is at the same level as the * and / signs, unlike the //
	//        ^ sign, which is at the binary logic level (OR, AND, XOR). //
//	inline const Vector4D operator % ( const Vector4D& _Vs ) const {
//		// This is actually wrong, but I don't know how to do a 4D cross //
//		return Vector4D(
//			(y * _Vs.z) - (z * _Vs.y),
//			(z * _Vs.x) - (x * _Vs.z),
//			(x * _Vs.y) - (y * _Vs.x),
//			);
//	}
	// - -------------------------------------------------------------------------------------- - //
	// Negate Operator //
	inline const Vector4D operator - ( ) const {
		return Vector4D( -x, -y, -z, -w );
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Scalar //
	OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( += );
	OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( -= );
	OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( *= );
	OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( /= );
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D& Normalize() {
		Real Mag( Magnitude() );
	
		if ( Mag.IsZeroPositive() )
			return Vector4D::Zero;
	
		return *this /= Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that returns the Magnitude after calculating the normalized vector //
	inline const Real NormalizeRet() {
		Real Mag( Magnitude() );
	
		if ( Mag.IsZeroPositive() )
			return Real::Zero;
	
		*this /= Mag;
		return Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation of Normalize that only returns the normal //
	inline const Vector4D Normal() const {
		Real Mag( Magnitude() );
	
		if ( Mag.IsZeroPositive() )
			return Vector4D::Zero;
		
		Vector4D Result( *this );
		Result /= Mag;
		
		return Result;
	}	
	// - -------------------------------------------------------------------------------------- - //
	// The length of a vector //
	inline const Real Magnitude() const {
		Real Mag( MagnitudeSquared() );
		Mag = Mag.Sqrt();
	
		if ( Mag.IsZeroPositive() )
			return Real::Zero;
		else
			return Mag;
	}
	// - -------------------------------------------------------------------------------------- - //
	// The squared length of a vector //
	inline const Real MagnitudeSquared() const {
		return (x * x) + (y * y) + (z * z) + (w * w);
	}
	// - -------------------------------------------------------------------------------------- - //
	// The sum of all absolute value parts //
	inline const Real Manhattan() const {
		return x.Abs() + y.Abs() + z.Abs() + w.Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Limiting Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D& MinClamp( const Vector4D& _Vs ) {
		if ( x < _Vs.x )
			x = _Vs.x;
		if ( y < _Vs.y )
			y = _Vs.y;
		if ( z < _Vs.z )
			z = _Vs.z;
		if ( w < _Vs.w )
			w = _Vs.w;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D& MaxClamp( const Vector4D& _Vs ) {
		if ( x > _Vs.x )
			x = _Vs.x;
		if ( y > _Vs.y )
			y = _Vs.y;
		if ( z > _Vs.z )
			z = _Vs.z;
		if ( w > _Vs.w )
			w = _Vs.w;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D& MinClamp( const Real& _x, const Real& _y, const Real& _z, const Real& _w ) {
		if ( x < _x )
			x = _x;
		if ( y < _y )
			y = _y;
		if ( z < _z )
			z = _z;
		if ( w < _w )
			w = _w;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D& MaxClamp( const Real& _x, const Real& _y, const Real& _z, const Real& _w ) {
		if ( x > _x )
			x = _x;
		if ( y > _y )
			y = _y;
		if ( z > _z )
			z = _z;
		if ( w > _w )
			w = _w;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D Min( const Vector4D& _Vs ) const {
		Vector4D Vec = *this;
		Vec.MinClamp( _Vs );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D Max( const Vector4D& _Vs ) const {
		Vector4D Vec = *this;
		Vec.MaxClamp( _Vs );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D Min( const Real& _x, const Real& _y, const Real& _z, const Real& _w ) const {
		Vector4D Vec = *this;
		Vec.MinClamp( _x, _y, _z, _w );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector4D Max( const Real& _x, const Real& _y, const Real& _z, const Real& _w ) const {
		Vector4D Vec = *this;
		Vec.MaxClamp( _x, _y, _z, _w );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
	// General Vector vs. Vector Angle Tests //
	// - -------------------------------------------------------------------------------------- - //
	// If it's an Acute angle between vectors, the dot will return a positive number //
	inline const bool IsAcuteAngle( const Vector4D& _Vs ) const {
		return ((*this) * _Vs) > Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If it's an obtuse angle between vectors, the dot will return a negative number //
	inline const bool IsObtuseAngle( const Vector4D& _Vs ) const {
		return ((*this) * _Vs) < Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If it's a 90 degree angle between vectors, the dot will return zero (or near zero) //
	inline const bool IsRightAngle( const Vector4D& _Vs ) const {
		return ((*this) * _Vs).IsZero();
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	inline const bool IsZero() const {
		return x.IsZero() && y.IsZero() && z.IsZero();
	}
	// - -------------------------------------------------------------------------------------- - //
	// Variation, that requires the guarentee that the number is positive. Used with magnitude. //
	inline const bool IsZeroPositive() const {
		return x.IsZeroPositive() && y.IsZeroPositive() && z.IsZeroPositive();
	}
	// - -------------------------------------------------------------------------------------- - //


	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Explicit Conversion Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const class Vector2D ToVector2D() const;
	inline const class Vector3D ToVector3D() const;
	
//	inline const class Matrix2x1& ToMatrix2x1();
//	inline const class Matrix1x2& ToMatrix1x2();
//	inline const class Matrix2x1& ToMatrix3x1();
//	inline const class Matrix1x2& ToMatrix1x3();
//	inline const class Matrix2x1& ToMatrix4x1();
//	inline const class Matrix1x2& ToMatrix1x4();
	
	inline const class ScalarVector4D& ToScalarVector() const;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Projection //
	// - -------------------------------------------------------------------------------------- - //
//	inline Vector4D ApplyMatrix( const class Matrix3x3& );
//	inline Vector4D ApplyMatrix( const class Matrix4x4& );
//	inline Vector4D ApplyMatrix( const class Matrix4x3& );
//	inline Vector4D ApplyMatrix( const class Matrix3x4& );
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// External Scalar Maths //
// - ------------------------------------------------------------------------------------------ - //
inline const Vector4D operator - ( const Real& a, const Vector4D& b ) {
	Vector4D Ret( a - b.x, a - b.y, a - b.z, a - b.w );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //
inline const Vector4D operator / ( const Real& a, const Vector4D& b ) {
	Vector4D Ret( a / b.x, a / b.y, a / b.z, a / b.w );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#undef OVERLOAD_SYMBOLEQUALS_OPERATOR
#undef OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Vector4D_H__ //
// - ------------------------------------------------------------------------------------------ - //
