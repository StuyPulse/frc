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

Command s4[] = {
	{JSTK, 1, -1, 1000},
	{END, 0, 0, 0}
};

Command s5[] = {
	{TURN, -45, 0, 0},
	{END, 0, 0, 0}
};

Command s6[] = {
	{END, 0, 0, 0}
};

Command s7[] = {
	{END, 0, 0, 0}
};

Command* scripts[] = { s1, s2, s3, s4, s5, s6, s7 };
