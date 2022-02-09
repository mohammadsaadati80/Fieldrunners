#include "The_Runner.hpp"
using namespace std;

void The_Runners::first_pos(vector<int> enemies_path,int wave)
{
    current_house[X] = FIRST_X;
    current_house[Y] = FIRST_Y;
    enemie_path = enemies_path;
    position[X] = THE_RUNNERS_FIRST_POS_X + enemies_path[current_house[X]]*BACKGROUND_SQUARE_LENGHT;
    position[Y] = THE_RUNNERS_FIRST_POS_Y + enemies_path[current_house[Y]]*BACKGROUND_SQUARE_LENGHT;
    health = (double(ENEMY_HEALTH_BASE) + double(ENEMY_HEALTH_ADDITIONAL)*(float(wave + 1)))*float(THE_RUNNERS_INITIAL_HEALTH);
    initial_health = health;
    status = ALIVE;
    moving_status = MOVING;
    speed = float(THE_RUNNERS_SPEED)*float(DELAY)/float(1000);
    reduce_speed_status = NOT_REDUCED;
    current_reduce_speed_time = 0;
    movement_direction = 0;
    image_count = 0;
}

void The_Runners::update(Window* window)
{
    if(reduce_speed_status == REDUCED)
        current_reduce_speed_time++;
    if (reduce_speed_status == REDUCED && current_reduce_speed_time % reduce_speed_time == 0)
    {
        current_reduce_speed_time = 0;
        reduce_speed_status = NOT_REDUCED;
        speed = float(THE_RUNNERS_SPEED)*float(DELAY)/float(1000);
    }
    find_next_direction();
    update_current_position();    
}

void The_Runners::find_next_direction()
{
    if (((THE_RUNNERS_FIRST_POS_X + enemie_path[current_house[X] + 2]*BACKGROUND_SQUARE_LENGHT) > position[X]) && (enemie_path[current_house[Y] + 2] == enemie_path[current_house[Y]])) 
    {
        position[X] += speed;
        movement_direction = RIGHT;
    }
    if (((THE_RUNNERS_FIRST_POS_Y + enemie_path[current_house[Y] + 2]*BACKGROUND_SQUARE_LENGHT) > position[Y]) && (enemie_path[current_house[X] + 2] == enemie_path[current_house[X]]))
    {
        position[Y] += speed;
        movement_direction = DOWN;
    }
    if (((THE_RUNNERS_FIRST_POS_X + enemie_path[current_house[X] + 2]*BACKGROUND_SQUARE_LENGHT) < position[X]) && (enemie_path[current_house[Y] + 2] == enemie_path[current_house[Y]]))
    {
        position[X] -= speed;
        movement_direction = LEFT;
    }
    if (((THE_RUNNERS_FIRST_POS_Y + enemie_path[current_house[Y] + 2]*BACKGROUND_SQUARE_LENGHT) < position[Y]) && (enemie_path[current_house[X] + 2] == enemie_path[current_house[X]]))
    {
        position[Y] -= speed;
        movement_direction = UP;
    }
}

void The_Runners::update_current_position()
{
    if ((fabs((THE_RUNNERS_FIRST_POS_X + enemie_path[current_house[X] + 2]*BACKGROUND_SQUARE_LENGHT) - position[X]) < speed) && (fabs((THE_RUNNERS_FIRST_POS_Y + enemie_path[current_house[Y] + 2]*BACKGROUND_SQUARE_LENGHT) - position[Y]) < speed))
    {
        current_house[X] += 2;
        current_house[Y] += 2;
    }
}

void The_Runners::check_reach_the_end_of_the_path()
{
    if (((current_house[X] + 2) > enemie_path.size() || (current_house[Y] + 2) > enemie_path.size()) && moving_status == MOVING)
        moving_status = NOT_MOVING;
}

void The_Runners::draw(Window* window)
{
    if (health > 0 && moving_status == MOVING)
    {
        draw_image(window);
        window->draw_rect(Rectangle(position[X]- 5, position[Y] - 3, float(health)/float(initial_health)*float(HEALTH_TAPE_LENGHT) , 4), RED);
    }
}

void The_Runners::draw_image(Window* window)
{
    string num = convert_number_to_string(image_count/THE_RUNNERS_REPEAT_THE_IMAGE);
    if (movement_direction == UP)
        window->draw_img(THE_RUNNERS_IMAGE_FILE_ADDRESS_UP + num + PNG,Rectangle( position[X], position[Y], THE_RUNNERS_IMAGE_WIDTH, THE_RUNNERS_IMAGE_HEIGHT));
    if (movement_direction == DOWN)
        window->draw_img(THE_RUNNERS_IMAGE_FILE_ADDRESS_DOWN + num + PNG,Rectangle( position[X], position[Y], THE_RUNNERS_IMAGE_WIDTH, THE_RUNNERS_IMAGE_HEIGHT));
    if (movement_direction == RIGHT)
        window->draw_img(THE_RUNNERS_IMAGE_FILE_ADDRESS_RIGHT + num + PNG,Rectangle( position[X], position[Y], THE_RUNNERS_IMAGE_WIDTH, THE_RUNNERS_IMAGE_HEIGHT));
    if (movement_direction == LEFT)
        window->draw_img(THE_RUNNERS_IMAGE_FILE_ADDRESS_RIGHT + num + PNG,Rectangle( position[X], position[Y], THE_RUNNERS_IMAGE_WIDTH, THE_RUNNERS_IMAGE_HEIGHT), NULL_RECT,0,true);
    image_count++;
    if(image_count > THE_RUNNERS_ALL_IMAGE_REPEATED)
        image_count = 0;
}

string The_Runners::convert_number_to_string(int number)
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

float The_Runners::get_position_x() {return position[X];}
float The_Runners::get_position_y() {return position[Y];}

void The_Runners::reduce_health(int reduce_health_amount)
{
    if (health > 0)
        health -= reduce_health_amount;
}

void The_Runners::reduce_speed(float decrease_speed_amount, int decrease_speed_time)
{
    speed = speed*(float(1) - decrease_speed_amount);
    reduce_speed_size = decrease_speed_amount;
    reduce_speed_time = decrease_speed_time;
    reduce_speed_status = REDUCED;
    current_reduce_speed_time = 0;
}

int The_Runners::check_health()
{
    if(health <= 0 && status == ALIVE)
    {
        status = DEAD;
        return 1;
    }
    else
        return 0;
}

int The_Runners::check_not_being_killed()
{
    if(moving_status == NOT_MOVING && status == ALIVE)
    {
        moving_status = NOT_MOVING_COUNTED;
        status = DEAD;
        return 1;
    }
    else
        return 0;
}

int The_Runners::get_status() {return status;}
int The_Runners::get_moving_status() {return moving_status;}
int The_Runners::get_reduce_speed_status() {return reduce_speed_status;}