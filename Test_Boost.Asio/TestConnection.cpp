#include <boost/asio.hpp>
#include <iostream>
#include <chrono>

int main() {
    try {
        auto start = std::chrono::high_resolution_clock::now(); // 시간 측정 시작

        boost::asio::io_context io_context;

        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve("www.naver.com", "80");

        boost::asio::ip::tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        auto end = std::chrono::high_resolution_clock::now(); // 시간 측정 종료
        std::chrono::duration<double> elapsed = end - start; // 경과 시간 계산

        std::cout << "www.naver.com 페이지에 연결합니다.\n";
        std::cout << "경과 시간: " << elapsed.count() << " 초\n"; // 경과 시간 출력

    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}