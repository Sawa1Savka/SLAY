#include <iostream>
using namespace std;

void result(double* x, int iteration, int row)
{
    cout << "Ответ:" << endl;
    for (int i = 0; i < row; i++) {
        cout << "x" << i + 1 << " = " << x[i] << endl;
    }
    cout << "Итераций: " << iteration << endl;
    }

void simple_iteration(int row, double **array)
{
    double sum, eps, norm;
    int iteration = 0;
    double* x = new double[row];
    double* xo = new double[row];
    double* xx = new double[row];

    cout << "Получить решение СЛАУ с точностью" << endl;
    cin >> eps;
           
    do
    {
        for (int i = 0; i < row; i++) {
            x[i] = 0; // Начальное приближение решения
            sum = 0.0;
            for (int j = 0; j < row; j++) {
                if (i != j) {
                    sum += array[i][j] * x[j];
                }
            }
            x[i] = (array[i][3] - sum) / array[i][i];
        }

        norm = 0.0;

        for (int i = 0; i < row; i++) {
            xx[i] = abs(x[i] - xo[i]);
        }

        for (int i = 0; i < row; i++) {
            norm = max(norm,xx[i]);
            xo[i] = x[i];
        }
        
        iteration++;
        cout << iteration << endl;
    }

    while (norm > eps);
    delete[] array,xo;
    result(x, iteration, row);
}

int main()
{
    setlocale(LC_ALL, "ru");

    int row, column, iteration;
        double sum, not0, number;
        start:
        cout << "Вас преветствует консольное приложение по решению СЛАУ (системы линейных алгебраических уравнений) методом простой итерации\n"<< endl <<"Введите количество переменных в СЛАУ (системы линейных алгебраических уравнений): ";
        cin >> row;
        if (cin.fail() or row <= 0) {
            cin.clear();
            cin.ignore(255, '\n');
            cout << "Вы ввели неверное значение, введите целое положительное число" << endl;
            goto start;
        }
       
        column = row+1; 
        double **array = new double* [row];
        double* x = new double[row];
        for (int i = 0; i < row; i++)
        {
            array[i] = new double[column];
        }
        cout << "Заполните СЛАУ" << endl;
        for (int i = 0; i < row; i++)
        {                        
            for (int j = 0; j < column; j++)
            {
                repeat:
                if (j == column-1)
                {
                    cout << "Введите B" << i + 1 << " :";
                    cin >> number;
                    if (cin.fail()) {
                        cin.clear();
                        cin.ignore(255,'\n');
                        cout << "Введите число "<< endl;
                        goto repeat;
                    }
                    else {
                        array[i][j] = number;
                    }
                }
                else
                {
                    cout << "Введите A" << i + 1 << j + 1 << " :";
                    cin >> number;
                   if (cin.fail()) {
                        cin.clear();
                        cin.ignore(255,'\n');
                        cout << "Введите число "<< endl;
                        goto repeat;
                    }
                    else {
                        array[i][j] = number;
                    }
                                        
                }
            }
        }

        for (int i = 0; i < row; i++)
        {
            for (int j = 0; j < column; j++)
            {
                cout << array[i][j] << "\t";
            }
            cout << endl;
        }
        // Проверка сходимости
        for (int i = 0; i < row; i++) {
            sum = 0;
            not0 = 0;
            for (int j = 0; j < row; j++) {
                if (i != j) {
                    sum += abs(array[i][j]);
                }
                not0 += abs(array[i][j]);
            }
            if (abs(array[i][i]) < sum) {
                cout << "Матрица не удовлетворяет условию сходимости." << endl;
                goto start;  // переход к началу программы
            }
            if(not0 == 0) {
                cout << "Одна из сток заполнена 0." << endl;
                goto start;  // переход к началу программы
            }
            
        }  
        
        simple_iteration(row, array);
        
        return 0;
}