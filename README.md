# File System Manager

A C++ program that provides basic file system operations like navigating directories, creating/deleting files and folders, and more.

## Features

- **Display files**: View contents of directories
- **Directory navigation**: Move in/out of directories
- **File operations**:
  - Create new files (txt, csv, docx, pptx)
  - Delete files
  - Copy/paste files 
- **Folder operations**:
  - Create new folders
  - Delete folders
  - Copy/paste folders (implementation pending)
- **System information**: View available drives/partitions with details

## Commands

| Command   | Full Form      | Description                      |
|-----------|----------------|----------------------------------|
| `--h`     | `help`         | List all available operations    |
| `--movi`  | `move_in`      | Enter a directory                |
| `--movo`  | `move_out`     | Exit current directory           |
| `--nfi`   | `new_file`     | Create a new file                |
| `--nfo`   | `new_folder`   | Create a new folder              |
| `--dfi`   | `delete_file`  | Delete a file                    |
| `--dfo`   | `delete_folder`| Delete a folder                  |
| `--cfi`   | `copy_file`    | Copy a file                      |
| `--cfo`   | `copy_folder`  | Copy a folder *(pending)*        |
| `--curp`  | `current_path` | Show current directory path      |


### Example Flow
1. Program starts by showing available drives/partitions
2. Use `--movi` to enter a directory
3. Use other commands to perform operations
4. Use `--movo` to move back to parent directory

## Requirements

- C++17 or later (uses filesystem library)
- Windows OS (uses Windows-specific APIs for drive detection)
- Compiler with C++17 support

## Implementation Notes

- Uses C++17's `<filesystem>` library for most operations
- Windows-specific code for partition detection using WinAPI
- Maintains a stack of visited directories for navigation
- Error handling for filesystem operations

## How to run
- Clone the repo\
- `git clone https://github.com/n0th9ng2311/c-FileManager-cmd-based-.git`
- `cd c-FileManager-cmd-based-`\

- Compile the files\
`g++ -std=c++17 main.cpp -o filesystem_manager`\

- Then run\
`./filesystem_manager`


