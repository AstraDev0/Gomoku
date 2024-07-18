/*
** EPITECH PROJECT, 2023
** B-AIA-500-LYN-5-1-gomoku-louis.de-caumont
** File description:
** utils
*/

#include "../includes/utils.hpp"

std::vector<std::string> split(const std::string& str, const std::string& delims)
{
    std::vector<std::string> tokens;
    std::string token;
    std::istringstream tokenStream(str);

    while (getline(tokenStream, token)) {
        size_t start = 0, end;
        while ((end = token.find_first_of(delims, start)) != std::string::npos) {
            if (end != start) {
                tokens.push_back(token.substr(start, end - start));
            }
            start = end + 1;
        }
        if (start < token.size()) {
            tokens.push_back(token.substr(start));
        }
    }
    return tokens;
}