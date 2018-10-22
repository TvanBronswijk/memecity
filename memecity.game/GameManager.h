#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H
#include "MemeEngine.h"
#include "CityGenerator.h"

class GameManager : public MemeEngine 
{
private:
	std::unique_ptr<CityGenerator> city_generator;
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Texture> text;

protected:
	bool init() override;
	void handle() override;

};


#endif