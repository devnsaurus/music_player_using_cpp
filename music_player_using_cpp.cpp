#include <windows.h>
#include <mmsystem.h>
#include <iostream>
#include <filesystem>
#include <vector>

#pragma comment(lib, "winmm.lib")

int main() {
    std::vector<std::string> filenames;
    int choice, current_song = 0;
    bool playing = false;

    std::cout << "Music Files in 'songs' folder:\n";

    // Get the current directory
    std::string current_dir = std::filesystem::current_path().string();

    // Construct the path to the 'songs' folder
    std::string songs_dir = current_dir + "\\songs";

    // Iterate through files in the 'songs' folder and display them with numbers
    int file_number = 1;
    for (const auto& entry : std::filesystem::directory_iterator(songs_dir)) {
        if (entry.is_regular_file()) {
            std::cout << file_number << ". " << entry.path().filename().string() << std::endl;
            filenames.push_back(entry.path().string());
            file_number++;
        }
    }


    std::cout << "\nChoose a file number to play: ";
    std::cin >> choice;

    if (choice >= 1 && choice <= filenames.size()) {
        current_song = choice - 1;
        std::cout << "Playing " << filenames[current_song] << "\n";
        PlaySound(filenames[current_song].c_str(), NULL, SND_FILENAME | SND_ASYNC);
        playing = true;
    } else {
        std::cout << "Invalid choice.\n";
        return 0;
    }

    while (true) {
        char input;
        std::cout << "Enter command: \n\tp --> play/pause \n\t] --> next song \n\t[ --> previous song \n\ts --> stop \n\n\t: ";
        std::cin >> input;

        switch (input) {
            case 'p':
            case 'P':
                if (playing) {
                    PlaySound(NULL, 0, 0); // Pause
                    playing = false;
                    std::cout << "Paused.\n";
                } else {
                    PlaySound(filenames[current_song].c_str(), NULL, SND_FILENAME | SND_ASYNC);
                    playing = true;
                    std::cout << "Resumed.\n";
                }
                break;
            case ']':
                if (current_song < filenames.size() - 1) {
                    current_song++;
                    if (playing) {
                        PlaySound(filenames[current_song].c_str(), NULL, SND_FILENAME | SND_ASYNC);
                        std::cout << "Playing " << filenames[current_song] << "\n";
                    }
                } else {
                    std::cout << "Last song reached.\n";
                }
                break;
            case '[':
                if (current_song > 0) {
                    current_song--;
                    if (playing) {
                        PlaySound(filenames[current_song].c_str(), NULL, SND_FILENAME | SND_ASYNC);
                        std::cout << "Playing " << filenames[current_song] << "\n";
                    }
                } else {
                    std::cout << "First song reached.\n";
                }
                break;
            case 's':
                PlaySound(NULL, 0, 0); // Stop
                playing = false;
                std::cout << "Stopped.\n";
                return 0;
            default:
                std::cout << "Invalid input.\n";
        }
    }

    return 0;
}

//g++ d5.cpp -o d5.exe -lwinmm
