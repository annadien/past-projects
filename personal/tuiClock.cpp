
 /********
 * 
 * TUI Clock Display
 * 
 * May 2024
 * 
 * github annadien
 * 
 * 
 * 
 */
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
    char hand[13] = "|/,-`\\|/,-~\\"; //clock hand characters

    char grid[25][13] = {0}; //25x13 grid display   
    
    //clock hands relative positions
    int positions[12][2] = 
        {{4,0},{6,0},{7,1}, //12 1 2
         {8,2},{8,3},{6,4}, //3 4 5
         {4,4},{2,4},{1,3}, //6 7 8
         {0,2},{1,1},{2,0}  //9 10 11
        };  
    //positions grid corner 4,9
    int i=9;
    int j=4;  
    
    //tick starters
    int leftTick = 12;
    int rightTick = 0;
    int inc = 13;

    //=== FILL ALL INDICES ===
    for (int y=0;y<13;y++)
    {
        //ticks reset to unprinted before start of every line
        bool Lprinted = 0;
        bool Rprinted = 0;
        
        for(int x=1;x<=25;x++)
        {
            if((x==13)&&(y==6)) //if centre clock nose
            {
                grid[x][y] = '*';
                x++;
            }
            //=== LEFT TICKS ===
            else if (!Lprinted)
            {                 
                if ((x%inc)==0) //at incremented spacing
                {
                    if ((y%2)==0) //even lines
                    {
                        if ((leftTick/10)>=1) //shift index for double digit
                        {
                            grid[x][y] = '0' +  (leftTick/10);
                            x++;
                        }
                        grid[x][y] = '0' + (leftTick%10); //print left tick
                        leftTick--; //update tick
                    } 
                    else
                    {
                        grid[x][y] = '}'; //odd lines tick
                    }
                    
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
                grid[x][y] = 'H';

                if((hy==my)&&(hx==mx)) //if arms aligned 
                {
                    grid[x+1][y] = 'M';
                    x++;
                }                    
            }
            else if ( (x==mx) && (y==my) ) //minutes hand
            {
                grid[x][y] = 'M';
            }
            //=== ARMS ===
            else if ( (x==((mx-i)/3+3+i)) && (y==((my-j)/2+1+j)) ) //M arm
            {
                grid[x][y] = hand[minute];
            }
            else if ( (x==((hx-i)/3+3+i)) && (y==((hy-j)/2+1+j)) ) //H arm
            {
                grid[x][y] = hand[hour];
            }
            //=== RIGHT TICKS ===
            else if ((!Rprinted)&&((x+inc)>25)) //on last increment of the line 
            {
                if((y==0)||(y==12)) //dont print extra tick on 0 and 6
                {
                    grid[x][y] = '.';
                    rightTick++; //update tick
                }
                else if ((y%2)==0) //even lines
                {
                    grid[x][y] = '0' +  rightTick; //print right tick
                    rightTick++;
                } 
                else
                {
                    grid[x][y] = '{'; //odd lines tick
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

        if (y<6) //swap increments after middle
        {
            inc-=2;
        }
        else
        {
            inc+=2;    
        }
    }

    //=== PRINT CLOCK DISPLAY ===
    for (int y=0;y<13;y++)
    {
        for(int x=1;x<=25;x++)
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
