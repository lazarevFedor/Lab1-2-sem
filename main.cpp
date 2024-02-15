#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int choise;
const int SIZE = 30;

void clearStream() {
	cin.clear();
	cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

struct Student{
	string name;
	char sex;
	int group;
	int id;
	int grades[8];
	float averageScore;
};

Student dataBase[SIZE];

Student creatStudent() {
	clearStream();
	Student student;
	getline(cin, student.name);
	cin >> student.sex;
	cin >> student.group; 
	cin >> student.id;
	for (int i = 0; i < 8; i++) cin >> student.grades[i];
	return student;
}

int binSearch(int arr[], int value, int len) {
	int low = 0;
	int high = len - 1;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (value == arr[mid]) {
			return mid;
		}
		else if (value > arr[mid]) {
			low = mid + 1;
		}
		else {
			high = mid - 1;
		}
	}
	return -1;
}

void showStudents(Student dataBase[], int& count) {
	for (int j = 0; j < count; j++) {
		cout << dataBase[j].name << "\t";
		cout << dataBase[j].sex << "\t";
		cout << dataBase[j].group << "\t";
		cout << dataBase[j].id << "\t";
		for (int i = 0; i < 8; i++) {
			cout << dataBase[j].grades[i] << " ";
		}
		cout << "\n\n";
	}
}

float countScore(int grades[8]) {
	float score = 0;
	for (int i = 0; i < 8; i++) {
		score += grades[i];
	}
	score /= 8;
	return score;
}

void topStudents(Student top[SIZE], int &count) {
	int j;
	Student buff;
	for (int i = 1; i < count; i++) {
		buff = top[i];
		j = i - 1;
		while (j >= 0 && top[j].averageScore > buff.averageScore) {
			top[j + 1] = top[j];
			j = j - 1;
		}
		top[j + 1] = buff;
	}
	for (int j = count-1; j >= 0 ; j--) {
		cout << top[j].name << "\t";
		cout << top[j].sex << "\t";
		cout << top[j].group << "\t";
		cout << top[j].id << "\t";
		for (int i = 0; i < 8; i++) {
			cout << top[j].grades[i] << " ";
		}
		cout << "\t" << top[j].averageScore;
		cout << "\n\n";
	}
}

void changeStudent(int &numGroup, int &numId, int &count) {
	Student student;
	int check = -1;
	for (int i = 0; i < count; i++) {
		if (dataBase[i].group == numGroup && dataBase[i].id == numId) {
			student = dataBase[i];
			check = i;
			break;
		}
	}
	if (check == -1) {
		cout << "\nТакого студента нет.\n\n";
	}
	else {
		cout << "\nВыберите данные:\n" <<
			"1) ФИО\n" <<
			"2) Пол\n" <<
			"3) Группа\n" <<
			"4) Номер\n" <<
			"5) Оценки\n" << "-->> ";
		cin >> choise;
		switch (choise){
		case 1:
			cout << "\nВведите данные -->> ";
			student.name = "";
			clearStream();
			getline(cin, student.name);
			break;
		case 2:
			cout << "\nВведите данные -->> ";
			cin >> student.sex;
			break;
		case 3:
			cout << "\nВведите данные -->> ";
			cin >> student.group;
			break;
		case 4:
			cout << "\nВведите данные -->> ";
			cin >> student.id;
			break;
		case 5:
			cout << "\nВведите данные -->> ";
			for (int i = 0; i < 8; i++) {
				cin >> student.grades[i];
			}
			break;
		}
		dataBase[check] = student;
	}
}


int main(){
	setlocale(LC_ALL, "Russian");
	ofstream fout;
	ifstream fin;
	int count = 0, numGroup, numId, countM = 0, countW = 0, countG = 0;
	fin.open("LETI.txt");
	if (!fin.is_open()) {
		cout << "Ошибка открытия файла!!!";
		exit(404);
	}
	else {
		while (!fin.eof()) {
			getline(fin, dataBase[count].name);
			fin >> dataBase[count].sex;
			fin >> dataBase[count].group;
			fin >> dataBase[count].id;
			for (int i = 0; i < 8; i++) {
				fin >> dataBase[count].grades[i];
			}
			count++;
			fin.get();
		}
		cout << "Данные из файла считаны.\n\n";
	}
	fin.close();
	while (true) {
		cout << "1) Создать новую запись\n" <<
			"2) Внести изменения в запись\n" <<
			"3) Вывод всех данных\n" <<
			"4) Вывод информации обо всех студентах группы N\n" <<
			"5) Студенты с наивысшим баллом\n" <<
			"6) Количество студентов мужского и женского пола\n" <<
			"7) Вывод данных успеваемости студентов\n" <<
			"8) Вывод данных о студентах, имеющих номер в списке – k\n" <<
			"9) Выход\n" << "-->> ";
		cin >> choise;
		switch (choise){
		case 1:
			fout.open("LETI.txt", ofstream::app);
			if (!fout.is_open()) {
				cout << "Ошибка открытия файла!!!";
				exit(0);
			}
			else if ((count + 1) > SIZE) {
				cout << "Закончилось место для записи!\n";
			}
			else {
				cout << "\nВведите данные:\n";
				dataBase[count] = creatStudent();
				fout << '\n' << dataBase[count].name << '\n';
				fout << dataBase[count].sex << '\n';
				fout << dataBase[count].group << '\n';
				fout << dataBase[count].id << '\n';
				for (int i = 0; i < 7; i++) {
					fout << dataBase[count].grades[i] << " ";
				}
				fout << dataBase[count].grades[7];
				count++;
			}
			fout.close();
			cout << "\nЗапись создана!\n";
			break;
		case 2:
			cout << "\nВведите номер группы -->> ";
			cin >> numGroup;
			cout << "Введите номер студента в группе -->> ";
			cin >> numId;
			changeStudent(numGroup, numId, count);
			break;
		case 3:
			system("cls");
			showStudents(dataBase, count);
			break;
		case 4:
			cout << "Введите номер группы -->> ";
			cin >> numGroup;
			for (int j = 0; j < count; j++) {
				if (dataBase[j].group == numGroup) {
					cout << dataBase[j].name << "\t";
					cout << dataBase[j].sex << "\t";
					cout << dataBase[j].group << "\t";
					cout << dataBase[j].id << "\t";
					for (int i = 0; i < 8; i++) {
						cout << dataBase[j].grades[i] << " ";
					}
					cout << "\n\n";
					++countG;
				}
			}
			if (countG == 0) {
				cout << "Ни одного студента не найдено.\n";
			}
			break;
		case 5:
			for (int i = 0; i < count; i++) {
				dataBase[i].averageScore = countScore(dataBase[i].grades);
			}
			topStudents(dataBase, count);
			break;
		case 6:
			for (int i = 0; i < count; i++) {
				if (dataBase[i].sex == 'M') {
					countM++;
				}
				else {
					countW++;
				}
			}
			cout << "\nКоличество пацанов: " << countM;
			cout << "\nКоличество девчат: " << countW << "\n";
			break;
		case 7:
			
			break;
		case 8:
			clearStream();
			cout << "\nВведите номер в списке -->> ";
			cin >> numId;
			for (int j = 0; j < count; j++) {
				if (dataBase[j].id == numId) {
					cout << dataBase[j].name << "\t";
					cout << dataBase[j].sex << "\t";
					cout << dataBase[j].group << "\t";
					cout << dataBase[j].id << "\t";
					for (int i = 0; i < 8; i++) {
						cout << dataBase[j].grades[i] << " ";
					}
					cout << "\n\n";
				}
			}
			break;
		case 9:
			exit(0);
		}
	}
	return 0;
}
