
// - ------------------------------------------------------------------------------------------ - //
#include <allegro.h>
// - ------------------------------------------------------------------------------------------ - //
#include <vector>
#include <deque>
#include <iostream>
using namespace std;
// - ------------------------------------------------------------------------------------------ - //
// Select part from Geometry Library //
#include <Geometry/Real.h>
#include <Geometry/Vector.h>
#include <Geometry/Matrix.h>
#include <Geometry/Rect.h>

#include "Graph/ConditionalGraph.h"
// - ------------------------------------------------------------------------------------------ - //
#include "MatrixDraw.h"
// - ------------------------------------------------------------------------------------------ - //
#include "Player.h"
#include "Block.h"
#include "PickUp.h"
#include "Game.h"
// - ------------------------------------------------------------------------------------------ - //
Matrix3x3 ViewMatrix;
Matrix3x3 Orientation;
Vector2D CameraDown;
// - ------------------------------------------------------------------------------------------ - //
int main( int argc, char* argv ) {
	cout << "Captain!  We're under attack!" << endl;
	
	const Matrix3x3 HomeMatrix(
		Real::One, Real::Zero, Real::Zero,
		Real::Zero, -Real::One, Real::Zero,
		Real(400), Real(300), Real::One
		);
	
	Orientation = Matrix3x3(
		Real::One, Real::Zero, Real::Zero,
		Real::Zero, Real::One, Real::Zero,
		Real::Zero, Real::Zero, Real::One
		);	

//	cout << ViewMatrix(0,0) << " " << ViewMatrix(1,0) << " " << ViewMatrix(2,0) << endl;
//	cout << ViewMatrix(0,1) << " " << ViewMatrix(1,1) << " " << ViewMatrix(2,1) << endl;
//	cout << ViewMatrix(0,2) << " " << ViewMatrix(1,2) << " " << ViewMatrix(2,2) << endl;
	
	CameraDown = Vector2D( 0, -1 );
	
	
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

			Orientation = Matrix3x3();
			Game.Step();
			ViewMatrix = Orientation;
			ViewMatrix *= HomeMatrix;
			Game.Draw( Buffer );
			
			// Sync and copy buffer to screen //
			vsync();
			blit( Buffer, screen, 0, 0, 0, 0, 800, 600 );
			rest( 0 );
			
			// Pause by pressing the Spacebar //
			while( key[ KEY_SPACE ] ) {
				// Step by pressing enter //
				if ( key[ KEY_ENTER ] ) {
					cout << Orientation(0,0) << " " << Orientation(1,0) << " " << Orientation(2,0) << endl;
					cout << Orientation(0,1) << " " << Orientation(1,1) << " " << Orientation(2,1) << endl;
					cout << Orientation(0,2) << " " << Orientation(1,2) << " " << Orientation(2,2) << endl;
					cout << endl;
					
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
