#include <SFML/Graphics.hpp>
#include <vector>
#include <cmath>

struct Charge {
    sf::Vector2f position;
    float value; // 单位：纳库仑(nC)
};

int main() {
    // 创建窗口
    sf::RenderWindow window(sf::VideoMode(800, 600), "两点电荷电场");
    
    // 创建电荷 (正电荷+负电荷)
    std::vector<Charge> charges;
    charges.push_back({ {200, 300}, 5.0 });  // 正电荷 (红色)
    charges.push_back({ {600, 300}, -5.0 }); // 负电荷 (蓝色)
    
    // 电场线计算函数
    auto calcField = [&](sf::Vector2f point) {
        sf::Vector2f total(0,0);
        for (const auto& charge : charges) {
            sf::Vector2f r = point - charge.position;
            float dist = std::sqrt(r.x*r.x + r.y*r.y);
            if (dist < 5.f) continue;
            float k = 9e9;
            float magnitude = k * charge.value * 1e-9 / (dist * dist);
            total += magnitude * r / dist;
        }
        return total;
    };

    // 主循环
    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        
        window.clear(sf::Color::Black);
        
        // 绘制电荷
        for (const auto& charge : charges) {
            sf::CircleShape circle(20);
            circle.setPosition(charge.position.x - 20, charge.position.y - 20);
            circle.setFillColor(charge.value > 0 ? sf::Color::Red : sf::Color::Blue);
            window.draw(circle);
        }
        
        // 绘制电场线
        for (int y = 0; y < 600; y += 20) {
            for (int x = 0; x < 800; x += 20) {
                sf::Vector2f field = calcField(sf::Vector2f(x, y));
                float length = std::sqrt(field.x*field.x + field.y*field.y);
                if (length > 50) { // 只绘制足够强的电场
                    sf::Vertex line[] = {
                        sf::Vertex(sf::Vector2f(x, y), sf::Color::Green),
                        sf::Vertex(sf::Vector2f(x + field.x/50, y + field.y/50), sf::Color::Yellow)
                    };
                    window.draw(line, 2, sf::Lines);
                }
            }
        }
        
        window.display();
    }
    return 0;
}