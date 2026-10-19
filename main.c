#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdlib.h>
#include <time.h>

struct ChoiceEmoji
{
    const char *choice;
    const char *emoji;
};

void welcome_user()
{
    printf("========================================\n");
    printf("  Welcome to Rock, Paper, Scissors! 🎮  \n");
    printf("========================================\n");
}

void get_user_input(char *out, char *valid_choices[], int size)
{
    while (true)
    {
        printf("Enter rock, paper, or scissors (or r/p/s): ");
        scanf("%s", out);

        for (int i = 0; out[i]; i++)
        {
            out[i] = tolower(out[i]);
        }

        if (strcmp(out, "r") == 0)
        {
            strcpy(out, "rock");
        }
        else if (strcmp(out, "p") == 0)
        {
            strcpy(out, "paper");
        }
        else if (strcmp(out, "s") == 0)
        {
            strcpy(out, "scissors");
        }

        bool is_valid_choice = false;

        for (int i = 0; i < 3; i++)
        {
            if (strcmp(out, valid_choices[i]) == 0)
            {
                is_valid_choice = true;
                break;
            }
        }

        if (is_valid_choice)
        {
            break;
        }
        printf("Oops! That's not a valid move. Please try again.\n");
    }
}

char *get_computer_choice(char *valid_choices[], int size)
{
    return valid_choices[rand() % size];
}

char *determine_winner(char *user_choice, char *computer_choice)
{
    if (strcmp(user_choice, computer_choice) == 0)
    {
        return "Draw!";
    }
    else if (strcmp(user_choice, "rock") == 0 && strcmp(computer_choice, "scissors") == 0)
    {
        return "You win!";
    }
    else if (strcmp(user_choice, "scissors") == 0 && strcmp(computer_choice, "paper") == 0)
    {
        return "You win!";
    }
    else if (strcmp(user_choice, "paper") == 0 && strcmp(computer_choice, "rock") == 0)
    {
        return "You win!";
    }
    else
    {
        return "You lose!";
    }
}

char *get_emoji(char *choice, struct ChoiceEmoji emoji_map[], int size){
    for (int i = 0; i < size; i++)
    {
        if (strcmp(choice, emoji_map[i].choice) == 0)
        {
            return (char *)emoji_map[i].emoji;
        }
    }
    return "";
}

int main()
{
    srand(time(NULL));

    welcome_user();
    char *valid_choices[] = {"rock", "paper", "scissors"};
    int player_score = 0;
    int computer_score = 0;
    int max_rounds = 0;
    char tiebreaker_pref[10];

    struct ChoiceEmoji EMOJI_MAP[] = {
        {"rock", "✊"},
        {"paper", "👋"},
        {"scissors", "✌️"}};

    printf("How many rounds would you like to play? ");
    scanf("%d", &max_rounds);

    printf("Do you want to enable Sudden Death Tie-breaker for ties? (y/n): ");
    scanf(" %s", tiebreaker_pref);

    for (int i = 0; tiebreaker_pref[i]; i++)
    {
        tiebreaker_pref[i] = tolower(tiebreaker_pref[i]);
    }
    
    bool enable_tiebreaker = (strcmp(tiebreaker_pref, "y") == 0 || strcmp(tiebreaker_pref, "yes") == 0);

    printf("\n--- Game Started! Total Rounds: %d ---\n", max_rounds);

    for (int current_round = 1; current_round <= max_rounds; current_round++)
    {
        printf("\n[ Round %d of %d ]\n", current_round, max_rounds);

        char user_choice[20];
        get_user_input(user_choice, valid_choices, 3);
        printf("You chose: %s (%s)\n", user_choice, get_emoji(user_choice, EMOJI_MAP, 3));

        char computer_choice[20];
        strcpy(computer_choice, get_computer_choice(valid_choices, 3));
        printf("Computer chose: %s (%s)\n", computer_choice, get_emoji(computer_choice, EMOJI_MAP, 3));

        char result[50];
        strcpy(result, determine_winner(user_choice, computer_choice));
        printf("%s\n", result);

        if (strcmp(result, "You win!") == 0)
        {
            player_score++;
        }
        else if (strcmp(result, "You lose!") == 0)
        {
            computer_score++;
        }

        printf("Current Score -> You: %d | Computer: %d\n", player_score, computer_score);
    }

    printf("\n========================================\n");
    printf("             GAME OVER                  \n");
    printf("========================================\n");
    printf("Final Score -> Your score: %d | Computer score: %d\n", player_score, computer_score);

    if (player_score == computer_score && enable_tiebreaker)
    {
        printf("\nMatch is tied! Entering Sudden Death Tie-breaker automatically...\n");
        while (true)
        {
            char tb_user[20];
            get_user_input(tb_user, valid_choices, 3);
            printf("You chose: %s (%s)\n", tb_user, get_emoji(tb_user, EMOJI_MAP, 3));

            char tb_comp[20];
            strcpy(tb_comp, get_computer_choice(valid_choices, 3));
            printf("Computer chose: %s (%s)\n", tb_comp, get_emoji(tb_comp, EMOJI_MAP, 3));

            char tb_result[50];
            strcpy(tb_result, determine_winner(tb_user, tb_comp));
            printf("%s\n", tb_result);

            if (strcmp(tb_result, "You win!") == 0)
            {
                player_score++;
                printf("Tie-breaker Won by You! 🎉\n");
                break;
            }
            else if (strcmp(tb_result, "You lose!") == 0)
            {
                computer_score++;
                printf("Tie-breaker Won by Computer! 🤖\n");
                break;
            }
            else
            {
                printf("Still Draw! Moving to next sudden death move automatically...\n\n");
            }
        }
        
        printf("\nUpdated Score after Tie-breaker -> Your score: %d | Computer score: %d\n", player_score, computer_score);
    }

    if (player_score > computer_score)
    {
        printf("Overall Result: Congratulations! You won the game! 🎉\n");
    }
    else if (computer_score > player_score)
    {
        printf("Overall Result: Sorry, Computer won the game! 🤖\n");
    }
    else
    {
        printf("Overall Result: It's a tie game! 🤝\n");
    }

    printf("Thank you for playing!\n");

    return 0;
}
