#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <sstream>

sf::Sprite Cactus1, Cactus2, Pterodactyl, Background1, Background2, Dino, Play, MenuBg, Exit;
sf::Texture texture1, texture2, texture3, texture4, texture5, texture6, texture7, PlayMenu, Menu, ExitMenu;
sf::Image image1, image2, image3, image4, image5, image6, image7;

void menu(sf::RenderWindow & window)
{
    Menu.loadFromFile("Menu.png");
    PlayMenu.loadFromFile("Play.png");
    ExitMenu.loadFromFile("Exit.png");

    MenuBg.setTexture(Menu);
    Play.setTexture(PlayMenu);
    Exit.setTexture(ExitMenu);

    bool IsMenu = 1;
    int MenuNum = 0;
    Play.setPosition(390, 390);
    Exit.setPosition(525, 625);

    while(IsMenu)
    {
        Play.setColor(sf::Color::White);
        Exit.setColor(sf::Color::White);
        MenuNum = 0;

        if (sf::IntRect(390, 390, 600, 200).contains(sf::Mouse::getPosition(window))){
            Play.setColor(sf::Color::Blue);
            MenuNum=1;
        }
        if (sf::IntRect(500, 600, 300, 150).contains(sf::Mouse::getPosition(window))){
            Exit.setColor(sf::Color::Blue);
            MenuNum=2;
        }


        if(sf::Mouse::isButtonPressed(sf::Mouse::Left)){
            if(MenuNum==1)
                IsMenu=false;
            if(MenuNum==2){
                IsMenu=false;
                window.close();
            }
        }

        window.draw(MenuBg);
        window.draw(Exit);
        window.draw(Play);
        window.display();
    }
}

bool StartGame()
{
    sf::RenderWindow window(sf::VideoMode(1500, 900), "Dino");

    ////Icon
    sf::Image icon;
    icon.loadFromFile("Icon.png");
    window.setIcon(32, 32, icon.getPixelsPtr());
    ////Icon

    menu(window);

    srand(time(0));

    ////Texture
    image1.loadFromFile("DinoStart.png");
    texture1.loadFromImage(image1);
    Dino.setTexture(texture1);
    Dino.setScale(5, 5);

    image2.loadFromFile("DinoRun.png");
    texture2.loadFromImage(image2);

    image3.loadFromFile("DinoDie.png");
    texture3.loadFromImage(image3);

    image4.loadFromFile("DinoUnder.png");
    texture4.loadFromImage(image4);

    image5.loadFromFile("Cactus.png");
    texture5.loadFromImage(image5);
    Cactus1.setTexture(texture5);
    Cactus1.setPosition(1600,625);
    Cactus1.setTextureRect(sf::IntRect(0,0,15,33));
    Cactus1.setScale(3, 3);

    Cactus2.setTexture(texture5);
    Cactus2.setPosition(2100,625);
    Cactus2.setTextureRect(sf::IntRect(0,0,15,33));
    Cactus2.setScale(3, 3);

    image6.loadFromFile("Pteriodactyl.png");
    texture6.loadFromImage(image6);
    Pterodactyl.setTexture(texture6);
    Pterodactyl.setPosition(2000, 100);
    Pterodactyl.setScale(4, 4);

    image7.loadFromFile("Background.png");
    texture7.loadFromImage(image7);
    Background1.setTexture(texture7);
    Background1.setPosition(0,0);
    Background1.setTextureRect(sf::IntRect(0,0,3000,900));

    Background2.setTexture(texture7);
    Background2.setPosition(3000, 0);
    Background2.setTextureRect(sf::IntRect(0,0,3000,900));
    ////Texture

    ////Text
    sf::Font Font;
    Font.loadFromFile("Font.ttf");

    sf::Text text("", Font, 100);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    text.setStyle(sf::Text::Bold);

    sf::Text Help("", Font, 50);

    sf::Text Exit("", Font, 35);

    sf::Text Start("", Font, 35);

    sf::Text GameOver("", Font, 250);
    text.setFillColor(sf::Color::White);
    text.setOutlineColor(sf::Color::Black);
    GameOver.setStyle(sf::Text::Bold);
    ////Text

    ////Sound
    sf::SoundBuffer JumpBuffer;
    JumpBuffer.loadFromFile("Jump.ogg");
    sf::Sound Jump(JumpBuffer);

    sf::SoundBuffer DieBuffer;
    DieBuffer.loadFromFile("Die.ogg");
    sf::Sound Die(DieBuffer);
    ////Sound

    sf::Clock clock;

    sf::FloatRect rect;
    rect.top=520;
    float dy=0;

    bool OnFloor=true;
    bool Life=true;
    bool Crawling=false;
    bool start=true;
    bool pause=false;
    bool exit=false;

    int CactusNumber=1;
    int BackgrondNumber=1; ////For Background

    float FrameNumber1=0;
    float FrameNumber2=0;
    float FrameNumber3=0;
    float V=0; ////For Background and Enemies
    float x=0;
    float Distance=0; ////For Background
    float xCactus1=1700; ////For Cactus
    float xCactus2=2200;
    float xPteriodactyl=2000;
    float CactusDistance1=0;
    float CactusDistance2=0;
    float PterodactylDistance=0;

    ////Music
    sf::Music music;
    music.openFromFile("Music.ogg");
    music.play();
    music.setVolume(5);
    music.setLoop(true);
    ////Music

    while (window.isOpen())
    {
        ////Timer
        float time = clock.getElapsedTime().asMicroseconds();
        clock.restart();
        time=time/800;
        ////Timer

        ////Level
        if (start==true) {
            Start.setString("Choose a difficulty level from 1 to 3 and press F2");
            Start.setPosition(50,800);
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num1)) {
                x=0.2;
                start=false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num2)) {
                x=0.25;
                start=false;
            }
            if(sf::Keyboard::isKeyPressed(sf::Keyboard::Num3)) {
                x=0.3;
                start=false;
            }
        }
        ////Level

        ////Close
        sf::Event event;
        while (window.pollEvent(event))
            if (event.type == sf::Event::Closed)
                window.close();

        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)&&pause==false&&start==false) {
            V = 0;
            pause = true;
            exit = true;
            Exit.setString("Are you sure? If you want to exit, press ENTER, otherwise press F2");
            Exit.setPosition(50,800);
        }
        if(exit==true&&sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            return false;
        ////Close

        ////Help
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F1)&&start==false&&exit==false) {
            V = 0;
            Help.setString("Help: Space - jump DOWN - crawling");
            Help.setPosition(50,800);
            pause = true;
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::F2)) {
            if (Life==true)
                V = x;
            Help.setString("");
            Exit.setString("");
            Start.setString("");
            exit = false;
            pause = false;
        }
        ////Help

        ////Background
        Background1.move(0-V*time, 0);
        Background2.move(0-V*time, 0);
        Distance+=V*time;

        if(Distance>3000){
            if(BackgrondNumber%2!=0){
                BackgrondNumber++;
                Distance=0;
                Background1.setPosition(3000, 0);
            }
            else{
                BackgrondNumber++;
                Distance=0;
                Background2.setPosition(3000, 0);
            }
        }
        ////Background

        ////Cactus
        Cactus1.move(0-V*time, 0);
        Cactus2.move(0-V*time, 0);
        CactusDistance1+=V*time;
        CactusDistance2+=V*time;

        if(CactusNumber%2!=0){
            if(CactusDistance1>xCactus1+50){
                CactusNumber++;
                xCactus1=1500+rand()%500;
                Cactus1.setPosition(0+xCactus1, 625);
                CactusDistance1=0;
            }
        }
        else{
            if(CactusDistance2>xCactus2+50){
                CactusNumber++;
                xCactus2=2000+rand()%500;
                Cactus2.setPosition(0+xCactus2, 625);
                CactusDistance2=0;
            }
        }
        ////Cactus

        ////Die
        sf::FloatRect DinoBounds=Dino.getGlobalBounds();
        sf::FloatRect Cactus1Bounds=Cactus1.getGlobalBounds();
        sf::FloatRect Cactus2Bounds=Cactus2.getGlobalBounds();

        if(DinoBounds.intersects(Cactus1Bounds))
            Life = false;
        if(DinoBounds.intersects(Cactus2Bounds))
            Life = false;

        if(Life==false){
            if(Crawling==true)
                Dino.setPosition(100, 520);
            Die.play();
            V=0;
            music.pause();
            GameOver.setString("GAME OVER");
            GameOver.setPosition(35,260);
            Dino.setTexture(texture3);
            FrameNumber3=0;
            Dino.setTextureRect(sf::IntRect(10,0,40,41));
        }
        ////Die

        ////Run
        if(OnFloor==true&&Life==true&&pause==false){
            FrameNumber1+=0.01*time;
            if(FrameNumber1>3)
                FrameNumber1-=3;
            Dino.setPosition(100,520);
            Dino.setTexture(texture2);
            Dino.setTextureRect(sf::IntRect(int(FrameNumber1)*50+10, 0, 40, 41));
        }
        ////Run

        ////PterodactylAnimation
        if (pause==false) {
            FrameNumber3+=0.0035*time;
            if(FrameNumber3>2)
                FrameNumber3-=2;
            Pterodactyl.setTexture(texture6);
            Pterodactyl.setTextureRect(sf::IntRect(int(FrameNumber3)*32, int(FrameNumber3)*6, 32, 27));
        }
        ////PterodactylAnimation

        ////Pterodactyl
        Pterodactyl.move(0-2*V*time, 0);
        PterodactylDistance+=2*V*time;

        if(PterodactylDistance>xPteriodactyl+100) {
            xPteriodactyl = 8000 + rand() % 1000;
            Pterodactyl.setPosition(0 + xPteriodactyl, 100+rand()%50);
            PterodactylDistance = 0;
        }
        ////Pterodactyl

        ////Crawling
        if(pause==false&&OnFloor==true&&Life==true&&(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))){
            Crawling=true;
            FrameNumber2+=0.0065*time;
            if(FrameNumber2>2)
                FrameNumber2-=2;
            Dino.setPosition(90,610);
            Dino.setTexture(texture4);
            Dino.setTextureRect(sf::IntRect(int(FrameNumber2)*50, 0, 50, 23));
        }
        ////Crawling

        ////Jump
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space)&&OnFloor==true&&Life==true&&pause==false) {
            OnFloor = false;
            Jump.play();
            dy=-0.5;
            Dino.setTexture(texture1);
            Dino.setPosition(100, 520);
            Dino.setTextureRect(sf::IntRect(10,0,40,41));
        }

        if(!OnFloor&&pause==false){
            dy+=0.0005*time;
            rect.top+=dy*time;
            if(rect.top>520){
                rect.top=520;
                dy=0;
                OnFloor=true;
            }
            Dino.setPosition(100, 0+rect.top);
        }
        ////jump

        ////Draw
        window.draw(Background2);
        window.draw(Background1);
        window.draw(GameOver);
        window.draw(Help);
        window.draw(Start);
        window.draw(Dino);
        window.draw(Cactus1);
        window.draw(Cactus2);
        window.draw(Exit);
        window.draw(Pterodactyl);
        window.display();
        ////Draw
    }
}

void GameRunning()
{
    if(StartGame())
        GameRunning();
}

int main()
{
    GameRunning();
    return 0;
}