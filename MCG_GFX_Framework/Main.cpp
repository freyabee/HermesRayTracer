
#include <cmath>
#include <iostream>
#include <memory>
#include <thread>
#include "Scene.h"
#include "Camera.h"
#include "Ray.h"
#include "RayTracer.h"
#include "ThreadPool.h"
#include "Timer.h"
#include "Material.h"
#include "MCG_GFX_Lib.h"

int windowX = 1000;
int windowY = 1000;

void RayTraceCoord(glm::ivec2 block, RayTracer _tracer, std::shared_ptr<Camera> _camera, glm::vec3 _pixelColour, glm::ivec2 blockSizes)
{
	glm::ivec2 _start_point = glm::ivec2(block.x*blockSizes.x, block.y*blockSizes.y);

	for (int x = _start_point.x; x <=_start_point.x +blockSizes.x; x++)
	{
		for (int y = _start_point.y; y <= _start_point.y+blockSizes.y; y++)
		{
			
			glm::ivec2 _pixelPosition = glm::ivec2(x, y);
			
			Ray currentRay = _camera->CalculateRay(_pixelPosition);
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


	float timer = 0.0f;

	//define desired height and width of pixel blocks to be sent to thread
	int blockW = 10;
	int blockH = 10;

	//calculate number of blocks across the x
	int numXBlocks = windowX / blockW;
	int numYBlocks = windowY / blockH;
	int numBlocks = numXBlocks * numYBlocks;


	// Set every pixel to the same colour
	MCG::SetBackground(glm::ivec3(0, 0, 0));

	//Creation of camera object
	std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec2(windowX, windowY));

	//define materials
	std::shared_ptr<Material> mirror = std::make_shared<Material>(true);
	std::shared_ptr<Material> white = std::make_shared<Material>(glm::vec3(0.9f, 0.9f, 0.9f));

	//define pallet
	std::shared_ptr<Material> p_blue = std::make_shared<Material>(9.f, 0.f, 136.f);
	std::shared_ptr<Material> p_purple = std::make_shared<Material>(147.f, 0.f, 119.f);
	std::shared_ptr<Material> p_pink = std::make_shared<Material>(228.f, 0.f, 124.f);
	std::shared_ptr<Material> p_yellow = std::make_shared<Material>(255.f, 189.f, 57.f);
	std::vector<std::shared_ptr<Material>> palette1;
	palette1.push_back(p_blue);
	palette1.push_back(p_purple);
	palette1.push_back(p_pink);
	palette1.push_back(p_yellow);

	/* Define Scenes*/


	Scene display;

	display.AddSphereToScene(glm::vec3(-20.0f, -5.0f, -100.0f), 15.0f, mirror);
	display.AddSphereToScene(glm::vec3(-10.0f, 30.0f, -100.0f), 5.0f, p_blue);
	display.AddSphereToScene(glm::vec3(20.0f, 30.0f, -100.0f), 5.0f, p_pink);
	display.AddSphereToScene(glm::vec3(20.0f, 0.0f, -100.0f), 20.0f, p_yellow);
	display.AddSphereToScene(glm::vec3(5.0f, -15.0f, -80.0f), 5.0f, mirror);
	display.AddSphereToScene(glm::vec3(-10.0f, -15.0f, -80.0f), 2.0f, p_yellow);


	display.AddPointLightToScene(glm::vec3(-20.0f, 10.0f, -90.0f), 100.0f, p_pink);
	display.AddPointLightToScene(glm::vec3(20.0f, 10.0f, -90.0f), 100.0f, p_purple);
	display.AddPointLightToScene(glm::vec3(0.0f, 10.0f, -110.0f), 100.0f, p_yellow);

	display.AddDirectionalLightToScene(glm::vec3(0.f, -1.f, 0.f), 1.5f, white);

	display.AddPlaneToScene(glm::vec3(0.f, -20.f, -150.f), glm::vec3(0.f, 1.f, 0.f), white);
	display.AddPlaneToScene(glm::vec3(0.f, 0.f, -200.f), glm::vec3(0.f, 0.f, 1.f), white);


	Scene grid;
	
	grid.AddPointLightToScene(glm::vec3(0.0f, 0.0f, -70.0f), 50.0f, p_pink);
	grid.AddPointLightToScene(glm::vec3(-20.0f, 0.0f, -70.0f), 50.0f, p_yellow);
	grid.AddPointLightToScene(glm::vec3(20.0f, 0.0f, -70.0f), 50.0f, p_yellow);


	grid.AddDirectionalLightToScene(glm::vec3(0.f, 0.f, -1.f), 1.5f, white);
	//grid.AddPlaneToScene(glm::vec3(0.f, -20.f, -150.f), glm::vec3(0.f, 1.f, 0.f), white);
	//grid.AddPlaneToScene(glm::vec3(0.f, 0.f, -200.f), glm::vec3(0.f, 0.f, 1.f), white);
	
	int gridsize = 7;

	glm::vec3 origin(-30.f, 30.f, -100.f);


	std::shared_ptr<Material> rainbow = std::make_shared<Material>();
	float dia = 10.f;
	float spacing = 10.f;
	//grid.AddSphereToScene(origin, 5.f, white);




	for (int x = 0; x < gridsize; x++)
	{
		for (int y = 0; y < gridsize; y++)
		{
			grid.AddSphereToScene(glm::vec3((x*dia)+origin.x, (y*-dia)+origin.y, -100.f), 5.f, white);
		}
	}




	while (MCG::ProcessFrame())
	{
		/* Initialize ray and raytracer object. */
		Ray currentRay;
		RayTracer tracer(p_blue->GetAlbedo());
		tracer.AddScene(grid);
		/* Initialize pixel coordinate variable. */
		glm::ivec2 pixelPosition;

		/*TIMER INIT*/
		Timer t;
		t.Start();

		/* THREADS INITIALIZATION */
		ThreadPool pool{ 64 };
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
