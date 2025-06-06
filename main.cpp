//WHAT I WANT FROM THE PROJECT
//--> Should be able to display files
//--> Should be able to move in and out of a directory
//--> Give the location of a file
//--> copy files from one directory to other
//--> Should be able to make new files
//--> Should be able to make new folders
//--> Should be able to delete them
//--> Should be able to sort them in different order

#include<iostream>
#include<filesystem>
#include<fstream>
#include<string>
#include<vector>
#include<windows.h>
#include<tchar.h>
#include<stdio.h>

//----------------------------------------------------------------------------------------
namespace drivePar
{
    void ListPartitionsWindows() { //This function displays the initial partitions and other info about those partitions
    TCHAR szDrive[] = _T("A:\\");
    DWORD uDriveMask = GetLogicalDrives();

    if (uDriveMask == 0) {
        _tprintf(_T("GetLogicalDrives() failed with error %d\n"), GetLastError());
        return;
    }

    _tprintf(_T("Available drives/partitions:\n"));

    while (uDriveMask) {
        if (uDriveMask & 1) {
            _tprintf(_T("  %s\n"), szDrive);

            // Get volume information
            TCHAR szVolumeName[MAX_PATH];
            TCHAR szFileSystemName[MAX_PATH];
            DWORD dwSerialNumber, dwMaxComponentLen, dwFileSystemFlags;

            if (GetVolumeInformation(
                szDrive,
                szVolumeName, MAX_PATH,
                &dwSerialNumber,
                &dwMaxComponentLen,
                &dwFileSystemFlags,
                szFileSystemName, MAX_PATH)) {

                _tprintf(_T("    Volume Name: %s\n"), szVolumeName);
                _tprintf(_T("    File System: %s\n"), szFileSystemName);
                _tprintf(_T("    Serial Number: %lu\n"), dwSerialNumber);
            }
        }
        ++szDrive[0];
        uDriveMask >>= 1;
    }
}

int _tmain(int argc, _TCHAR* argv[]) {
    ListPartitionsWindows();
    return 0;
}
}
//----------------------------------------------------------------------
namespace fs = std::filesystem;
using std::cout;
using std::cin;
using std::string;
using std::ofstream;
using std::cerr;
using std::getline;

//-----------------------------------------------------------------------
class FileOperations
{
private:
    std::vector<fs::path> prev_path{};//Stores the different paths taken by user while moving in and out of directories
public:
    FileOperations(){};//default constructor

    string choiceFnc()//function that helps us choose from available functions
    {
        string choice{};
        cin>>choice;

        if(choice == "--h")
        {
            cout<<"\n\n";
            displayChoice();//This function displays all the available operations for user
            cout<<'\n';
            choiceFnc();//calls the choice function again for user input
            cout<<'\n';
        }
        if(choice == "--movi")
        {
            moveInDire();//call in 'move in direction' function that helps you move in directories
            cout<<'\n';
            choiceFnc();//calls the choice function again after user enters a directory
            cout<<'\n';
        }
        if(choice == "--movo")
        {
            prev_path.pop_back();//pop backs the last directory in the prev_path vector
            moveOutDire();//exits from the most recent directory entered
            cout<<'\n';
            choiceFnc();//choice function again for further work
            cout<<'\n';
        }
        if(choice == "--nfi")
        {
            newFile();//calls in 'new file' function that helps you create a new file
            cout<<'\n';
            choiceFnc();//choice function again for further work
        }
        if(choice == "--nfo")
        {
            newFolder();//calls in 'new folder' function that helps you create a new folder
            cout<<'\n';
            choiceFnc();//choice function again for further work
        }
        if(choice == "--dfi")
        {
            deleteFile();//calls in 'delete file' function to remove a file from a directory/folder
            cout<<'\n';
            choiceFnc();//choice function again for further work
        }
        if(choice == "--dfo")
        {
            deleteFolder();//calls in 'delete folder' function to remove a directory/folder
            cout<<'\n';
            choiceFnc();//choice function again for further work
        }
        if(choice == "--cfi")
        {
            copyFile();//calls in 'copy folder' function to copy a file from a folder/directory
            cout<<'\n';
            choiceFnc();//choice function again for further work
        }
        if(choice == "--cfo")
        {
            copyFolder();//calls 'copy folder' function to copy a file/directory
            cout<<'\n';
            choiceFnc();//choice function again for further work
        }
        if(choice == "--pfi")
        {
            pasteFile();//calls in 'paste file' function to paste a file in a folder/directory
            cout<<'\n';
            choiceFnc();//choice function again for further work
        }
        if(choice == "--pfo")
        {
            pasteFolder();//calls in'paste folder' function to paste a folder in a folder/directory
            cout<<'\n';
            choiceFnc();//choice function again for further work
        }
        if(choice == "--curp")
        {
            cout<< "Current path: "<< get_curr_dir()<<"\n\n";//calls in a function to display the last directory entered into by the user
            choiceFnc();//choice function again for further work
        }
        else//condition if choice entered by the user in choiceFnc() is invalid/not supported yet
        {
            cout<<"Not a valid operation!\n\n";
            choiceFnc();
        }

    }
//---------------------------------------------------------------------------------------------
fs::path get_curr_dir() const {return prev_path.back();}//function to return the latest directory entered into by the user
//---------------------------------------------------------------------------------------------
   void displayChoice()//displays the available operations that can be done by the user
    {
        cout<<"The following operations are available: \n"
            <<"--h        help           :gives you the list of operations.\n"
            <<"--movi     move_in        :takes you into directories.\n"
            <<"--movo     move_out       :takes you out of a directory.\n"
            <<"--nfi      new_file       :gives you options to make new file.\n"
            <<"--nfo      new_folder     :gives you options to make new folder.\n"
            <<"--dfi      delete_file    :gives you option to delete a file.\n"
            <<"--dfo      delete_folder  :gives you option to delete a folder.\n"
            <<"--cfi      copy_file      :gives you option to copy a file.\n"
            <<"--cfo      copy_folder    :gives you option to copy a folder.\n"
            <<"--pfi      paste_file     :gives you option to paste the file.\n"
            <<"--pfo      paste_folder   :gives you option to paste the folder.\n"
            <<"--curp     current_path   :gives you current path/directory.\n";
    }
//---------------------------------------------------------------------------------------------
    void moveInDire()
    {
        if(!prev_path.empty())//case if prev_path is not empty
        {
            string original_path{}; //stores the path as string
            fs::path current_dir{}; //stores the complete path as fs::path
            cout<<"Enter the path: ";

            while(true)
            {
                getline(cin>>std::ws, original_path);
                auto sprev_path = (prev_path.back()).string() + '\\';
                fs::path current_dir_1 = sprev_path + original_path;//creates current_dir_1 which is used to check if the entered directory exists
                current_dir = current_dir_1;//sets current_dir as current_dir_1 to push_back on prev_path

                if(fs::exists(current_dir_1))
                {
                    break;
                }
                cout<<"Enter a valid path: ";
                cin.clear();
            }

           prev_path.push_back(current_dir);//push the current directory to prev_path

            cout<<"Currently in: "<<current_dir.string()<<'\n';
            for(const auto& entry : fs::directory_iterator(prev_path.back()))//displays the file available in the latest directory entered into by the user
                cout<< " "<<entry.path().filename()<< '\n';
        }

        else//case if prev_path is empty
        {
            cout<< "Please enter parent directory with ':\\' (for ex E:\\)\n";
            string original_path{};

            while(true)
            {
                getline(cin>>std::ws, original_path);
                fs::path current_dir = original_path;

                if(fs::exists(current_dir))//case if path does exist
                {
                    break;
                }
                cout<< "Invalid path, please enter a valid path: \n";
                cin.clear();
            }

            prev_path.push_back(original_path);

            cout<<"Currently in: "<<original_path<<'\n';
            for(const auto& entry : fs::directory_iterator(prev_path.back()))
                cout<<" "<< entry.path().filename()<<'\n';
        }
    }
 //---------------------------------------------------------------------------------------
    void moveOutDire()
    {
        if(!prev_path.empty())//case if prev_path is not empty
        {
            auto last_element = prev_path.back();
            cout<< "Now in: "<<last_element.string()<<'\n';

            for(const auto& entry : fs::directory_iterator(prev_path.back()))
                cout<< " "<< entry.path().filename()<<'\n';

            //prev_path.pop_back();//not using pop_back here because it also the 2nd most recent element

        }
        else//if prev_path is empty
        {
            cout<< "End of path"<<'\n';
        }
    }
//----------------------------------------------------------------------------------------
    void newFile()
    {
        int choice_file{};
        cout<< "\nWhat type of file do you want?\n"
            << "0)to exit\n"
            << "1)txt\n"
            << "2)csv(excel)\n"
            << "3)docx(word)\n"
            << "4)pptx(power point)\n";
        cin>>choice_file;

        if (choice_file == 0)
        {
            cout<< "Exiting\n";
        }
        if (choice_file == 1)
        {
            string file_name{};
            cout<< "Name of file: ";
            getline(cin>>std::ws, file_name);
            string file_path = (prev_path.back()).string()+"\\";

            ofstream outFile{file_path+file_name+".txt"};
            auto check_path_existance = file_path+file_name+".txt";

            if(!outFile)//checks if file was created
            {
                cerr<<"Error opening file\n";
            }
            else if(fs::exists(check_path_existance))//checks if file is already present
            {
                cout<<"File already exists\n";
            }
            else
            {
                cout<<"File created successfully\n";
            }
        }
        if (choice_file == 2)
        {
            string file_name{};
            cout<< "Name of file: ";
            getline(cin>>std::ws, file_name);
            string file_path = (prev_path.back()).string()+"\\";

            ofstream outFile{file_path+file_name+".csv"};
            auto check_path_existance = file_path+file_name+".csv";

            if(!outFile)
            {
                cerr<<"Error opening file\n";
            }
            else if(fs::exists(check_path_existance))
            {
                cout<<"File already exists\n";
            }
            else
            {
                cout<<"File created successfully\n";
            }
        }
        if (choice_file == 3)
        {
            string file_name{};
            cout<< "Name of file: ";
            getline(cin>>std::ws, file_name);
            string file_path = (prev_path.back()).string()+"\\";

            ofstream outFile{file_path+file_name+".docx"};
            auto check_path_existance = file_path+file_name+".docx";

            if(!outFile)
            {
                cerr<<"Error opening file\n";
            }
            else if(fs::exists(check_path_existance))
            {
                cout<<"File already exists\n";
            }
            else
            {
                cout<<"File created successfully\n";
            }
         }

        if (choice_file == 4)
        {
            string file_name{};
            cout<< "Name of file: ";
            getline(cin>>std::ws, file_name);
            string file_path = (prev_path.back()).string()+"\\";

            ofstream outFile{file_path+file_name+".pptx"};
            auto check_path_existance = file_path+file_name+".pptx";

            if(!outFile)
            {
                cerr<<"Error opening file\n";
            }
            else if(fs::exists(check_path_existance))
            {
                cout<<"File already exists\n";
            }
            else
            {
                cout<<"File created successfully\n";
            }
        }
    }
 //---------------------------------------------------------------------------------------
    void newFolder()
    {
        string folder_name{};
        cout<<"Name of folder: ";
        getline(cin>>std::ws, folder_name);

        string folder_dir = (prev_path.back()).string()+"\\";
        fs::path folder_loc = folder_dir+folder_name;

        if(fs::exists(folder_loc))//check if said folder already exists
        {
            cout<< "Folder already exists"<<'\n';
        }
        else
        {
            try {
                fs::create_directory(folder_dir+folder_name);

                cout << "Directory created successfully!\n";
            } catch (const fs::filesystem_error& e) {
                cerr << "Filesystem error: " << e.what() << '\n';
            } catch (const std::exception& e) {
                cerr << "General error: " << e.what() << '\n';
            }
        }
    }
    //---------------------------------------------------------------------------------------
    void deleteFolder()
    {
        try
        {
            string folder_to_rem {};
            cout<<"Folder to be removed: ";
            getline(cin>>std::ws, folder_to_rem);

            fs::path last_element = (prev_path.back()).string()+"\\"+folder_to_rem;
            if(fs::remove_all(last_element))
                cout<<"Directory removed successfully\n";

            cout<<"folder could not be removed";
        }
        catch(const fs::filesystem_error& err)
        {
            cerr<< "Filesystem error: "<< err.what()<< '\n';
        }
    }
    //--------------------------------------------------------------------------------------
    void deleteFile()
    {
        try
        {
            string file_name {};
            cout<< "Enter the name of file you want to remove with the extension of said file: ";
            getline(cin>>std::ws, file_name);

            fs::path last_element = (prev_path.back()).string() + "\\" + file_name;

            if(fs::remove(last_element))
                cout<<"File removed successfully\n";

            cout<<"File could not be removed\n";

        }catch(const fs::filesystem_error& err)
        {
            cerr<<"Filesystem error: "<< err.what()<<'\n';
        }
    }
    //-------------------------------------------------------------------------------------------
    void copyFile(){}
    void copyFolder(){}
    void pasteFile(){}
    void pasteFolder(){}
};

//------------------------------------------------------------------------------------------------
int main()
{
    FileOperations file{};
    file.displayChoice();
    cout<<'\n';
    drivePar::ListPartitionsWindows();
    cout<<'\n';
    file.choiceFnc();

    return 0;
}
