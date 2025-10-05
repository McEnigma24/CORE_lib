#pragma once
#include <chrono>
#include <cmath>
#include <cstdint>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <thread>
#include <time.h>
#include <vector>

using namespace std;

#define path_run_time_config "../run_time_config"

#define __FILENAME__ ((__FILE__) + SOURCE_PATH_SIZE)

#define var(x)   cout << __FILENAME__ << ":" << __LINE__ << " - " << #x << " = " << x << "\n";
#define varr(x)  cout << __FILENAME__ << ":" << __LINE__ << " - " << #x << " = " << x << " ";
#define line(x)  cout << __FILENAME__ << ":" << __LINE__ << " - " << x << "\n";
#define linee(x) cout << __FILENAME__ << ":" << __LINE__ << " - " << x << " ";
#define nline    cout << "\n";

// #define var(x)   cout << #x << " = " << x << '\n';
// #define varr(x)  cout << #x << " = " << x << ' ';
// #define line(x)  cout << x << '\n';
// #define linee(x) cout << x << ' ';
// #define nline    cout << '\n';

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

#define null      nullptr
#define pow2(x)   ((x) * (x))
#define pow3(x)   ((x) * (x) * (x))
#define base_0(x) (x - 1)

#define c_init(x)                   x(_##x)
#define cc_init(x)                  this->x = x;
#define member_assign(a, b, member) a.member = b.member;
#define THIS_OTHER(x)               this->x = other.x;

#define sizeof_imp(x)                                                                                                                                \
    {                                                                                                                                                \
        cout << ": " << std::setprecision(1) << fixed << (x) / 1000000000 << "gb " << (x) / 1000000 << "mb " << (x) / 1000 << "kb "                  \
             << std::setprecision(0) << (x) << "b \n";                                                                                               \
    }
#define show_sizeof(class)                                                                                                                           \
    {                                                                                                                                                \
        size_t size = sizeof(class);                                                                                                                 \
        cout << #class;                                                                                                                              \
        sizeof_imp((float)size);                                                                                                                     \
    }
#define show_sizeof_many(class, count)                                                                                                               \
    {                                                                                                                                                \
        size_t size = sizeof(class) * count;                                                                                                         \
        cout << #class;                                                                                                                              \
        sizeof_imp((float)size);                                                                                                                     \
    }

#define call_print(x) x.print(#x);

#define add_endl(string, how_many)                                                                                                                   \
    for (u16 i{}; i < how_many; i++)                                                                                                                 \
        string += "\n";

#define OUTPUT_TO_FILE(path, content)                                                                                                                \
    {                                                                                                                                                \
        ofstream file(path);                                                                                                                         \
        file << content;                                                                                                                             \
        file.close();                                                                                                                                \
    }

#define FATAL_ERROR(x)                                                                                                                               \
    {                                                                                                                                                \
        const string fatal = "FATAL ERROR - " + std::to_string(__LINE__) + " : " + __FILE__ + " -> " + x + "\n";                                     \
        cout << fatal;                                                                                                                               \
        exit(EXIT_FAILURE);                                                                                                                          \
    }
#define ASSERT_ER_IF_TRUE(x)                                                                                                                         \
    if (x) FATAL_ERROR(#x)
#define ASSERT_ER_IF_NULL(x)                                                                                                                         \
    if (x == null) FATAL_ERROR(#x)

#define check_nan(x)                                                                                                                                 \
    if (std::isnan(x)) { FATAL_ERROR("found it"); }

#define SAFETY_CHECK(x) x;
// #define SAFETY_CHECK(x)

#define delay_input std::this_thread::sleep_for(std::chrono::milliseconds(50));
#define sleep(x)    std::this_thread::sleep_for(std::chrono::milliseconds(x));

#define time_stamp(x)                                                                                                                                \
    std::cout << "\nTIME_STAMP: " << setw(50) << left << x << right << " " << CORE::get_current_local_time() << " (+ "                               \
              << CORE::calculate_time_difference() << ")\n";

#define time_stamp_reset() CORE::calculate_time_difference();

// #define time_stamp(x)
// #define time_stamp_reset(x)

// CRAZY PREPROCESSOR MAGIC //
#define GET_MACRO(_1, _2, _3, _4, _5, _6, NAME, ...) NAME

#define NUM_2(x1, x2)                 x1##x2
#define NUM_3(x1, x2, x3)             x1##x2##x3
#define NUM_4(x1, x2, x3, x4)         x1##x2##x3##x4
#define NUM_5(x1, x2, x3, x4, x5)     x1##x2##x3##x4##x5
#define NUM_6(x1, x2, x3, x4, x5, x6) x1##x2##x3##x4##x5##x6

#define NUM(...) GET_MACRO(__VA_ARGS__, NUM_6, NUM_5, NUM_4, NUM_3, NUM_2)(__VA_ARGS__)

namespace CORE
{
    std::string get_current_local_time();
    std::string calculate_time_difference();

    void clear_terminal();
    u64 convert_2d_to_1d(u64 x, u64 y, u64 WIDTH);

    template <typename T>
    std::string format_number(T number)
    {
        std::string str = std::to_string(number);

        // Sprawdzenie, czy liczba jest zmiennoprzecinkowa
        size_t dot_pos = str.find('.');
        if (dot_pos != std::string::npos)
        {
            // Oddziel część przed kropką
            std::string integer_part = str.substr(0, dot_pos);
            std::string fractional_part = str.substr(dot_pos + 1);

            // Formatowanie części całkowitej
            std::string formatted_integer;
            int count = 0;
            for (int i = integer_part.length() - 1; i >= 0; --i)
            {
                formatted_integer.insert(formatted_integer.begin(), integer_part[i]);
                count++;
                if (count == 3 && i != 0)
                {
                    formatted_integer.insert(formatted_integer.begin(), '`');
                    count = 0;
                }
            }

            // Złożenie wyniku
            return formatted_integer + "." + fractional_part;
        }
        else
        {
            // Jeśli liczba jest całkowita
            std::string integer_part = str;

            // Formatowanie części całkowitej
            std::string formatted_integer;
            int count = 0;
            for (int i = integer_part.length() - 1; i >= 0; --i)
            {
                formatted_integer.insert(formatted_integer.begin(), integer_part[i]);
                count++;
                if (count == 3 && i != 0)
                {
                    formatted_integer.insert(formatted_integer.begin(), '`');
                    count = 0;
                }
            }

            return formatted_integer;
        }
    }

    std::string humanReadableBytes(uint64_t bytes);

    namespace str
    {
        std::vector<std::string> split_string(const std::string& input, char delimiter);
        std::string to_lower_case(const std::string& input);
    }; // namespace str

    namespace vec
    {
        template <typename T>
        static void print_on_by_one(const std::vector<T>& vec)
        {
            for (auto& v : vec)
            {
                cout << v << "\n";
            }
        }

        template <typename T>
        static bool contains(const T& value, const std::vector<T>& vec)
        {
            return std::find(vec.begin(), vec.end(), value) != vec.end();
        }

        template <typename T>
        static void remove_by_value(const T& value, std::vector<T>& vec)
        {
            auto it = std::find(vec.begin(), vec.end(), value);

            if (it != vec.end()) { vec.erase(it); }
        }
    }; // namespace vec
};     // namespace CORE