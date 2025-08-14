
#include "../../include/components/GameObject.hpp"
#include "../../include/core/EventSystem/Signal.hpp"

#include <memory>

class CatcherTest : public GameObject
{
	public:
		CatcherTest ();

		void init() override;


	private:
		void send_debug_message();
};