#define END 0
#define TURN 1
#define JSTK 2
#define WAIT 3
#define FWD 4

typedef struct {
	int cmd;
	float param1;
	float param2;
	float param3;
} Command;

//Counter-clockwise corner routine
Command s1[] = {
//	{CMD, p1, p2, p3},
	{FWD, 1.3, 0, 0},
	{WAIT, .25, 0, 0},
	{TURN, -45, 0, 0},
	{WAIT, .25, 0, 0},
	{FWD, 17, 0, 0},
	{WAIT, .25, 0, 0},
	{TURN, -90, 0, 0},
	{END, 0, 0, 0}
};

//Clock-wise corner routine
Command s2[] = {
//	{CMD, p1, p2, p3},
//	Change back to forward first
	{FWD, 1.3, 0, 0},
	{WAIT, .25, 0, 0},
	{TURN, 45, 0, 0},
	{WAIT, .25, 0, 0},
	{FWD, 17, 0, 0},
	{WAIT, .25, 0, 0},
	{TURN, 90, 0, 0},
	{END, 0, 0, 0}
};

//Foward 23
Command s3[] = {
//	{CMD, p1, p2, p3},
	{FWD, 23, 0, 0},
	{END, 0, 0, 0}
};

//From left lower to left top
Command s4[] = {
	{FWD, 1.3, 0, 0},
	{WAIT, .25, 0, 0},
	{TURN, -45, 0, 0},
	{WAIT, .25, 0, 0},
	{FWD, 18, 0, 0},
	{WAIT, .25, 0, 0},
	{TURN, -45, 0, 0},
	{END, 0, 0, 0}
};

//top middle to top left
Command s5[] = {
	{FWD, 1.3, 0, 0},
	{WAIT, .25, 0, 0},
	{TURN, 90, 0, 0},
	{WAIT, .25, 0, 0},
	{FWD, 17, 0, 0},
	{WAIT, .25, 0, 0},
	{TURN, 45, 0, 0},
	{END, 0, 0, 0}
};

//lower right to top right 
Command s6[] = {
	{FWD, 1.3, 0, 0},
	{WAIT, .25, 0, 0},
	{TURN, 45, 0, 0},
	{WAIT, .25, 0, 0},
	{FWD, 17, 0, 0},
	{WAIT, .25, 0, 0},
	{TURN, 45, 0, 0},
	{END, 0, 0, 0}
};

// top middle to top right
Command s7[] = {
	{FWD, 1.3, 0, 0},
	{WAIT, .25, 0, 0},
	{TURN, 90, 0, 0},
	{WAIT, .25, 0, 0},
	{FWD, 16, 0, 0},
	{WAIT, .25, 0, 0},
	{TURN, 45, 0, 0},
	{END, 0, 0, 0}
};

Command s0[] = {
	{FWD, 15, 0, 0},
	{WAIT, 0.25, 0, 0},
	{JSTK, 1, -1, 15},
	{END, 0, 0, 0}
};

Command* scripts[] = {s0, s1, s2, s3, s4, s5, s6, s7};
