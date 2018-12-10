#pragma once
#include <vector>
#include <algorithm>
#include <functional>
#include "Highscore.h"

class HighscoreLoader
{
private:
	std::vector<Highscore> highscores;
	void sort()
	{
		std::sort(highscores.begin(), highscores.end(), [](const Highscore& lhs, const Highscore& rhs)
		{
			return lhs.score < rhs.score;
		});
	}

public:
	void Load()
	{
		//todo: Load from file
		highscores.emplace_back(10, "Simon");
		highscores.emplace_back(11, "Yoeri");
		highscores.emplace_back(19, "BLEEH");
		highscores.emplace_back(9, "BLAAH");
		sort();
	}

	void add_highscore(Highscore score)
	{
		highscores.emplace_back(score);
		sort();
	}

	std::vector<Highscore> get_highscores() const
	{
		return highscores;
	}


};
