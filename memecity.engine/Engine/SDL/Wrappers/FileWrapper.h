#ifndef _RW_OPS_WRAPPER_H
#define _RW_OPS_WRAPPER_H
#include <algorithm>
#include <string>
#include <fstream>

namespace memecity::engine::sdl {


	class FileWrapper
	{
	private:
		std::string _file_name;
		std::string _buffer;

	public:

		FileWrapper() = default;

		FileWrapper(const char* file_name)
			: _file_name(file_name) {}

		~FileWrapper() {}

		const std::string read_file()
		{
			std::ifstream input_stream;
			input_stream.open(_file_name);

			if (input_stream.is_open() && input_stream.good())
			{
				while (std::getline(input_stream, _buffer))
				{

				}
				input_stream.close();
			}

			return _buffer;
		}

		void write(const std::string& content)
		{
			std::ofstream output_stream(_file_name);

			if (output_stream)
			{
				output_stream << content;
				output_stream.close();
			}
		}

		int get_lines()
		{
			std::ifstream input_stream;
			input_stream.open(_file_name);

			const auto amount_of_lines = std::count(std::istreambuf_iterator<char>(input_stream),
				std::istreambuf_iterator<char>(), '\n');

			input_stream.close();

			return amount_of_lines;
		}
	};
}
#endif