
#include <cmath>
#include <iostream>
#include <memory>
#include "MCG_GFX_Lib.h"
#include "Camera.h"
#include "Ray.h"
#include "RayTracer.h"

int windowX = 500;
int windowY = 500;
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
	glm::vec3 pixelColour( 1, 0, 0 );


	// Draws a single pixel at the specified coordinates in the specified colour!
	//

	// Displays drawing to screen and holds until user closes window
	// You must call this after all your drawing calls
	// Program will exit after this line
	

	float timer = 0.0f;

	while( MCG::ProcessFrame() )
	{
		// Set every pixel to the same colour
		MCG::SetBackground( glm::ivec3( 0, 0, 0 ) );

		//Creation of camera object
		Camera camera(glm::vec2(windowX, windowY));
		Ray currentRay;
		RayTracer tracer;
		glm::ivec2 pixelPosition;


		tracer.AddSphereToScene(glm::vec3(0.0f, 0.0f, -100.0), 20.0f);

		for (int x_coord = 0; x_coord <= windowX; x_coord++)
		{
			
		}
		std::cout << "Render fin" << std::endl;
		return MCG::ShowAndHold();
		
	}

	void InterateThroughRow()
	{
		for (int y_coord = 0; y_coord <= windowY; y_coord++)
		{
			//std::cout << "Pixel: " << "(" << x_coord << "," << y_coord << ")" << std::endl;
			pixelPosition = glm::ivec2(x_coord, y_coord);
			currentRay = camera.CalculateRay(pixelPosition);
			pixelColour = tracer.TraceRay(currentRay);
			pixelColour = pixelColour * glm::vec3(255);
			MCG::DrawPixel(pixelPosition, pixelColour);
		}

	}
	
	return 0;


}
