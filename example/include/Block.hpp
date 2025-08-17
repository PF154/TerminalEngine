#pragma once

#include <components/GameObject.hpp>
#include <components/ComponentUtils.hpp>
#include <core/EventSystem/SignalEmitter.hpp>
#include <core/EventSystem/EventHandler.hpp>

#include <vector>
#include <string>
#include <memory>

class Block : public GameObject
{
	public:
		Block();
		virtual ~Block() = default;

		void setup() override;
		void init() override;
	private:
		void physicsProcess(double delta) override;

		std::shared_ptr<SignalEmitter> m_test_signal_emitter;


};