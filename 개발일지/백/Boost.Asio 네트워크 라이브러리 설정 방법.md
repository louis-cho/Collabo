# Boost.Asio 설정 매뉴얼

Boost.Asio를 사용하여 네트워크 프로그램을 개발하기 위해서는 Boost 라이브러리를 설정해야 합니다.
Windows 환경에서 Boost.Asio를 설정하는 방법을 단계별로 진행하겠습니다.

## 1. Boost 라이브러리 다운로드

Boost 공식 웹사이트에서 Boost 1.85.0 버전의 zip 파일을 다운로드합니다.
[Boost 다운로드 페이지](https://www.boost.org/users/download/)

## 2. Boost.Build 도구 설치

Boost 라이브러리를 빌드하기 위해 Boost.Build 도구를 설치합니다.

1. `boost_1_85_0` 폴더로 이동합니다.
2. `cmd` 창을 열고 다음 명령어를 실행합니다:

   ```cmd
   bootstrap.bat
   ```

## 3. Boost 라이브러리 빌드

Boost 라이브러리를 빌드합니다.

1. `cmd` 창에서 다음 명령어를 실행합니다:

   ```cmd
   b2
   ```

2. 빌드가 완료되면 다음 메시지가 출력됩니다:

   ```txt
   ...updated 3214 targets...

   The Boost C++ Libraries were successfully built!

   The following directory should be added to compiler include paths:
       [path_to_your_directory]\boost_1_85_0

   The following directory should be added to linker library paths:
       [path_to_your_directory]\boost_1_85_0\stage\lib
   ```

## 4. Visual Studio에서 Boost.Asio 설정

### i. C++ 프로젝트 생성

Visual Studio에서 새로운 C++ 프로젝트를 생성합니다.

### ii. 포함 디렉터리 추가

[프로젝트 속성] > [VC++ 디렉터리] 에서 다음 경로를 포함 디렉터리에 추가합니다:

- `[path_to_your_directory]\boost_1_85_0`

### iii. 라이브러리 디렉터리 추가

[프로젝트 속성] > [VC++ 디렉터리] 에서 다음 경로를 라이브러리 디렉터리에 추가합니다:

- `[path_to_your_directory]\boost_1_85_0\stage\lib`

### iv. 추가 포함 디렉터리 설정

`C/C++ > 일반(General)` 섹션에서 '추가 포함 디렉터리(Additional Include Directories)'에 다음 경로를 추가합니다:

- `[path_to_your_directory]\boost_1_85_0`
- (이 항목이 보이지 않는 경우, `main.cpp` 파일을 만들면 항목이 생깁니다)

### v. 추가 종속성 설정

`링커(Linker) > 입력(Input)` 섹션에서 '추가 종속성(Additional Dependencies)'에 필요한 Boost 라이브러리를 추가합니다:

- `..\boost_1_85_0\stage\lib\libboost_system-vc143-mt-x64-1_85.lib`

## 5. 예제 파일 작성

다음은 Boost.Asio를 사용한 예제 코드입니다. `main.cpp` 파일에 다음 코드를 추가합니다:

```cpp
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

    } catch (std::exception& e) {
        std::cerr << "Exception: " << e.what() << std::endl;
    }

    return 0;
}
```
