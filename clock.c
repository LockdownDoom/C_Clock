#include <stdio.h>
#include <ncurses.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>
#include <wchar.h>
#include <string.h>

#define RAD 0.0174533

void drawClock(int c_x, int c_y, int radius,WINDOW * win){
	time_t now = time(NULL);
	struct tm *now_ints;
	now_ints = localtime(&now);
	int seconds = now_ints->tm_sec; 
	float scale_sec = ((float)seconds)/60.0;
	int minutes = now_ints->tm_min;
	float scale_min = ((float)minutes)/60.0;
	int hours = now_ints->tm_hour;
	float scale_hr = ((float)hours)/12.0;
	attron(COLOR_PAIR(1));
	//draw the outline
	for (int a=0;a<360;a++){
		mvwprintw(win, c_y+sin(a)*radius,c_x+cos(a)*radius*2,"*");
	}
	//draw the clock hands
	for (int r=0;r<radius;r++){
		attron(COLOR_PAIR(2));
		mvwprintw(win, c_y+sin(RAD*((360.0*scale_sec)-90))*(float)r,c_x+cos(RAD*((360.0*scale_sec)-90))*2.0*(float)r,"*");
		attron(COLOR_PAIR(3));
		if (r<=0.9*radius){
			mvwprintw(win, c_y+sin(RAD*((360.0*scale_min)-90))*(float)r,c_x+cos(RAD*((360.0*scale_min)-90))*2.0*(float)r,"*");
	
		}
		attron(COLOR_PAIR(4));
		if (r<=0.7*radius){
			mvwprintw(win,c_y+sin(RAD*((360.0*scale_hr)-90))*(float)r,c_x+cos(RAD*((360.0*scale_hr)-90))*2.0*(float)r,"*");
		}
	}
}
int main(){
	WINDOW * win = initscr();
	start_color();
	init_pair(1, COLOR_WHITE, COLOR_BLACK);
	init_pair(2, COLOR_RED, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_GREEN, COLOR_BLACK);
	noecho();
	curs_set(FALSE);
	int y=0;
	int x=0;
	while (1){
		clear();
		getmaxyx(win,y,x);
		y/=2;
		x/=2;
		int rad=0;
		if (x<=y){
			rad=x;
		}else{
			rad=y;
		}
		drawClock(x,y,rad,win);
		refresh();
		usleep(1000000);
	}
	endwin();
	return 0;
}
