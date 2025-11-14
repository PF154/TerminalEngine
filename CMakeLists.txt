cmake_minimum_required(VERSION 3.14)

project(TerminalEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

include_directories(include)


add_executable(TerminalEngine
    src/main.cpp
    src/core/Engine.cpp
	src/core/Game.cpp
    src/core/Scene.cpp
	src/core/EventSystem/EventHandler.cpp
	src/core/EventSystem/SignalEmitter.cpp
	src/core/EventSystem/SignalCatcher.cpp
	src/utils/TerminalTools.cpp
	src/utils/Timer.cpp
	src/components/Viewport.cpp
	src/components/GameObject.cpp
	src/physics/PhysicsEngine.cpp
	src/input/Input.cpp
	example/src/Block.cpp
	example/src/StaticBlock.cpp
	example/src/CatcherTest.cpp
	example/src/BlockSpawner.cpp
)

target_include_directories(TerminalEngine PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

target_link_libraries(TerminalEngine PRIVATE ${CURSES_LIBRARIES})