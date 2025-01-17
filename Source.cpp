#include <iostream>
#include <thread>
#include <atomic>
#include <Windows.h>
#include <chrono>

std::atomic<bool> clicking(false);

void clicker() {
    while (clicking) {
        // координаты курсора
        POINT p;
        GetCursorPos(&p);
        int x = p.x;
        int y = p.y;

        // клик мыши
        mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
        
        // 0 = Смерть!!!!!
        std::this_thread::sleep_for(std::chrono::microseconds(2));
    }
}

int main() {
    bool altPressed = false;

    while (true) {
        if (GetAsyncKeyState(VK_LMENU) & 0x8000) {
            if (!altPressed) {
                clicking = !clicking;
                altPressed = true;
                if (clicking) {
                    std::cout << "Clicking started" << std::endl;
                    // поток для выполнения кликов в отдельном потоке
                    std::thread(clicker).detach();
                }
                else {
                    std::cout << "Clicking stopped" << std::endl;
                }
            }
        }
        else {
            altPressed = false;
        }
        // доп задержка для цп
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}
