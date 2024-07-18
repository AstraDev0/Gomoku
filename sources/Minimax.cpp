/*
** EPITECH PROJECT, 2023
** B-AIA-500-LYN-5-1-gomoku-louis.de-caumont
** File description:
** Minimax
*/

#include "../includes/Minimax.hpp"

Minimax::Minimax() = default;

Minimax::~Minimax() = default;

long Minimax::minimax(std::vector<std::vector<int>>& board, int depth, long alpha, long beta, bool isMaximizingPlayer, TranspositionTable& tt)
{
    if (depth == 0) return evaluate(board, isMaximizingPlayer);

    auto it = tt.find(board);
    if (it != tt.end())
        return it->second;

    std::vector<std::pair<int, int>> moves = generateMoves(board);
    sortMoves(moves, board);

    long bestVal = isMaximizingPlayer ? LONG_MIN_VAL : LONG_MAX_VAL;

    for (auto& move : moves) {
        board[move.first][move.second] = isMaximizingPlayer ? PLAYER1 : PLAYER2;
        long val = minimax(board, depth - 1, alpha, beta, !isMaximizingPlayer, tt);

        board[move.first][move.second] = EMPTY;
        if (isMaximizingPlayer) {
            bestVal = std::max(bestVal, val);
            alpha = std::max(alpha, val);
        } else {
            bestVal = std::min(bestVal, val);
            beta = std::min(beta, val);
        }
        if (beta <= alpha) {
            break;
        }
    }
    tt[board] = bestVal;
    return bestVal;
}

std::pair<int, int> Minimax::findBestMove(std::vector<std::vector<int>>& board, int maxDepth)
{
    std::pair<int, int> bestMove;
    long bestVal = LONG_MIN;
    TranspositionTable tt;
    for (int depth = 1; depth <= maxDepth; ++depth) {
    std::vector<std::pair<int, int>> moves = generateMoves(board);
    sortMoves(moves, board);
    for (auto& m : moves) {
        if (board[m.first][m.second] == EMPTY) {
            board[m.first][m.second] = PLAYER1;
            long val = minimax(board, depth - 1, LONG_MIN, LONG_MAX, false, tt);
            board[m.first][m.second] = EMPTY;
            if (val > bestVal) {
                bestVal = val;
                bestMove = m;
            }
        }
    }
}
    return bestMove;
}

int Minimax::evaluatePawn(saveParams *params, int pawn, Player player, bool turn)
{
	int score = 0x00;

    if (pawn == player) {
        params->countConsecutive++;
	} else if (pawn == EMPTY && params->countConsecutive > 0x00) {
        params->openEnds++;
        score += evaluateScore(params->countConsecutive, params->openEnds, turn);
        params->countConsecutive = 0x00;
        params->openEnds = 0x1;
    } else if (pawn == EMPTY) {
        params->openEnds = 0x1;
	} else if (params->countConsecutive > 0x00) {
        score += evaluateScore(params->countConsecutive, params->openEnds, turn);
        params->countConsecutive = 0x00;
        params->openEnds = 0x00;
    } else {
        params->openEnds = 0x00;
	}
    return score;
}

long Minimax::handleRestScore(saveParams *params, Player player, bool turn)
{
	long score = 0;

	if (params->countConsecutive > 0x00)
		score += evaluateScore(params->countConsecutive, params->openEnds, turn);
	params->countConsecutive = 0;
	params->openEnds = 0;
	return score;
}

long Minimax::evaluate(std::vector<std::vector<int>> &board, bool turn)
{
    long score = 0x00;
    std::map<int, saveParams> mp;

 	for (auto &row : board) {
        for (size_t x = 0; x < row.size(); ++x) {
            score += evaluatePawn(&mp[0], row[x], PLAYER1, turn);
            score -= evaluatePawn(&mp[1], row[x], PLAYER2, !turn);
        }
		score += handleRestScore(&mp[0], PLAYER1, turn);
		score -= handleRestScore(&mp[1], PLAYER2, !turn);
    }

    for (size_t x = 0; x < _boardSize; ++x) {
        for (size_t y = 0; y < _boardSize; ++y) {
            score += evaluatePawn(&mp[2], board[y][x], PLAYER1, turn);
            score -= evaluatePawn(&mp[3], board[y][x], PLAYER2, !turn);
        }
		score += handleRestScore(&mp[2], PLAYER1, turn);
		score -= handleRestScore(&mp[3], PLAYER2, !turn);
    }

    for (size_t y = 0; y < _boardSize; ++y) {
        for (size_t x = 0; y + x < _boardSize && x < _boardSize; ++x) {
			score += evaluatePawn(&mp[4],board[y + x][x], PLAYER1, turn);
            score -= evaluatePawn(&mp[5], board[y + x][x], PLAYER2, !turn);
        }
		score += handleRestScore(&mp[4], PLAYER1, turn);
		score -= handleRestScore(&mp[5], PLAYER2, !turn);
    }

    for (size_t y = 1; y < _boardSize; ++y) {
        for (size_t x = 0; x + y < _boardSize && x < _boardSize; ++x) {
 			score += evaluatePawn(&mp[6], board[x][x + y], PLAYER1, turn);
            score -= evaluatePawn(&mp[7], board[x][x + y], PLAYER2, !turn);
        }
		score += handleRestScore(&mp[6], PLAYER1, turn);
		score -= handleRestScore(&mp[7], PLAYER2, !turn);
    }

	for (size_t y = 0; y < _boardSize; ++y) {
  		for (size_t x = y; x < _boardSize && x >= 0 ; --x) {
          
 			score += evaluatePawn(&mp[7], board[y - x][x], PLAYER1, turn);
            score -= evaluatePawn(&mp[8], board[y - x][x], PLAYER2, !turn);
        }
		score += handleRestScore(&mp[7], PLAYER1, turn);
		score -= handleRestScore(&mp[8], PLAYER2, !turn);
    }

    for (size_t y = 1; y < _boardSize; ++y) {
        for (size_t x = _boardSize - 1; (y + (_boardSize - 1 - x)) < _boardSize && x >= 0; --x) {
            score += evaluatePawn(&mp[9], board[y + (_boardSize - 1 - x)][x], PLAYER1, turn);
            score -= evaluatePawn(&mp[10], board[y + (_boardSize - 1 - x)][x], PLAYER2, !turn);
        }
        score += handleRestScore(&mp[9], PLAYER1, turn);
        score -= handleRestScore(&mp[10], PLAYER2, !turn);
    }
    return score;
}

long Minimax::evaluateScore(int consecutive, int openEnds, bool currentTurn)
{
    switch (consecutive) {
        case 4:
            switch (openEnds) {
                case 1:
                    return currentTurn ? 1000000 : 100000;
                case 2:
                    return currentTurn ? 10000000 : 500000;
            }
            break;
        case 3:
            switch (openEnds) {
                case 1:
                    return currentTurn ? 200 : 100;
                case 2:
                    return currentTurn ? 50000 : 25000;
            }
            break;
        case 2:
            switch (openEnds) {
                case 1:
                    return 50;
                case 2:
                    return 100;
            }
            break;
        case 1:
            switch (openEnds) {
                case 1:
                    return 1;
                case 2:
                    return 2;
            }
            break;
        default:
            return 200000000;
    }
    return 0;
}


void Minimax::sortMoves(std::vector<std::pair<int, int>>& moves, const std::vector<std::vector<int>>& board)
{
    std::sort(moves.begin(), moves.end(), [&board, this](const std::pair<int, int>& a, const std::pair<int, int>& b) {
        int scoreA = movePriorityScore(board, a.first, a.second);
        int scoreB = movePriorityScore(board, b.first, b.second);
        return scoreA > scoreB;
    });
}

int Minimax::movePriorityScore(const std::vector<std::vector<int>>& board, int y, int x)
{
    int score = 0;

    for (int dy = -1; dy <= 1; dy++) {
        for (int dx = -1; dx <= 1; dx++) {
            if (dy == 0 && dx == 0) continue;

            int newY = y + dy;
            int newX = x + dx;
            if (newY >= 0 && newY < static_cast<int>(board.size()) &&
                newX >= 0 && newX < static_cast<int>(board[newY].size()) &&
                board[newY][newX] != EMPTY) {
                score += 10;
            }
        }
    }

    return score;
}

std::vector<std::pair<int, int>> Minimax::generateMoves(const std::vector<std::vector<int>>& board)
{
    std::vector<std::pair<int, int>> moves;
    std::vector<std::pair<int, int>> defensiveMoves;

    for (size_t y = 0; y < board.size(); ++y) {
        for (size_t x = 0; x < board[y].size(); ++x) {
            if (board[y][x] == EMPTY) {
                if (isAdjacentToStone(board, y, x)) {
                    moves.emplace_back(y, x);
                }
                if (isDefensiveMove(board, y, x)) {
                    moves.emplace_back(y, x);
                }
            }
        }
    }

    defensiveMoves.insert(defensiveMoves.end(), moves.begin(), moves.end());
    return defensiveMoves;
}

bool Minimax::isDefensiveMove(const std::vector<std::vector<int>>& board, int y, int x)
{
    for (int player = PLAYER1; player <= PLAYER2; player++) {
        if (wouldBlockLine(board, y, x, static_cast<Player>(player))) {
            return true;
        }
    }
    return false;
}

bool Minimax::wouldBlockLine(const std::vector<std::vector<int>>& board, int y, int x, Player player)
{
    return checkLine(board, y, x, 0, 1, player) ||
           checkLine(board, y, x, 1, 0, player) ||
           checkLine(board, y, x, 1, 1, player) ||
           checkLine(board, y, x, 1, -1, player);
}

bool Minimax::checkLine(const std::vector<std::vector<int>>& board, int startY, int startX, int deltaY, int deltaX, Player player)
{
    int count = 0;

    for (int i = 0; i < 3; ++i) {
        int y = startY + i * deltaY;
        int x = startX + i * deltaX;

        if (y >= 0 && y < _boardSize && x >= 0 && x < _boardSize && board[y][x] == player) {
            count++;
        }
    }
    return count >= 2;
}

bool Minimax::isAdjacentToStone(const std::vector<std::vector<int>>& board, int y, int x)
{
    for (int dy = -2; dy <= 2; dy++) {
        for (int dx = -2; dx <= 2; dx++) {
            if (dy == 0 && dx == 0) continue;

            int newY = y + dy;
            int newX = x + dx;
            if (newY >= 0 && newY < _boardSize &&
                newX >= 0 && newX < _boardSize &&
                board[newY][newX] != EMPTY) {
                return true;
            }
        }
    }
    return false;
}

void Minimax::newPawn(int y, int x, Player player)
{
    _gameBoard[y][x] = player;
}

std::pair<int, int> Minimax::run()
{
    return findBestMove(_gameBoard, 1);
}
