#include <iostream>
#include <string>
#include <cmath>
#include <ctime>
#include <random>
using namespace std;

int find_letter(char letter, string alphabet) {
	for (int j = 0; j < alphabet.size(); j++) {
		if (letter == alphabet[j]) return j;
	}
	return -1;
}

unsigned long long key_generator(unsigned long long int p, unsigned long long int g) {
	srand(time(NULL));
	int a = 1 + rand() % 21;       //Случайное число, которое знает только Алиса
	int b = 1 + rand() % 21;       //Случайное число, которое знает только Боб
	cout << endl << "Число, которое знает только Алиса: " << a << endl;
	cout << endl << "Число, которое знает только Боб: " << b << endl;
	unsigned long long int A = pow(g, a);
	A = A % p;
	unsigned long long int B = pow(g, b);
	B = B % p;
	cout << endl << "Алиса знает: a = " << a << " и A = " << g << "^" << a << " mod " << p << " = " << A << endl;
	cout << "   Не знает: b, но знает" << " B = " << g << "^b mod " << p << " = " << B << endl;
	cout << endl << "Боб знает: b = " << b << " и B = " << g << "^" << b << " mod " << p << " = " << B << endl;
	cout << " Не знает: a, но знает" << " A = " << g << "^a mod " << p << " = " << A << endl;
	cout << endl << "Шпион знает: " << "A = " << g << "^a mod " << p << " = " << A << endl;
	cout << "Шпион знает: " << "B = " << g << "^b mod " << p << " = " << B << endl;
	cout << "   Не знает: a и b " << endl;
	unsigned long long int Alice_key = pow(B, a);
	Alice_key = Alice_key % p; //Ключ, получившийся у Алисы
	unsigned long long int Bob_key = pow(A, b);
	Bob_key = Bob_key % p; //Ключ, получившийся у Боба
	if (Alice_key == Bob_key) {
		cout << endl << "Алиса знает: p = " << p << ", g = " << g << ", a = " << a << ", A = " << A << ", B = " << B << " и свой ключ s1 = " << Alice_key << endl;
		cout << "   не знает: b" << endl;
		cout << endl << "Боб знает: p = " << p << ", g = " << g << ", b = " << b << ", A = " << A << ", B = " << B << " и свой ключ s2 = " << Bob_key << endl;
		cout << " не знает: a" << endl;
		cout << endl << "Шпион знает: p = " << p << ", g = " << g << ", A = " << A << ", B = " << B << endl;
		cout << "   не знает: a, b, ключи s1 и s2" << endl;
		cout << endl << "Таким образом, Алиса и боб получили общий одинаковый ключ, который знают только они и с его помощью Алиса передаст Бобу сообщение через шифр Цезаря" << endl;
		return Alice_key;
	}
	else {
		cout << "Ошибка, ключи не совпадают, возможно числа слишком велики";
		exit(0);
	}
}
string to_Bob(string message, unsigned long long int key) {
	string low_alphabet = " abcdefghijklmnopqrstuvwxyz";
	string big_alphabet = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string numbers = "0123456789";
	int j;
	for (int i = 0; i < message.size(); i++) {
		j = find_letter(message[i], low_alphabet);
		if (j == -1) {
			j = find_letter(message[i], big_alphabet);
			if (j == -1) {
				j = find_letter(message[i], numbers);
				if (j == -1) {
					cout << endl << "В сообщении есть буква не существующая в алфавите!";
					exit(0);
				}
				message[i] = numbers[(key + j) % numbers.size()];
			}
			else message[i] = big_alphabet[(key + j) % big_alphabet.size()];
		}
		else message[i] = low_alphabet[(key + j) % low_alphabet.size()];
	}
	cout << endl << "Алиса отправила: " << message << endl;
	return message;
}
void from_Alice(string message, unsigned long long int key) {
	string low_alphabet = " abcdefghijklmnopqrstuvwxyz";
	string big_alphabet = " ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	string numbers = "0123456789";
	int j;
	for (int i = 0; i < message.size(); i++) {
		j = find_letter(message[i], low_alphabet);
		if (j == -1) {
			j = find_letter(message[i], big_alphabet);
			if (j == -1) {
				j = find_letter(message[i], numbers);
				if (j == -1) {
					cout << endl << "В сообщении есть буква не существующая в алфавите!";
					exit(0);
				}
				message[i] = numbers[(j - key + numbers.size()) % numbers.size()];
			}
			else message[i] = big_alphabet[(j - key + big_alphabet.size()) % big_alphabet.size()];
		}
		else message[i] = low_alphabet[(j - key + low_alphabet.size()) % low_alphabet.size()];
	}
	cout << endl << "Боб получил: " << message << endl;
}
int main() {
	setlocale(0, "");
	unsigned long long int p;
	unsigned long long int g;
	cout << "Введите два числа через пробел, которые будут известны Алисе, Бобу и шпиону в диапазоне от 0 до 18446744073709551615 (max 20 цифр): ";
	cin >> p >> g;
	unsigned long long int key = key_generator(p, g);
	string message;
	cout << endl << "Введите сообщение, которое Алиса отправит Бобу шифром Цезаря: ";
	while (isspace(cin.peek())) cin.get();
	getline(cin, message);
	message = to_Bob(message, key);
	from_Alice(message, key);
}