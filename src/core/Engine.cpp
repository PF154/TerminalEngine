#include "../../include/core/Engine.hpp"
#include "../../include/core/Game.hpp"
#include "../../include/core/Scene.hpp"
#include "../../include/utils/TerminalTools.hpp"
#include "../../include/components/GameObject.hpp"
#include "../../include/components/VisualObject.hpp"

#include "../../example/include/Block.hpp"

#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include <iostream>
#include <memory>
#include <fstream>

std::ofstream debug_log("debug_log.txt", std::ios::app);
bool printMesh = true;

Engine::Engine()
{
	this->viewport = Viewport(60, 40);
}

Engine::~Engine()
{

}

void Engine::begin()
{
	this->game->play();

	for (int i=0; i<this->viewport.getYSize()+2; i++) 
	{
		std::cout << "." << std::string(this->viewport.getXSize()+2, '.') << std::endl;
	}
}

void Engine::run()
{

	if (this->game == nullptr)
	{
		std::cout << "Attempted to run engine on undefined game, aborting." << std::endl;
		return;
	}

	begin();

	using clock = std::chrono::steady_clock;

	// const std::chrono::duration<double> target_frame_duration{1.0 / tick_rate};
	const std::chrono::duration<double> target_frame_duration{1.0 / tick_rate};


	debug_log << "target_frame_duration = " << target_frame_duration << std::endl;

	double last_delta = 0.0;
	while (true) {
		auto frame_start = clock::now();

		update(last_delta);

		auto frame_end = clock::now();
		std::chrono::duration<double> delta = frame_end - frame_start;

		// Wait for frame to end to keep a consistent frame rate
		if (delta < target_frame_duration)
		{
			// NOTE: This is not the best way to do this, because we cannot accept input
			// Instead, I think we should get stuck in a while loop until the right time is hit
			// sleep(target_frame_duration.count() - delta.count());
			std::this_thread::sleep_for(target_frame_duration - delta);
		}

		last_delta = delta.count();
	}
}

void Engine::update(double delta)
{

	// At each tick, we want to compute collisions (this should eventually be a part of calling update on objects I think?)
	Scene* currentScene = this->game->getCurrentScene();
	if (!currentScene) {
		std::cout << "ERROR: currentScene is null!\n" << std::endl;
		return;
	}

	for (std::shared_ptr<GameObject> gameObject : currentScene->getGameObjects()) gameObject->update(delta);

	// Draw Frame
	graphicsUpdate(delta);

}

void Engine::graphicsUpdate(double delta)
{
	// std::cout << "Graphics update called" << std::endl;
	// Draw logic
	// At every tick, the engine should compute the frame to draw to the terminal
	// We first want to get the viewport frame
	// Then, we want to get the information of every GameObject in the scene
	// The GameObject will not have it's own draw function.
	// GameObject should have a getMesh() function or something similar, that
	// sends it's visual representation to the engine.
	// However, the problem is that we need to check which parts of the mesh are in the viewport.
	// I think what we want is to get the whole visual from the GameObject, along with the GameObject's position
	// From there, we can calculate which vertices (characters) are on screen


	// Draw viewport

	// Frame corresponds to the frame to be rendered, not just the "picture frame" outline of the viewport
	// We do, however, use the viewport outline as a starting point
	std::vector<std::string> frame = this->viewport.getVisual();
	moveCursorUp(frame.size() + 2);

	// // Due to z-sorting, this loop should automatically iterate back-to-front

	if (!this->game) {
		std::cout << "ERROR: game is null!\n" << std::endl;
		return;
	}

	Scene* currentScene = this->game->getCurrentScene();
	// std::cout << "got scene at " << static_cast<const void*>(currentScene) << std::endl;

	if (!currentScene) {
		std::cout << "ERROR: currentScene is null!\n" << std::endl;
		return;
	}

	// std::vector<VisualObject*> visualObjects;
	// for (GameObject* gameObject : currentScene->getGameObjects())

	for (std::shared_ptr<GameObject> gameObject : currentScene->getGameObjects())
	{
		std::shared_ptr<VisualObject> visualObject = std::dynamic_pointer_cast<VisualObject>(gameObject);
		if (visualObject)
		{
			// std::cout << "Attempting to get mesh" << std::endl;
			std::vector<std::string> mesh = visualObject->getVisual();
			if (printMesh) {
				for (std::string line : mesh)
				{
					debug_log << line << std::endl;
				}
				printMesh = false;
			}
			// std::cout << "Got visual: " << mesh[0] << std::endl;

			// Calculate which parts of the mesh are on screen
			int y_size = visualObject->getSize().y;
			int x_size = visualObject->getSize().x;

			int y_pos = visualObject->getPosition().y;
			int x_pos = visualObject->getPosition().x;

			// Replace lines of screen with mesh
			for (int line=0; line<frame.size(); line++)
			{
				if (line >= y_pos && line <= y_pos + y_size)
				{
					// If we are in here, then we are on a line that could potentially have an object on screen

					if (x_pos < frame[line].length() && x_pos + x_size > 0)
					{
						std::string header = frame[line].substr(0, x_pos);
						std::string object = mesh[line - y_pos];
						std::string trailer = frame[line].substr(header.size() + object.size(), frame[line].size());
						// std::string new_line = 	frame[line].substr(0, x_pos) + 	// Empty space before object
						// 						mesh[y_pos - line] + 			// Object itself
						// 														// Empty space after object
						// 						frame[line].substr(x_pos + mesh[0].length() + frame[line].length() -(x_pos + mesh[0].length()));
						std::string new_line = header + object + trailer;
						frame[line] = new_line;
					}
				}
			}

			

		}
		
	}

	for (int line=0; line<frame.size(); line++)
	{
		clearLine();
		std::cout << frame[line] << std::endl;
	}
	std::cout << "Game objects in scene: " << currentScene->getGameObjects().size() << std::endl;
	// std::cout << "Filtered objects in scene: " << visualObjects.size() << std::endl;
	std::cout << "FPS: " << 1.0 / delta << std::endl;


}