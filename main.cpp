#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

struct Music {
    string track_name;
    string artist;
    string genre;
    int bpm;
    double popularity;
    double duration;
};

void readCSV();
void parse(string line, vector<Music>& musicList);
void displayMusic(const vector<Music>& musicList);
int searchTrackByName(const vector<Music>& musicList, const string& trackName);
void displayTrack(const vector<Music>& musicList, int index);

int main() {
    readCSV();
    return 0;
}

void parse(string line, vector<Music>& musicList) {
    stringstream ss(line);
    string temp;
    Music music;

    getline(ss, music.track_name, ',');
    getline(ss, music.artist, ',');
    getline(ss, music.genre, ',');

    getline(ss, temp, ',');
    music.bpm = stoi(temp);  // BPM to int

    getline(ss, temp, ',');
    music.popularity = stod(temp);  // Popularity to double

    getline(ss, temp, ',');
    music.duration = stod(temp);  // Duration to double

    musicList.push_back(music);
}

void displayTrack(const vector<Music>& musicList, int index){
    if (index != -1){
        const auto& music = musicList[index];
        cout << "Track Found: \n";
        cout << "Track Name: " << music.track_name << "\n"
        << "Artist: " << music.artist << "\n"
        << "Genre: " << music.genre << "\n"
        << "BPM: " << music.bpm << "\n"
        << "Popularity: " << music.popularity << "\n"
        << "Duration: " << music.duration << " min\n";
    }else{
        cout << "Track not found" << endl;
    }
}

int searchTrackByName(const vector<Music>& musicList, const string& trackName) {
    for (int i = 0; i < musicList.size(); i++){
        if (musicList[i].track_name == trackName){
            return i;
        }
    }
    return -1;
}

void displayMusic(const vector<Music>& musicList) {
    cout << "-------------------------------------------------------------" << endl;
    cout << " Track Name | Artist        | Genre       | BPM  | Pop. | Dur." << endl;
    cout << "-------------------------------------------------------------" << endl;

    for (const auto& music : musicList) {
        cout << " " << music.track_name
             << " | " << music.artist
             << " | " << music.genre
             << " | " << music.bpm
             << " | " << music.popularity
             << " | " << music.duration << " min"
             << endl;
    }
    cout << "-------------------------------------------------------------\n";
}

void readCSV() {
    ifstream fin("modern_music_data.csv");
    string line;
    vector<Music> musicList;

    if (fin) {
        // Read and discard the first line (header)
        if (getline(fin, line)) {
            cout << line << endl;
        }

        // Read each line and parse it
        while (getline(fin, line)) {
            if (!line.empty()) {
                parse(line, musicList);
            }
        }

        // Display parsed data
        displayMusic(musicList);

        // Asking the user to search for a track
        string tackName;
        cout << "Enter track name: ";
        getline(cin, tackName);

        int index = searchTrackByName(musicList, tackName);
        displayTrack(musicList, index);


    } else {
        cout << "File Not Found" << endl;
    }
}