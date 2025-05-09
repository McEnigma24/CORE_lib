#include "__preprocessor__.h"

class test
{
    int tab[100];
};

#ifdef BUILD_EXECUTABLE
int main(int argc, char* argv[])
{
    srand(time(NULL));
    // CORE::clear_terminal();
    time_stamp("It just works");

    CORE::str::split_string("Hello, World!", ' ');
    var(CORE::str::to_lower_case("Hello, World!"));

    show_sizeof(test);
    show_sizeof_many(test, 100);

    int num = 123456789;
    double num2 = 1234567.89123;

    var(CORE::format_number(num));
    var(CORE::format_number(num2));

    var(CORE::format_number(NUM(1, 000)));
    var(CORE::format_number(NUM(1, 000, 000)));
    var(CORE::format_number(NUM(1, 000, 000, 000)));
    var(CORE::format_number(NUM(1, 000, 000, 000, 000)));
    var(CORE::format_number(NUM(1, 000, 000, 000, 000, 000)));

    return 0;
}
#endif