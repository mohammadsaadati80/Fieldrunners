#include "Fieldrunners.hpp"
using namespace std;

void Fieldrunners::get_input()
{
    vector<string> input_waves_file_lines = read_input_waves_lines();
    enemies_path = separate_the_number_in_string_line(input_waves_file_lines[PATH_OF_THE_ENEMIES]);
    waves = calculate_input_waves(input_waves_file_lines);
    time_count = 0;
    player.gold = PLAYER_INITIAL_GOLD;
    player.hearts = PLAYER_INITIAL_HEARTS;
    wave = 0;
    enemies_killed = 0;
    number_of_enemy_in_current_wave = calculate_number_of_enemies_in_current_wave();
    game_status = PLAYING_GAME;
    play_music = NOT_PLAY_MUSIC;
}

vector<string> Fieldrunners::read_input_waves_lines()
{
    vector<string> input_file_lines;
    string line;
    while(getline(cin, line))
        input_file_lines.push_back(line);
    return input_file_lines;
}

vector<int> Fieldrunners::separate_the_number_in_string_line(string path_of_the_enemies)
{
    vector<int> numbers_in_line;
    stringstream string_stream(path_of_the_enemies);
    string string_number;
    while(getline(string_stream,string_number, SEPARATOR))
        numbers_in_line.push_back(convert_number_string_to_int(string_number));
    return numbers_in_line;
}

int Fieldrunners::convert_number_string_to_int(string line_element)
{
	int number = 0;
	for (int current = 0; current < line_element.size(); current++)
	{
		if (current > 0)
			number *= 10;
		number += (int(line_element[current]) - 48);
	}
	return number;
}

vector<vector<int> > Fieldrunners::calculate_input_waves(vector<string> input_waves_file_lines)
{
    vector<vector<int> > waves;
    for(int current_line = FIRST_VALID_WAVE_LINE; current_line < input_waves_file_lines.size(); current_line++)
        waves.push_back(separate_the_number_in_string_line(input_waves_file_lines[current_line]));
    return waves;
}

void Fieldrunners::update(Window* window)
{
    if(window->has_pending_event()) 
    {
		Event event = window->poll_for_event();
		switch(event.get_type()) {
			case Event::EventType::QUIT:
				exit(0);
				break;
            case Event::EventType::LCLICK:
				mouse_position = event.get_mouse_position();
                break;
            case Event::EventType::KEY_PRESS:
                char pressed_key;    
                pressed_key = event.get_pressed_key();
                check_pressed_key(pressed_key);
                break;
		}
	}
    if(game_status == PLAYING_GAME)
    {
        check_can_insert_new_enemeis(); 
        check_for_attack();
        check_enemies_reach_the_end_of_the_path();
        check_not_killed_enemies();
        update_enemeis(window);
    }
    check_for_play_music(window);
}

void Fieldrunners::check_pressed_key(char &pressed_key)
{
    if (pressed_key == GATLING_INSERT_KEY)
        create_new_gatling_tower();
    if (pressed_key == UPDATE_TOWER_INSERT_KEY)
         update_tower();
    if (pressed_key == TESLA_INSERT_KEY)
        create_new_tesla_tower();
    if (pressed_key == MISSILE_INSERT_KEY)
        create_new_missile_tower();
    if (pressed_key == GLUE_INSERT_KEY)
        create_new_glue_tower();
}

void Fieldrunners::create_new_gatling_tower()
{
    Gatling new_gatling;
    new_gatling.initialization(mouse_position);
    towers.gatling_info.push_back(new_gatling);
    player.gold -= GATLING_BUILDING_COST;
}

void Fieldrunners::create_new_glue_tower()
{
    Glue new_glue;
    new_glue.initialization(mouse_position);
    towers.glue_info.push_back(new_glue);
    player.gold -= GLUE_BUILDING_COST;
}

void Fieldrunners::create_new_missile_tower()
{
    Missile new_missile;
    new_missile.initialization(mouse_position);
    towers.missile_info.push_back(new_missile);
    player.gold -= MISSILE_BUILDING_COST;
}

void Fieldrunners::create_new_tesla_tower()
{
    Tesla new_tesla;
    new_tesla.initialization(mouse_position);
    towers.tesla_info.push_back(new_tesla);
    player.gold -= TESLA_BUILDING_COST;
}

void Fieldrunners::update_tower()
{
    float house_position[2];
    house_position[X] = (mouse_position.x - FIRST_HOUSE_TABLE_X)/BACKGROUND_SQUARE_LENGHT;
    house_position[Y]= (mouse_position.y - FIRST_HOUSE_TABLE_Y)/BACKGROUND_SQUARE_LENGHT;
    check_for_update_gatling(house_position);
    check_for_update_tesla(house_position);
    check_for_update_missile(house_position);
    check_for_update_glue(house_position);
}

void Fieldrunners::check_for_update_glue(float house_position[2])
{
    for(int current_glue = 0; current_glue < towers.glue_info.size(); current_glue++)
        if (towers.glue_info[current_glue].get_house_position_x() == house_position[X] && towers.glue_info[current_glue].get_house_position_y() == house_position[Y])
        {
            towers.glue_info[current_glue].upgrade();
            player.gold -= GLUE_UPGRADE_COST;
        }
}

void Fieldrunners::check_for_update_missile(float house_position[2])
{
    for(int current_missile = 0; current_missile < towers.missile_info.size(); current_missile++)
        if (towers.missile_info[current_missile].get_house_position_x() == house_position[X] && towers.missile_info[current_missile].get_house_position_y() == house_position[Y])
        {
            towers.missile_info[current_missile].upgrade();
            player.gold -= MISSILE_UPGRADE_COST;
        }
}

void Fieldrunners::check_for_update_tesla(float house_position[2])
{
    for(int current_tesla = 0; current_tesla < towers.tesla_info.size(); current_tesla++)
        if (towers.tesla_info[current_tesla].get_house_position_x() == house_position[X] && towers.tesla_info[current_tesla].get_house_position_y() == house_position[Y])
        {
            towers.tesla_info[current_tesla].upgrade();
            player.gold -= TESLA_UPGRADE_COST;
        }
}

void Fieldrunners::check_for_update_gatling(float house_position[2])
{
    for(int current_gatling = 0; current_gatling < towers.gatling_info.size(); current_gatling++)
        if (towers.gatling_info[current_gatling].get_house_position_x() == house_position[X] && towers.gatling_info[current_gatling].get_house_position_y() == house_position[Y])
        {
            towers.gatling_info[current_gatling].upgrade();
            player.gold -= GATLING_UPGRADE_COST;
        }
}

void Fieldrunners::check_can_insert_new_enemeis()
{
    if ((time_count % TIME_BETWEEN_INSERT_ENEMIES == 0) && ((enemies.the_runners_info.size()+enemies.stubborn_runners_info.size()+enemies.super_troopers_info.size()+enemies.scramblers_info.size()) < number_of_enemy_in_current_wave))
    {
        bool result = true;
        while(result)
        {
            int random = rand() % 4;
            if (random == 0)
                result = check_can_insert_new_the_runner();
            if (random == 1) 
                result = check_can_insert_new_stubborn_runners();
            if (random == 2)
                result = check_can_insert_new_super_trooper();
            if (random == 3)
                result = check_can_insert_new_scrambler();
        }
        if (time_count == 9000)
            time_count = 0;
    }
}

bool Fieldrunners::check_can_insert_new_the_runner()
{
    if (enemies.the_runners_info.size() < waves[wave][THE_RUNNER - 1])
    {
        The_Runners new_the_runner;
        new_the_runner.first_pos(enemies_path, wave);
        enemies.the_runners_info.push_back(new_the_runner);
        return false;
    }
    return true;
}

bool Fieldrunners::check_can_insert_new_stubborn_runners()
{
    if (enemies.stubborn_runners_info.size() < waves[wave][STUBBORN_RUNNER - 1])
    {
        Stubborn_Runner new_stubborn_runner;
         new_stubborn_runner.first_pos(enemies_path, wave);
        enemies.stubborn_runners_info.push_back(new_stubborn_runner);
        return false;
    }
    return true;
}

bool Fieldrunners::check_can_insert_new_super_trooper()
{
    if (enemies.super_troopers_info.size() < waves[wave][SUPER_TROOPER - 1])
    {
        Super_Trooper new_super_trooper;
        new_super_trooper.first_pos(enemies_path, wave);
        enemies.super_troopers_info.push_back(new_super_trooper);
        return false;
    }
    return true;
}

bool Fieldrunners::check_can_insert_new_scrambler( )
{
    if (enemies.scramblers_info.size() < waves[wave][SCRAMBLER - 1])
    {
        Scrambler new_scrambler;
        new_scrambler.first_pos(enemies_path, wave);
        enemies.scramblers_info.push_back(new_scrambler);
        return false;
    }
    return true;
}

void Fieldrunners::check_for_attack()
{
    check_for_attack_with_gatling();
    check_for_attack_with_tesla();
    check_for_attack_with_missile();
    check_for_attack_with_glue();
}

void Fieldrunners::check_for_attack_with_gatling()
{
    for(int current_gatling = 0 ;current_gatling < towers.gatling_info.size(); current_gatling++ )
    {
        if (towers.gatling_info[current_gatling].get_status() == NOT_ATTACKING)
        {
            vector<float> closest_enemies_in_the_range_of_tower = find_enemies_in_the_range_of_gatling(current_gatling);
            if (closest_enemies_in_the_range_of_tower[ENEMY_TYPE] < 5)   
                towers.gatling_info[current_gatling].fill_enemie_details(closest_enemies_in_the_range_of_tower[ENEMY_TYPE], closest_enemies_in_the_range_of_tower[ENEMY_NUMBER]);
        }
        if (towers.gatling_info[current_gatling].get_status() == ATTACKING)
        {
            if (towers.gatling_info[current_gatling].get_enemy_type() == THE_RUNNER)
                attack_with_gatling_on_the_runner(current_gatling);
            if (towers.gatling_info[current_gatling].get_enemy_type() == STUBBORN_RUNNER)
                attack_with_gatling_on_stubborn_runners(current_gatling);
            if (towers.gatling_info[current_gatling].get_enemy_type() == SUPER_TROOPER)
                attack_with_gatling_on_super_trooper(current_gatling);
            if (towers.gatling_info[current_gatling].get_enemy_type() == SCRAMBLER)
                attack_with_gatling_on_scrambler(current_gatling);
        }
    }
}

vector<float> Fieldrunners::find_enemies_in_the_range_of_gatling(int current_tower)
{

    vector<float> closest_enemies_in_the_range_of_tower = create_vector();
    find_the_runners_in_the_range_of_gatling(current_tower, closest_enemies_in_the_range_of_tower);
    find_stubborn_runners_in_the_range_of_gatling(current_tower, closest_enemies_in_the_range_of_tower);
    find_super_trooper_in_the_range_of_gatling(current_tower, closest_enemies_in_the_range_of_tower);
    find_scrambler_in_the_range_of_gatling(current_tower, closest_enemies_in_the_range_of_tower);
    return closest_enemies_in_the_range_of_tower;
}

vector<float> Fieldrunners::create_vector()
{
    vector<float> new_vector;
    while(new_vector.size() < 3)
        new_vector.push_back(23000);
    return new_vector;
}

void Fieldrunners::find_the_runners_in_the_range_of_gatling(int current_tower, vector<float> &closest_enemies_in_the_range_of_tower)
{
    for(int current_the_runners = 0; current_the_runners < enemies.the_runners_info.size(); current_the_runners++)
    {
        float current_the_runners_position[2];
        current_the_runners_position[X] = enemies.the_runners_info[current_the_runners].get_position_x();
        current_the_runners_position[Y] = enemies.the_runners_info[current_the_runners].get_position_y();
        if(towers.gatling_info[current_tower].check_enemies_distance(current_the_runners_position) && (enemies.the_runners_info[current_the_runners].get_status() == ALIVE))
           if (towers.gatling_info[current_tower].distance_size(current_the_runners_position) < closest_enemies_in_the_range_of_tower[ENEMY_DISTANCE])
            {
                closest_enemies_in_the_range_of_tower[ENEMY_TYPE] = THE_RUNNER;
                closest_enemies_in_the_range_of_tower[ENEMY_NUMBER] = current_the_runners;
            }
    }
}

void Fieldrunners::find_stubborn_runners_in_the_range_of_gatling(int current_tower, vector<float> &closest_enemies_in_the_range_of_tower)
{
    for(int current_stubborn_runners = 0; current_stubborn_runners < enemies.stubborn_runners_info.size(); current_stubborn_runners++)
    {
        float current_stubborn_runners_position[2];
        current_stubborn_runners_position[X] = enemies.stubborn_runners_info[current_stubborn_runners].get_position_x();
        current_stubborn_runners_position[Y] = enemies.stubborn_runners_info[current_stubborn_runners].get_position_y();
        if(towers.gatling_info[current_tower].check_enemies_distance(current_stubborn_runners_position) && (enemies.stubborn_runners_info[current_stubborn_runners].get_status() == ALIVE))
        {
            if (towers.gatling_info[current_tower].distance_size(current_stubborn_runners_position) < closest_enemies_in_the_range_of_tower[ENEMY_DISTANCE])
            {
                closest_enemies_in_the_range_of_tower[ENEMY_TYPE] = STUBBORN_RUNNER;
                closest_enemies_in_the_range_of_tower[ENEMY_NUMBER] = current_stubborn_runners;
            }
        }
    }
}

void Fieldrunners::find_super_trooper_in_the_range_of_gatling(int current_tower, vector<float> &closest_enemies_in_the_range_of_tower)
{
    for(int current_super_troopers = 0; current_super_troopers < enemies.super_troopers_info.size(); current_super_troopers++)
    {
        float current_super_troopers_position[2];
        current_super_troopers_position[X] = enemies.super_troopers_info[current_super_troopers].get_position_x();
        current_super_troopers_position[Y] = enemies.super_troopers_info[current_super_troopers].get_position_y();
        if(towers.gatling_info[current_tower].check_enemies_distance(current_super_troopers_position) && (enemies.super_troopers_info[current_super_troopers].get_status() == ALIVE))
        {
            if (towers.gatling_info[current_tower].distance_size(current_super_troopers_position) < closest_enemies_in_the_range_of_tower[ENEMY_DISTANCE])
            {
                closest_enemies_in_the_range_of_tower[ENEMY_TYPE] = SUPER_TROOPER;
                closest_enemies_in_the_range_of_tower[ENEMY_NUMBER] = current_super_troopers;
            }
        }
    }
}

void Fieldrunners::find_scrambler_in_the_range_of_gatling(int current_tower, vector<float> &closest_enemies_in_the_range_of_tower)
{
    for(int current_scramber = 0; current_scramber < enemies.scramblers_info.size(); current_scramber++)
    {
        float current_scramber_position[2];
        current_scramber_position[X] = enemies.scramblers_info[current_scramber].get_position_x();
        current_scramber_position[Y] = enemies.scramblers_info[current_scramber].get_position_y();
        if(towers.gatling_info[current_tower].check_enemies_distance(current_scramber_position)&& (enemies.scramblers_info[current_scramber].get_status() == ALIVE))
        {
            if (towers.gatling_info[current_tower].distance_size(current_scramber_position) < closest_enemies_in_the_range_of_tower[ENEMY_DISTANCE])
            {
                closest_enemies_in_the_range_of_tower[ENEMY_TYPE] = SCRAMBLER;
                closest_enemies_in_the_range_of_tower[ENEMY_NUMBER] = current_scramber;
            }
        }
    }
}

void Fieldrunners::attack_with_gatling_on_the_runner(int current_gatling)
{
    float current_the_runner_position[2];
    current_the_runner_position[X] = enemies.the_runners_info[towers.gatling_info[current_gatling].get_enemy_number()].get_position_x();
    current_the_runner_position[Y] = enemies.the_runners_info[towers.gatling_info[current_gatling].get_enemy_number()].get_position_y();
    if (towers.gatling_info[current_gatling].check_enemies_distance(current_the_runner_position) && (enemies.the_runners_info[towers.gatling_info[current_gatling].get_enemy_number()].get_status() == ALIVE) && (enemies.the_runners_info[towers.gatling_info[current_gatling].get_enemy_number()].get_moving_status() == MOVING))
    {
        if (towers.gatling_info[current_gatling].get_attack_time() % GATLING_ATTACK_SPEED == ATTACK_TIME)
        {
            enemies.the_runners_info[towers.gatling_info[current_gatling].get_enemy_number()].reduce_health(towers.gatling_info[current_gatling].get_damage());
            check_the_runner_killed(towers.gatling_info[current_gatling].get_enemy_number());
        }
        else
            towers.gatling_info[current_gatling].fill_current_enemy_position(current_the_runner_position);
    }
    else
        towers.gatling_info[current_gatling].change_attack_status();
}

void Fieldrunners::attack_with_gatling_on_stubborn_runners(int current_gatling)
{
    float current_stubborn_runners_position[2];
    current_stubborn_runners_position[X] = enemies.stubborn_runners_info[towers.gatling_info[current_gatling].get_enemy_number()].get_position_x();
    current_stubborn_runners_position[Y] = enemies.stubborn_runners_info[towers.gatling_info[current_gatling].get_enemy_number()].get_position_y();
    if (towers.gatling_info[current_gatling].check_enemies_distance(current_stubborn_runners_position) && (enemies.stubborn_runners_info[towers.gatling_info[current_gatling].get_enemy_number()].get_status() == ALIVE) && (enemies.stubborn_runners_info[towers.gatling_info[current_gatling].get_enemy_number()].get_moving_status() == MOVING))
    {
        if (towers.gatling_info[current_gatling].get_attack_time() % GATLING_ATTACK_SPEED == ATTACK_TIME)
            check_stubborn_runners_killed(towers.gatling_info[current_gatling].get_enemy_number());
        else
            towers.gatling_info[current_gatling].fill_current_enemy_position(current_stubborn_runners_position);
    }
    else
        towers.gatling_info[current_gatling].change_attack_status();
}

void Fieldrunners::attack_with_gatling_on_super_trooper(int current_gatling)
{
    float current_super_troopers_position[2];
    current_super_troopers_position[X] = enemies.super_troopers_info[towers.gatling_info[current_gatling].get_enemy_number()].get_position_x();
    current_super_troopers_position[Y] = enemies.super_troopers_info[towers.gatling_info[current_gatling].get_enemy_number()].get_position_y();
    if (towers.gatling_info[current_gatling].check_enemies_distance(current_super_troopers_position) && (enemies.super_troopers_info[towers.gatling_info[current_gatling].get_enemy_number()].get_status() == ALIVE )&& (enemies.super_troopers_info[towers.gatling_info[current_gatling].get_enemy_number()].get_moving_status() == MOVING))
    {
        if (towers.gatling_info[current_gatling].get_attack_time() % GATLING_ATTACK_SPEED == ATTACK_TIME)
        {    
            enemies.super_troopers_info[towers.gatling_info[current_gatling].get_enemy_number()].reduce_health(towers.gatling_info[current_gatling].get_damage());
            check_super_trooper_killed(towers.gatling_info[current_gatling].get_enemy_number());
        }
        else
            towers.gatling_info[current_gatling].fill_current_enemy_position(current_super_troopers_position);
    }
    else
        towers.gatling_info[current_gatling].change_attack_status();
}

void Fieldrunners::attack_with_gatling_on_scrambler(int current_gatling)
{
    float current_scrambler_position[2];
    current_scrambler_position[X] = enemies.scramblers_info[towers.gatling_info[current_gatling].get_enemy_number()].get_position_x();
    current_scrambler_position[Y] = enemies.scramblers_info[towers.gatling_info[current_gatling].get_enemy_number()].get_position_y();
    if (towers.gatling_info[current_gatling].check_enemies_distance(current_scrambler_position) && (enemies.scramblers_info[towers.gatling_info[current_gatling].get_enemy_number()].get_status() == ALIVE)  && (enemies.scramblers_info[towers.gatling_info[current_gatling].get_enemy_number()].get_moving_status() == MOVING))
    {
        if (towers.gatling_info[current_gatling].get_attack_time() % GATLING_ATTACK_SPEED == ATTACK_TIME)
        {    
            enemies.scramblers_info[towers.gatling_info[current_gatling].get_enemy_number()].reduce_health(towers.gatling_info[current_gatling].get_damage());
            check_scrambler_killed(towers.gatling_info[current_gatling].get_enemy_number());
        }
        else
            towers.gatling_info[current_gatling].fill_current_enemy_position(current_scrambler_position);
    }
    else
        towers.gatling_info[current_gatling].change_attack_status();
}

void Fieldrunners::check_for_attack_with_tesla()
{
    for(int current_tesla = 0 ;current_tesla < towers.tesla_info.size(); current_tesla++ )
    {
        if (towers.tesla_info[current_tesla].get_status() == NOT_ATTACKING)
        {
            vector<float> closest_enemies_in_the_range_of_tower = find_enemies_in_the_range_of_tesla(current_tesla);
            if (closest_enemies_in_the_range_of_tower[ENEMY_TYPE] < 5)   
                towers.tesla_info[current_tesla].fill_enemie_details(closest_enemies_in_the_range_of_tower[ENEMY_TYPE], closest_enemies_in_the_range_of_tower[ENEMY_NUMBER]);
        }
        if (towers.tesla_info[current_tesla].get_status() == ATTACKING)
        {
            if (towers.tesla_info[current_tesla].get_enemy_type() == THE_RUNNER)
                attack_with_tesla_on_the_runner(current_tesla);
            if (towers.tesla_info[current_tesla].get_enemy_type() == STUBBORN_RUNNER)
                attack_with_tesla_on_stubborn_runners(current_tesla);
            if (towers.tesla_info[current_tesla].get_enemy_type() == SUPER_TROOPER)
                attack_with_tesla_on_super_trooper(current_tesla);
            if (towers.tesla_info[current_tesla].get_enemy_type() == SCRAMBLER)
                attack_with_tesla_on_scrambler(current_tesla);
        }
    }
}

vector<float> Fieldrunners::find_enemies_in_the_range_of_tesla(int current_tower)
{
    vector<float> closest_enemies_in_the_range_of_tower = create_vector();
    find_the_runners_in_the_range_of_tesla(current_tower, closest_enemies_in_the_range_of_tower);
    find_stubborn_runners_in_the_range_of_tesla(current_tower, closest_enemies_in_the_range_of_tower);
    find_super_trooper_in_the_range_of_tesla(current_tower, closest_enemies_in_the_range_of_tower);
    find_scrambler_in_the_range_of_tesla(current_tower, closest_enemies_in_the_range_of_tower);
    return closest_enemies_in_the_range_of_tower;   
}

void Fieldrunners::find_the_runners_in_the_range_of_tesla(int current_tower, vector<float> &closest_enemies_in_the_range_of_tower)
{
    for(int current_the_runners = 0; current_the_runners < enemies.the_runners_info.size(); current_the_runners++)
    {
        float current_the_runners_position[2];
        current_the_runners_position[X] = enemies.the_runners_info[current_the_runners].get_position_x();
        current_the_runners_position[Y] = enemies.the_runners_info[current_the_runners].get_position_y();
        if(towers.tesla_info[current_tower].check_enemies_distance(current_the_runners_position) && (enemies.the_runners_info[current_the_runners].get_status() == ALIVE))
            if (towers.tesla_info[current_tower].distance_size(current_the_runners_position) < closest_enemies_in_the_range_of_tower[ENEMY_DISTANCE])
            {
                closest_enemies_in_the_range_of_tower[ENEMY_TYPE] = THE_RUNNER;
                closest_enemies_in_the_range_of_tower[ENEMY_NUMBER] = current_the_runners;
            }
    }
}

void Fieldrunners::find_stubborn_runners_in_the_range_of_tesla(int current_tower, vector<float> &closest_enemies_in_the_range_of_tower)
{
    for(int current_stubborn_runners = 0; current_stubborn_runners < enemies.stubborn_runners_info.size(); current_stubborn_runners++)
    {
        float current_stubborn_runners_position[2];
        current_stubborn_runners_position[X] = enemies.stubborn_runners_info[current_stubborn_runners].get_position_x();
        current_stubborn_runners_position[Y] = enemies.stubborn_runners_info[current_stubborn_runners].get_position_y();
        if(towers.tesla_info[current_tower].check_enemies_distance(current_stubborn_runners_position) && (enemies.stubborn_runners_info[current_stubborn_runners].get_status() == ALIVE))
            if (towers.tesla_info[current_tower].distance_size(current_stubborn_runners_position) < closest_enemies_in_the_range_of_tower[ENEMY_DISTANCE])
            {
                closest_enemies_in_the_range_of_tower[ENEMY_TYPE] = STUBBORN_RUNNER;
                closest_enemies_in_the_range_of_tower[ENEMY_NUMBER] = current_stubborn_runners;
            }
    }
}

void Fieldrunners::find_super_trooper_in_the_range_of_tesla(int current_tower, vector<float> &closest_enemies_in_the_range_of_tower)
{
    for(int current_super_troopers = 0; current_super_troopers < enemies.super_troopers_info.size(); current_super_troopers++)
    {
        float current_super_troopers_position[2];
        current_super_troopers_position[X] = enemies.super_troopers_info[current_super_troopers].get_position_x();
        current_super_troopers_position[Y] = enemies.super_troopers_info[current_super_troopers].get_position_y();
        if(towers.tesla_info[current_tower].check_enemies_distance(current_super_troopers_position) && (enemies.super_troopers_info[current_super_troopers].get_status() == ALIVE))
            if (towers.tesla_info[current_tower].distance_size(current_super_troopers_position) < closest_enemies_in_the_range_of_tower[ENEMY_DISTANCE])
            {
                closest_enemies_in_the_range_of_tower[ENEMY_TYPE] = SUPER_TROOPER;
                closest_enemies_in_the_range_of_tower[ENEMY_NUMBER] = current_super_troopers;
            }
    }
}

void Fieldrunners::find_scrambler_in_the_range_of_tesla(int current_tower, vector<float> &closest_enemies_in_the_range_of_tower)
{
    for(int current_scramber = 0; current_scramber < enemies.scramblers_info.size(); current_scramber++)
    {
        float current_scramber_position[2];
        current_scramber_position[X] = enemies.scramblers_info[current_scramber].get_position_x();
        current_scramber_position[Y] = enemies.scramblers_info[current_scramber].get_position_y();
        if(towers.tesla_info[current_tower].check_enemies_distance(current_scramber_position)&& (enemies.scramblers_info[current_scramber].get_status() == ALIVE))
            if (towers.tesla_info[current_tower].distance_size(current_scramber_position) < closest_enemies_in_the_range_of_tower[ENEMY_DISTANCE])
            {
                closest_enemies_in_the_range_of_tower[ENEMY_TYPE] = SCRAMBLER;
                closest_enemies_in_the_range_of_tower[ENEMY_NUMBER] = current_scramber;
            }
    }
}

void Fieldrunners::attack_with_tesla_on_the_runner(int current_tesla)
{
    float current_the_runner_position[2];
    current_the_runner_position[X] = enemies.the_runners_info[towers.tesla_info[current_tesla].get_enemy_number()].get_position_x();
    current_the_runner_position[Y] = enemies.the_runners_info[towers.tesla_info[current_tesla].get_enemy_number()].get_position_y();
    if (towers.tesla_info[current_tesla].check_enemies_distance(current_the_runner_position) && (enemies.the_runners_info[towers.tesla_info[current_tesla].get_enemy_number()].get_status() == ALIVE))
    {
        if (towers.tesla_info[current_tesla].get_attack_time() % TESLA_ATTACK_SPEED == ATTACK_TIME)
        {
            enemies.the_runners_info[towers.tesla_info[current_tesla].get_enemy_number()].reduce_health(towers.tesla_info[current_tesla].get_damage());
            check_the_runner_killed(towers.tesla_info[current_tesla].get_enemy_number());
        }
        else
            towers.tesla_info[current_tesla].fill_current_enemy_position(current_the_runner_position);
    }
    else
        towers.tesla_info[current_tesla].change_attack_status();
}

void Fieldrunners::attack_with_tesla_on_stubborn_runners(int current_tesla)
{
    float current_stubborn_runners_position[2];
    current_stubborn_runners_position[X] = enemies.stubborn_runners_info[towers.tesla_info[current_tesla].get_enemy_number()].get_position_x();
    current_stubborn_runners_position[Y] = enemies.stubborn_runners_info[towers.tesla_info[current_tesla].get_enemy_number()].get_position_y();
    if (towers.tesla_info[current_tesla].check_enemies_distance(current_stubborn_runners_position) && (enemies.stubborn_runners_info[towers.tesla_info[current_tesla].get_enemy_number()].get_status() == ALIVE))
    {
        if (towers.tesla_info[current_tesla].get_attack_time() % TESLA_ATTACK_SPEED == ATTACK_TIME)
        {    
            enemies.stubborn_runners_info[towers.tesla_info[current_tesla].get_enemy_number()].reduce_health(towers.tesla_info[current_tesla].get_damage());
            check_stubborn_runners_killed(towers.tesla_info[current_tesla].get_enemy_number());
        }
        else
            towers.tesla_info[current_tesla].fill_current_enemy_position(current_stubborn_runners_position);
    }
    else
        towers.tesla_info[current_tesla].change_attack_status();
}

void Fieldrunners::attack_with_tesla_on_super_trooper(int current_tesla)
{
    float current_super_troopers_position[2];
    current_super_troopers_position[X] = enemies.super_troopers_info[towers.tesla_info[current_tesla].get_enemy_number()].get_position_x();
    current_super_troopers_position[Y] = enemies.super_troopers_info[towers.tesla_info[current_tesla].get_enemy_number()].get_position_y();
    if (towers.tesla_info[current_tesla].check_enemies_distance(current_super_troopers_position) && (enemies.super_troopers_info[towers.tesla_info[current_tesla].get_enemy_number()].get_status() == ALIVE ))
    {
        if (towers.tesla_info[current_tesla].get_attack_time() % TESLA_ATTACK_SPEED == ATTACK_TIME)
        {    
            enemies.super_troopers_info[towers.tesla_info[current_tesla].get_enemy_number()].reduce_health(towers.tesla_info[current_tesla].get_damage());
            check_super_trooper_killed(towers.tesla_info[current_tesla].get_enemy_number());
        }
        else
            towers.tesla_info[current_tesla].fill_current_enemy_position(current_super_troopers_position);
    }
    else
        towers.tesla_info[current_tesla].change_attack_status();
}

void Fieldrunners::attack_with_tesla_on_scrambler(int current_tesla)
{
    float current_scrambler_position[2];
    current_scrambler_position[X] = enemies.scramblers_info[towers.tesla_info[current_tesla].get_enemy_number()].get_position_x();
    current_scrambler_position[Y] = enemies.scramblers_info[towers.tesla_info[current_tesla].get_enemy_number()].get_position_y();
    if (towers.tesla_info[current_tesla].check_enemies_distance(current_scrambler_position) && (enemies.scramblers_info[towers.tesla_info[current_tesla].get_enemy_number()].get_status() == ALIVE))
    {
        if (towers.tesla_info[current_tesla].get_attack_time() % TESLA_ATTACK_SPEED == ATTACK_TIME)
        {    
            enemies.scramblers_info[towers.tesla_info[current_tesla].get_enemy_number()].reduce_health(towers.tesla_info[current_tesla].get_damage());
            check_scrambler_killed(towers.tesla_info[current_tesla].get_enemy_number());
        }
        else
            towers.tesla_info[current_tesla].fill_current_enemy_position(current_scrambler_position);
    }
    else
        towers.tesla_info[current_tesla].change_attack_status();
}

void Fieldrunners::check_for_attack_with_missile()
{
    for(int current_missile = 0 ;current_missile < towers.missile_info.size(); current_missile++ )
    {
        if (towers.missile_info[current_missile].get_status() == NOT_ATTACKING)
        {
            vector<float> closest_enemies_in_the_range_of_tower = find_enemies_in_the_range_of_missile(current_missile);
            if (closest_enemies_in_the_range_of_tower[ENEMY_TYPE] < 5)   
                towers.missile_info[current_missile].fill_enemie_details(closest_enemies_in_the_range_of_tower[ENEMY_TYPE], closest_enemies_in_the_range_of_tower[ENEMY_NUMBER]);
        }
        if (towers.missile_info[current_missile].get_status() == ATTACKING)
        {
            if (towers.missile_info[current_missile].get_enemy_type() == THE_RUNNER)
                attack_with_missile_on_the_runner(current_missile);
            if (towers.missile_info[current_missile].get_enemy_type() == STUBBORN_RUNNER)
                attack_with_missile_on_stubborn_runners(current_missile);
            if (towers.missile_info[current_missile].get_enemy_type() == SUPER_TROOPER)
                attack_with_missile_on_super_trooper(current_missile);
            if (towers.missile_info[current_missile].get_enemy_type() == SCRAMBLER)
                attack_with_missile_on_scrambler(current_missile);
        }
    }
}

vector<float> Fieldrunners::find_enemies_in_the_range_of_missile(int current_tower)
{
    vector<float> closest_enemies_in_the_range_of_tower = create_vector();
    find_the_runners_in_the_range_of_missile(current_tower, closest_enemies_in_the_range_of_tower);
    find_stubborn_runners_in_the_range_of_missile(current_tower, closest_enemies_in_the_range_of_tower);
    find_super_trooper_in_the_range_of_missile(current_tower, closest_enemies_in_the_range_of_tower);
    find_scrambler_in_the_range_of_missile(current_tower, closest_enemies_in_the_range_of_tower);
    return closest_enemies_in_the_range_of_tower;
}

void Fieldrunners::find_the_runners_in_the_range_of_missile(int current_tower, vector<float> &closest_enemies_in_the_range_of_tower)
{
    for(int current_the_runners = 0; current_the_runners < enemies.the_runners_info.size(); current_the_runners++)
    {
        float current_the_runners_position[2];
        current_the_runners_position[X] = enemies.the_runners_info[current_the_runners].get_position_x();
        current_the_runners_position[Y] = enemies.the_runners_info[current_the_runners].get_position_y();
        if(towers.missile_info[current_tower].check_enemies_distance(current_the_runners_position) && (enemies.the_runners_info[current_the_runners].get_status() == ALIVE))
           if (towers.missile_info[current_tower].distance_size(current_the_runners_position) < closest_enemies_in_the_range_of_tower[ENEMY_DISTANCE])
            {
                closest_enemies_in_the_range_of_tower[ENEMY_TYPE] = THE_RUNNER;
                closest_enemies_in_the_range_of_tower[ENEMY_NUMBER] = current_the_runners;
            }
    }
}

void Fieldrunners::find_stubborn_runners_in_the_range_of_missile(int current_tower, vector<float> &closest_enemies_in_the_range_of_tower)
{
    for(int current_stubborn_runners = 0; current_stubborn_runners < enemies.stubborn_runners_info.size(); current_stubborn_runners++)
    {
        float current_stubborn_runners_position[2];
        current_stubborn_runners_position[X] = enemies.stubborn_runners_info[current_stubborn_runners].get_position_x();
        current_stubborn_runners_position[Y] = enemies.stubborn_runners_info[current_stubborn_runners].get_position_y();
        if(towers.missile_info[current_tower].check_enemies_distance(current_stubborn_runners_position) && (enemies.stubborn_runners_info[current_stubborn_runners].get_status() == ALIVE))
            if (towers.missile_info[current_tower].distance_size(current_stubborn_runners_position) < closest_enemies_in_the_range_of_tower[ENEMY_DISTANCE])
            {
                closest_enemies_in_the_range_of_tower[ENEMY_TYPE] = STUBBORN_RUNNER;
                closest_enemies_in_the_range_of_tower[ENEMY_NUMBER] = current_stubborn_runners;
            }
    }
}

void Fieldrunners::find_super_trooper_in_the_range_of_missile(int current_tower, vector<float> &closest_enemies_in_the_range_of_tower)
{
    for(int current_super_troopers = 0; current_super_troopers < enemies.super_troopers_info.size(); current_super_troopers++)
    {
        float current_super_troopers_position[2];
        current_super_troopers_position[X] = enemies.super_troopers_info[current_super_troopers].get_position_x();
        current_super_troopers_position[Y] = enemies.super_troopers_info[current_super_troopers].get_position_y();
        if(towers.missile_info[current_tower].check_enemies_distance(current_super_troopers_position) && (enemies.super_troopers_info[current_super_troopers].get_status() == ALIVE))
            if (towers.missile_info[current_tower].distance_size(current_super_troopers_position) < closest_enemies_in_the_range_of_tower[ENEMY_DISTANCE])
            {
                closest_enemies_in_the_range_of_tower[ENEMY_TYPE] = SUPER_TROOPER;
                closest_enemies_in_the_range_of_tower[ENEMY_NUMBER] = current_super_troopers;
            }
    }
}

void Fieldrunners::find_scrambler_in_the_range_of_missile(int current_tower, vector<float> &closest_enemies_in_the_range_of_tower)
{
    for(int current_scramber = 0; current_scramber < enemies.scramblers_info.size(); current_scramber++)
    {
        float current_scramber_position[2];
        current_scramber_position[X] = enemies.scramblers_info[current_scramber].get_position_x();
        current_scramber_position[Y] = enemies.scramblers_info[current_scramber].get_position_y();
        if(towers.missile_info[current_tower].check_enemies_distance(current_scramber_position)&& (enemies.scramblers_info[current_scramber].get_status() == ALIVE))
            if (towers.missile_info[current_tower].distance_size(current_scramber_position) < closest_enemies_in_the_range_of_tower[ENEMY_DISTANCE])
            {
                closest_enemies_in_the_range_of_tower[ENEMY_TYPE] = SCRAMBLER;
                closest_enemies_in_the_range_of_tower[ENEMY_NUMBER] = current_scramber;
            }
    }
}

void Fieldrunners::attack_with_missile_on_the_runner(int current_missile)
{
    float current_the_runner_position[2];
    current_the_runner_position[X] = enemies.the_runners_info[towers.missile_info[current_missile].get_enemy_number()].get_position_x();
    current_the_runner_position[Y] = enemies.the_runners_info[towers.missile_info[current_missile].get_enemy_number()].get_position_y();
    if (towers.missile_info[current_missile].check_enemies_distance(current_the_runner_position) && (enemies.the_runners_info[towers.missile_info[current_missile].get_enemy_number()].get_status() == ALIVE))
    {
        if (towers.missile_info[current_missile].get_attack_time() % MISSILE_ATTACK_SPEED == ATTACK_TIME)
        {
            enemies.the_runners_info[towers.missile_info[current_missile].get_enemy_number()].reduce_health(towers.missile_info[current_missile].get_damage());
            check_the_runner_killed(towers.missile_info[current_missile].get_enemy_number());
            check_for_atteck_with_missile_on_another_enemies(current_missile,current_the_runner_position);
        }
        else
            towers.missile_info[current_missile].fill_current_enemy_position(current_the_runner_position);
    }
    else
        towers.missile_info[current_missile].change_attack_status();
}

void Fieldrunners::attack_with_missile_on_stubborn_runners(int current_missile)
{
    float current_stubborn_runners_position[2];
    current_stubborn_runners_position[X] = enemies.stubborn_runners_info[towers.missile_info[current_missile].get_enemy_number()].get_position_x();
    current_stubborn_runners_position[Y] = enemies.stubborn_runners_info[towers.missile_info[current_missile].get_enemy_number()].get_position_y();
    if (towers.missile_info[current_missile].check_enemies_distance(current_stubborn_runners_position) && (enemies.stubborn_runners_info[towers.missile_info[current_missile].get_enemy_number()].get_status() == ALIVE))
    {
        if (towers.missile_info[current_missile].get_attack_time() % MISSILE_ATTACK_SPEED == ATTACK_TIME)
        {    
            enemies.stubborn_runners_info[towers.missile_info[current_missile].get_enemy_number()].reduce_health(towers.missile_info[current_missile].get_damage());
            check_stubborn_runners_killed(towers.missile_info[current_missile].get_enemy_number());
            check_for_atteck_with_missile_on_another_enemies(current_missile,current_stubborn_runners_position);
        }
        else
            towers.missile_info[current_missile].fill_current_enemy_position(current_stubborn_runners_position);
    }
    else
        towers.missile_info[current_missile].change_attack_status();
}

void Fieldrunners::attack_with_missile_on_super_trooper(int current_missile)
{
    float current_super_troopers_position[2];
    current_super_troopers_position[X] = enemies.super_troopers_info[towers.missile_info[current_missile].get_enemy_number()].get_position_x();
    current_super_troopers_position[Y] = enemies.super_troopers_info[towers.missile_info[current_missile].get_enemy_number()].get_position_y();
    if (towers.missile_info[current_missile].check_enemies_distance(current_super_troopers_position) && (enemies.super_troopers_info[towers.missile_info[current_missile].get_enemy_number()].get_status() == ALIVE ))
    {
        if (towers.missile_info[current_missile].get_attack_time() % MISSILE_ATTACK_SPEED == ATTACK_TIME)
        {    
            enemies.super_troopers_info[towers.missile_info[current_missile].get_enemy_number()].reduce_health(towers.missile_info[current_missile].get_damage());
            check_super_trooper_killed(towers.missile_info[current_missile].get_enemy_number());
            check_for_atteck_with_missile_on_another_enemies(current_missile,current_super_troopers_position);
        }
        else
            towers.missile_info[current_missile].fill_current_enemy_position(current_super_troopers_position);
    }
    else
        towers.missile_info[current_missile].change_attack_status();
}

void Fieldrunners::attack_with_missile_on_scrambler(int current_missile)
{
    float current_scrambler_position[2];
    current_scrambler_position[X] = enemies.scramblers_info[towers.missile_info[current_missile].get_enemy_number()].get_position_x();
    current_scrambler_position[Y] = enemies.scramblers_info[towers.missile_info[current_missile].get_enemy_number()].get_position_y();
    if (towers.missile_info[current_missile].check_enemies_distance(current_scrambler_position) && (enemies.scramblers_info[towers.missile_info[current_missile].get_enemy_number()].get_status() == ALIVE))
    {
        if (towers.missile_info[current_missile].get_attack_time() % MISSILE_ATTACK_SPEED == ATTACK_TIME)
        {   
            enemies.scramblers_info[towers.missile_info[current_missile].get_enemy_number()].reduce_health(towers.missile_info[current_missile].get_damage());
            check_scrambler_killed(towers.missile_info[current_missile].get_enemy_number());
            check_for_atteck_with_missile_on_another_enemies(current_missile,current_scrambler_position);
        }
        else
            towers.missile_info[current_missile].fill_current_enemy_position(current_scrambler_position);
    }
    else
        towers.missile_info[current_missile].change_attack_status();
}

void Fieldrunners::check_for_atteck_with_missile_on_another_enemies(int current_missile, float first_enemy_position[2])
{
    vector<int> enemies_in_the_range_of_input_enemy = find_enemies_close_to_the_current_enemy(first_enemy_position, MISSILE_DAMAGE_DISTANCE);
    for(int current = 0; current < enemies_in_the_range_of_input_enemy.size(); current += 2)
    {
        if (enemies_in_the_range_of_input_enemy[current] == THE_RUNNER)
        {
            enemies.the_runners_info[enemies_in_the_range_of_input_enemy[current+1]].reduce_health(towers.missile_info[current_missile].get_damage());
            check_the_runner_killed(enemies_in_the_range_of_input_enemy[current+1]);
        }
        if (enemies_in_the_range_of_input_enemy[current] == STUBBORN_RUNNER)
        {
            enemies.stubborn_runners_info[enemies_in_the_range_of_input_enemy[current+1]].reduce_health(towers.missile_info[current_missile].get_damage());
            check_stubborn_runners_killed(enemies_in_the_range_of_input_enemy[current+1]);
        }
        if (enemies_in_the_range_of_input_enemy[current] == SUPER_TROOPER)
        {
            enemies.super_troopers_info[enemies_in_the_range_of_input_enemy[current+1]].reduce_health(towers.missile_info[current_missile].get_damage());
            check_super_trooper_killed(enemies_in_the_range_of_input_enemy[current+1]);
        }
        if (enemies_in_the_range_of_input_enemy[current] == SCRAMBLER)
        {    
            enemies.scramblers_info[enemies_in_the_range_of_input_enemy[current+1]].reduce_health(towers.missile_info[current_missile].get_damage());
            check_scrambler_killed(enemies_in_the_range_of_input_enemy[current+1]);
        }
    }
}

vector<int> Fieldrunners::find_enemies_close_to_the_current_enemy(float first_enemy_position[2], int distance)
{
    vector<int> enemies_in_the_range_of_input_enemy;
    float current_enemy_position[2];
    find_the_runner_close_to_the_current_enemy(first_enemy_position, enemies_in_the_range_of_input_enemy, distance);
    find_stubborn_runners_close_to_the_current_enemy(first_enemy_position, enemies_in_the_range_of_input_enemy, distance);
    find_super_trooper_close_to_the_current_enemy(first_enemy_position, enemies_in_the_range_of_input_enemy, distance);
    find_scrambler_close_to_the_current_enemy(first_enemy_position, enemies_in_the_range_of_input_enemy, distance);
    return enemies_in_the_range_of_input_enemy;
}

void Fieldrunners::find_the_runner_close_to_the_current_enemy(float first_enemy_position[2], vector<int> &enemies_in_the_range_of_input_enemy, int distance)
{
    float current_enemy_position[2];
    for(int current = 0; current < enemies.the_runners_info.size();current++)
    {
        current_enemy_position[X] = enemies.the_runners_info[current].get_position_x();
        current_enemy_position[Y] = enemies.the_runners_info[current].get_position_y();
        if(calculate_the_distance_between_two_enemies(first_enemy_position, current_enemy_position, distance))
        {
            enemies_in_the_range_of_input_enemy.push_back(THE_RUNNER);
            enemies_in_the_range_of_input_enemy.push_back(current);
        }
    }
}

void Fieldrunners::find_stubborn_runners_close_to_the_current_enemy(float first_enemy_position[2], vector<int> &enemies_in_the_range_of_input_enemy, int distance)
{
    float current_enemy_position[2];
    for(int current = 0; current < enemies.stubborn_runners_info.size();current++)
    {
        current_enemy_position[X] = enemies.stubborn_runners_info[current].get_position_x();
        current_enemy_position[Y] = enemies.stubborn_runners_info[current].get_position_y();
        if(calculate_the_distance_between_two_enemies(first_enemy_position, current_enemy_position, distance))
        {
            enemies_in_the_range_of_input_enemy.push_back(STUBBORN_RUNNER);
            enemies_in_the_range_of_input_enemy.push_back(current);
        }
    }
}

void Fieldrunners::find_super_trooper_close_to_the_current_enemy(float first_enemy_position[2], vector<int> &enemies_in_the_range_of_input_enemy, int distance)
{
    float current_enemy_position[2];
    for(int current = 0; current < enemies.super_troopers_info.size();current++)
    {
        current_enemy_position[X] = enemies.super_troopers_info[current].get_position_x();
        current_enemy_position[Y] = enemies.super_troopers_info[current].get_position_y();
        if(calculate_the_distance_between_two_enemies(first_enemy_position, current_enemy_position, distance))
        {
            enemies_in_the_range_of_input_enemy.push_back(SUPER_TROOPER);
            enemies_in_the_range_of_input_enemy.push_back(current);
        }
    }
}

void Fieldrunners::find_scrambler_close_to_the_current_enemy(float first_enemy_position[2], vector<int> &enemies_in_the_range_of_input_enemy, int distance)
{
    float current_enemy_position[2];
    for(int current = 0; current < enemies.scramblers_info.size();current++)
    {
        current_enemy_position[X] = enemies.scramblers_info[current].get_position_x();
        current_enemy_position[Y] = enemies.scramblers_info[current].get_position_y();
        if(calculate_the_distance_between_two_enemies(first_enemy_position, current_enemy_position, distance))
        {
            enemies_in_the_range_of_input_enemy.push_back(SCRAMBLER);
            enemies_in_the_range_of_input_enemy.push_back(current);
        }
    }
}

bool Fieldrunners::calculate_the_distance_between_two_enemies(float first_enemy_position[2], float current_the_enemy_position[2], int distance)
{
    if((pow(fabs(first_enemy_position[X] - current_the_enemy_position[X]), 2) + pow(fabs(first_enemy_position[Y] - current_the_enemy_position[Y]), 2)) <= pow(distance, 2) && (pow(fabs(first_enemy_position[X] - current_the_enemy_position[X]), 2) + pow(fabs(first_enemy_position[Y] - current_the_enemy_position[Y]), 2)) > 0)
        return true;
    else
        return false;
}

void Fieldrunners::check_for_attack_with_glue()
{
    for(int current_glue = 0 ;current_glue < towers.glue_info.size(); current_glue++ )
    {
        if (towers.glue_info[current_glue].get_status() == NOT_ATTACKING)
        {
            vector<float> closest_enemies_in_the_range_of_tower = find_enemies_in_the_range_of_glue(current_glue);
            if (closest_enemies_in_the_range_of_tower[ENEMY_TYPE] < 5)   
                towers.glue_info[current_glue].fill_enemie_details(closest_enemies_in_the_range_of_tower[ENEMY_TYPE], closest_enemies_in_the_range_of_tower[ENEMY_NUMBER]);
        }
        if (towers.glue_info[current_glue].get_status() == ATTACKING)
        {
            if (towers.glue_info[current_glue].get_enemy_type() == THE_RUNNER)
                attack_with_glue_on_the_runner(current_glue);
            if (towers.glue_info[current_glue].get_enemy_type() == STUBBORN_RUNNER)
                attack_with_glue_on_stubborn_runners(current_glue);
            if (towers.glue_info[current_glue].get_enemy_type() == SUPER_TROOPER)
                attack_with_glue_on_super_trooper(current_glue);
            if (towers.glue_info[current_glue].get_enemy_type() == SCRAMBLER)
                attack_with_glue_on_scrambler(current_glue);
        }
    }
}

vector<float> Fieldrunners::find_enemies_in_the_range_of_glue(int current_tower)
{
    vector<float> closest_enemies_in_the_range_of_tower = create_vector();
    find_the_runners_in_the_range_of_glue(current_tower, closest_enemies_in_the_range_of_tower);
    find_stubborn_runners_in_the_range_of_glue(current_tower, closest_enemies_in_the_range_of_tower);
    find_super_trooper_in_the_range_of_glue(current_tower, closest_enemies_in_the_range_of_tower);
    find_scrambler_in_the_range_of_glue(current_tower, closest_enemies_in_the_range_of_tower);
    return closest_enemies_in_the_range_of_tower;
}

void Fieldrunners::find_the_runners_in_the_range_of_glue(int current_tower, vector<float> &closest_enemies_in_the_range_of_tower)
{
    for(int current_the_runners = 0; current_the_runners < enemies.the_runners_info.size(); current_the_runners++)
    {
        float current_the_runners_position[2];
        current_the_runners_position[X] = enemies.the_runners_info[current_the_runners].get_position_x();
        current_the_runners_position[Y] = enemies.the_runners_info[current_the_runners].get_position_y();
        if(towers.glue_info[current_tower].check_enemies_distance(current_the_runners_position) && (enemies.the_runners_info[current_the_runners].get_status() == ALIVE) && (enemies.the_runners_info[current_the_runners].get_reduce_speed_status() == NOT_REDUCED))
            if (towers.glue_info[current_tower].distance_size(current_the_runners_position) < closest_enemies_in_the_range_of_tower[ENEMY_DISTANCE])
            {
                closest_enemies_in_the_range_of_tower[ENEMY_TYPE] = THE_RUNNER;
                closest_enemies_in_the_range_of_tower[ENEMY_NUMBER] = current_the_runners;
            }
    }
}

void Fieldrunners::find_stubborn_runners_in_the_range_of_glue(int current_tower, vector<float> &closest_enemies_in_the_range_of_tower)
{
    for(int current_stubborn_runners = 0; current_stubborn_runners < enemies.stubborn_runners_info.size(); current_stubborn_runners++)
    {
        float current_stubborn_runners_position[2];
        current_stubborn_runners_position[X] = enemies.stubborn_runners_info[current_stubborn_runners].get_position_x();
        current_stubborn_runners_position[Y] = enemies.stubborn_runners_info[current_stubborn_runners].get_position_y();
        if(towers.glue_info[current_tower].check_enemies_distance(current_stubborn_runners_position) && (enemies.stubborn_runners_info[current_stubborn_runners].get_status() == ALIVE) && (enemies.stubborn_runners_info[current_stubborn_runners].get_reduce_speed_status() == NOT_REDUCED))
            if (towers.glue_info[current_tower].distance_size(current_stubborn_runners_position) < closest_enemies_in_the_range_of_tower[ENEMY_DISTANCE])
            {
                closest_enemies_in_the_range_of_tower[ENEMY_TYPE] = STUBBORN_RUNNER;
                closest_enemies_in_the_range_of_tower[ENEMY_NUMBER] = current_stubborn_runners;
            }
    }
}

void Fieldrunners::find_super_trooper_in_the_range_of_glue(int current_tower, vector<float> &closest_enemies_in_the_range_of_tower)
{
    for(int current_super_troopers = 0; current_super_troopers < enemies.super_troopers_info.size(); current_super_troopers++)
    {
        float current_super_troopers_position[2];
        current_super_troopers_position[X] = enemies.super_troopers_info[current_super_troopers].get_position_x();
        current_super_troopers_position[Y] = enemies.super_troopers_info[current_super_troopers].get_position_y();
        if(towers.glue_info[current_tower].check_enemies_distance(current_super_troopers_position) && (enemies.super_troopers_info[current_super_troopers].get_status() == ALIVE) && (enemies.super_troopers_info[current_super_troopers].get_reduce_speed_status() == NOT_REDUCED))
            if (towers.glue_info[current_tower].distance_size(current_super_troopers_position) < closest_enemies_in_the_range_of_tower[ENEMY_DISTANCE])
            {
                closest_enemies_in_the_range_of_tower[ENEMY_TYPE] = SUPER_TROOPER;
                closest_enemies_in_the_range_of_tower[ENEMY_NUMBER] = current_super_troopers;
            }
    }
}

void Fieldrunners::find_scrambler_in_the_range_of_glue(int current_tower, vector<float> &closest_enemies_in_the_range_of_tower)
{
    for(int current_scramber = 0; current_scramber < enemies.scramblers_info.size(); current_scramber++)
    {
        float current_scramber_position[2];
        current_scramber_position[X] = enemies.scramblers_info[current_scramber].get_position_x();
        current_scramber_position[Y] = enemies.scramblers_info[current_scramber].get_position_y();
        if(towers.glue_info[current_tower].check_enemies_distance(current_scramber_position)&& (enemies.scramblers_info[current_scramber].get_status() == ALIVE) && (enemies.scramblers_info[current_scramber].get_reduce_speed_status() == NOT_REDUCED))
            if (towers.glue_info[current_tower].distance_size(current_scramber_position) < closest_enemies_in_the_range_of_tower[ENEMY_DISTANCE])
            {
                closest_enemies_in_the_range_of_tower[ENEMY_TYPE] = SCRAMBLER;
                closest_enemies_in_the_range_of_tower[ENEMY_NUMBER] = current_scramber;
            }
    }
}

void Fieldrunners::attack_with_glue_on_the_runner(int current_glue)
{
    float current_the_runner_position[2];
    current_the_runner_position[X] = enemies.the_runners_info[towers.glue_info[current_glue].get_enemy_number()].get_position_x();
    current_the_runner_position[Y] = enemies.the_runners_info[towers.glue_info[current_glue].get_enemy_number()].get_position_y();
    if (towers.glue_info[current_glue].check_enemies_distance(current_the_runner_position) && (enemies.the_runners_info[towers.glue_info[current_glue].get_enemy_number()].get_status() == ALIVE))
    {
        if (towers.glue_info[current_glue].get_attack_time() % GLUE_ATTACK_SPEED == ATTACK_TIME)
        {
            enemies.the_runners_info[towers.glue_info[current_glue].get_enemy_number()].reduce_speed(towers.glue_info[current_glue].get_damage(), towers.glue_info[current_glue].get_reduce_speed_time());
            check_for_atteck_with_glue_on_another_enemies(current_glue,current_the_runner_position);
        }
        else
            towers.glue_info[current_glue].fill_current_enemy_position(current_the_runner_position);
    }
    else
        towers.glue_info[current_glue].change_attack_status();
}

void Fieldrunners::attack_with_glue_on_stubborn_runners(int current_glue)
{
    float current_stubborn_runners_position[2];
    current_stubborn_runners_position[X] = enemies.stubborn_runners_info[towers.glue_info[current_glue].get_enemy_number()].get_position_x();
    current_stubborn_runners_position[Y] = enemies.stubborn_runners_info[towers.glue_info[current_glue].get_enemy_number()].get_position_y();
    if (towers.glue_info[current_glue].check_enemies_distance(current_stubborn_runners_position) && (enemies.stubborn_runners_info[towers.glue_info[current_glue].get_enemy_number()].get_status() == ALIVE))
    {
        if (towers.glue_info[current_glue].get_attack_time() % GLUE_ATTACK_SPEED == ATTACK_TIME)
           check_for_atteck_with_glue_on_another_enemies(current_glue,current_stubborn_runners_position);
        else
            towers.glue_info[current_glue].fill_current_enemy_position(current_stubborn_runners_position);
    }
    else
        towers.glue_info[current_glue].change_attack_status();
}

void Fieldrunners::attack_with_glue_on_super_trooper(int current_glue)
{
    float current_super_troopers_position[2];
    current_super_troopers_position[X] = enemies.super_troopers_info[towers.glue_info[current_glue].get_enemy_number()].get_position_x();
    current_super_troopers_position[Y] = enemies.super_troopers_info[towers.glue_info[current_glue].get_enemy_number()].get_position_y();
    if (towers.glue_info[current_glue].check_enemies_distance(current_super_troopers_position) && (enemies.super_troopers_info[towers.glue_info[current_glue].get_enemy_number()].get_status() == ALIVE))
    {
        if (towers.glue_info[current_glue].get_attack_time() % GLUE_ATTACK_SPEED == ATTACK_TIME)
        {
            enemies.super_troopers_info[towers.glue_info[current_glue].get_enemy_number()].reduce_speed(towers.glue_info[current_glue].get_damage(), towers.glue_info[current_glue].get_reduce_speed_time());
            check_for_atteck_with_glue_on_another_enemies(current_glue,current_super_troopers_position);
        }
        else
            towers.glue_info[current_glue].fill_current_enemy_position(current_super_troopers_position);
    }
    else
        towers.glue_info[current_glue].change_attack_status();
}

void Fieldrunners::attack_with_glue_on_scrambler(int current_glue)
{
    float current_scramblers_position[2];
    current_scramblers_position[X] = enemies.scramblers_info[towers.glue_info[current_glue].get_enemy_number()].get_position_x();
    current_scramblers_position[Y] = enemies.scramblers_info[towers.glue_info[current_glue].get_enemy_number()].get_position_y();
    if (towers.glue_info[current_glue].check_enemies_distance(current_scramblers_position) && (enemies.scramblers_info[towers.glue_info[current_glue].get_enemy_number()].get_status() == ALIVE))
    {
        if (towers.glue_info[current_glue].get_attack_time() % GLUE_ATTACK_SPEED == ATTACK_TIME)
        {
            enemies.scramblers_info[towers.glue_info[current_glue].get_enemy_number()].reduce_speed(towers.glue_info[current_glue].get_damage(), towers.glue_info[current_glue].get_reduce_speed_time());
            check_for_atteck_with_glue_on_another_enemies(current_glue,current_scramblers_position);
        }
        else
            towers.glue_info[current_glue].fill_current_enemy_position(current_scramblers_position);
    }
    else
        towers.glue_info[current_glue].change_attack_status();
}

void Fieldrunners::check_for_atteck_with_glue_on_another_enemies(int current_glue, float first_enemy_position[2])
{
    vector<int> enemies_in_the_range_of_input_enemy = find_enemies_close_to_the_current_enemy(first_enemy_position, GLUE_DAMAGE_DISTANCE);
    for(int current = 0; current < enemies_in_the_range_of_input_enemy.size(); current += 2)
    {
        if (enemies_in_the_range_of_input_enemy[current] == THE_RUNNER)
            enemies.the_runners_info[enemies_in_the_range_of_input_enemy[current+1]].reduce_speed(towers.glue_info[current_glue].get_damage(), towers.glue_info[current_glue].get_reduce_speed_time());
        if (enemies_in_the_range_of_input_enemy[current] == STUBBORN_RUNNER)
            enemies.stubborn_runners_info[enemies_in_the_range_of_input_enemy[current+1]].reduce_speed(towers.glue_info[current_glue].get_damage(), towers.glue_info[current_glue].get_reduce_speed_time());
        if (enemies_in_the_range_of_input_enemy[current] == SUPER_TROOPER)
            enemies.super_troopers_info[enemies_in_the_range_of_input_enemy[current+1]].reduce_speed(towers.glue_info[current_glue].get_damage(), towers.glue_info[current_glue].get_reduce_speed_time());
        if (enemies_in_the_range_of_input_enemy[current] == SCRAMBLER)
            enemies.scramblers_info[enemies_in_the_range_of_input_enemy[current+1]].reduce_speed(towers.glue_info[current_glue].get_damage(), towers.glue_info[current_glue].get_reduce_speed_time());
    }
}

void Fieldrunners::check_the_runner_killed(int current_the_runner)
{
    if(enemies.the_runners_info[current_the_runner].check_health())
    {
        enemies_killed++;
        player.gold += THE_RUNNERS_KILLING_REWARD;
    }
}

void Fieldrunners::check_super_trooper_killed(int current_super_trooper)
{
    if(enemies.super_troopers_info[current_super_trooper].check_health())
    {
        enemies_killed++;
        player.gold += SUPER_TROOPER_KILLING_REWARD;
    }
}

void Fieldrunners::check_stubborn_runners_killed(int current_stubborn_runners)
{
    if(enemies.stubborn_runners_info[current_stubborn_runners].check_health())
    {
        enemies_killed++;
        player.gold += STUBBORN_RUNNER_KILLING_REWARD;
    }
}

void Fieldrunners::check_scrambler_killed(int current_scrambler)
{
    if (enemies.scramblers_info[current_scrambler].check_health())
    {
        enemies_killed++;
        player.gold += SCRAMBLER_KILLING_REWARD;
    }
}

void Fieldrunners::check_enemies_reach_the_end_of_the_path()
{
    for (int current = 0; current < enemies.the_runners_info.size(); current++)
        enemies.the_runners_info[current].check_reach_the_end_of_the_path();
    for (int current = 0; current < enemies.scramblers_info.size(); current++)
        enemies.scramblers_info[current].check_reach_the_end_of_the_path();
    for (int current = 0; current < enemies.stubborn_runners_info.size(); current++)
        enemies.stubborn_runners_info[current].check_reach_the_end_of_the_path();
    for (int current = 0; current < enemies.super_troopers_info.size(); current++)
        enemies.super_troopers_info[current].check_reach_the_end_of_the_path();
}

void Fieldrunners::check_not_killed_enemies()
{
    for (int current = 0; current < enemies.the_runners_info.size(); current++)
        if(enemies.the_runners_info[current].check_not_being_killed())
        {
            player.hearts -= THE_RUNNERS_REDUCE_PLAYER_HEALTH;
            enemies_killed++;
        }
    for (int current = 0; current < enemies.scramblers_info.size(); current++)
        if(enemies.scramblers_info[current].check_not_being_killed())
        {
            player.hearts -= SCRAMBLER_REDUCE_PLAYER_HEALTH;
            enemies_killed++;
        }
    for (int current = 0; current < enemies.stubborn_runners_info.size(); current++)
        if(enemies.stubborn_runners_info[current].check_not_being_killed())
        {
            player.hearts -= STUBBORN_RUNNER_REDUCE_PLAYER_HEALTH;
            enemies_killed++;
        }
    for (int current = 0; current < enemies.super_troopers_info.size(); current++)
        if(enemies.super_troopers_info[current].check_not_being_killed())
        {
            player.hearts -= SUPER_TROOPER_REDUCE_PLAYER_HEALTH;
            enemies_killed++;
        }
}

void Fieldrunners::update_enemeis(Window* window)
{
    for (int i = 0; i< enemies.the_runners_info.size(); i++)
        enemies.the_runners_info[i].update(window);
    for (int i = 0; i< enemies.stubborn_runners_info.size(); i++)
        enemies.stubborn_runners_info[i].update(window);
    for (int i = 0; i< enemies.super_troopers_info.size(); i++)
        enemies.super_troopers_info[i].update(window);
    for (int i = 0; i< enemies.scramblers_info.size(); i++)
        enemies.scramblers_info[i].update(window);
}

void Fieldrunners::check_for_play_music(Window *window)
{
    if (game_status == PLAYING_GAME && play_music != PLAY_BACKGROUND_MUSIC && player.hearts >= DESIRED_PLAYER_HEALTH_FOR_PLAY_BACKGROUND_MUSIC_BEFORE_LOSE)
    {
        window->play_music(BACKGROUND_MUSIC_ADDRESS);
        play_music = PLAY_BACKGROUND_MUSIC;
    }
    if (game_status == PLAYING_GAME && play_music != PLAY_BACKGROUND_MUSIC_BEFORE_LOSE && player.hearts < DESIRED_PLAYER_HEALTH_FOR_PLAY_BACKGROUND_MUSIC_BEFORE_LOSE)
    {
        window->play_music(BACKGROUND_MUSIC_BEFORE_LOSE_ADDRESS);
        play_music = PLAY_BACKGROUND_MUSIC_BEFORE_LOSE;
    }
    if (game_status == WIN && play_music != PLAY_WIN_MUSIC)
    {
        window->play_music(YOU_WIN_MUSIC_ADDRESS);
        play_music = PLAY_WIN_MUSIC;
    }
    if (game_status == LOSE && play_music != PLAY_LOSE_MUSIC)
    {
        window->play_music(YOU_LOSE_MUSIC_ADDRESS);
        play_music = PLAY_LOSE_MUSIC;
    }
}

void Fieldrunners::draw(Window* window)
{
    window->clear();
    window->draw_img(BACKGROUND_IMAGE_FILE_ADDRESS);
    draw_route(window);
    draw_mouse_position(window);
    draw_start_end_flag(window);
    show_player_information(window);
    show_enemies_details(window);
    show_tower_details(window);
    draw_towers(window);
    draw_enemies(window);
    if (game_status != PLAYING_GAME)
        show_final_result(window);
    window->update_screen();
}

void Fieldrunners::draw_route(Window* window)
{
    for (int current_x = 0, current_y = 1; current_x < enemies_path.size() && current_y < enemies_path.size(); current_x += 2, current_y += 2)
    {
        int random = (enemies_path[current_x]+ enemies_path[current_y])% 8;
        string rand_num = convert_number_to_string(random);
        string tile_address = TILE_ADDRESS + rand_num + JPG;
        window->draw_img(tile_address,Rectangle(SQUARE_FIRST_POS_X + enemies_path[current_x]*BACKGROUND_SQUARE_LENGHT,SQUARE_FIRST_POS_Y + enemies_path[current_y]*BACKGROUND_SQUARE_LENGHT,BACKGROUND_SQUARE_LENGHT,BACKGROUND_SQUARE_LENGHT));
        draw_the_route_of_non_adjacent_houses(window, current_x, current_y);
    }
}

void Fieldrunners::draw_the_route_of_non_adjacent_houses(Window* window, int current_x, int current_y)
{
    
    if (abs(enemies_path[current_x] - enemies_path[current_x + 2]) > 1 && current_x + 2 < enemies_path.size())
        if (enemies_path[current_x] > enemies_path[current_x + 2])
            draw_rectangle_in_x(window, enemies_path[current_x + 2], enemies_path[current_y], enemies_path[current_x]);
        else
            draw_rectangle_in_x(window, enemies_path[current_x], enemies_path[current_y],enemies_path[current_x + 2]);
    if (abs(enemies_path[current_y] - enemies_path[current_y + 2]) > 1 && current_x + 2 < enemies_path.size())
        if (enemies_path[current_y] > enemies_path[current_y + 2])
            draw_rectangle_in_y(window, enemies_path[current_y + 2], enemies_path[current_x], enemies_path[current_y]);
        else
            draw_rectangle_in_y(window, enemies_path[current_y], enemies_path[current_x],enemies_path[current_y + 2]);   
}

void Fieldrunners::draw_rectangle_in_x (Window* window, int first_x, int y, int last_x)
{
    for (int current = first_x; current < last_x; current++)
    {
        int random = (current + y)% 8;
        string rand_num = convert_number_to_string(random);
        string tile_address = TILE_ADDRESS + rand_num + JPG;
        window->draw_img(tile_address, Rectangle(SQUARE_FIRST_POS_X + current*BACKGROUND_SQUARE_LENGHT,SQUARE_FIRST_POS_Y + y*BACKGROUND_SQUARE_LENGHT,BACKGROUND_SQUARE_LENGHT,BACKGROUND_SQUARE_LENGHT));
    }
}

void Fieldrunners::draw_rectangle_in_y (Window* window, int first_y, int x, int last_y)
{
    for (int current = first_y; current < last_y; current++)
    {
        int random = (x + current)% 8;
        string rand_num = convert_number_to_string(random);
        string tile_address = TILE_ADDRESS + rand_num + JPG;
        window->draw_img(tile_address, Rectangle(SQUARE_FIRST_POS_X + x*BACKGROUND_SQUARE_LENGHT,SQUARE_FIRST_POS_Y + current*BACKGROUND_SQUARE_LENGHT,BACKGROUND_SQUARE_LENGHT,BACKGROUND_SQUARE_LENGHT));
    }
}

void Fieldrunners::draw_mouse_position(Window* window)
{
    int house_pos_x = (mouse_position.x - FIRST_HOUSE_TABLE_X)/BACKGROUND_SQUARE_LENGHT;
    int house_pos_y = (mouse_position.y - FIRST_HOUSE_TABLE_Y)/BACKGROUND_SQUARE_LENGHT;
    window->draw_img(MOUSE_HOUSE_IMAGE_ADDRESS, Rectangle(FIRST_HOUSE_TABLE_X - FLAG_CALIBER_X + house_pos_x*BACKGROUND_SQUARE_LENGHT,FIRST_HOUSE_TABLE_Y - FLAG_CALIBER_Y + house_pos_y*BACKGROUND_SQUARE_LENGHT,BACKGROUND_SQUARE_LENGHT,BACKGROUND_SQUARE_LENGHT));
}

void Fieldrunners::draw_start_end_flag(Window* window)
{
    int house_pos_x = enemies_path[FIRST_X]*BACKGROUND_SQUARE_LENGHT + FIRST_HOUSE_TABLE_X;
    int house_pos_y = enemies_path[FIRST_Y]*BACKGROUND_SQUARE_LENGHT + FIRST_HOUSE_TABLE_Y;
    window->draw_img(START_FLAG_IMAGE_ADDRESS, Rectangle(house_pos_x - FLAG_CALIBER_X, house_pos_y - FLAG_CALIBER_Y, BACKGROUND_SQUARE_LENGHT, BACKGROUND_SQUARE_LENGHT));
    house_pos_x = enemies_path[enemies_path.size() - LAST_X]*BACKGROUND_SQUARE_LENGHT + FIRST_HOUSE_TABLE_X;
    house_pos_y = enemies_path[enemies_path.size() - LAST_Y]*BACKGROUND_SQUARE_LENGHT + FIRST_HOUSE_TABLE_Y;
    window->draw_img(END_FLAG_IMAGE_ADDRESS, Rectangle(house_pos_x - FLAG_CALIBER_X, house_pos_y - FLAG_CALIBER_Y, BACKGROUND_SQUARE_LENGHT, BACKGROUND_SQUARE_LENGHT));
}

void Fieldrunners::show_player_information(Window* window)
{
    window->draw_img(HEART_IMAGE_FILE_ADDRESS,Rectangle(HEART_IMAGE_POS_X,HEART_IMAGE_POS_Y,HEART_IMAGE_LENGHT,HEART_IMAGE_HIEGHT));
    window->draw_img(MONEY_IMAGE_FILE_ADDRESS,Rectangle(MONEY_IMAGE_POS_X,MONEY_IMAGE_POS_Y,MONEY_IMAGE_LENGHT,MONEY_IMAGE_HIEGHT));
    if(player.gold >= 0)
    {
        string player_gold = convert_number_to_string(player.gold);
        window->show_text(player_gold, Point (PLAYER_GOLD_INFORMATION_POS_X,PLAYER_INFORMATION_POS_Y), WHITE, FONT_ADDRESS, PLAYER_INFORMATION_FONT_SIZE);
    }
    if(player.hearts >= 0)
    {
        string player_heart = convert_number_to_string(player.hearts);
        window->show_text(player_heart, Point(PLAYER_HEART_INFORMATION_POS_X,PLAYER_INFORMATION_POS_Y), WHITE, FONT_ADDRESS, PLAYER_INFORMATION_FONT_SIZE);
    }
    string round = convert_number_to_string(wave + 1);
    window->show_text(ROUND_TEXT , Point(ROUND_TEXT_POS_X,PLAYER_INFORMATION_POS_Y), WHITE, FONT_ADDRESS, PLAYER_INFORMATION_FONT_SIZE);
    window->show_text(round, Point(ROUND_NUMBER_POS_X ,PLAYER_INFORMATION_POS_Y), WHITE, FONT_ADDRESS, PLAYER_INFORMATION_FONT_SIZE);
}

string Fieldrunners::convert_number_to_string(int number)
{
    string reversed_number;
    if (number <= 0)
    {
        string zero_number;
        zero_number.push_back(ZERO_CHARACTER);
        return zero_number;
    }
    while (number > 0)
    {
        int current_number = number % 10;
        reversed_number.push_back(char(current_number + 48));
        number = (number - current_number)/10;
    }
    string converted_number;
    for (int current = reversed_number.size() - 1; current >=0; current--)
        converted_number.push_back(reversed_number[current]);
    return converted_number;
}

void Fieldrunners::show_tower_details(Window* window)
{
    window->show_text(BUILDING_COST, Point(TOWER_DETAILS_TEXT_POS_X, TEXT_DETAILS_LINE_ONE_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
    window->show_text(UPGRADE_COST, Point(TOWER_DETAILS_TEXT_POS_X, TEXT_DETAILS_LINE_TWO_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
    show_gattling_details(window);
    show_tesla_details(window);
    show_missile_trooper_details(window);
    show_glue_details(window);
}

void Fieldrunners::show_gattling_details(Window* window)
{
    window->draw_img(GATLING_BACKGROND_IMAGE_ADDRESS,Rectangle(FIRST_TOWER_DETAILS_TEXT_POS_X, IMAGE_DETAILS_POS_Y - FLAG_CALIBER_Y,BACKGROUND_SQUARE_LENGHT ,BACKGROUND_SQUARE_LENGHT ));
    string building_cost = convert_number_to_string(GATLING_BUILDING_COST);
    window->show_text(building_cost, Point(FIRST_TOWER_DETAILS_TEXT_POS_X, TEXT_DETAILS_LINE_ONE_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
    string upgrade_cost = convert_number_to_string(GATLING_UPGRADE_COST);
    window->show_text(upgrade_cost, Point(FIRST_TOWER_DETAILS_TEXT_POS_X, TEXT_DETAILS_LINE_TWO_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
}

void Fieldrunners::show_tesla_details(Window* window)
{
    window->draw_img(TESLA_BACKGROND_IMAGE_ADDRESS,Rectangle(FIRST_TOWER_DETAILS_TEXT_POS_X + 2*DISTANCE_BETWEEN_NUMBER_TEXT, IMAGE_DETAILS_POS_Y - FLAG_CALIBER_Y,TESLA_IMAGE_WIDTH - 2*FLAG_CALIBER_Y,TESLA_IMAGE_HEIGHT));
    string building_cost = convert_number_to_string(TESLA_BUILDING_COST);
    window->show_text(building_cost, Point(FIRST_TOWER_DETAILS_TEXT_POS_X + 2*DISTANCE_BETWEEN_NUMBER_TEXT, TEXT_DETAILS_LINE_ONE_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
    string upgrade_cost = convert_number_to_string(TESLA_UPGRADE_COST);
    window->show_text(upgrade_cost, Point(FIRST_TOWER_DETAILS_TEXT_POS_X + 2*DISTANCE_BETWEEN_NUMBER_TEXT, TEXT_DETAILS_LINE_TWO_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
}

void Fieldrunners::show_missile_trooper_details(Window* window)
{
    window->draw_img(MISSILE_BACKGROND_IMAGE_ADDRESS,Rectangle(FIRST_TOWER_DETAILS_TEXT_POS_X + DISTANCE_BETWEEN_NUMBER_TEXT, IMAGE_DETAILS_POS_Y - FLAG_CALIBER_Y,BACKGROUND_SQUARE_LENGHT ,BACKGROUND_SQUARE_LENGHT ));
    string building_cost = convert_number_to_string(MISSILE_BUILDING_COST);
    window->show_text(building_cost, Point(FIRST_TOWER_DETAILS_TEXT_POS_X + DISTANCE_BETWEEN_NUMBER_TEXT, TEXT_DETAILS_LINE_ONE_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
    string upgrade_cost = convert_number_to_string(MISSILE_UPGRADE_COST);
    window->show_text(upgrade_cost, Point(FIRST_TOWER_DETAILS_TEXT_POS_X + DISTANCE_BETWEEN_NUMBER_TEXT, TEXT_DETAILS_LINE_TWO_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
}

void Fieldrunners::show_glue_details(Window* window)
{
    window->draw_img(GLUE_BACKGROND_IMAGE_ADDRESS,Rectangle(FIRST_TOWER_DETAILS_TEXT_POS_X + 3*DISTANCE_BETWEEN_NUMBER_TEXT, IMAGE_DETAILS_POS_Y - FLAG_CALIBER_Y,BACKGROUND_SQUARE_LENGHT ,BACKGROUND_SQUARE_LENGHT ));
    string building_cost = convert_number_to_string(GLUE_BUILDING_COST);
    window->show_text(building_cost, Point(FIRST_TOWER_DETAILS_TEXT_POS_X + 3*DISTANCE_BETWEEN_NUMBER_TEXT, TEXT_DETAILS_LINE_ONE_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
    string upgrade_cost = convert_number_to_string(GLUE_UPGRADE_COST);
    window->show_text(upgrade_cost, Point(FIRST_TOWER_DETAILS_TEXT_POS_X + 3*DISTANCE_BETWEEN_NUMBER_TEXT, TEXT_DETAILS_LINE_TWO_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
}

void Fieldrunners::show_enemies_details(Window* window)
{
    window->show_text(KILLING_REWARD , Point(ENEMY_DETAILS_TEXT_POS_X, TEXT_DETAILS_LINE_ONE_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
    window->show_text(REDUCE_HEALTH, Point(ENEMY_DETAILS_TEXT_POS_X, TEXT_DETAILS_LINE_TWO_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
    show_runner_details(window);
    show_stubborn_runner_details(window);
    show_super_trooper_details(window);
    show_scrambler_details(window);
}

void Fieldrunners::show_runner_details(Window* window)
{
    window->draw_img(THE_RUNNER_BACKGROND_IMAGE_ADDRESS,Rectangle(FIRST_ENEMY_DETAILS_TEXT_POS_X, IMAGE_DETAILS_POS_Y,THE_RUNNERS_IMAGE_WIDTH,THE_RUNNERS_IMAGE_HEIGHT));
    string killing_reward = convert_number_to_string(THE_RUNNERS_KILLING_REWARD);
    window->show_text(killing_reward, Point(FIRST_ENEMY_DETAILS_TEXT_POS_X, TEXT_DETAILS_LINE_ONE_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
    string reduce_health = convert_number_to_string(THE_RUNNERS_REDUCE_PLAYER_HEALTH);
    window->show_text(reduce_health, Point(FIRST_ENEMY_DETAILS_TEXT_POS_X, TEXT_DETAILS_LINE_TWO_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
}

void Fieldrunners::show_stubborn_runner_details(Window* window)
{
    window->draw_img(STUBBORN_RUNNER_BACKGROND_IMAGE_ADDRESS,Rectangle(FIRST_ENEMY_DETAILS_TEXT_POS_X + DISTANCE_BETWEEN_NUMBER_TEXT, IMAGE_DETAILS_POS_Y,STUBBORN_RUNNER_IMAGE_WIDTH,STUBBORN_RUNNER_IMAGE_HEIGHT));
    string killing_reward = convert_number_to_string(STUBBORN_RUNNER_KILLING_REWARD);
    window->show_text(killing_reward, Point(FIRST_ENEMY_DETAILS_TEXT_POS_X + DISTANCE_BETWEEN_NUMBER_TEXT, TEXT_DETAILS_LINE_ONE_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
    string reduce_health = convert_number_to_string(STUBBORN_RUNNER_REDUCE_PLAYER_HEALTH);
    window->show_text(reduce_health, Point(FIRST_ENEMY_DETAILS_TEXT_POS_X + DISTANCE_BETWEEN_NUMBER_TEXT, TEXT_DETAILS_LINE_TWO_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
}

void Fieldrunners::show_super_trooper_details(Window* window)
{
    window->draw_img(SUPER_TROOPER_BACKGROND_IMAGE_ADDRESS,Rectangle(FIRST_ENEMY_DETAILS_TEXT_POS_X + 2*DISTANCE_BETWEEN_NUMBER_TEXT, IMAGE_DETAILS_POS_Y,SUPER_TROOPER_IMAGE_WIDTH,SUPER_TROOPER_IMAGE_HEIGHT));
    string killing_reward = convert_number_to_string(SUPER_TROOPER_KILLING_REWARD);
    window->show_text(killing_reward, Point(FIRST_ENEMY_DETAILS_TEXT_POS_X + 2*DISTANCE_BETWEEN_NUMBER_TEXT, TEXT_DETAILS_LINE_ONE_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
    string reduce_health = convert_number_to_string(SUPER_TROOPER_REDUCE_PLAYER_HEALTH);
    window->show_text(reduce_health, Point(FIRST_ENEMY_DETAILS_TEXT_POS_X + 2*DISTANCE_BETWEEN_NUMBER_TEXT, TEXT_DETAILS_LINE_TWO_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
}

void Fieldrunners::show_scrambler_details(Window* window)
{
    window->draw_img(SCRAMBLER_BACKGROND_IMAGE_ADDRESS,Rectangle(FIRST_ENEMY_DETAILS_TEXT_POS_X + 3*DISTANCE_BETWEEN_NUMBER_TEXT, IMAGE_DETAILS_POS_Y,SCRAMBLER_IMAGE_WIDTH,SCRAMBLER_IMAGE_HEIGHT - FLAG_CALIBER_Y));
    string killing_reward = convert_number_to_string(SCRAMBLER_KILLING_REWARD);
    window->show_text(killing_reward, Point(FIRST_ENEMY_DETAILS_TEXT_POS_X + 3*DISTANCE_BETWEEN_NUMBER_TEXT, TEXT_DETAILS_LINE_ONE_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
    string reduce_health = convert_number_to_string(SCRAMBLER_REDUCE_PLAYER_HEALTH);
    window->show_text(reduce_health, Point(FIRST_ENEMY_DETAILS_TEXT_POS_X + 3*DISTANCE_BETWEEN_NUMBER_TEXT, TEXT_DETAILS_LINE_TWO_POS_Y),WHITE, FONT_ADDRESS , PLAYER_INFORMATION_FONT_SIZE);
}

void Fieldrunners::draw_towers(Window* window)
{
    for (int current = 0; current < towers.gatling_info.size(); current++)
        towers.gatling_info[current].draw(window);
    for(int current = 0; current < towers.tesla_info.size(); current++)
        towers.tesla_info[current].draw(window); 
    for(int current = 0; current < towers.missile_info.size(); current++)
        towers.missile_info[current].draw(window);
    for(int current = 0;current < towers.glue_info.size(); current++)
        towers.glue_info[current].draw(window);
}

void Fieldrunners::draw_enemies(Window* window)
{
    for (int i = 0; i< enemies.the_runners_info.size(); i++)
        enemies.the_runners_info[i].draw(window);
    for (int i = 0; i< enemies.stubborn_runners_info.size(); i++)
        enemies.stubborn_runners_info[i].draw(window);
    for (int i = 0; i< enemies.super_troopers_info.size(); i++)
        enemies.super_troopers_info[i].draw(window);
    for (int i = 0; i< enemies.scramblers_info.size(); i++)
        enemies.scramblers_info[i].draw(window);
}

void Fieldrunners::show_final_result(Window* window)
{
    if (game_status == WIN)
        window->draw_img(WIN_IMAGE_ADDRESS,Rectangle(0,0,GAME_WINDOW_LENGHT,GAME_WINDOW_HEIGHT));
    if (game_status == LOSE)
        window->draw_img(LOSE_IMAGE_ADDRESS,Rectangle(0,0,GAME_WINDOW_LENGHT,GAME_WINDOW_HEIGHT));
}

int Fieldrunners::get_game_status() {return game_status;}
void Fieldrunners::upgrade_time_count() { time_count++;}

void Fieldrunners::check_end_game()
{
    if (enemies_killed == number_of_enemy_in_current_wave)
    {
        wave++;
        if(wave < waves.size())
        {
            enemies.the_runners_info.clear();
            enemies.super_troopers_info.clear();
            enemies.stubborn_runners_info.clear();
            enemies.scramblers_info.clear();
            number_of_enemy_in_current_wave = calculate_number_of_enemies_in_current_wave();
            enemies_killed = 0;
            delay(DELAY_BETWEEN_WAVES);
        }
        else if(player.hearts > 0)
            game_status = WIN;
        else
            game_status = LOSE;
    }
    else if (player.hearts <= 0)
        game_status = LOSE;
}

int Fieldrunners::calculate_number_of_enemies_in_current_wave()
{
    number_of_enemy_in_current_wave = 0;
    for (int current = 0; current < 4 ;current++)
        number_of_enemy_in_current_wave += waves[wave][current];
    return number_of_enemy_in_current_wave;
}