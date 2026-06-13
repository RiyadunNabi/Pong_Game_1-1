#include "iGraphics.h"
#include <stdlib.h> // for rand() function
#include <math.h>

int screenWidth = 720, screenHeight = 480;
float x = screenWidth / 2, y = screenHeight / 2, radius = 7.5; // ball co-ordinate x,y
// paddle
float length = 10, breadth = 70;
float c_paddleX = 20, c_paddleY = y - breadth / 2;			  // left computer paddle co-ordinate c_paddleX,c_paddleY
float paddleX = 720 - 20 - length, paddleY = y - breadth / 2; // right-paddle co-ordinate paddleX,paddleY

int difficultyLevel;
int winScore = 3;

bool onePlayer;
bool isPlay = false;
bool player_1_wins = false;
bool player_2_wins = false;
bool playSound_on = true;
bool ball_moves_right = true; // ball will move to right direction(90 degree) first

void play_sound(int n);
void c_paddleControl();
// void c_paddleControl2();
// double c_controlPaddle3()
void restartGame();
void displayScore();
void resetScore();
void rePosition_all();
void newGame();
int scorePlayer1 = 0, scorePlayer2 = 0;
void winnerChecker();

int bgIndex = 0;

int sl_No = 0;
int play_bg = 4;
int play_mode;
void background(int sl_No)
{
	if (sl_No == 0)
	{
		iShowBMP(0, 0, "BG\\Pong\\Menu.bmp");
	}
	else if (sl_No == 11)
	{
		iShowBMP(0, 0, "BG\\Pong\\GamePlay_mode.bmp");
	}
	else if (sl_No == 111)
	{
		iShowBMP(0, 0, "BG\\Pong\\Difficulty_level.bmp");
	}
	else if (sl_No == 1)
	{
		if (play_bg == 0)
			iShowBMP(0, 0, "BG\\Pong\\gameplay_bg_solid.bmp");
		else if (play_bg == 1)
		{ // black
		}
		else if (play_bg == 2)
			iShowBMP(0, 0, "BG\\Pong\\play_BG_a.bmp");
		else if (play_bg == 3)
			iShowBMP(0, 0, "BG\\Pong\\play_BG_b.bmp");
		else if (play_bg == 4)
			iShowBMP(0, 0, "BG\\Pong\\play_BG_c.bmp");
		else if (play_bg == 5)
			iShowBMP(0, 0, "BG\\Pong\\play_BG_d.bmp");
		else if (play_bg == 6)
			iShowBMP(0, 0, "BG\\Pong\\play_BG_e.bmp");

		iSetColor(0, 204, 0);
		iFilledCircle(x, y, radius, 1000);

		iSetColor(204, 0, 0);
		iFilledRectangle(paddleX, paddleY, length, breadth);
		iFilledCircle(paddleX + length / 2, paddleY, length / 2);			// lower circle
		iFilledCircle(paddleX + length / 2, paddleY + breadth, length / 2); // upper circle

		// iSetColor(192, 192, 192);
		iFilledRectangle(c_paddleX, c_paddleY, length, breadth);
		iFilledCircle(c_paddleX + length / 2, c_paddleY, length / 2);			// lower circle
		iFilledCircle(c_paddleX + length / 2, c_paddleY + breadth, length / 2); // upper circle

		// if (!isPlay)
		// {
		// 	iSetColor(255, 255, 0);
		// 	iText(screenWidth / 2 - 100, 70, "Press Spacebar to Start!" /* , GLUT_BITMAP_HELVETICA_12 */);
		// 	iText(215, 30, "Press key 'C' to change background." /* , GLUT_BITMAP_HELVETICA_12 */);
		// }

		displayScore();
		winnerChecker();
	}
	else if (sl_No == 2)
	{
		if (playSound_on)
		{
			iShowBMP(0, 0, "BG\\Pong\\SoundEffect_on.bmp");
		}
		else
		{
			iShowBMP(0, 0, "BG\\Pong\\SoundEffect_off.bmp");
		}
	}
	else if (sl_No == 3)
		iShowBMP(0, 0, "BG\\Pong\\Instructions.bmp");
	else if (sl_No == 4)
		iShowBMP(0, 0, "BG\\Pong\\Credits.bmp");
}
/*
	function iDraw() is called again and again by the system.

*/
void iDraw()
{
	// place your drawing codes here
	iClear();
	background(sl_No);

	// iSetColor(20, 200, 0);
	// iText(40, 40, "Hi, I am iGraphics");

	if (sl_No != 0 && (sl_No != 1 || !isPlay))
	{
		iSetColor(0, 204, 204);
		iText(10, 450, "Back", GLUT_BITMAP_HELVETICA_18);
	}
	if (sl_No == 1 && !isPlay)
	{
		iSetColor(255, 255, 0);
		if (!player_2_wins)
		{
			iText(screenWidth / 2 - 100, 50, "Press Spacebar to Start!" /* , GLUT_BITMAP_HELVETICA_12 */);
			iText(215, 20, "Press key 'C' to change background." /* , GLUT_BITMAP_HELVETICA_12 */);
		}
		
		if (player_2_wins)
		{
			iText(screenWidth / 2 - 130, 20, "Press Spacebar to Start Again!" /* , GLUT_BITMAP_HELVETICA_12 */);
		}
	}
}

/*
	function iMouseMove() is called when the user presses and drags the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouseMove(int mx, int my)
{
	printf("x = %d, y= %d\n", mx, my);
	// place your codes here
}
// double test();
// double predict();
/*
	function iMouse() is called when the user presses/releases the mouse.
	(mx, my) is the position where the mouse pointer is.
	*/
void iMouse(int button, int state, int mx, int my)
{
	if (sl_No != 0 && mx >= 0 && mx <= 50 && my >= 430 && my <= 670)
	{
		if (sl_No == 1)
		{
			play_sound(0);
			isPlay = false;
		}
		sl_No = 0;				 // Exit to Menu
		ball_moves_right = true; // ball will move to right direction(90 degree) first
	}

	if (sl_No == 0)
	{
		if (mx >= 310 && mx <= 400 && my >= 245 && my <= 275 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			sl_No = 11; // play mode
		}
		else if (mx >= 275 && mx <= 440 && my >= 195 && my <= 220 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			sl_No = 2; // settings sound effect
		}
		else if (mx >= 245 && mx <= 475 && my >= 137 && my <= 165 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			sl_No = 3; // instruction
		}
		else if (mx >= 290 && mx <= 430 && my >= 80 && my <= 110 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			sl_No = 4; // Credit
		}
		// if(mx>=530 && mx<=667 && my>=192 && my<=215 )

		// if(mx>=555 && mx<=634 && my>= && my<= )

		// if(mx>= && mx<= && my>= && my<= )
		else if (mx >= 320 && mx <= 400 && my >= 30 && my <= 50 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // exit
		{
			exit(0); // Exit
		}
	}

	else if (sl_No == 11) // Play Mode
	{
		if (mx >= 245 && mx <= 475 && my >= 250 && my <= 290 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // one player
		{
			onePlayer = true;
			sl_No = 111; // difficulty level
		}
		else if (mx >= 245 && mx <= 475 && my >= 190 && my <= 225 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // two player
		{
			onePlayer = false;
			sl_No = 1; // Play Two Player
			play_sound(10);
			newGame();
		}
	}
	else if (sl_No == 111)
	{
		if (mx >= 300 && mx <= 420 && my >= 290 && my <= 315 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // easy
		{
			difficultyLevel = 25;
			sl_No = 1;
			play_sound(10);
			newGame();
		}
		else if (mx >= 280 && mx <= 435 && my >= 230 && my <= 260 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // medium
		{
			difficultyLevel = 28;
			sl_No = 1;
			play_sound(10);
			newGame();
		}
		else if (mx >= 310 && mx <= 410 && my >= 170 && my <= 195 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) // hard
		{
			difficultyLevel = 29;
			sl_No = 1;
			play_sound(10);
			newGame();
		}
	}
	else if (sl_No == 2) // soundeffect
	{
		if (playSound_on && mx >= 465 && mx <= 485 && my >= 250 && my <= 290 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			PlaySound(NULL, NULL, NULL);
			playSound_on = false;
		}
		else if (!playSound_on && mx >= 465 && mx <= 485 && my >= 250 && my <= 290 && button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
		{
			playSound_on = true;
			play_sound(0);
		}
	}

	// else if (sl_No == 1)
	// {
	// }
}
/*
	function iKeyboard() is called whenever the user hits a key in keyboard.
	key- holds the ASCII value of the key pressed.
*/
void iKeyboard(unsigned char key)
{
	if (key == 'q')
	{
		exit(0);
	}
	if (sl_No == 1)
	{
		if (key == ' ' && !isPlay)
		{
			isPlay = true;
			resetScore();
		}
		else if (key == ' ' && isPlay)
		{
			isPlay = false;
		}

		// changing gameplay bg
		if (key == 'c' && play_bg >= 0 && play_bg <= 6)
		{
			if (play_bg == 6)
			{
				play_bg = 0;
			}
			else
				play_bg++;
		}

		// two player control
		if (!onePlayer)
		{
			if (key == 's' && c_paddleY <= 480 - breadth - 10)
			{
				c_paddleY += 10;
			}
			if (key == 'x' && c_paddleY - 10 >= 0)
			{
				c_paddleY -= 10;
			}
		}
	}

	// place your codes for other keys here
}
/*
	function iSpecialKeyboard() is called whenver user hits special keys like-
	function keys, home, end, pg up, pg down, arraows etc. you have to use
	appropriate constants to detect them. A list is:
	GLUT_KEY_F1, GLUT_KEY_F2, GLUT_KEY_F3, GLUT_KEY_F4, GLUT_KEY_F5, GLUT_KEY_F6,
	GLUT_KEY_F7, GLUT_KEY_F8, GLUT_KEY_F9, GLUT_KEY_F10, GLUT_KEY_F11, GLUT_KEY_F12,
	GLUT_KEY_LEFT, GLUT_KEY_UP, GLUT_KEY_RIGHT, GLUT_KEY_DOWN, GLUT_KEY_PAGE UP,
	GLUT_KEY_PAGE DOWN, GLUT_KEY_HOME, GLUT_KEY_END, GLUT_KEY_INSERT
	*/
void iSpecialKeyboard(unsigned char key)
{

	if (key == GLUT_KEY_END)
	{
		exit(0);
	}
	if (key == GLUT_KEY_UP && paddleY <= 480 - breadth - 10)
	{
		paddleY += 10;
	}
	if (key == GLUT_KEY_DOWN && paddleY - 10 >= 0)
	{
		paddleY -= 10;
	}
	// place your codes for other keys here
}

// float dx = 7.5, dy = 7.5;
float v = 7;
float theta = 3.1416 / 2;
float dx = v * sin(theta);
float dy = v * cos(theta);
float invisible_length = 0;
void change()
{
	if (sl_No == 1)
	{
		if (isPlay)
		{

			x += dx;
			y += dy;
			if (v <= 9)
			{
				v += 0.001;
				invisible_length += 0.001;
			}

			// c_paddleY = y;
			if (onePlayer)
			{
				c_paddleControl();
			}

			if (((x + radius) > paddleX && (x + radius) < (paddleX + length + invisible_length) && y >= (paddleY - 5) /*for small ball of 5 radius*/ && y <= (paddleY + breadth + 5)) || ((x - radius) < (c_paddleX + length)) && ((x - radius) > (c_paddleX - invisible_length)) && (y >= (c_paddleY - 5)) && (y <= (c_paddleY + breadth + 5)))
			{
				if (x < (720 / 2))
				{ // 5+5 for upper & lower circle
					theta = (120 / (breadth + 10) * (y - c_paddleY) + float(30)) * (3.1416 / 180);
					if (y < (c_paddleY + breadth / 2))
					{
						dx = +v * sin(theta);
						dy = -v * abs(cos(theta));
					}
					else
					{
						dx = +v * sin(theta);
						dy = v * abs(cos(theta));
					}
					// printf("ball =%f,%f, hit_l=%f, theta=%f, dx=%.2f, dy=%.2f\n", y, c_paddleY, v, y - c_paddleY, theta * 180 / 3.1416, dx, dy);
				}
				else if (x > (720 / 2))
				{
					theta = (120 / (breadth + 10) * (y - paddleY) + float(30)) * (3.1416 / 180);
					if (y < (paddleY + breadth / 2))
					{
						dx = -v * sin(theta);
						dy = -v * abs(cos(theta));
					}
					else
					{
						dx = -v * sin(theta);
						dy = v * abs(cos(theta));
					}
					// printf("v=%f, hit_r=%f, theta=%f, dx=%.2f, dy=%.2f\n", v, y - paddleY, theta * 180 / 3.1416, dx, dy);
				}
				play_sound(1);
			}

			if ((y - radius) <= 0 || (y + radius) >= 480)
			{
				dy *= -1;
				play_sound(1);
				// printf("Hit x,y=%lf %lf,dx=%lf,dy=%lf\n", x, y, dx, dy);
			}

			if (x <= 0)
			{
				scorePlayer2++;
				if (scorePlayer2 < winScore)
				{
					play_sound(2);
				}
				restartGame();
			}
			if (x >= screenWidth)
			{
				scorePlayer1++;
				if (scorePlayer1 < winScore)
				{
					play_sound(3);
				}
				restartGame();
			}
		}
	}
}

/*double c_controlPaddle3()
{

	double CollisionPoint = predict();
	double rangeY1 = std::max(double(0) + (double)breadth, CollisionPoint - double(breadth) / 2);
	double rangeY2 = std::min((double)screenHeight - breadth, CollisionPoint + double(breadth) / 2);
	static double speed = 0;
	static bool calCulatedBefore=false;
	if(dx>0)
	{
		speed=0;
		calCulatedBefore=false;
	}
	else if ((c_paddleY + (double)breadth / 2 < rangeY1 || c_paddleY + (double)breadth / 2 > rangeY2)&&!calCulatedBefore)
	{
		printf("HERE!!!");
		int predictedPosition = rand() % (int(rangeY2) - int(rangeY1)) + int(rangeY1);
		c_paddleY = (double)predictedPosition;
		double time = (x - 0) / (-dx);
		calCulatedBefore=true;
		speed = ((double)predictedPosition - c_paddleY) / time;
		if (speed < -10.0)
			speed = -10;
		if (speed > 10.0)
			speed = 10;
	}
	else if((c_paddleY + (double)breadth / 2 >= rangeY1&& c_paddleY + (double)breadth / 2 <= rangeY2))
	{
		speed=0;
	}
	return speed;
}

double predict()
{
	static bool calCulatedBefore = false;
	double predictedY;
	double nextCollision = test();
	if (nextCollision < 0 && !calCulatedBefore)
	{
		double time = (x - 20) / (-dx);
		predictedY = y + time * dy;
		calCulatedBefore = true;
	}
	else
	{
		calCulatedBefore = false;
		predictedY = c_paddleY;
	}
	return predictedY;
}

double test()
{
	double time;
	double nextCollision;
	if (dy < 0)
	{
		time = (y - 0) / (-dy);
		nextCollision = time * dx + x;
	}
	else
	{
		time = (480 - y) / (dy);
		nextCollision = time * dx + x;
	}
	return nextCollision;
}
*/

int main()
{
	// place your own initialization codes here.

	iSetTimer(10, change);
	if (playSound_on)
	{
		play_sound(0);
	}
	iInitialize(screenWidth, screenHeight, "Pong Rush Game");

	return 0;
}

int c_paddleSpeed = 5; // Initial computer-controlled paddle speed
float c_paddleSpeed2 = 2;
void c_paddleControl()
{
	// Inside the updateGame function where you handle paddle movement:
	if (x < 360 - 7.5 && dx < 0 /*(c_paddleY+breadth/2 - 20 < y || c_paddleY+breadth/2 + 20 > y)*/)
	{								   // Adjusted for the left paddle
		int randomValue = rand() % 30; // Generate a random value between 0 and 15
		if (randomValue < difficultyLevel)
		{ // Move the paddle most of the time
			if ((c_paddleY + breadth / 2) < y && abs((c_paddleY + breadth / 2) - y) > 10 && c_paddleY <= (480 - breadth - 10))
			{
				c_paddleY += c_paddleSpeed; // Move paddle up
			}
			else if ((c_paddleY + breadth / 2) > y && abs((c_paddleY + breadth / 2) - y) > 10 && (c_paddleY - 10) >= 0)
			{
				c_paddleY -= c_paddleSpeed; // Move paddle down
			}
		}
	}
	else if (x > 360 - 7.5 && dx < 0)
	{
		if ((c_paddleY + breadth / 2) < y && abs((c_paddleY + breadth / 2) - y) > 100)
		{
			c_paddleY += c_paddleSpeed2; // Move paddle up
		}
		else if ((c_paddleY + breadth / 2) > y && abs((c_paddleY + breadth / 2) - y) > 100)
		{
			c_paddleY -= c_paddleSpeed2; // Move paddle down
		}
	}
}

void play_sound(int n)
{
	if (playSound_on)
	{
		if (n == 0) // menu bg
		{
			PlaySound(TEXT("Sound\\0_Chiptune_game_bg.wav"), NULL, SND_ASYNC);
		}
		if (n == 10) // start
		{
			PlaySound(TEXT("Sound\\0_start.wav"), NULL, SND_ASYNC);
		}
		if (n == 1) // colission
		{
			PlaySound(TEXT("Sound\\1_2_collision_wood_edit.wav"), NULL, SND_ASYNC);
		}			// 1_2_collision_wood
		if (n == 2) // scorePlayer++
		{
			PlaySound(TEXT("Sound\\2_missEnemy_scorePlayer.wav"), NULL, SND_ASYNC);
		}
		if (n == 3) // missPlayer
		{
			PlaySound(TEXT("Sound\\3_missPlayer.wav"), NULL, SND_ASYNC);
		}
		if (n == 4) // gameWin
		{
			PlaySound(TEXT("Sound\\4_1_gameWin.wav"), NULL, SND_ASYNC);
		}
		if (n == 5) // you_lost_game_over_tiutiu
		{
			PlaySound(TEXT("Sound\\5_game_over_tiutiu.wav"), NULL, SND_ASYNC);
		}
	}
}
void displayScore()
{
	// Convert scores to strings
	char scoreStrPlayer1[10];
	char scoreStrPlayer2[10];
	sprintf(scoreStrPlayer1, "%d", scorePlayer1);
	sprintf(scoreStrPlayer2, "%d", scorePlayer2);

	// Display scores on the screen
	if (onePlayer)
	{
		iSetColor(255, 255, 255);

		iText(225, 441, "          AI:", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(325, 440, scoreStrPlayer1, GLUT_BITMAP_TIMES_ROMAN_24);

		iText(370, 441, "You:", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(425, 440, scoreStrPlayer2, GLUT_BITMAP_TIMES_ROMAN_24);
	}
	else
	{
		iSetColor(255, 255, 255);

		iText(250, 441, "Player 1:", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(337, 440, scoreStrPlayer1, GLUT_BITMAP_TIMES_ROMAN_24);

		iText(370, 441, "Player 2:", GLUT_BITMAP_TIMES_ROMAN_24);
		iText(463, 440, scoreStrPlayer2, GLUT_BITMAP_TIMES_ROMAN_24);
	}
}

void winnerChecker()
{
	if (onePlayer)
	{
		if (player_1_wins)
		{
			iSetColor(255, 0, 0);
			iText(screenWidth / 2 - 45, 400, "You lost!", GLUT_BITMAP_TIMES_ROMAN_24);
			// play_sound(4);
		}
		if (player_2_wins)
		{
			// iSetColor(255, 0, 0);
			// iText(screenWidth / 2 - 45, 400, "You Won!", GLUT_BITMAP_TIMES_ROMAN_24);
			// // play_sound(5);
			iShowBMP(0, 0, "BG\\Pong\\you_win.bmp");
		}
	}
	else
	{
		if (player_1_wins)
		{
			iSetColor(255, 0, 0);
			iText(screenWidth / 2 - 70, 400, "Player 1 Wins!", GLUT_BITMAP_TIMES_ROMAN_24);
			// play_sound(4);
		}
		if (player_2_wins)
		{
			iSetColor(255, 0, 0);
			iText(screenWidth / 2 - 70, 400, "Player 2 Wins!", GLUT_BITMAP_TIMES_ROMAN_24);
			// play_sound(5);
		}
	}
}
void resetScore()
{
	if (player_1_wins)
	{
		player_1_wins = false;
		scorePlayer1 = 0;
		scorePlayer2 = 0;
	}
	else if (player_2_wins)
	{
		player_2_wins = false;
		scorePlayer1 = 0;
		scorePlayer2 = 0;
	}
}
void restartGame()
{
	rePosition_all();
	if (scorePlayer1 >= winScore)
	{
		player_1_wins = true;
		play_sound(5);
	}
	else if (scorePlayer2 >= winScore)
	{
		player_2_wins = true;
		play_sound(4);
	}
}

void rePosition_all()
{
	x = screenWidth / 2;
	y = screenHeight / 2; // ball co-ordinate x,y

	v = 7;

	if (ball_moves_right) // if ball_moves_rightt=true;  ball will move to right direction(90 degree) first.
	{
		theta = 90 * 3.1416 / 180;
		ball_moves_right = false;
	}
	else if (!ball_moves_right)
	{
		theta = -85 * 3.1416 / 180;
		ball_moves_right = true;
	}

	dx = v * sin(theta);
	dy = v * cos(theta);

	paddleY = y - breadth / 2; // right-paddle co-ordinate paddleX,paddleY
	c_paddleY = y - breadth / 2;

	isPlay = false;
}
void newGame()
{
	rePosition_all();
	scorePlayer1 = 0;
	scorePlayer2 = 0;
}