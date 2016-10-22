#define WIDTH 7
#define HEIGHT 7
#define tile 32

// stores two values in one place for ease of access
class point {
public:
	point () {
		a = 0;
		b = 0;
	}
	
	point (int c, int d) {
		a = c;
		b = d;
	}
	
	int a;
	int b;
};

// allows addition of points in form <point> = <point1> + <point2>
point operator+(const point &p1, const point &p2){
	point temp  = p1;
	temp.a += p2.a;
	temp.b += p2.b;
	
	return temp;
}

// stores data for a charchter
class person {
public:
	person () {
		loc.a = 2;
		loc.b = 2;
		hp = 10;
	}
	
	int getX (){ return loc.a; }
	int getY (){ return loc.b; }
	point getLoc (){ return loc; }
	int getHp (){ return hp; }
	
	void giveHp (int heal) { hp += heal; }
	
	void move (point dest) {
		loc.a = dest.a;
		loc.b = dest.b;
	}
private:
	point loc;
	int hp;
};

// door to different areas
class door {
public:
	door () {
		myLoc = point(-1,-1);
		goesToLoc = point(-1,-1);
		roomTo = -1;
	}
	
	door (point here, point there, int where) : myLoc(here), goesToLoc(there), roomTo (where) { }
	
	point getLoc () { return myLoc; }
	point getDest () { return goesToLoc; }
	int getRoomTo () { return roomTo; }
private:
	point myLoc;
	point goesToLoc;
	int roomTo;
};

// areas made here
//field needs to be made private, no idea how to return 2d array for getter
class room {
public:
	room () {
		id = -1;
		for (int i = 0; i < XSIZE; i += 1){
			for (int j = 0; j < YSIZE; j += 1){
				field[i][j] = 0;
			}
		}
	}
	
	room (int me, door enter) {
		room();
		id = me;
		door1 = enter;
		field[door1.getLoc().a][door1.getLoc().b] = 7;
	}
	
	int getId () { return id; }
	door getDoor() { return door1; }
	
	int field[XSIZE][YSIZE];
private:
	door door1;
	int id;
};


room field;
room f1(1, door(point(3,6), point(3,5), 2)); // dest points are backwards but it works
room f2(2, door(point(3,0), point(3,1), 1)); // i dont know why
