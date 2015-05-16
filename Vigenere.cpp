#include "Vigenere.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>


Vigenere::Vigenere() : tab(26, std::vector<char>(26)), fileOutput("output.txt", std::ios::app)
{
	/*for (size_t i = 0; i < tab.size(); i++)
	{
		for (size_t j = 0; j < tab[i].size(); j++)
		{
			tab[i][j] = '-';
		}
	}*/

}


Vigenere::~Vigenere()
{
	if (fileOutput.is_open())
	{
		fileOutput.close();
	}

	for (size_t i = 0; i < tab.size(); i++)
	{
		tab[i].clear();
	}
	tab.clear();
}

void Vigenere::Init()
{
	// read orginally alphabet into vector
	std::fstream file("alphabet.txt", std::ios::in);
	for (size_t i = 0; i < tab.size(); i++)
	{
		file >> tab[0][i]; // read every char into vector
		tab[0][i] = std::toupper(tab[0][i]);
	}
	file.close();

	// fill table with shifted alphabet
	for (size_t i = 1; i < tab.size(); i++)
	{
		tab[i] = tab[0]; // duplicate row with first row
		std::rotate(tab[i].begin(), tab[i].begin() + i, tab[i].end()); // shift left current row
	}
	


	
	/*for (size_t i = 0; i < tab.size(); i++)
	{
		for (size_t j = 0; j < tab[i].size(); j++)
		{
			printf("%c ", tab[i][j]);
		}
		printf("\n");
	}
	printf("\n\n");*/
	
}

void Vigenere::decrypt(const std::string key)
{
	size_t keyIndex = 0, col = 0, row = 0;;
	char c = '-';
	std::string str, coded;
	
	int controlIndex = 0;


	fileOutput << "[" << key << "] "; // add key before decoded string
	std::fstream filePlainText("szyfr.txt", std::ios::in);
	while (filePlainText >> str) // every word
	{
		coded.clear(); // reset output word
		keyIndex = 0; // reset index of key word

		for (size_t i = 0; i < str.length(); i++) // every char in word
		{
			controlIndex++;

			str[i] = std::toupper(str[i]);
			col = str[i] - 65;
			row = key[keyIndex%key.length()] - 65;
			if (col >= 0 && col <= 26 && row >= 0 && row <= 26)
			{
				coded += tab[col][row];
				keyIndex++;
			} 
			else
			{
				coded += str[i];
			}
		}
		//printf("%s \n", coded.c_str());
		fileOutput << coded << " ";

		// process only 100 chars
		if (controlIndex > 100)
		{
			controlIndex = 0;
			break;
		}
	}
	fileOutput << "\n";
	filePlainText.close();
}