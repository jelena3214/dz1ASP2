#include <iostream>
#include <cmath>
#include <string>

using namespace std;
int main() {
	string meni = "Unesite opciju:\n"
		"1. Pokreni igru\n"
		"2. Kraj programa";

	int choice;

	while (true) {
		cout << meni;
		cin >> choice;

		if (choice == 1) {

			double starting_point, ending_point;
			int num_of_decimal_places;

			cout << "Unesite opseg bojeva: ";
			cin >> starting_point >> ending_point;
			cout << endl;

			cout << "Unesite broj decimalnih mesta: ";
			cin >> num_of_decimal_places;
			cout << endl;

			double step = 1.0 / pow(10, num_of_decimal_places);

			int num_of_steps = 1;
			double value = starting_point;
			int flag = 0; //0 manj, 1 veci, 2 u dozvoiljenom
			double old_val = value; //vidi ovo jos

			while (true) {
				cout << "Da li je vas broj: " << value;
				cout << endl;

				cin >> flag;
				if (flag == 2) {
					cout << "Pogodio sam!\n" << endl;
					cout << num_of_steps;
					break;
				}
				else if (flag == 1) {
					step *= 2;
					old_val = value;
					value = starting_point + step;
					num_of_steps++;
					if (value > ending_point) {
						cout << "Izasli ste iz datog opsega\n";
						exit(0);
					}
				}
				else {
					double high = value;
					double low = old_val;
					while (1) {
						num_of_steps++;
						double mid = (high + low) / 2;

						cout << "Da li je vas broj: " << mid;
						cout << endl;

						cin >> flag;

						if (flag == 2) {
							cout << "Pogodio sam!" << endl;
							cout << num_of_steps;
							break;
						}
						else if (flag == 1) {
							low = mid + 1.0 / pow(10, num_of_decimal_places);
						}
						else {
							high = mid - 1.0 / pow(10, num_of_decimal_places);
						}
					}
					break;
				}
			}
		}
		else {
			exit(0);
		}
	}
}
