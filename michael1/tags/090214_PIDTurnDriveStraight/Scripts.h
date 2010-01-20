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
/* YO Always subtract .5 from the actual distance.... 
 * If u do not know how to subtract .5, look under this line
 * first, u subtract .1
 * second u do step 1 5 (YES 5 OMG) times OMFG NFW LOL HAHA MUHAHAHA */

	Command s1[] = {
//	{CMD, p1, p2, p3},
	{FWD, 1.5, 0, 0}, //forward 2 feet
	{TURN, 45, 0, 0}, //turn 45
	{FWD, 22.75, 0, 0},
	{TURN, 30, 0, 0},
	{FWD, 2, 0, 0},
	{TURN, 30, 0 ,0},
	{FWD, 2, 0, 0},
	{TURN, 30, 0 ,0},
	{END, 0, 0, 0}
};

Command s2[] = {
//	{CMD, p1, p2, p3},
//	Change back to forward first
	{FWD, 1.3, 0, 0},
	{WAIT, .25, 0, 0},
	{TURN, 45, 0, 0},
	{WAIT, .25, 0, 0},  //HALVED ALL FWDS
	{FWD, 17, 0, 0},
	{TURN, 90, 0, 0},
	{END, 0, 0, 0}
};

Command s3[] = {
//	{CMD, p1, p2, p3},
	{FWD, 2, 0, 0},
	{WAIT, 1, 0, 0},
	{TURN, 45, 0, 0},
	{WAIT, 1, 0, 0},
	{FWD, 5, 0, 0},
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
