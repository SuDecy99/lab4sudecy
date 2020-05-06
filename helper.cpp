#include "helper.h"
#include <QDebug>
#include <QRandomGenerator>


Helper::Helper(QObject *parent) : QObject(parent)
{

}

int randomInt(int min, int max)
{
    return min + (rand() % static_cast<int>(max - min + 1));
}

// Генерация поля
void Helper::generateMaze(int pos, QVector<int>& bricks)
{
    // Координаты в 2D
    int pos_x = pos % 10;
    int pos_y = pos / 10;

    // Куда можно построить соединение
    QVector<int> directions;

    // Находим все доступные направления
    if(pos_x > 0)
    {
        if(bricks[(pos_x - 1) + pos_y * 10] == 0)
        {
            directions.push_back(4);
        }
    }
    if(pos_x < 9)
    {
        if(bricks[(pos_x + 1) + pos_y * 10] == 0)
        {
            directions.push_back(1);
        }
    }
    if(pos_y > 0)
    {
        if(bricks[pos_x + (pos_y - 1) * 10] == 0)
        {
            directions.push_back(8);
        }
    }
    if(pos_y < 9)
    {
        if(bricks[pos_x + (pos_y + 1) * 10] == 0)
        {
            directions.push_back(2);
        }
    }

    int d_len = directions.length();

    // Строим соединение если есть пустые плитки
    if(d_len > 0)
    {

        // Случайное направление из доступных
        int dir = directions[randomInt(0, d_len - 1)];

        // Добавляем дорожку на текущей плитке
        bricks[pos] |= dir;

        int next_pos = pos;
        int next_dir = 0;

        // Место в массиве и направление дорожки
        // на следующей плитке
        if(dir == 8)
        {
            next_pos -= 10;
            next_dir = 2;
        }
        else if(dir == 4)
        {
            next_pos -= 1;
            next_dir = 1;
        }
        else if(dir == 2)
        {
            next_pos += 10;
            next_dir = 8;
        }
        else if(dir == 1)
        {
            next_pos += 1;
            next_dir = 4;
        }

        bricks[next_pos] |= next_dir;
        generateMaze(next_pos, bricks);
    }

    // Если были свободные плитки строим ещё соединение
    // Ранее свободные плитки могут быть уже заняты
    if(d_len > 1) {
        generateMaze(pos, bricks);
    }
    return;
}

// Запуск новой игры
QVector<int> Helper::newGame()
{
    QVector<int> bricks;
    for(int i = 0; i < 100; i++)
    {
        bricks.push_back(0);
    }

    // генерируем поле
    generateMaze(0, bricks);

    // перемешиваем поле
    for(int i=1; i<100; i++)
    {
        for(int k = 0; k < (rand() % 5 ) ; k++)
        {
            bricks[i] = (bricks[i] >> 1) | (bricks[i] << 3);
        }
    }
//    qDebug()<<bricks;
    return bricks;
}

// Обновление запитанных плиток
QVector<bool> Helper::light(QVector<int> bricks)
{
    QVector<bool> lights;
    int i=0;
    for( i = 0; i<100; i++)
        lights.push_back(false);

for(int j=0;j<100;j++){
for(i=0;i<100;i++){

    if (i == 0)
        lights.replace(0, true);

    if (i == 9) {
        if(( ((bricks[i] & 4) != 0) && ((bricks[i-1] & 1) != 0) && (lights.value(i-1) == true )) ||
           ( ((bricks[i] & 2) != 0) && ((bricks[i+10] & 8) != 0) && (lights.value(i+10) == true  ))
          )
            lights.replace(i, true);
            else
            lights.replace(i, false);

    }
    if (i == 90) {
        if(( ((bricks[i] & 8) != 0) && ((bricks[i-10] & 2) != 0) && (lights.value(i-10) == true )) ||
           ( ((bricks[i] & 1) != 0) && ((bricks[i+1] & 4) != 0) && (lights.value(i+1) == true  ))
          )
            lights.replace(i, true);
            else
            lights.replace(i, false);

    }
    if (i == 99) {
        if(( ((bricks[i] & 8) != 0) && ((bricks[i-10] & 2) != 0) && (lights.value(i-10) == true )) ||
           ( ((bricks[i] & 4) != 0) && ((bricks[i-1] & 1) != 0) && (lights.value(i-1) == true  ))
          )
            lights.replace(i, true);
            else
            lights.replace(i, false);
    }

    }

for(i=1;i<9;i++) {
    if(( ((bricks[i] & 1) != 0) && ((bricks[i+1] & 4) != 0) && (lights.value(i+1) == true )) ||
       ( ((bricks[i] & 2) != 0) && ((bricks[i+10] & 8) != 0) && (lights.value(i+10) == true  )) ||
       ( ((bricks[i] & 4) != 0) && ((bricks[i-1] & 1) != 0) && (lights.value(i-1) == true ))
      )
        lights.replace(i, true);
        else
        lights.replace(i, false);
}
for(i=91;i<99;i++) {
    if(( ((bricks[i] & 1) != 0) && ((bricks[i+1] & 4) != 0) && (lights.value(i+1) == true )) ||
       ( ((bricks[i] & 8) != 0) && ((bricks[i-10] & 2) != 0) && (lights.value(i-10) == true  )) ||
       ( ((bricks[i] & 4) != 0) && ((bricks[i-1] & 1) != 0) && (lights.value(i-1) == true ))
      )
        lights.replace(i, true);
        else
        lights.replace(i, false);
}
for(i=19;i<99;) {
    if(( ((bricks[i] & 2) != 0) && ((bricks[i+10] & 8) != 0) && (lights.value(i+10) == true )) ||
       ( ((bricks[i] & 8) != 0) && ((bricks[i-10] & 2) != 0) && (lights.value(i-10) == true  )) ||
       ( ((bricks[i] & 4) != 0) && ((bricks[i-1] & 1) != 0) && (lights.value(i-1) == true ))
      )
        lights.replace(i, true);
        else
        lights.replace(i, false);
    i+=10;
}
for(i=10;i<90;) {
    if(( ((bricks[i] & 2) != 0) && ((bricks[i+10] & 8) != 0) && (lights.value(i+10) == true )) ||
       ( ((bricks[i] & 8) != 0) && ((bricks[i-10] & 2) != 0) && (lights.value(i-10) == true  )) ||
       ( ((bricks[i] & 1) != 0) && ((bricks[i+1] & 4) != 0) && (lights.value(i+1) == true ))

      )
        lights.replace(i, true);
        else
        lights.replace(i, false);
    i+=10;
}



for (i=11;i<89;i++) {
    if( (i%10)<9 && (i/10)>0 && lights.value(i) == false)
    {
        if(( ((bricks[i] & 1) != 0) && ((bricks[i+1] & 4) != 0) && (lights.value(i+1) == true )) ||
           ( ((bricks[i] & 2) != 0) && ((bricks[i+10] & 8) != 0) && (lights.value(i+10) == true  )) ||
           ( ((bricks[i] & 4) != 0) && ((bricks[i-1] & 1) != 0) && (lights.value(i-1) == true )) ||
           ( ((bricks[i] & 8) != 0) && ((bricks[i-10] & 2) != 0) && (lights.value(i-10) == true  ))
          )
            lights.replace(i, true);
            else
            lights.replace(i, false);
    }

}
}

    return lights;
}
