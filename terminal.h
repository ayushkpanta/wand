#ifndef TERMINAL_H
#define TERMINAL_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <unistd.h>
#include <limits.h>
#include <vector>

void cdCommand(std::string commandInput);

// void interactWithTerminal_TEST(std::string commandInput);

void interactWithTerminal_OG(std::string commandInput, int clientSocket);

#endif
