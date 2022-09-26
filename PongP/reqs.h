#pragma once
//purpose of file is to just add all the important headers
#include<iostream>
#include<SFML/Graphics.hpp>
#include<string>
#include<SFML/Audio.hpp>
//resolution
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 800;
const int GameMode = 1;
//might add networking
#define DEBUG 0
#if DEBUG 
#define LOG(x) std::cout << x << "\n";//please killme
#else
#define LOG(x);
#endif
