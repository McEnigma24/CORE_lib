#include "__preprocessor__.h"

// NORMAL //
namespace CORE
{
    void clear_terminal()
    {
#ifdef _WIN32
        int status = std::system("cls"); // Windows
#else
        int status = std::system("clear"); // Linux / macOS
#endif
    }

    u64 convert_2d_to_1d(u64 x, u64 y, u64 WIDTH) { return (y * WIDTH) + x; }

    std::chrono::steady_clock::time_point time_stamp_last_time = std::chrono::steady_clock::now();

    std::string get_current_local_time()
    {
        auto now = std::chrono::system_clock::now();
        std::time_t czas = std::chrono::system_clock::to_time_t(now);
        std::tm* aktualnyCzas = std::localtime(&czas);

        std::ostringstream oss;
        oss << std::put_time(aktualnyCzas, "%H:%M:%S");
        return oss.str();
    }

    std::string calculate_time_difference()
    {
        auto now = std::chrono::steady_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(now - time_stamp_last_time);
        time_stamp_last_time = now; // Aktualizuj czas ostatniego pomiaru

        // Konwersja na jednostki czasu
        long long nanoseconds = duration.count();
        long long hours = nanoseconds / (1000LL * 1000 * 1000 * 60 * 60);
        nanoseconds %= (1000LL * 1000 * 1000 * 60 * 60);
        long long minutes = nanoseconds / (1000LL * 1000 * 1000 * 60);
        nanoseconds %= (1000LL * 1000 * 1000 * 60);
        long long seconds = nanoseconds / (1000LL * 1000 * 1000);
        nanoseconds %= (1000LL * 1000 * 1000);
        long long milliseconds = nanoseconds / (1000LL * 1000);
        nanoseconds %= (1000LL * 1000);
        long long microseconds = nanoseconds / 1000LL;
        nanoseconds %= 1000LL;

        bool show_all_other = false;
        std::ostringstream oss;
        if (hours > 0)
        {
            show_all_other = true;
            oss << hours << "h ";
        }
        if (minutes > 0 || show_all_other)
        {
            show_all_other = true;
            oss << minutes << "m ";
        }
        if (seconds > 0 || show_all_other)
        {
            show_all_other = true;
            oss << seconds << "s ";
        }
        if (milliseconds > 0 || show_all_other)
        {
            show_all_other = true;
            oss << milliseconds << "mili ";
        }
        if (microseconds > 0 || show_all_other)
        {
            show_all_other = true;
            oss << microseconds << "micro ";
        }
        if (nanoseconds > 0 || show_all_other)
        {
            show_all_other = true;
            oss << nanoseconds << "nano ";
        }
        return oss.str();
    }

    namespace str
    {
        std::vector<std::string> split_string(const std::string& input, char delimiter)
        {
            std::vector<std::string> result;
            std::string segment;
            std::istringstream stream(input);

            while (std::getline(stream, segment, delimiter))
            {
                result.push_back(segment);
            }

            return result;
        }
        std::string to_lower_case(const std::string& input)
        {
            std::string result;
            result.reserve(input.size());
            for (char c : input)
            {
                result += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
            }

            return result;
        }
    }; // namespace str

};     // namespace CORE
