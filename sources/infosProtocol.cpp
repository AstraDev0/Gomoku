//
// Created by sibulcod on 20/11/23.
//

#include "../includes/infosProtocol.hpp"


void InfoProtocol::handleTimeoutTurn(int value)
{
    _config["timeout_turn"] = value;
}


void InfoProtocol::handleTimeoutMatch(int value) {
    _config["timeout_match"] = value;

}

void InfoProtocol::handleMaxMemory(int value) {
    _config["max_memory"] = value;

}

void InfoProtocol::handleTimeLeft(int value) {
    _config["time_left"] = value;

}

void InfoProtocol::handleGameType(int value) {
    _config["game_type"] = value;

}

void InfoProtocol::handleRule(int value) {
    _config["rule"] = value;

}

void InfoProtocol::handleFolder(int value) {
    _config["evaluate"] = value;

}

void InfoProtocol::handleEvaluate(const std::string &value) {
    //_config["folder"] = value;
}

void InfoProtocol::resetConfig()
{
    _config.clear();
}