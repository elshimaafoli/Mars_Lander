#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <time.h>
#include"Collision.cpp"
#include <iostream>
#include <cmath>
using namespace sf;
using namespace std;
using namespace Collision;

float speed = 0,angle =0,pi=180;
float movementx,movementy,dy=3.55;
int fuel = 5000;
int t=0,c;
int main()
{

    bool gameOver=false,win=false;
    RenderWindow app(VideoMode(1920, 1080), "Mars Lander Game!");
    //font
    sf::Font font;
    if(!font.loadFromFile("font/arial.ttf"))return -1;

    sf::SoundBuffer buffer;
    buffer.loadFromFile("sounds/engine.ogg");
    sf::Sound sound;
    sound.setBuffer(buffer);

    sf::SoundBuffer buffer1;
    buffer1.loadFromFile("sounds/explosion.ogg");
    sf::Sound sound1;
    sound1.setBuffer(buffer1);
    sf::SoundBuffer buffer2;
    buffer2.loadFromFile("sounds/bg.wav");
    sf::Sound sound2;
    sound2.setBuffer(buffer2);


    // angle - time - speedVertical - speedHorizontal
    Text angleText;
    angleText.setString("Angle :");
    angleText.setFont(font);
    angleText.setFillColor(Color::White);
    angleText.setCharacterSize(20);
    angleText.setPosition(0,0);
    Text angleNum;
    angleNum.setString(to_string(angle));
    angleNum.setFont(font);
    angleNum.setFillColor(Color::White);
    angleNum.setCharacterSize(20);
    angleNum.setPosition(angleText.getGlobalBounds().width,0);

    //speedVertical
    Text speedVerticalText;
    speedVerticalText.setString("Speed Vertical :");
    speedVerticalText.setFont(font);
    speedVerticalText.setFillColor(Color::White);
    speedVerticalText.setCharacterSize(20);
    speedVerticalText.setPosition(0,angleText.getGlobalBounds().height+10);
    Text speedVertical;
    speedVertical.setString(to_string(movementy));
    speedVertical.setFont(font);
    speedVertical.setFillColor(Color::White);
    speedVertical.setCharacterSize(20);
    speedVertical.setPosition(speedVerticalText.getGlobalBounds().width,angleText.getGlobalBounds().height+10);

    //speed horizontal
    Text speedhorizontalText;
    speedhorizontalText.setString("Speed Horizontal :");
    speedhorizontalText.setFont(font);
    speedhorizontalText.setFillColor(Color::White);
    speedhorizontalText.setCharacterSize(20);
    speedhorizontalText.setPosition(0,angleText.getGlobalBounds().height+15+speedVerticalText.getGlobalBounds().height);
    Text speedhorizontal;
    speedhorizontal.setString(to_string(movementx));
    speedhorizontal.setFont(font);
    speedhorizontal.setFillColor(Color::White);
    speedhorizontal.setCharacterSize(20);
    speedhorizontal.setPosition(speedhorizontalText.getGlobalBounds().width,angleText.getGlobalBounds().height+15+speedVerticalText.getGlobalBounds().height);



Text timeText;
    timeText.setFont(font);
    timeText.setCharacterSize(20);
    timeText.setFillColor(sf::Color::White);

    //text win
    Text WinText;
    WinText.setFont(font);
    WinText.setString("You Win!");
    WinText.setCharacterSize(60);
    WinText.setFillColor(sf::Color::Blue);
    WinText.setOrigin(WinText.getGlobalBounds().width/2,WinText.getGlobalBounds().height/2);
    WinText.setPosition(app.getSize().x/2,app.getSize().y/2);

    // text__loser ...
    Text gameoverText;
    gameoverText.setFont(font);
    gameoverText.setString("Game Over!");
    gameoverText.setCharacterSize(60);
    gameoverText.setFillColor(sf::Color::Blue);
    gameoverText.setOrigin(gameoverText.getGlobalBounds().width/2,gameoverText.getGlobalBounds().height/2);
    gameoverText.setPosition(app.getSize().x/2,app.getSize().y/2);


    Texture safeAreaTex;
    if(!safeAreaTex.loadFromFile("images/safeArea.png"))return -1;
    Sprite safeArea;
    safeArea.setTexture(safeAreaTex);

    Texture obsticalesTex[4];
    Sprite obsticales[4];
    for(int i=0; i<4; i++)
    {
        if(!obsticalesTex[i].loadFromFile("images/obsticale"+to_string(i+1)+".png")) return -1;
        obsticales[i].setTexture(obsticalesTex[i]);
        obsticales[i].setOrigin(obsticales[i].getGlobalBounds().width/2,obsticales[i].getGlobalBounds().height/2);
    }
    Texture t1,t2,t3,t4,t5;
    if(! t1.loadFromFile("rocket.png"))return -1;
    if(!t2.loadFromFile("images/01.png"))return -1;
    if(!t3.loadFromFile("images/02.png"))return -1;
    if(!t4.loadFromFile("images/03.png"))return -1;
    if(!t5.loadFromFile("images/04.png"))return -1;
    Sprite Rocket(t1);
    Sprite fire(t2);
    fire.setTexture(t2);
    Sprite fire1(t3);
    fire1.setTexture(t3);
    Sprite fire2(t4);
    fire2.setTexture(t4);
    Sprite fire3(t5);
    fire3.setTexture(t5);
    app.setFramerateLimit(30);
    Rocket.setPosition(rand()%1200,rand()%150);
    Rocket.setOrigin(50,87.5);
    safeArea.setOrigin(safeArea.getGlobalBounds().width/2,safeArea.getGlobalBounds().height/2);

    safeArea.setPosition(app.getSize().x/2,app.getSize().y-safeArea.getGlobalBounds().height);


    sound2.play();

    while (app.isOpen())
    {

        c++;
        if(c>=60){t++; c=0;
        timeText.setPosition(300,0);
        timeText.setString("timt : "+to_string(t)+"sec");}

        Event e;

        while (app.pollEvent(e))
        {
            if (e.type == Event::Closed)
            {
                app.close();
            }


            if (Keyboard::isKeyPressed(Keyboard::Right) && angle <=44)
            {
                angle=angle+1;
                Rocket.rotate(+1);
                fire.rotate(+1);
                fire1.rotate(+1);
                fire2.rotate(+1);
                fire3.rotate(+1);
            }
            if (Keyboard::isKeyPressed(Keyboard::Left) && angle >=-44)
            {
                angle=angle-1;
                Rocket.rotate(-1);
                fire.rotate(-1);
                fire1.rotate(-1);
                fire2.rotate(-1);
                fire3.rotate(-1);
            }
            if (Keyboard::isKeyPressed(Keyboard::Up)&& speed <3.5) speed=speed+1;

            if (Keyboard::isKeyPressed(Keyboard::Down)&& speed >0) speed=speed-1;
        }

        //logic
        if(speed>0)sound.play();
        //position of rockets
        obsticales[0].setPosition(abs(0-(obsticales[0].getGlobalBounds().width/2)),app.getSize().y-obsticales[0].getGlobalBounds().height+(safeArea.getGlobalBounds().height));
        obsticales[1].setPosition((obsticales[0].getGlobalBounds().width/3)-30+
                                  (obsticales[1].getGlobalBounds().width/2),app.getSize().y-obsticales[1].getGlobalBounds().height/3);
        obsticales[2].setPosition((obsticales[0].getGlobalBounds().width/3)+(obsticales[1].getGlobalBounds().width/2)+(obsticales[2].getGlobalBounds().width/2)+
                                  +50+(safeArea.getGlobalBounds().width),app.getSize().y-obsticales[2].getGlobalBounds().height/3);
        obsticales[3].setPosition((obsticales[0].getGlobalBounds().width/3)+(obsticales[1].getGlobalBounds().width/2)+(obsticales[2].getGlobalBounds().width/2)+
                                  (safeArea.getGlobalBounds().width)+
                                  (obsticales[3].getGlobalBounds().width/2),app.getSize().y-obsticales[3].getGlobalBounds().height+(safeArea.getGlobalBounds().height));

        Rocket.move(0,dy); //gravity
        movementx= +abs(speed*sin((180/3.14)*angle));
        movementy= -abs(speed*cos((180/3.14)*angle));

        if (Rocket.getPosition().x<=0-100)
        {
           // Rocket.setPosition(sf::Vector2f(50,Rocket.getPosition().y));
            gameOver = true;
        }
        if (Rocket.getPosition().y<=0-175)
        {   gameOver = true;
            //Rocket.setPosition(sf::Vector2f(Rocket.getPosition().x,87.5));
        }
        if (Rocket.getPosition().y>=app.getSize().y+175)
        {   gameOver = true;
            //Rocket.setPosition(sf::Vector2f(Rocket.getPosition().x,app.getSize().y-87.5));
        }
        if (Rocket.getPosition().x>=app.getSize().x-50)
        {
            Rocket.setPosition(sf::Vector2f(app.getSize().x-50,Rocket.getPosition().y));
        }
        if(angle<=0)
        {
            Rocket.move(-movementx,movementy);
        }
        else
        {
            Rocket.move(movementx,movementy);
        }


        if(PixelPerfectTest(Rocket,safeArea) && angle == 0)
        {
            win=true;
        }
        else if (PixelPerfectTest(Rocket,safeArea) && angle != 0) gameOver=true;
        for(int i=0; i<4; i++)
        {
            if(PixelPerfectTest(Rocket,obsticales[i]))
            {
                gameOver=true;
            }
        }
        if (fuel ==0) speed =0;
        //drawing
        app.clear(Color(110,65,46));
        if (gameOver)
        {
            //  app.draw(background);
            app.draw(gameoverText);
            sound1.play();


        }
        else if (win)
        {
            //  app.draw(background);
            Rocket.setPosition(Rocket.getPosition().x,5);
            app.draw(WinText);

        }

        else
        {
            app.draw(Rocket);
            app.draw(safeArea);
            app.draw(obsticales[0]);
            app.draw(obsticales[3]);
            app.draw(obsticales[2]);
            app.draw(obsticales[1]);
            angleNum.setString(to_string(angle));
            app.draw(timeText);
            timeText.setFillColor(sf::Color::White);
            app.draw(speedVerticalText);
            speedVertical.setString(to_string(movementy));
            app.draw(speedVertical);

            app.draw(speedhorizontalText);
            speedhorizontal.setString(to_string(movementx));
            app.draw(speedhorizontal);


            app.draw(angleText);
            app.draw(angleNum);
            if(speed==1)
            {
                fuel= fuel -10;
                fire.setOrigin(Rocket.getOrigin().x+10,Rocket.getOrigin().y-105);
                fire.setPosition(Rocket.getPosition().x,Rocket.getPosition().y);
                app.draw (fire);

            }
            else if (speed==2)
            {
                fuel= fuel -50;
                fire1.setOrigin(Rocket.getOrigin().x+10,Rocket.getOrigin().y-105);
                fire1.setPosition(Rocket.getPosition().x,Rocket.getPosition().y);
                app.draw (fire1);

            }
            else if (speed==3)
            {
                fuel= fuel -100;
                fire2.setOrigin(Rocket.getOrigin().x+10,Rocket.getOrigin().y-105);
                fire2.setPosition(Rocket.getPosition().x,Rocket.getPosition().y);
                app.draw (fire2);
            }
            else if (speed==4)
            {
                fuel= fuel -150;
                fire3.setOrigin(Rocket.getOrigin().x+10,Rocket.getOrigin().y-105);
                fire3.setPosition(Rocket.getPosition().x,Rocket.getPosition().y);
                app.draw (fire3);
            }
            /*else if (speed==0.8)
            {
                 fire3.setOrigin(Rocket.getOrigin().x+10,Rocket.getOrigin().y-105);
                fire3.setPosition(Rocket.getPosition().x,Rocket.getPosition().y);
                app.draw (fire3);
                        }*/
        }
        app.display();
    }


}
