#pragma once
#include <fcntl.h>
#include <iostream>
#include <string>
#include <sys/wait.h>
#include <unistd.h>
//#define debug
using namespace std;
const int BUFFER_SIZE = 4096;
void debug_message(const string &message);

void SetNonBlocking(int fd);