//============================================================================
// Name        : game.cpp
// Author      : Hassan Mustafa
// Version     :
// Copyright   : (c) Reserved
// Description : Basic 2D game of Dodge 'Em...
//============================================================================

#ifndef DODGE_CPP_
#define DODGE_CPP_
#include <iostream>
#include<cmath> // for basic math functions such as cos, sin, sqrt
using namespace std;

// seed the random numbers generator by current time (see the documentation of srand for further help)...

/* Function sets canvas size (drawing area) in pixels...
 *  that is what dimensions (x and y) your game will have
 *  Note that the bottom-left coordinate has value (0,0) and top-right coordinate has value (width-1,height-1)
 * */
void SetCanvasSize(int width, int height) {
	glMatrixMode (GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, width, 0, height, -1, 1); // set the screen size to given width and height.
	glMatrixMode (GL_MODELVIEW);
	glLoadIdentity();
}


/*
 * Main Canvas drawing function.
 * */
//Board *b;
//Global Variables 
int map[840][960] = {{0}};
int food[840][960] = {{0}};
float x=445, y=30, x2 =345 , y2 = 30;
const float speed =1;
int gap_turn=60, sx=20, sy=10, sheight=10, swidth=(0.8*(800/2-gap_turn/2)),up_=0,down_=0,right_=0,left_=0,start_=1,score=0;
const int x_shrink = 74, y_shrink = 74;
string str_score= "";
void foodlocation(){
	for(int i = 40; i < 840; i+=75){
		for(int j =40; j < 800; j+=75)
			food[i][j]= 1;
		}
}
void foodupdate(){
	for(int i = 0; i < 840; i++){
		for(int j = 0; j < 840; j++){
			if(food[i][j]==1 && ((i-x)<=60 && (x-i) <=20) && (abs(y-j)<=20)){
				food[i][j]=0;
				score++;
				str_score = to_string(score);
				cout<<"str_score "<<str_score<<"\n";
			}
		}
	}
}
	
void GameDisplay()/**/{
	// set the background color using function glClearColor.
	// to change the background play with the red, green and blue values below.
	// Note that r, g and b values must be in the range [0,1] where 0 means dim rid and 1 means pure red and so on.
	
	glClearColor(0/*Red Component*/, 0,	//148.0/255/*Green Component*/,
			0.0/*Blue Component*/, 0 /*Alpha component*/); // Red==Green==Blue==1 --> White Colour
	glClear (GL_COLOR_BUFFER_BIT); //Update the colors

	// calling some functions from util.cpp file to help students
	
	//Square at 400,20 position
	//DrawSquare( 400 , 20 ,100,colors[RED]); 
	//Square at 250,250 position
	// 
	
	//Triangle at 300, 450 position
	//DrawTriangle( 300, 450 , 340, 450 , 320 , 490, colors[MISTY_ROSE] ); 
	//Trianlge Vertices v1(300,50) , v2(500,50) , v3(400,250)
	//Circle at 50, 670 position
	//DrawCircle(sx+swidth*2+gap_turn+x_shrink, 450,10,colors[GREEN]);
	//Line from 550,50 to 550,480 with width 10
	//DrawLine(int x1, int y1, int x2, int y2, int lwidth, float *color)
	//DrawLine( 770, 50 ,  550 , 480 , 10 , colors[MISTY_ROSE] );	
	
	//Drawing food
	for(int i = 0; i < 840; i++){
		for(int j = 0; j < 840; j++){
			if(food[i][j] ==1)
				DrawSquare( i , j ,10,colors[MISTY_ROSE]);
		}
	}
	//Display Score
	DrawString( 500, 900,"42", colors[MISTY_ROSE]);		
	//collision check
	if(abs(x-x2)<=40 && abs(y-y2)<=40){
		x=445; y=30; x2 =345; y2 = 30;}
		


	// Drawing player car
	float width = 12; 
	float height = 8;
	float* color = colors[CRIMSON]; 
	float radius = 5.0;
	DrawRoundRect(x,y,width,height,color,radius); // bottom left tyre
	DrawRoundRect(x+width*3,y,width,height,color,radius); // bottom right tyre
	DrawRoundRect(x+width*3,y+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(x,y+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(x, y+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(x+width, y+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(x+width*3, y+height*2, width, height, color, radius/2); // body right rect
	
	// Drawing opponent car
	 width = 12; 
	 height = 8;
	 color = colors[BLUE_VIOLET]; 
	 radius = 5.0;
	DrawRoundRect(x2,y2,width,height,color,radius); // bottom left tyre
	DrawRoundRect(x2+width*3,y2,width,height,color,radius); // bottom right tyre
	DrawRoundRect(x2+width*3,y2+height*4,width,height,color,radius); // top right tyre
	DrawRoundRect(x2,y2+height*4,width,height,color,radius); // top left tyre
	DrawRoundRect(x2, y2+height*2, width, height, color, radius/2); // body left rect
	DrawRoundRect(x2+width, y2+height, width*2, height*3, color, radius/2); // body center rect
	DrawRoundRect(x2+width*3, y2+height*2, width, height, color, radius/2); // body right rect


	// Drawing Arena(Outermost boundaries)
	gap_turn = 60;
	sx = 20;
	sy = 10;
	swidth = (800/2 - gap_turn/2); // half width
	sheight = 10;
	float *scolor = colors[BROWN];
	DrawRectangle(sx, sy, swidth, sheight, scolor); // bottom left
	DrawRectangle(sx + swidth + gap_turn, sy, swidth, sheight, scolor); // bottom right
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight, sheight*2, swidth, scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn, sy+810, swidth, sheight, scolor); // top left
	DrawRectangle(sx, sy+810, swidth, sheight, scolor); // top right
	DrawRectangle(sx-sheight*2, sy+sheight+swidth+gap_turn, sheight*2, swidth, scolor); // left up
	DrawRectangle(sx-sheight*2, sy+sheight, sheight*2, swidth, scolor); // left down
	
	// Drawing Arena(2nd to Outermost boundaries)
	const int x_shrink = 74, y_shrink = 74;
	swidth = 0.8*(800/2 - gap_turn/2); // half width
	scolor = colors[BROWN];
	DrawRectangle(sx+x_shrink, sy+y_shrink, swidth, sheight, scolor); // bottom left
	DrawRectangle(sx + swidth + gap_turn+x_shrink, sy+y_shrink, swidth, sheight, scolor); // bottom right
	DrawRectangle(sx+swidth*2+gap_turn+x_shrink, sy+sheight+y_shrink, sheight*2, swidth, scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn+ x_shrink, sy+sheight+swidth+gap_turn+y_shrink, sheight*2, swidth, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn+x_shrink, sy+810-y_shrink, swidth, sheight, scolor); // top left
	DrawRectangle(sx+x_shrink, sy+810-y_shrink, swidth, sheight, scolor); // top right
	DrawRectangle(sx-sheight*2+x_shrink, sy+sheight+swidth+gap_turn+y_shrink, sheight*2, swidth, scolor); // left up
	DrawRectangle(sx-sheight*2+x_shrink, sy+sheight+y_shrink, sheight*2, swidth, scolor); // left down
	
	// Drawing Arena(3rd to Outermost boundaries)
	swidth = 0.6*(800/2 - gap_turn/2); // half width
	scolor = colors[BROWN];
	DrawRectangle(sx+(2*x_shrink), sy+(2*y_shrink), swidth, sheight, scolor); // bottom left
	DrawRectangle(sx + swidth + gap_turn+(2*x_shrink), sy+(2*y_shrink), swidth, sheight, scolor); // bottom right
	DrawRectangle(sx+swidth*2+gap_turn+(2*x_shrink), sy+sheight+(2*y_shrink), sheight*2, swidth, scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn+ (2*x_shrink), sy+sheight+swidth+gap_turn+(2*y_shrink), sheight*2, swidth, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn+(2*x_shrink), sy+810-(2*y_shrink), swidth, sheight, scolor); // top left
	DrawRectangle(sx+(2*x_shrink), sy+810-(2*y_shrink), swidth, sheight, scolor); // top right
	DrawRectangle(sx-sheight*2+(2*x_shrink), sy+sheight+swidth+gap_turn+(2*y_shrink), sheight*2, swidth, scolor); // left up
	DrawRectangle(sx-sheight*2+(2*x_shrink), sy+sheight+(2*y_shrink), sheight*2, swidth, scolor); // left down
	
	// Drawing Arena(4th to Outermost boundaries)
	swidth = 0.4*(800/2 - gap_turn/2); // half width
	scolor = colors[BROWN];
	DrawRectangle(sx+(3*x_shrink), sy+(3*y_shrink), swidth, sheight, scolor); // bottom left
	DrawRectangle(sx + swidth + gap_turn+(3*x_shrink), sy+(3*y_shrink), swidth, sheight, scolor); // bottom right
	DrawRectangle(sx+swidth*2+gap_turn+(3*x_shrink), sy+sheight+(3*y_shrink), sheight*2, swidth, scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn+ (3*x_shrink), sy+sheight+swidth+gap_turn+(3*y_shrink), sheight*2, swidth, scolor); // right up
	DrawRectangle(sx + swidth + gap_turn+(3*x_shrink), sy+810-(3*y_shrink), swidth, sheight, scolor); // top left
	DrawRectangle(sx+(3*x_shrink), sy+810-(3*y_shrink), swidth, sheight, scolor); // top right
	DrawRectangle(sx-sheight*2+(3*x_shrink), sy+sheight+swidth+gap_turn+(3*y_shrink), sheight*2, swidth, scolor); // left up
	DrawRectangle(sx-sheight*2+(3*x_shrink), sy+sheight+(3*y_shrink), sheight*2, swidth, scolor); // left down

	// Drawing Arena(innermost boundaries)
	swidth = 0.2*(800/2 - gap_turn/2); // half width
	scolor = colors[BROWN];
	DrawRectangle(sx+(4*x_shrink), sy+(4*y_shrink), swidth, sheight, scolor); // bottom left
	DrawRectangle(sx +(4*x_shrink), sy+(4*y_shrink),2*swidth+gap_turn, sheight, scolor); // bottom right
	DrawRectangle(sx+swidth*2+gap_turn+(4*x_shrink), sy+sheight+(4*y_shrink), sheight*2, swidth, scolor); // right down
	DrawRectangle(sx+swidth*2+gap_turn+ (4*x_shrink), sy+sheight+swidth+gap_turn+(4*y_shrink), sheight*2, swidth, scolor); // right up
	DrawRectangle(sx +(4*x_shrink), sy+810-(4*y_shrink), 2*swidth + gap_turn, sheight, scolor); // top left
	DrawRectangle(sx+(4*x_shrink), sy+810-(4*y_shrink), swidth, sheight, scolor); // top right
	DrawRectangle(sx-sheight*2+(4*x_shrink), sy+sheight+swidth+gap_turn+(4*y_shrink), sheight*2, swidth, scolor); // left up
	DrawRectangle(sx-sheight*2+(4*x_shrink), sy+sheight+(4*y_shrink), sheight*2, swidth, scolor); // left down

	
	
	glutSwapBuffers(); // do not modify this line.. or draw anything below this line
}

/*This function is called (automatically) whenever any non-printable key (such as up-arrow, down-arraw)
 * is pressed from the keyboard
 *
 * You will have to add the necessary code here when the arrow keys are pressed or any other key is pressed...
 *
 * This function has three argument variable key contains the ASCII of the key pressed, while a and b tells the
 * program coordinates of mouse pointer when key was pressed.
 *
 * */

/*
 * This function is called after every 1000.0/FPS milliseconds
 * (FPS is defined on in the beginning).
 * You can use this function to animate objects and control the
 * speed of different moving objects by varying the constant FPS.
 *
 * */
void Timer(int m) {

	// implement your functionality here
	// once again we tell the library to call our Timer function after next 1000/FPS
	glutPostRedisplay();
	if(start_){
		if(x2 >= 20 && y2 <= 30)
			x2-=speed;
		if(x2<=20 && y2< 770)
			y2+=speed;
		if(y2>=770 && x2 < 770)
			x2+=speed;
		if(x2>=770 && y2 > 30)
			y2-=speed;
	}
	if(left_){
		x-=speed;
		foodupdate();
	}
	if(right_){
		x+=speed;
		foodupdate();
	}
	if(up_){
		y+=speed;
		foodupdate();
	}
	if(down_){
		y-=speed;
		foodupdate();
	}
	glutTimerFunc(20.0, Timer, 0);
	
}


void NonPrintableKeys(int key, int a, int b) {
	if (key
			== GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/) {
		// what to do when left key is pressed...
		/*if(x>=770 && (y>385 && y<445)){
			y=395;
			up_= 0; down_= 0; right_= 0;
			start_=0;
			left_=1;
			glutTimerFunc(20.0, Timer, 0);
		}*/
		left_=1; right_=0; up_=0; down_=0; 
				glutTimerFunc(20.0, Timer, 0);
			
	} else if (key
			== GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/) {
		
		left_=0; right_=1; up_=0; down_=0; 
				glutTimerFunc(20.0, Timer, 0);

	} else if (key
			== GLUT_KEY_UP/*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/) {
		/*if(y==395){ 
			if(!((x > 748 &&  x< 766) || (x > 671 &&  x< 691) ||(x > 598 &&  x< 618) ||(x > 526 &&  x< 545) ||(x > 297 &&  x< 316) ||(x > 224 &&  x< 243) ||(x > 148 &&  x< 168) ||(x > 76 &&  x< 94))){
				left_=0; right_=0; up_=1; down_=0; start_=0;
				glutTimerFunc(20.0, Timer, 0);
			}
		}*/
		left_=0; right_=0; up_=1; down_=0; 
				glutTimerFunc(20.0, Timer, 0);
	}else if (key
			== GLUT_KEY_DOWN/*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/) {
				left_=0; right_=0; up_=0; down_=1; 
				glutTimerFunc(20.0, Timer, 0);
	}

	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();


}

/*This function is called (automatically) whenever any printable key (such as x,b, enter, etc.)
 * is pressed from the keyboard
 * This function has three argument variable key contains the ASCII of the key pressed, while x and y tells the
 * program coordinates of mouse pointer when key was pressed.
 * */
void PrintableKeys(unsigned char key, int x, int y) {
	if (key == 27/* Escape key ASCII*/) {
		exit(1); // exit the program when escape key is pressed.
	}

	if (key == 'b' || key == 'B')
			{
		//do something if b is pressed
		cout << "b pressed" << endl;
	
	}
	if(key==32);
		

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse moves witin inside the game window
 *
 * You will have to add the necessary code here for finding the direction of shooting
 *
 * This function has two arguments: x & y that tells the coordinate of current position of move mouse
 *
 * */
void MousePressedAndMoved(int x, int y) {
	cout << x << " " << y << endl;
	glutPostRedisplay();
}
void MouseMoved(int x, int y) {

	glutPostRedisplay();
}

/*This function is called (automatically) whenever your mouse button is clicked witin inside the game window
 *
 * You will have to add the necessary code here for shooting, etc.
 *
 * This function has four arguments: button (Left, Middle or Right), state (button is pressed or released),
 * x & y that tells the coordinate of current position of move mouse
 *
 * */
void MouseClicked(int button, int state, int x, int y) {

	if (button == GLUT_LEFT_BUTTON) // dealing only with left button
			{
		cout << GLUT_DOWN << " " << GLUT_UP << endl;

	} else if (button == GLUT_RIGHT_BUTTON) // dealing with right button
			{

	}
	glutPostRedisplay();
}
/*
 * our gateway main function
 * */
	int main(int argc, char*argv[]) {
	//b = new Board(60, 60); // create a new board object to use in the Display Function ...
	foodlocation();
	int width = 840, height = 960; // i have set my window size to be 800 x 600
	//b->InitalizeBoard(width, height);
	InitRandomizer(); // seed the random number generator...
	glutInit(&argc, argv); // initialize the graphics library...
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA); // we will be using color display mode
	glutInitWindowPosition(50, 50); // set the initial position of our window
	glutInitWindowSize(width, height); // set the size of our window
	glutCreateWindow("OOP Centipede"); // set the title of our game window
	SetCanvasSize(width, height); // set the number of pixels...

	// Register your functions to the library,
	// you are telling the library names of function to call for different tasks.
	//glutDisplayFunc(display); // tell library which function to call for drawing Canvas.

	glutDisplayFunc(GameDisplay); // tell library which function to call for drawing Canvas.
	glutTimerFunc(20.0, Timer, 0);
	glutSpecialFunc(NonPrintableKeys); // tell library which function to call for non-printable ASCII characters
	glutKeyboardFunc(PrintableKeys); // tell library which function to call for printable ASCII characters
	// This function tells the library to call our Timer function after 1000.0/FPS milliseconds...
	

	glutMouseFunc(MouseClicked);
	glutPassiveMotionFunc(MouseMoved); // Mouse
	glutMotionFunc(MousePressedAndMoved); // Mouse

	// now handle the control to library and it will call our registered functions when
	// it deems necessary...
	glutMainLoop();
	return 1;
}
#endif /* AsteroidS_CPP_ */
