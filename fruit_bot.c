// fruit_bot.c
// Assignment 3, COMP1511 18s1: Fruit Bot
//
// This program by Anthony Dang (z5207756) on 23/5/18
//
// Version 1.0.0: Assignment released.
// Version 1.0.1: minor bug in main fixed

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>

#include "fruit_bot.h"

void print_player_name(void);
void print_move(struct bot *b, int* choice, int* play);
void run_unit_tests(int argc, char *argv[]);

// ADD PROTOTYPES FOR YOUR FUNCTIONS HERE

int buy_fruit_distance(struct bot *b);
int sell_fruit_distance(struct bot *b);
int electricity_distance(struct bot *b);
int buy_fruit(struct bot *b);
int sell_fruit(struct bot *b);
int recharge_bot(struct bot *b);
int bot_count(struct bot *b);
char* print_function(struct bot *b);

// YOU SHOULD NOT NEED TO CHANGE THIS MAIN FUNCTION

int main(int argc, char *argv[]) {

    if (argc > 1) {
        // supply any command-line argument to run unit tests
        run_unit_tests(argc, argv);
        return 0;
    }

    int choice = -1;
    int play = -1;

    struct bot *me = fruit_bot_input(stdin);
    if (me == NULL) {
        print_player_name();
    } else {
        print_move(me, &choice, &play);
    }

    return 0;
}

void print_player_name(void) {
    // CHANGE THIS PRINTF TO YOUR DESIRED PLAYER NAME
    printf("wallah to allah cuz\n");

}

// print_move - should print a single line indicating
//              the move your bot wishes to make
//
// This line should contain only the word Move, Sell or Buy
// followed by a single integer

void print_move(struct bot *b, int* choice, int* play) {

    struct location *head = b->location;

    // play - number to move, buy or sell
    // choice: 0 - move, 1 - buy, 2 - sell

    int elecDist = 0;
    int buyDist = 0;
    int sellDist = 0;

    // always find distance to nearest electricity
    elecDist = electricity_distance(b);
    
    // find a seller if there is no fruit being held
    if (b->fruit_kg == 0 && b->battery_level >= (b->battery_capacity / 3)) {
        buyDist = buy_fruit_distance(b);
    }

    // find a buyer if there is a fruit being held
    if (b->fruit_kg != 0 && b->battery_level >= (b->battery_capacity / 3)) {
        sellDist = sell_fruit_distance(b);
    }

    if (b->turns_left < 3 && b->fruit_kg == 0) {
        *play = 1;
        *choice = 0;
    } else if (b->battery_level <= (b->battery_capacity / 3) && elecDist != 0) {
        *play = elecDist;
        *choice = 0;
    } else if (b->fruit_kg == 0 && buyDist != 0) {
        *play = buyDist;
        *choice = 0;
    } else if (b->fruit_kg != 0 && sellDist != 0) {
        *play = sellDist;
        *choice = 0;
    } else if (b->fruit_kg == 0 && head->price < 0 && buyDist == 0 
        && buy_fruit(b) != 0 && head->quantity > 0 && b->cash > head->price) {
        *play = buy_fruit(b);
        *choice = 1;
    } else if (b->fruit_kg != 0 && head->price > 0 && sellDist == 0
        && strcmp(b->fruit, head->fruit) == 0 && head->quantity > 0) {
        *play = sell_fruit(b);
        *choice = 2;
    } else if (strcmp(head->fruit, "Electricity") == 0 && head->price < 0
        && elecDist == 0 && head->quantity > 0 
        && b->battery_level != b->battery_capacity) {
        *play = recharge_bot(b);
        *choice = 1;
    } else {
        *play = 1;
        *choice = 0;
    }

    // print moves
    if (*choice == 0) {
        printf("Move %d\n", *play);
    } else if (*choice == 1) {
        printf("Buy %d\n", *play);
    } else {
        printf("Sell %d\n", *play);
    }

}

// ADD A COMMENT HERE EXPLAINING YOUR OVERALL TESTING STRATEGY

// Test the bot through a full game normally and see the moves that it takes
// Place the bot in different scenarios
// This includes making it move, buy and sell (worlds 1-8)
// Also moving to recharge if at a low battery level (world 11 and 12)
// And if turns are < 3 with fruit (world 9 and 10) and without fruit (world 13 and 14)
// choice 0 - move, 1 - buy, 2 - sell
// play - amount to move, buy or sell

void run_unit_tests(int argc, char *argv[]) {
    // PUT YOUR UNIT TESTS HERE
    // This is a difficult assignment to write unit tests for,
    // but make sure you describe your testing strategy above.

    FILE *testWorld1 = NULL;
    FILE *testWorld2 = NULL;
    FILE *testWorld3 = NULL;
    FILE *testWorld4 = NULL;
    FILE *testWorld5 = NULL;
    FILE *testWorld6 = NULL;
    FILE *testWorld7 = NULL;
    FILE *testWorld8 = NULL;
    FILE *testWorld9 = NULL;
    FILE *testWorld10 = NULL;
    FILE *testWorld11 = NULL;
    FILE *testWorld12 = NULL;
    FILE *testWorld13 = NULL;
    FILE *testWorld14 = NULL;
    FILE *testWorld15 = NULL;
    FILE *testWorld16 = NULL;

    int i = 0;

    while (i < argc) {
        
        if (strcmp(argv[i], "world1.txt") == 0) {
            testWorld1 = fopen(argv[i], "r");
        } else if (strcmp(argv[i], "world2.txt") == 0) {
            testWorld2 = fopen(argv[i], "r");
        } else if (strcmp(argv[i], "world3.txt") == 0) {
            testWorld3 = fopen(argv[i], "r");
        } else if (strcmp(argv[i], "world4.txt") == 0) {
            testWorld4 = fopen(argv[i], "r");
        } else if (strcmp(argv[i], "world5.txt") == 0) {
            testWorld5 = fopen(argv[i], "r");
        } else if (strcmp(argv[i], "world6.txt") == 0) {
            testWorld6 = fopen(argv[i], "r");
        } else if (strcmp(argv[i], "world7.txt") == 0) {
            testWorld7 = fopen(argv[i], "r");
        } else if (strcmp(argv[i], "world8.txt") == 0) {
            testWorld8 = fopen(argv[i], "r");
        } else if (strcmp(argv[i], "world9.txt") == 0) {
            testWorld9 = fopen(argv[i], "r");
        } else if (strcmp(argv[i], "world10.txt") == 0) {
            testWorld10 = fopen(argv[i], "r");
        } else if (strcmp(argv[i], "world11.txt") == 0) {
            testWorld11 = fopen(argv[i], "r");
        } else if (strcmp(argv[i], "world12.txt") == 0) {
            testWorld12 = fopen(argv[i], "r");
        } else if (strcmp(argv[i], "world13.txt") == 0) {
            testWorld13 = fopen(argv[i], "r");
        } else if (strcmp(argv[i], "world14.txt") == 0) {
            testWorld14 = fopen(argv[i], "r");
        }

        i++;
    }

    int choice = -1;
    int play = -1;

    if (testWorld1 != NULL) {
        struct bot *test1 = fruit_bot_input(testWorld1);
        choice = -1;
        play = -1;
        print_move(test1, &choice, &play);
        assert(choice == 0);
        assert(play == -3);
        fclose(testWorld1);
    } else if (testWorld2 != NULL) {
        struct bot *test2 = fruit_bot_input(testWorld2);
        choice = -1;
        play = -1;
        print_move(test2, &choice, &play);
        assert(choice == 1);
        assert(play == 29);
        fclose(testWorld2);   
    } else if (testWorld3 != NULL) {
        struct bot *test3 = fruit_bot_input(testWorld3);
        choice = -1;
        play = -1;
        print_move(test3, &choice, &play);
        assert(choice == 0);
        assert(play == -1);
        fclose(testWorld3);        
    } else if (testWorld4 != NULL) {
        struct bot *test4 = fruit_bot_input(testWorld4);
        choice = -1;
        play = -1;
        print_move(test4, &choice, &play);
        assert(choice == 2);
        assert(play == 5);
        fclose(testWorld4);        
    } else if (testWorld5 != NULL) {
        struct bot *test5 = fruit_bot_input(testWorld5);
        choice = -1;
        play = -1;
        print_move(test5, &choice, &play);
        assert(choice == 0);
        assert(play == 1);
        fclose(testWorld5);        
    } else if (testWorld6 != NULL) {
        struct bot *test6 = fruit_bot_input(testWorld6);
        choice = -1;
        play = -1;
        print_move(test6, &choice, &play);
        assert(choice == 1);
        assert(play == 24);
        fclose(testWorld6);        
    } else if (testWorld7 != NULL) {
        struct bot *test7 = fruit_bot_input(testWorld7);
        choice = -1;
        play = -1;
        print_move(test7, &choice, &play);
        assert(choice == 0);
        assert(play == -1);
        fclose(testWorld7);        
    } else if (testWorld8 != NULL) {
        struct bot *test8 = fruit_bot_input(testWorld8);
        choice = -1;
        play = -1;
        print_move(test8, &choice, &play);
        assert(choice == 2);
        assert(play == 7);
        fclose(testWorld8);        
    } else if (testWorld9 != NULL) {
        struct bot *test9 = fruit_bot_input(testWorld9);
        choice = -1;
        play = -1;
        print_move(test9, &choice, &play);
        assert(choice == 0);
        assert(play == 2);
        fclose(testWorld9);        
    } else if (testWorld10 != NULL) {
        struct bot *test10 = fruit_bot_input(testWorld10);
        choice = -1;
        play = -1;
        print_move(test10, &choice, &play);
        assert(choice == 2);
        assert(play == 9);
        fclose(testWorld10);        
    } else if (testWorld11 != NULL) {
        struct bot *test11 = fruit_bot_input(testWorld11);
        choice = -1;
        play = -1;
        print_move(test11, &choice, &play);
        assert(choice == 0);
        assert(play == -1);
        fclose(testWorld11);        
    } else if (testWorld12 != NULL) {
        struct bot *test12 = fruit_bot_input(testWorld12);
        choice = -1;
        play = -1;
        print_move(test12, &choice, &play);
        assert(choice == 1);
        assert(play == 14);
        fclose(testWorld12);        
    } else if (testWorld13 != NULL) {
        struct bot *test13 = fruit_bot_input(testWorld13);
        choice = -1;
        play = -1;
        print_move(test13, &choice, &play);
        assert(choice == 0);
        assert(play == 1);
        fclose(testWorld13);        
    } else if (testWorld14 != NULL) {
        struct bot *test14 = fruit_bot_input(testWorld14);
        choice = -1;
        play = -1;
        print_move(test14, &choice, &play);
        assert(choice == 0);
        assert(play == 1);
        fclose(testWorld14);        
    }

}

int bot_count(struct bot *b) {

    struct bot_list *curr = b->location->bots;
    int botCount = 0;

    while (curr != NULL) {
        botCount++;
        curr = curr->next;
    }

    return botCount;
}

// recharge the bot to battery capacity
int recharge_bot(struct bot *b) {

    struct location *head = b->location;

    int quantity = b->battery_capacity - b->battery_level;

    return quantity;
}

// buy quantity of fruit which matches the quantity of a buyer of the same fruit
int buy_fruit(struct bot *b) {

    struct location *head = b->location;
    struct location *curr_east = NULL;
    struct location *curr_west = NULL;

    int quantity = 0;

    int numBots = bot_count(b);

    if (head->quantity / numBots > 0) {
        while (curr_east != head && curr_west != head) {

            if (curr_east == NULL && curr_west == NULL) {
                curr_east = head;
                curr_west = head;
            }

            if (strcmp(head->fruit, curr_east->fruit) == 0 && curr_east->price > 0
                && curr_east->quantity > 0) {
                quantity = curr_east->quantity;
                break;
            } else if (strcmp(head->fruit, curr_west->fruit) == 0 && curr_west->price > 0
                && curr_west->quantity > 0) {
                quantity = curr_west->quantity;
                break;
            }

            curr_east = curr_east->east;
            curr_west = curr_west->west;
        }
        return quantity;
    } else if (head->quantity / numBots < 1) {
        return 0;
    }

    return 0;
}

// sell all fruit being held
int sell_fruit(struct bot *b) {

    int quantity = b->fruit_kg;

    return quantity;

}

// distance counter going east and west to find the nearest buyer of the same fruit
int sell_fruit_distance(struct bot *b) {

    struct location *head = b->location;
    struct location *curr_east = NULL;
    struct location *curr_west = NULL;
    int distance = 0;   

    if (strcmp(head->fruit, b->fruit) == 0 && head->quantity > 0 
        && head->price > 0) {
        return 0;
    }

    while (curr_east != head && curr_west != head) {
        
        if (curr_east == NULL && curr_west == NULL) {
            curr_east = head;
            curr_west = head;
        }

        if (strcmp(curr_east->fruit, b->fruit) == 0 && curr_east->quantity > 0
            && curr_east->price > 0) {
            return distance;
        } else if (strcmp(curr_west->fruit, b->fruit) == 0 && curr_west->quantity > 0
            && curr_west->price > 0) {
            return -distance;
        }

        distance++;
        curr_east = curr_east->east;
        curr_west = curr_west->west;
        
    }

    return 0;
}

// distance counter going east and west to nearest fruit seller
int buy_fruit_distance(struct bot *b) {

    struct location *head = b->location;
    struct location *curr_east = NULL;
    struct location *curr_west = NULL;
    int distance = 0;

    if (strcmp(head->fruit, "Electricity") != 0 && head->quantity > 0
        && head->price < 0) {
        return 0;
    }

    while (curr_east != head && curr_west != head) {
        
        if (curr_east == NULL && curr_west == NULL) {
            curr_east = head;
            curr_west = head;
        }

        if (strcmp(curr_east->fruit, "Electricity") != 0 && curr_east->quantity > 0
            && curr_east->price < 0) {
            return distance;
        } else if (strcmp(curr_west->fruit, "Electricity") != 0 && curr_west->quantity > 0
            && curr_west->price < 0) {
            return -distance;
        }

        distance++;
        curr_east = curr_east->east;
        curr_west = curr_west->west;
        
    }

    return 0;
}

// distance counter going east and west to nearest electricity seller
int electricity_distance(struct bot *b) {
    
    struct location *head = b->location;
    struct location *curr_east = NULL;
    struct location *curr_west = NULL;

    int distance = 0;

    if (strcmp(head->fruit, "Electricity") == 0 && head->quantity > 0) {
        return 0;
    }

    while (curr_east != head && curr_west != head) {
        
        if (curr_east == NULL && curr_west == NULL) {
            curr_east = head;
            curr_west = head;
        }

        if (strcmp(curr_east->fruit, "Electricity") == 0 && curr_east->quantity > 0) {
            return distance;
        } else if (strcmp(curr_west->fruit, "Electricity") == 0 
            && curr_west->quantity > 0) {
            return -distance;
        }

        distance++;
        curr_east = curr_east->east;
        curr_west = curr_west->west;
    }

    return 0;
}
