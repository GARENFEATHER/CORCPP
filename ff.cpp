#include <iostream>
struct Square {
	bool empty;
	bool valid;
	int color;
	int piece;
    Square(): empty(false), valid(false), color(-1), piece(-1){}
	void moveTo(Square &des);
	void clear();
	void reset();
};
struct board {
	Square b[2][2];
};
int main()
{

}