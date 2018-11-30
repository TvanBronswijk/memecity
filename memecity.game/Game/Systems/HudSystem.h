#ifndef HUDSYSTEM_H
#define HUDSYSTEM_H

#include <ECS.h>
#include "../Event/HealthChangedArgs.h"
class Overlay;

class HudSystem : public memecity::engine::ecs::System
{
public:
	HudSystem()
	{
		//_hud = nullptr;
	}
	void on_health_changed(memecity::engine::ecs::EntityManager& em, HealthChangedEventArgs args) ;
	void run(memecity::engine::ecs::EntityManager& em) const override;
	//void set_hud(memecity::engine::ui::overlay::Overlay& overlay) { _hud = &overlay; }
private:
	Overlay* _hud;
};
#endif // HUDSYSTEM_H
