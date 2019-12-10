
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
#include "Material.h"

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


	while (MCG::ProcessFrame())
	{
		// Set every pixel to the same colour
		MCG::SetBackground(glm::ivec3(0, 0, 0));

		//Creation of camera object
		std::shared_ptr<Camera> camera = std::make_shared<Camera>(glm::vec2(windowX, windowY));


		//define ray class
		Ray currentRay;
		//define raytracer
		RayTracer tracer(glm::vec3(0.f, 0.8f, 0.8f));
		//predefine current pixel position
		glm::ivec2 pixelPosition;


		//define materials
		std::shared_ptr<Material> white = std::make_shared<Material>(glm::vec3(0.9f, 0.9f, 0.9f));
		std::shared_ptr<Material> skyblue = std::make_shared<Material>(glm::vec3(0.f, 0.8f, 0.8f));
		std::shared_ptr<Material> grey = std::make_shared<Material>(glm::vec3(0.7f, 0.7f, 0.7f));
		std::shared_ptr<Material> pink = std::make_shared<Material>(glm::vec3(0.8f, 0.3f, 0.8f));
		std::shared_ptr<Material> red = std::make_shared<Material>(glm::vec3(0.8f, 0.f, 0.f));
		std::shared_ptr<Material> green = std::make_shared<Material>(glm::vec3(0.f, 0.8f, 0.f));
		std::shared_ptr<Material> blue = std::make_shared<Material>(glm::vec3(0.f, 0.f, 0.8f));
		std::shared_ptr<Material> mirror = std::make_shared<Material>(true);



		//Add plane(s)
		glm::vec3 planepos(0.0f, -20.0f, -150.f);
		glm::vec3 planenormal(0.f, 1.f, 0.f);
		tracer.AddPlaneToScene(planepos, planenormal, grey);




		//tracer.AddSphereToScene(glm::vec3(0.0f, 10.0f, -95.0f), 10.0f, grey);

		/*

				

		*/
		//add sphere to screen
		tracer.AddSphereToScene(glm::vec3(-20.0f, -5.0f, -100.0f), 15.0f, mirror);
		tracer.AddSphereToScene(glm::vec3(-10.0f, 30.0f, -100.0f), 5.0f, white);
		tracer.AddSphereToScene(glm::vec3(20.0f, 30.0f, -100.0f), 5.0f, green);
		tracer.AddSphereToScene(glm::vec3(20.0f, 0.0f, -100.0f), 20.0f, mirror);
		tracer.AddSphereToScene(glm::vec3(5.0f, -15.0f, -80.0f), 5.0f, pink);
		



		/*DIRECTIONAL LIGHTING*/
		glm::vec3 lightDirection(0.f, -1.0f, 0.f);
		//glm::vec3 lightColor(0.0f, 0.0f, 0.0f);
		glm::vec3 lightColor(1.0f, 1.0f, 1.0f);
		tracer.AddDirectionalLightToScene(lightColor, lightDirection, 1.5f);

		/*POINT LIGHTING*/
		glm::vec3 plCentre(0.f, 0.f, -100.f);

		


		tracer.AddPointLightToScene(glm::vec3(-20.0f, 10.0f, -80.0f), 100.0f, glm::vec3(0.8f, 0.f, 0.f));
		tracer.AddPointLightToScene(glm::vec3(20.0f, 10.0f, -80.0f), 100.0f, glm::vec3(0.f, 0.8f, 0.f));


		/*TIMER INIT*/
		Timer t;
		t.Start();

		/* THREADS INITIALIZATION */
		ThreadPool pool{ 16 };
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
