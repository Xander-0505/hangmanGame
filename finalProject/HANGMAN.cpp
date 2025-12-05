#include <iostream>
#include <string>
#include <vector>
#include <ctime>
#include <cstdlib>
#include <fstream>

using namespace std;

vector<string> animalsEasy = { "cat", "dog", "bird", "cow", "fish" };
vector<string> animalsMed = { "panther", "giraffe", "buffalo", "dolphin", "penguin" };
vector<string> animalsHard = { "chameleon", "hippopotamus", "orangutan", "alligator", "rhinoceros" };

vector<string> moviesEasy = { "cars", "frozen", "shrek", "coco", "up" };
vector<string> moviesMed = { "avatar", "inception", "rocky", "gladiator", "goodfellas" };
vector<string> moviesHard = { "interstellar", "jurassicpark", "2fast2furious", "dontbeamenacetosouthcentralwhiledrinkingyourjuiceinthehood", "thedictator" };

vector<string> countryEasy = { "usa", "china", "india", "spain", "italy" };
vector<string> countryMed = { "mexico", "germany", "france", "canada", "brazil" };
vector<string> countryHard = { "australia", "bangladesh", "philippines", "kazakhstan", "switzerland" };

vector<string> stateEasy = { "texas", "ohio", "maine", "idaho", "utah" };
vector<string> stateMed = { "florida", "georgia", "kentucky", "tennessee", "maryland" };
vector<string> stateHard = { "connecticut", "pennsylvania", "massachusetts", "washington", "california" };

vector<string> showEasy = { "friends", "glee", "lost", "arrow", "flash" };
vector<string> showMed = { "invincible", "brooklyn99", "familyguy", "prisonbreak", "strangerthings" };
vector<string> showHard = { "gameofthrones", "breakingbad", "mandalorian", "walkingdead", "houseofthedragon" };


string getRandomWord(vector<string> list) 
{
    return list[rand() % list.size()];
}

vector<string> loadWordsFromFile(string filename) 
{
    vector<string> words;
    ifstream file(filename);

    if (!file) 
    {
        cout << "File not found.\n";
        return words;
    }

    string line;
    while (getline(file, line)) 
    {
        if (!line.empty())
            words.push_back(line);
    }

    file.close();
    return words;
}

string chooseWord(int genre, int difficulty) 
{
    switch (genre) 
    {
    case 1:
        if (difficulty == 1) return getRandomWord(animalsEasy);
        if (difficulty == 2) return getRandomWord(animalsMed);
        return getRandomWord(animalsHard);

    case 2:
        if (difficulty == 1) return getRandomWord(moviesEasy);
        if (difficulty == 2) return getRandomWord(moviesMed);
        return getRandomWord(moviesHard);

    case 3:
        if (difficulty == 1) return getRandomWord(countryEasy);
        if (difficulty == 2) return getRandomWord(countryMed);
        return getRandomWord(countryHard);

    case 4:
        if (difficulty == 1) return getRandomWord(stateEasy);
        if (difficulty == 2) return getRandomWord(stateMed);
        return getRandomWord(stateHard);

    case 5:
        if (difficulty == 1) return getRandomWord(showEasy);
        if (difficulty == 2) return getRandomWord(showMed);
        return getRandomWord(showHard);
    }

    return "error";
}


void drawHangman(int wrong) 
{
    cout << "\nWrong guesses: " << wrong << "\n";

    switch (wrong) 
    {
    case 6: cout << "  _______\n";
    case 5: cout << "  |     |\n";
    case 4: cout << "  |     O\n";
    case 3: cout << "  |    /|\\\n";
    case 2: cout << "  |    / \\\n";
    case 1: cout << "  |\n";
    default: cout << " _|_\n\n";
    }
}


void playHangman(string word) 
{
    int maxWrong = 6;
    int wrong = 0;
    vector<char> guessed;
    string display(word.size(), '_');

    while (wrong < maxWrong && display != word) 
    {
        cout << "\nWord: " << display << "\n";
        cout << "Guessed letters: ";
        for (char c : guessed) cout << c << " ";
        cout << "\nEnter a letter: ";
        char guess;
        cin >> guess;

        bool repeat = false;
        for (char c : guessed)
            if (c == guess) repeat = true;

        if (repeat) 
        {
            cout << "Already guessed!\n";
            continue;
        }

        guessed.push_back(guess);
        bool hit = false;

        for (int i = 0; i < word.size(); i++)
            if (word[i] == guess) 
            {
                display[i] = guess;
                hit = true;
            }

        if (!hit) wrong++;

        drawHangman(wrong);
    }

    if (display == word)
        cout << "\nYou win! Word: " << word << "\n";
    else
        cout << "\nYou lost! Word was: " << word << "\n";
}


int main() 
{
    cout << "===== HANGMAN =====\n";
    cout << "1. Play vs Computer\n";
    cout << "2. Play vs Friend\n";
    cout << "3. Load word file\n";
    int mode;
    cin >> mode;

    string word;

    if (mode == 1) 
    {
        int genre, difficulty;

        cout << "\nChoose a genre:\n";
        cout << "1. Animals\n2. Movies\n3. Countries\n4. States\n5. TV Shows\n";
        cin >> genre;

        cout << "\nChoose difficulty:\n";
        cout << "1. Easy\n2. Medium\n3. Hard\n";
        cin >> difficulty;

        word = chooseWord(genre, difficulty);
    }
    else if (mode == 2) 
    {
        cout << "Player 1, enter a word for the opponent:\n";
        cin >> word;
        system("CLS");
    }
    else if (mode == 3) 
    {
        string filename;
        cout << "Enter filename (ex: words.txt): ";
        cin >> filename;

        vector<string> fileWords = loadWordsFromFile(filename);

        if (fileWords.empty()) 
        {
            cout << "Could not load words — exiting.\n";
            return 0;
        }

        word = getRandomWord(fileWords);
    }
    else 
    {
        cout << "Invalid option.\n";
        return 0;
    }

    playHangman(word);

    return 0;
}