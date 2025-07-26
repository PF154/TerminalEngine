#include "../../include/components/GameObject.hpp"

#include <string>
#include <chrono>
#include <iostream>

class DummyObject : public GameObject
{
	public:
		DummyObject();
		~DummyObject();
	private:
		void process(double delta) override;
		
		std::chrono::duration<double> total_time_elapsed = std::chrono::duration<double>(0.0);

};

DummyObject::DummyObject()
{
	this->total_time_elapsed = std::chrono::duration<double>(0.0);
}

DummyObject::~DummyObject()
{
	std::cout << total_time_elapsed.count() << std::endl;
}

void DummyObject::process(double delta)
{
	total_time_elapsed += std::chrono::duration<double>(delta);
}

