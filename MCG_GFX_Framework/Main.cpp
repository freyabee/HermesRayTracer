
#include <cmath>

#include "MCG_GFX_Lib.h"

#include "Camera.h"
#include "Ray.h"
#include "RayTracer.h"

int windowX = 640;
int windowY = 480;
int main( int argc, char *argv[] )
{
	// Variable for storing window dimensions
	glm::ivec2 windowSize( windowX, windowY );

	// Call MCG::Init to initialise and create your window
	// Tell it what size you want the window to be
	if( !MCG::Init( windowSize ) )
	{
		// We must check if something went wrong
		// (this is very unlikely)
		return -1;
	}

	// Sets every pixel to the same colour
	MCG::SetBackground( glm::ivec3(0,0,0) );

	// Preparing a position to draw a pixel
	glm::ivec2 pixelPosition = windowSize / 2;

	// Preparing a colour to draw
	glm::ivec3 pixelColour( 255, 0, 0 );


	// Draws a single pixel at the specified coordinates in the specified colour!
	//MCG::DrawPixel( pixelPosition, pixelColour );

	// Displays drawing to screen and holds until user closes window
	// You must call this after all your drawing calls
	// Program will exit after this line
	//return MCG::ShowAndHold();

	float timer = 0.0f;

	while( MCG::ProcessFrame() )
	{
		// Set every pixel to the same colour
		MCG::SetBackground( glm::ivec3( 0, 0, 0 ) );

		// Change our pixel's X coordinate according to time
		pixelPosition.x = (windowSize.x / 2) + (int)(sin(timer) * 100.0f);
		// Update our time variable
		timer += 1.0f / 60.0f;

		// Draw the pixel to the screen
		MCG::DrawPixel( pixelPosition, pixelColour );



		for (int x_coord = 0; x_coord < windowX; x_coord++)
		{
			for (int y_coord = 0; y_coord < windowY; windowY++)
			{

			}
		}


	}

	return 0;


}
