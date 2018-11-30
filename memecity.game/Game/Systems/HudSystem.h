#ifndef HUDSYSTEM_H
#define HUDSYSTEM_H

#include <ECS.h>
#include "../Event/HealthChangedArgs.h"
#include "UI/Overlay/Overlay.h"

class HudSystem : public memecity::engine::ecs::System
{
public:
	HudSystem(memecity::engine::ui::overlay::Overlay& overlay):_hud(&overlay)
	{
		//_hud = nullptr;
	}
	void on_health_changed(memecity::engine::ecs::EntityManager& em, HealthChangedEventArgs args) ;
	void run(memecity::engine::ecs::EntityManager& em) const override;
private:
	memecity::engine::ui::overlay::Overlay* _hud;
};
#endif // HUDSYSTEM_H
