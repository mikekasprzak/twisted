
// - ------------------------------------------------------------------------------------------ - //
#include <allegro.h>
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <deque>
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
// Select part from Geometry Library //
#include <Geometry/Real.h>
#include <Geometry/Vector.h>
#include <Geometry/Matrix.h>
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Player.h"
#include "Block.h"
#include "PickUp.h"
#include "Game.h"
// - ------------------------------------------------------------------------------------------ - //
void MatrixRect( BITMAP* Target, const Matrix3x3& Matrix, const Rect2D& Rect, int Color ) {
	// Get our points //
	Vector2D Point[4];
	Point[0] = Rect.P1();
	Point[1] = Vector2D( Rect.P2().x, Rect.P1().y );
	Point[2] = Rect.P2();
	Point[3] = Vector2D( Rect.P1().x, Rect.P2().y );
	
	// Transform them by the matrix //
	Point[0] = Point[0].ToVector3D().ApplyMatrix( Matrix ).ToVector2D();
	Point[1] = Point[1].ToVector3D().ApplyMatrix( Matrix ).ToVector2D();
	Point[2] = Point[2].ToVector3D().ApplyMatrix( Matrix ).ToVector2D();
	Point[3] = Point[3].ToVector3D().ApplyMatrix( Matrix ).ToVector2D();
	
	// Draw our 4 lines to make the rectangle //
	rect( Target, (int)(Point[0].x), (int)(Point[0].y), (int)(Point[1].x), (int)(Point[1].y), Color );
	rect( Target, (int)(Point[1].x), (int)(Point[1].y), (int)(Point[2].x), (int)(Point[2].y), Color );
	rect( Target, (int)(Point[2].x), (int)(Point[2].y), (int)(Point[3].x), (int)(Point[3].y), Color );
	rect( Target, (int)(Point[3].x), (int)(Point[0].y), (int)(Point[0].x), (int)(Point[0].y), Color );
}
// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv ) {
	// Initialize Allegro //
	allegro_init();
	install_keyboard();
	install_mouse();
	//install_joystick();
	
	// Create our window and back buffer //
	set_color_depth( 16 );
	set_gfx_mode( GFX_AUTODETECT_WINDOWED, 800, 600, 0, 0 );
	
	BITMAP* Buffer = create_bitmap( 800, 600 );
	
	// Killed by pressing ESC //
	while( !key[ KEY_ESC ] ) {
		// Initialize things for our experiment //
		cGame Game;
		Contact.clear();
		
		// The Loop - killed by ESC, reset by TAB //
		while( !key[ KEY_ESC ] && !key[ KEY_TAB ] ) {
			clear_to_color( Buffer, makecol(30, 0, 0) );

			Game.Step();
			Game.Draw( Buffer );
			
			// Sync and copy buffer to screen //
			vsync();
			blit( Buffer, screen, 0, 0, 0, 0, 800, 600 );
			rest( 0 );
			
			// Pause by pressing the Spacebar //
			while( key[ KEY_SPACE ] ) {
				// Step by pressing enter //
				if ( key[ KEY_ENTER ] ) {
					while( key[ KEY_ENTER ] ) {	
					}
					break;
				}
			}
		};
	};
	
	destroy_bitmap( Buffer );
		
	// Kill Allegro (big sharp knife) //
	allegro_exit();
	
	return 0;
}
END_OF_MAIN();
// - ------------------------------------------------------------------------------------------ - //
