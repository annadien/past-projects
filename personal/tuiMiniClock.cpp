
 /********
 * 
 * TUI Clock Display
 * 
 * May 2024
 * github annadien
 * 
 * Displays TUI clockface for user input hour and minute values. 
 * Modified tuiClock to smaller dimensions.
 * 
 *********/

 #include <iostream>

void clockdisplay()
{
    //initialize time
    int hr = 0;
    int min = 0;
    
    //=== USER INPUT TIME ===
    std::cout <<"Hour: ";
    std::cin>>hr;
    std::cout<<"Minute: ";
    std::cin>>min; 
    
    //=== TIME CONVERSION ===
    hr = (hr+min/60) % 12;
    min = min % 60;
    
    int hour = hr;
    std::cout<<"DISPLAYING TIME: "<<hr<<":";
    if (min<10){
        std::cout<<"0";
    }
    std::cout<<min<<"\n";
    
    int minute = min * 0.2; 
    if((minute*10+5)<(min*2)) //fix minute floor rounding
    {
        minute++;
    }
    
    if (minute>5) //accuracy for hour hand
    {
        hour++;
    }
    
    hour = hour % 12; //hour tick
    minute = minute % 12; //minute tick
    
    //=== DISPLAY INITS ===
    char hand[13] = "|/,-`\\|/,-`\\"; //clock hand characters

    char grid[15][7] = {0}; //15x7 grid display   
    
    //clock hands relative positions
    int positions[12][2] = 
        {{1,0},{2,0},{4,0}, //12 1 2
         {3,1},{4,2},{2,2}, //3 4 5
         {1,2},{0,2},{0,1}, //6 7 8
         {-1,1},{0,1},{0,0}  //9 10 11
        };  
    //positions grid corner 2,6
    int i=7;
    int j=2;  
    
    //tick starters
    int leftTick = 12;
    int rightTick = 0;
    int inc = 8;

    //=== FILL ALL INDICES ===
    for (int y=0;y<7;y++)
    {
        //ticks reset to unprinted before start of every line
        bool Lprinted = 0;
        bool Rprinted = 0;
        
        for(int x=1;x<=15;x++)
        {
            if((x==8)&&(y==3)) //if centre clock nose
            {
                grid[x][y] = '+';
                x++;
            }
            //=== LEFT TICKS ===
            else if (!Lprinted)
            {                 
                if ((x%inc)==0) //at incremented spacing
                {
                    if ((leftTick/10)>=1) //shift index for double digit
                    {
                        grid[x][y] = '0' +  (leftTick/10);
                        x++;
                    }
                    grid[x][y] = '0' + (leftTick%10); //print left tick
                    leftTick--; //update tick
                    Lprinted = 1;
                    x++; //shift index
                }
            }
            //=== HAND DISPLAY ===
            //indices for hands to point to each tick
            int mx = i+positions[minute][0];
            int my = j+positions[minute][1];
            int hx = i+positions[hour][0];
            int hy = j+positions[hour][1];

            if ( (x==hx) && (y==hy) ) //hours hand
            {
                grid[x][y] = hand[hour];
            }
            else if ( (x==mx) && (y==my) ) //minutes hand
            {
                grid[x][y] = hand[minute];
            }
            //=== RIGHT TICKS ===
            else if ((!Rprinted)&&((x+inc)>15)) //on last increment of the line 
            {
                if((y==0)||(y==6)) //dont print extra tick on 0 and 6
                {
                    grid[x][y] = '.';
                    rightTick++; //update tick
                }
                else
                {
                    grid[x][y] = '0' +  rightTick; //print right tick
                    rightTick++;
                }
                Rprinted = 1;
            }
            //=== SPACE ===
            else if (Lprinted&&(!Rprinted)) //fill clock with empty space
            {
                grid[x][y] = ' ';
            }
            else
            {
                grid[x][y] = '.'; //fill outside clock with ....
            }
        }

        if (y<3) //swap increments after middle
        {
            inc-=2;
        }
        else
        {
            inc+=2;    
        }
    }

    //=== PRINT CLOCK DISPLAY ===
    for (int y=0;y<7;y++)
    {
        for(int x=1;x<=15;x++)
        {
            std::cout<<grid[x][y];
        }
        std::cout <<"\n";
    }
}

int main()
{   
    char userinput;
    do
    {
        userinput=0;
        clockdisplay();
        std::cout <<"GO AGAIN? Y/N: ";
        std::cin>>userinput;
    }
    while((userinput=='y')||(userinput=='Y'));
    
    return 0;
}