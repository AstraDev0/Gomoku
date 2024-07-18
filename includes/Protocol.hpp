/*
** EPITECH PROJECT, 2023
** B-AIA-500-LYN-5-1-gomoku-louis.de-caumont
** File description:
** Protocol
*/

#ifndef MANAGER_HPP_
#define MANAGER_HPP_

#include <string>
#include <unordered_map>
#include <functional>
#include "../includes/utils.hpp"
#include "../includes/Brain.hpp"

typedef std::function<int(std::vector<std::vector<std::string>>)> CommandHandler;

class Protocol {
public:
    Protocol();
    ~Protocol();
    int checkCommand(std::string &command);
    void run();

private:
    Brain *_brain = new Brain();
    std::unordered_map<std::string, CommandHandler> commandHandlers;
    std::vector<std::vector<std::string>> vectorTable;
    bool boardMode = false;
};

#endif /* !MANAGER_HPP_ */
