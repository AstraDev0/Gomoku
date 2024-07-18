/*
** EPITECH PROJECT, 2023
** B-AIA-500-LYN-5-1-gomoku-louis.de-caumont
** File description:
** Protocol
*/

#include "../includes/Protocol.hpp"

Protocol::Protocol() {
    commandHandlers["START"] = [this](const std::vector<std::vector<std::string>>&table) {
        return _brain->start(table[0]);
    };
    commandHandlers["BEGIN"] = [this](const std::vector<std::vector<std::string>>&table) {
        return _brain->begin(table[0]);
    };
    commandHandlers["INFO"] = [this](const std::vector<std::vector<std::string>>&table) {
        return _brain->info(table[0]);
    };
    commandHandlers["BOARD"] = [this](const std::vector<std::vector<std::string>>& table) {
        return _brain->board(table);
    };
    commandHandlers["TURN"] = [this](const std::vector<std::vector<std::string>>&table) {
        return _brain->turn(table[0]);
    };
    commandHandlers["RECTSTART"] = [this](const std::vector<std::vector<std::string>>&table) {
        return _brain->rectStart(table[0]);
    };
    commandHandlers["ABOUT"] = [this](const std::vector<std::vector<std::string>>& table) {
        return _brain->about();
    };
    commandHandlers["RESTART"] = [this](const std::vector<std::vector<std::string>>& table) {
        return _brain->restart();
    };
    commandHandlers["END"] = [this](const std::vector<std::vector<std::string>>& table) {
        return _brain->end();
    };
    commandHandlers["DISPLAY"] = [this](const std::vector<std::vector<std::string>>& table) {
        return _brain->display();
    };
}
Protocol::~Protocol() {
    delete _brain;
}

int Protocol::checkCommand(std::string &command)
{
    int result = 0;

    try {
        std::vector<std::string> vectorString = split(command, ", \n\r");
        if (vectorString.empty())
            return 84;
        std::string cmd = vectorString[0];
        if (!boardMode) {
            vectorString.erase(vectorString.begin());
        }   
        if (cmd == "BOARD") {
            boardMode = true;
            return 0;
        } else if (cmd == "DONE" && boardMode) {
            boardMode = false;
            result = commandHandlers["BOARD"](vectorTable);
            vectorTable.clear();
            return result;
        }
        if (boardMode) {
            vectorTable.push_back(vectorString);
            return 0;
        }
        vectorTable.push_back(vectorString);
        result = commandHandlers[cmd](vectorTable);
        vectorTable.clear();
        return result;
    } catch(...) {
        std::cout << "ERROR - Unknown command" << std::endl;
        return 84;
    }
}

void Protocol::run()
{
    while (true) {
        std::string input;
        std::getline(std::cin, input);
        if (input.empty())
            continue;
        if (checkCommand(input) == 1)
            break;
    }
}