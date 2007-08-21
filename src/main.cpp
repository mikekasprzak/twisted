
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
#include <Geometry/Rect.h>
// - ------------------------------------------------------------------------------------------ - //
#include "Player.h"
#include "Block.h"
#include "PickUp.h"
#include "Game.h"
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
