#include <vector>



class Cursor {
private:
	double lastx, lasty;
	bool first_move = true;

public:
	Cursor();

	double get_lastx();
	double get_lasty();

	std::pair<double, double> get_offset(double new_x, double new_y);

	void update(double new_x, double new_y);
};



