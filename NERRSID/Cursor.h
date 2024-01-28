#pragma once

class Cursor
{
private:
	bool CursorSetFlag;
	int PositionXCoordinate;
	int PositionYCoordinate;
	// path to destination
public:
	Cursor();
	~Cursor();
	bool GetCursorSetFlag();
	int GetPositionXCoordinate();
	int GetPositionYCoordinate();

	void GetCursorSetFlag(bool cursorSetFlag);
	void SetPositionXCoordinate(int positionXCoordinate);
	void SetPositionYCoordinate(int positionYCoordinate);
};
