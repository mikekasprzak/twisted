// - ------------------------------------------------------------------------------------------ - //
// Vector3D //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Vector3D_H__
#define __Geometry_Vector3D_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include <boost/operators.hpp>

#include "../Real.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_OPERATOR( _OP_ ) \
	inline const Vector3D& operator _OP_ ( const Vector3D& _Vs ) { \
		x _OP_ _Vs.x; \
		y _OP_ _Vs.y; \
		z _OP_ _Vs.z; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
#define OVERLOAD_SYMBOLEQUALS_REAL_OPERATOR( _OP_ ) \
	inline const Vector3D& operator _OP_ ( const Real& _Vs ) { \
		x _OP_ _Vs; \
		y _OP_ _Vs; \
		z _OP_ _Vs; \
		return *this; \
	}
// - ------------------------------------------------------------------------------------------ - //
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// A two part Vector class //
// - ------------------------------------------------------------------------------------------ - //
class Vector3D : 
	boost::additive< Vector3D,
	boost::arithmetic2< Vector3D, Real
	> >
{
public:
	// - -------------------------------------------------------------------------------------- - //
	Real x, y, z;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Regular constants //
	// - -------------------------------------------------------------------------------------- - //
	static const Vector3D Identity;
	static const Vector3D Zero;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
public:
	// - -------------------------------------------------------------------------------------- - //
	// Constructors //
	// - -------------------------------------------------------------------------------------- - //
	inline Vector3D() {
	}
	// - -------------------------------------------------------------------------------------- - //
	inline Vector3D( const Real& _x, const Real& _y, const Real& _z ) :
		x( _x ),
		y( _y ),
		z( _z )
	{
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D& Set( const Real& _x, const Real& _y, const Real& _z ) {
		x = _x;
		y = _y;
		z = _z;
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
	inline const Real operator * ( const Vector3D& _Vs ) const {
		return (x * _Vs.x) + (y * _Vs.y) + (z * _Vs.z);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Cross product //
	// *note* this is the % sign because it is at the same level as the * and / signs, unlike the //
	//        ^ sign, which is at the binary logic level (OR, AND, XOR). //
	inline const Vector3D operator % ( const Vector3D& _Vs ) const {
		return Vector3D(
			(y * _Vs.z) - (z * _Vs.y),
			(z * _Vs.x) - (x * _Vs.z),
			(x * _Vs.y) - (y * _Vs.x)
			);
	}
	// - -------------------------------------------------------------------------------------- - //
	// Negate Operator //
	inline const Vector3D operator - ( ) const {
		return Vector3D( -x, -y, -z );
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
	inline const Vector3D& Normalize() {
		Real Mag( Magnitude() );
	
		if ( Mag.IsZeroPositive() )
			return Vector3D::Zero;
	
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
	inline const Vector3D Normal() const {
		Real Mag( Magnitude() );
	
		if ( Mag.IsZeroPositive() )
			return Vector3D::Zero;
		
		Vector3D Result( *this );
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
		return (x * x) + (y * y) + (z * z);
	}
	// - -------------------------------------------------------------------------------------- - //
	// The sum of all absolute value parts //
	inline const Real Manhattan() const {
		return x.Abs() + y.Abs() + z.Abs();
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	// Limiting Functions //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D& MinClamp( const Vector3D& _Vs ) {
		if ( x < _Vs.x )
			x = _Vs.x;
		if ( y < _Vs.y )
			y = _Vs.y;
		if ( z < _Vs.z )
			z = _Vs.z;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D& MaxClamp( const Vector3D& _Vs ) {
		if ( x > _Vs.x )
			x = _Vs.x;
		if ( y > _Vs.y )
			y = _Vs.y;
		if ( z > _Vs.z )
			z = _Vs.z;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D& MinClamp( const Real& _x, const Real& _y, const Real& _z ) {
		if ( x < _x )
			x = _x;
		if ( y < _y )
			y = _y;
		if ( z < _z )
			z = _z;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D& MaxClamp( const Real& _x, const Real& _y, const Real& _z ) {
		if ( x > _x )
			x = _x;
		if ( y > _y )
			y = _y;
		if ( z > _z )
			z = _z;
		return *this;
	}
	// - -------------------------------------------------------------------------------------- - //
	
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D Min( const Vector3D& _Vs ) const {
		Vector3D Vec = *this;
		Vec.MinClamp( _Vs );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D Max( const Vector3D& _Vs ) const {
		Vector3D Vec = *this;
		Vec.MaxClamp( _Vs );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D Min( const Real& _x, const Real& _y, const Real& _z ) const {
		Vector3D Vec = *this;
		Vec.MinClamp( _x, _y, _z );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D Max( const Real& _x, const Real& _y, const Real& _z ) const {
		Vector3D Vec = *this;
		Vec.MaxClamp( _x, _y, _z );
		return Vec;
	}
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// General Vector vs. Vector Angle Tests //
	// - -------------------------------------------------------------------------------------- - //
	// If it's an Acute angle between vectors, the dot will return a positive number //
	inline const bool IsAcuteAngle( const Vector3D& _Vs ) const {
		return ((*this) * _Vs) > Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If it's an obtuse angle between vectors, the dot will return a negative number //
	inline const bool IsObtuseAngle( const Vector3D& _Vs ) const {
		return ((*this) * _Vs) < Real::Zero;
	}
	// - -------------------------------------------------------------------------------------- - //
	// If it's a 90 degree angle between vectors, the dot will return zero (or near zero) //
	inline const bool IsRightAngle( const Vector3D& _Vs ) const {
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
	inline const class Vector4D ToVector4D() const;
	inline const class Vector4D ToHomoVector4D() const;
	
//	inline const class Matrix2x1& ToMatrix2x1() const;
//	inline const class Matrix1x2& ToMatrix1x2() const;
	inline const class Matrix3x1& ToMatrix3x1() const;
	inline const class Matrix1x3& ToMatrix1x3() const;
//	inline const class Matrix4x1& ToMatrix4x1() const;
//	inline const class Matrix1x4& ToMatrix1x4() const;
	
	inline const class ScalarVector3D& ToScalarVector() const;
	// - -------------------------------------------------------------------------------------- - //

	// - -------------------------------------------------------------------------------------- - //
	// Projection //
	// - -------------------------------------------------------------------------------------- - //
	inline const Vector3D ApplyMatrix( const class Matrix3x3& ) const;
//	inline const Vector3D ApplyMatrix( const class Matrix4x4& ) const;
//	inline const Vector3D ApplyMatrix( const class Matrix4x3& ) const;
//	inline const Vector3D ApplyMatrix( const class Matrix3x4& ) const;
	// - -------------------------------------------------------------------------------------- - //
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// External Scalar Maths //
// - ------------------------------------------------------------------------------------------ - //
inline const Vector3D operator - ( const Real& a, const Vector3D& b ) {
	Vector3D Ret( a - b.x, a - b.y, a - b.z );
	return Ret;
}
// -- ---------------------------------------------------------------------------------------- -- //
inline const Vector3D operator / ( const Real& a, const Vector3D& b ) {
	Vector3D Ret( a / b.x, a / b.y, a / b.z );
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
#endif // __Geometry_Vector3D_H__ //
// - ------------------------------------------------------------------------------------------ - //
