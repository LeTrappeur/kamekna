#include <SFML/graphics.hpp>
#include <cmath>
#include<iostream>
#include<vector>

int Orientation(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p)
{
    // Determinant
    int Orin = (p2.x - p1.x) * (p.y - p1.y) - (p.x - p1.x) * (p2.y - p1.y);

    if (Orin > 0)
        return -1; //          (* Orientaion is to the left-hand side  *)
    if (Orin < 0)
        return 1; // (* Orientaion is to the right-hand side *)

    return 0; //  (* Orientaion is neutral aka collinear  *)
}

sf::Vector2f getMostLeft(const std::vector< sf::Vector2f >& pts)
{
    sf::Vector2f ptLeft = pts[0];
    for(int i = 1; i < pts.size() ; i++)
        {
            if(pts[i].x < ptLeft.x)
                ptLeft = pts[i];
        }
    return ptLeft;
}

std::vector< sf::Vector2f > ConvexHull(std::vector< sf::Vector2f > points)
        {
            std::vector< sf::Vector2f > hull;

            // get leftmost point
            sf::Vector2f vPointOnHull = getMostLeft(points);
            sf::Vector2f vEndpoint;
            do
            {
                hull.push_back(vPointOnHull);
                vEndpoint = points[0];

                for (int i = 1; i < points.size(); i++)
                {
                    if ((vPointOnHull == vEndpoint)
                        || (Orientation(vPointOnHull, vEndpoint, points[i]) == -1))
                    {
                        vEndpoint = points[i];
                    }
                }

                vPointOnHull = vEndpoint;

            }
            while (vEndpoint != hull[0]);

            return hull;
}


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Asteroids prototype");

    std::vector< sf::Vector2f > randomPoints(5);
    randomPoints[0] = sf::Vector2f(100,500);
    randomPoints[1] = sf::Vector2f(120,375);
    randomPoints[2] = sf::Vector2f(400,300);
    randomPoints[3] = sf::Vector2f(50,500);
    randomPoints[4] = sf::Vector2f(70,220);

    std::vector< sf::Vector2f > sortPoints;
    sortPoints = ConvexHull(randomPoints);

    while (window.isOpen())
    {
        // Process events
        sf::Event event;
        while (window.pollEvent(event))
        {
            // Close window : exit
            if (event.type == sf::Event::Closed)
                window.close();
        }
        // Clear screen
        window.clear(sf::Color::White);

        for(int i=0; i<5; i++)
        {
            sf::RectangleShape point(sf::Vector2f(5,5));
            point.setOrigin(2.5f,2.5f);
            point.setFillColor(sf::Color::Red);
            point.setPosition(randomPoints.at(i));

            window.draw(point);
        }

        for(int i=0; i< sortPoints.size(); i++)
        {
            sf::ConvexShape envelop(sortPoints.size());
            envelop.setFillColor(sf::Color(80, 170, 200, 200));
            for(int i=0; i<sortPoints.size(); i++)
            {
                envelop.setPoint(i, sortPoints[i]);
            }

            window.draw(envelop);
        }

        // Update the window
        window.display();
    }
    return EXIT_SUCCESS;
}
