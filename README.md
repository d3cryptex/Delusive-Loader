# Delusive-Loader

> DLL injector and cheat loader manager for Rust (Devblog 236 and newer).

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
├── Dlls/
│   └── delusiveDevblog236.dll
├── Sounds/
│   └── sound.wav
├── Include/
│   └── Include.hpp
├── Inject.hpp
├── UI.hpp
├── Security.hpp
├── xorstr.hpp
├── Lazyimporter.hpp
├── main.cpp
```

---

## 📥 DLL Download

- DLL is auto-downloaded from:
  ```
  https://raw.githubusercontent.com/6275SeNpai/Delusive-Dlls/main/Devblog236.dll
  ```

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

## 🚫 Legal Notice

This project is for educational/research use only. Do not use in protected or online games—it may violate game Terms of Service.

---

## 📜 License

MIT License © 2025
