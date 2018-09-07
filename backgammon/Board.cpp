#include "Board.h"
#include "framework.h"

Board::Board()
{
}


void Board::Init()
{
    Players_t a = PLAYER_FIRST;
	lines[5] = Line(PLAYER_FIRST, 5);
	lines[7] = Line(PLAYER_FIRST, 3);
	lines[12] = Line(PLAYER_FIRST, 5);
	lines[23] = Line(PLAYER_FIRST, 2);

	lines[19] = Line(PLAYER_SECOND, 5);
	lines[17] = Line(PLAYER_SECOND, 3);
	lines[11] = Line(PLAYER_SECOND, 5);
	lines[0] = Line(PLAYER_SECOND, 2);

	currentOriginIndex = -1;
	//validMovementOptions = {};
}


void Board::DisplayPieces(int joystick_location, int selected_location)
{
    DEBUG("--------------------------------");
    DEBUG("--------------------------------");
    for(int line_index = 0; line_index < LINES_COUNT; line_index++)
    {
        if (joystick_location == line_index)
        {
            DEBUG_NONEWLINE("J");
        }
        else
        {
            DEBUG_NONEWLINE(" ");
        }

        if (selected_location == line_index)
        {
            DEBUG_NONEWLINE("S");
        }
        else
        {
            DEBUG_NONEWLINE(" ");
        }

        Line line = lines[line_index];

        if (line.player != PLAYER_NONE)
        {
            const char* piece;
            if (line.player == PLAYER_FIRST)
            {
                piece = "1";
            }
            if (line.player == PLAYER_SECOND)
            {
                piece = "2";
            }

            for (int i = 0; i < line.pieces; i++)
            {
                DEBUG_NONEWLINE(piece);
            }
        }

        DEBUG("");
    }
}

/*void Board::SetOriginPiece(Player player, int index)
{

}*/


bool Board::Move(int originalIndex, int targetIndex)
{
    Line& fromLine = lines[originalIndex];
    Line& toLine = lines[targetIndex];

    // Eating?
    if ((toLine.player != fromLine.player) &&
        (toLine.player != PLAYER_NONE))
    {
        // TODO: One was eaten

        toLine.pieces = 0;
    }

    toLine.player = fromLine.player;
    fromLine.pieces -= 1;
    toLine.pieces += 1;
}
