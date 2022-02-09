#include "Tesla.hpp"
using namespace std;

void Tesla::initialization(Point mouse_position)
{
    house_position[X] = (mouse_position.x - FIRST_HOUSE_TABLE_X)/BACKGROUND_SQUARE_LENGHT;
    house_position[Y]= (mouse_position.y - FIRST_HOUSE_TABLE_Y)/BACKGROUND_SQUARE_LENGHT;
    position[X] = TESLA_FIRST_POS_X + house_position[X]*BACKGROUND_SQUARE_LENGHT;
    position[Y] = TESLA_FIRST_POS_Y + house_position[Y]*BACKGROUND_SQUARE_LENGHT;
    state = 1;
    damage = TESLA_DAMAGE;
    attack_time = 0;
    status = NOT_ATTACKING;
}

void Tesla::draw(Window* window)
{
    draw_tower(window);
    if(status == ATTACKING  && attack_time % TESLA_ATTACK_SPEED < ATTACK_TIME)
        draw_attack_arrow(window);
    if(status == ATTACKING)
        attack_time++;
    if ((attack_time % TESLA_ATTACK_SPEED) == 0)
        attack_time = 0; 
}

void Tesla::draw_tower(Window* window)
{
    if (status == ATTACKING && attack_time < ATTACK_TIME)
        draw_attacking_tower(window);
    else
        draw_not_attacking_tower(window);
}

void Tesla::draw_attacking_tower(Window* window)
{
    if (state == 1)
        window->draw_img(TESLA1_IMAGE_FILE_ADDRESS_2,Rectangle(position[X], position[Y], TESLA_IMAGE_WIDTH, TESLA_IMAGE_HEIGHT));
    if (state == 2)
        window->draw_img(TESLA2_IMAGE_FILE_ADDRESS_2,Rectangle(position[X], position[Y], TESLA_IMAGE_WIDTH, TESLA_IMAGE_HEIGHT));
    if (state == 3)
        window->draw_img(TESLA3_IMAGE_FILE_ADDRESS_2,Rectangle(position[X], position[Y], TESLA_IMAGE_WIDTH, TESLA_IMAGE_HEIGHT));
}

void Tesla::draw_not_attacking_tower(Window* window)
{
    if (state == 1)
        window->draw_img(TESLA1_IMAGE_FILE_ADDRESS_1,Rectangle(position[X], position[Y], TESLA_IMAGE_WIDTH, TESLA_IMAGE_HEIGHT));
    if (state == 2)
        window->draw_img(TESLA2_IMAGE_FILE_ADDRESS_1,Rectangle(position[X], position[Y], TESLA_IMAGE_WIDTH, TESLA_IMAGE_HEIGHT));
    if (state == 3)
        window->draw_img(TESLA3_IMAGE_FILE_ADDRESS_1,Rectangle(position[X], position[Y], TESLA_IMAGE_WIDTH, TESLA_IMAGE_HEIGHT));
}

void Tesla::draw_attack_arrow(Window* window)
{
    float arrow_position[2];
    int turn = attack_time;
    if (current_enemy_position[X] >= position[X])
        arrow_position[X] = position[X] + TESLA_FIRST_ARROW_POS_X + (current_enemy_position[X] - position[X])/float(TESLA_ATTACK_TURN)*float(turn);
    if (current_enemy_position[Y] >= position[Y])
        arrow_position[Y] = position[Y] + TESLA_FIRST_ARROW_POS_Y + (current_enemy_position[Y] - position[Y])/float(TESLA_ATTACK_TURN)*float(turn);
    if (current_enemy_position[Y] < position[Y])
        arrow_position[Y] = position[Y] + TESLA_FIRST_ARROW_POS_Y - (position[Y] - current_enemy_position[Y])/float(TESLA_ATTACK_TURN)*float(turn);
    if (current_enemy_position[X] < position[X])
        arrow_position[X] = position[X] + TESLA_FIRST_ARROW_POS_X - (position[X] - current_enemy_position[X])/float(TESLA_ATTACK_TURN)*float(turn);
    window->draw_img(TESLA_ARROW_IMAGE_ADDRESS, Rectangle(arrow_position[X] - ARROW_REDIUS,arrow_position[Y] - ARROW_REDIUS,2*ARROW_REDIUS,2*ARROW_REDIUS));
    window->play_sound_effect(TESLA_ATTACK_SOUND_ADDRESS);
}

bool Tesla::check_enemies_distance(float enemie_pos[2])
{
    if (pow(fabs(enemie_pos[X] - position[X]), 2) + pow(fabs(enemie_pos[Y] - position[Y]), 2) <= pow(TESLA_ATTACK_DISTANCE, 2))
        return true;
    else
        return false;
}

float Tesla::distance_size(float enemie_pos[2])
{
    return (pow(fabs(enemie_pos[X] - position[X]), 2) + pow(fabs(enemie_pos[Y] - position[Y]), 2));
}

int Tesla::get_status() {return status;}

void Tesla::fill_enemie_details(int enemy_type ,int enemy_num)
{
    status = ATTACKING;
    enemy_number = enemy_num;
    enemie_type = enemy_type;
}

int Tesla::get_damage()
 {
    if ((attack_time % TESLA_ATTACK_SPEED == ATTACK_TIME) && status == ATTACKING)
        return damage;
    else
        return 0; 
}

int Tesla::get_house_position_x() {return house_position[X];}
int Tesla::get_house_position_y() {return house_position[Y];}

void Tesla::upgrade()
{
    state++;
    damage += TESLA_UPGRADE_DAMAGE;
}

int Tesla::get_enemy_type() {return enemie_type;}
int Tesla::get_enemy_number() {return enemy_number;}
int Tesla::get_attack_time() {return attack_time;}

void Tesla::change_attack_status()
{
    status = NOT_ATTACKING;
}

void Tesla::fill_current_enemy_position(float current_enemy_pos[2])
{
    current_enemy_position[X] = current_enemy_pos[X];
    current_enemy_position[Y] = current_enemy_pos[Y];
}