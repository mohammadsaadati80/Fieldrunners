#ifndef TESLA_H
#define TESLA_H "TESLA_H"
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
#define TESLA_FIRST_POS_X 120
#define TESLA_FIRST_POS_Y 177
#define BACKGROUND_SQUARE_LENGHT 60
#define TESLA1_IMAGE_FILE_ADDRESS_1 "Assets/towers/tesla/tesla1/1.png"
#define TESLA1_IMAGE_FILE_ADDRESS_2 "Assets/towers/tesla/tesla1/2.png"
#define TESLA2_IMAGE_FILE_ADDRESS_1 "Assets/towers/tesla/tesla2/1.png"
#define TESLA2_IMAGE_FILE_ADDRESS_2 "Assets/towers/tesla/tesla2/2.png"
#define TESLA3_IMAGE_FILE_ADDRESS_1 "Assets/towers/tesla/tesla3/1.png"
#define TESLA3_IMAGE_FILE_ADDRESS_2 "Assets/towers/tesla/tesla3/2.png"
#define TESLA_IMAGE_WIDTH 60
#define TESLA_IMAGE_HEIGHT 61
#define TESLA_DAMAGE 700
#define TESLA_ATTACK_SPEED 150
#define TESLA_BUILDING_COST 120
#define TESLA_UPGRADE_COST 100
#define TESLA_UPGRADE_DAMAGE 1000
#define TESLA_ATTACK_DISTANCE 150
#define X 0
#define Y 1
#define ATTACKING 0
#define NOT_ATTACKING 1
#define TESLA_ATTACK_TURN 19
#define TESLA_FIRST_ARROW_POS_X 25
#define TESLA_FIRST_ARROW_POS_Y 31
#define ARROW_REDIUS 5
#define TESLA_ARROW_IMAGE_ADDRESS "./Assets/arrow/t2.png"
#define ATTACK_TIME 20
#define TESLA_ATTACK_SOUND_ADDRESS "./Assets/tesla.wav"


class Tesla {
public:
    void initialization(Point mouse_position);
    void draw(Window* window);
    void draw_tower(Window* window);
    void draw_attacking_tower(Window* window);
    void draw_not_attacking_tower(Window* window);
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