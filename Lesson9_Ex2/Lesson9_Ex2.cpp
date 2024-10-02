#include <iostream>
#include <cmath>
#include <string>

#ifndef M_PI
#define M_PI 3.14
#endif

enum Color { None, Red, Green, Blue };

std::string colorToString(Color color) {
    switch (color) {
    case Red: return "Red";
    case Green: return "Green";
    case Blue: return "Blue";
    default: return "None";
    }
}

class Shape {
protected:
    double x, y;
    Color color;

public:
    Shape(double x, double y, Color color) : x(x), y(y), color(color) {}

    std::string getColor() const {
        return colorToString(color);
    }

    virtual double area() const = 0;

    virtual void boundingBox() const = 0;

    virtual ~Shape() {}
};

class Circle : public Shape {
private:
    double radius;

public:
    Circle(double x, double y, Color color, double radius)
        : Shape(x, y, color), radius(radius) {}

    double area() const override {
        return M_PI * radius * radius;
    }

    void boundingBox() const override {
        std::cout << "Bounding box: (" << x - radius << ", " << y - radius
            << ") to (" << x + radius << ", " << y + radius << ")\n";
    }
};

class Square : public Shape {
private:
    double side;

public:
    Square(double x, double y, Color color, double side)
        : Shape(x, y, color), side(side) {}

    double area() const override {
        return side * side;
    }

    void boundingBox() const override {
        std::cout << "Bounding box: (" << x - side / 2 << ", " << y - side / 2
            << ") to (" << x + side / 2 << ", " << y + side / 2 << ")\n";
    }
};

class Triangle : public Shape {
private:
    double side;

public:
    Triangle(double x, double y, Color color, double side)
        : Shape(x, y, color), side(side) {}

    double area() const override {
        return (side * side * std::sqrt(3)) / 4;
    }

    void boundingBox() const override {
        double height = (std::sqrt(3) / 2) * side;
        std::cout << "Bounding box: (" << x - side / 2 << ", " << y - height / 2
            << ") to (" << x + side / 2 << ", " << y + height / 2 << ")\n";
    }
};

class Rectangle : public Shape {
private:
    double width, height;

public:
    Rectangle(double x, double y, Color color, double width, double height)
        : Shape(x, y, color), width(width), height(height) {}

    double area() const override {
        return width * height;
    }

    void boundingBox() const override {
        std::cout << "Bounding box: (" << x - width / 2 << ", " << y - height / 2
            << ") to (" << x + width / 2 << ", " << y + height / 2 << ")\n";
    }
};

int main() {
    std::string command;
    while (true) {
        std::cout << "Enter command (circle, square, triangle, rectangle, exit): ";
        std::cin >> command;

        if (command == "circle") {
            double x, y, radius;
            int colorInput;
            std::cout << "Enter x, y, radius, color (0:None, 1:Red, 2:Green, 3:Blue): ";
            std::cin >> x >> y >> radius >> colorInput;
            Circle circle(x, y, static_cast<Color>(colorInput), radius);
            std::cout << "Color: " << circle.getColor() << "\n";
            std::cout << "Area: " << circle.area() << "\n";
            circle.boundingBox();
        }
        else if (command == "square") {
            double x, y, side;
            int colorInput;
            std::cout << "Enter x, y, side, color (0:None, 1:Red, 2:Green, 3:Blue): ";
            std::cin >> x >> y >> side >> colorInput;
            Square square(x, y, static_cast<Color>(colorInput), side);
            std::cout << "Color: " << square.getColor() << "\n";
            std::cout << "Area: " << square.area() << "\n";
            square.boundingBox();
        }
        else if (command == "triangle") {
            double x, y, side;
            int colorInput;
            std::cout << "Enter x, y, side, color (0:None, 1:Red, 2:Green, 3:Blue): ";
            std::cin >> x >> y >> side >> colorInput;
            Triangle triangle(x, y, static_cast<Color>(colorInput), side);
            std::cout << "Color: " << triangle.getColor() << "\n";
            std::cout << "Area: " << triangle.area() << "\n";
            triangle.boundingBox();
        }
        else if (command == "rectangle") {
            double x, y, width, height;
            int colorInput;
            std::cout << "Enter x, y, width, height, color (0:None, 1:Red, 2:Green, 3:Blue): ";
            std::cin >> x >> y >> width >> height >> colorInput;
            Rectangle rectangle(x, y, static_cast<Color>(colorInput), width, height);
            std::cout << "Color: " << rectangle.getColor() << "\n";
            std::cout << "Area: " << rectangle.area() << "\n";
            rectangle.boundingBox();
        }
        else if (command == "exit") {
            break;
        }
        else {
            std::cout << "Unknown command. Try again.\n";
        }
    }

    return 0;
}
