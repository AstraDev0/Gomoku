/*
** EPITECH PROJECT, 2023
** B-AIA-500-LYN-5-1-gomoku-louis.de-caumont
** File description:
** Brain
*/

#ifndef BRAIN_HPP_
#define BRAIN_HPP_

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <stdexcept>
#include <random>
#include "infosProtocol.hpp"
#include "Minimax.hpp"

class Brain {
public:
    Brain();
    ~Brain();
    void defaultParams();
    int start(const std::vector<std::string>& args);
    int turn(const std::vector<std::string>& args);
    int begin(const std::vector<std::string>& args);
    int board(const std::vector<std::vector<std::string>>& args);
    int info(const std::vector<std::string>& args);
    int rectStart(const std::vector<std::string>& args);
    int restart();
    int about();
    int end();
    int display();

private:
    InfoProtocol *_infoProtocol = new InfoProtocol();
    Minimax *_minimax = new Minimax();
    int _boardWidth{};
    int _boardHeight{};
    bool _start = false;
};

#endif /* !BRAIN_HPP_ */
