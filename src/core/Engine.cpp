#include <core/Engine.hpp>
#include <core/Game.hpp>
#include <core/Scene.hpp>
#include <utils/TerminalTools.hpp>
#include <components/GameObject.hpp>
#include <components/Mesh.hpp>
#include <physics/PhysicsEngine.hpp>


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
	this->m_viewport = Viewport(60, 40);
	debug_log << "\n";
}

Engine::~Engine()
{

}

void Engine::begin()
{
	this->m_game->play();

	loadNewScene(m_game->getCurrentScene());

	for (int i=0; i<this->m_viewport.getYSize()+2; i++) 
	{
		std::cout << "." << std::string(this->m_viewport.getXSize()+2, '.') << std::endl;
	}
}

void Engine::run()
{

	if (this->m_game == nullptr)
	{
		std::cout << "Attempted to run engine on undefined game, aborting." << std::endl;
		return;
	}

	begin();

	using clock = std::chrono::steady_clock;

	// const std::chrono::duration<double> target_frame_duration{1.0 / tick_rate};
	const std::chrono::duration<double> target_frame_duration{1.0 / m_tick_rate};


	debug_log << "target_frame_duration = " << target_frame_duration << std::endl;

	double last_delta = 0.0;
	while (true) {
		auto frame_start = clock::now();

		update(last_delta);

		// auto frame_end = clock::now();
		// std::chrono::duration<double> delta = frame_end - frame_start;

		// Wait for frame to end to keep a consistent frame rate
		// if (delta < target_frame_duration)
		// {
		// 	// NOTE: This is not the best way to do this, because we cannot accept input
		// 	// Instead, I think we should get stuck in a while loop until the right time is hit
		// 	// sleep(target_frame_duration.count() - delta.count());
		// 	// std::this_thread::sleep_for(target_frame_duration - delta);
		// }

		while (clock::now() - frame_start < target_frame_duration)
		{
			// Here we can just check for input or whatever we want to still happen between frames
		}

		auto frame_end = clock::now();
		std::chrono::duration<double> delta = frame_end - frame_start;

		last_delta = delta.count();
	}
}

void Engine::update(double delta)
{
	// At each tick, we want to compute collisions (this should eventually be a part of calling update on objects I think?)
	if (!m_current_scene) {
		std::cout << "ERROR: m_current_scene is null!\n" << std::endl;
		return;
	}

	// Calculate new positions
	physicsUpdate(delta);

	for (std::shared_ptr<GameObject> gameObject : m_current_scene->getGameObjects())
	{ 
		if (gameObject->should_delete())
		{
			m_current_scene->delete_object(gameObject);
			continue;
		}
		gameObject->update(delta);
	}

	// Draw Frame
	graphicsUpdate(delta);

}

void Engine::physicsUpdate(double delta)
{
	Physics::updatePhysicsObjects(m_current_scene->getGameObjects(), delta);
	Physics::processExternalForces(m_current_scene->getGameObjects(), delta);
	Physics::processCollisions(m_current_scene->getGameObjects());
}

void Engine::graphicsUpdate(double delta)
{
	// Draw viewport

	// Frame corresponds to the frame to be rendered, not just the "picture frame" outline of the viewport
	// We do, however, use the viewport outline as a starting point
	std::vector<std::string> frame = this->m_viewport.getVisual();
	moveCursorUp(frame.size() + 2);

	// // Due to z-sorting, this loop should automatically iterate back-to-front

	if (!this->m_game) {
		std::cout << "ERROR: game is null!\n" << std::endl;
		return;
	}

	if (!m_current_scene) {
		std::cout << "ERROR: currentScene is null!\n" << std::endl;
		return;
	}

	for (std::shared_ptr<GameObject> gameObject : m_current_scene->get_scene_data()->m_game_objects)
	{
		debug_log << "engine graphics update" << std::endl;

		
		if (gameObject->get_mesh().has_value())
		{
			std::shared_ptr<Mesh> obj_mesh = gameObject->get_mesh().value();
			// std::cout << "Attempting to get mesh" << std::endl;
			std::vector<std::string> mesh = obj_mesh->get_current_sprite(delta);
			if (printMesh) 
			{
				for (std::string line : mesh)
				{
					debug_log << line << std::endl;
				}
				printMesh = false;
			}
			// std::cout << "Got visual: " << mesh[0] << std::endl;

			// Calculate which parts of the mesh are on screen
			int y_size = obj_mesh->get_size().y;
			int x_size = obj_mesh->get_size().x;

			int y_pos;
			int x_pos;
			Position obj_pos = gameObject->get_position();
			if (obj_pos.valid)
			{
				y_pos = obj_pos.y;
				x_pos = obj_pos.x;
			}
			else
			{
				continue;
			}

			debug_log << "engine graphics update: about to print" << std::endl;
			debug_log << "x,y = " << x_pos << ", " << y_pos << std::endl;
			debug_log << "x,y size = " << x_size << ", " << y_size << std::endl;

			// Replace lines of screen with mesh
			// We need some kind of check here, or maybe in mesh to ensure that the size correctly reflects the size of the object
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
	std::cout << "Game objects in scene: " << m_current_scene->get_scene_data()->m_game_objects.size() << std::endl;
	// std::cout << "Filtered objects in scene: " << visualObjects.size() << std::endl;
	std::cout << "FPS: " << 1.0 / delta << std::endl;


}

void Engine::loadNewScene(std::shared_ptr<Scene> new_scene)
{
	// Old Scene Clean up (probably handled in Scene destructor??)

	m_current_scene = new_scene;
	for (std::shared_ptr<GameObject> gameObject : m_current_scene->get_scene_data()->m_game_objects)
	{
		debug_log << "Calling init on " << gameObject << std::endl;
		gameObject->setup();
		gameObject->init();
	}
}