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

Command s1[] = {
//	{CMD, p1, p2, p3},
	{TURN, 40, 0, 0},
	{WAIT, 1, 0, 0},
	{TURN, -45, 0, 0},
	{WAIT, 1, 0, 0},
	{TURN, 90, 0, 0},
	{WAIT, 1, 0, 0},
	{TURN, -180, 0, 0},
	{END, 0, 0, 0}	
};

Command s2[] = {
//	{CMD, p1, p2, p3},
	{TURN, 40, 0, 0},
	{WAIT, 1, 0, 0},
	{TURN, -45, 0, 0},
	{WAIT, 1, 0, 0},
	{TURN, 90, 0, 0},
	{WAIT, 1, 0, 0},
	{TURN, -180, 0, 0},
	{END, 0, 0, 0}
};

Command s3[] = {
//	{CMD, p1, p2, p3},
	{TURN, 40, 0, 0},
	{WAIT, 1, 0, 0},
	{TURN, -45, 0, 0},
	{WAIT, 1, 0, 0},
	{TURN, 90, 0, 0},
	{WAIT, 1, 0, 0},
	{TURN, -180, 0, 0},
	{END, 0, 0, 0}
};

Command s4[] = {
	{JSTK, 1, 1, .5},
	{JSTK, -1, -1, .5},
	{END, 0, 0, 0}
};

Command s5[] = {
	{END, 0, 0, 0}
};

Command s6[] = {
	{END, 0, 0, 0}
};

Command s7[] = {
	{END, 0, 0, 0}
};

Command* scripts[] = { s1, s2, s3, s4, s5, s6, s7 };
