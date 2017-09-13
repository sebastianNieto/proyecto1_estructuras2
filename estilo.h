/* Estilos de ubicacion, color y marco
*  Fecha 06/09/2017
*  Elaborado por: John Sebastian Nieto gil 
*  Elaborado por: Ricardo Andres Villalobos
*/

#define negro 0 
#define azul 1 
#define verde 2 
#define cyan 3 
#define rojo 4 
#define magenta 5 
#define marron 6 
#define grisclaro 7 
#define grisoscuro 8 
#define azulclaro 9 
#define verdeclaro 10 
#define cyanclaro 11 
#define rojoclaro 12 
#define magentaclaro 13 
#define amarillo 14 
#define blanco 15

void gotoxy(int x, int y);
void dibujaRectangulo(int superiorX, int superiorY, int inferiorX, int inferiorY, char marco);
void color(int n);

//Ubica la posición del cursor
void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

int wherex()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.X;
}
int wherey()
{
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    return csbi.dwCursorPosition.Y;
}


//Dibuja un marco en pantalla
void dibujaRectangulo(int superiorX, int superiorY, int inferiorX, int inferiorY, char marco = '\260')
{
	int x1,x2,i;
	x1=superiorX;
	x2=inferiorX;
	i = superiorX;
	for(i;i<=inferiorX;i++)
	{
		gotoxy(x1,superiorY);
		printf("%c", marco);
		gotoxy(x2,inferiorY);
		printf("%c", marco);
		x1++;
		x2--;
	}
	x1=superiorY;
	x2=inferiorY;
	i = superiorY;
	for(i;i<=inferiorY;i++)
	{
		gotoxy(superiorX,x1);
		printf("%c", marco);
		gotoxy(inferiorX,x2);
		printf("%c", marco);
		x1++;
		x2--;
	}
	
}

//Cambia el color de la letra
void color(int n)
{ 
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), n); 
} 

void limpiaPantalla(int superiorX, int superiorY, int inferiorX, int inferiorY)
{
	int i;
	while(superiorY != inferiorY)
	{
		i = superiorX;
		for(i;i<=inferiorX;i++)
		{
			gotoxy(i,superiorY);printf("%c", ' ');
		}
		superiorY++;
	}
}
