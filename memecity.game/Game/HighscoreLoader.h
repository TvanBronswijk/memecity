#pragma once
#include <vector>
#include "Highscore.h"

class HighscoreLoader
{
private:
	std::vector<Highscore> highscores;
public:
	void Load()
	{
		//todo: Load from file
		highscores.emplace_back(10, "Simon");
		highscores.emplace_back(11, "Yoeri");
	}

	void add_highscore(Highscore score)
	{
		highscores.push_back(score);
	}
	std::vector<Highscore> get_highscores() const
	{
		return highscores;
	}
};
