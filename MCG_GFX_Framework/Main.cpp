
#include <cmath>
#include <iostream>
#include <memory>
#include <thread>
#include "MCG_GFX_Lib.h"
#include "Camera.h"
#include "Ray.h"
#include "RayTracer.h"

int windowX = 500;
int windowY = 500;

void RayTraceCoord(glm::ivec2 block, RayTracer _tracer, Camera _camera, glm::vec3 _pixelColour, int block_size)
{
	glm::ivec2 _start_point = glm::ivec2(block.x*block_size, block.y*block_size);

	for (int x = _start_point.x; x <=_start_point.x +block_size; x++)
	{
		for (int y = _start_point.y; y <= _start_point.y+block_size; y++)
		{
			
			glm::ivec2 _pixelPosition = glm::ivec2(x, y);
			
			Ray currentRay = _camera.CalculateRay(_pixelPosition);
			_pixelColour = _tracer.TraceRay(currentRay);
			_pixelColour = _pixelColour * glm::vec3(255);
			MCG::DrawPixel(_pixelPosition, _pixelColour);
			
			//std::cout << "drawn at " << _pixelPosition.x << "," << _pixelPosition.y << std::endl;
		}
	}
	
}

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
		/*
		for (int x_coord = 0; x_coord <= windowX; x_coord++)
		{
			for (int y_coord = 0; y_coord <= windowY; y_coord++)
			{
				pixelPosition =  glm::ivec2(x_coord, y_coord);

				currentRay = camera.CalculateRay(pixelPosition);
				pixelColour = tracer.TraceRay(currentRay);


				pixelColour = pixelColour * glm::vec3(255);
				MCG::DrawPixel(pixelPosition, pixelColour);
			}
		}
		*/
		int block_size = 10;

		int parts = 2;
		int num_blocks_y = windowX / block_size;
		int num_blocks_x = windowY / block_size;


		/*
		for (int y = 0; y <= num_blocks_y; y++)
		{
			for (int x = 0; x < num_blocks_x; x = x + 2)
			{
				std::thread first(RayTraceCoord, glm::ivec2(x,y), tracer, camera, pixelColour, block_size);
				std::thread second(RayTraceCoord, glm::ivec2(x+1,y), tracer, camera, pixelColour, block_size);
				first.join();
				second.join();
			}
		}
		*/
		
		

		std::cout << "Render fin" << std::endl;
		return MCG::ShowAndHold();
		
	}
	return 0;
}