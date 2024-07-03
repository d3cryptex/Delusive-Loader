#pragma once

enum ConsoleColor
{
    Black = 0,
    Blue = 1,
    Green = 2,
    Cyan = 3,
    Red = 4,
    Magenta = 5,
    Brown = 6,
    LightGray = 7,
    DarkGray = 8,
    LightBlue = 9,
    LightGreen = 10,
    LightCyan = 11,
    LightRed = 12,
    LightMagenta = 13,
    Yellow = 14,
    White = 15
};

class Engine_UI
{
public:
    auto SetColor(ConsoleColor text, ConsoleColor background) -> void;
    auto WindowSize(SHORT x, SHORT y) -> void;
    auto GetRandom() -> char;
    auto SetTitle(std::string title) -> void;
};

namespace Loader {
    extern Engine_UI UI;
}