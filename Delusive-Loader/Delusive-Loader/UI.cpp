#include "Include.hpp"
#include "UI.hpp"

namespace Loader {
    Engine_UI UI;
}

static const char rundomword[] = "0123456789" "qwertyuiopasdfghjklzxcvbnm" "QWERTYUIOPASDFGHJKLZXCVBNM";
int Length = sizeof(rundomword) - 1;

auto Engine_UI::SetColor(ConsoleColor text, ConsoleColor background) -> void
{
    HANDLE hwnd = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hwnd, (WORD)((background << 4) | text));
}

auto Engine_UI::WindowSize(SHORT x, SHORT y) -> void
{
    HWND hWindowConsole = GetConsoleWindow();
    RECT r;
    GetWindowRect(hWindowConsole, &r);
    MoveWindow(hWindowConsole, r.left, r.top, x, y, TRUE);
}

auto Engine_UI::GetRandom() -> char
{
    return rundomword[rand() % Length];
}

auto Engine_UI::SetTitle(std::string title) -> void
{
    srand(static_cast<unsigned int>(time(nullptr)));
    for (unsigned int i = 0; i < 40; ++i) {
        title += GetRandom();
    }

    std::wstring wideTitle(title.begin(), title.end());

    SetConsoleTitle(wideTitle.c_str());
}