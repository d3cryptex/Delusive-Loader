#include "Include.hpp"
using namespace std;

HANDLE hProc;
std::string Title;
LPCWSTR dll_path = L"C:\\Delusive\\Loader\\Dlls\\delusiveDevblog236.dll";
LPCWSTR dll_link = L"https://raw.githubusercontent.com/6275SeNpai/Delusive-Dlls/main/Devblog236.dll";
int menu, submenu, spoofer, inject;

bool findtext(const std::string filename, const std::string word)
{
    std::ifstream file(filename);
    std::string tmp;
    while (file >> tmp)
    {
        if (word == tmp)
            return true;
    }
    return false;
}

string trim(const string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

string replaceAll(string str, const string& from, const string& to) {
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length();
    }
    return str;
}

string removeInvisibleCharacters(const string& str) {
    string result;
    for (char c : str) {
        if (!iscntrl(c) || c == '\n' || c == '\r') {
            result += c;
        }
    }
    return result;
}

string DownloadString(string URL) {
    HINTERNET interwebs = InternetOpenA(xorstr_("Mozilla/5.0"), INTERNET_OPEN_TYPE_DIRECT, NULL, NULL, NULL);
    HINTERNET urlFile;
    string rtn;
    if (interwebs) {
        urlFile = InternetOpenUrlA(interwebs, URL.c_str(), NULL, NULL, NULL, NULL);
        if (urlFile) {
            char buffer[2000];
            DWORD bytesRead;
            do {
                InternetReadFile(urlFile, buffer, 2000, &bytesRead);
                rtn.append(buffer, bytesRead);
                memset(buffer, 0, 2000);
            } while (bytesRead);
            InternetCloseHandle(urlFile);
        }
        InternetCloseHandle(interwebs);
    }
    rtn = replaceAll(rtn, xorstr_("|n"), "\r\n");
    rtn = trim(rtn);
    rtn = removeInvisibleCharacters(rtn);
    return rtn;
}

vector<string> splitString(const string& str, char delimiter) {
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter)) {
        tokens.push_back(token);
    }
    return tokens;
}

unordered_map<string, string> parseJSON(const string& jsonString) {
    unordered_map<string, string> result;
    size_t start = 0, end = 0;

    while ((start = jsonString.find('"', start)) != string::npos) {
        end = jsonString.find('"', start + 1);
        string key = jsonString.substr(start + 1, end - start - 1);

        start = jsonString.find(':', end) + 1;
        start = jsonString.find('"', start) + 1;
        end = jsonString.find('"', start);
        string value = jsonString.substr(start, end - start);

        result[key] = value;
        start = end + 1;
    }

    return result;
}

string getFromPaste(int number, string content) {
    string pasteContent = DownloadString(content);
    unordered_map<string, string> statusMap = parseJSON(pasteContent);

    if (number == 1 && statusMap.find(xorstr_("devblog236")) != statusMap.end()) {
        return statusMap[xorstr_("devblog236")];
    }
    else if (number == 2 && statusMap.find(xorstr_("alkad")) != statusMap.end()) {
        return statusMap[xorstr_("alkad")];
    }
    return "";
}

bool IsRunAsAdmin()
{
    BOOL isAdmin = FALSE;
    HANDLE hToken = NULL;
    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken))
    {
        TOKEN_ELEVATION elevation;
        DWORD size = sizeof(TOKEN_ELEVATION);
        if (GetTokenInformation(hToken, TokenElevation, &elevation, sizeof(elevation), &size))
        {
            isAdmin = elevation.TokenIsElevated;
        }
    }
    if (hToken)
    {
        CloseHandle(hToken);
    }
    return isAdmin != 0;
}

auto AdminCheck() -> void
{
    if (!IsRunAsAdmin())
    {
        Loader::UI.SetColor(Red, Black);
        std::cout << xorstr_("[+] The program is not running as administrator") << std::endl;
        this_thread::sleep_for(chrono::seconds(1));
        exit(1);
    }
    else {
        system(xorstr_("cls"));
    }
}

void SetVolume(int volume) {
    DWORD dwVolume = ((DWORD)volume << 16) | (DWORD)volume;
    waveOutSetVolume(0, dwVolume);
}

void PlayMusic() {
    if (GetFileAttributes(L"C:\\Delusive\\Loader\\Sounds\\sound.wav") == INVALID_FILE_ATTRIBUTES) {
        return;
    }
    else {
        PlaySound(L"C:\\Delusive\\Loader\\Sounds\\sound.wav", NULL, SND_LOOP | SND_ASYNC);
    }
}

auto Version() -> void 
{
    Loader::UI.SetColor(White, Black);
    cout << xorstr_("[?] Checking Version..") << endl;
    this_thread::sleep_for(chrono::seconds(1));

    if (VERSION != DownloadString(GETVERSION))
    {
        Loader::UI.SetColor(Red, Black);
        cout << xorstr_("[-] Download New Version!") << endl;
        this_thread::sleep_for(chrono::seconds(2));
        exit(1);
    }
    else {
        Loader::UI.SetColor(Green, Black);
        cout << xorstr_("[+] Version Correct") << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
    system(xorstr_("cls"));
}

void Status() {
    string statusLine = getFromPaste(submenu, GETSTATUS);
    statusLine = trim(statusLine);
    if (statusLine == xorstr_("Undetect")) {
        Loader::UI.SetColor(Green, Black);
        cout << xorstr_("Undetect") << endl;
        Loader::UI.SetColor(White, Black);
    }
    else if (statusLine == xorstr_("Detect")) {
        Loader::UI.SetColor(Red, Black);
        cout << xorstr_("Detect") << endl;
        Loader::UI.SetColor(White, Black);
    }
    else if (statusLine == xorstr_("UseAtOwnRisk")) {
        Loader::UI.SetColor(Yellow, Black);
        cout << xorstr_("Use At Own Risk") << endl;
        Loader::UI.SetColor(White, Black);
    }
    else {
        Loader::UI.SetColor(White, Black);
        cout << xorstr_("Unknown status") << endl;
    }
}

auto Update() -> void
{
    string updateContent = getFromPaste(submenu, GETUPDATE);
    updateContent = trim(updateContent);
    Loader::UI.SetColor(White, Black);
    cout << updateContent << endl;
}

auto Loading(int const sec) -> void 
{
    for (size_t i = 0; i < sec; i++)
    {
        Loader::UI.SetColor(Green, Black);
        cout << xorstr_("Loading.");
        this_thread::sleep_for(chrono::seconds(1));
        cout << xorstr_(".");
        this_thread::sleep_for(chrono::seconds(1));
        cout << xorstr_(".") << endl;
        this_thread::sleep_for(chrono::seconds(1));
        system(xorstr_("cls"));
    }
}

auto Download() -> void 
{
    Loader::UI.SetColor(White, Black);
    cout << xorstr_("[?] Downloading dlls..") << endl;

    HRESULT resultDownload = URLDownloadToFile(NULL, dll_link, dll_path, 0, NULL);
    this_thread::sleep_for(chrono::seconds(1));

    if (resultDownload == S_OK)
    {
        Loader::UI.SetColor(Green, Black);
        cout << xorstr_("[+] Succesfully downloaded") << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
    else {
        Loader::UI.SetColor(Red, Black);
        cout << xorstr_("[-] Download Error!") << endl;
        this_thread::sleep_for(chrono::seconds(2));
    }
    system("cls");
}

auto InjectProcess() -> void
{
    Loading(2);

    HANDLE hProc = nullptr;

    PROCESSENTRY32 entry;
    entry.dwSize = sizeof(PROCESSENTRY32);

    while (true)
    {
        HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);

        if (Process32First(snapshot, &entry) == TRUE)
        {
            do
            {
                if (_wcsicmp(entry.szExeFile, xorstr_(L"RustClient.exe")) == 0)
                {
                    hProc = OpenProcess(PROCESS_ALL_ACCESS, TRUE, entry.th32ProcessID);
                    break;
                }
            } while (Process32Next(snapshot, &entry) == TRUE);
        }

        CloseHandle(snapshot);

        if (hProc)
            break;

        Loader::UI.SetColor(Yellow, Black);
        std::wcout << xorstr_(L"[-] RustClient.exe not found. Waiting for the game to start...") << std::endl;
        this_thread::sleep_for(chrono::seconds(2));
    }

    if (!hProc || hProc == INVALID_HANDLE_VALUE)
    {
        Loader::UI.SetColor(Red, Black);
        std::cout << xorstr_("[-] Failed to open RustClient.exe process.") << std::endl;
        exit(1);
    }

    if (Inject(DLLPATH, hProc))
    {
        Loader::UI.SetColor(Red, Black);
        std::cout << xorstr_("[-] Injection Error. Please try again.") << std::endl;
    }
    else
    {
        Loader::UI.SetColor(Green, Black);
        std::cout << xorstr_("[+] Successfully Injected!") << std::endl;
    }

    CloseHandle(hProc);
    this_thread::sleep_for(chrono::seconds(2));
    exit(0);
}

//tabs
auto CheatTab1() -> void 
{
    do {
        system("cls");
        Loader::UI.SetColor(Yellow, Black);
        cout << "Rust Devblog 236" << endl;
        Loader::UI.SetColor(White, Black);
        cout << endl;
        cout << "Status: "; Status();
        cout << "Last Update: "; Update();
        cout << "Rust Version: Devblog 236" << endl;
        cout << endl;
        cout << "[1] - Inject Cheat" << endl;
        cout << "[2] - Go back" << endl;
        cout << endl;
        cout << "Choose option: "; cin >> inject;

        switch (inject)
        {
        case 1:
            system("cls");
            InjectProcess();
            break;
        case 2:
            system("cls");
            return;
        }
    } while (inject != 2);
}

auto CheatTab2() -> void
{
    do {
        system(xorstr_("cls"));
        Loader::UI.SetColor(Yellow, Black);
        cout << xorstr_("Soon..") << endl;
        Loader::UI.SetColor(White, Black);
        cout << endl;
        cout << xorstr_("[1] - Go back") << endl;
        cout << endl;
        cout << xorstr_("Choose option: "); cin >> inject;

        switch (inject)
        {
        case 1:
            system(xorstr_("cls"));
            return;
        }

    } while (inject != 1);
}

auto CatalogTab() -> void 
{
    do {
        Loader::UI.SetColor(Yellow, Black);
        cout << xorstr_("Choose cheat") << endl;
        Loader::UI.SetColor(White, Black);
        cout << endl;
        cout << xorstr_("[1] - Rust Devblog 236") << endl;
        cout << xorstr_("[2] - Rust Alkad") << endl;
        cout << xorstr_("[3] - Go back") << endl;
        cout << endl;
        cout << xorstr_("Choose option: "); cin >> submenu;
        system(xorstr_("cls"));
        
        switch (submenu)
        {
        case 1:
            CheatTab1();
            break;
        case 2:
            CheatTab2();
            break;
        case 3:
            system(xorstr_("cls"));
            return;
        }
    } while (submenu != 3);
}

auto SpooferTab() -> void 
{
    do {
        Loader::UI.SetColor(Yellow, Black);
        cout << xorstr_("Soon...") << endl;
        Loader::UI.SetColor(White, Black);
        cout << endl;
        cout << xorstr_("[1] - Go back") << endl;
        cout << xorstr_("Choose option: "); cin >> spoofer;

        switch (spoofer)
        {
        case 1:
            system(xorstr_("cls"));
            return;
        }
    } while (spoofer != 1);
}

auto Menu() -> void 
{
    do {
        Loader::UI.SetColor(Yellow, Black);
        cout << xorstr_("Delusive Loader") << endl;
        Loader::UI.SetColor(White, Black);
        cout << xorstr_("Loader Version: ") << VERSION << endl;
        cout << endl;
        cout << xorstr_("[1] - Catalog of cheats") << endl;
        cout << xorstr_("[2] - Spoofer") << endl;
        cout << xorstr_("[3] - Exit") << endl;

        cout << xorstr_("Choose option: "); cin >> menu;
        system(xorstr_("cls"));

        switch (menu)
        {
        case 1:
            CatalogTab();
            break;
        case 2:
            SpooferTab();
            break;
        case 3:
            break;
        }
    } while (menu != 3);
}

int main()
{
    Loader::UI.WindowSize(350, 200);
    Loader::UI.SetTitle(Title);

    _mkdir(xorstr_("C:\\Delusive"));
    _mkdir(xorstr_("C:\\Delusive\\Loader"));
    _mkdir(xorstr_("C:\\Delusive\\Loader\\Sounds"));
    _mkdir(xorstr_("C:\\Delusive\\Loader\\Dlls"));

    SetVolume(0x4000);
    PlayMusic();

    std::thread security(ProcessSecurity);
    security.detach();

    HideProcess();
    Loading(2);
    AdminCheck();
    Version();
    Download();
    Menu();

    cin.get();
}