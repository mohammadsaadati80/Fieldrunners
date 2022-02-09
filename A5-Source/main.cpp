#include "rsdl.hpp"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <math.h>
#include <iomanip>
#include "Fieldrunners.hpp"
using namespace std;

int main(int argc, char* argv[])
{
    Fieldrunners fieldrunners;
    fieldrunners.get_input();
    Window *window = new Window(GAME_WINDOW_LENGHT, GAME_WINDOW_HEIGHT, GAME_WINDOW_NAME);
    while(true)
    {
        fieldrunners.update(window);
        fieldrunners.draw(window);
        delay(DELAY);
        fieldrunners.upgrade_time_count();
        fieldrunners.check_end_game();
    }
    return 0;
}