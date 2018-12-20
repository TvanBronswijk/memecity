#include "FileStrategy.h"
#include "../../CityGenerator.h"

generate::models::City generate::strategy::FileStrategy::generate(int w, int h)
{
	w = h = 0;
	for (char item : map_string)
	{
		if (item == '\n')
		{
			h++;
		}
		else if (h == 0)
		{
			w++;
		}
	}
	models::City city(w, h);
	city.start.x = 5;
	city.start.y = 5;
	int x = 0;
	int y = 0;
	for (char item : map_string)
	{
		if (item != '\n')
		{
			city.tiles(x, y) = item;
		}
		if (item == '\n')
		{
			y++;
			x = 0;
		}
		else
		{
			x++;			
		}

	}

	return city;
}
