#include "Missile.hpp"
using namespace std;

void Missile::initialization(Point mouse_position)
{
    house_position[X] = (mouse_position.x - FIRST_HOUSE_TABLE_X)/BACKGROUND_SQUARE_LENGHT;
    house_position[Y]= (mouse_position.y - FIRST_HOUSE_TABLE_Y)/BACKGROUND_SQUARE_LENGHT;
    position[X] = MISSILE_FIRST_POS_X + house_position[X]*BACKGROUND_SQUARE_LENGHT;
    position[Y] = MISSILE_FIRST_POS_Y + house_position[Y]*BACKGROUND_SQUARE_LENGHT;
    state = 1;
    damage = MISSILE_DAMAGE;
    attack_time = 0;
    status = NOT_ATTACKING;
}

void Missile::draw(Window* window)
{
    if (status == NOT_ATTACKING)
        draw_not_attacking_tower(window);
    else
        draw_tower(window);
    if(status == ATTACKING  && attack_time % MISSILE_ATTACK_SPEED < ATTACK_TIME)
        draw_attack_arrow(window);
    if(status == ATTACKING)
        attack_time++;
    if ((attack_time % MISSILE_ATTACK_SPEED) == 0)
        attack_time = 0;
}

void Missile::draw_not_attacking_tower(Window* window)
{
    if (state == 1)
        window->draw_img(MISSILE_IMAGE_FILE_ADDRESS_1,Rectangle(position[X], position[Y], MISSILE_IMAGE_LENGHT, MISSILE_IMAGE_LENGHT));
    if (state == 2)
        window->draw_img(MISSILE_IMAGE_FILE_ADDRESS_2,Rectangle(position[X], position[Y], MISSILE_IMAGE_LENGHT, MISSILE_IMAGE_LENGHT));
    if (state == 3)
        window->draw_img(MISSILE_IMAGE_FILE_ADDRESS_3,Rectangle(position[X], position[Y], MISSILE_IMAGE_LENGHT, MISSILE_IMAGE_LENGHT));
}

void Missile::draw_tower(Window* window)
{
    double angle = calculate_angle_between_tower_and_enemy(current_enemy_position,position);
    if (angle <= 180)
        draw_normal_tower(window, angle);
    else
        draw_horizontal_tower(window, angle);
}

void Missile::draw_normal_tower(Window* window, double angle)
{
    int number = angle/10 + 1;
    string num = convert_number_to_string(number);
    if (state == 1)
        window->draw_img(MISSILE_ATTACK_IMAGE_FILE_ADDRESS_1 + num + PNG,Rectangle(position[X], position[Y], MISSILE_IMAGE_LENGHT, MISSILE_IMAGE_LENGHT));
    if (state == 2)
        window->draw_img(MISSILE_ATTACK_IMAGE_FILE_ADDRESS_2 + num + PNG,Rectangle(position[X], position[Y], MISSILE_IMAGE_LENGHT, MISSILE_IMAGE_LENGHT));
    if (state == 3)
       window->draw_img(MISSILE_ATTACK_IMAGE_FILE_ADDRESS_3 + num + PNG,Rectangle(position[X], position[Y], MISSILE_IMAGE_LENGHT, MISSILE_IMAGE_LENGHT));
}

void Missile::draw_horizontal_tower(Window* window, double angle)
{
    angle = 360 - angle;
    int number = angle/10 + 1;
    string num = convert_number_to_string(number);
    if (state == 1)
        window->draw_img(MISSILE_ATTACK_IMAGE_FILE_ADDRESS_1 + num + PNG,Rectangle(position[X], position[Y], MISSILE_IMAGE_LENGHT, MISSILE_IMAGE_LENGHT), NULL_RECT,0,true);
    if (state == 2)
        window->draw_img(MISSILE_ATTACK_IMAGE_FILE_ADDRESS_2 + num + PNG,Rectangle(position[X], position[Y], MISSILE_IMAGE_LENGHT, MISSILE_IMAGE_LENGHT), NULL_RECT,0,true);
    if (state == 3)
        window->draw_img(MISSILE_ATTACK_IMAGE_FILE_ADDRESS_3 + num + PNG,Rectangle(position[X], position[Y], MISSILE_IMAGE_LENGHT, MISSILE_IMAGE_LENGHT), NULL_RECT,0,true);
}

double Missile::calculate_angle_between_tower_and_enemy(float current_enemy_position[2], float position[2])
{
    double angle = atan2(current_enemy_position[Y] - position[Y], current_enemy_position[X] - position[X])*double(180)/double(PI);
	if (angle < 0)
		angle += double(360);
    angle += 90;
    if (angle >= 360)
        angle -= 360;
    return angle;
}

string Missile::convert_number_to_string(int number)
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

void Missile::draw_attack_arrow(Window* window)
{   
    float arrow_position[2];
    int turn = attack_time;
    if (current_enemy_position[X] >= position[X])
        arrow_position[X] = position[X] + MISSILE_FIRST_ARROW_POS_X + (current_enemy_position[X] - position[X])/float(MISSILE_ATTACK_TURN)*float(turn);
    if (current_enemy_position[Y] >= position[Y])
        arrow_position[Y] = position[Y] + MISSILE_FIRST_ARROW_POS_Y + (current_enemy_position[Y] - position[Y])/float(MISSILE_ATTACK_TURN)*float(turn);
    if (current_enemy_position[Y] < position[Y])
        arrow_position[Y] = position[Y] + MISSILE_FIRST_ARROW_POS_Y - (position[Y] - current_enemy_position[Y])/float(MISSILE_ATTACK_TURN)*float(turn);
    if (current_enemy_position[X] < position[X])
        arrow_position[X] = position[X] + MISSILE_FIRST_ARROW_POS_X - (position[X] - current_enemy_position[X])/float(MISSILE_ATTACK_TURN)*float(turn);
    window->draw_img(MISSILE_ARROW_IMAGE_ADDRESS, Rectangle(arrow_position[X] - ARROW_REDIUS,arrow_position[Y] - ARROW_REDIUS,2*ARROW_REDIUS,2*ARROW_REDIUS));
    window->play_sound_effect(MISSILE_ATTACK_SOUND_ADDRESS);
}

bool Missile::check_enemies_distance(float enemie_pos[2])
{
    if (pow(fabs(enemie_pos[X] - position[X]), 2) + pow(fabs(enemie_pos[Y] - position[Y]), 2) <= pow(MISSILE_ATTACK_DISTANCE, 2))
        return true;
    else
        return false;
}

float Missile::distance_size(float enemie_pos[2])
{
    return (pow(fabs(enemie_pos[X] - position[X]), 2) + pow(fabs(enemie_pos[Y] - position[Y]), 2));
}

int Missile::get_status() {return status;}

void Missile::fill_enemie_details(int enemy_type ,int enemy_num)
{
    status = ATTACKING;
    enemy_number = enemy_num;
    enemie_type = enemy_type;
}

int Missile::get_damage()
 {
    if ((attack_time % MISSILE_ATTACK_SPEED == ATTACK_TIME) && status == ATTACKING)
        return damage;
    else
        return 0;
}

int Missile::get_house_position_x() {return house_position[X];}
int Missile::get_house_position_y() {return house_position[Y];}

void Missile::upgrade()
{
    state++;
    damage += MISSILE_UPGRADE_DAMAGE;
}

int Missile::get_enemy_type() {return enemie_type;}
int Missile::get_enemy_number() {return enemy_number;}
int Missile::get_attack_time() {return attack_time;}

void Missile::change_attack_status()
{
    status = NOT_ATTACKING;
}

void Missile::fill_current_enemy_position(float current_enemy_pos[2])
{
    current_enemy_position[X] = current_enemy_pos[X];
    current_enemy_position[Y] = current_enemy_pos[Y];
}