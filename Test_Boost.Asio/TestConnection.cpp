#include <boost/asio.hpp>
#include <iostream>
#include <chrono>

int main() {
    try {
        auto start = std::chrono::high_resolution_clock::now(); // �ð� ���� ����

        boost::asio::io_context io_context;

        boost::asio::ip::tcp::resolver resolver(io_context);
        boost::asio::ip::tcp::resolver::results_type endpoints = resolver.resolve("www.naver.com", "80");

        boost::asio::ip::tcp::socket socket(io_context);
        boost::asio::connect(socket, endpoints);

        auto end = std::chrono::high_resolution_clock::now(); // �ð� ���� ����
        std::chrono::duration<double> elapsed = end - start; // ��� �ð� ���

        std::cout << "www.naver.com �������� �����մϴ�.\n";
        std::cout << "��� �ð�: " << elapsed.count() << " ��\n"; // ��� �ð� ���

    }
    catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}