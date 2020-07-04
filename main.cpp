#include <QApplication>
#include <QWidget>
#include <QKeyEvent>
#include <QPainter>
#include <QTime>

class Cat : public QWidget
{

    public:
      Cat(QWidget *parent = 0);

    protected:
      void paintEvent(QPaintEvent *);
      void timerEvent(QTimerEvent *);   //Формирует игровой цикл
      void keyPressEvent(QKeyEvent *);

    private:
      static const int B_WIDTH = 350;   //Ширина поля
      static const int B_HEIGHT = 300;  //Высота поля
      static const int DOT_SIZE = 10;   //Размер объектов
      static const int ALL_DOGS = 100;  //Максимальное количество собак
      static const int RAND_POS = 29;   //Константа для определения местоположения корма
      static const int DELAY = 100;     //Скорость игры
      static const int DOG_STEP=5;      //Длина шага собаки
      static const int CAT_STEP=10;     //Длина шага кошки

      int timerId;
      int dogs;     //Количество собак
      int x_Meat;   //Координаты корма
      int y_Meat;
      int x_Cat;    //Координаты кошки
      int y_Cat;
      int dx_Dog;   //Изменения координат собак
      int dy_Dog;

      int x_hover_point;    //Координаты точки наведения собаки
      int y_hover_point;

      int x[ALL_DOGS];      //Массив для хранения координат собак
      int y[ALL_DOGS];

      bool leftDirection;   //Переменные для определения направления движения кошки
      bool rightDirection;
      bool upDirection;
      bool downDirection;

      bool inGame;

      void initGame();      //Запуск игры
      void locateMeat();    //Размещает корм в случайную точку
      void checkMeat();     //Проверяет, съедено ли мясо, увеличивает к-во собак и вызывает locateMeat()
      void checkCollision();//Обнаруживает столкновение кошки с собаками, меняет направление движения кошки при столкновении
                            //с границей поля на противоположное
      void move();          //Определяет изменения координат собак и кошки
      void doDrawing();     //Рисует объекты на поле
      void gameOver(QPainter &);    //Выводит сообщение в заключение игры
};

Cat::Cat(QWidget *parent) : QWidget(parent)
{
    setStyleSheet("background-color:yellow;");
    leftDirection = false;
    rightDirection = true;
    upDirection = false;
    downDirection = false;
    inGame = true;

    resize(B_WIDTH, B_HEIGHT);

    initGame();
}



void Cat::initGame()
{
    dogs=1;
    x_Cat=150;
    y_Cat=150;

    locateMeat();

    for (int z = 0; z < ALL_DOGS; z++)
    {
        x[z]=50;
        y[z]=50;
    }

    timerId = startTimer(DELAY);
}

void Cat::paintEvent(QPaintEvent *e)
{
    Q_UNUSED(e);
    doDrawing();
}

void Cat::doDrawing()
{
    QPainter qp(this);
    if (inGame)
    {
        qp.setRenderHint (QPainter::Antialiasing,true);
        qp.setBrush(QBrush(Qt::green));
        qp.setPen(QPen(Qt::black));
        qp.drawRoundRect(QRect (x_Meat, y_Meat,DOT_SIZE,DOT_SIZE),100,100);
        qp.setBrush(QBrush(Qt::black));

        qp.drawRect(x_Cat,y_Cat,DOT_SIZE,DOT_SIZE);
        qp.setBrush(QBrush(Qt::red));

        for (int z = 0; z <dogs; z++)
        {
            qp.drawRoundRect(QRect (x[z], y[z],DOT_SIZE,DOT_SIZE),70,90);
        }
    }
    else
    {
        gameOver(qp);
    }
}

void Cat::gameOver(QPainter &qp)
{
    QString message = "Game over. Your result: %1 ";
    QFont font("Courier", 15, QFont::DemiBold);
    QFontMetrics fm(font);
    int textWidth = fm.width(message);

    qp.setPen(QColor(Qt::blue));
    qp.setFont(font);
    int h = height();
    int w = width();

    qp.translate(QPoint(w/2, h/2));
    qp.drawText(-textWidth/2, 0, message.arg(dogs));
}

void Cat::checkMeat()
{
    if ((x_Cat == x_Meat) && (y_Cat == y_Meat))
    {
        dogs++;
        locateMeat();
    }
}

void Cat::move()
{
        for (int z = 0; z < dogs; z+=5)
        {
            x_hover_point=x_Cat;
            y_hover_point=y_Cat;
            if (abs(x_hover_point-x[z])>abs(y_hover_point-y[z]))
            {
                    if (x_hover_point>x[z])
                    {
                        dx_Dog=DOG_STEP;
                        dy_Dog=0;
                    }
                    else
                    {
                        dx_Dog=0-DOG_STEP;
                        dy_Dog=0;
                    }
            }
            else
            {
                    if (y_hover_point>y[z])
                    {
                        dx_Dog=0;
                        dy_Dog=DOG_STEP;
                    }
                    else
                    {
                        dx_Dog=0;
                        dy_Dog=0-DOG_STEP;
                    }
            }
            x[z]=x[z]+dx_Dog;
            y[z]=y[z]+dy_Dog;
        }
        for (int z = 1; z < dogs; z+=5)
        {
            x_hover_point=x_Cat+2*CAT_STEP;
            y_hover_point=y_Cat;
            if (abs(x_hover_point-x[z])<abs(y_hover_point-y[z]))
            {
                    if (x_hover_point>x[z])
                    {
                        dx_Dog=DOG_STEP;
                        dy_Dog=0;
                    }
                    else
                    {
                        dx_Dog=0-DOG_STEP;
                        dy_Dog=0;
                    }
            }
            else
            {
                    if (y_hover_point>y[z])
                    {
                        dx_Dog=0;
                        dy_Dog=DOG_STEP;
                    }
                    else
                    {
                        dx_Dog=0;
                        dy_Dog=0-DOG_STEP;
                    }
            }
            x[z]=x[z]+dx_Dog;
            y[z]=y[z]+dy_Dog;
        }
        for (int z = 2; z < dogs; z+=5)
        {
            x_hover_point=x_Cat;
            y_hover_point=y_Cat+2*CAT_STEP;
            if (abs(x_hover_point-x[z])>abs(y_hover_point-y[z]))
            {
                    if (x_hover_point>x[z])
                    {
                        dx_Dog=DOG_STEP;
                        dy_Dog=0;
                    }
                    else
                    {
                        dx_Dog=0-DOG_STEP;
                        dy_Dog=0;
                    }
            }
            else
            {
                    if (y_hover_point>y[z])
                    {
                        dx_Dog=0;
                        dy_Dog=DOG_STEP;
                    }
                    else
                    {
                        dx_Dog=0;
                        dy_Dog=0-DOG_STEP;
                    }
            }
            x[z]=x[z]+dx_Dog;
            y[z]=y[z]+dy_Dog;
        }
        for (int z = 3; z < dogs; z+=5)
        {
            x_hover_point=x_Cat-2*CAT_STEP;
            y_hover_point=y_Cat;
            if (abs(x_hover_point-x[z])<abs(y_hover_point-y[z]))
            {
                    if (x_hover_point>x[z])
                    {
                        dx_Dog=DOG_STEP;
                        dy_Dog=0;
                    }
                    else
                    {
                        dx_Dog=0-DOG_STEP;
                        dy_Dog=0;
                    }
            }
            else
            {
                    if (y_hover_point>y[z])
                    {
                        dx_Dog=0;
                        dy_Dog=DOG_STEP;
                    }
                    else
                    {
                        dx_Dog=0;
                        dy_Dog=0-DOG_STEP;
                    }
            }
            x[z]=x[z]+dx_Dog;
            y[z]=y[z]+dy_Dog;
        }
        for (int z = 4; z < dogs; z+=5)
        {
            x_hover_point=x_Cat;
            y_hover_point=y_Cat-2*CAT_STEP;
            if (abs(x_hover_point-x[z])>abs(y_hover_point-y[z]))
            {
                    if (x_hover_point>x[z])
                    {
                        dx_Dog=DOG_STEP;
                        dy_Dog=0;
                    }
                    else
                    {
                        dx_Dog=0-DOG_STEP;
                        dy_Dog=0;
                    }
            }
            else
            {
                    if (y_hover_point>y[z])
                    {
                        dx_Dog=0;
                        dy_Dog=DOG_STEP;
                    }
                    else
                    {
                        dx_Dog=0;
                        dy_Dog=0-DOG_STEP;
                    }
            }
            x[z]=x[z]+dx_Dog;
            y[z]=y[z]+dy_Dog;
        }

    if (leftDirection)
    {
        x_Cat-= CAT_STEP;
    }

    if (rightDirection)
    {
        x_Cat += CAT_STEP;
    }

    if (upDirection)
    {
        y_Cat -= CAT_STEP;
    }

    if (downDirection)
    {
        y_Cat += CAT_STEP;
    }
}

void Cat::checkCollision()
{
    for (int z = 0; z < dogs; z++)
    {
        if (x_Cat==x[z] && y_Cat==y[z])
            inGame = false;
    }
    if (y_Cat >= B_HEIGHT)
    {
        upDirection = true;
        downDirection=false;
        leftDirection = false;
        rightDirection=false;
    }
    if (y_Cat < 0)
    {
        downDirection = true;
        upDirection=false;
        leftDirection = false;
        rightDirection=false;
    }
    if (x_Cat >= B_WIDTH)
    {
        leftDirection = true;
        rightDirection=false;
        upDirection = false;
        downDirection=false;
    }

    if (x_Cat < 0)
    {
        rightDirection = true;
        leftDirection=false;
        upDirection = false;
        downDirection=false;
    }
    if(!inGame)
    {
        killTimer(timerId);
    }
}

void Cat::locateMeat()
{
    QTime time = QTime::currentTime();
    qsrand((uint) time.msec());
    int r = qrand() % RAND_POS;
    x_Meat = (r * DOT_SIZE);
    r = qrand() % RAND_POS;
    y_Meat = (r * DOT_SIZE);
}

void Cat::timerEvent(QTimerEvent *e)
{
    Q_UNUSED(e);
    if (inGame)
    {
        move();
        checkCollision();
        checkMeat();
     }
    repaint();
}

void Cat::keyPressEvent(QKeyEvent *e)
{
    int key = e->key();
    if (key == Qt::Key_Left)
    {
        leftDirection = true;
        upDirection = false;
        downDirection = false;
        rightDirection=false;
    }

    if (key == Qt::Key_Right)
    {
        rightDirection = true;
        upDirection = false;
        downDirection = false;
        leftDirection=false;
    }

    if (key == Qt::Key_Up)
    {
        upDirection = true;
        rightDirection = false;
        leftDirection = false;
        downDirection=false;
    }

    if (key == Qt::Key_Down)
    {
        downDirection = true;
        rightDirection = false;
        leftDirection = false;
        upDirection=false;
    }
}

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  Cat window;

  window.setWindowTitle("Hungry Cat");
  window.show();

  return app.exec();
}

