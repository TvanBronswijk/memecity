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
	std::unique_ptr<City> city;

protected:
	bool Init() override;
	void Handle() override;

};


#endif