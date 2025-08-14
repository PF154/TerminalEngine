#pragma once

#include "../../include/components/CollisionObject.hpp"
#include "../../include/components/ComponentUtils.hpp"
#include "../../include/core/EventSystem/SignalEmitter.hpp"
#include "../../include/core/EventSystem/EventHandler.hpp"

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