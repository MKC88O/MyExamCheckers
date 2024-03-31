// MyExamCheckers.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//Автор: Фёдоров-Марущак Максим Юрьевич. Группа ПВ312.

#include <iostream>
#include <windows.h>
#include <cmath>
#include <ctime>
#include <string>
#include "WinMessage.h"

using namespace std;

// объявляем перечисление с возможными типами на доске

/// <summary>
/// Перечисление с возможными типами на доске
/// </summary>
enum Checkers 
{ 
    /// <summary>
    /// EMPTY - Пустая клетка.
    /// </summary>
    EMPTY,
    /// <summary>
    /// WHITE - Белая шашка.
    /// </summary>
    WHITE, 
    /// <summary>
    /// BLACK - Черная шашка.
    /// </summary>
    BLACK,
    /// <summary>
    /// WHITE_KING - Белая дамка.
    /// </summary>
    WHITE_KING, 
    /// <summary>
    /// BLACK_KING - Черная дамка.
    /// </summary>
    BLACK_KING, 
    /// <summary>
    /// SIZEb - Размер доски (8 * 8 клеток)
    /// </summary>
    SIZEb = 8 
};

//создаем структуру для задачи координат хода
/// <summary>
/// Структура для передачи координат хода
/// </summary>
struct Turn
{
    /// <summary>
    /// Поле fromCol типа 'char' предназначено для передачи координат столбцов двумерного массива в виде литеры
    ///  английского алфавита от 'a' до 'h' и относится к клетке ИЗ которой делается ход.    
    /// </summary>
    char fromCol;
    /// <summary>
    /// Поле toCol типа 'char' предназначено для передачи координат столбцов двумерного массива в виде литеры
    /// английского алфавита от 'a' до 'h' и относится к клетке В которую делается ход.
    /// </summary>
    char toCol;
    /// <summary>
    /// Поле fromRow типа 'int' предназначено для передачи координат рядов двумерного массива в виде целых 
    /// чисел от 1 до 8. Относится к клетке ИЗ которой делается ход.
    /// </summary>
    int fromRow;
    /// <summary>
    /// Поле toRow типа 'int' предназначено для передачи координат рядов двумерного массива в виде целых 
    /// чисел от 1 до 8. Относится к клетке В которую делается ход.
    /// </summary>
    int toRow;
};

//делаем прототипы функций:

/// <summary>
/// Функция которая расставляет шашки.
/// </summary>
/// <param name="board">Текущее состояние доски.</param>
void configBoard(int board[SIZEb][SIZEb]);//функция которая расставляет шашки

/// <summary>
/// Отрисовка доски(её изображение).
/// </summary>
/// <param name="board">Текущее состояние доски.</param>
/// <param name="kletkaSize">Размер клетки и которых состоит доска(количество пробелов).</param>
/// <param name="whiteTotal">Счетчик для белых шашек для отображения счета игры (НЕ количество битых белых шашек, а количество
/// которое белые шашки побили.</param>
/// <param name="blackTotal">Счетчик для черных шашек для отображения счета игры (НЕ количество битых черных шашек, а количество
/// которое черные шашки побили.</param>
void boardCheckers(int board[SIZEb][SIZEb], int kletkaSize, int whiteTotal, int blackTotal);//отрисовка доски

/// <summary>
/// Функция для проверки возможности хода( не выходит ли шашка за пределы доски, не ходит ли на занятую клетку или но большее количество клеток 
/// чем ей разрешено.
/// </summary>
/// <param name="board">Текущее состояние доски.</param>
/// <param name="nowPlay">Проверка текущего игрока.</param>
/// <param name="turn">Параметр отвечающий за координаты хода(координаты погоризотали клетки ИЗ которой делается ход,
/// координаты по вертикали клетки ИЗ которой делается ход, координаты погоризотали клетки В которую делается ход, координаты по вертикали клетки В которой делается ход.</param>
/// <returns>Возвращает тру если все условия соблюдены и шашка может сделать ход.</returns>
bool potentialTurn(int board[SIZEb][SIZEb], int nowPlay, Turn turn);//функция для проверки возможности хода

/// <summary>
/// Функция выполняющая ход.
/// </summary>
/// <param name="board">Текущее состояние доски.</param>
/// <param name="turn">Параметр отвечающий за координаты хода(координаты погоризотали клетки ИЗ которой делается ход,
/// координаты по вертикали клетки ИЗ которой делается ход, координаты погоризотали клетки В которую делается ход, координаты по вертикали клетки В которой делается ход.</param>
/// <param name="nowPlay">Проверка текущего игрока.</param>
/// <param name="whiteTotal">Счетчик для белых шашек для отображения счета игры (НЕ количество битых белых шашек, а количество
/// которое белые шашки побили.</param>
/// <param name="blackTotal">Счетчик для черных шашек для отображения счета игры (НЕ количество битых черных шашек, а количество
/// которое черные шашки побили.</param>
void makeTurn(int board[SIZEb][SIZEb], Turn turn, int nowPlay, int& whiteTotal, int& blackTotal);//функция выполняющая сам ход

/// <summary>
/// Функция проверяющая возможность бить несколько раз подряд(2 и больше).
/// </summary>
/// <param name="board">Текущее состояние доски.</param>
/// <param name="row">Координаты клетки по вертикали.</param>
/// <param name="col">Координаты клетки по горизонтали.</param>
/// <param name="nowPlay">Проверка текущего игрока.</param>
/// <returns>Функция возвращает тру, если на расстоянии одной клетки от шашки, совершившей ход-битье, есть шашка противника и при этом 
/// следующаая клетка пустая.</returns>
bool beatMore(int board[SIZEb][SIZEb], int row, int col, int nowPlay);//функция проверяющая возможность бить несколько раз подряд(2 и больше)

/// <summary>
/// Функция проверяющая победу одного из игроков.
/// </summary>
/// <param name="board">Текущее состояние доски. </param>
/// <param name="nowPlay">Проверка текущего игрока.</param>
/// <returns>Функция проверяет наличие шашек текущего игрока в текущем соостоянии доски и возвращяет тру если шашки есть.
/// В противном случае объявляет победу другого игрока. </returns>
bool Win(int board[SIZEb][SIZEb], int nowPlay);//функция проверяющая победу одного из игроков




/////////////////////////////////////////////////////////////////////////////  M  A  I  N  /////////////////////////////////////////////////////////////////////////////////////////////
int main() {
    Turn turn;

    //объявляем переменные которые будут хранить счет игры
    int whiteTotal = 0;
    int blackTotal = 0;


    // объявляем двумерный массив который будет доской
    int board[SIZEb][SIZEb];

    //расставляем шашки на доске
    configBoard(board);

    // выводим доску перед началом игры 
    boardCheckers(board, 6, whiteTotal, blackTotal);

    //объявляем переменную в которой будет хранится информация о текущем игроке(первыми ходят белые)
    int nowPlay = WHITE;

    //запускаем основной цикл игры
    while (true)
    {
        //выводим информацию о том чей сейчас ход
        cout << "\n\n\n";
        cout << "\t\t\t\t\t\t\t\t\t\033[5;37m" << (nowPlay == WHITE ? u8" W  H  I  T  E⚪" : u8" B  L  A  C  K⚫\033[0m") << "\033[30m\n";

        //просим пользователя ввести координаты хода, и показываем пример как это сделать
        //cout << "\t\t\t\t\t\t\033[36mEnter coordinats (For example: a3 b4): \033[0m";

        //считываем эти координаты
        cout << "\t\t\t\t\t\t\t\t\t\t";
        cout << "\033[0;36m";//задаем цвет текста ввода, отличный от остального текста с помощью эскейп-последовательности
        cin >> turn.fromCol >> turn.fromRow >> turn.toCol >> turn.toRow;
        cin.clear();//сбрасываем состояние ошибки ввода что бы снова можно было вводить данные
        cin.ignore(1000, '\n');//на случай если пользователь ввел не то что ожидается, удаляем все (до1000 символов)
        cout << "\033[0m";

        //преобразование полученных от пользователя координат в индексы массива
        turn.fromCol = turn.fromCol - 'a';//буква 'а' в аскии имеет код 97, поэтому отнимая это число мы получаем индекс(97(а) - 97(а) = 0(индекс),
        //98(b) - 97(a) = 1(индекс), 99(c) - 97(a) = 2(индекс) и т.д 
        turn.toCol = turn.toCol - 'a';//тоже самое 
        turn.fromRow = turn.fromRow - 1;//здесь просто отнимаем 1 и получаем индекс 
        turn.toRow = turn.toRow - 1;// и здесь тоже

        //если ход возможен то..
        if (potentialTurn(board, nowPlay, turn))
        {
            //выполняем ход
            makeTurn(board, turn, nowPlay, whiteTotal, blackTotal);
            //если ход был сделан больше чем на 1 клетку значит это был не просто ход а битье
            if (turn.fromRow - turn.toRow > 1 || turn.fromRow - turn.toRow < -1)
            {
                //если есть возможность побить несколько шашек, ход остается у  бьющего игрока пока шашки для битья не закончатся
                if (beatMore(board, turn.toRow, turn.toCol, nowPlay))
                {
                    // если больше нет шашки, которую можно побить меняем игрока 
                    nowPlay = (nowPlay == WHITE ? BLACK : WHITE);
                }
            }

            //и меняем игрока
            nowPlay = (nowPlay == WHITE ? BLACK : WHITE);
            // выводим доску после каждого хода
            boardCheckers(board, 6, whiteTotal, blackTotal);
        }
        //если ход невозможен то..
        else
        {
            //просим игрока ввести координаты еще раз
            cout << "\n\n\n\n";
            cout << "\t\t\t\t\t\t\033[37mInvalid coordinates. Try again.\033[0m\n";
        }

        //если остается мало шашек( в нашем случае по 1 у каждого игрока) то объявляется ничья 
        if (whiteTotal > 10 && blackTotal > 10)
        {
            cout << "\n\n\n\n";
            cout << u8"\t\t\t\t\t\t\t\t \033[37m    D    R    A    W    !\033[0m\n";
            return true;
        }


        //если выполнены условия победы
        if (Win(board, nowPlay))
        {
            //выходим из програмы
            break;
        }
    }


}

//////////////////////////////////////////////////////////////////////////          configBoard            ///////////////////////////////////////////////////////////////////////////////
void configBoard(int board[SIZEb][SIZEb])
{
    // расставляем пустые клетки
    for (int row = 0; row < SIZEb; row++)
    {
        for (int col = 0; col < SIZEb; col++)
        {
            board[row][col] = EMPTY;
        }
    }

    // расставляем белые шашки вверху, первые три рядв
    for (int row = 0; row < 3; row++)
    {
        for (int col = (row + 1) % 2; col < SIZEb; col += 2)
        {
            board[row][col] = WHITE;
        }
    }

    // и черные шашки внизу, последние три ряда
    for (int row = SIZEb - 1; row >= SIZEb - 3; row--)
    {
        for (int col = (row + 1) % 2; col < SIZEb; col += 2)
        {
            board[row][col] = BLACK;
        }
    }
}

/////////////////////////////////////////////////////////////////                boardCheckers                ///////////////////////////////////////////////////////////////////////////
// отрсовка доски
void boardCheckers(int board[SIZEb][SIZEb], int kletkaSize, int whiteTotal, int blackTotal)
{
    system("CLS");
    SetConsoleOutputCP(CP_UTF8);
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(h, 8);


    cout << u8"\t\t\t\t\t\t\t\t\033[30m ♔\033[36m  C  H  E  C  K  E  R  S \033[37m♔\033[0m \n";

    //выводим счет игры
    cout << "\n\n\n\n\n";
    cout << "\t\033[36mTOTAL:\n";
    cout << u8"\t\tWHITE⚪ - " << blackTotal << "\n\n";
    cout << u8"\t\tBLACK⚫ - " << whiteTotal << "\n\033[0m";


    //складываем побитые шашки возле доски(типа))
    cout << "\n\n\n\n\n";
    cout << "\t";
    for (int i = 0; i < whiteTotal; i++)
    {
        cout << u8" ⚪";
    }
    cout << "\n\n\n";
    cout << "\t";
    for (int i = 0; i < blackTotal; i++)
    {
        cout << u8" ⚫";
    }
    cout << "\n";
    // определяем цвета для клеток доски
    int Color1 = 395;
    int Color2 = 0;
    //int Color1 = 8899135;
    //int Color2 = 42782928;
    //42782919;
    //цвет рамки
    int borderColorLeftTop = 24 * 16;
    int borderColorRightBottom = 40 * 16;

    //координаты доски
    int x = 55;
    int y = 6;

    //выводим координаты столбцов(символы от A до H)  
    //сверху доски
    COORD temp = { short(x - 3), short(y - 3) };
    SetConsoleCursorPosition(h, temp);
    SetConsoleTextAttribute(h, 8);
    for (char col = 'A'; col <= 'H'; ++col)
    {
        for (int i = 0; i < kletkaSize - 1; ++i)
        {
            cout << " ";
        }
        cout << col;
    }

    //снизу доски
    COORD temp1 = { short(x - 2), short(y + 26) };
    SetConsoleCursorPosition(h, temp1);
    SetConsoleTextAttribute(h, 8);
    for (char col = 'A'; col <= 'H'; ++col)
    {
        for (int i = 0; i < kletkaSize - 1; ++i)
        {
            cout << " ";
        }
        cout << col;
    }

    // Выводим доску
    for (int row = 0; row < 8; row++)
    {
        // Выводим цифру слева
        temp = { short(x - 6), short((y + 1) + row * kletkaSize / 2) };
        SetConsoleCursorPosition(h, temp);
        SetConsoleTextAttribute(h, 8);
        std::cout << row + 1;

        // Выводим цифру справа
        temp = { short(x + 1 + 8 * kletkaSize + 4), short((y + 1) + row * kletkaSize / 2) };
        SetConsoleCursorPosition(h, temp);
        SetConsoleTextAttribute(h, 8);
        cout << row + 1;


        for (int col = 0; col < 8; col++)
        {
            // Определяем цвет клетки в зависимости от ее позиции
            int color = (row + col) % 2 == 0 ? Color1 : Color2;

            // Устанавливаем цвет и координаты курсора
            COORD temp = { short(x + col * kletkaSize), short(y + row * kletkaSize / 2) };
            SetConsoleCursorPosition(h, temp);
            SetConsoleTextAttribute(h, color);

            // Выводим клетку
            for (int i = 0; i < kletkaSize / 2; i++)
            {
                for (int j = 0; j < kletkaSize; j++)
                {
                    cout << " ";
                }
                temp.Y++;
                SetConsoleCursorPosition(h, temp);
                SetConsoleTextAttribute(h, color);
            }
            if (board[row][col] == BLACK)
            {
                temp = { short(x + col * kletkaSize + kletkaSize / 3), short(y + row * kletkaSize / 2 + kletkaSize / 4) };
                SetConsoleCursorPosition(h, temp);
                //SetConsoleTextAttribute(h, 5);
                cout << u8"⚫";

            }
            else if (board[row][col] == WHITE)
            {
                temp = { short(x + col * kletkaSize + kletkaSize / 3), short(y + row * kletkaSize / 2 + kletkaSize / 4) };
                SetConsoleCursorPosition(h, temp);
                //SetConsoleTextAttribute(h, 5);
                cout << u8"⚪";
            }
            else if (board[row][col] == BLACK_KING)
            {
                temp = { short(x + col * kletkaSize + kletkaSize / 3), short(y + row * kletkaSize / 2 + kletkaSize / 4) };
                SetConsoleCursorPosition(h, temp);
                //SetConsoleTextAttribute(h, 5);
                cout << u8"\033[30m♔\033[0m";
            }
            else if (board[row][col] == WHITE_KING)
            {
                temp = { short(x + col * kletkaSize + kletkaSize / 3), short(y + row * kletkaSize / 2 + kletkaSize / 4) };
                SetConsoleCursorPosition(h, temp);
                //SetConsoleTextAttribute(h, 7 + 8 * 16);
                //cout << u8"♔";
                cout << u8"\033[37m♔\033[0m";
            }

        }

    }
    cout << "\n";

    // gorizonalnye chasti ramki
    for (int i = 0; i < 8 * kletkaSize + 8; i++)
    {
        //верхняя(внутреняя рамка)
        temp = { short(x + i - 4), short(y - 2) };
        SetConsoleCursorPosition(h, temp);
        SetConsoleTextAttribute(h, borderColorLeftTop);
        cout << " ";

        //нижняя(внутреняя рамка)
        temp = { short(x + i - 4), short(y + 1 + 8 * kletkaSize / 2) };
        SetConsoleCursorPosition(h, temp);
        SetConsoleTextAttribute(h, borderColorRightBottom);
        cout << " ";
    }
    for (int i = 0; i < 8 * kletkaSize + 18; i++)
    {

        //верхняя(внешняя рамка)
        temp = { short(x + i - 9), short(y - 4) };
        SetConsoleCursorPosition(h, temp);
        SetConsoleTextAttribute(h, borderColorRightBottom);
        cout << " ";

        //нижняя(внешняя рамка)
        temp = { short(x + i - 9), short(y + 9 * kletkaSize / 2) };
        SetConsoleCursorPosition(h, temp);
        SetConsoleTextAttribute(h, borderColorLeftTop);
        cout << " ";
    }

    //vertikalnye chasti ramki
    for (int i = 0; i < 9 * kletkaSize / 2; i++)
    {
        //слева ближе к доске
        temp = { short(x - 4), short(y - 1 + i) };
        SetConsoleCursorPosition(h, temp);
        SetConsoleTextAttribute(h, borderColorLeftTop);
        cout << "  ";
        //справа ближе к доске
        temp = { short((x + 2) + 8 * kletkaSize), short(y - 1 + i) };
        SetConsoleCursorPosition(h, temp);
        SetConsoleTextAttribute(h, borderColorRightBottom);
        cout << "  ";
    }
    for (int i = 0; i < 9 * (kletkaSize + 1) / 2; i++)
    {
        //слева чуть дальше от доски
        temp = { short(x - 9), short(y - 4 + i) };
        SetConsoleCursorPosition(h, temp);
        SetConsoleTextAttribute(h, borderColorRightBottom);
        cout << "  ";
        //справа чуть дальше от доски
        temp = { short(x + 1 + 9 * kletkaSize), short(y - 4 + i) };
        SetConsoleCursorPosition(h, temp);
        SetConsoleTextAttribute(h, borderColorLeftTop);
        cout << "  ";
    }
    SetConsoleTextAttribute(h, 8);
}


////////////////////////////////////////////////////////////////                validTurn                ///////////////////////////////////////////////////////////////////////////
//функция для проверки возможности хода
bool potentialTurn(int board[SIZEb][SIZEb], int nowPlay, Turn turn)
{

    // проверяем что не выходим за пределы доски
    if (turn.toRow < 0 || turn.toRow >= SIZEb || turn.toCol < 0 || turn.toCol >= SIZEb)
    {
        return false;
    }

    // проверяем что конечная клетка пуста
    if (board[turn.toRow][turn.toCol] != EMPTY)
    {
        return false;
    }

    // проверяем что выбранная фигура принадлежит текущему игроку
    if (board[turn.fromRow][turn.fromCol] != nowPlay &&
        board[turn.fromRow][turn.fromCol] != (nowPlay == WHITE ? WHITE_KING : BLACK_KING))
    {
        return false;
    }

    // проверка хода для белых
    if (board[turn.fromRow][turn.fromCol] == WHITE)
    {
        // разрешаем ходить на одну клетку вниз по доске 
        if ((turn.toRow - turn.fromRow == 1) && (turn.toCol - turn.fromCol == 1 || turn.toCol - turn.fromCol == -1))
        {
            return true;
        }

    }

    // проверка хода для черных
    if (board[turn.fromRow][turn.fromCol] == BLACK)
    {
        // разрешаем ходить на одну клетку вверх по доске
        if ((turn.toRow - turn.fromRow == -1) && (turn.toCol - turn.fromCol == 1 || turn.toCol - turn.fromCol == -1))
        {
            return true;
        }

    }

    //ход для дамок
    if (board[turn.fromRow][turn.fromCol] == WHITE_KING || board[turn.fromRow][turn.fromCol] == BLACK_KING)
    {
        // разрешаем ходить на любое количество клеток вперед или назад
        if ((turn.toRow - turn.fromRow == turn.toCol - turn.fromCol) || (turn.toRow - turn.fromRow == turn.fromCol - turn.toCol))
        {
            return true;
        }
    }

    //вычисляем координаты промежуточной клетки, на которой стоит шашка противника
    int damageR = (turn.toRow + turn.fromRow) / 2;
    int damageC = (turn.toCol + turn.fromCol) / 2;

    // проверяем на битье
    if ((turn.toRow - turn.fromRow == 2 || turn.toRow - turn.fromRow == -2) && (turn.toCol - turn.fromCol == 2 || turn.toCol - turn.fromCol == -2))
    {
        //проверяем что есть простая шашка противника для битья
        if (board[damageR][damageC] != (nowPlay == WHITE ? BLACK : WHITE))
        {
            //и еще проверяем есть ли дамка противника для битья
            if (board[damageR][damageC] != (nowPlay == WHITE ? BLACK_KING : WHITE_KING))
            {
                return false; //
            }
            return true;
        }
        return true;
    }
    return false;
}


////////////////////////////////////////////////////////////////                makeTurn                ////////////////////////////////////////////////////////////////////////////////
//функция выполняющая сам ход
void makeTurn(int board[SIZEb][SIZEb], Turn turn, int nowPlay, int& whiteTotal, int& blackTotal)
{

    // перемещаем фигуру на новое место
    board[turn.toRow][turn.toCol] = board[turn.fromRow][turn.fromCol];
    // а на том месте, где была фигура, выводим пустую клетку
    board[turn.fromRow][turn.fromCol] = EMPTY;

    // проверяем становится ли фигура дамкой
    if ((turn.toRow == 0 && board[turn.toRow][turn.toCol] == BLACK) ||
        (turn.toRow == SIZEb - 1 && board[turn.toRow][turn.toCol] == WHITE))
    {
        board[turn.toRow][turn.toCol] = (board[turn.toRow][turn.toCol] == WHITE ? WHITE_KING : BLACK_KING);
    }

    // Проверяем, является ли ход битьем
    if (abs(turn.toRow - turn.fromRow) > 1 && (board[turn.toRow][turn.toCol] == nowPlay || board[turn.toRow][turn.toCol] == (nowPlay == WHITE ? WHITE_KING : BLACK_KING)))
    {
        // удаляем захваченные фигуры, если есть

        int stepRow = (turn.toRow - turn.fromRow) / abs(turn.toRow - turn.fromRow);
        int stepCol = (turn.toCol - turn.fromCol) / abs(turn.toCol - turn.fromCol);
        while (turn.fromRow != turn.toRow && turn.fromCol != turn.toCol)
        {
            turn.fromRow += stepRow;
            turn.fromCol += stepCol;
            // Если на промежуточной клетке есть фигура противника, удаляем её
            if (board[turn.fromRow][turn.fromCol] != EMPTY && board[turn.fromRow][turn.fromCol] != nowPlay &&
                board[turn.fromRow][turn.fromCol] != (nowPlay == WHITE ? WHITE_KING : BLACK_KING))
            {
                if (board[turn.fromRow][turn.toCol] != (nowPlay == WHITE ? BLACK : WHITE))
                {
                    //board[fromRow][fromCol] = EMPTY;
                    if (board[turn.fromRow][turn.fromCol] == BLACK || board[turn.fromRow][turn.fromCol] == BLACK_KING)
                    {
                        blackTotal++;

                    }
                    else if (board[turn.fromRow][turn.fromCol] == WHITE || board[turn.fromRow][turn.fromCol] == WHITE_KING)
                    {
                        whiteTotal++;

                    }
                    board[turn.fromRow][turn.fromCol] = EMPTY;
                    //останавливаем цикл после удаления шашки
                    break;
                }
            }
        }
    }
}



////////////////////////////////////////////////////////////////                     Win                     ///////////////////////////////////////////////////////////////////////////
bool Win(int board[SIZEb][SIZEb], int nowPlay)
{
    Turn turn;
    bool WHITE_Lose = false;
    bool BLACK_Lose = false;

    // Проверяем, есть ли у игроков еще шашки на доске
    for (int row = 0; row < SIZEb; ++row)
    {
        for (int col = 0; col < SIZEb; ++col)
        {

            if (board[row][col] == WHITE || board[row][col] == WHITE_KING)
            {
                WHITE_Lose = true;
            }
            else if (board[row][col] == BLACK || board[row][col] == BLACK_KING)
            {
                BLACK_Lose = true;
            }
        }
    }




    // Если у одного из игроков не осталось шашек, то это победа другого
    if (!WHITE_Lose)
    {
        WinMessage();
        cout << "\n";
        cout << u8"\t\t\t\t\t\t\t\t \033[37mB  L  A  C  K ⚫    W  I  N  !\033[0m\n";
        Sleep(500);
        return true;
    }
    else if (!BLACK_Lose)
    {
        WinMessage();
        cout << "\n";
        cout << u8"\t\t\t\t\t\t\t\t \033[37mW  H  I  T  E ⚪   W  I  N  !\033[0m\n";
        Sleep(500);
        return true;
    }
    return false;
}

////////////////////////////////////////////////////////////////                beatMore                ///////////////////////////////////////////////////////////////////////////
// функция для проверки возможности бить несколько раз подряд
bool beatMore(int board[SIZEb][SIZEb], int row, int col, int nowPlay)
{
    // ссоздаем переменную для возврата результата работы функции
    bool goBeat = false;

    // проверка битья для белых
    if (nowPlay == WHITE || nowPlay == WHITE_KING)
    {
        // проверяем можно ли побить шашку противника слева сверху
        if (row >= 2 && col >= 2 &&//проверяем что текущее положение достаточно далеко от верха доски и от левого края
            (board[row - 1][col - 1] == BLACK || board[row - 1][col - 1] == BLACK_KING) &&//проверяем что на соседней клетке есть шашк или дамка противника
            board[row - 2][col - 2] == EMPTY)//также проверяем что следующая клетка пустая что бы поставить тудасвою шашку
        {
            goBeat = true;
        }
        // проверяем можно ли побить шашку противника справа сверху
        if (row >= 2 && col < SIZEb - 2 &&//проверяем что текущее положение достаточно далеко от верха доски и от правого края
            (board[row - 1][col + 1] == BLACK || board[row - 1][col + 1] == BLACK_KING) &&//проверяем что на соседней клетке есть шашк или дамка противника
            board[row - 2][col + 2] == EMPTY)//также проверяем что следующая клетка пустая что бы поставить тудасвою шашку
        {
            goBeat = true;
        }
        // проверяем можно ли побить шашку противника слева снизу
        if (row < SIZEb - 2 && col >= 2 &&//проверяем что текущее положение достаточно далеко от низа доски и от левого края
            (board[row + 1][col - 1] == BLACK || board[row + 1][col - 1] == BLACK_KING) &&//проверяем что на соседней клетке есть шашк или дамка противника
            board[row + 2][col - 2] == EMPTY)//также проверяем что следующая клетка пустая что бы поставить тудасвою шашку
        {
            goBeat = true;
        }
        // проверяем можно ли побить шашку противника справа снизу
        if (row < SIZEb - 2 && col < SIZEb - 2 &&//проверяем что текущее положение достаточно далеко от низа доски и от правого края
            (board[row + 1][col + 1] == BLACK || board[row + 1][col + 1] == BLACK_KING) &&//проверяем что на соседней клетке есть шашка или дамка противника
            board[row + 2][col + 2] == EMPTY)//также проверяем что следующая клетка пустая что бы поставить тудасвою шашку
        {
            goBeat = true;
        }
    }
    // проверка битья для черных
    if (nowPlay == BLACK || nowPlay == BLACK_KING)
    {
        // проверяем можно ли побить шашку противника слева сверху
        if (row >= 2 && col >= 2 &&//проверяем что текущее положение достаточно далеко от верха доски и от левого края
            (board[row - 1][col - 1] == WHITE || board[row - 1][col - 1] == WHITE_KING) &&//проверяем что на соседней клетке есть шашка или дамка противника
            board[row - 2][col - 2] == EMPTY)//также проверяем что следующая клетка пустая что бы поставить тудасвою шашку
        {
            goBeat = true;
        }
        // проверяем можно ли побить шашку противника справа сверху
        if (row >= 2 && col < SIZEb - 2 &&//проверяем что текущее положение достаточно далеко от верха доски и от правого края
            (board[row - 1][col + 1] == WHITE || board[row - 1][col + 1] == WHITE_KING) &&//проверяем что на соседней клетке есть шашка или дамка противника
            board[row - 2][col + 2] == EMPTY)//также проверяем что следующая клетка пустая что бы поставить тудасвою шашку
        {
            goBeat = true;
        }
        // проверяем можно ли побить шашку противника слева снизу
        if (row < SIZEb - 2 && col >= 2 &&//проверяем что текущее положение достаточно далеко от низа доски и от левого края
            (board[row + 1][col - 1] == WHITE || board[row + 1][col - 1] == WHITE_KING) &&//проверяем что на соседней клетке есть шашк или дамка противника
            board[row + 2][col - 2] == EMPTY)//также проверяем что следующая клетка пустая что бы поставить тудасвою шашку
        {
            goBeat = true;
        }
        // проверяем можно ли побить шашку противника справа снизу
        if (row < SIZEb - 2 && col < SIZEb - 2 &&//проверяем что текущее положение достаточно далеко от низа доски и от правого края
            (board[row + 1][col + 1] == WHITE || board[row + 1][col + 1] == WHITE_KING) &&//проверяем что на соседней клетке есть шашк или дамка противника
            board[row + 2][col + 2] == EMPTY)//также проверяем что следующая клетка пустая что бы поставить тудасвою шашку
        {
            goBeat = true;
        }
    }
    return goBeat;
}


////////////////////////////////////////////////////////////////                WinMessage                ///////////////////////////////////////////////////////////////////////////
/*void WinMessage()
{
    //srand(time(0));

    int size = 100;
    char* str = new char[size] {'C', 'O', 'N', 'G', 'R', 'A', 'T', 'U', 'L', 'A', 'T', 'I', 'O', 'N', 'S', '!', '!', '!'};

    //int color = rand() % 8 + 30;
    int color = 37;

    cout << "\n\n\n\n";
    for (size_t i = 0; i < strlen(str); i++)
    {
        cout << "\033[" << color << "m";
        cout << "\t" << str[i] << " ";
        cout << "\033[0m";
        Sleep(100);
    }
    cout << "\n";
    delete[] str;
}*/
