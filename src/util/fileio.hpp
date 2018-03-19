
#include <string>
#include <fstream>
#include <sstream>


namespace util {
		
	std::string read_file(const std::string& filename)
	{
			// TODO: fixme
			std::fstream file;
			file.open(filename);
			std::stringstream str_stream;
			if (file.good()) {
				std::string line;
				while (getline(file, line, '\n')) {
					str_stream << line;
				}
			}
			//str_stream << file.rdbuf();
			file.close();
			return str_stream.str();
	}


	/*
	std::string DecToBin(int number)
	{
		if ( number == 0 ) return "0";
		if ( number == 1 ) return "1";

		if ( number % 2 == 0 )
			return DecToBin(number / 2) + "0";
		else
			return DecToBin(number / 2) + "1";
	}

	int BinToDec(string number)
	{
		int result = 0, pow = 1;
		for ( int i = number.length() - 1; i >= 0; --i, pow <<= 1 )
			result += (number[i] - '0') * pow;

		return result;
	}
	*/
}