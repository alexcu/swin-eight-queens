//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//
//                   --N-QUEENS PUZZLE--
//              Written By Alex Cummaudo, 1744070
//     For HIT1301 - Algorithmic Problem Solving Portfolio
//			
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include <stdio.h>
#include "SwinGame.h"
#include "usrio.h"
#include <stdlib.h>

typedef struct ctrl_data
{
	int n;
	int attempts;
} ctrl_data;

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                          SETUP GAME
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------
// get_chequer_colour function
// DESCRIPTION: returns the colour of appropriate chequered
//				space
//-----------------------------------------------------------

color get_chequer_colour(const int &row, const int &col) 
{
		// If even row?
		if (row % 2 == 0) {
			// If col is even?
			if (col % 2 == 0)
				return ColorBlack; // Draw it black
			// If col is odd?
			else
				return ColorWhite; // Draw it white
		}
		// If odd row?
		else {
			// If col is even?
			if (col % 2 == 0)
				return ColorWhite; // Draw it black
			// If col is odd?
			else
				return ColorBlack; // Draw it white
		}
}

//-----------------------------------------------------------
// draw_row Procedure
// DESCRIPTION: Draws a row for a grid
//-----------------------------------------------------------

void draw_row(const int &length, const int &row)
{
	int col;
	color clr;
	for (col = 0; col < length; col++) {

		clr = get_chequer_colour(row, col);

		fill_rectangle(clr, col * 50, row * 50, 50, 50);
	}
}

//-----------------------------------------------------------
// draw_grid Procedure
// DESCRIPTION: Draws an x by x grid
//-----------------------------------------------------------

void draw_grid(const int &length)
{
	int row;
	for (row = 0; row < length; row++) {
		// Draw a row here
		draw_row(length, row);
	}
}

//-----------------------------------------------------------
// draw_queens Procedure
// DESCRIPTION: Draws a queen on the screen row by row
//-----------------------------------------------------------
void draw_queens(const int *queens, const int &max_row)
{
	int row;
	int x_pos;
	int y_pos;
	string qNo;

	for (row = 0; row < max_row; row++) {
		// X = Column (Horiz)
		x_pos = queens[row] * 50;
		// Y = Row (Vert)
		y_pos = row * 50;

		sprintf(qNo.str, "Q%d", row + 1); // + 1 so not 0-based
		
		/*

		{{ DEBUG ONLY }}

		string qRow;
		string qCol;
		sprintf(qRow.str, "R=%d", row + 1); // + 1 so not 0-based
		sprintf(qCol.str, "C=%d", queens[row] + 1); // + 1 so not 0-based
		draw_text(	qRow.str,
					ColorGreen,
					x_pos,
					y_pos);
		draw_text(	qCol.str,
					ColorGreen,
					x_pos,
					y_pos + 11);
		

		draw_line(	ColorGreen,
					x_pos - 1000,
					y_pos - 1000,
					x_pos + 1000,
					y_pos + 1000 );
		draw_line(	ColorGreen,
					x_pos - 1000,
					y_pos + 1000,
					x_pos + 1000,
					y_pos - 1000 );

		{{ / DEBUG ONLY }}

		*/

		fill_circle(ColorRed,
					x_pos + 25,
					y_pos + 25,
					10);
		draw_text(	qNo.str,
					ColorWhite,
					x_pos + 18,
					y_pos + 21);
	}
}

//-----------------------------------------------------------
// draw_chessboard Procedure
// DESCRIPTION: Draws the queens at their current location
//				and the chequered board
//-----------------------------------------------------------

void draw_chessboard(const ctrl_data &ctrl, const int *queens) {
	clear_screen(ColorBlue);
	draw_grid(ctrl.n);
	draw_queens(queens, ctrl.n);

	string atmptStr;
	sprintf(atmptStr.str, "ATTEMPT: %d", ctrl.attempts);

	// Draw the attempt no as well
	draw_text(atmptStr.str, ColorWhite, 3, screen_height()-10 );

	refresh_screen();
}

//-----------------------------------------------------------
// initialise Function
// DESCRIPTION: Initialises a new game
//-----------------------------------------------------------

ctrl_data initialise()
{
	ctrl_data ctrl;
	// User enters the grid size to open a suitably sized window
	ctrl.n = read_integer_range("	> Enter n to solve: ", 6, 20);

	// Reset values to initial values
	ctrl.attempts = 1;

	string window_title;
	sprintf(window_title.str, "Queens Puzzle - %dx%d",ctrl.n, ctrl.n);

	// Open a window
	open_graphics_window(window_title.str, ctrl.n * 50, ctrl.n * 50 + 13);
	load_default_colors();

	return ctrl;
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                          CHECK
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//-----------------------------------------------------------
// try_placement Function
// DESCRIPTION: Returns true if queen can be placed at the 
//				current cur_row
//-----------------------------------------------------------

bool try_placement(const int &cur_row, int *queens) {
	
	int row;

	// For every row?
	for (row = 0; row < cur_row; row++) {

		// Check if in LoS (i.e. illegal move)
		if (queens[cur_row] == queens[row] || 							// Same Col?
			abs(queens[cur_row] - queens[row]) == abs(cur_row - row)) 	// Same Diag?
			return false;
	
	}

	// Above was passed---not in LoS 
	// Will not attach each other so legal
	return true;

}

//-----------------------------------------------------------
// run_check Procedure
// DESCRIPTION: Runs the recursive, backtracking method for
//				all possible placements
//-----------------------------------------------------------
bool run_check(int row, int *queens, ctrl_data &ctrl) {

	int col;
	int max_row;
	max_row = ctrl.n - 1;

	// Is this row a legal, non-attacking position?
	if (try_placement(row, queens)) {
		// We've reached the last row?
		if (row >= max_row) {
			draw_chessboard(ctrl, queens);
			return true;
		}
		// Otherwise...
		else {
			// For every col on board
			for (col = 0; col <= max_row; col++) {
				// Run in case we get stuck for a while
				process_events(); if ( window_close_requested() ) break;
				// Increase the attempt
				ctrl.attempts++;
				// Shift to next row and assign it that col
				queens[row + 1] = col;
				// Run for next row
				run_check(row + 1, queens, ctrl);
			}
		}
	}
}

//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
//                          MAIN
//++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
int main()
{
	printf("	 *** N-QUEENS PUZZLE *** \n");
	ctrl_data ctrl;
	ctrl = initialise();
	string success_msg;

	// Create the queens array, which will store the
	// row number (index number) and the column number (index value)
	int queens[ctrl.n];

	// Set all queens to column 0.
	int i;
	for (i = 0; i < ctrl.n; i++)
		queens[i] = 0;

	draw_chessboard(ctrl, queens);

	if (run_check(0, queens, ctrl)) // If runcheck successful?
		sprintf(success_msg.str, "SOLUTION FOUND"); // Display Soln.

	do
	{		
		// Flash Message
		draw_text(	success_msg.str,
					ColorRed,
					screen_width() - 115,
					screen_height() - 10);
		refresh_screen();
		delay(500);

		process_events();

	} while ( ! window_close_requested() );
	
	close_audio();

	release_all_resources();
	return 0;
}
