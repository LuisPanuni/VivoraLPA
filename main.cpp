#include<iostream>
#include<windows.h>
#include<conio.h>
#include<stdlib.h>

#define ARRIBA 72
#define ABAJO 80
#define IZQUIERDA 75
#define DERECHA 77
#define ESC 27

using namespace std;

int vivora [200][2];
int s=1;
int tamano = 10;
int x=10;
int y=12;
int dir=3;
int xb=30;
int yb=15;
int velocidad=100;
int h=1;
char teclas;
int puntuacion=0;

void gotoxy(int x, int y){
	HANDLE hcon;
	hcon = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD dwPos;
	dwPos.X = x;
	dwPos.Y = y;
	SetConsoleCursorPosition(hcon, dwPos);
}
	
void marco(){
	for(int i=2; i<78; i++){
		gotoxy(i,3);printf("%c",205);
		gotoxy(i,23);printf("%c",205);
	}
	for(int i=4; i<23; i++){
		gotoxy(2,i);printf("%c",186);
		gotoxy(77,i);printf("%c",186);
	}
	gotoxy(2,3);printf("%c",201);
	gotoxy(77,3);printf("%c",187);
	gotoxy(77,23);printf("%c",188);
	gotoxy(2,23);printf("%c",200);
}

void guardar(){
	vivora[s][0]=x;
	vivora[s][1]=y;
	s++;
	if(s==tamano){
		s=1;
	}
}

void dibujar(){
	for(int i=1; i<tamano; i++){
		gotoxy(vivora[i][0], vivora[i][1]); printf("%c",15);
	}	
}

void borrar(){
	for(int i=1; i<tamano;i++){
		gotoxy(vivora[i][0], vivora[i][1]); printf(" ");
	}
}

void movimientos(){
	if(kbhit()){
		teclas=getch();
		switch(teclas){
			case ARRIBA:
				if(dir!=2){
					dir=1;
				} 
				break;
			case ABAJO:
				if(dir!=1){
					dir=2;
				} 
				break;
			case DERECHA:
				if(dir!=4){
					dir=3;
				} 
				break;
			case IZQUIERDA:
				if(dir!=3){
					dir=4;
				} 
				break;
		}
	}	
}
	
void vel(){
	if(puntuacion==h*20){
		velocidad-=10;
		h++;
	}
}

void bolitas(){
	if(x==xb && y==yb){
		xb=(rand()%73)+4;
		yb=(rand()%19)+4;
		tamano++;
		puntuacion+=10;
		gotoxy(xb,yb);printf("%c",1);
	}
	vel();
}

bool choque(){
	if(x==2 || x==77 || y==3 || y==23){
		return false;
	}
	for(int j=tamano -1; j>0; j--){
		if(vivora [j][0]==x && vivora [j][1]==y){
			return false;
		}
	}
	return true;
}
	
void score(){
	gotoxy(3,1);printf("Score of Player: %d", puntuacion);
}
int main (int argc, char *argv[]) {
	marco();
	gotoxy(xb, yb);printf("%c",1);
	while(teclas != ESC && choque()){
		borrar();
		guardar();
		dibujar();
		bolitas();
		score();
		movimientos();
		movimientos();
		
		if(dir==1){y--;}
		if(dir==2){y++;}
		if(dir==3){x++;}
		if(dir==4){x--;}
		Sleep(velocidad);
	}
	marco();
	system("pause>null");
	return 0;
}

