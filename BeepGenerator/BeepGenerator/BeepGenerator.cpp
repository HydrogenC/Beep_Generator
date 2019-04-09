#include "BGScriptReader.h"
#include <filesystem>

using namespace std::filesystem;

int wmain(int argc, Char* argv[])
{
	if (argc == 2) {
		sourceFile = argv[1];
		fin = IFStream(sourceFile);
	}
	else {
		wcout << L"File name: ";
		wcin >> sourceFile;
		fin = IFStream(sourceFile);
	}
	if (!exists(path(sourceFile))) {
		wcout << L"Failed: " << sourceFile << L" doesn't exist! " << endl;
	}
	else {
		String content;
		while (getline(fin, content)) {
			for (Command cmd : cmdList) {
				if (content.substr(0, cmd.Token.length()) == cmd.Token) {
					cmd.Execute(content.substr(cmd.Token.length()));
					break;
				}
			}
		}
		wcout << L"All finished, saved to " << outFile << L". " << endl;
	}
	Console(L"pause>nul");
	return 0;
}
