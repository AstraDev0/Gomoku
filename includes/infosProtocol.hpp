//
// Created by sibulcod on 20/11/23.
//

#ifndef PBRAIN_GOMOKU_AI_INFOS_PROTOCOL_HPP
#define PBRAIN_GOMOKU_AI_INFOS_PROTOCOL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <stdexcept>
#include <random>
#include <thread>

class InfoProtocol {
public:
    void handleTimeoutTurn(int value);
    void handleTimeoutMatch(int value);
    void handleMaxMemory(int value);
    void handleTimeLeft(int value);
    void handleGameType(int value);
    void handleRule(int value);
    void handleFolder(int value);
    void handleEvaluate(const std::string& value);
    void resetConfig();
    std::unordered_map<std::string, int> get_config() {
        return _config;
    };
private:
    std::unordered_map<std::string, int> _config;
};

#endif
