#ifndef SCRAMBLER_H
#define SCRAMBLER_H "SCRAMBLER_H"
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

#define DELAY 10
#define FIRST_X 0 
#define FIRST_Y 1
#define SCRAMBLER_FIRST_POS_X 124
#define SCRAMBLER_FIRST_POS_Y 179
#define BACKGROUND_SQUARE_LENGHT 60
#define SCRAMBLER_IMAGE_FILE_ADDRESS "Assets/enemies/scrambler.png"
#define SCRAMBLER_IMAGE_FILE_ADDRESS_DOWN "./Assets/enemies/Bike/bike_run_down_"
#define SCRAMBLER_IMAGE_FILE_ADDRESS_RIGHT "./Assets/enemies/Bike/bike_run_right_"
#define SCRAMBLER_IMAGE_FILE_ADDRESS_UP "./Assets/enemies/Bike/bike_run_up_"
#define PNG ".png"
#define SCRAMBLER_SPEED 90
#define X 0
#define Y 1
#define SCRAMBLER_INITIAL_HEALTH 100
#define SCRAMBLER_IMAGE_WIDTH  55
#define SCRAMBLER_IMAGE_HEIGHT 62
#define HEALTH_TAPE_LENGHT 52
#define ALIVE 1
#define DEAD 0
#define SCRAMBLER_KILLING_REWARD 4
#define SCRAMBLER_REDUCE_PLAYER_HEALTH 2
#define MOVING 1
#define NOT_MOVING 0
#define NOT_MOVING_COUNTED 2
#define REDUCED 1
#define NOT_REDUCED 0
#define UP 1
#define DOWN 2
#define RIGHT 3
#define LEFT 4
#define ENEMY_HEALTH_BASE 0.9
#define ENEMY_HEALTH_ADDITIONAL 0.1
#define SCRAMBLER_REPEAT_THE_IMAGE 3
#define SCRAMBLER_ALL_IMAGE_REPEATED 11
#define ZERO_CHARACTER '0'


class Scrambler {
public:
    void first_pos(std::vector<int> enemies_path,int wave);
    void update(Window* window);
    void find_next_direction();
    void update_current_pos();
    void check_reach_the_end_of_the_path();
    void draw(Window* window);
    void draw_image(Window* window);
    std::string convert_number_to_string(int number);
    float get_position_x();
    float get_position_y();
    void reduce_health(int reduce_health_amount);
    void reduce_speed(float decrease_amount, int decrease_speed_time);
    int check_health();
    int check_not_being_killed();
    int get_status();
    int get_moving_status();
    int get_reduce_speed_status();

private:
    float position[2];
    int current_house[2];
    std::vector<int> enemie_path;
    float health;
    int status;
    int moving_status;
    float initial_health;
    float speed;
    float reduce_speed_size;
    int reduce_speed_time;
    int current_reduce_speed_time;
    int reduce_speed_status;
    int image_count;
    int movement_direction;
};

#endif