# Display Resolution Setter Tool

## Overview
The Display Resolution Setter Tool is a command-line utility for Windows that allows users to change their display resolution and refresh rate. Additionally, it supports reverting to a previously saved resolution and refresh rate from a backup file.

## Key Features
- Set display resolution and refresh rate via command-line arguments.
- Revert to a previously saved resolution and refresh rate if no arguments are provided.
- Automatic fallback to default QHD resolution and 60Hz refresh rate in case of invalid arguments.
- Backup and restore functionality for display settings.

## Requirements
- Windows Operating System
- Microsoft C++ Compiler
- Windows SDK
- CMake (version 3.0 or higher)

## Building the Project
To build the project, follow these steps:
1. Clone the repository.
2. Open a command prompt and navigate to the project directory.
3. Run the following commands:
```
mkdir build
cd build
cmake ..
cmake --build .
```

## Usage
The Display Resolution Setter Tool can be used as follows:
```
WinSetDisplayMode.exe [width] [height] [refresh rate]
```
If no arguments are provided, the tool will revert to the previously saved resolution and refresh rate.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
```