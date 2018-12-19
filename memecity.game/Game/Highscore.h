#ifndef _HIGHSCORE_H
#define _HIGHSCORE_H
#include <string>

struct Highscore
{
	int score;
	std::string name;

	Highscore() = default;
	Highscore(int score, std::string name)
		: score(score), name(name) {}


	std::string get_string() const
	{
		return name + " " + std::to_string(score);
	}
};

#endif