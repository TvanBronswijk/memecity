#ifndef _GAME_MANAGER_H
#define _GAME_MANAGER_H
#include "MemeEngine.h"

class GameManager : public MemeEngine 
{
private:
	std::shared_ptr<Texture> texture;
	std::shared_ptr<Texture> text;

protected:
	bool Init() override;
	void Handle() override;

};


#endif