#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int extractNom(const string &line, double arr[]) {
  int count = 0;
  string current = "";
  bool inNumber = false;
  bool hasDot = false;
  bool hasDigit = false;

  for (int i = 0; i <= line.size(); i++) {
    char c = (i < line.size()) ? line[i] : ' ';

    if (isdigit(c)) {
      current += c;
      inNumber = true;
      hasDigit = true;
    } else if (c == '-' && !inNumber) {
      current += c;
      inNumber = true;
    } else if (c == '.' && inNumber && !hasDot) {
      current += c;
      hasDot = true;
    } else {
      if (inNumber && hasDigit) {
        arr[count++] = atof(current.c_str());
      }
      current = "";
      inNumber = false;
      hasDot = false;
      hasDigit = false;
    }
  }
  return count;
}

double arefSum(double arr[], int n) {
  double s = 0;
  for (int i = 0; i < n; i++)
    s += arr[i];
  return s / n;
}

double geomSum(double arr[], int n) {
  double p = 1;
  for (int i = 0; i < n; i++) {
    if (arr[i] <= 0)
      return -1;
    p *= arr[i];
  }
  return pow(p, 1.0 / n);
}

int main() {
  ifstream fin("in.txt");
  ofstream fout("out.txt");

  if (!fin.is_open()) {
    cout << "Помилка відкриття in.txt\n";
    return 1;
  }

  string line;
  double nums[100];

  cout << "Вміст файлу in.txt:\n";

  while (getline(fin, line)) {

    // Показуємо рядок, як він є у файлі
    cout << line << endl;

    // Витягуємо числа
    int count = extractNom(line, nums);

    if (count == 0) {
      fout << "У рядку немає чисел\n";
      continue;
    }

    double a = arefSum(nums, count);
    double g = geomSum(nums, count);

    // Вивід на екран
    cout << "   Числа: ";
    for (int i = 0; i < count; i++)
      cout << nums[i] << " ";

    cout << "\n   Середнє арифметичне: " << a;

    if (g < 0)
      cout << "\n   Геометричне: не визначене";
    else
      cout << "\n   Геометричне: " << g;

    cout << "\n----------------------\n";

    fout << "Числа: ";
    for (int i = 0; i < count; i++)
      fout << nums[i] << " ";
    fout << "\nСереднє арифметичне: " << a << "\n";

    if (g < 0)
      fout << "Середнє геометричне: не визначене\n";
    else
      fout << "Середнє геометричне: " << g << "\n";

    fout << "-----------------------------\n";
  }

  return 0;
}
