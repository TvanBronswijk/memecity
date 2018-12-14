#ifndef _ITEMGENERATOR_H
#define  _ITEMGENERATOR_H
#include <ECS.h>
#include <Engine\MultimediaManager.h>
namespace generate {
	class ItemGenerator {
	private:
		memecity::engine::MultimediaManager& multimedia_manager;
		memecity::engine::ecs::EntityManager& entity_manager;
	public:
		void MakeAllItems();

		ItemGenerator(
			memecity::engine::MultimediaManager& multimedia_manager, memecity::engine::ecs::EntityManager& entity_manager) :
			entity_manager(entity_manager), multimedia_manager(multimedia_manager) {}
	};
}

#endif

