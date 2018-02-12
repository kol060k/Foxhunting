# Foxhunting

Правила игры "Охота на лис":
  1) На поле некоторым образом сидят 10 лис. Ваша задача их всех убить!
  2) Каждый Ваш ход состоит из одного выстрела в любую точку поля (кроме дерева, о деревьях позднее).
    а) Если Вы попали в лису, то она считатся убитой.
    б) Если Вы попали в пустую клетку, то на ней появляется число - количество лис, которых видно из этой точки, если смотреть по вертикали, горизонтали или двум диагоналям. Деревья мешают обзору. То есть перед деревом видно лис, а за ним уже нет.
  3) Вы играете против ИИ, который стреляет по Вашим лисам (которых вы расставили на своём поле в начале игры).
  4) Игра заканчивается, когда один из игроков убивает всех лис противника. Этот игрок и считается победителем.

Техническое задание 2 сем: ----------------------------------------------

Алгоритм


Графика и обработка действий игрока
  1) Таблица рекордов;
  2) Отображение времени игры и числа ходов;
  3) Добавить новые окна:
      - окно ввода параметров игры вместо консоли;
      - "начальный экран игры";
  4) Пофиксить баг расширения окна игры;
  5) Функция текстового ввода в графическом окне;
  6) Выделение клеток зажатой правой кнопкой мыши;
  7) Добавление инструкции к игре и приложению по F1;
  8) Пауза по клавише Esc;

Техническое задание 1 сем: ----------------------------------------------
1) Алгоритм / игра 
  а) Обработка и хранение состояния игры 
  б) ИИ 
  в) Интерфейс игрока 
  г) Вывод текущего состояния в консоль
2) Графика игры
  а) Создание и заполнение двух полей
  б) Отрисовка неопределённой клетки
  б) Отрисовка обнаружения лисицы
  в) Отрисовка "зануления" и "разнуления" клетки по правой кнопке мыши (ход не тратится)
  г) Отрисовка всех чисел в клетке
  д) Отрисовка дерева
  е) Отрисовка своих лис
  ж) Работа с текстурами:
    1) Программа конвертации массива jpg_565 в массив RGB
    2) Создание текстур из картинок в интернете и перевод их в заголовочные файлы при помощи программы пункта ж.1
