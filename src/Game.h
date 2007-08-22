// - ------------------------------------------------------------------------------------------ - //
#ifndef __GAME_H__
#define __GAME_H__
// - ------------------------------------------------------------------------------------------ - //
class cGame {
public:
	vector< cPlayer > Player;
	vector< cPickUp > PickUp;
	
	vector< cBlock > Block;
	
	// Global Gravity that affects sliding blocks //
	Real Gravity;
	Vector2D GravityNormal;

public:
	cGame() :
		Gravity( 0.2 ),
		GravityNormal( 0, 1 ) 
	{
		// Test Map //
		Player.push_back( cPlayer( Vector2D(610, 264) ) );
		
		PickUp.push_back( cPickUp( Vector2D(300, 300) ) );
		
		// Static Collision (climbable, not movable at all) //
		Block.push_back( cBlock( Vector2D( 400, 300 ), true, false, true ) );
		Block.back().Rect.push_back( Rect2D( Vector2D(-350,-225), Vector2D(700,50) ) );
		Block.back().Rect.push_back( Rect2D( Vector2D(-150,225), Vector2D(500,50) ) );
		Block.back().Rect.push_back( Rect2D( Vector2D(-350,-225), Vector2D(50,500) ) );
		Block.back().Rect.push_back( Rect2D( Vector2D(350,-225), Vector2D(50,500) ) );
		
		// Pushable, non climbable block //
		Block.push_back( cBlock( Vector2D(400, 400), false, true, true ) );
		Block.back().Rect.push_back( Rect2D( Vector2D(-100,-50), Vector2D(200,50) ) );
		Block.back().Rect.push_back( Rect2D( Vector2D(-50,0), Vector2D(100,100) ) );
		
		// Climbable, non pushable block //
		Block.push_back( cBlock( Vector2D(220, 200), false, false, true ) );
		Block.back().Rect.push_back( Rect2D( Vector2D(-100,-50), Vector2D(200,50) ) );
		Block.back().Rect.push_back( Rect2D( Vector2D(-50,0), Vector2D(100,100) ) );		
	}
public:
	void Step() {
		// Gravity Change cheats //
		if ( key[ KEY_1 ] )
			GravityNormal = Vector2D( 0, 1 );
		if ( key[ KEY_2 ] )
			GravityNormal = Vector2D( 0, -1 );
		if ( key[ KEY_3 ] )
			GravityNormal = Vector2D( 1, 0 );
		if ( key[ KEY_4 ] )
			GravityNormal = Vector2D( -1, 0 );

		
		// Move Players //
		for ( size_t idx = 0; idx < Player.size(); idx++ ) {
			Player[idx].Step( Gravity );
		}
		
		// Move Blocks //
		for ( size_t idx = 0; idx < Block.size(); idx++ ) {
			Block[idx].Step( Gravity * GravityNormal );
		}
		
		
		// TODO: Players Vs PickUp's //
		
		// TODO: Enemies, Hostages

		// Relaxation loop, for solidity //
		for ( size_t Relax = 0; Relax < 4; Relax++ ) {
			// TODO: Player's Vs Players //
			
			// Player Vs Blocks //
			for ( size_t idx = 0; idx < Block.size(); idx++ ) {
				for ( size_t idx2 = 0; idx2 < Player.size(); idx2++ ) {
					Block[idx].Solve( Player[idx2], Real::Half );
				}
			}
			
			// Blocks Vs. Blocks //
			for ( size_t idx = 0; idx < Block.size(); idx++ ) {
				for ( size_t idx2 = idx+1; idx2 < Block.size(); idx2++ ) {
					Block[idx].Solve( Block[idx2], Real::Half );
				}
			}
		}
		
		// Work Players //
		for ( size_t idx = 0; idx < Player.size(); idx++ ) {
			Player[idx].Work( );
		}		
	}
	
	void Draw( BITMAP* Buffer ) {
		// TODO: Use camera orientable draw code (stored here in game, passed to functions) //
		
		// Players //
		for ( size_t idx = 0; idx < Player.size(); idx++ ) {
			Player[idx].Draw( Buffer );
		}		
		
		// PickUp's //
		for ( size_t idx = 0; idx < PickUp.size(); idx++ ) {
			PickUp[idx].Draw( Buffer );
		}
				
		// Blocks //
		for ( size_t idx = 0; idx < Block.size(); idx++ ) {
			Block[idx].Draw( Buffer );
		}	
		
		for ( size_t idx = 0; idx < Contact.size(); idx++ ) {
			MatrixRect(
				Buffer,
				ViewMatrix,
				Contact[idx],
				makecol( 255, 255, 255 )
				);
		}
	}
};
// - ------------------------------------------------------------------------------------------ - //
#endif // __GAME_H__
// - ------------------------------------------------------------------------------------------ - //
