/*
** EPITECH PROJECT, 2023
** B-AIA-500-LYN-5-1-gomoku-louis.de-caumont
** File description:
** Brain
*/

#include "../includes/Brain.hpp"

Brain::Brain()
{
    defaultParams();
};

Brain::~Brain()
{
    delete _minimax;
    delete _infoProtocol;
};

void Brain::defaultParams()
{
    _start = false;
    _infoProtocol->handleTimeoutTurn(50000);
    _infoProtocol->handleMaxMemory(70000000);
    _infoProtocol->handleRule(1);
}

int Brain::start(const std::vector<std::string>& args)
{
    if (args.empty()) {
        std::cout << "ERROR - No arguments provided" << std::endl;
        return 84;
    }
    try {
        if (std::stoi(args[0]) <= 0) {
            std::cout << "ERROR size not available" << std::endl;
            return 84;
        }
        int boardSizeTmp = std::stoi(args[0]);
        if (boardSizeTmp < 0) {
            _minimax->_boardSize = boardSizeTmp;
            std::cout << "ERROR size not available" << std::endl;
            return 84;
        } else {
            _minimax->_boardSize = std::stoi(args[0]);
            _minimax->_gameBoard = std::vector(_minimax->_boardSize, std::vector<int>(_minimax->_boardSize, 0));
            _start = true;
            std::cout << "OK" << std::endl;
        }
    } catch (const std::invalid_argument& e) {
        std::cout << "ERROR - Invalid argument: not an integer" << std::endl;
        return 84;
    } catch (const std::out_of_range& e) {
        std::cout << "ERROR - Integer out of range" << std::endl;
        return 84;
    }
    return 0;
}

int Brain::restart()
{
    _minimax->_gameBoard.clear();
    _infoProtocol->resetConfig();
    defaultParams();
    start(std::vector<std::string>{std::to_string(_minimax->_boardSize)});
    return 0;
}

int Brain::turn(const std::vector<std::string>& args)
{
    if (!_start) {
        std::cout << "ERROR - Use command start before" << std::endl;
        return 84;
    }
    if (args.size() < 2) {
        std::cout << "ERROR - Not enough arguments" << std::endl;
        return 84;
    }
    try {
        const int x = std::stoi(args[0]);
        const int y = std::stoi(args[1]);

        if (x < 0 || x >= _minimax->_boardSize || y < 0 || y >= _minimax->_boardSize) {
            std::cout << "ERROR - coordinate out of bounds" << std::endl;
            return 84;
        }
        if (_minimax->_gameBoard[x][y] == PLAYER1 || _minimax->_gameBoard[x][y] == PLAYER2) {
            std::cout << "ERROR - Place already taken" << std::endl;
            return 84;
        }
        _minimax->newPawn(x, y, PLAYER2);
        std::pair<int, int> move = _minimax->run();
        _minimax->newPawn(move.first, move.second, PLAYER1);
        std::cout << move.first << "," << move.second << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "ERROR - Invalid argument: not an integer" << std::endl;
        return 84;
    } catch (const std::out_of_range& e) {
        std::cout << "ERROR - Integer out of range" << std::endl;
        return 84;
    }
    return 0;
}

int Brain::begin(const std::vector<std::string>& args)
{
    if (!_start) {
        std::cout << "ERROR - Use command start before" << std::endl;
        return 84;
    }
    if (!args.empty()) {
        std::cout << "ERROR - Too much arguments" << std::endl;
        return 84;
    }

    try {
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> distrib(0, _minimax->_boardSize - 1);

        const int x = distrib(gen);
        const int y = distrib(gen);

        _minimax->newPawn(x, y, PLAYER1);
        _minimax->run();

        std::cout << x << "," << y << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "ERROR - Invalid argument: not an integer" << std::endl;
        return 84;
    } catch (const std::out_of_range& e) {
        std::cout << "ERROR - Integer out of range" << std::endl;
        return 84;
    }
    return 0;
}

int Brain::board(const std::vector<std::vector<std::string >>& args)
{
    try {
        _minimax->_gameBoard = std::vector(_minimax->_boardSize, std::vector<int>(_minimax->_boardSize, 0));

        for (const auto& field : args) {
            if (field.size() != 3) {
                std::cout << "ERROR - Invalid field data" << std::endl;
                return 84;
            }
            const int x = std::stoi(field[0]);
            const int y = std::stoi(field[1]);
            const int value = std::stoi(field[2]);

            if (x >= 0 && x < _minimax->_boardSize && y >= 0 && y < _minimax->_boardSize) {
                _minimax->newPawn(x, y, Player(value));
            } else {
                std::cout << "ERROR - Coordinate out of bounds" << std::endl;
                return 84;
            }
        }
        std::pair<int, int> move = _minimax->run();
        _minimax->newPawn(move.first, move.second, PLAYER2);
        std::cout << move.first << "," << move.second << std::endl;
    } catch (const std::exception& e) {
        std::cout << "Exception caught: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}

int Brain::info(const std::vector<std::string>& args)
{
    if (args.size() % 2 != 0) {
        std::cout << "ERROR - Key-value pairs are incomplete" << std::endl;
        return 84;
    }
    try {
        for (size_t i = 0; i < args.size(); i += 2) {
            const std::string& key = args[i];
            const std::string& value = args[i + 1];

            if (key == "timeout_turn") {
                _infoProtocol->handleTimeoutTurn(std::stol(value));
            } else if (key == "timeout_match") {
                _infoProtocol->handleTimeoutMatch(std::stol(value));
            } else if (key == "max_memory") {
                _infoProtocol->handleMaxMemory(std::stol(value));
            } else if (key == "time_left") {
                _infoProtocol->handleTimeLeft(std::stol(value));
            } else if (key == "game_type") {
                _infoProtocol->handleGameType(std::stol(value));
            } else if (key == "rule") {
                _infoProtocol->handleRule(std::stol(value));
            } else if (key == "folder") {
                _infoProtocol->handleFolder(std::stol(value));
            } else if (key == "evaluate") {
                _infoProtocol->handleEvaluate(value);
            } else {
                return 84;
            }
        }
    } catch (const std::exception& e) {
        std::cout << "ERROR processing INFO command: " << e.what() << std::endl;
        return 84;
    }
    return 0;
}

int Brain::rectStart(const std::vector<std::string>& args)
{
    if (args.size() < 2) {
        std::cout << "ERROR - Not enough arguments" << std::endl;
        return 84;
    }
    try {
        _boardWidth = std::stoi(args[0]);
        _boardHeight = std::stoi(args[1]);
        if (_boardWidth <= 0 || _boardHeight <= 0 || _boardWidth == _boardHeight) {
            std::cout << "ERROR - Invalid dimensions for a rectangular board" << std::endl;
            return 84;
        }
        _minimax->_gameBoard = std::vector<std::vector<int>>(_boardHeight, std::vector<int>(_boardWidth, 0));
        std::cout << "OK - Rectangular board of size " << _boardWidth << "x" << _boardHeight << " initialized" << std::endl;
    } catch (const std::invalid_argument& e) {
        std::cout << "ERROR - Invalid argument: not an integer" << std::endl;
        return 84;
    } catch (const std::out_of_range& e) {
        std::cout << "ERROR - Integer out of range" << std::endl;
        return 84;
    }
    return 0;
}


int Brain::about()
{
    std::cout << R"(name="Gomoku", version="1.0", author="Matthis and Louis", country="France")" << std::endl;
    return 0;
}

int Brain::end()
{
    return 1;
}

int Brain::display()
{
    for (auto const& cols : _minimax->_gameBoard) {
        bool first = true;
        for (auto const row : cols) {
            if (!first) {
                std::cout << "  ";
            } else {
                first = false;
            }
            if (row == 0)
                std::cout << ".";
            else
                std::cout << row;
        }
        std::cout << std::endl;
    }
    return 0;
}
