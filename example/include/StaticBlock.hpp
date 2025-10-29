#pragma once

#include <components/GameObject.hpp>
#include <components/ComponentUtils.hpp>
#include <core/EventSystem/SignalEmitter.hpp>
#include <core/EventSystem/EventHandler.hpp>

#include <vector>
#include <string>
#include <memory>

class StaticBlock : public GameObject
{
	public:
		StaticBlock();
		virtual ~StaticBlock() = default;

		void setup() override;
		void init() override;
	private:
		void physicsProcess(double delta) override;

		std::shared_ptr<SignalEmitter> m_test_signal_emitter;


};