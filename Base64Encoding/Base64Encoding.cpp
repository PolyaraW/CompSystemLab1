#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
	char base64Set[64];
	for (int i = 0; i < 26; ++i)
		base64Set[i] = 'A' + i;
	for (int i = 26; i < 52; ++i)
		base64Set[i] = 'a' + i - 26;
	for (int i = 52; i < 62; ++i)
		base64Set[i] = '0' + i - 52;
	base64Set[62] = '+';
	base64Set[63] = '/';

	while (true)
	{
		string originalFilePath, encodedFilePath;
		cout << "Enter path to save result (type q for exit): ";
		getline(cin, originalFilePath);
		if (originalFilePath == "q")
			break;


		ifstream ifs;
		ifs.open(originalFilePath, ios::binary);
		if (!ifs.is_open())
		{
			cout << "Invalid file path!" << endl;
			continue;
		}

		cout << "Enter path to save the encoded file: ";
		getline(cin, encodedFilePath);

		ofstream ofs;
		ofs.open(encodedFilePath);
		if (!ofs.is_open())
		{
			cout << "Invalid file path" << endl;
			continue;
		}

		int previousBits = 0;
		char currentSymbol, previousSymbol;
		for (; ifs.read(&currentSymbol, 1); previousSymbol = currentSymbol)
		{
			switch (previousBits)
			{
				case 0:
					ofs.put(base64Set[(currentSymbol & 252) >> 2]);
					previousBits = 2;
					break;
				case 2:
					ofs.put(base64Set[((previousSymbol & 3) << 4) | ((currentSymbol & 240) >> 4)]);
					previousBits = 4;
					break;
				case 4:
					ofs.put(base64Set[((previousSymbol & 15) << 2) | ((currentSymbol & 192) >> 6)]);
					ofs.put(base64Set[currentSymbol & 63]);
					previousBits = 0;
					break;
			}
		}


		if (previousBits == 2)
		{
			ofs.put(base64Set[(previousSymbol & 3) << 4]);
			ofs.write("==", 2);
		}
		else if (previousBits == 4)
		{
			ofs.put(base64Set[(previousSymbol & 15) << 2]);
			ofs.put('=');
		}

		cout << "File was encoded successfully." << endl;
		cout << "=======================================" << endl;
	}
	return 0;
}