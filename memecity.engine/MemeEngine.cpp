#include "MemeEngine.h"
#include "ExampleGuy.h"
#include "SerializationFacade.h"

MemeEngine::MemeEngine()
{

	multimedia_manager = std::make_shared<MultimediaManager>(false);
	input_manager = std::make_unique<InputManager>();
	timer = std::make_unique<TimerFacade>();

}


int MemeEngine::run()
{
	auto guy = example_guy();

	guy.age = 5;
	guy.name = "bob";
	guy.friends = true;
	guy.money = 5.5;
	auto tomap = guy.to_map();
	SerializationFacade serialization = SerializationFacade();
	auto serialized = serialization.serialize(tomap);
	guy = example_guy();

	auto deserialize = serialization.deserialize(serialized);
	guy.from_map(deserialize);



	if (init()) {
		while (!input_manager->is_quit_pressed())
		{
			handle();
		}
		return 0;
	}
	return 1;
}



