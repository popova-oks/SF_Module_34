#include <iostream>
#include <concepts>
#include <string>
#include <variant>

template <typename T>
concept ComplexConcept = requires(T t) {
    { t.hash() } -> std::convertible_to<long>;
    { t.toString() } -> std::same_as<std::string>;
}  && !std::has_virtual_destructor_v<T>;

class Converter {
  public:
    Converter() : _num{} {};
    void set_num(double num) { _num = num; }
   
    long hash() { return long(_num); }
    std::string toString() const { return std::to_string(_num); }

  private:
    double _num;
};

using value = std::variant<long, std::string, std::monostate>;

value to_convert(ComplexConcept auto& c, int mode) {
    if(mode == 1) {
        return c.hash();
    } else if(mode == 2) {
        return c.toString();
    } else {
        return std::monostate();
    }
}

// функция печати результата
void printResult(const value &v) {
    if (std::holds_alternative<long>(v)) {
        std::cout << "Long value: " << std::get<long>(v) << std::endl;
    } else if (std::holds_alternative<std::string>(v)) {
        std::cout << "String: " << std::get<std::string>(v) << std::endl;
    } else {
        std::cout << "No real roots found.\n";
    }
}

int main() {
    std::cout << "Enter long number: ";
    double num;
    std::cin >> num;

    Converter c;
    c.set_num(num);

    std::cout << "Enter mode: 1 (convert to long) or 2 (convert to string) : ";
    int mode;
    std::cin >> mode;

    value v = to_convert(c, mode);
    printResult(v);    
   
    return 0;
}