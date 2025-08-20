#include <iostream>
#include <string>
#include <vector>
#include <memory>

// Pure interface - all functions are pure virtual
class Drawable {
public:
    virtual ~Drawable() = default;  // Virtual destructor
    
    // Pure virtual functions define the interface contract
    virtual void draw() const = 0;
    virtual void setPosition(int x, int y) = 0;
    virtual void setColor(const std::string& color) = 0;
};

// Another interface for objects that can be resized
class Resizable {
public:
    virtual ~Resizable() = default;
    
    virtual void resize(double factor) = 0;
    virtual double getArea() const = 0;
};

// Interface for objects that can be serialized
class Serializable {
public:
    virtual ~Serializable() = default;
    
    virtual std::string serialize() const = 0;
    virtual void deserialize(const std::string& data) = 0;
};

// Concrete class implementing multiple interfaces
class Rectangle : public Drawable, public Resizable, public Serializable {
private:
    int x, y;
    double width, height;
    std::string color;

public:
    Rectangle(int x, int y, double w, double h, const std::string& c)
        : x(x), y(y), width(w), height(h), color(c) {}
    
    // Implement Drawable interface
    void draw() const override {
        std::cout << "Drawing " << color << " rectangle at (" 
                  << x << "," << y << ") size " << width << "x" << height << std::endl;
    }
    
    void setPosition(int newX, int newY) override {
        x = newX;
        y = newY;
    }
    
    void setColor(const std::string& newColor) override {
        color = newColor;
    }
    
    // Implement Resizable interface
    void resize(double factor) override {
        width *= factor;
        height *= factor;
    }
    
    double getArea() const override {
        return width * height;
    }
    
    // Implement Serializable interface
    std::string serialize() const override {
        return "Rectangle:" + std::to_string(x) + "," + std::to_string(y) + "," +
               std::to_string(width) + "," + std::to_string(height) + "," + color;
    }
    
    void deserialize(const std::string& data) override {
        // Simple parsing (real implementation would be more robust)
        size_t pos = data.find(':');
        if (pos != std::string::npos) {
            std::string values = data.substr(pos + 1);
            // Parse comma-separated values...
            std::cout << "Deserializing: " << values << std::endl;
        }
    }
};

class Circle : public Drawable, public Resizable {
private:
    int x, y;
    double radius;
    std::string color;

public:
    Circle(int x, int y, double r, const std::string& c)
        : x(x), y(y), radius(r), color(c) {}
    
    // Implement Drawable interface
    void draw() const override {
        std::cout << "Drawing " << color << " circle at (" 
                  << x << "," << y << ") radius " << radius << std::endl;
    }
    
    void setPosition(int newX, int newY) override {
        x = newX;
        y = newY;
    }
    
    void setColor(const std::string& newColor) override {
        color = newColor;
    }
    
    // Implement Resizable interface
    void resize(double factor) override {
        radius *= factor;
    }
    
    double getArea() const override {
        return 3.14159 * radius * radius;
    }
};

// Interface for input/output operations
class IODevice {
public:
    virtual ~IODevice() = default;
    
    virtual bool open() = 0;
    virtual void close() = 0;
    virtual bool isOpen() const = 0;
};

class FileDevice : public IODevice {
private:
    std::string filename;
    bool opened;

public:
    explicit FileDevice(const std::string& name) : filename(name), opened(false) {}
    
    bool open() override {
        std::cout << "Opening file: " << filename << std::endl;
        opened = true;
        return opened;
    }
    
    void close() override {
        if (opened) {
            std::cout << "Closing file: " << filename << std::endl;
            opened = false;
        }
    }
    
    bool isOpen() const override {
        return opened;
    }
};

class NetworkDevice : public IODevice {
private:
    std::string address;
    bool connected;

public:
    explicit NetworkDevice(const std::string& addr) : address(addr), connected(false) {}
    
    bool open() override {
        std::cout << "Connecting to: " << address << std::endl;
        connected = true;
        return connected;
    }
    
    void close() override {
        if (connected) {
            std::cout << "Disconnecting from: " << address << std::endl;
            connected = false;
        }
    }
    
    bool isOpen() const override {
        return connected;
    }
};

// Interface segregation principle example
class BasicPrinter {
public:
    virtual ~BasicPrinter() = default;
    virtual void print(const std::string& document) = 0;
};

class AdvancedPrinter {
public:
    virtual ~AdvancedPrinter() = default;
    virtual void printColor(const std::string& document) = 0;
    virtual void scan(const std::string& document) = 0;
    virtual void fax(const std::string& document) = 0;
};

// Simple printer only implements basic functionality
class SimplePrinter : public BasicPrinter {
public:
    void print(const std::string& document) override {
        std::cout << "Printing: " << document << std::endl;
    }
};

// Multi-function printer implements both interfaces
class MultiFunctionPrinter : public BasicPrinter, public AdvancedPrinter {
public:
    void print(const std::string& document) override {
        std::cout << "Basic printing: " << document << std::endl;
    }
    
    void printColor(const std::string& document) override {
        std::cout << "Color printing: " << document << std::endl;
    }
    
    void scan(const std::string& document) override {
        std::cout << "Scanning: " << document << std::endl;
    }
    
    void fax(const std::string& document) override {
        std::cout << "Faxing: " << document << std::endl;
    }
};

// Function accepting interface - dependency inversion
void processDrawable(Drawable& drawable) {
    drawable.setColor("Blue");
    drawable.draw();
}

void processResizable(Resizable& resizable) {
    std::cout << "Original area: " << resizable.getArea() << std::endl;
    resizable.resize(1.5);
    std::cout << "After resize area: " << resizable.getArea() << std::endl;
}

void manageDevice(IODevice& device) {
    if (device.open()) {
        std::cout << "Device opened successfully" << std::endl;
        // Use device...
        device.close();
    } else {
        std::cout << "Failed to open device" << std::endl;
    }
}

int main() {
    std::cout << "Interfaces Demo:" << std::endl;
    
    // Multiple interface implementation
    std::cout << "\n--- Multiple Interface Implementation ---" << std::endl;
    
    Rectangle rect(10, 20, 5.0, 3.0, "Red");
    Circle circle(0, 0, 2.0, "Green");
    
    // Use as Drawable
    processDrawable(rect);
    processDrawable(circle);
    
    // Use as Resizable
    processResizable(rect);
    processResizable(circle);
    
    // Use as Serializable (only Rectangle implements this)
    std::cout << "\n--- Serialization ---" << std::endl;
    std::string data = rect.serialize();
    std::cout << "Serialized: " << data << std::endl;
    
    Rectangle newRect(0, 0, 1.0, 1.0, "Black");
    newRect.deserialize(data);
    
    // Polymorphic collections with interfaces
    std::cout << "\n--- Polymorphic Collections ---" << std::endl;
    
    std::vector<std::unique_ptr<Drawable>> drawables;
    drawables.push_back(std::make_unique<Rectangle>(0, 0, 4.0, 2.0, "Purple"));
    drawables.push_back(std::make_unique<Circle>(5, 5, 1.5, "Orange"));
    
    for (auto& drawable : drawables) {
        drawable->draw();
    }
    
    // Interface segregation principle
    std::cout << "\n--- Interface Segregation ---" << std::endl;
    
    SimplePrinter simple;
    MultiFunctionPrinter multiFunc;
    
    // Both can be used as BasicPrinter
    BasicPrinter* printers[] = { &simple, &multiFunc };
    
    for (auto printer : printers) {
        printer->print("Test Document");
    }
    
    // Only MultiFunctionPrinter has advanced features
    AdvancedPrinter* advanced = &multiFunc;
    advanced->printColor("Color Document");
    advanced->scan("Photo");
    
    // Device management through interface
    std::cout << "\n--- Device Management ---" << std::endl;
    
    FileDevice file("data.txt");
    NetworkDevice network("192.168.1.1");
    
    manageDevice(file);
    manageDevice(network);
    
    // Interface casting
    std::cout << "\n--- Interface Casting ---" << std::endl;
    
    Drawable* drawablePtr = &rect;
    
    // Cast to different interfaces
    if (auto* resizable = dynamic_cast<Resizable*>(drawablePtr)) {
        std::cout << "Object is resizable, area: " << resizable->getArea() << std::endl;
    }
    
    if (auto* serializable = dynamic_cast<Serializable*>(drawablePtr)) {
        std::cout << "Object is serializable: " << serializable->serialize() << std::endl;
    }
    
    return 0;
}
