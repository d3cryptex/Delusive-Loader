#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>
#include <vector>
#include <TlHelp32.h>
#include <thread>
#include <chrono>
#include <conio.h>
#include <WinInet.h>
#include <urlmon.h>
#include <Psapi.h>
#include <direct.h>
#include <stdio.h>
#include <objbase.h>
#include <mmsystem.h>
#include <mmdeviceapi.h>
#include <endpointvolume.h>
#include <unordered_map>

#include "xorstr.hpp"
#include "Lazyimporter.hpp"

#pragma comment(lib, "WinInet.lib")
#pragma comment(lib, "urlmon.lib") 
#pragma comment(lib, "psapi.lib") 
#pragma comment(lib, "winmm.lib")

#include "Inject.hpp"
#include "UI.hpp"
#include "Security.hpp"

#define DLLPATH "C:\\Delusive\\Loader\\Dlls\\delusiveDevblog236.dll"

#define VERSION "v1.0"
#define GETVERSION "https://pastebin.com/raw/Wu6UUSgQ"
#define GETSTATUS "https://pastebin.com/raw/UgBLCE8Q"
#define GETUPDATE "https://pastebin.com/raw/AKu7VtX1"

