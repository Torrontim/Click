#include <iostream>
#include <thread>
#include <atomic>
#include <Windows.h>
#include <chrono>

std::atomic<bool> clicking(false);

void clicker() {
    while (clicking) {
        // ���������� �������
        POINT p;
        GetCursorPos(&p);
        int x = p.x;
        int y = p.y;

        // ���� ����
        mouse_event(MOUSEEVENTF_LEFTDOWN, x, y, 0, 0);
        mouse_event(MOUSEEVENTF_LEFTUP, x, y, 0, 0);
        
        // 0 = ������!!!!!
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
                    // ����� ��� ���������� ������ � ��������� ������
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
        // ��� �������� ��� ��
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    return 0;
}
