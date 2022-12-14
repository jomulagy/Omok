#include "omokncurses.h"
#include "check.h"

int winidentifier(char* board[19][20])
{
	for (int i = 0; i < 19; i++)
		for (int j = 0; j < 19; j++)
			if ((i < 15) &&
				strcmp(board[i][j], "@") == 0 &&
				strcmp(board[i + 1][j], "@") == 0 &&
				strcmp(board[i + 2][j], "@") == 0 &&
				strcmp(board[i + 3][j], "@") == 0 &&
				strcmp(board[i + 4][j], "@") == 0)
				return 1;
			else if ((j < 15) &&
				strcmp(board[i][j], "@") == 0 &&
				strcmp(board[i][j + 1], "@") == 0 &&
				strcmp(board[i][j + 2], "@") == 0 &&
				strcmp(board[i][j + 3], "@") == 0 &&
				strcmp(board[i][j + 4], "@") == 0)
				return 1;
			else if ((j < 15) && (i < 15) &&
				strcmp(board[i][j], "@") == 0 &&
				strcmp(board[i + 1][j + 1], "@") == 0 &&
				strcmp(board[i + 2][j + 2], "@") == 0 &&
				strcmp(board[i + 3][j + 3], "@") == 0 &&
				strcmp(board[i + 4][j + 4], "@") == 0)
				return 1;
			else if ((i > 4) &&
				strcmp(board[i][j], "@") == 0 &&
				strcmp(board[i - 1][j + 1], "@") == 0 &&
				strcmp(board[i - 2][j + 2], "@") == 0 &&
				strcmp(board[i - 3][j + 3], "@") == 0 &&
				strcmp(board[i - 4][j + 4], "@") == 0)
				return 1;
			else if ((j < 15) &&
				strcmp(board[i][j], "O") == 0 &&
				strcmp(board[i][j + 1], "O") == 0 &&
				strcmp(board[i][j + 2], "O") == 0 &&
				strcmp(board[i][j + 3], "O") == 0 &&
				strcmp(board[i][j + 4], "O") == 0)
				return 2;
			else if ((i < 15) &&
				strcmp(board[i][j], "O") == 0 &&
				strcmp(board[i + 1][j], "O") == 0 &&
				strcmp(board[i + 2][j], "O") == 0 &&
				strcmp(board[i + 3][j], "O") == 0 &&
				strcmp(board[i + 4][j], "O") == 0)
				return 2;
			else if ((i < 15) && (j < 15) &&
				strcmp(board[i][j], "O") == 0 &&
				strcmp(board[i + 1][j + 1], "O") == 0 &&
				strcmp(board[i + 2][j + 2], "O") == 0 &&
				strcmp(board[i + 3][j + 3], "O") == 0 &&
				strcmp(board[i + 4][j + 4], "O") == 0)
				return 2;
			else if ((i > 4) && (strcmp(board[i][j], "O")) == 0 &&
				strcmp(board[i - 1][j + 1], "O") == 0 &&
				strcmp(board[i - 2][j + 2], "O") == 0 &&
				strcmp(board[i - 3][j + 3], "O") == 0 &&
				strcmp(board[i - 4][j + 4], "O") == 0)
				return 2;
	return 0;
}

int omokManager(char user1[], char user2[], char* board[19][20], char* user_id)
{
	
	initscr();
	clear();
	cbreak();
	noecho();
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);

	WINDOW* gamewind = newwin(30, 59, yMax / 2 - 12, xMax / 2 - 30);

	keypad(gamewind, TRUE);
	box(gamewind, 0, 0);
	refresh();
	wrefresh(gamewind);

	int xpos = 3;
	for (int i = 0; i < 19; i++) {
		xpos = 3;
		for (int j = 0; j < 19; j++) {
			mvwprintw(gamewind, 1 + i, xpos - 2, " %s ", board[i][j]);
			xpos += 3;
		}
	}
	int win = winidentifier(board);
	if (win == 1) {
		delwin(gamewind);
		endwin();
		printf("%s win!\n", user1);
		return 0;
	}
	else if (win == 2) {
		delwin(gamewind);
		endwin();
		printf("%s win\n", user2);
		return 0;
	}
	if (user_id == "1")
		mvwprintw(gamewind, 25, 10, "%s TURN", user1);
	else
		mvwprintw(gamewind, 25, 10, "%s TURN", user2);
	int highlight = 1;
	int choice;
	int enter = 1;
	while (enter) {
		for (int i = 0; i < 361; i++) {
			if (i == highlight) {
				wattron(gamewind, A_REVERSE);
			}
			mvwprintw(gamewind, (i / 19) + 1, (3 * (i % 19) + 2), "%s", board[i / 19][i % 19]);
			wattroff(gamewind, A_REVERSE);
		}
		refresh();
		wrefresh(gamewind);
		choice = getch();
		switch (choice) {
		case KEY_UP:
			if (highlight / 19 == 0) {
				highlight = highlight + (18 * 19);
			}
			else {
				highlight -= 19;
			}
			break;
		case KEY_DOWN:
			if (highlight / 19 == 18) {
				highlight = highlight % 19;
			}
			else {
				highlight += 19;
			}
			break;
		case KEY_LEFT:
			if (highlight % 19 == 0) {
				highlight = highlight + 18;
			}
			else {
				highlight -= 1;
			}
			break;
		case KEY_RIGHT:
			if (highlight % 19 == 18) {
				highlight = highlight - 18;
			}
			else {
				highlight += 1;
			}
			break;
		case 10:

			wrefresh(gamewind);
			int col, row;
			if (highlight / 19 == 0) {
				col = 0;
				row = highlight;
			}
			else {
				col = highlight / 19;
				row = highlight % 19;
			}
			int chck = check(board,user_id, highlight/19, highlight%19);
			if (strcmp(board[col][row], "+") != 0) {
				mvwprintw(gamewind, 26, 10, "Place already tooked!");
				continue;
			}
			else if(chck == 33){

				mvwprintw(gamewind, 28, 10, "Cant place there. 3*3");
				continue;
			}
			
			else if(chck == 44){

				mvwprintw(gamewind, 28, 10, "Cant place there. 4*4");
				continue;
			}
			
			else {

				mvwprintw(gamewind, 26, 10, "                      ");
				mvwprintw(gamewind, 28, 10, "                      ");
				

			}

			if (strcmp(user_id,"1")==0) {
				board[col][row] = "@";
				enter = 0;
			}
			else {
				board[col][row] = "0";
				enter = 0;
			}
			


			break;
		default:
			break;
		}
	}
	endwin();
	return 2 * highlight;
}


int chooseModeWindow() {
	clear();
	initscr();
	cbreak();
	noecho();
	int yMax, xMax;
	getmaxyx(stdscr, yMax, xMax);
	WINDOW* menuwin = newwin(yMax / 2, xMax / 2, yMax / 4, xMax / 4);
	box(menuwin, 0, 0);
	refresh();
	wrefresh(menuwin);
	int myMax, mxMax;
	getmaxyx(menuwin, myMax, mxMax);
	mvwprintw(menuwin, 2, (mxMax - 9) / 2, "OMOK MENU");
	refresh();
	wrefresh(menuwin);

	keypad(menuwin, true);

	char* choices[3] = { "VS Computer Mode", "PVP Mode", "Exit" };
	int choice;
	int highlight = 0;
	bool enter = 1;
	while (enter) {
		for (int i = 0; i < 3; i++) {
			if (i == highlight) {
				wattron(menuwin, A_REVERSE);
			}
			mvwprintw(menuwin, i + myMax / 2, (mxMax - strlen(choices[i])) / 2, "%s", choices[i]);
			wattroff(menuwin, A_REVERSE);
		}
		choice = wgetch(menuwin);

		switch (choice) {
		case KEY_UP:
			highlight--;
			if (highlight == -1)
				highlight = 0;
			break;
		case KEY_DOWN:
			highlight++;
			if (highlight == 3)
				highlight = 2;
			break;
		case 10:
			enter = 0;
			break;
		default:
			break;
		}
	}
	endwin();

	return highlight;
}
