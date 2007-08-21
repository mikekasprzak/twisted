// - ------------------------------------------------------------------------------------------ - //
#ifndef __PICKUP_H__
#define __PICKUP_H__
// - ------------------------------------------------------------------------------------------ - //
// Treasure (Pickup, unaffected by gravity)
// Key (Pickup, unaffected by gravity)
// Inverter (Pickup, inverts player gravity)
// - ------------------------------------------------------------------------------------------ - //
class cPickUp {
public:
	// We don't care about physics, we just are where we are //
	Vector2D Pos;
	
	// For collision, treat me as a sphere //
	Real Radius;
	
	// Is the Pickup active? //
	bool IsActive;
public:
	cPickUp( const Vector2D& _Pos ) :
		Pos( _Pos ),
		Radius( Real( 8 ) ),
		IsActive( true )
	{
		
	}
public:
	void Step() {
		// Animate //
	}
	
	void Draw( BITMAP* Target ) {
		// TODO: Use camera orientable draw code //
		if ( IsActive ) {
			circle( Target, (int)Pos.x, (int)Pos.y, (int)Radius, makecol( 128, 0, 255 ) );
		}
	}		
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PICKUP_H__
// - ------------------------------------------------------------------------------------------ - //
