#include "../memecity.engine.ecs/System.h"
#include "../memecity.engine.ecs/EntityManager.h"
#include <cstdlib>
#include "InteractionEventArgs.h"
#include "InteractionEvent.h"
#include "PositionComponent.h"
#include "interactionComponent.h"
#include "../memecity.engine/MultimediaManager.h"

class InteractionSystem : public System {

	static std::string SYSTEM_TYPE;

private:
	std::weak_ptr<MultimediaManager> multimedia_manager;
public:
	InteractionSystem(std::weak_ptr<MultimediaManager> multimedia_manager);
	std::string get_type() override;
	void run(EntityManager &em) override;
	void run(EntityManager &em, EventArgs& e) override;
};
