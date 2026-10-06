#include <windows.h>
#include <string>

#define ID_EDIT_X 101
#define ID_EDIT_Y 102
#define ID_EDIT_Z 103
#define ID_BUTTON_CALC 104
#define ID_STATIC_RESULT 105

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE hInst;

int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow) {
    hInst = hInstance;
    const wchar_t szClassName[] = L"Lab3Task1";

    WNDCLASS wc = { 0 };
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(nullptr, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = szClassName;

    if (!RegisterClass(&wc)) return FALSE;

    HWND hwnd = CreateWindowEx(0, szClassName, L"Лабораторна робота 3 - Завдання 1",
        WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 400, 300,
        nullptr, nullptr, hInstance, nullptr);

    if (!hwnd) return FALSE;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg = { 0 };
    while (GetMessage(&msg, nullptr, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) {
    static HWND hEditX, hEditY, hEditZ, hButton, hResult;

    switch (message) {
    case WM_CREATE: {
        // Метки (STATIC)
        CreateWindowW(L"STATIC", L"Введіть x:", WS_CHILD | WS_VISIBLE, 30, 30, 80, 20, hwnd, nullptr, hInst, nullptr);
        CreateWindowW(L"STATIC", L"Введіть y:", WS_CHILD | WS_VISIBLE, 30, 70, 80, 20, hwnd, nullptr, hInst, nullptr);
        CreateWindowW(L"STATIC", L"Введіть z:", WS_CHILD | WS_VISIBLE, 30, 110, 80, 20, hwnd, nullptr, hInst, nullptr);

        // Поля ввода (EDIT)
        hEditX = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 120, 30, 100, 25, hwnd, (HMENU)ID_EDIT_X, hInst, nullptr);
        hEditY = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 120, 70, 100, 25, hwnd, (HMENU)ID_EDIT_Y, hInst, nullptr);
        hEditZ = CreateWindowW(L"EDIT", L"0", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_RIGHT, 120, 110, 100, 25, hwnd, (HMENU)ID_EDIT_Z, hInst, nullptr);

        // Кнопка (BUTTON)
        hButton = CreateWindowW(L"BUTTON", L"Розрахувати", WS_CHILD | WS_VISIBLE | BS_PUSHBUTTON, 120, 150, 100, 30, hwnd, (HMENU)ID_BUTTON_CALC, hInst, nullptr);

        // Поле для результата (STATIC)
        hResult = CreateWindowW(L"STATIC", L"Результат:", WS_CHILD | WS_VISIBLE, 30, 200, 300, 25, hwnd, (HMENU)ID_STATIC_RESULT, hInst, nullptr);
        break;
    }

    case WM_COMMAND: {
        if (LOWORD(wParam) == ID_BUTTON_CALC) {
            wchar_t bufX[50], bufY[50], bufZ[50];
            GetWindowTextW(hEditX, bufX, 50);
            GetWindowTextW(hEditY, bufY, 50);
            GetWindowTextW(hEditZ, bufZ, 50);

            try {
                // Конвертируем текст в числа (double)
                double x = std::stod(bufX);
                double y = std::stod(bufY);
                double z = std::stod(bufZ);

                // Считаем по формуле: f(x,y,z) = x*(z+1) - 2yz
                double result = x * (z + 1.0) - 2.0 * y * z;

                // Выводим результат
                std::wstring resStr = L"Результат: " + std::to_wstring(result);
                SetWindowTextW(hResult, resStr.c_str());
            }
            catch (...) {
                SetWindowTextW(hResult, L"Помилка: введіть коректні числа!");
            }
        }
        break;
    }

    case WM_DESTROY: {
        PostQuitMessage(0);
        break;
    }
    }
    return DefWindowProc(hwnd, message, wParam, lParam);
}