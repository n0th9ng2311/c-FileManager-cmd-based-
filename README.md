# File System Manager

A C++ program that provides basic file system operations like navigating directories, creating/deleting files and folders, and more.

## Features

- **Display files**: View contents of directories
- **Directory navigation**: Move in/out of directories
- **File operations**:
  - Create new files (txt, csv, docx, pptx)
  - Delete files
  - Copy/paste files (implementation pending)
- **Folder operations**:
  - Create new folders
  - Delete folders
  - Copy/paste folders (implementation pending)
- **System information**: View available drives/partitions with details

## Commands
--h     help          : List all available operations\
--movi  move_in       : Enter a directory\
--movo  move_out      : Exit current directory\
--nfi   new_file      : Create a new file\
--nfo   new_folder    : Create a new folder\
--dfi   delete_file   : Delete a file\
--dfo   delete_folder : Delete a folder\
--cfi   copy_file     : Copy a file (pending)\
--cfo   copy_folder   : Copy a folder (pending)\
--pfi   paste_file    : Paste a file (pending)\
--pfo   paste_folder  : Paste a folder (pending)\
--curp  current_path  : Show current directory path\

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
- Basic error handling for filesystem operations

## Pending Features

- Complete implementation of copy/paste operations
- File sorting functionality
- Additional error handling

## How to Compile
bash\
g++ -std=c++17 main.cpp -o filesystem_manager

- Then run\
./filesystem_manager


