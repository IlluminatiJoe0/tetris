#include "colors.h"

#include <vector>

const Color darkGrey = {20, 20, 20, 255};
const Color red = {255, 0, 0, 255};
const Color yellow = {255, 255, 0, 255};
const Color green = {0, 255, 0, 255};
const Color blue = {0, 0, 255, 255};
const Color cyan = {0, 255, 255, 255};
const Color magenta = {255, 0, 255, 255};
const Color orange = {255, 128, 0, 255};
const Color lightBlue = {59, 85, 162, 255};
const Color darkBlue = {44, 44, 127, 255};

std::vector<Color> getCellColors() {
    return {darkGrey, red, yellow, green, blue, cyan, magenta, orange};
}