#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MIN_RUN 1
#define MAX_RUN 6
#define BALLS 6

void PrintBorder(char symbol, int count);
int ReadInteger(const char *prompt);
int ReadRunGuess(int ball_number);
int GenerateComputerGuess(void);
int ChooseDifficulty(void);
int AskPlayAgain(void);
void PlayCricketGame(void);

int main(void)
{
    srand((unsigned)time(NULL));

    PrintBorder('=', 60);
    printf("WELCOME TO THE SIMPLE CRICKET GAME\n");
    PrintBorder('=', 60);
    printf("In this game, you score runs from %d to %d each ball.\n", MIN_RUN, MAX_RUN);
    printf("Avoid the computer guess or you'll be declared out.\n");
    printf("Win by reaching the target before your balls are finished.\n\n");

    do
    {
        PlayCricketGame();
    } while (AskPlayAgain());

    printf("\nThank you for playing!\n");
    return 0;
}

void PlayCricketGame(void)
{
    const int difficulty = ChooseDifficulty();
    const int target = (difficulty == 1) ? 24 : (difficulty == 3) ? 32 : 28;
    int score = 0;
    int ball_score[BALLS] = {0};

    PrintBorder('-', 60);
    printf("Game difficulty: %s\n",
           (difficulty == 1) ? "Easy" : (difficulty == 3) ? "Hard" : "Medium");
    printf("Target: %d runs in %d balls\n", target, BALLS);
    PrintBorder('-', 60);

    for (int ball = 1; ball <= BALLS; ball++)
    {
        printf("\nBall %d of %d. Runs needed: %d\n", ball, BALLS, target - score);
        int player_guess = ReadRunGuess(ball);
        int computer_guess = GenerateComputerGuess();

        printf("Computer guess: %d\n", computer_guess);

        if (player_guess == computer_guess)
        {
            printf("You're out on ball %d!\n", ball);
            break;
        }

        score += player_guess;
        ball_score[ball - 1] = player_guess;
        printf("You scored %d runs on ball %d. Total score: %d\n", player_guess, ball, score);

        if (score >= target)
        {
            printf("\nTarget reached!\n");
            break;
        }
    }

    PrintBorder('-', 60);
    printf("MATCH SUMMARY\n");
    PrintBorder('-', 60);
    for (int i = 0; i < BALLS; i++)
    {
        printf("Ball %2d: %d runs\n", i + 1, ball_score[i]);
    }
    printf("\nFinal score: %d / %d\n", score, target);

    if (score >= target)
    {
        printf("Result: Congratulations! You win.\n");
    }
    else
    {
        printf("Result: You lost. Better luck next time.\n");
    }
}

int ChooseDifficulty(void)
{
    printf("Choose difficulty:\n");
    printf(" 1. Easy  (Target 24 in %d balls)\n", BALLS);
    printf(" 2. Medium(Target 28 in %d balls)\n", BALLS);
    printf(" 3. Hard  (Target 32 in %d balls)\n", BALLS);

    int difficulty;
    do
    {
        difficulty = ReadInteger("Enter difficulty number (1-3): ");
        if (difficulty < 1 || difficulty > 3)
        {
            printf("Invalid choice. Please enter 1, 2, or 3.\n");
        }
    } while (difficulty < 1 || difficulty > 3);

    return difficulty;
}

int ReadInteger(const char *prompt)
{
    int value;
    int result;

    while (1)
    {
        printf("%s", prompt);
        result = scanf("%d", &value);
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF)
            ;

        if (result == 1)
        {
            return value;
        }

        printf("Invalid input. Please enter a valid integer.\n");
    }
}

int ReadRunGuess(int ball_number)
{
    int run;
    do
    {
        run = ReadInteger("Enter your run guess (1-6): ");
        if (run < MIN_RUN || run > MAX_RUN)
        {
            printf("Invalid run. Please choose a number between %d and %d.\n", MIN_RUN, MAX_RUN);
        }
    } while (run < MIN_RUN || run > MAX_RUN);

    return run;
}

int GenerateComputerGuess(void)
{
    return (rand() % (MAX_RUN - MIN_RUN + 1)) + MIN_RUN;
}

int AskPlayAgain(void)
{
    int choice = ReadInteger("\nPlay again? Enter 1 for yes or 0 for no: ");
    return (choice == 1);
}

void PrintBorder(char symbol, int count)
{
    for (int i = 0; i < count; i++)
    {
        putchar(symbol);
    }
    putchar('\n');
}
