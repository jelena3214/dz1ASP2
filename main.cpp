#include <iostream>
#include <cmath>

using namespace std;
//Proveriti smisao, dodati da se ponavlja u krug, meni?????
int main() {
	double starting_point, ending_popint;
	int num_of_decimal_places;

	double acceptable_accuracy;

	cout << "Unesite opseg bojeva: ";
	cin >> starting_point >> ending_popint;
	cout << endl;

	cout << "Unesite broj decimalnih mesta: ";
	cin >> num_of_decimal_places;
	cout << endl;

	cout << "Unesite prihvatljivu gresku : ";
	cin >> acceptable_accuracy;
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
			cout << "Pogodio sam!" << endl;
			cout << num_of_steps;
			break;
		}
		else if(flag == 1){
			step *= 2;
			old_val = value;
			value = starting_point + step;
			num_of_steps++;
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