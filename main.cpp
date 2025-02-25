#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

struct Music{
    string track_name;
    string artist;
    string genre;
    int bpm;
    double popularity;
    double duration;
};

void readCSV(vector<Music>& musicList);
void parse(string line, vector<Music>& musicList);
void displayMusic(const vector<Music>& musicList);
int searchTrackByName(const vector<Music>& musicList, const string& trackName);
void displayTrack(const vector<Music>& musicList, int index);
map<string, int> countByGenre(const vector<Music>& musicList);
void displayByGenre(const vector<Music>& musicList, const string& genre);
int calculateAverageBPM(const vector<Music>& musicList);
Music findHighestBPM(const vector<Music>& musicList);
Music findLowestBPM(const vector<Music>& musicList);
vector<Music> searchTrackByPartialInput(const vector<Music>& musicList, const string& searchTerm);
bool compareByPopularity(const Music& a, const Music& b);
void displaySortedByPopularity(vector<Music>& musicList);

int main() {
    vector<Music> musicList;
    readCSV(musicList);  // Now it will modify the musicList vector

    int choice;
    string trackName, genre, searchTerm;
    int index, averageBPM;
    Music highestBPM, lowestBPM;
    vector<Music> searchResults;
    map<string, int> genreCount;

    do {
        cout << "\n==== Music Menu ====\n";
        cout << "1. Display All Tracks\n";
        cout << "2. Search Track by Name\n";
        cout << "3. Display Tracks by Genre\n";
        cout << "4. Display Highest, Lowest and Average BPM\n";
        cout << "5. Search Tracks by Partial Name\n";
        cout << "6. Display Tracks Sorted by Popularity in Descending\n";
        cout << "7. Exit\n";
        cout << "Enter your choice: ";

        while (!(cin >> choice) || choice < 1 || choice > 7) {
            cin.clear();  // Clear the error flag
            cin.ignore(numeric_limits<streamsize>::max(), '\n');  // Ignore incorrect input
            cout << "Invalid input. Please enter a number between 1 and 7: ";
        }

        cin.ignore();

        switch (choice) {
        case 1:
            displayMusic(musicList);
            break;
        case 2:
            cout << "Enter track name: ";
            getline(cin, trackName);

            index = searchTrackByName(musicList, trackName);
            displayTrack(musicList, index);
            break;
        case 3:
            genreCount = countByGenre(musicList);
            cout << "\nGenre Count: \n";
            for (const auto& [genre, count] : genreCount) {
                cout << genre << ": " << count << endl;
            }

            cout << "Enter genre to filter: ";
            getline(cin, genre);
            displayByGenre(musicList, genre);
            break;
        case 4:
            averageBPM = calculateAverageBPM(musicList);
            highestBPM = findHighestBPM(musicList);
            lowestBPM = findLowestBPM(musicList);

            cout << "Average BPM: " << averageBPM << "\n";
            cout << "Highest BPM Track: " << highestBPM.track_name << "(" << highestBPM.bpm << " BPM)\n";
            cout << "Lowest BPM Track: " << lowestBPM.track_name << "(" << lowestBPM.bpm << " BPM)\n";
            break;
        case 5:
            cout << "Input a track name: ";
            getline(cin, searchTerm);

            searchResults = searchTrackByPartialInput(musicList, searchTerm);

            if (!searchResults.empty()) {
                cout << "\nSearch Results: \n";
                displayMusic(searchResults);
            }
            else {
                cout << "\nTrack not found-" << endl;
            }
            break;
        case 6:
            displaySortedByPopularity(musicList);
            break;
        case 7:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid choice.\n";
            break;
        }
    } while (choice != 7);

    return 0;
}


void parse(string line, vector<Music>& musicList){
    stringstream ss(line);
    string temp;
    Music music;

    getline(ss, music.track_name, ',');
    getline(ss, music.artist, ',');
    getline(ss, music.genre, ',');

    getline(ss, temp, ',');
    music.bpm = stoi(temp); // BPM to int

    getline(ss, temp, ',');
    music.popularity = stod(temp); // Popularity to double

    getline(ss, temp, ',');
    music.duration = stod(temp); // Duration to double

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
            << "Popularity: " << fixed << setprecision(2) << music.popularity << "\n"
            << "Duration: " << fixed << setprecision(2) << music.duration << " min\n";
    }
    else{
        cout << "Track not found" << endl;
    }
}

map<string, int> countByGenre(const vector<Music>& musicList){
    map<string, int> genreCount;
    for (const auto& music : musicList){
        genreCount[music.genre]++;
    }
    return genreCount;
}

int searchTrackByName(const vector<Music>& musicList, const string& trackName){
    for (int i = 0; i < musicList.size(); i++){
        if (musicList[i].track_name == trackName){
            return i;
        }
    }
    return -1;
}

vector<Music> searchTrackByPartialInput(const vector<Music>& musicList, const string& searchTerm){
    vector<Music> result;

    for (const auto& music : musicList){
        if (music.track_name.find(searchTerm) != string::npos){
            result.push_back(music);
        }
    }
    return result;
}

void displayMusic(const vector<Music>& musicList){
    cout << "-------------------------------------------------------------" << endl;
    cout << " Track Name | Artist   | Genre   | BPM  | Pop. | Dur." << endl;
    cout << "-------------------------------------------------------------" << endl;

    for (const auto& music : musicList){
        cout << " " << music.track_name
            << " | " << music.artist
            << " | " << music.genre
            << " | " << music.bpm
            << " | " << fixed << setprecision(2) << music.popularity
            << " | " << fixed << setprecision(2) << music.duration << " min"
            << endl;
    }
    cout << "-------------------------------------------------------------\n";
}

void displayByGenre(const vector<Music>& musicList, const string& genre){
    cout << "\nTracks in Genres: " << genre << endl;
    cout << "-------------------------------------------------------------" << endl;
    cout << " Track Name | Artist   | Genre   | BPM  | Pop. | Dur." << endl;
    cout << "-------------------------------------------------------------" << endl;

    bool found = false;
    for (const auto& music : musicList){
        if (music.genre == genre){
            cout << " " << music.track_name
                << " | " << music.artist
                << " | " << music.genre
                << " | " << music.bpm
                << " | " << fixed << setprecision(2) << music.popularity
                << " | " << fixed << setprecision(2) << music.duration << " min"
                << endl;
            found = true;
        }
    }

    if (!found){
        cout << "Track not found-" << endl;
    }

    cout << "-------------------------------------------------------------\n";
}

bool compareByPopularity(const Music& a, const Music& b){
    return a.popularity > b.popularity; // Descending order
}

void displaySortedByPopularity(vector<Music>& musicList){
    sort(musicList.begin(), musicList.end(), compareByPopularity);

    displayMusic(musicList);
}


int calculateAverageBPM(const vector<Music>& musicList){
    if (musicList.empty()){
        return 0;
    }

    int totalBPM = 0;

    for (const auto& music : musicList){
        totalBPM += music.bpm;
    }

    return static_cast<int>(round(static_cast<double>(totalBPM) / musicList.size()));
}

Music findHighestBPM(const vector<Music>& musicList){
    if (musicList.empty()){
        return {};
    }

    Music highestBPM = musicList[0];
    for (const auto& music : musicList){
        if (music.bpm > highestBPM.bpm){
            highestBPM = music;
        }
    }

    return highestBPM;
}

Music findLowestBPM(const vector<Music>& musicList){
    if (musicList.empty()){
        return {};
    }

    Music lowestBPM = musicList[0];
    for (const auto& music : musicList){
        if (music.bpm < lowestBPM.bpm){
            lowestBPM = music;
        }
    }

    return lowestBPM;
}

void readCSV(vector<Music>& musicList){
    ifstream fin("modern_music_data.csv");
    string line;

    if (fin){
        // Read and discard the first line (header)
        if (getline(fin, line)){
            cout << line << endl;
        }

        // Read each line and parse it
        while (getline(fin, line)){
            if (!line.empty()){
                parse(line, musicList);
            }
        }
    }
    else{
        cout << "File Not Found" << endl;
    }
}
