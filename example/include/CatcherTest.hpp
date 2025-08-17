
#include <components/GameObject.hpp>
#include <core/EventSystem/Signal.hpp>

#include <memory>

class CatcherTest : public GameObject
{
	public:
		CatcherTest ();

		void setup() override;

	private:
		void send_debug_message();
};