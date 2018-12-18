#include "StorageManager.h"
#include <fstream>
#include <algorithm>
#include <iostream>
#include <SDL.h>

namespace memecity::engine
{
	bool StorageManager::save(const std::string& file_path, serialization::SerializeInfo data) const
	{
		std::string text;

		try
		{
			std::for_each(data.begin(), data.end(),
              [&](const std::pair<std::string, std::string> pair)
              {
	              text += pair.first + "=" + pair.second + "\n";
              });
		
		}
		catch (std::exception& exception)
		{
			std::cout << exception.what() << "\n";
			return false;
		}

		return save_string(file_path, text);
	}



	bool StorageManager::save_string(const std::string& file_path, std::string data) const
	{
		try
		{
			std::string full_path = SDL_GetBasePath();
			full_path += "\\" + file_path;
			std::ofstream output_stream(full_path);
			if (output_stream)
			{			
				output_stream << data;
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
			std::string full_path = SDL_GetBasePath();
			full_path += "\\" + file_path;
			std::ifstream input_stream;
			input_stream.open(full_path);

			if (input_stream.is_open() && input_stream.good())
			{
				std::string line;
				while (std::getline(input_stream, line))
				{
					auto key = line.substr(0, line.find('='));
					const auto value = line.substr(line.find('=') + 1);
					result[key] = value;
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

	std::string StorageManager::load_string(const std::string& file_path) const
	{
		std::string result;

		try
		{
			std::string full_path = SDL_GetBasePath();
			full_path += "\\" + file_path;
			std::ifstream input_stream;
			input_stream.open(full_path);

			if (input_stream.is_open() && input_stream.good())
			{
				std::string line;
				while (std::getline(input_stream, line))
				{
					result += line + '\n';
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

