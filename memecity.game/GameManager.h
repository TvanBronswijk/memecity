#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H
#include "MemeEngine.h"
#include "../memecity.engine.ecs/EntityManager.h"

class GameManager : public MemeEngine 
{
private:
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Texture> text;
	EntityManager em;

protected:
	bool init() override;
	void handle() override;
};


#endif