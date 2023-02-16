#include <iostream>

using namespace std;
int comparesQ = 0;
int movesD = 0;

void printMatrixFromArray(int array[], int M, int N) {
    int iter = 0;
    while (iter < (M * N)) {
        if (iter % N == 0) {
            cout << "\n";
        }
        cout << array[iter] << "  ";
        iter += 1;
    }
    cout << "\n";
}

void printClockMatrix(int array[], int M, int N) {
    int **a = new int *[M];
    for (int i = 0; i < M; ++i) {
        a[i] = new int[N];
    }

    int Ibeg = 0, Ifin = 0, Jbeg = 0, Jfin = 0;

    int k = 1;
    int i = 0;
    int j = 0;

    while (k <= N * M) {
        a[i][j] = array[k - 1];
        if (i == Ibeg && j < M - Jfin - 1)
            ++j;
        else if (j == M - Jfin - 1 && i < N - Ifin - 1)
            ++i;
        else if (i == N - Ifin - 1 && j > Jbeg)
            --j;
        else
            --i;

        if ((i == Ibeg + 1) && (j == Jbeg) && (Jbeg != M - Jfin - 1)) {
            ++Ibeg;
            ++Ifin;
            ++Jbeg;
            ++Jfin;
        }
        ++k;
    }

    for (int x = 0; x < M; ++x) {
        for (int y = 0; y < N; ++y)
            cout << a[x][y] << "  ";
        printf("\n");
    }
    cout << "\n";
}

int findSmallestPosition(int list[], int startPosition, int listLength) {
    int smallestPosition = startPosition;

    for (int i = startPosition; i < listLength; i++) {
        if (list[i] < list[smallestPosition])
            smallestPosition = i;
    }
    return smallestPosition;
}

long *selectionSort(int list[], int listLength) {
    long *replace_compare = new long[2];
    for (int i = 0; i < listLength; i++) {
        int smallestPosition = findSmallestPosition(list, i, listLength);
        swap(list[i], list[smallestPosition]);
        if (list[i] != list[smallestPosition]) {
            replace_compare[0] += 1;
        }
        replace_compare[1] += listLength - i;
    }
    return replace_compare;
}

long *insertionSort(int list[], int listLength) {
    long *replace_compare = new long[2];
    for (int i = 1; i < listLength; i++) {
        int j = i - 1;
        while (j >= 0 && list[j] > list[j + 1]) {
            replace_compare[1] += 1;
            replace_compare[0] += 1;
            swap(list[j], list[j + 1]);

            j--;
        }
    }
    return replace_compare;
}

long *shellSort(int list[], int listLength) {
    long *replace_compare = new long[2];
    for (int step = listLength / 2; step > 0; step /= 2) {
        for (int i = step; i < listLength; i += 1) {
            int j = i;
            while (j >= step && list[j - step] > list[i]) {
                replace_compare[0] += 1;
                replace_compare[1] += 1;
                swap(list[j], list[j - step]);
                j -= step;
            }
        }
    }
    return replace_compare;
}

long *quickSort(int *mas, int size) {
    long *replace_compare = new long[2];
    //Указатели в начало и в конец массива
    int i = 0;
    int j = size - 1;

    //Центральный элемент массива
    int mid = mas[size / 2];

    //Делим массив
    do {

        while (mas[i] < mid) {
            i++;
        }

        while (mas[j] > mid) {
            j--;
        }

        //Меняем элементы местами
        if (i <= j) {
            comparesQ += 1;
            if (mas[i] != mas[j]) {
                movesD += 1;
            }

            int tmp = mas[i];
            mas[i] = mas[j];
            mas[j] = tmp;

            i++;
            j--;
        }
    } while (i <= j);


    //Рекурсивные вызовы, если осталось, что сортировать
    if (j > 0) {
        //"Левый кусок"
        quickSort(mas, j + 1);
    }
    if (i < size) {
        //"Првый кусок"
        quickSort(&mas[i], size - i);
    }
    return replace_compare;
}

int main() {
    // Вводим размеры матрицы, M - кол-во столбцов, N - кол-во строк
    int M, N;
    cin >> M;
    cin >> N;
    if (cin.fail()) {
        cout << "Введены недопустимые значения";
        return 0;
    } else if (M > 1000 || N > 1000 || M == 0 || N == 0|| M<=2 || N <=2 || M!=N) {
        cout << "размер матрицы недопустимый";
        return 0;
    }
    //
    auto sizeTryArray = M * N;
    int *tryArray = new int[sizeTryArray];

    //
    for (int i = 0; i < M * N; ++i) {
        tryArray[i] = rand()%10;
    }
    printf("Печатаем начальный массив");
    printMatrixFromArray(tryArray, M, N);

    // Bubble sort подготовка
    int *bubbleArray = new int[sizeTryArray];
    copy_n(tryArray, sizeTryArray, bubbleArray);
    long bubbleCountCompare = 0;
    long bubbleCountMove = 0;
    int temp;

    // Bubble sort алгоритм
    for (int i = 0; i < sizeTryArray - 1; ++i) {
        for (int j = 0; j < sizeTryArray - i - 1; ++j) {
            bubbleCountCompare += 1;
            if (bubbleArray[j] > bubbleArray[j + 1]) {
                bubbleCountMove += 1;

                temp = bubbleArray[j];
                bubbleArray[j] = bubbleArray[j + 1];
                bubbleArray[j + 1] = temp;
            }
        }
    }

//    printMatrixFromArray(tryArray, M, N);
    printf("Печатаем Bubble\n");
    printClockMatrix(bubbleArray, M, N);

    // отбор
    int *choiceArray = new int[sizeTryArray];
    copy_n(tryArray, sizeTryArray, choiceArray);
    long choiceCountCompare = 0;
    long choiceCountMove = 0;
    long *arr = selectionSort(choiceArray, sizeTryArray);
    choiceCountMove = arr[0];
    choiceCountCompare = arr[1];
    printf("Печатаем Choice\n");
    printClockMatrix(choiceArray, M, N);


    //вставка
    int *insertArray = new int[sizeTryArray];
    copy_n(tryArray, sizeTryArray, insertArray);
    long insertCountCompare = 0;
    long insertCountMove = 0;
    long *arr2 = insertionSort(insertArray, sizeTryArray);
    insertCountMove = arr2[0];
    insertCountCompare = arr2[1];
    printf("Печатаем Insert\n");
    printClockMatrix(insertArray, M, N);


    // Шелл
    int *shellArray = new int[sizeTryArray];
    copy_n(tryArray, sizeTryArray, shellArray);
    long shellCountCompare = 0;
    long shellCountMove = 0;
    long *arr3 = shellSort(shellArray, sizeTryArray);
    shellCountMove = arr3[0];
    shellCountCompare = arr3[1];
    printf("Печатаем Shell\n");
    printClockMatrix(bubbleArray, M, N);



    // Быстрая сортировка
    int *quickArray = new int[sizeTryArray];
    copy_n(tryArray, sizeTryArray, quickArray);
    long quickCountCompare = 0;
    long quickCountMove = 0;
    long *arr4 = quickSort(quickArray, sizeTryArray);
    quickCountMove = arr4[0];
    quickCountCompare = arr4[1];
    printf("Печатаем Quick\n");
    printClockMatrix(choiceArray, M, N);
    //
    string titles[] = {"Пузырёк", "Отбор  ", "Вставка", "Шелл   ", "Быстрая"};
    long compares[] = {bubbleCountCompare, choiceCountCompare, insertCountCompare, shellCountCompare, comparesQ};
    long moves[] = {bubbleCountMove, choiceCountMove, insertCountMove, shellCountMove, movesD};

    printf("|==========|=====================|==================|\n");
    printf("| Название | Кол-во перестановок | Кол-во сравнений |\n");
    printf("|==========|=====================|==================|\n");

    for (int i = 0; i < 5; ++i) {
        printf("| %s %2s %10ld %10s %9ld %8s\n", titles[i].c_str(), "|", moves[i], "|", compares[i], "|");

    }
    printf("|==========|=====================|==================|\n");
    return 0;
}
