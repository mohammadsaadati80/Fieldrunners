#include "Glue.hpp"
using namespace std;

void Glue::initialization(Point mouse_position)
{
    house_position[X] = (mouse_position.x - FIRST_HOUSE_TABLE_X)/BACKGROUND_SQUARE_LENGHT;
    house_position[Y]= (mouse_position.y - FIRST_HOUSE_TABLE_Y)/BACKGROUND_SQUARE_LENGHT;
    position[X] = GLUE_FIRST_POS_X + house_position[X]*BACKGROUND_SQUARE_LENGHT;
    position[Y] = GLUE_FIRST_POS_Y + house_position[Y]*BACKGROUND_SQUARE_LENGHT;
    state = 1;
    reduce_speed = float(GLUE_REDUCE_SPEED);
    attack_time = 0;
    status = NOT_ATTACKING;
    reduce_speed_time = GLUE_REDUCE_SPEED_TIME;
}

void Glue::draw(Window* window)
{
    if (status == NOT_ATTACKING)
        draw_not_attacking_tower(window);
    else
        draw_tower(window);
    if(status == ATTACKING  && attack_time % GLUE_ATTACK_SPEED < ATTACK_TIME)
        draw_attack_arrow(window);
    if(status == ATTACKING)
        attack_time++;
    if ((attack_time % GLUE_ATTACK_SPEED) == 0)
        attack_time = 0;
}

void Glue::draw_not_attacking_tower(Window* window)
{
    if (state == 1)
        window->draw_img(GLUE_IMAGE_FILE_ADDRESS_1,Rectangle(position[X], position[Y], GLUE_IMAGE_LENGHT, GLUE_IMAGE_LENGHT));
    if (state == 2)
        window->draw_img(GLUE_IMAGE_FILE_ADDRESS_2,Rectangle(position[X], position[Y], GLUE_IMAGE_LENGHT, GLUE_IMAGE_LENGHT));
    if (state == 3)
        window->draw_img(GLUE_IMAGE_FILE_ADDRESS_3,Rectangle(position[X], position[Y], GLUE_IMAGE_LENGHT, GLUE_IMAGE_LENGHT));
}

void Glue::draw_tower(Window* window)
{
    double angle = calculate_angle_between_tower_and_enemy(current_enemy_position,position);
    if (angle < 180)
        draw_normal_tower(window, angle);
    else
        draw_horizontal_tower(window, angle);
}

void Glue::draw_normal_tower(Window* window, double angle)
{
    int number = angle/10 + 1;
    string num = convert_number_to_string(number);
    if (state == 1)
        window->draw_img(GLUE_ATTACK_IMAGE_FILE_ADDRESS_1 + num + PNG,Rectangle(position[X], position[Y], GLUE_IMAGE_LENGHT, GLUE_IMAGE_LENGHT));
    if (state == 2)
        window->draw_img(GLUE_ATTACK_IMAGE_FILE_ADDRESS_2 + num + PNG,Rectangle(position[X], position[Y], GLUE_IMAGE_LENGHT, GLUE_IMAGE_LENGHT));
    if (state == 3)
        window->draw_img(GLUE_ATTACK_IMAGE_FILE_ADDRESS_3 + num + PNG,Rectangle(position[X], position[Y], GLUE_IMAGE_LENGHT, GLUE_IMAGE_LENGHT));
}

void Glue::draw_horizontal_tower(Window* window, double angle)
{
    angle = 360 - angle;
        int number = angle/10 + 1;
        string num = convert_number_to_string(number);
        if (state == 1)
            window->draw_img(GLUE_ATTACK_IMAGE_FILE_ADDRESS_1 + num + PNG,Rectangle(position[X], position[Y], GLUE_IMAGE_LENGHT, GLUE_IMAGE_LENGHT), NULL_RECT,0,true);
        if (state == 2)
            window->draw_img(GLUE_ATTACK_IMAGE_FILE_ADDRESS_2 + num + PNG,Rectangle(position[X], position[Y], GLUE_IMAGE_LENGHT, GLUE_IMAGE_LENGHT), NULL_RECT,0,true);
        if (state == 3)
            window->draw_img(GLUE_ATTACK_IMAGE_FILE_ADDRESS_3 + num + PNG,Rectangle(position[X], position[Y], GLUE_IMAGE_LENGHT, GLUE_IMAGE_LENGHT), NULL_RECT,0,true);
}

double Glue::calculate_angle_between_tower_and_enemy(float current_enemy_position[2], float position[2])
{
    double angle = atan2(current_enemy_position[Y] - position[Y], current_enemy_position[X] - position[X])*double(180)/double(PI);
	if (angle < 0)
		angle += double(360);
    angle += 90;
    if (angle >= 360)
        angle -= 360;
    return angle;
}

string Glue::convert_number_to_string(int number)
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

void Glue::draw_attack_arrow(Window* window)
{
    float arrow_position[2];
    int turn = attack_time;
    if (current_enemy_position[X] >= position[X])
        arrow_position[X] = position[X] + GLUE_FIRST_ARROW_POS_X + (current_enemy_position[X] - position[X])/float(GLUE_ATTACK_TURN)*float(turn);
    if (current_enemy_position[Y] >= position[Y])
        arrow_position[Y] = position[Y] + GLUE_FIRST_ARROW_POS_Y + (current_enemy_position[Y] - position[Y])/float(GLUE_ATTACK_TURN)*float(turn);
    if (current_enemy_position[Y] < position[Y])
        arrow_position[Y] = position[Y] + GLUE_FIRST_ARROW_POS_Y - (position[Y] - current_enemy_position[Y])/float(GLUE_ATTACK_TURN)*float(turn);
    if (current_enemy_position[X] < position[X])
        arrow_position[X] = position[X] + GLUE_FIRST_ARROW_POS_X - (position[X] - current_enemy_position[X])/float(GLUE_ATTACK_TURN)*float(turn);
    window->draw_img(GLUE_ARROW_IMAGE_ADDRESS, Rectangle(arrow_position[X] - ARROW_REDIUS,arrow_position[Y] - ARROW_REDIUS,2*ARROW_REDIUS,2*ARROW_REDIUS));
    window->play_sound_effect(GLUE_ATTACK_SOUND_ADDRESS);
}

bool Glue::check_enemies_distance(float enemie_pos[2])
{
    if (pow(fabs(enemie_pos[X] - position[X]), 2) + pow(fabs(enemie_pos[Y] - position[Y]), 2) <= pow(GLUE_ATTACK_DISTANCE, 2))
        return true;
    else
        return false;
}

float Glue::distance_size(float enemie_pos[2])
{
    return (pow(fabs(enemie_pos[X] - position[X]), 2) + pow(fabs(enemie_pos[Y] - position[Y]), 2));
}

int Glue::get_status() {return status;}

void Glue::fill_enemie_details(int enemy_type ,int enemy_num)
{
    status = ATTACKING;
    enemy_number = enemy_num;
    enemie_type = enemy_type;
}

float Glue::get_damage()
 {  
    if ((attack_time % GLUE_ATTACK_SPEED == ATTACK_TIME) && status == ATTACKING)
        return reduce_speed;
    else
        return 0;
}

int Glue::get_reduce_speed_time() { return reduce_speed_time;}
int Glue::get_house_position_x() {return house_position[X];}
int Glue::get_house_position_y() {return house_position[Y];}

void Glue::upgrade()
{
    state++;
    reduce_speed += GLUE_UPGRADE_REDUCE_SPEED;
    reduce_speed_time += GLUE_UPGRADE_REDUCE_SPEED_TIME;
}

int Glue::get_enemy_type() {return enemie_type;}
int Glue::get_enemy_number() {return enemy_number;}
int Glue::get_attack_time() {return attack_time;}

void Glue::change_attack_status()
{
    status = NOT_ATTACKING;
}

void Glue::fill_current_enemy_position(float current_enemy_pos[2])
{
    current_enemy_position[X] = current_enemy_pos[X];
    current_enemy_position[Y] = current_enemy_pos[Y];
}