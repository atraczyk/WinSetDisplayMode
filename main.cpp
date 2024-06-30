#include <windows.h>
#include <iostream>
#include <fstream>
#include <shlobj.h> // For SHGetFolderPath
#include <string>
#include <vector>

bool GetCurrentDisplaySettings(DEVMODE& dm) {
    memset(&dm, 0, sizeof(dm));
    dm.dmSize = sizeof(dm);
    return EnumDisplaySettings(NULL, ENUM_CURRENT_SETTINGS, &dm) != 0;
}

std::wstring GetAppDataPath() {
    wchar_t appDataPath[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_APPDATA, NULL, 0, appDataPath))) {
        return std::wstring(appDataPath) + L"\\ResolutionBackup.csv";
    }
    return L"";
}

bool WriteBackupResolution(int width, int height, int refreshRate) {
    auto appDataPath = GetAppDataPath();
    if (appDataPath.empty()) {
        return false;
    }
    std::wofstream outFile(appDataPath, std::ios::app);
    if (outFile.is_open()) {
        // Clear the file if it's not empty
        if (outFile.tellp() != 0) {
            outFile.seekp(0);
            outFile << L"";
        }
        outFile << width << L"," << height << L"," << refreshRate << std::endl;
        outFile.close();
        return true;
    }
    return false;
}

bool ReadBackupResolution(int& width, int& height, int& refreshRate) {
    auto appDataPath = GetAppDataPath();
    if (appDataPath.empty()) {
        return false;
    }
    std::wifstream inFile(appDataPath);
    std::wstring lastLine, line;
    while (std::getline(inFile, line)) {
        lastLine = line;
    }
    inFile.close();
    if (!lastLine.empty()) {
        size_t firstCommaPos = lastLine.find(',');
        size_t secondCommaPos = lastLine.rfind(',');
        if (firstCommaPos != std::string::npos && secondCommaPos != std::string::npos && firstCommaPos != secondCommaPos) {
            width = std::stoi(lastLine.substr(0, firstCommaPos));
            height = std::stoi(lastLine.substr(firstCommaPos + 1, secondCommaPos - firstCommaPos - 1));
            refreshRate = std::stoi(lastLine.substr(secondCommaPos + 1));
            return true;
        }
    }
    return false;
}

bool ChangeDisplayResolution(int width, int height, int refreshRate) {
    DEVMODE dm;
    if (!GetCurrentDisplaySettings(dm)) {
        return false;
    }

    // Backup current resolution and refresh rate before changing
    if (!WriteBackupResolution(dm.dmPelsWidth, dm.dmPelsHeight, dm.dmDisplayFrequency)) {
        std::cerr << "Failed to backup current resolution and refresh rate." << std::endl;
        return false;
    }

    dm.dmPelsWidth = width;
    dm.dmPelsHeight = height;
    dm.dmDisplayFrequency = refreshRate;
    dm.dmFields = DM_PELSWIDTH | DM_PELSHEIGHT | DM_DISPLAYFREQUENCY;

    return ChangeDisplaySettings(&dm, CDS_TEST) == DISP_CHANGE_SUCCESSFUL &&
           ChangeDisplaySettings(&dm, CDS_UPDATEREGISTRY) == DISP_CHANGE_SUCCESSFUL;
}

void HandleResolutionChangeResult(bool success) {
    if (success) {
        std::cout << "Resolution and refresh rate changed successfully" << std::endl;
    } else {
        std::cout << "Unable to change resolution and refresh rate" << std::endl;
    }
}

int main(int argc, char* argv[])
{
    // Default to QHD resolution and 60Hz refresh rate
    int width = 2560;
    int height = 1440;
    int refreshRate = 60;
    bool revertToBackup = false;

    if (argc == 4) {
        try {
            width = std::stoi(argv[1]);
            height = std::stoi(argv[2]);
            refreshRate = std::stoi(argv[3]);
        } catch (const std::exception&) {
            std::cout << "Invalid arguments. Using default QHD resolution and 60Hz refresh rate." << std::endl;
        }
    } else if (argc == 1) {
        std::cout << "No arguments provided. Reverting to backup resolution and refresh rate." << std::endl;
        if (!ReadBackupResolution(width, height, refreshRate)) {
            std::cerr << "No backup resolution or refresh rate found or invalid backup." << std::endl;
            return -1;
        }
        revertToBackup = true;
    } else {
        std::cout << "Usage: " << argv[0] << " <width> <height> <refreshRate>." << std::endl;
        return -1;
    }

    bool result = ChangeDisplayResolution(width, height, refreshRate);
    if (revertToBackup) {
        // Delete the backup file if we reverted to backup resolution
        auto appDataPath = GetAppDataPath();
        if (!appDataPath.empty()) {
            DeleteFileW(appDataPath.c_str());
        }
    }
    HandleResolutionChangeResult(result);

    return result ? 0 : -1;
}
