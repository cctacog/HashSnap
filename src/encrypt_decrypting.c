/*
Sophia Garcia
01-31-2023
*/

#include "encrypt_decrypt.h"

The_Round crypt(const The_Round terms_)
{
    //prints title of program
    printf("\nENCRYPTION!\n\n\n");

    /*
        to keep is simple
        no malloc 
        no leaking memorey
    */
    The_Round terms;
    char prev_use[MAX];
    printf("Would you like to use the previous code & key? [ex: no]: ");
    gets(prev_use);

    if(prev_use[0] == 'y' || prev_use[0] == 'Y')
    {       
        transfer(terms_, &terms);
        empty_q(&terms);
        empty_s(&terms);         
    } 
    else
    {
        printf("Enter code: ");
        gets(terms.code);
        terms.code_len = strlen(terms.code);
        printf("Enter key: ");
        gets(terms.key);  
        def_values_q(&terms.queue);
        def_values_s(&terms.stack);
    }

    /*
    encrypts each array location of secret (equal to the lengths of the code/key)
    from the operation of the code and key at the said array location
    */

    char operate[MAX];
    printf("\n\nWhat operation(s) would you like to use?\n1.AND\n2. OR\n3. NAND\n4. NOR\n5. XOR\n6. XNOR\nOperator(s) [ex: 5231 or 2]: ");
    gets(operate);
    enum Operator op;
    for(int i = 0; i < 20 && operate[i] != '\0'; ++i)
    {
        switch(operate[0])
        {
            case '1':
                op = AND;            
                break;
            case '2':
                op = OR;
                break;
            case '3':
                op = NAND;
                break;
            case '4':
                op = NOR;
                break;        
            case '5':
                op = XOR;
                break;
            case '6':
                op = XNOR;
                break;
            //terms.queue        
        }
        insert(&(terms.queue), op);
        push(&(terms.stack), op);
    }    

    secret_thru_queue(&terms);
    //print final product
    printf("\nThe secret after encrypting: ");

    for(int z = 0; z < terms.code_len; z++)
    {
        int num = terms.secret[z];
        if(num < 0)
            printf("%c", num);
        else printf("%c", alphabet(num));
    }

    secret_thru_stack(&terms);
    printf("\nThe secret after decrypting: ");

    for(int z = 0; z < terms.code_len; z++)
    {
        int num = terms.secret[z];
        if(num < 0)
            printf("%c", num);
        else printf("%c", alphabet(num));
    }

    char replay[MAX];

    printf("\n\nWould you care to play again?: [ex: yes]  ");
    gets(replay);

    if(replay[0] == 'y' || replay[0] == 'Y')
    {
        terms.play_again = 1;       
    }
    else
    {
        terms.play_again = 0;
    }

    // free(code);
    // free(key);
    // free(secret); only needed when using malloc 

    return terms;
}

