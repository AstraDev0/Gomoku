/*
** EPITECH PROJECT, 2023
** B-AIA-500-LYN-5-1-gomoku-louis.de-caumont
** File description:
** Minimax
*/

#ifndef MINIMAX_HPP_
#define MINIMAX_HPP_

#include <vector>
#include <iostream>
#include <stack>
#include <climits>
#include <limits>
#include <unordered_map>
#include <algorithm>
#include <map>
enum Player { EMPTY, PLAYER1, PLAYER2 };

const long LONG_MIN_VAL = LONG_MIN;
const long LONG_MAX_VAL = LONG_MAX;

struct saveParams {
    int openEnds;
    int countConsecutive;
};

struct BoardHash {
    size_t operator()(const std::vector<std::vector<int>>& board) const {
        const size_t prime = 31;
        size_t hashValue = 0;

        for (const auto & i : board) {
            for (int j : i) {
                hashValue = hashValue * prime + j;
            }
        }

        return hashValue;
    }
};

using TranspositionTable = std::unordered_map<std::vector<std::vector<int>>, long, BoardHash>;

class Minimax {
public:
    Minimax();
    ~Minimax();
    std::pair<int, int> findBestMove(std::vector<std::vector<int>>& board, int depth);
    long minimax(std::vector<std::vector<int>>& board, int depth, long alpha, long beta, bool isMaximizingPlayer, TranspositionTable& tt);
    std::pair<int, int> run(std::vector<std::vector<int>>& board);
    static long evaluateScore(int consecutive, int openEnds, bool currentTurn);
    long evaluate(std::vector<std::vector<int>>& board, bool turn);
    void sortMoves(std::vector<std::pair<int, int>>& moves, const std::vector<std::vector<int>>& board);
    static int movePriorityScore(const std::vector<std::vector<int>>& board, int y, int x);
    std::vector<std::pair<int, int>> generateMoves(const std::vector<std::vector<int>>& board);
    bool isAdjacentToStone(const std::vector<std::vector<int>>& board, int y, int x);
    bool isDefensiveMove(const std::vector<std::vector<int>>& board, int y, int x);
    bool wouldBlockLine(const std::vector<std::vector<int>>& board, int y, int x, Player player);
    bool checkLine(const std::vector<std::vector<int>>& board, int startY, int startX, int deltaY, int deltaX, Player player);
    bool analyzeThreats(const std::vector<std::vector<int>>& board, std::pair<int, int>& bestMove);
    int evaluateThreatLevel(const std::vector<std::vector<int>>& board, int y, int x);
    int checkLineThreat(const std::vector<std::vector<int>>& board, int y, int x, int deltaY, int deltaX);
    long checkDirectionOffense(const std::vector<std::vector<int>>& board, int startY, int startX, int deltaY, int deltaX, int player);
    void newPawn(int y, int x, Player player);
    int evaluatePawn(saveParams *params, int pawn, Player player, bool turn);
    std::pair<int, int> run();
    long handleRestScore(saveParams *params, Player player, bool turn);
    int _boardSize;
    std::vector<std::vector<int>> _gameBoard;
};

#endif /* !MINIMAX_HPP_ */