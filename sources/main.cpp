/*
** EPITECH PROJECT, 2023
** B-AIA-500-LYN-5-1-gomoku-louis.de-caumont
** File description:
** main
*/

#include "../includes/main.hpp"

int main(int argc, char **argv)
{
    Protocol *protocol = new Protocol();
    protocol->run();
    delete protocol;
}