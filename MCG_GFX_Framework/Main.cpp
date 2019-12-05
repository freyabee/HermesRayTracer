
#include <cmath>
#include <iostream>
#include <memory>
#include <thread>
#include "MCG_GFX_Lib.h"
#include "Camera.h"
#include "Ray.h"
#include "RayTracer.h"
#include "ThreadPool.h"
#include "Timer.h"


int windowX = 500;
int windowY = 500;




void RayTraceCoord(glm::ivec2 block, RayTracer _tracer, Camera _camera, glm::vec3 _pixelColour, glm::ivec2 blockSizes)
{
	glm::ivec2 _start_point = glm::ivec2(block.x*blockSizes.x, block.y*blockSizes.y);

	for (int x = _start_point.x; x <=_start_point.x +blockSizes.x; x++)
	{
		for (int y = _start_point.y; y <= _start_point.y+blockSizes.y; y++)
		{
			
			glm::ivec2 _pixelPosition = glm::ivec2(x, y);
			
			Ray currentRay = _camera.CalculateRay(_pixelPosition);
			_pixelColour = _tracer.TraceRay(currentRay);
			_pixelColour = _pixelColour * glm::vec3(255);

			try
			{
				MCG::DrawPixel(_pixelPosition, _pixelColour);
			}
			catch (std::exception& e)
			{
				std::cout << "Error occured at print pixel" << std::endl;
			}

			
		}
	}
	//std::cout << "drawn block " << block.x <<","<< block.y << std::endl;
}

void TestFunction(int xCoord, int yCoord)
{
	std::cout << xCoord << ", " << yCoord << std::endl;
}


//TODO HAVE A LOOK AT THIS https://ncona.com/2019/05/using-thread-pools-in-cpp/



struct Input
{
	glm::ivec2 coord;
	RayTracer tracer;
	Camera camera;
	glm::ivec3 pixelColour;
	int block_size;

};

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


	float timer = 0.0f;

	//define desired height and width of pixel blocks to be sent to thread
	int blockW = 10;
	int blockH = 10;

	//calculate number of blocks across the x
	int numXBlocks = windowX / blockW;
	int numYBlocks = windowY / blockH;

	int numBlocks = numXBlocks * numYBlocks;


	while (MCG::ProcessFrame())
	{
		// Set every pixel to the same colour
		MCG::SetBackground(glm::ivec3(0, 0, 0));

		//Creation of camera object
		Camera camera(glm::vec2(windowX, windowY));


		//define ray class
		Ray currentRay;
		//define raytracer
		RayTracer tracer;
		//predefine current pixel position
		glm::ivec2 pixelPosition;


		//add sphere to screen
		tracer.AddSphereToScene(glm::vec3(20.0f, 0.0f, -100.0), 15.0f);
		tracer.AddLightToScene(glm::vec3(-10.0f, 0.0f, -100.0), 10.0f);
		
		/*TIMER INIT*/
		Timer t;
		t.Start();
		/* THREAD INIT */
		//int max_threads = std::thread::hardware_concurrency(); //Retrieve maximum number of threads supported
		//init thread pool
		ThreadPool pool{ 32 };

		//std::cout << max_threads << std::endl;
		glm::ivec2 block(0, 0);
		glm::ivec2 blockSize(blockW, blockH);

		//iterate through each block and send it to render
		for (int y = 0; y <= numYBlocks; y++)
		{
			for (int x = 0; x <= numXBlocks; x++)
			{
				
				block.x = x;
				block.y = y;

				pool.addToQ([block, tracer, camera, pixelColour, blockSize]
				{
					RayTraceCoord(block, tracer, camera, pixelColour, blockSize);
				}
				);
			}
		}
		pool.stop();
		t.Stop();
		std::cout << "Render fin" << std::endl;
		return MCG::ShowAndHold();

	}


	return 0;
}
