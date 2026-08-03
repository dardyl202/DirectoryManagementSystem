#include <iostream>
#include <filesystem>
using namespace std;

namespace fs = std::filesystem;

// Function for listing files
void list_file()
{
    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "             LIST FILES\n";
        cout << "====================================\n";
        cout << "1. List all files\n";
        cout << "2. List files by extension\n";
        cout << "3. List files by pattern\n";
        cout << "4. Back to Main Menu\n";
        cout << "====================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            cout << "\nFiles in current directory:\n";

            for (const auto& entry : fs::directory_iterator(fs::current_path()))
{
    if (entry.is_regular_file())
    {
        cout << entry.path().filename().string() << endl;
    }
}
            break;

        case 2:
{
    string extension;

    cout << "\nEnter file extension (example: .txt): ";
    cin >> extension;

    cout << "\nFiles with extension " << extension << ":\n";

    bool found = false;

    for (const auto& entry : fs::directory_iterator(fs::current_path()))
    {
        if (entry.is_regular_file() &&
            entry.path().extension() == extension)
        {
            cout << entry.path().filename().string() << endl;
            found = true;
        }
    }

    if (!found)
    {
        cout << "No files found with that extension.\n";
    }

    break;
}

        case 3:
{
    string pattern;

    cout << "\nEnter file pattern (example: moha*.*): ";
    cin >> pattern;

    cout << "\nFiles matching " << pattern << ":\n";

    bool found = false;

    // Check if the pattern ends with *.*
    if (pattern.size() >= 3 &&
        pattern.substr(pattern.size() - 3) == "*.*")
    {
        string prefix = pattern.substr(0, pattern.size() - 3);

        for (const auto& entry : fs::directory_iterator(fs::current_path()))
        {
            if (entry.is_regular_file())
            {
                string filename = entry.path().filename().string();

                if (filename.rfind(prefix, 0) == 0)
                {
                    cout << filename << endl;
                    found = true;
                }
            }
        }
    }

    if (!found)
    {
        cout << "No files found matching the pattern.\n";
    }

    break;
}

        case 4:
            cout << "\nReturning to Main Menu...\n";
            break;

        default:
            cout << "\nInvalid choice.\n";
        }

    } while (choice != 4);
}

void directory()
{
    string folderName;

    cout << "\n====================================\n";
    cout << "         CREATE DIRECTORY\n";
    cout << "====================================\n";
    cout << "Enter directory name: ";
    cin >> folderName;

    fs::path folderPath = fs::current_path() / folderName;

    try
    {
        if (fs::exists(folderPath))
        {
            cout << "\nDirectory already exists.\n";
        }
        else
        {
            if (fs::create_directory(folderPath))
            {
                cout << "\nDirectory created successfully!\n";
            }
            else
            {
                cout << "\nFailed to create directory.\n";
            }
        }
    }
    catch (const fs::filesystem_error& e)
    {
        cout << "\nError: " << e.what() << endl;
    }
}

void change_dir()
{
    int choice;

    do
    {
        cout << "\n====================================\n";
        cout << "          CHANGE DIRECTORY\n";
        cout << "====================================\n";
        cout << "Current Directory:\n";
        cout << fs::current_path() << endl;
        cout << "------------------------------------\n";
        cout << "1. Move to parent directory\n";
        cout << "2. Move to root directory\n";
        cout << "3. Move to specific directory\n";
        cout << "4. Back to Main Menu\n";
        cout << "====================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        try
        {
            switch (choice)
            {
            case 1:
            {
                fs::path current = fs::current_path();
                fs::path parent = current.parent_path();

                if (current == parent)
                {
                    cout << "\nAlready at the root directory.\n";
                }
                else
                {
                    fs::current_path(parent);
                    cout << "\nMoved to parent directory successfully.\n";
                }

                break;
            }

            case 2:
            {
                fs::path root = fs::current_path().root_path();

                fs::current_path(root);

                cout << "\nMoved to root directory successfully.\n";
                break;
            }

            case 3:
            {
                string path;

                cout << "\nEnter directory path: ";
                cin >> path;

                fs::path newPath(path);

                if (fs::exists(newPath) && fs::is_directory(newPath))
                {
                    fs::current_path(newPath);

                    cout << "\nDirectory changed successfully.\n";
                }
                else
                {
                    cout << "\nDirectory does not exist.\n";
                }

                break;
            }

            case 4:
                cout << "\nReturning to Main Menu...\n";
                break;

            default:
                cout << "\nInvalid choice. Please try again.\n";
            }
        }
        catch (const fs::filesystem_error& e)
        {
            cout << "\nError: " << e.what() << endl;
        }

    } while (choice != 4);
}

int main()
{
    int choice;

    do
    {
        cout << "\n====================================\n";
cout << "     DIRECTORY MANAGEMENT SYSTEM\n";
cout << "====================================\n";
cout << "Current Directory:\n";
cout << fs::current_path() << "\n";
cout << "------------------------------------\n";
        cout << "1. List Files\n";
        cout << "2. Create Directory\n";
        cout << "3. Change Directory\n";
        cout << "4. Exit\n";
        cout << "====================================\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            list_file();
            break;

        case 2:
            directory();
            break;

        case 3:
            change_dir();
            break;

        case 4:
            cout << "\nExiting program...\n";
            break;

        default:
            cout << "\nInvalid choice. Please try again.\n";
        }

    } while (choice != 4);

    return 0;
}