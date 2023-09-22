#include "crypt_helper.h"
/*
Sophia Garcia
01-31-2023
*/


void code_thru_array(The_Round *terms)
{
     
    for(int i = 0; i < 10; ++i)
    {
        terms->secret[i] = terms->code[i];
    }
    
    for(int q = 0; terms->ops_order[q] != NONE && q < 10; ++q)
    {                         
        enum Operator op = terms->ops_order[q]; 
        int iK = 0;                                 
        for(int i = 0; (i < terms->code_len) && i < 10; ++i)
        {
            /*
            because a character cannot xor itself the
            array location will equal the said character
            */
            // if(terms->code[i] == terms->key[iK] && (op == XOR || op == XNOR))
            // {           
            //     terms->secret[i] = terms->code[i];
            //     continue;
            // }
            printf("code: %i, key: %i", terms->secret[i], terms->key[iK]);                        
            terms->secret[i] = possibleActions(op, terms->secret[i], terms->key[iK]);            
            printf(", s: %i\n", terms->secret[i]);                        
            /*
            if terms->code about to end at the i+1 location
            then the code will end at i+1
            */
            ++iK;     
            //only for when characters involved       
            // if(terms->code[i+1] == '\0')
            //     terms->code[i+1] = '\0';
            // if(terms->key[iK] == '\0')
            //     iK = 0;
        }        
    }

}

void code_thru_stack(The_Round *terms)
{   
    for(int s = 0;!isEmpty_s(&(terms->stack)); ++s)
    {
        enum Operator op = pop(&(terms->stack));     
        int iK = 0;
        for(int i = 0; (i < terms->code_len) && (terms->code[i] != '\0') && op != NONE; ++i)
        {
            
            /*
            because a character cannot xor itself the
            array location will equal the said character
            */
            // if(terms->code[i] == terms->key[iK] && (op == XOR || op == XNOR))
            // {           
            //     terms->secret[i] = terms->code[i];
            //     continue;
            // }            

            terms->secret[i] = possibleActions(op, terms->secret[i], terms->key[iK]);            
            /*
            if terms->code about to end at the i+1 location
            then the code will end at i+1
            */
            iK++;
            //only for when characters involved       
            // if(terms->code[i+1] == '\0')
            //     terms->code[i+1] = '\0';
            // if(terms->key[iK] == '\0')
            //     iK = 0;
        }
    }
}


char* print_op(const enum Operator op)
{
    char *result;
    switch(op)
        {
            case AND:
                result = "AND";
                break;
            case OR:
                result = "OR";
                break;
            case NAND:
                result = "NAND";
                break;
            case NOR:
                result = "NOR";
                break;
            case XOR:
                result = "XOR";
                break;
            case XNOR:
                result = "XNOR";
                break;
            case NONE:
                result = "NONE";
                break;
            default:
                result = "nope";            
                break;
        }
     return result;
}

unsigned char possibleActions(enum Operator i, unsigned char c, unsigned char k)
{    
    unsigned int answ = 0;    
    switch(i)
    {
        case AND:
            answ = c & k;
            break;
        case OR:
            answ = c | k;
            break;
        case NAND:
            answ = ~(c & k);
            break;
        case NOR:
            answ = ~(c | k);
            break;
        case XOR:
            answ = c ^ k;
            break;
        case XNOR:
            answ = ~(c ^ k);
            break;
        case NONE:
            printf("oops");
            break;
        default:
            perror("Error by input");
            answ = 'f';
            break;
    }

    answ &= 1u;
    return answ;
}


char alphabet(int b)
{
    char alphabet[255];

    for(int i = 0; i < 255; i++)
    {
        alphabet[i] = i;
    }

    if(b >= 0)
    {
        return alphabet_print(alphabet, b);            
    }
    else
    {
        return alphabet_print_listed(alphabet);        
    }        
}

char alphabet_print_listed(char alphabet_[])
{
    char yn[10];
    printf("\n\nWould you like to see the C ascii alphabet?: [ex: yes] ");
    gets(yn);

    if(yn[0] == 'y' || yn[0] == 'Y')
        alphabet(-1);

    printf("\nHave a nice day!\n");
    const char non_printable[33][5] = {"NULL", "SOH", "STX", "ETX", "EOT", "ENQ", "ACK", 
    "BEL", "BS", "TAB", "LF", "VT", "FF", "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", 
    "NAK", "SYN", "CAN", "EM", "SUB", "ESC", "SUB", "ESC", "FS", "GS", "RS", "US", "SPACE" };
    char move;
    for(int i = 0; i < 255; i++)
    {
        printf("Ascii character of %i: ", i);
        if(i < 33)
        {
            printf(non_printable[i]);
        }
        else
        {
            printf("%c", alphabet_[i]);
        }
        if((i+1) % 2 == 0)
            move = '\n';
        else move = '\t';
        printf("%c", move);
    }       
    return move;
}

char alphabet_print(char alphabet[], int letter)
{
    return alphabet[letter];    
}
