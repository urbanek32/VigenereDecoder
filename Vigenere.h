#pragma once

#include <vector>
#include <fstream>
#include <string>


class Vigenere
{
public:
	Vigenere();
	~Vigenere();

	void Init();
	void decrypt(const std::string key);


private:
	std::fstream fileOutput;
	std::vector<std::vector<char>> tab;
};

