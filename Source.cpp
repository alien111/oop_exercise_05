#include <algorithm>
#include <iostream>

#include "DobriyArray.h"

void menu() {
	std::cout << "0 : EXIT\n";
	std::cout << "1 : GO THROUGH VECTOR WITH ITERATOR AND INPUT DATA\n";
	std::cout << "2 : GET ITEM CENTER BY INDEX\n";
	std::cout << "3 : GET AMOUNT OF OBJECTS WITH SQUARE LESS THAN...\n";
	std::cout << "4 : GO THROUGH VECTOR WITH ITERATOR AND SHOW EVERY STEP\n";
	std::cout << "5 : GO THROUGH VECTOR WITH ITERATOR AND INSERT A NEW OBJECT BEFORE THIS ONE\n";
	std::cout << "6 : GO THROUGH VECTOR WITH ITERATOR AND ERASE THIS OBJECT\n";
	std::cout << "> ";
}

int main() {


	int cmd;
	bool doWeHaveAVector = false;

	std::cout << "Enter size of your vector : ";
	int size;
	std::cin >> size;

	containers::DobriyArray< rectangle<int> > Vector(size);

	while (true) {
		menu();
		std::cin >> cmd;
		if (cmd == 0) return 0;
		else if (cmd == 1) {
			for (int i = 0; i < Vector.getSize(); i++) {
				std::cout << "Enter vertices : \n";
				rectangle<int> rect(std::cin);
				Vector.push_back(rect);
			} 
		} else if (cmd == 2) {
			std::cout << "Enter index : ";
			int index;
			std::cin >> index;
			std::cout << Vector[index].center();
		} else if (cmd == 3) {
			int res = 0;
			std::cout << "Enter your square : ";
			double square;
			std::cin >> square;

			int cmdcmd;
			std::cout << "Do you want to use std::count_if? : 1 - yes; 0 - no; : ";
			std::cin >> cmdcmd;

			if (cmdcmd == 1) res = std::count_if(Vector.begin(), Vector.end(), [square](rectangle<int> i) {return i.area() < square;});
			else {
				auto it = Vector.begin();
				auto end = Vector.end();

				while (it != end) {
					if ((*it).area() < square) res++;
					++it;
				}
			}

			std::cout << "Amount is " << res << '\n';
		} else if (cmd == 4) {
			int cmdcmd;
			std::cout << "Do you want to use std::for_each? : 1 - yes; 0 - no; : ";
			std::cin >> cmdcmd;

			if (cmdcmd == 1) std::for_each(Vector.begin(), Vector.end(), [](rectangle<int> i) -> void{i.print();});
			else {
				auto it = Vector.begin();
				auto end = Vector.end();

				int n = 0; 

				while (it != end) {
					std::cout << "___OBJECT_" << n << "__\n";
					std::cout << *it;
					++it;
					n++;
				}

			}

		} else if (cmd == 5) {
			std::cout << "Enter vertices of object you want to delete : "; 
			rectangle<int> toDelete(std::cin);

			std::cout << "Enter vertices of object you want to insert : "; 
			rectangle<int> toInsert(std::cin);
			
			auto it = Vector.begin();
			auto end = Vector.end();

			while (it != end) {
				if (*it == toDelete) {
					Vector.insert(it, toInsert);
					break;
				}
				++it;
			}

			it = Vector.begin();
			end = Vector.end();

			std::cout << "Now vector is like : \n";
			int n = 0;

			while (it != end) {
				std::cout << "___OBJECT_" << n << "__\n";
				std::cout << *it;
				++it;
				n++;
			}
		} else if (cmd == 6) {
			std::cout << "Enter vertices of object you want to erase : "; 
			rectangle<int> toDelete(std::cin);

			auto it = Vector.begin();
			auto end = Vector.end();

			while (it != end) {
				if (*it == toDelete) {
					Vector.erase(it);
				}
				++it;
			}

			it = Vector.begin();

			std::cout << "Now vector is like : \n";
			int n = 0;

			while (it != end) {
				std::cout << "___OBJECT_" << n << "__\n";
				std::cout << *it;
				++it;
				n++;
			}
		}  
	}
 	

}
