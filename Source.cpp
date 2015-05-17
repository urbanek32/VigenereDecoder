#include <iostream>
#include <fstream>
#include <string>

#include "Vigenere.h"




int main(int _Argc, char ** _Argv)
{
	Vigenere *vig = new Vigenere("textToDecode.txt");
	vig->Init();

	std::string keyPhrase;
	size_t counter = 0;

	std::fstream keys("keys.txt", std::ios::in);
	while (keys >> keyPhrase)
	{
		vig->decrypt(keyPhrase);

		counter++;
		if (counter%10000 == 0)
		{
			printf("%d ", counter);
		}
	}
	keys.close();

	delete vig;
	//system("pause");
	return 0;
}