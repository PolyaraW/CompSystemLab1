#include <iostream>
#include <Windows.h>
#include <fstream>
#include <string>
#include <map>

using namespace std;

int main()
{
	SetConsoleOutputCP(1251);
	while (true)
	{
		string filePath;
		cout << "Enter path of file to analyze (type q for exit): ";
		getline(cin, filePath);
		if (filePath == "q")
			break;

		ifstream ifs;
		ifs.open(filePath);
		if (!ifs.is_open())
		{
			cout << "File can't be analyzed!" << endl;
			continue;
		}

		map<char, int> chars;
		int symbolsCount = 0;
		double H = 0.0;
		for (char ch; ifs.get(ch); )
			++chars[ch], ++symbolsCount;

		cout << "Total count of symbols: " << symbolsCount << endl;

		cout << "Info about separate characters:" << endl;
		for (const auto& [symbol, count] : chars)
		{
			double probability = (double)count / symbolsCount;
			H -= probability * log2(probability);
			cout << "'" << symbol << "': Count = " << count << ", Probability = " << probability << endl;
		}

		cout << "Avarage entropy of the alphabet for text in file: " << H << " bits." << endl;

		cout << "Information content of the text in file: " << H * symbolsCount / 8 << " bytes." << endl;

		cout << "==============================================================" << endl;
	}
	return 0;
}