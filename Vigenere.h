#pragma once

#include <vector>
#include <fstream>
#include <string>


class Vigenere
{
public:
	Vigenere(const std::string filepathCipheredText);
	~Vigenere();

	void Init();
	void decrypt(const std::string key);


private:
	const std::string filepathCipheredText;
	std::fstream fileOutput;
	std::vector<std::vector<char>> tab;
};

