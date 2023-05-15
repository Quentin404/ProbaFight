#pragma once

#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

template <typename T> void say(const T &s) { std::cout << s << "\n"; }

template <typename T, typename... Args>
void say(const T &s, const Args &...args) {
  std::cout << s;
  say(args...);
}

int stringToInt(const string &str);

string ask(string channel, string question);

bool quit();