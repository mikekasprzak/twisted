// - ------------------------------------------------------------------------------------------ - //
// Matrix1x3 //
// - ------------------------------------------------------------------------------------------ - //
#ifndef __Geometry_Matrix1x3_H__
#define __Geometry_Matrix1x3_H__
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#include "../Vector/Vector3D.h"
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Utility class for determining the vector multiplication type against a matrix //
// - ------------------------------------------------------------------------------------------ - //
class Matrix1x3: public Vector3D {
public:
	inline Matrix1x3() {
	}
	
	inline Matrix1x3( const Real& _x, const Real& _y, const Real& _z ) :
		Vector3D( _x, _y, _z )
	{
	}

	const Vector3D& ToVector3D() const {
		return (const Vector3D&)*this;
	}
};
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
// Define the function that converts to a Matrix //
// - ------------------------------------------------------------------------------------------ - //
const Matrix1x3& Vector3D::ToMatrix1x3() const {
	return (const Matrix1x3&)*this;
}
// - ------------------------------------------------------------------------------------------ - //

// - ------------------------------------------------------------------------------------------ - //
#endif // __Geometry_Matrix1x3_H__ //
// - ------------------------------------------------------------------------------------------ - //
