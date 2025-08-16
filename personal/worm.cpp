
 /********
 * 
 * TUI Worm Explorer Display
 * 
 * June 2024
 * github annadien
 * 
 * Displays TUI to depict the dirt channels created by a worm whose movement is controlled by user input ASD.
 * 
 * 
 *********/

#include <iostream>

void placeWorm(int me)
{
    char ground[25] = {0};

    for (int i=0; i<25; i++)
    {
        if (i==me)
        {
            ground[i] = ' ';
        }
        else
        {
            ground[i] = '#';
        }
    }
    

    for (int i=0; i<25; i++)
    {
        std::cout<<ground[i];
    }        
    std::cout<<" >";

    return;
}

int updatePosition(int me)
{
    //Read character from input buffer
    char move = 0;
    std::cin.get(move);

    bool forward = 0;
    
    //Character movement
    if(move=='x')    //Exit button
    {
        return -1;
    }
    else if((move=='a')&&(me>0)) //Left step
    {
        me--;
        placeWorm(me);
    }
    else if((move=='d')&&(me<24)) //Right step
    {
        me++;
        placeWorm(me);
    }
    else if((move=='s')||(move=='a')||(move=='d'))
    {
        placeWorm(me);
    }
    
    //if (move!='\n')
    //{
    //    std::cout<<'\n';        
    //}

    return me;
}

int main()
{   
    int me = 25/2;
    int newline = 0;
    std::cout<< "use 'a, s, d' to move the worm. 'x' to exit  ";
    do
    {       
        me = updatePosition(me);
    }
    while(me>=0);
    
    return 0;
}