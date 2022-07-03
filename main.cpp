#include <iostream>
#include <ccomplex>
#include <cmath>
#include <vector>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

#define PI 3.1415926535897932384626433832795028841971
#define G (6.67430*pow(10,-11))
#define WIDTH 2880
#define HEIGHT 1800
#define FPS 99999 //120
#define CIRCLE 200

using namespace std;

sf::RenderWindow Window(sf::VideoMode(WIDTH, HEIGHT), "Complex Graphic");

double GetAngle(complex<double> a, complex<double> b)
{
    double c = a.real()*b.real() - a.imag()*b.imag();
    return acos(c/abs(a)/abs(b));
}
complex<double> Homothety(complex<double> a, double k, complex<double> h)
{
    return k*(a-h);
}

/*void DrawDot(complex<double> r)
{
    sf::Vertex circle[];
    Window.draw(,,sf::CircleShape);
}//*/

void DrawLine(complex<double> a, complex<double> b)
{
    sf::Vertex line[] =
            {
                    sf::Vertex(sf::Vector2f(a.real() + WIDTH / 2, a.imag() + HEIGHT / 2)),
                    sf::Vertex(sf::Vector2f(b.real() + WIDTH / 2, b.imag() + HEIGHT / 2))
            };

    Window.draw(line, 2, sf::Lines);
}

struct polygon{
    unsigned int N;
    bool IsRegular;

    vector<complex<double>> vertex;

    polygon(int n, bool reg)
    {
        N = n;
        IsRegular = reg;
    }

    void SetPoints(double ang = 0, complex<double>* dots = nullptr)
    {
        if(IsRegular)
        {
            for(int n = 0; n < N; ++n)
                vertex.push_back( {cos(2 * PI * n / N + ang), sin(2 * PI * n / N + ang)} );
        }
        else
        {
            for (int n = 0; n < N; ++n)
                vertex.push_back(dots[n]);
        }
    }

    void RotateRelPoint(double ang, complex<double> P = {0, 0})
    {
        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] -= P;

        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] = {vertex[i].real()*cos(ang) - vertex[i].imag()*sin(ang), vertex[i].imag()*cos(ang) + vertex[i].real()*sin(ang)};

        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] += P;
    }

    void RotateCentral(double ang)
    {
        complex<double> C;
        for(int i = 0; i < vertex.size(); ++i)
            C += vertex[i];

        C = (1.0/(double)N) * C;

        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] -= C;

        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] = {vertex[i].real()*cos(ang) - vertex[i].imag()*sin(ang), vertex[i].imag()*cos(ang) + vertex[i].real()*sin(ang)};

        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] += C;
    }

    void MoveTo(complex<double> r)
    {
        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] += r;
    }

    void Reflect(complex<double> ax)
    {
        double betta = GetAngle(ax, {1,0});

        RotateRelPoint(-betta);

        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] = {vertex[i].real(), -vertex[i].imag()};

        RotateRelPoint(betta);
    }

    void HomothetyPol(double k, complex<double> h)
    {
        for(int i = 0; i < vertex.size(); ++i)
            vertex[i] = Homothety(vertex[i], k, h);
    }

    void DisplayVert()
    {
        for(int i = 0; i < vertex.size(); ++i)
            cout << vertex[i] << endl;
        cout << endl;
    }

    void Draw()
    {
        for(int i = 0; i < vertex.size() - 1; ++i)
            DrawLine(vertex[i],vertex[i+1]);
        DrawLine(vertex[0], vertex[N-1]);
    }//*/
};

struct surface{
    vector<polygon> figures;

    surface(polygon* mas, unsigned long int n)
    {
        for(int i = 0; i < n; ++i)
        {
            figures.push_back(mas[i]);
        }
    }

    void RotateRelPoint(double ang, complex<double> P = {0, 0})
    {
        for(int j = 0; j < figures.size(); ++j)
        {
            for (int i = 0; i < figures[j].vertex.size(); ++i)
                figures[j].vertex[i] -= P;

            for (int i = 0; i < figures[j].vertex.size(); ++i)
                figures[j].vertex[i] = {figures[j].vertex[i].real() * cos(ang) - figures[j].vertex[i].imag() * sin(ang), figures[j].vertex[i].imag() * cos(ang) + figures[j].vertex[i].real() * sin(ang)};

            for (int i = 0; i < figures[j].vertex.size(); ++i)
                figures[j].vertex[i] += P;
        }
    }

    void RotateCentral(double ang)
    {
        complex<double> C;
        for(int j = 0; j < figures.size(); ++j) {
            for (int i = 0; i < figures[j].vertex.size(); ++i)
                C += figures[j].vertex[i];
        }

        unsigned int n = 0;
        for(int i = 0; i < figures.size(); ++ i)
            n += figures[i].N;

        C = (1.0 / (double) n) * C;


        for(int j = 0; j < figures.size(); ++j)
        {
            for (int i = 0; i < figures[j].vertex.size(); ++i)
                figures[j].vertex[i] -= C;

            for (int i = 0; i < figures[j].vertex.size(); ++i)
                figures[j].vertex[i] = {figures[j].vertex[i].real() * cos(ang) - figures[j].vertex[i].imag() * sin(ang), figures[j].vertex[i].imag() * cos(ang) + figures[j].vertex[i].real() * sin(ang)};

            for (int i = 0; i < figures[j].vertex.size(); ++i)
                figures[j].vertex[i] += C;
        }
    }

    void MoveTo(complex<double> r)
    {
        for(int j = 0; j < figures.size(); ++j)
        {
            for (int i = 0; i < figures[j].vertex.size(); ++i)
                figures[j].vertex[i] += r;
        }
    }

    void Reflect(complex<double> ax)
    {
        double betta = GetAngle(ax, {1,0});

        for(int j = 0; j < figures.size(); ++j)
        {
            figures[j].RotateRelPoint(-betta);

            for (int i = 0; i < figures[j].vertex.size(); ++i)
                figures[j].vertex[i] = {figures[j].vertex[i].real(), -figures[j].vertex[i].imag()};

            figures[j].RotateRelPoint(betta);
        }
    }

    void HomothetyPol(double k, complex<double> h)
    {
        for(int j = 0; j < figures.size(); j++)
        {
            for (int i = 0; i < figures[j].vertex.size(); ++i)
                figures[j].vertex[i] = Homothety(figures[j].vertex[i], k, h);
        }
    }

    void DisplayVert()
    {
        for(int j = 0; j < figures.size(); ++j)
        {
            cout << "Polygon number " << j << ':' << endl;
            for (int i = 0; i < figures[j].vertex.size(); ++i)
                cout << figures[j].vertex[i] << endl;
            cout << endl;
        }
    }

    void Draw()
    {
        for(int j = 0; j < figures.size(); ++j)
        {
            for (int i = 0; i < figures[j].vertex.size() - 1; ++i)
                DrawLine(figures[j].vertex[i], figures[j].vertex[i + 1]);
            DrawLine(figures[j].vertex[0], figures[j].vertex[figures[j].N - 1]);
        }
    }//*/
};//*/



int main() {

    Window.setFramerateLimit(FPS);

    polygon O1(CIRCLE, true);
    O1.SetPoints();
    O1.MoveTo({-1,0});

    polygon O2(CIRCLE, true);
    O2.SetPoints();
    O2.MoveTo({1,0});

    polygon O3(CIRCLE, true);
    O3.SetPoints();
    O3.MoveTo({0,5});

    polygon Rect(4, false);
    complex<double> RectV[4] = {{-1, 5}, {1, 5}, {1, 0}, {-1, 0}};
    Rect.SetPoints(0, RectV);

    polygon magen[4] = {O1, O2, O3, Rect};

    surface Magen(magen, 4);

    Magen.HomothetyPol(100, {0, 0});

    while (Window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;
        while (Window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                Window.close();
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
            Magen.RotateCentral(PI/180);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
            Magen.RotateCentral(-PI/180);
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
            Magen.MoveTo({0, -1});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
            Magen.MoveTo({0, 1});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
            Magen.MoveTo({-1, 0});
        }
        if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
            Magen.MoveTo({1, 0});
        }//*/

        // clear the window with black color
        Window.clear();
        // draw everything here...
        // window.draw(...);

        Magen.Draw();
        // end the current frame
        Window.display();
    }

    return 0;
}
