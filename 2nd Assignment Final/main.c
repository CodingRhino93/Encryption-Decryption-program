//Program made by: Jakub Zareba, 2019
//A program to compare user input to access code and determine if it's correct
//IDE used: Clion with CygWin compiler

#include <stdio.h>
#define SIZE 4

//Prototypes
void Encrypt(int[]);
void Decrypt(int[]);
int User_Input(int[], int*);
int Verify(int[], int[]);

int main() {

    //Declaring and initializing variables
    int option, unlocked, equal_codes, encrypted, reset_encrypted, successful_attempts, unsuccessful_attempts;
    unlocked = 0;
    encrypted = 0;
    reset_encrypted = 0;
    successful_attempts = 0;
    unsuccessful_attempts = 0;

    int user_code[SIZE];

    //Declaring access code, giving it a fixed value and encrypting straight away
    int access_code[SIZE] = {1, 2, 3, 4};
    Encrypt(access_code);

    //do while loop to display menu
    do
    {
        //resetting variables each iteration
        option = 0;

        //A menu to choose an option along with scanf
        printf("\n\n1. Enter code.\n");
        printf("2. Encrypt code and verify.\n");
        printf("3. Decrypt code.\n");
        printf("4. Display the number of times the code was entered.\n");
        printf("5. Exit program.\n");

        scanf("%d", &option);
        //buffer flush
        while(getchar() != '\n');

        switch(option)
        {
            default:
            {
                printf("Invalid option.");
                break;
            }

            case 5:
            {
                printf("Program closed.");
                break;
            }

            case 1:
            {
                reset_encrypted = User_Input(user_code, &unlocked);

                if(reset_encrypted == 1)
                {
                    encrypted = 0;
                }

                break;
            }

            case 2:
            {
                if(unlocked == 1)
                {
                    if(encrypted == 1)
                    {
                        printf("\nCode already encrypted.");
                    }

                    if(encrypted == 2)
                    {
                        printf("\nCode already encrypted. Still wrong code.");
                    }

                    if(encrypted == 0)
                    {
                        Encrypt(user_code);
                        equal_codes = Verify(user_code, access_code);

                        if(equal_codes == 1)
                        {
                            printf("\nCorrect Code entered.");
                            encrypted = 1;
                            successful_attempts++;
                        }

                        else
                        {
                            printf("\nWrong Code entered.");
                            encrypted = 2;
                            unsuccessful_attempts++;
                        }
                    }
                }

                else
                {
                    printf("\nYou need to enter the code first.");
                }

                break;
            }

            case 3:
            {
                if(unlocked == 1)
                {
                    if(encrypted != 0)
                    {
                        printf("\nCode decrypted.");
                        Decrypt(user_code);
                        encrypted = 0;
                    }

                    else
                    {
                        printf("\nThe code must be encrypted first.");
                    }

                }

                else
                {
                    printf("\nYou need to enter the code first.");
                }

                break;
            }

            case 4:
            {
                printf("\nThe code was entered %d times.\n", (unsuccessful_attempts + successful_attempts));
                printf("Successful attempts: %d\n", successful_attempts);
                printf("Unsuccessful attempts: %d", unsuccessful_attempts);

                break;
            }
        }

    }//end do
    while(option != 5);


    return 0;
}//end main

int User_Input(int array[], int *unlocked) {

    //declaring and initializing local variables
    int i, proper_input, validate;
    proper_input = 0;
    validate = 0;

    int code[SIZE];

    printf("\nEnter the code: ");

    //a loop to read in user input
    for(i = 0; i < SIZE; i++)
    {
        if( scanf("%1d", &*(code + i)) == 1)
        {
            validate++;
        }
    }

    //checking if code is 4 digits long and flushing the buffer
    if(getchar() != '\n')
    {
        printf("\nCode can contain only numbers and must be 4 digits long.");
        while(getchar() != '\n');
        return 0;
    }

    //these variables must be incremented, otherwise the program will not save the user input and/or unlock option 2&3
    if(validate == SIZE)
    {
        proper_input++;
        *unlocked = 1;
    }

    //a loop to save the user input into the parameter array
    if(proper_input == 1)
    {
        printf("\nCode saved.");

        for(i = 0; i < SIZE; i++)
        {
            *(array + i) = *(code + i);
        }

        return 1;
    }

}//end User_Input function

int Verify(int user_code[], int access_code[]) {

    //declaring and initializing variables
    int i, is_equal, codes_are_equal;
    is_equal = 0;

    //a loop to compare user input to the access code
    for(i = 0; i < SIZE; i++)
    {
        if( *(user_code + i) == *(access_code + i))
        {
            is_equal++;
        }
    }

    if(is_equal == SIZE)
    {
        codes_are_equal = 1;
    }

    else
    {
        codes_are_equal = 0;
    }

    return codes_are_equal;

}//end Verify function

void Encrypt(int array[]) {

    int i, temp;

    //Swapping the values within the array
    temp = *(array + 0);
    *(array + 0) = *(array + 2);
    *(array + 2) = temp;
    temp = *(array + 1);
    *(array + 1) = *(array + 3);
    *(array + 3) = temp;

    //a loop to add 1 to each value
    for(i = 0; i < SIZE; i++)
    {
        *(array + i) = *(array + i) + 1;
    }

    //a loop to check if the value is 10 and if so, reset it to 0
    for(i = 0; i < SIZE; i++)
    {
        if(*(array + i) == 10)
        {
            *(array + i) = 0;
        }
    }

}//end Encrypt function

void Decrypt(int array[]) {

    int i, temp;

    //a loop that substracts 1 from each value
    for(i = 0; i < SIZE; i++)
    {
        *(array + i) = *(array + i) - 1;
    }

    //a loop that checks if there is any value equal to -1 and changes it to 9
    for(i = 0; i < SIZE; i++)
    {
        if(*(array + i) == -1)
        {
            *(array + i) = 9;
        }
    }

    //swapping the values inside the array
    temp = *(array + 0);
    *(array + 0) = *(array + 2);
    *(array + 2) = temp;
    temp = *(array + 1);
    *(array + 1) = *(array + 3);
    *(array + 3) = temp;

}//end Decrypt function

