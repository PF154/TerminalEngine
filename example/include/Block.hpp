#pragma once

#include <components/CollisionObject.hpp>
#include <components/ComponentUtils.hpp>
#include <core/EventSystem/SignalEmitter.hpp>
#include <core/EventSystem/EventHandler.hpp>

#include <vector>
#include <string>
#include <memory>

class Block : public CollisionObject
{
	public:
		Block();
		virtual ~Block() = default;

		std::vector<std::string> getVisual() override;

		void init() override;
	private:
		void physicsProcess(double delta) override;

		std::vector<std::vector<std::string>*> sprites;
		std::vector<std::string>* currentSprite;

		std::shared_ptr<SignalEmitter> m_test_signal_emitter;


};