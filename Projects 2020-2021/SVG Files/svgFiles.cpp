#include "svgFiles.h"
#include "Circle.h"
#include "Ellipse.h"
#include "Factory.h"
#include "Figure.h"
#include "Functions.h"
#include "Line.h"
#include "Rectangle.h"
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

void printMessage() {
    std::cout << std::endl;
    std::cout << "**************************************************************************************" << std::endl;
    std::cout << "*                         What would you like to do next:                            *" << std::endl;
    std::cout << "**************************************************************************************" << std::endl;
    std::cout << std::endl;
}

void SVGFiles::copy(std::vector<Figure *> otherFigures) {
    for (int i = 0; i < otherFigures.size(); i++) {
        figures.push_back(otherFigures[i]->clone());
    }
}

void SVGFiles::destroy() {
    for (Figure *p : figures) {
        delete p;
    }
    figures.clear();
}

SVGFiles::SVGFiles(std::vector<Figure *> otherFigures) {
    copy(otherFigures);
}

SVGFiles::SVGFiles(const SVGFiles &other) {
    copy(other.figures);
}

SVGFiles::~SVGFiles() {
    destroy();
}

SVGFiles &SVGFiles::operator=(const SVGFiles &other) {
    if (this != &other) {
        destroy();
        copy(other.figures);
    }
    return *this;
}

void SVGFiles::printHelp() const {
    std::cout << "\n The following commands are supported: \n";
    std::cout << "    <> open <file> - opens <file>\n";
    std::cout << "    <> close - closes the currently opened file\n";
    std::cout << "    <> save - saves the currently opened file\n";
    std::cout << "    <> saveas <file> - saves the currently opened file in <file>\n";
    std::cout << "    <> help - prints this information\n";
    std::cout << "    <> exit - exits the program\n";
    std::cout << "    <> print - prints all figures\n";
    std::cout << "    <> create - creates a new figure\n";
    std::cout << "    <> erase <n> - erases a figure with serial number n\n";
    std::cout << "    <> translate [<n>] - translates a figure or all of the figures\n";
    std::cout << "    <> within <option> - shows all figures which are located within a given circle/rectangle\n";
}

void SVGFiles::loadFigures(const std::string &fileName) {
    std::ifstream file(fileName.c_str(), std::ios::in);
    if (file.good()) {
        std::string s;
        while (!file.eof()) {
            file >> s;
            if (isKeyWord(s)) {
                Figure *f = FigureFactory::make(s);
                f->deserialize(file);
                figures.push_back(f->clone());
                delete f;
            }
        }
    }
    file.close();
}

void SVGFiles::print() const {
    if (figures.size() == 0) {
        std::cout << "There are no figures to be printed.\n";
        return;
    }

    int i = 0;
    for (auto f : figures) {
        std::cout << i + 1 << ". ";
        i++;
        f->print();
    }
}

void SVGFiles::serialize(std::ofstream &outFile) {
    if (figures.size() == 0) {
        std::cout << "There are no figures to be serialized.\n";
        return;
    }

    outFile << "<?xml version=\"1.0\" standalone=\"no\"?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\"\n\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n<svg>\n";
    for (auto f : figures) {
        f->serialize(outFile);
    }
    outFile << "</svg>";
}

void SVGFiles::createFigure(const std::vector<std::string> &info) {
    if (!isKeyWord(info[0])) {
        std::cout << "Unknown figure type.\n";
        return;
    }
    Figure *f = FigureFactory::make(info[0]);
    if (f->create(info)) {
        figures.push_back(f->clone());
    }
    delete f;
}

void SVGFiles::erase(const std::vector<std::string> &info) {
    if (figures.size() == 0) {
        std::cout << "There are no figures to be erased.\n";
        return;
    }
    if (intoNumber(info[0], -1) > figures.size() || intoNumber(info[0], -1) <= 0) {
        std::cout << "There is no figure number " << intoNumber(info[0], -1) << ".\n";
        return;
    }

    figures.erase(figures.begin() + intoNumber(info[0], -1) - 1);
    std::cout << "You have successfully erased the figure.\n";
}

void SVGFiles::translate(const std::vector<std::string> &info) {
    if (figures.size() == 0) {
        std::cout << "There are no figures to be translated.\n";
        return;
    }
    if (info.size() == 2) {
        for (auto f : figures) {
            f->translate(intoNumber(info[0], elemIndex(info[0], '=')), intoNumber(info[1], elemIndex(info[1], '=')));
        }
        std::cout << "Translated all figures.\n";
    } else if (info.size() == 3) {
        if (intoNumber(info[0], -1) > figures.size() || intoNumber(info[0], -1) <= 0) {
            std::cout << "There is no figure number " << intoNumber(info[0], -1) << ".\n";
            return;
        }
        if (intoNumber(info[0], elemIndex(info[0], '=')) > figures.size()) {
            std::cout << "There is no figure number " << intoNumber(info[0], elemIndex(info[0], '=')) << ".\n";
            return;
        }
        figures[intoNumber(info[0], elemIndex(info[0], '=')) - 1]->translate(intoNumber(info[1], elemIndex(info[1], '=')), intoNumber(info[2], elemIndex(info[2], '=')));
        std::cout << "You have successfully translated the figure.\n";
    }
}

void SVGFiles::within(const std::vector<std::string> &info) {
    if (figures.size() == 0) {
        std::cout << "There are no figures to be shown.\n";
        return;
    }
    if (info[0] == "circle") {

        if (info.size() != 4 || !isNumber(info[1]) || !isNumber(info[2]) || !isNumber(info[3])) {
            std::cout << "Invalid info.\n";
            return;
        }
        std::cout << "Printing figures within that " << info[0] << ": " << std::endl;
        for (auto f : figures) {
            if (f->withinCircle(intoNumber(info[1], elemIndex(info[1], '=')),
                                intoNumber(info[2], elemIndex(info[2], '=')),
                                intoNumber(info[3], elemIndex(info[3], '=')))) {
                f->print();
            }
        }
    } else if (info[0] == "rectangle") {
        if (info.size() != 5 || !isNumber(info[1]) || !isNumber(info[2]) || !isNumber(info[3]) || !isNumber(info[4])) {
            std::cout << "Invalid info.\n";
            return;
        }
        std::cout << "Printing figures within that " << info[0] << ": " << std::endl;
        for (auto f : figures) {
            if (f->withinRect(intoNumber(info[1], elemIndex(info[1], '=')),
                              intoNumber(info[2], elemIndex(info[2], '=')),
                              intoNumber(info[3], elemIndex(info[3], '=')),
                              intoNumber(info[4], elemIndex(info[4], '=')))) {
                f->print();
            }
        }
    } else {
        std::cout << "You can only see figures within a given circle or rectangle.\n";
    }
}

void SVGFiles::svgRun() {
    std::vector<std::string> commands;
    std::vector<std::string> fileNames;

    std::string choice;
    bool isOpen = true;
    while (isOpen == true) {
        printMessage();

        getline(std::cin, choice);
        std::vector<std::string> _choice;
        splitIntoWords(choice, _choice, 0);
        commands.push_back(_choice[0]);

        if (commands.size() > 2 && commands[commands.size() - 2] == "close") {
            while (_choice[0] != "open" && _choice[0] != "exit") {
                if (choice == "help") {
                    printHelp();
                    std::cout << "\n";
                } else {
                    std::cout << "Invalid command. Valid commands after closing a file: help, exit, open a new file.\n";
                }
                getline(std::cin, choice);
                _choice.clear();
                splitIntoWords(choice, _choice, 0);
            }
            commands.push_back(choice);
        }
        if (_choice[0] == "open") {
            if (fileNames.size() != 0) {
                std::cout << "There is already an open file. Please, close it before opening another one.\n";
            } else {
                fileNames.push_back(_choice[1]);
                loadFigures(_choice[1]);
                std::cout << "You have successfully opened " << _choice[1] << ".\n";
            }
        } else if (_choice[0] == "help") {
            printHelp();
        } else if (_choice[0] == "print") {
            print();
        } else if (_choice[0] == "create") {
            _choice.erase(_choice.begin());
            createFigure(_choice);
        } else if (_choice[0] == "erase") {
            _choice.erase(_choice.begin());
            erase(_choice);
        } else if (_choice[0] == "within") {
            _choice.erase(_choice.begin());
            within(_choice);
        } else if (_choice[0] == "translate") {
            _choice.erase(_choice.begin());
            translate(_choice);
        } else if (choice == "save") {
            std::ofstream file(fileNames[fileNames.size() - 1].c_str(), std::ios::out | std::ios::trunc);
            serialize(file);
            file.close();
            std::cout << "You have successfully saved " << fileNames[fileNames.size() - 1] << ".\n";
        } else if (choice == "saveas") {
            std::ofstream newFile(_choice[1].c_str(), std::ios::out);
            serialize(newFile);
            newFile.close();
            std::cout << "You have successfully saved another " << _choice[1] << ".\n";
        } else if (choice == "close") {
            destroy();
            std::cout << "You have successfully closed " << fileNames[fileNames.size() - 1] << ".\n";
            fileNames.erase(fileNames.begin() + fileNames.size() - 1);
        } else if (choice == "exit") {
            std::cout << "Exiting..." << std::endl;
            isOpen = false;
        } else {
            std::cout << "Invalid command. Please, try again." << std::endl;
        }
    }
}
