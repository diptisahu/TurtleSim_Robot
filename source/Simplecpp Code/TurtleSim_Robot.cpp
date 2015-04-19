#include <windows.h>
#include <simplecpp>
#include <time.h>
#include <fstream>
#include <string.h>

using namespace std; //includes standard library

HANDLE hPort = CreateFile("COM7", GENERIC_WRITE|GENERIC_READ, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
/*HANDLE: In windows programming, the windows maintains a table of all icons, ports, menus, etc, and each file has a
unique identifier through which it can be accessed. Windows is given the handle and it returns the port we want.or
communication */
DCB dcb; //DCB: A structure that defines the control setting for a serial communications device.

bool writebyte (char* data)
{
    DWORD byteswritten; //DWORD: DWORD is datatype used to represent 32-bit quantities in Windows.
    if (!GetCommState(hPort, &dcb)) //receives the status of COM port
    {
        cout<<"\n Serial port can't be opened";
        return false;
    }

    dcb.BaudRate = CBR_9600; //Sets Baudrate
    dcb.ByteSize = 8; //Sets ByteSize
    dcb.Parity = NOPARITY; //Sets Parity
    dcb.StopBits = ONESTOPBIT; //Sets no. of bits

    if (!SetCommState(hPort, &dcb)) //Sets the state of COM port
    return false;

    bool retVal = WriteFile(hPort, data, 1, &byteswritten, NULL); //Sends char by COM port
    return retVal;
}

//Function used for turning robot by specified degrees
void angle_rotate(unsigned int Degrees)
{
	wait(Degrees/125.0);
	char stop= 0x35;
	writebyte(&stop); //Stop robot
}

//Function used for moving robot forward by specified distance
void linear_distance_mm(unsigned int DistanceInMM)
{
	wait(DistanceInMM/17.3);
	char stop= 0x35;
	writebyte(&stop); //Stop robot
}

//Function used to move the bot forward
void forward()
{
    char forwrd=0x38;
    writebyte(&forwrd);
}

//Function to move the bot backward
void backward()
{
    char backwrd=0x32;
    writebyte(&backwrd);
}

//Function to rotate the bot right
void right()
{
    char rght=0x36;
    writebyte(&rght);
}

//Function to rotate the bot left
void left()
{
    char lft=0x34;
    writebyte(&lft);
}

//Function to draw a Circle taking radius as arguement
void circle(int arg)
{
    repeat(360)
    {
        forward();
        linear_distance_mm(arg*(3.14/180.0)); //arg*(3.14/180) is the arc length for 1 degree distance
        right();
        angle_rotate(1);
    }
}

//Function to draw rectangle taking length and width as arguements
void rectangle(int arg1, int arg2)
{
    repeat(2)
    {
        forward();
        linear_distance_mm(arg1);
        right();
        angle_rotate(90);
        forward();
        linear_distance_mm(arg2);
        right(90);
    }
}

//Function to lift the servo motor Up
void penup()
{
    char penup=0x30;
    writebyte(&penup);
}

//Function to bring down the servo motor
void pendown()
{
    char pendown=0x31;
    writebyte(&pendown);
}

//Function to call buzzer ON
void buzzerON()
{
    char buzzer_on=0x37;
    writebyte(&buzzer_on);
}

//Function to call buzzer OFF
void buzzerOFF()
{
    char buzzer_off=0x39;
    writebyte(&buzzer_off);
}

//Function to call an ERROR
void error()
{
    char Error=0x33;
    writebyte(&Error);
}

//Function to convert character to integer
int convert(char x)
{
    switch (x)
    {
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case '0': return 0;
        default: error();
                return 0;
    }
}

//Function to execute the statements within the repeat statement
void repet(string code,int number, int &i) //takes string"code", the number of times(number) it will be executed, and the position of pointer(i) as arguements
{
    int x=i; //stores the value of i at intial
    int inp[3]; //stores the arguement in integer format(only one digit)
    int num,num1; //stores the arguement in decimal format
    repeat(number)
    {
        i=x;
        while(1)
        {
        if (code.compare(i,9,"forward(-")==0) //compares the string to "forward(-"
        {
            if (code[i+10]==')') //retrives the position of ')' in the code
            {
            inp[2]=convert(code[i+9]);
            inp[0]=0;
            inp[1]=0;
            i=i+12;
            }
            else if (code[i+11]==')')
            {
            inp[1]=convert(code[i+9]);
            inp[2]=convert(code[i+10]);
            inp[0]=0;
            i=i+13;
            }
            else if (code[i+12]==')')
            {
                inp[0]=convert(code[i+9]);
                inp[1]=convert(code[i+10]);
                inp[2]=convert(code[i+11]);
                i=i+14;
            }
            if (code[i-1]==';');
            else { error(); break;} //calls error due to absence of ';'
            num=(inp[0]*100)+(inp[1]*10)+inp[2]; // stores the argeument in integer format
            backward();
            linear_distance_mm(num);
        }
        else if (code.compare(i,8,"forward(")==0) //compares the string to "forward("
        {
            if (code[i+9]==')') //retrives the position of ')' in the code
            {
                inp[2]=convert(code[i+8]);
                inp[0]=0;
                inp[1]=0;
                i=i+11;
            }
            else if (code[i+10]==')')
            {
                inp[1]=convert(code[i+8]);
                inp[2]=convert(code[i+9]);
                inp[0]=0;
                i=i+12;
            }
            else if (code[i+11]==')')
            {
                inp[0]=convert(code[i+8]);
                inp[1]=convert(code[i+9]);
                inp[2]=convert(code[i+10]);
                i=i+13;
            }
            if (code[i-1]==';');
            else { error(); break;} //calls error due to absence of ';'
            num=(inp[0]*100)+(inp[1]*10)+inp[2]; // stores the argeument in integer format
            forward();
            linear_distance_mm(num);
        }
        else if (code.compare(i,10,"Rectangle(")==0) //compares the string to "Rectangle("
        {
            if (code[i+12]==',') //retrives the position of ',' in the code
            {
                inp[2]=convert(code[i+10]);
                inp[0]=0;
                inp[1]=0;
                i=i+13;
            }
            else if (code[i+13]==',')
            {
                inp[1]=convert(code[i+10]);
                inp[2]=convert(code[i+11]);
                inp[0]=0;
                i=i+14;
            }
            else if (code[i+14]==',')
            {
                inp[0]=convert(code[i+10]);
                inp[1]=convert(code[i+11]);
                inp[2]=convert(code[i+12]);
                i=i+15;
            }
            num=(inp[0]*100)+(inp[1]*10)+inp[2]; // stores the argeument in integer format
            if (code[i+1]==')')
            {
                inp[2]=convert(code[i]);
                inp[0]=0;
                inp[1]=0;
                i=i+3;
            }
            else if (code[i+2]==')')
            {
                inp[1]=convert(code[i]);
                inp[2]=convert(code[i+1]);
                inp[0]=0;
                i=i+4;
            }
            else if (code[i+3]==')')
            {
                inp[0]=convert(code[i]);
                inp[1]=convert(code[i+1]);
                inp[2]=convert(code[i+2]);
                i=i+5;
            }
            if (code[i-1]==';');
            else { error(); break;} //calls error due to absence of ';'
            num1=(inp[0]*100)+(inp[1]*10)+inp[2]; // stores the argeument in integer format
            rectangle(num,num1);
        }
        else if (code.compare(i,7,"Circle(")==0) //compares the string to "Circle("
        {
            if (code[i+8]==')') //retrives the position of ')' in the code
            {
                inp[2]=convert(code[i+7]);
                inp[0]=0;
                inp[1]=0;
                i=i+10;
            }
            else if (code[i+9]==')')
            {
                inp[1]=convert(code[i+7]);
                inp[2]=convert(code[i+8]);
                inp[0]=0;
                i=i+11;
            }
            else if (code[i+10]==')')
            {
                inp[0]=convert(code[i+7]);
                inp[1]=convert(code[i+8]);
                inp[2]=convert(code[i+9]);
                i=i+12;
            }
            if (code[i-1]==';');
            else { error(); break;} //calls error due to absence of ';'
            num=(inp[0]*100)+(inp[1]*10)+inp[2]; // stores the argeument in integer format
            circle(num);
        }
        else if (code.compare(i,5,"left(")==0) //compares the string to "left("
        {
            if (code[i+6]==')') //retrives the position of ')' in the code
            {
                inp[2]=convert(code[i+5]);
                inp[0]=0;
                inp[1]=0;
                i=i+8;
            }
            else if (code[i+7]==')')
            {
                inp[1]=convert(code[i+5]);
                inp[2]=convert(code[i+6]);
                inp[0]=0;
                i=i+9;
            }
            else if (code[i+8]==')')
            {
                inp[0]=convert(code[i+5]);
                inp[1]=convert(code[i+6]);
                inp[2]=convert(code[i+7]);
                i=i+10;
            }
            if (code[i-1]==';');
            else { error(); break;} //calls error due to absence of ';'
            num=(inp[0]*100)+(inp[1]*10)+inp[2]; // stores the argeument in integer format
            left();
            angle_rotate(num);
        }
        else if (code.compare(i,6,"right(")==0) //compares the string to "right("
        {
            if (code[i+7]==')') //retrives the position of ')' in the code
            {
                inp[2]=convert(code[i+6]);
                inp[0]=0;
                inp[1]=0;
                i=i+9;
            }
            else if (code[i+8]==')')
            {
                inp[1]=convert(code[i+6]);
                inp[2]=convert(code[i+7]);
                inp[0]=0;
                i=i+10;
            }
            else if (code[i+9]==')')
            {
                inp[0]=convert(code[i+6]);
                inp[1]=convert(code[i+7]);
                inp[2]=convert(code[i+8]);
                i=i+11;
            }
            if (code[i-1]==';');
            else { error(); break;} //calls error due to absence of ';'
            num=(inp[0]*100)+(inp[1]*10)+inp[2]; // stores the argeument in integer format
            right();
            angle_rotate(num);
        }
        else if (code.compare(i,8, "penUp();")==0) //compares the string to "penUp();"
        {
            penup();
            i=i+8;
        }
        else if (code.compare(i,10, "penDown();")==0) //compares the string to "penDown();"
        {
            pendown();
            i=i+10;
        }
        else if (code.compare(i,7,"repeat(")==0) //compares the string to "repeat" and causes recursion
        {
            if (code[i+8]==')') //retrives the position of ')' in the code
            {
                inp[2]=convert(code[i+8]);
                inp[0]=0;
                inp[1]=0;
                i=i+10;
            }
            else if (code[i+9]==')')
            {
                inp[1]=convert(code[i+8]);
                inp[2]=convert(code[i+9]);
                inp[0]=0;
                i=i+11;
            }
            else if (code[i+10]==')')
            {
                inp[0]=convert(code[i+8]);
                inp[1]=convert(code[i+9]);
                inp[2]=convert(code[i+10]);
                i=i+12;
            }
            num=(inp[0]*100)+(inp[1]*10)+inp[2]; // stores the argeument in integer format
            repet(code,num,i); //recursion statement
        }
        else if (code[i]=='}') //compares the string to '}' to stop the code and break out of while loop
        {
            i++;
            break; //breaks from the while loop
        }
        else if (code.compare(i,2,"/*")==0) //compares the string to "/*" to negelect the comments
        {
            i=i+2;
            for( ;code.compare(i,2,"*/") != 0;i++); //neglects the comments
            i=i+2;
        }
        else
        {
            error(); //calls error
            break; //breaks from the while loop
        }
    }
    }
    i++;
}

//Main Function
int main(void)
{
    ifstream input("program.txt"); //reads the .txt file
    int length; //stores length of code
    char program[2000]; //stores the program in character arrray
    int i = 0; //i- shows the position of the char being read
    repeat(2000) //maximum 2000 charactes code
    {
        input >> program[i]; //takes input and stores it in program[i]
        if (program[i] == '\0')
            break;
        i++;
    }
    string code=program; //converts the character array to string
    length=code.length(); //stores the length of string
    int inp[3]; //stores only 1 digit of arguements
    int num,num1; //stores the arguement in decimal format
    if (code.compare(0,44,"#include<simplecpp>main_program{turtleSim();")==0) //compares the initial string with "...."
    {
        i=44; //sets the value of i=44
        buzzerON(); //sets buzzer ON
        wait(0.5); // wait for 0.5 second
        buzzerOFF(); //sets the buzzer OFF
        pendown(); //Initiaalizes by putting the pen down
        while(i<length-1) //continues to the last char of code
        {
            if (code.compare(i,9,"forward(-")==0) //compares the string to "forward(-"
            {
                if (code[i+10]==')') //retrives the position of ')' in the code
                {
                    inp[2]=convert(code[i+9]);
                    inp[0]=0;
                    inp[1]=0;
                    i=i+12;
                }
                else if (code[i+11]==')')
                {
                    inp[1]=convert(code[i+9]);
                    inp[2]=convert(code[i+10]);
                    inp[0]=0;
                    i=i+13;
                }
                else if (code[i+12]==')')
                {
                    inp[0]=convert(code[i+9]);
                    inp[1]=convert(code[i+10]);
                    inp[2]=convert(code[i+11]);
                    i=i+14;
                }
                if (code[i-1]==';');
                else { error(); break;} //calls error due to absence of ';'
                num=(inp[0]*100)+(inp[1]*10)+inp[2]; // stores the argeument in integer format
                backward();
                linear_distance_mm(num);
            }
            else if (code.compare(i,8,"forward(")==0) //compares the string to "forward("
            {
                if (code[i+9]==')') //retrives the position of ')' in the code
                {
                    inp[2]=convert(code[i+8]);
                    inp[0]=0;
                    inp[1]=0;
                    i=i+11;
                }
                else if (code[i+10]==')')
                {
                    inp[1]=convert(code[i+8]);
                    inp[2]=convert(code[i+9]);
                    inp[0]=0;
                    i=i+12;
                }
                else if (code[i+11]==')')
                {
                    inp[0]=convert(code[i+8]);
                    inp[1]=convert(code[i+9]);
                    inp[2]=convert(code[i+10]);
                    i=i+13;
                }
                if (code[i-1]==';');
                else { error(); break;} //calls error due to absence of ';'
                num=(inp[0]*100)+(inp[1]*10)+inp[2]; // stores the argeument in integer format
                forward();
                linear_distance_mm(num);
            }
            else if (code.compare(i,10,"Rectangle(")==0) //compares the string to "Rectangle("
            {
                if (code[i+12]==',') //retrives the position of ',' in the code
                {
                    inp[2]=convert(code[i+10]);
                    inp[0]=0;
                    inp[1]=0;
                    i=i+13;
                }
                else if (code[i+13]==',')
                {
                    inp[1]=convert(code[i+10]);
                    inp[2]=convert(code[i+11]);
                    inp[0]=0;
                    i=i+14;
                }
                else if (code[i+14]==',')
                {
                    inp[0]=convert(code[i+10]);
                    inp[1]=convert(code[i+11]);
                    inp[2]=convert(code[i+12]);
                    i=i+15;
                }
                num=(inp[0]*100)+(inp[1]*10)+inp[2]; // stores the argeument in integer format
                if (code[i+1]==')') //retrives the position of ')' in the code
                {
                    inp[2]=convert(code[i]);
                    inp[0]=0;
                    inp[1]=0;
                    i=i+3;
                }
                else if (code[i+2]==')')
                {
                    inp[1]=convert(code[i]);
                    inp[2]=convert(code[i+1]);
                    inp[0]=0;
                    i=i+4;
                }
                else if (code[i+3]==')')
                {
                    inp[0]=convert(code[i]);
                    inp[1]=convert(code[i+1]);
                    inp[2]=convert(code[i+2]);
                    i=i+5;
                }
                if (code[i-1]==';');
                else { error(); break;} //calls error due to absence of ';'
                num1=(inp[0]*100)+(inp[1]*10)+inp[2]; // stores the argeument in integer format
                rectangle(num,num1);
            }
            else if (code.compare(i,7,"Circle(")==0) //compares the string to "Circle("
            {
                if (code[i+8]==')') //retrives the position of ')' in the code
                {
                    inp[2]=convert(code[i+7]);
                    inp[0]=0;
                    inp[1]=0;
                    i=i+10;
                }
                else if (code[i+9]==')')
                {
                    inp[1]=convert(code[i+7]);
                    inp[2]=convert(code[i+8]);
                    inp[0]=0;
                    i=i+11;
                }
                else if (code[i+10]==')')
                {
                    inp[0]=convert(code[i+7]);
                    inp[1]=convert(code[i+8]);
                    inp[2]=convert(code[i+9]);
                    i=i+12;
                }
                if (code[i-1]==';');
                else { error(); break;} //calls error due to absence of ';'
                num=(inp[0]*100)+(inp[1]*10)+inp[2]; // stores the argeument in integer format
                circle(num);
            }
            else if (code.compare(i,5,"left(")==0) //compares the string to "left("
            {
                if (code[i+6]==')') //retrives the position of ')' in the code
                {
                    inp[2]=convert(code[i+5]);
                    inp[0]=0;
                    inp[1]=0;
                    i=i+8;
                }
                else if (code[i+7]==')')
                {
                    inp[1]=convert(code[i+5]);
                    inp[2]=convert(code[i+6]);
                    inp[0]=0;
                    i=i+9;
                }
                else if (code[i+8]==')')
                {
                    inp[0]=convert(code[i+5]);
                    inp[1]=convert(code[i+6]);
                    inp[2]=convert(code[i+7]);
                    i=i+10;
                }
                if (code[i-1]==';');
                else { error(); break;} //calls error due to absence of ';'
                num=(inp[0]*100)+(inp[1]*10)+inp[2]; // stores the argeument in integer format
                left();
                angle_rotate(num);
            }
            else if (code.compare(i,6,"right(")==0) //compares the string to "right("
            {
                if (code[i+7]==')') //retrives the position of ')' in the code
                {
                    inp[2]=convert(code[i+6]);
                    inp[0]=0;
                    inp[1]=0;
                    i=i+9;
                }
                else if (code[i+8]==')')
                {
                    inp[1]=convert(code[i+6]);
                    inp[2]=convert(code[i+7]);
                    inp[0]=0;
                    i=i+10;
                }
                else if (code[i+9]==')')
                {
                    inp[0]=convert(code[i+6]);
                    inp[1]=convert(code[i+7]);
                    inp[2]=convert(code[i+8]);
                    i=i+11;
                }
                if (code[i-1]==';');
                else { error(); break;} //calls error due to absence of ';'
                num=(inp[0]*100)+(inp[1]*10)+inp[2]; // stores the argeument in integer format
                right();
                angle_rotate(num);
            }
            else if (code.compare(i,8,"penUp();")==0) //compares the string to "penUp();"
            {
                penup();
                i=i+8;
            }
            else if (code.compare(i,10,"penDown();")==0) //compares the string to "penDown();"
            {
                pendown();
                i=i+10;
            }
            else if (code.compare(i,7,"repeat(")==0) //compares the string to "repeat("
            {
                if (code[i+8]==')') //retrives the position of ')' in the code
                {
                    inp[2]=convert(code[i+7]);
                    inp[0]=0;
                    inp[1]=0;
                    i=i+10;
                }
                else if (code[i+9]==')')
                {
                    inp[1]=convert(code[i+7]);
                    inp[2]=convert(code[i+8]);
                    inp[0]=0;
                    i=i+11;
                }
                else if (code[i+10]==')')
                {
                    inp[0]=convert(code[i+7]);
                    inp[1]=convert(code[i+8]);
                    inp[2]=convert(code[i+9]);
                    i=i+12;
                }
                num=(inp[0]*100)+(inp[1]*10)+inp[2]; // stores the argeument in integer format
                repet(code,num,i); //calls repet();
            }
            else if (code[i]=='}') //compares the string to '}' to stop the code and break out of while loop
            {
                i++;
                break;
            }
            else if (code.compare(i,2,"/*")==0) //compares the string to "/*" to negelect the comments
            {
                i=i+2;
                for( ;code.compare(i,2,"*/") != 0;i++); //neglects the comments
                i=i+2;
            }
            else
            {
                error(); //calls error
                break; //breaks from the while loop
            }
        }
    }
    else
    {
        error(); //calls error
    }

    buzzerON();
    wait(1);
    buzzerOFF();
    CloseHandle(hPort); //closes the COM port
}
//END

