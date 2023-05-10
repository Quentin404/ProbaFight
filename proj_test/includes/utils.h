#pragma once

#include <algorithm>
#include <iostream>

using namespace std;

template <typename T> void say(const T &s) { std::cout << s << "\n"; }

template <typename T, typename... Args>
void say(const T &s, const Args &...args) {
  std::cout << s << " ";
  say(args...);
}

string ask(string question);

bool quit();