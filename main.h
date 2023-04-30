// main.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <conio.h>
#include <iostream>
#include <dirent.h>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>
#include <opencv2/core/utility.hpp>
#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include "opencv2/imgproc.hpp"
#include <algorithm>
#include <iterator>

using namespace cv;
using namespace std;

static int parseParameters(int argc, char** argv, string* imageFile);
void mouse_click(int event, int x, int y, int flags, void *param);
