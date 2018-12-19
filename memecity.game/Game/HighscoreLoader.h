#pragma once
#include <vector>
#include <algorithm>
#include "Highscore.h"

class HighscoreLoader
{
private:
	std::vector<Highscore> highscores;
	void sort()
	{
		std::sort(highscores.begin(), highscores.end(), [](const Highscore& lhs, const Highscore& rhs)
		{
			return lhs.score > rhs.score;
		});
	}

	void clip()
	{
		highscores.resize(10);
	}

public:
	void Load(memecity::engine::serialization::SerializeInfo& data)
	{
		std::for_each(data.begin(), data.end(), [&](const std::pair<std::string, std::string> pair)
		{
			auto key = pair.first;
			const auto component = std::string(key.substr(0, key.find(':')));
			key = key.substr(key.find(':') + 1, key.find('='));
			const auto value = std::string(pair.second);

			highscores.emplace_back(std::stoi(value), key);
		});
		sort();
		clip();
	}

	void add_highscore(Highscore score)
	{
		highscores.emplace_back(score);
		sort();
		clip();
	}

	std::vector<Highscore> get_highscores() const
	{
		return highscores;
	}


};
