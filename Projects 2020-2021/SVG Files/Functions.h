#pragma once

#include<string>
#include<vector>
#include<cmath>

void splitIntoWords (const std::string& info, std::vector<std::string>& words, const int& start) {
    std::string word;
    for (int i = start; i < info.size(); i++) {
        if (info[i] == ' ') {
            i++;
            words.push_back(word);
            word.clear();
        }
        word.push_back(info[i]);
    }
    words.push_back(word);
}

int elemIndex (const std::string& word, const char& elem) {
    for (int i = 0 ; i < word.size() ; i++) {
        if (word[i] == elem) {
            return i;
        }
    }
    return -1;
}

double getNumber (const std::string& word) {
    double num = 0.0;
    int ind = elemIndex(word, '"');
    int ind1 = elemIndex(word, '.');
    int cnt;
    if (ind1 == -1) {
        cnt = word.size() - ind - 3;
        while (word[ind + 1] != '"' && cnt >= 0) {
            num += (word[ind + 1] - '0') * pow(10, cnt);
            cnt--;
            ind++;
        }
    }
    else {
        cnt = ind1 - ind - 2;
        while (word[ind + 1] != '"') {
            if (word[ind + 1] == '.') {
                cnt = -1;
                ind++;
            }
            num += (word[ind + 1] - '0') * pow(10, cnt);
            cnt--;
            ind++;
        }
    }
    return num;
}

std::string getFill (const std::string& word) {
    std::string _fill;
    int ind = elemIndex(word, '"');
    while (word[ind+1] != '"') {
        _fill.push_back(word[ind + 1]);
        ind++;
    }
    return _fill;
}

double intoNumber(const std::string& word, int ind) {
    double num = 0;
    int cnt;
    if (elemIndex(word, '.') == -1) {
        cnt = word.size() - ind - 2;
        while ((ind + 1) < word.size() && cnt >= 0) {
            num += (word[ind + 1] - '0') * pow(10, cnt);
            cnt--;
            ind++;
        }
    }
    else {
        cnt = elemIndex(word, '.') - ind - 2;
        while ((ind + 1) < word.size()) {
            if (word[ind+1] == '.') {
                cnt = -1;
                ind++;
            }
            num += (word[ind + 1] - '0') * pow(10, cnt);
            cnt--;
            ind++;
        }
    }
    return num;
}

bool isKeyWord (const std::string& word) {
    return word == "<line" || word == "<ellipse" || word == "<circle" || word == "<rect" ||
           word == "line" || word == "ellipse" || word == "circle" || word == "rectangle";
}

bool isNumber (const std::string& word) {
    for (int i = 0; i < word.size(); i++) {
        if ((word[i] > '9' || word[i] < '0') && word[i] != '.') {
            return false;
        }
    }
    return true;
}
