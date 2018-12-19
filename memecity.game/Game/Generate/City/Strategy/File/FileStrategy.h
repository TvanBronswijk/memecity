#ifndef _FILE_STRATEGY_H
#define _FILE_STRATEGY_H
#include "../Strategy.h"
#include <memory>

namespace generate::strategy {
	class FileStrategy : public Strategy
	{
	private:
		std::string map_string;
	public:
		FileStrategy(std::string map) 
			: map_string(map) {}

		models::City generate(int w, int h) override;

	};
}
#endif

