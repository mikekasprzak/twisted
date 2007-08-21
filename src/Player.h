// - ------------------------------------------------------------------------------------------ - //
#ifndef __PLAYER_H__
#define __PLAYER_H__
// - ------------------------------------------------------------------------------------------ - //
// Player (Verlet Sphere, should not push blocks, use gravity powers to kill baddies) //
// Enemies (Same squish death rules, multiple movement patterns, speed adjustable)
//    - Fixed distance movement (walks in to walls, turning around walking their full distance)
//    - Wall contact movement (keeps going until they hit a wall, does not climb)
//    - Fixed distance climbing
//    - Wall climbing infinite distance (walks like a player holding down left or right)
//    - Path Flier (does not use walls, follows paths)
//    - Homing Flier (attempts to hunt down nearest player, stop at walls (Impossible Mission orb)
// Hostages (Characters you don't control, but also must not hurt.  Like a pickup you can kill)
// - ------------------------------------------------------------------------------------------ - //
class cPlayer {
public:
	// Verlet positions //
	Vector2D Pos, Old, Home;
	
	// My local gravity //
	Vector2D GravityNormal, HomeGravityNormal;
	
	// Our character is a sphere, this'll be mostly constant, unless we pull a "size matters" //
	Real Radius;
	
	// Current Friction based on conditions //
	Real Friction;

	// Character not dead flag //
	bool IsActive;


	// TODO: Hack, until I have real input code //	
	bool PressedJump;
	int PressedWalk;

public:
	// List of our physics contacts //
	class cContact {
	public:
		deque< Vector2D > Vector;
		deque< Real > Length;
		deque< Rect2D* > Rect;
		deque< bool > IsClimbable;
	
	public:
		void Clear() {
			Vector.clear();
			Rect.clear();
			IsClimbable.clear();
		}
		
		inline const size_t Size() const {
			return Vector.size();
		}
		
		void AddContact( const Vector2D& _Vector, const Real& _Length, Rect2D* _Rect, const bool& _IsClimbable ) {
			// Confirm and bail if this Rectangle has been added to the list before //
			for ( size_t idx = 0; idx < Rect.size(); idx++ ) {
				if ( Rect[idx] == _Rect ) {
					Length[idx] += _Length;
					return;	
				}
			}
			
			// So long as it wasn't a dupe, add it //
			Vector.push_back( _Vector );
			Length.push_back( _Length );
			Rect.push_back( _Rect );
			IsClimbable.push_back( _IsClimbable );
		}
		
		void Optimize() {
			for ( size_t idx = 0; idx < Vector.size(); idx++ ) {
				for ( size_t idx2 = idx+1; idx2 < Vector.size(); idx2++ ) {
					if ( Vector[idx] * Vector[idx2] == Real::One ) {
						// TODO: Remove an entry, as it's a dupe //
						
					}
				}
			}			
		}
	};
	
	cContact Contact;
public:
	cPlayer( const Vector2D& _Pos, const Vector2D& _GravityNormal = Vector2D( 0, 1 ) ) :
		Pos( _Pos ),
		Old( _Pos ),
		Home( _Pos ),
		GravityNormal( _GravityNormal ),
		HomeGravityNormal( _GravityNormal ),
		Radius( Real( 16 ) ),
		Friction( Real( 0.998 ) ),
		IsActive( true ),
		PressedJump( false ),
		PressedWalk( 0 )
	{
	}
	
	inline const Vector2D Velocity() const {
		return Old - Pos;
	}
	
public:
	void Reset() {
		Pos = Home;
		Old = Home;
		GravityNormal = HomeGravityNormal;
		//Radius = Real( 16 );
		
		IsActive = true;
	}
	
	void Step( Real _Gravity ) {
		if ( IsActive ) {
			// Verlet Step //
			Vector2D Velocity = (Pos - Old) + (GravityNormal * _Gravity);
			Old = Pos;
			// Lame drag/friction //
			Pos += Velocity * Friction;
			
			// TODO: Remove junk friction above, and make this explicitly fluidic drag. //
			
			// Clear Contacts //
			Contact.Clear();
		}
	}
	
	void Work() {
		if ( IsActive ) {
			// Do controls //
			Real Stick = Real::Zero;
			
			if ( key[ KEY_LEFT ] ) {
				Stick = -Real::One;
				PressedWalk++;
			}
			else if ( key[ KEY_RIGHT ] ) {
				Stick = Real::One;
				PressedWalk++;
			}
			else {
				PressedWalk = 0;
			}
			
			// Jumping hack //
			if ( !PressedJump ) {
				if ( key[ KEY_A ] ) {
					PressedJump = true;
					
					// TODO: Search for a contact that's reasonably parallel with gravity normal //
					//  If one exists, then allow a jump //
					if ( Contact.Size() > 0 ) {
						Pos += -GravityNormal * Real( 6 );
					}
				}
			}
			if ( !key[ KEY_A ] ) {
				PressedJump = false;	
			}
			
			
			// Clamp speed addition to max speed (Velocity dot Normal.Tangent)
			if ( Stick != Real::Zero ) {
				Real TangentalMotion = Velocity() * GravityNormal.Tangent();
				Real Acceleration = Real( 0.4 ) * Stick;
				Real MotionSum = TangentalMotion + Acceleration;
				Real MaxSpeed( 3 );
				
				// If the Tangental Motion is greater than the maximum speed, then we can't accelerate
				// in a specific direction, natually at least //
				if ( TangentalMotion.Abs() > MaxSpeed ) {
				}
				
				// If the sum of the motions in greater than the maximum speed, then it's too much //
				// We need to use a fraction of the speed, or zero.
				if ( MotionSum.Abs() > MaxSpeed ) {
					// If we're not trying to make the speed larger, then our acceleration is fine //
					if ( MotionSum.Abs() < TangentalMotion.Abs() ) {
						// If we're not traveling faster than our max speed, accumulate some acceleration //
						if ( TangentalMotion.Abs() < MaxSpeed ) {
							Acceleration = (MaxSpeed * Stick) - TangentalMotion;
						}
						// If we are, we can't accelerate faster in this direction //
						else {		
							Acceleration = 0;
						}
					}
				}
				// Add stick to character //
				Pos += Acceleration * GravityNormal.Tangent();
			}
				
			
			// Optimize contacts (remove duplicate normals, from crossing connected blocks) //
			//Contact.Optimize();
		
			// If there were any contacts //
			if ( Contact.Size() > 0 ) {
				// Set Friction to suit a surface contact //
				Friction = Real( 0.9 );
				
				// If there were multiple contacts, allow us to scale a neighbouring wall //
				if ( Contact.Size() > 1 ) {
					// If controls produce a scenario that suits changing gravity, change it //
					//if ( (Stick != Real::Zero) && key[ KEY_A ] ) {
					//if ( (Stick != Real::Zero) && (PressedWalk < 8) ) {
					if ( (Stick != Real::Zero) ) {
						// Take "most tangent" contact as new normal //
						Vector2D MostTangentContact = Vector2D::Zero;
						Real MostTangentValue = -Real::One;
						int FoundContact = 0;
						
						for ( size_t idx = 0; idx < Contact.Size(); idx++ ) {
							// Ignore a side if the side isn't climbable //
							if ( !Contact.IsClimbable[idx] )
								continue;
							
							Real TangentValue = Contact.Vector[idx] * (Stick.Normal() * GravityNormal.Tangent());
							
							if ( TangentValue > MostTangentValue ) {
								MostTangentContact = Contact.Vector[idx];
								MostTangentValue = TangentValue;
								FoundContact++;
							}
						}
						
						// Take "most tangent" contact as new normal, if one was found //
						if ( FoundContact ) {
							GravityNormal = MostTangentContact;
						}
					}
				}
				
				// If there were multiple contacts, see if we were squished //
				if ( Contact.Size() > 1 ) {
					// To be considered squished, you need much motion, and an impact with an //
					// acute angle //
					
					// TODO: Acute Angle test (death only from sqishing) //
					// TODO: Limit acute angle sqishings only to blocks from 45 degrees off axis //
					if ( true ) {
						
						for ( size_t idx = 0; idx < Contact.Size(); idx++ ) {
							// Test if our solved motion breaks a limit (death limit) //
							// This should be larger than top speed, else getting squished in a //
							// corner might be too easy //
							if ( Contact.Length[idx] > Real(6) ) {
								// Too much push.  I'm dead. //
								IsActive = false;
							}
						}
					}
				}
			}
			// No contacts //
			else {
				// Set friction to suit no contacts //
				Friction = Real( 0.998 );
			}
		}
	}
	
	void Draw( BITMAP* Target ) {
		// TODO: Use camera orientable draw code //
		
		if ( IsActive ) {
			// Circle Collision Placeholder //
			circle( Target, (int)Pos.x, (int)Pos.y, (int)Radius, makecol( 255, 255, 0 ) );
			
			// Gravity Normal //
			Vector2D GravNormal = Pos + (GravityNormal * Radius);
			line(
				Target,
				(int)Pos.x, (int)Pos.y,
				(int)GravNormal.x, (int)GravNormal.y,
				makecol( 255, 255, 255 )
				);
		}
		else {
			// Circle Collision Placeholder //
			circle( Target, (int)Pos.x, (int)Pos.y, (int)Radius, makecol( 128, 128, 0 ) );
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __PLAYER_H__ //
// - ------------------------------------------------------------------------------------------ - //
