#include "StorageManager.h"
#include <fstream>
#include <algorithm>
#include <iostream>

namespace memecity::engine
{
	bool StorageManager::save(const std::string& file_path, serialization::SerializeInfo data) const
	{
		try
		{
			std::ofstream output_stream(file_path);
			if (output_stream)
			{
				std::for_each(data.begin(), data.end(),
				              [&](const std::pair<std::string, std::string> pair)
				              {
					              output_stream << pair.first << ":" << pair.second << "\n";
				              });
				output_stream.close();
			}
		}
		catch (std::exception& exception)
		{
			std::cout << exception.what() << "\n";
			return false;
		}

		return true;
	}

	serialization::SerializeInfo StorageManager::load(const std::string& file_path) const
	{
		serialization::SerializeInfo result;

		try
		{
			std::ifstream input_stream;
			input_stream.open(file_path);

			if (input_stream.is_open() && input_stream.good())
			{
				std::string line;
				while (std::getline(input_stream, line))
				{
					auto key = line.substr(0, line.find(':'));
					const auto value = line.substr(line.find(':') + 1);
					result[key] = value;

					std::cout << "Key: " << key << ", value: " << value << "\n";
				}

				input_stream.close();
			}
		}
		catch (std::exception& exception)
		{
			std::cout << exception.what() << "\n";
		}

		return result;
	}
}
