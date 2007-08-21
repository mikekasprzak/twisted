// - ------------------------------------------------------------------------------------------ - //
#ifndef __BLOCK_H__
#define __BLOCK_H__
// - ------------------------------------------------------------------------------------------ - //
// Contact Tracking //
vector< Rect2D > Contact;
// TODO: give each contact a lifetime, of a few seconds //
// - ------------------------------------------------------------------------------------------ - //
// Wall (Rectangle, optionally dynamic unaffected by anything)
// Shifting Wall (Rectangle, a wall that moves via gravity, unaffected by the character)
// Pushable Wall (Rectangle, A shifting wall with a 50% solve vs character)
// TODO: Death Block/Spikes
// TODO: Doors
// - ------------------------------------------------------------------------------------------ - //
class cBlock {
public:
	// Center //
	Vector2D Pos, Old, Home;
	
	// Rectangles (made up of many, for more complex shapes) //
	vector<	Rect2D > Rect;
	
	// ID if this is a key disabling block //
	int KeyID;
	
	// Is the block active (locked)? //
	bool IsActive;
	
	// Does Gravity move me? //
	bool IsSolid;
	
	// Is this block pushable by the character //
	bool IsPushable;
	
	// Can this block be climbed (i.e. change orientation on)? //
	bool IsClimbable;
	
	// What sort of entities can collide with me? //
	bool IsBlockCollision;
	bool IsPlayerCollision;
public:
	cBlock( const Vector2D& _Pos = Vector2D::Zero, const bool& _IsSolid = false, const bool& _IsPushable = true, const bool& _IsClimbable = true, const bool& _IsBlockCollision = true, const bool& _IsPlayerCollision = true ) :
		Pos( _Pos ),
		Old( _Pos ),
		Home( _Pos ),
		KeyID( 0 ),
		IsActive( true ),
		IsSolid( _IsSolid ),
		IsPushable( _IsPushable ),
		IsClimbable( _IsClimbable ),
		IsBlockCollision( _IsBlockCollision ),
		IsPlayerCollision( _IsPlayerCollision )
	{
	}
public:
	void Reset() {
		Pos = Home;
		Old = Home;
		IsActive = true;
	}
	
	void Step( const Vector2D& GravityVector ) {
		if ( !IsSolid && IsActive ) {
			// Verlet Step //
			Vector2D Velocity = (Pos - Old) + GravityVector;
			Old = Pos;
			// Lame drag/friction //
			Pos += Velocity * Real( 0.998 );
		}
	}
	
	void Draw( BITMAP* Target ) {
		// TODO: Use camera orientable draw code //
		
		int Value = 255;
		if (!IsActive)
			Value = 128;
		
		// Draw Rectangle parts //
		for ( size_t idx = 0; idx < Rect.size(); idx++ ) {
			rect(
				Target,
				(int)(Rect[idx].P1().x + Pos.x), (int)(Rect[idx].P1().y + Pos.y),
				(int)(Rect[idx].P2().x + Pos.x), (int)(Rect[idx].P2().y + Pos.y),
				makecol( IsSolid || (!IsBlockCollision || !IsPlayerCollision)?Value:0, IsPushable || !IsBlockCollision?Value:0, IsClimbable || !IsPlayerCollision?Value:0 )
				);
		}
		
		// Draw center point //
		circle( Target, (int)Pos.x, (int)Pos.y, 2, makecol( Value, Value, Value ) );
	}	
public:
	void Solve( cBlock& Vs, const Real& SolveRatio ) {
		// Bail if blocks have some property that means we can't/don't move //
		if ( !IsActive )
			return;
		if ( !Vs.IsActive )
			return;
			
		if ( IsSolid && Vs.IsSolid )
			return;
			
		if ( !IsBlockCollision )
			return;
		if ( !Vs.IsBlockCollision )
			return;
		
		// Calculate our solving ratios //
		Real MyRatio = SolveRatio;
		if ( IsSolid )
			MyRatio = Real::Zero;
		
		Real VsRatio = Real::One - SolveRatio;
		if ( Vs.IsSolid )
			VsRatio = Real::Zero;
		
		// For every rectangle in me versus every rectangle in the Vs object //
		for ( size_t idx = 0; idx < Rect.size(); idx++ ) {
			for ( size_t idx2 = 0; idx2 < Vs.Rect.size(); idx2++ ) {
				// If Collision //
				if ( (Rect[idx] + Pos) == (Vs.Rect[idx2] + Vs.Pos) ) {
					// Calculate the Rectangle difference //
					Rect2D Diff = Rect[idx] + Pos;
					Diff -= Vs.Rect[idx2] + Vs.Pos;
					
					//Contact.push_back( Diff );
					
					// TODO: Contact tracking per object, and friction

					// Depending on the rectangle difference, and who's P1 is greater, solve //
					if ( Diff.Width() < Diff.Height() ) {
						if ( (Rect[idx] + Pos).P1().x > (Vs.Rect[idx2] + Vs.Pos).P1().x ) {
							Pos.x += Diff.Width() * MyRatio;
							Vs.Pos.x -= Diff.Width() * VsRatio;
						}
						else {
							Pos.x -= Diff.Width() * MyRatio;
							Vs.Pos.x += Diff.Width() * VsRatio;	
						}
					}
					else {
						if ( (Rect[idx] + Pos).P1().y > (Vs.Rect[idx2] + Vs.Pos).P1().y ) {
							Pos.y += Diff.Height() * MyRatio;
							Vs.Pos.y -= Diff.Height() * VsRatio;
						}
						else {
							Pos.y -= Diff.Height() * MyRatio;
							Vs.Pos.y += Diff.Height() * VsRatio;							
						}					
					}
				}
			}
		}
	}

	void Solve( cPlayer& Vs, const Real& SolveRatio ) {
		// Bail if this block has some property that means we can't/don't move //
		if ( !IsActive )
			return;
		if ( !Vs.IsActive )
			return;
			
		if ( !IsPlayerCollision )
			return;
			
		// Do door key testing here (if player has key for me, kill me) //
			
		// Calculate our solving ratios //
		Real MyRatio = SolveRatio;
		if ( !IsPushable )
			MyRatio = Real::Zero;
		if ( IsSolid )
			MyRatio = Real::Zero;
		
		Real VsRatio = Real::One - SolveRatio;

		// For each rectangle in me //
		for ( size_t idx = 0; idx < Rect.size(); idx++ ) {
			// Calculate reference points and vector //
			Vector2D Point = (Rect[idx] + Pos).ClosestPoint( Vs.Pos );
			Vector2D CollisionVector = Point - Vs.Pos;
			Real RadiusSquared = (Vs.Radius * Vs.Radius);
			
			// If closest point returns the same point passed, push out of rect //
			if ( Point == Vs.Pos ) {
				Vector2D EdgePoint = (Rect[idx] + Pos).NearestEdgePoint( Vs.Pos );
				Vector2D CollisionVector = EdgePoint - Vs.Pos;
				
				Real Diff = CollisionVector.NormalizeRet();
				Diff += Vs.Radius;
				
				// Solve //
				Pos -= CollisionVector * (Diff * MyRatio);
				Vs.Pos += CollisionVector * (Diff * VsRatio);
				
				// TODO: Add friction here to solving //
				// Instead of scaling down to 0, scale towards surface motion //
				
				// Note the contact inside the player //
				Vs.Contact.AddContact( CollisionVector.AxisAligned().Normal(), Diff * VsRatio, &Rect[idx], IsClimbable );
				// Axis aligning is ok here, because we're an axis aligned box. //
				// For other surfaces, non aligned, you need to pick an edge to align to, and //
				// return that. NOT the corner vector!!! //
			}
			// If distance from shape to center is less than radius, we collide //
			else if ( CollisionVector.MagnitudeSquared() <= RadiusSquared ) {
				// Calculate difference, and normalize //
				Real Diff = CollisionVector.NormalizeRet();
				Diff -= Vs.Radius;
				
				// Solve //
				Pos -= CollisionVector * (Diff * MyRatio);
				Vs.Pos += CollisionVector * (Diff * VsRatio);
				
				// TODO: Add friction here to solving //
				// Instead of scaling down to 0, scale towards surface motion //
				
				// Note the contact inside the player //
				Vs.Contact.AddContact( CollisionVector.AxisAligned().Normal(), Diff * VsRatio, &Rect[idx], IsClimbable );
				// Axis aligning is ok here, because we're an axis aligned box. //
				// For other surfaces, non aligned, you need to pick an edge to align to, and //
				// return that. NOT the corner vector!!! //
			}
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __BLOCK_H__ //
// - ------------------------------------------------------------------------------------------ - //
