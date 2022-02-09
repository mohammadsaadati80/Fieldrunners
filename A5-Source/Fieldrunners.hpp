#ifndef FIELDRUNNERS_H
#define FIELDRUNNERS_H "FIELDRUNNERS_H"
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
#include "rsdl.hpp"
#include "The_Runner.hpp"
#include "Stubborn_Runner.hpp"
#include "Super_Trooper.hpp"
#include "Scrambler.hpp"
#include "Gatling.hpp"
#include "Tesla.hpp"
#include "Missile.hpp"
#include "Glue.hpp"

#define DELAY 10
#define PATH_OF_THE_ENEMIES 0
#define SEPARATOR ' '
#define FIRST_VALID_WAVE_LINE 1
#define BACKGROUND_IMAGE_FILE_ADDRESS "./Assets/background.png"
#define HEART_IMAGE_FILE_ADDRESS "./Assets/heart.png"
#define MONEY_IMAGE_FILE_ADDRESS "./Assets/money.png"
#define FONT_ADDRESS "./Assets/OpenSans.ttf"
#define LOSE_IMAGE_ADDRESS "./Assets/you_lose.jpg"
#define WIN_IMAGE_ADDRESS "./Assets/you_win.jpg"
#define YOU_WIN_MUSIC_ADDRESS "./Assets/you_win.mp3"
#define BACKGROUND_MUSIC_ADDRESS "./Assets/17.Flight School.mp3"
#define BACKGROUND_MUSIC_BEFORE_LOSE_ADDRESS "./Assets/04.Hunted.mp3"
#define YOU_LOSE_MUSIC_ADDRESS "./Assets/02.The War to End All Wars.mp3"
#define TILE_ADDRESS "./Assets/tile/tile"
#define JPG ".jpg"
#define REDUCE_PLAYER_LIFE_OF_THE_RUNNER 1
#define REDUCE_PLAYER_LIFE_OF_STUBBORN_RUNNER 4
#define REDUCE_PLAYER_LIFE_OF_SUPER_TROOPER 4
#define REDUCE_PLAYER_LIFE_OF_SCRAMBLER 2
#define PLAYER_INITIAL_HEARTS 20
#define PLAYER_INITIAL_GOLD 200
#define SQUARE_FIRST_POS_X 120
#define SQUARE_FIRST_POS_Y 172
#define SQUARE_LENGHT 2
#define PLAYING_GAME 0
#define WIN 1
#define LOSE -1
#define THE_RUNNER 1
#define STUBBORN_RUNNER 2
#define SUPER_TROOPER 3
#define SCRAMBLER 4
#define ENEMY_TYPE 0
#define ENEMY_NUMBER 1
#define ENEMY_DISTANCE 2
#define PLAY_WIN_MUSIC 2
#define PLAY_LOSE_MUSIC -1
#define PLAY_BACKGROUND_MUSIC 1
#define PLAY_BACKGROUND_MUSIC_BEFORE_LOSE 3
#define NOT_PLAY_MUSIC 0
#define DELAY_BETWEEN_WAVES 2990
#define GATLING_INSERT_KEY 'g'
#define TESLA_INSERT_KEY 't'
#define MISSILE_INSERT_KEY 'm'
#define GLUE_INSERT_KEY 'l'
#define UPDATE_TOWER_INSERT_KEY 'u'
#define TIME_BETWEEN_INSERT_ENEMIES 50
#define DESIRED_PLAYER_HEALTH_FOR_PLAY_BACKGROUND_MUSIC_BEFORE_LOSE 8
#define GAME_WINDOW_LENGHT 1365
#define GAME_WINDOW_HEIGHT 1024
#define GAME_WINDOW_NAME "FieldRunners"
#define HEART_IMAGE_POS_X 1295
#define HEART_IMAGE_POS_Y 10 
#define HEART_IMAGE_LENGHT 60 
#define HEART_IMAGE_HIEGHT 60
#define MONEY_IMAGE_POS_X 7
#define MONEY_IMAGE_POS_Y 6 
#define MONEY_IMAGE_LENGHT 60 
#define MONEY_IMAGE_HIEGHT 75
#define PLAYER_INFORMATION_FONT_SIZE 30
#define PLAYER_INFORMATION_POS_Y 20
#define PLAYER_GOLD_INFORMATION_POS_X 60
#define PLAYER_HEART_INFORMATION_POS_X 1260
#define ROUND_TEXT "Round:"
#define ROUND_TEXT_POS_X 620
#define ROUND_NUMBER_POS_X 730
#define MOUSE_HOUSE_IMAGE_ADDRESS "./Assets/mousehouse.png"
#define START_FLAG_IMAGE_ADDRESS "./Assets/start.png"
#define END_FLAG_IMAGE_ADDRESS "./Assets/end.png"
#define FIRST_X 0
#define FIRST_Y 1
#define LAST_X 2
#define LAST_Y 1
#define FLAG_CALIBER_X 5
#define FLAG_CALIBER_Y 7
#define THE_RUNNER_BACKGROND_IMAGE_ADDRESS "./Assets/runner.png"
#define STUBBORN_RUNNER_BACKGROND_IMAGE_ADDRESS "./Assets/stubborn-runner.png"
#define SUPER_TROOPER_BACKGROND_IMAGE_ADDRESS "./Assets/supertrooper.png"
#define SCRAMBLER_BACKGROND_IMAGE_ADDRESS "./Assets/scrambler.png"
#define GATLING_BACKGROND_IMAGE_ADDRESS "./Assets/gattling.png"
#define TESLA_BACKGROND_IMAGE_ADDRESS "./Assets/tesla.png"
#define MISSILE_BACKGROND_IMAGE_ADDRESS "./Assets/missile.png"
#define GLUE_BACKGROND_IMAGE_ADDRESS "./Assets/glue.png"
#define BUILDING_COST "Building Cost:"
#define UPGRADE_COST "Upgrade Cost:"
#define IMAGE_DETAILS_POS_Y 850
#define TEXT_DETAILS_LINE_ONE_POS_Y 900
#define TEXT_DETAILS_LINE_TWO_POS_Y 950
#define ENEMY_DETAILS_TEXT_POS_X 10
#define FIRST_ENEMY_DETAILS_TEXT_POS_X 260
#define DISTANCE_BETWEEN_NUMBER_TEXT 100
#define TOWER_DETAILS_TEXT_POS_X 680
#define FIRST_TOWER_DETAILS_TEXT_POS_X 920
#define KILLING_REWARD "Killing Reward:"
#define REDUCE_HEALTH "Reduce Health:"


typedef struct enemies Enemies;
typedef struct player Player;
typedef struct towers Towers;

struct enemies {
    std::vector<The_Runners> the_runners_info;
    std::vector<Stubborn_Runner> stubborn_runners_info;
    std::vector<Super_Trooper> super_troopers_info;
    std::vector<Scrambler> scramblers_info;
};

struct player {
    int hearts;
    int gold;
    int status;
};

struct towers {
    std::vector<Gatling> gatling_info;
    std::vector<Tesla> tesla_info;
    std::vector<Missile> missile_info;
    std::vector<Glue> glue_info;
};

class Fieldrunners {
public:
    void get_input();
    std::vector<std::string> read_input_waves_lines();
    std::vector<int> separate_the_number_in_string_line(std::string path_of_the_enemies);
    int convert_number_string_to_int(std::string line_element);
    std::vector<std::vector<int> > calculate_input_waves(std::vector<std::string> input_waves_file_lines);
    void update(Window* window);
    void check_pressed_key(char &pressed_key);
    void create_new_gatling_tower();
    void create_new_tesla_tower();
    void create_new_missile_tower();
    void create_new_glue_tower();
    void update_tower();
    void check_for_update_gatling(float house_position[2]);
    void check_for_update_tesla(float house_position[2]);
    void check_for_update_missile(float house_position[2]);
    void check_for_update_glue(float house_position[2]);
    void check_can_insert_new_enemeis();
    bool check_can_insert_new_the_runner();
    bool check_can_insert_new_stubborn_runners();
    bool check_can_insert_new_super_trooper();
    bool check_can_insert_new_scrambler();
    void check_for_attack();
    void check_for_attack_with_gatling();
    std::vector<float> find_enemies_in_the_range_of_gatling(int current_tower);
    std::vector<float> create_vector();
    void find_the_runners_in_the_range_of_gatling(int current_tower, std::vector<float> &closest_enemies_in_the_range_of_tower);
    void find_stubborn_runners_in_the_range_of_gatling(int current_tower, std::vector<float> &closest_enemies_in_the_range_of_tower);
    void find_super_trooper_in_the_range_of_gatling(int current_tower, std::vector<float> &closest_enemies_in_the_range_of_tower);
    void find_scrambler_in_the_range_of_gatling(int current_tower, std::vector<float> &closest_enemies_in_the_range_of_tower);
    void attack_with_gatling_on_the_runner(int current_gatling);
    void attack_with_gatling_on_stubborn_runners(int current_gatling);
    void attack_with_gatling_on_super_trooper(int current_gatling);
    void attack_with_gatling_on_scrambler(int current_gatling);
    void check_for_attack_with_tesla();
    std::vector<float> find_enemies_in_the_range_of_tesla(int current_tower);
    void find_the_runners_in_the_range_of_tesla(int current_tower, std::vector<float> &closest_enemies_in_the_range_of_tower);
    void find_stubborn_runners_in_the_range_of_tesla(int current_tower, std::vector<float> &closest_enemies_in_the_range_of_tower);
    void find_super_trooper_in_the_range_of_tesla(int current_tower, std::vector<float> &closest_enemies_in_the_range_of_tower);
    void find_scrambler_in_the_range_of_tesla(int current_tower, std::vector<float> &closest_enemies_in_the_range_of_tower);
    void attack_with_tesla_on_the_runner(int current_gatling);
    void attack_with_tesla_on_stubborn_runners(int current_gatling);
    void attack_with_tesla_on_super_trooper(int current_gatling);
    void attack_with_tesla_on_scrambler(int current_gatling);
    void check_for_attack_with_missile();
    std::vector<float> find_enemies_in_the_range_of_missile(int current_tower);
    void find_the_runners_in_the_range_of_missile(int current_tower, std::vector<float> &closest_enemies_in_the_range_of_tower);
    void find_stubborn_runners_in_the_range_of_missile(int current_tower, std::vector<float> &closest_enemies_in_the_range_of_tower);
    void find_super_trooper_in_the_range_of_missile(int current_tower, std::vector<float> &closest_enemies_in_the_range_of_tower);
    void find_scrambler_in_the_range_of_missile(int current_tower, std::vector<float> &closest_enemies_in_the_range_of_tower);
    void attack_with_missile_on_the_runner(int current_missile);
    void attack_with_missile_on_stubborn_runners(int current_missile);
    void attack_with_missile_on_super_trooper(int current_missile);
    void attack_with_missile_on_scrambler(int current_missile);
    void check_for_atteck_with_missile_on_another_enemies(int current_missile, float current_the_enemy_position[2]);
    std::vector<int> find_enemies_close_to_the_current_enemy(float current_the_enemy_position[2], int distance);
    void find_the_runner_close_to_the_current_enemy(float first_enemy_position[2], std::vector<int> &enemies_in_the_range_of_input_enemy, int distance);
    void find_stubborn_runners_close_to_the_current_enemy(float first_enemy_position[2], std::vector<int> &enemies_in_the_range_of_input_enemy, int distance);
    void find_super_trooper_close_to_the_current_enemy(float first_enemy_position[2], std::vector<int> &enemies_in_the_range_of_input_enemy, int distance);
    void find_scrambler_close_to_the_current_enemy(float first_enemy_position[2], std::vector<int> &enemies_in_the_range_of_input_enemy, int distance);
    bool calculate_the_distance_between_two_enemies(float first_enemy_position[2], float current_the_enemy_position[2], int distance);
    void check_for_attack_with_glue();
    std::vector<float> find_enemies_in_the_range_of_glue(int current_tower);
    void find_the_runners_in_the_range_of_glue(int current_tower, std::vector<float> &closest_enemies_in_the_range_of_tower);
    void find_stubborn_runners_in_the_range_of_glue(int current_tower, std::vector<float> &closest_enemies_in_the_range_of_tower);
    void find_super_trooper_in_the_range_of_glue(int current_tower, std::vector<float> &closest_enemies_in_the_range_of_tower);
    void find_scrambler_in_the_range_of_glue(int current_tower, std::vector<float> &closest_enemies_in_the_range_of_tower);
    void attack_with_glue_on_the_runner(int current_glue);
    void attack_with_glue_on_stubborn_runners(int current_glue);
    void attack_with_glue_on_super_trooper(int current_glue);
    void attack_with_glue_on_scrambler(int current_glue);
    void check_for_atteck_with_glue_on_another_enemies(int current_missile, float current_the_enemy_position[2]);
    void check_the_runner_killed(int current_the_runner);
    void check_super_trooper_killed(int current_super_trooper);
    void check_stubborn_runners_killed(int current_stubborn_runners);
    void check_scrambler_killed(int current_scrambler);
    void check_enemies_reach_the_end_of_the_path();
    void check_not_killed_enemies();
    void update_enemeis(Window* window);
    void check_for_play_music(Window *window);
    void draw(Window* window);
    void draw_route(Window* window);
    void draw_the_route_of_non_adjacent_houses(Window* window, int current_x, int current_y);
    void draw_rectangle_in_x (Window* window, int first_x, int y, int last_x);
    void draw_rectangle_in_y (Window* window, int first_y, int x, int last_y);
    void draw_mouse_position(Window* window);
    void draw_start_end_flag(Window* window);
    void show_player_information(Window* window);
    std::string convert_number_to_string(int number);
    void show_enemies_details(Window* window);
    void show_runner_details(Window* window);
    void show_stubborn_runner_details(Window* window);
    void show_super_trooper_details(Window* window);
    void show_scrambler_details(Window* window);
    void show_tower_details(Window* window);
    void show_gattling_details(Window* window);
    void show_tesla_details(Window* window);
    void show_missile_trooper_details(Window* window);
    void show_glue_details(Window* window);
    void draw_towers(Window* window);
    void draw_enemies(Window* window);
    void show_final_result(Window* window);
    int get_game_status();
    void upgrade_time_count();
    void check_end_game();
    int calculate_number_of_enemies_in_current_wave();

private:
    Enemies enemies;
    Towers towers;
    std::vector<int> enemies_path;
    std::vector<std::vector<int> > waves;
    int time_count; 
    Point mouse_position;
    Player player;
    int wave;
    int number_of_enemy_in_current_wave;
    int enemies_killed;
    int game_status;
    int play_music;

};

#endif