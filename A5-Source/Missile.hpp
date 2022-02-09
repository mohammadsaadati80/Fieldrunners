#ifndef MISSILE_H
#define MISSILE_H "MISSILE_H"
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
#define MISSILE_FIRST_POS_X 113
#define MISSILE_FIRST_POS_Y 169
#define BACKGROUND_SQUARE_LENGHT 60
#define MISSILE_IMAGE_FILE_ADDRESS_1 "Assets/towers/missile1.png"
#define MISSILE_IMAGE_FILE_ADDRESS_2 "Assets/towers/missile2.png"
#define MISSILE_IMAGE_FILE_ADDRESS_3 "Assets/towers/missile3.png"
#define MISSILE_ATTACK_IMAGE_FILE_ADDRESS_1 "Assets/towers/missile/missile1/"
#define MISSILE_ATTACK_IMAGE_FILE_ADDRESS_2 "Assets/towers/missile/missile2/"
#define MISSILE_ATTACK_IMAGE_FILE_ADDRESS_3 "Assets/towers/missile/missile3/"
#define PNG ".png"
#define MISSILE_IMAGE_LENGHT 75
#define MISSILE_DAMAGE 75
#define MISSILE_ATTACK_SPEED 300
#define MISSILE_BUILDING_COST 70
#define MISSILE_UPGRADE_COST 60
#define MISSILE_UPGRADE_DAMAGE 75
#define MISSILE_ATTACK_DISTANCE 150
#define MISSILE_DAMAGE_DISTANCE 50
#define X 0
#define Y 1
#define ATTACKING 0
#define NOT_ATTACKING 1
#define PI 3.14159265
#define ZERO_CHARACTER '0'
#define MISSILE_ATTACK_TURN 19
#define MISSILE_FIRST_ARROW_POS_X 40
#define MISSILE_FIRST_ARROW_POS_Y 40
#define ARROW_REDIUS 5
#define MISSILE_ARROW_IMAGE_ADDRESS "./Assets/arrow/m2.png"
#define ATTACK_TIME 20
#define MISSILE_ATTACK_SOUND_ADDRESS "./Assets/missile.wav"


class Missile {
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
    int get_damage();
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
    int damage;
    int status;
    int attack_time;
};

#endif