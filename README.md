# Display Resolution Setter Tool

## Intended Use
Sunshine Command Preparations allowing the client to set the host display mode. This is very useful when the user's PC defaults to an ultra-wide resolution, but the moonlight client is on a TV with a 16:9 aspect ratio. For instance:

- Do: `cmd /C "FullPath\WinSetDisplayMode.exe %SUNSHINE_CLIENT_WIDTH% %SUNSHINE_CLIENT_HEIGHT% %SUNSHINE_CLIENT_FPS%"`
- Undo: `cmd /C "FullPath\WinSetDisplayMode.exe"`

## Overview
The Display Resolution Setter Tool is a command-line utility for Windows that allows users to change their display resolution and refresh rate. Additionally, it supports reverting to a previously saved resolution and refresh rate from a backup file.

## Motivation
The inspiration for this tool came from not being able to find a simple open-source utility that could set the display resolution and refresh rate via command-line arguments as well as revert to a previously saved resolution and refresh rate.

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

## TODO
- Add support for multiple monitors.
- Add support for HDR settings.

## License
This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
```