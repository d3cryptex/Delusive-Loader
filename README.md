# Delusive-Loader

DLL injector and cheat loader manager for Rust (Devblog 236 and newer).

---

## 🔧 Features

- ✅ Injects DLL into RustClient.exe process
- 🌐 Checks for latest cheat version via Pastebin API
- 🔐 Status check of cheat (Undetect / Detect / UseAtOwnRisk)
- 🎵 Plays a sound on startup
- 📥 Automatically downloads .dll from GitHub
- 🔊 System volume control
- 🛑 Admin privileges check

---

## 📁 Directory Structure

```
Delusive-Loader/
├── Delusive-Loader/
│   ├── Delusive-Loader.vcxproj
│   ├── Delusive-Loader.vcxproj.filters
│   ├── Delusive-Loader.vcxproj.user
│   ├── Include.hpp
│   ├── Inject.cpp
│   ├── Inject.hpp
│   ├── Lazyimporter.hpp
│   ├── Main.cpp
│   ├── Security.hpp
│   ├── UI.cpp
│   ├── UI.hpp
│   ├── crypt.cpp
│   ├── crypt.h
│   ├── dchar.h
│   ├── xorstr.hpp
│   └── x64/
│       └── Release/
│           ├── Delusive-Loader.exe
│           └── Delusive-Loader.pdb
└── Delusive-Loader.sln
```

---

## 📥 Custom Links

- You need to change some link like DLL download and pastebin.You can also you other file cloud instead of pastebin.

---

## 🧪 Usage

1. Run `Delusive-Loader.exe` **as Administrator**
2. Wait for `RustClient.exe` to launch
3. Choose the cheat from the menu
4. Press `[1] - Inject Cheat`

---

## 🔒 Security

- Uses `xorstr_()` for string obfuscation
- Injection via `NtCreateThreadEx` or `CreateRemoteThreadEx`
- DLL integrity check before injection

---

## 📦 Dependencies

- Windows.h, WinInet.h, urlmon.h
- Psapi.lib, winmm.lib, etc.
- [xorstr](https://github.com/JustasMasiulis/xorstr)
- [LazyImporter](https://github.com/JustasMasiulis/lazy_importer)

---

## 📜 License

MIT License © 2025

---

Made with ❤️ to help you **learn by building**.

By **d3cryptex**
