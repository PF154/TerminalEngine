cmake_minimum_required(VERSION 3.14)

project(TerminalEngine)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

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
	src/components/Viewport.cpp
	src/components/GameObject.cpp
	src/components/CollisionObject.cpp
	src/components/VisualObject.cpp
	example/src/Block.cpp
	example/src/CatcherTest.cpp
)