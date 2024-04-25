#include <iostream>
#include <string>
#include <optional>
#include <iomanip>
#include "business.h"

void run(const std::string &code, const int candle, const std::string &day)
{
    std::string url = R"(https://web.ifzq.gtimg.cn/appstock/app/fqkline/get?_var=kline_dayqfq&param=)" + code + R"(,day,,,)" + day + R"(,qfq)";
    //std::cout << url << std::endl;
    auto response = dataRequest(url);

    if (response.empty())
    {
        std::cout << "ERROR REQUEST!!!" << std::endl;
        return;
    }

    try
    {
        std::vector<DateData> list = dataRespond(response);

        if (list.empty())
        {
            std::cout << "HAS EMPTY QUEUE!!!" << std::endl;
            return;
        }

        getMarkData(list, candle);
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

int main(int argc, char *argv[])
{
    // for (int i = 0;i < argc;i ++)
    //     std::cout << argv[i] << std::endl;
    SetConsoleOutputCP(CP_UTF8);

    std::string day = "80";
    MarkDataPO::beginHour = 9;
    MarkDataPO::beginMin = 30;

    if (argc >= 2)
    {
        MarkDataPO::beginHour = std::stoi(argv[1]);
    }

    if (argc >= 3)
    {
        MarkDataPO::beginMin = std::stoi(argv[2]);
    }

    if (argc >= 4)
    {
        day = argv[3];
    }

    while (1)
    {
        std::string i_code;
        std::string i_candle;

        std::cout << "Code :";
        std::getline(std::cin, i_code);

        i_code.erase(std::remove_if(i_code.begin(), i_code.end(), ::isspace), i_code.end());

        if (i_code.empty())
        {
            continue;
        }

        auto code = setPreCode(i_code);

        std::cout << "R0-4 G0-4 F0-4:";
        std::getline(std::cin, i_candle);

        int candle = -1;
        try
        {
            candle = std::stoi(i_candle);
        }
        catch (const std::invalid_argument &e)
        {
        }

        run(code, candle, day);
    }

    return 0;
}
