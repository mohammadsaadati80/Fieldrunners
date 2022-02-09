#ifndef GLUE_H
#define GLUE_H "GLUE_H"
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
#define FIRST_HOUSE_TABLE_X 125
#define FIRST_HOUSE_TABLE_Y 179
#define GLUE_FIRST_POS_X 117
#define GLUE_FIRST_POS_Y 174
#define BACKGROUND_SQUARE_LENGHT 60
#define GLUE_IMAGE_FILE_ADDRESS_1 "Assets/towers/glue1.png"
#define GLUE_IMAGE_FILE_ADDRESS_2 "Assets/towers/glue2.png"
#define GLUE_IMAGE_FILE_ADDRESS_3 "Assets/towers/glue3.png"
#define GLUE_ATTACK_IMAGE_FILE_ADDRESS_1 "Assets/towers/goo/glue1/"
#define GLUE_ATTACK_IMAGE_FILE_ADDRESS_2 "Assets/towers/goo/glue2/"
#define GLUE_ATTACK_IMAGE_FILE_ADDRESS_3 "Assets/towers/goo/glue3/"
#define PNG ".png"
#define GLUE_IMAGE_LENGHT 70
#define GLUE_REDUCE_SPEED 0.4
#define GLUE_ATTACK_SPEED 200
#define GLUE_REDUCE_SPEED_TIME 250
#define GLUE_BUILDING_COST 60
#define GLUE_UPGRADE_COST 45
#define GLUE_UPGRADE_REDUCE_SPEED 0.1
#define GLUE_UPGRADE_REDUCE_SPEED_TIME 50
#define GLUE_ATTACK_DISTANCE 150
#define GLUE_DAMAGE_DISTANCE 30
#define X 0
#define Y 1
#define ATTACKING 0
#define NOT_ATTACKING 1
#define PI 3.14159265
#define ZERO_CHARACTER '0'
#define GLUE_ATTACK_TURN 19
#define GLUE_FIRST_ARROW_POS_X 35
#define GLUE_FIRST_ARROW_POS_Y 35
#define ARROW_REDIUS 5
#define GLUE_ARROW_IMAGE_ADDRESS "./Assets/arrow/l2.png"
#define ATTACK_TIME 20
#define GLUE_ATTACK_SOUND_ADDRESS "./Assets/glue.wav"


class Glue {
public:
    void initialization(Point mouse_position);
    void draw(Window* window);
    void draw_not_attacking_tower(Window* window);
    void draw_tower(Window* window);
    void draw_normal_tower(Window* window, double angle);
    void draw_horizontal_tower(Window* window, double angle);
    double calculate_angle_between_tower_and_enemy(float current_enemy_position[2], float position[2]);
    std::string convert_number_to_string(int number);
    void draw_attack_arrow(Window* window);
    bool check_enemies_distance(float enemie_position[2]);
    float distance_size(float enemie_pos[2]);
    int get_status();
    void fill_enemie_details(int enemy_type ,int enemy_num);
    float get_damage();
    int get_reduce_speed_time();
    int get_house_position_x();
    int get_house_position_y();
    void upgrade();
    int get_enemy_type();
    int get_enemy_number();
    int get_attack_time();
    void change_attack_status();
    void fill_current_enemy_position(float current_enemy_position[2]);

private:
    float position[2];
    int house_position[2];
    int state;
    float current_enemy_position[2];
    int enemy_house[2];
    int enemy_number;
    int enemie_type;
    float attack_circle_position[2];
    float reduce_speed;
    int status;
    int attack_time;
    int reduce_speed_time;
};

#endif