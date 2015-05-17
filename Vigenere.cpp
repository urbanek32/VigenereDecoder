#include "Vigenere.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <cctype>


Vigenere::Vigenere(const std::string filepathCT) : tab(26, std::vector<char>(26)),
fileOutput("output.txt", std::ios::app),
filepathCipheredText(filepathCT)
{
	
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
		
}

void Vigenere::decrypt(const std::string key)
{
	size_t keyIndex = 0, col = 0, row = 0;;
	std::string str, coded;
	
	int controlIndex = 0;


	fileOutput << "[" << key << "] "; // add key before decoded string
	std::fstream fileCipheredText(filepathCipheredText, std::ios::in);
	while (fileCipheredText >> str) // every word
	{
		coded.clear(); // reset output word

		for (size_t i = 0; i < str.length(); i++) // every char in word
		{
			col = row = 500; // reset vars
			controlIndex++;

			str[i] = std::toupper(str[i]);

			// find correct row in table
			for (size_t pos_row = 0; pos_row < tab.size(); pos_row++)
			{
				
				if (tab[pos_row][0] == key[keyIndex%key.length()])
				{
					row = pos_row;
					break;
				}
			}
			
			// in found row find correct column
			for (size_t pos_col = 0; pos_col < tab[row].size(); pos_col++)
			{
				if (tab[row][pos_col] == str[i])
				{
					col = pos_col;
					break;
				}
			}

			// read orginally char in found column
			if (col <= 26 && row <= 26)
			{
				coded += tab[0][col];
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
			//break;
		}
	}
	fileOutput << "\n";
	fileCipheredText.close();
}