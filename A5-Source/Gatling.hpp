#ifndef GATLING_H
#define GATLING_H "GATLING_H"
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
#define GATLING_FIRST_POS_X 108
#define GATLING_FIRST_POS_Y 170
#define BACKGROUND_SQUARE_LENGHT 60
#define GATLING_IMAGE_FILE_ADDRESS_1 "Assets/towers/gattling1.png"
#define GATLING_IMAGE_FILE_ADDRESS_2 "Assets/towers/gattling2.png"
#define GATLING_IMAGE_FILE_ADDRESS_3 "Assets/towers/gattling3.png"
#define GATLING_ATTACK_IMAGE_FILE_ADDRESS_1 "Assets/towers/gattling/Gattling1/"
#define GATLING_ATTACK_IMAGE_FILE_ADDRESS_2 "Assets/towers/gattling/Gattling2/"
#define GATLING_ATTACK_IMAGE_FILE_ADDRESS_3 "Assets/towers/gattling/Gattling3/"
#define GATLING_ATTACK_SHOOT_IMAGE_FILE_ADDRESS_1 "Assets/towers/gattling/Gattling1/shoot/"
#define GATLING_ATTACK_SHOOT_IMAGE_FILE_ADDRESS_2 "Assets/towers/gattling/Gattling2/shoot/"
#define GATLING_ATTACK_SHOOT_IMAGE_FILE_ADDRESS_3 "Assets/towers/gattling/Gattling3/shoot/"
#define PNG ".png"
#define GATLING_IMAGE_LENGHT 84
#define GATLING_DAMAGE 35
#define GATLING_ATTACK_SPEED 100
#define GATLING_BUILDING_COST 55
#define GATLING_UPGRADE_COST 40
#define GATLING_UPGRADE_DAMAGE 35
#define GATLING_ATTACK_DISTANCE 150
#define X 0
#define Y 1
#define ATTACKING 0
#define NOT_ATTACKING 1
#define PI 3.14159265
#define ZERO_CHARACTER '0'
#define GATLING_ATTACK_TURN 19
#define GATLING_FIRST_ARROW_POS_X 40
#define GATLING_FIRST_ARROW_POS_Y 30
#define ARROW_REDIUS 5
#define GATLING_ARROW_IMAGE_ADDRESS "./Assets/arrow/g2.png"
#define ATTACK_TIME 20
#define GATLING_ATTACK_SOUND_ADDRESS "./Assets/gatling.wav"


class Gatling {
public:
    void initialization(Point mouse_position);
    void draw(Window* window);
    void draw_not_attacking_tower(Window* window);
    void draw_tower(Window* window);
    void draw_normal_tower(Window* window, double angle);
    void draw_normal_shooting_tower(Window* window, std::string num);
    void draw_normal_not_shooting_tower(Window* window, std::string num);
    void draw_horizontal_tower(Window* window, double angle);
    void draw_horizontal_shooting_tower(Window* window, std::string num);
    void draw_horizontal_not_shooting_tower(Window* window, std::string num);
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