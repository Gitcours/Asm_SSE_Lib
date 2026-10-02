#include <iostream>

#include "Vec4.h"
#include "Vec3.h"

int main() {


	Vec3 a(25, 48, 15);
	Vec3 b(84, 14, 96);

	Vec3 c(a + b);

	std::cout << c.x() << " " << c.y() << " " << c.z();

	return 0;
}