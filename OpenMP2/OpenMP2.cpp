#include <iostream>
#include <omp.h>
#include <time.h>

using namespace std;

int main()
{
	setlocale(0, "");
	srand(time(NULL));
	int n;

	cout << "Укажите размерность матрицы: ";
	cin >> n;

	omp_set_dynamic(0);
	omp_set_num_threads(4);

	int** matrix1 = new int* [n];
	int** matrix2 = new int* [n];
	int** sum = new int* [n];

	for (int s = 0; s < n; s++) {
		matrix1[s] = new int[n];
		matrix2[s] = new int[n];
		sum[s] = new int[n];
	}

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			matrix1[i][j] = rand() % 100;
			matrix2[i][j] = rand() % 100;
		}

	double timer = omp_get_wtime();

#pragma omp parallel for
	{
		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
#pragma omp critical
				sum[i][j] = matrix1[i][j] + matrix2[i][j];
	}

	cout << "Время выполнения: " << omp_get_wtime() - timer << " секунд\n";

	cout << "Один поток:\n";

	timer = omp_get_wtime();

	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			sum[i][j] = matrix1[i][j] + matrix2[i][j];

	cout << "Время выполнения: " << omp_get_wtime() - timer << " секунд\n";
	system("PAUSE");
	return 0;
}