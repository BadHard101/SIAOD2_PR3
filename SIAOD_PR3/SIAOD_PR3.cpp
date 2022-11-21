#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <vector>
#include <string>
using namespace std;

// пример функции обработки, которая выводит индекс начала найденного образца
int f(size_t i)
{
    //printf("%d\n", i);
    return 1;
}
// str строка поиска.
// obr образец, который ищем.
// pi массив длин префиксов для образца (минимум  сколько символов в образце).
// int f(size_t i) когда образец найден, вызывается эта функция, 
// ей передается индекс начала найденного в str образца.
// функция возвращает 0, если надо прекратить поиск и 1, если надо продолжить.
void prefix_find(char* str, char* obr, size_t* pi, int (*f)(size_t), int& counter)
{
    pi[0] = 0;     // в i-м элементе (его индекс i-1) количество совпавших 
                 // символов в начале образца и в конце подстроки длины i. 
                 // p[0]=0 всегда, p[1]=1, если начинается с двух одинаковых 
    size_t l;    // будет длина образца
    // заполняем массив длин префиксов для образца
    for (l = 1; obr[l]; ++l)
    {
        size_t j = pi[l - 1];
        while ((j > 0) && (obr[l] != obr[j])) // не равны
            j = pi[j - 1];	         // берем ранее рассчитанное значение (начиная с максимально возможных)
        if (obr[l] == obr[j])      // равны 
            ++j;
        pi[l] = j;
    }
    size_t j = 0; // количество совпавших символов, оно же индекс сравниваемого 
    // символа в образце. В строке сравниваемый символ будет иметь индекс i
    for (size_t i = 0; str[i]; ++i)
    {
        while ((j > 0) && (str[i] != obr[j]))
            // Очередной символ строки не совпал с символом в образце. Сдвигаем образец, 
            // причем точно знаем, что первые j символов образца совпали с символами строки 
            // и надо сравнить j+1й символ образца (его индекс j) с i+1м символом строки.
            j = pi[j - 1];    // если j=0, то достигли начала образца и цикл следует прервать

        if (str[i] == obr[j]) // есть совпадение очередного символа 
            ++j;              // увеличиваем длину совпавшего фрагмента на 1
        if (j == l) {
            if (!f(i - l + 1)) // образец найден, вызовем функцию обработки
                return;  // и выйдем из процедуры, если она вернет 0.
            counter++;
        }
    }
}

vector<char>* get_last_word(string str) {
    vector<char> * last_word = new vector<char>();
    reverse(str.begin(), str.end());
    for (auto& i : str) {
        if (isalpha(i)) {
            last_word->push_back(i);
        }
        else if (last_word->size() > 0)
            break;
    }
    return last_word;
}

int main()
{
    cout << "Enter text: ";
    string text;
    getline(cin, text);

    char str[] = "Aba bala ba, da ba la bada la ba! Bala bla bada ba.";
    string string_str = str;

    strcpy(str, text.c_str());

    vector<char>* last_word = get_last_word(string_str);
    char * obr = new char[65546]();


    for (int i = 0; i < last_word->size(); i++)
        obr[i] = last_word->at(last_word->size()-i-1);

    cout << "Last word finded: " << obr << endl;

    size_t * pi = new size_t();
    int counter = 0;
    prefix_find(str, obr, pi, f, counter);

    cout << "Word (" << obr << ") was founded in text for " << counter << " times.";
}