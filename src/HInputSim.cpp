#include <windows.h>
#include <vector>
#include <cmath>
#include <thread>
#include <string>
#include <iostream>

#ifndef HInputSim_IMPLEMENTATION
#define HInputSim_IMPLEMENTATION

namespace HInputSim
{
    enum MOUSE_BUTTON : u_long
    {
        LEFT,
        RIGHT,
        MIDDLE
    };
    enum KEYCODES : u_short
    {
        LEFT_MOUSE = 0X01,
        RIGHT_MOUSE = 0X02,
        CONTROL_BREAK_PROCESSING = 0X03,
        MIDDLE_MOUSE = 0X04,
        X1_MOUSE = 0X05,
        X2_MOUSE = 0X06,
        BACKSPACE = 0X08,
        TAB = 0X09,
        CLEAR = 0X0C,
        ENTER = 0X0D,
        SHIFT = 0X10,
        CTRL = 0X11,
        ALT = 0X12,
        PAUSE = 0X13,
        CAPS_LOCK = 0X14,
        IME_KANA_MODE = 0X15,
        IME_HANGUL_MODE = 0X15,
        IME_ON = 0X16,
        IME_JUNJA_MODE = 0X17,
        IME_FINAL_MODE = 0X18,
        IME_HANJA_MODE = 0X19,
        IME_KANJI_MODE = 0X19,
        IME_OFF = 0X1A,
        ESC_KEY = 0X1B,
        IME_CONVERT = 0X1C,
        IME_NONCONVERT = 0X1D,
        IME_ACCEPT = 0X1E,
        IME_MODE_CHANGE_REQUEST = 0X1F,
        SPACEBAR = 0X20,
        PAGE_UP = 0X21,
        PAGE_DOWN = 0X22,
        END = 0X23,
        HOME = 0X24,
        LEFT_ARROW = 0X25,
        UP_ARROW = 0X26,
        RIGHT_ARROW = 0X27,
        DOWN_ARROW = 0X28,
        SELECT = 0X29,
        PRINT = 0X2A,
        EXECUTE = 0X2B,
        PRINT_SCREEN = 0X2C,
        INS = 0X2D,
        DEL = 0X2E,
        HELP = 0X2F,
        NUM_0 = 0X30,
        NUM_1 = 0X31,
        NUM_2 = 0X32,
        NUM_3 = 0X33,
        NUM_4 = 0X34,
        NUM_5 = 0X35,
        NUM_6 = 0X36,
        NUM_7 = 0X37,
        NUM_8 = 0X38,
        NUM_9 = 0X39,
        A = 0X41,
        B = 0X42,
        C = 0X43,
        D = 0X44,
        E = 0X45,
        F = 0X46,
        G = 0X47,
        H = 0X48,
        I = 0X49,
        J = 0X4A,
        K = 0X4B,
        L = 0X4C,
        M = 0X4D,
        N = 0X4E,
        O = 0X4F,
        P = 0X50,
        Q = 0X51,
        R = 0X52,
        S = 0X53,
        T = 0X54,
        U = 0X55,
        V = 0X56,
        W = 0X57,
        X = 0X58,
        Y = 0X59,
        Z = 0X5A,
        LEFT_WINDOWNS = 0X5B,
        RIGHT_WINDOWNS = 0X5C,
        APPLICATIONS_KEY = 0X5D,
        COMPUTER_SLEEP_KEY = 0X5F,
        NUMPAD_0 = 0X60,
        NUMPAD_1 = 0X61,
        NUMPAD_2 = 0X62,
        NUMPAD_3 = 0X63,
        NUMPAD_4 = 0X64,
        NUMPAD_5 = 0X65,
        NUMPAD_6 = 0X66,
        NUMPAD_7 = 0X67,
        NUMPAD_8 = 0X68,
        NUMPAD_9 = 0X69,
        NUMPAD_MULTIPLY = 0X6A,
        NUMPAD_ADD = 0X6B,
        NUMPAD_SEPARATOR = 0X6C,
        NUMPAD_SUBTRACT = 0X6D,
        NUMPAD_DECIMAL = 0X6E,
        NUMPAD_DIVIDE = 0X6F,
        F1 = 0X70,
        F2 = 0X71,
        F3 = 0X72,
        F4 = 0X73,
        F5 = 0X74,
        F6 = 0X75,
        F7 = 0X76,
        F8 = 0X77,
        F9 = 0X78,
        F10 = 0X79,
        F11 = 0X7A,
        F12 = 0X7B,
        F13 = 0X7C,
        F14 = 0X7D,
        F15 = 0X7E,
        F16 = 0X7F,
        F17 = 0X80,
        F18 = 0X81,
        F19 = 0X82,
        F20 = 0X83,
        F21 = 0X84,
        F22 = 0X85,
        F23 = 0X86,
        F24 = 0X87,
        NUM_LOCK = 0X90,
        SCROLL_LOCK = 0X91,
        LEFT_SHIFT = 0XA0,
        RIGHT_SHIFT = 0XA1,
        LEFT_CONTROL = 0XA2,
        RIGHT_CONTROL = 0XA3,
        LEFT_ALT = 0XA4,
        RIGHT_ALT = 0XA5,
        BROWSER_BACK = 0XA6,
        BROWSER_FORWARD = 0XA7,
        BROWSER_REFRESH = 0XA8,
        BROWSER_STOP = 0XA9,
        BROWSER_SEARCH = 0XAA,
        BROWSER_FAVORITES = 0XAB,
        BROWSER_START_AND_HOME = 0XAC,
        VOLUME_MUTE = 0XAD,
        VOLUME_DOWN = 0XAE,
        VOLUME_UP = 0XAF,
        NEXT_TRACK = 0XB0,
        PREVIOUS_TRACK = 0XB1,
        STOP_MEDIA = 0XB2,
        PLAY_PAUSE_MEDIA = 0XB3,
        START_MAIL = 0XB4,
        SELECT_MEDIA = 0XB5,
        START_APPLICATION_1_KEY = 0XB6,
        START_APPLICATION_2_KEY = 0XB7,
        MISC_US_SEMICOLON_OR_COLON = 0XBA,
        ANY_COUNTRY_PLUS = 0XBB,
        ANY_COUNTRY_COMMA = 0XBC,
        ANY_COUNTRY_MINUS = 0XBD,
        ANY_COUNTRY_PERIOD = 0XBE,
        MISC_US_SLASH_OR_QUESTIONMARK = 0XBF,
        MISC_US_GRAVE_ACCENT_OR_TILDE = 0XC0,
        MISC_US_LEFT_SQUARE_BRACKET_OR_LEFT_CURLY_BRACKET = 0XDB,
        MISC_US_BACKSLASH_OR_VERTICAL_BAR = 0XDC,
        MISC_US_RIGHT_SQUARE_BRACKET_OR_RIGHT_CURLY_BRACKET = 0XDD,
        MISC_US_APOSTROPHE_OR_QUOTATION_MARK = 0XDE,
        MISC = 0XDF,
        OEM_SPECIFIC_1 = 0XE1,
        MISC_US_LESS_THAN_SIGN_OR_GREATER_THAN_SIGN = 0XE2,
        IME_PROCESS = 0XE5,
        OEM_SPECIFIC_2 = 0XE6,
        PACKET = 0XE7,
        ATTN = 0XF6,
        CRSEL = 0XF7,
        EXSEL = 0XF8,
        ERASE_EOF = 0XF9,
        PLAY = 0XFA,
        ZOOM = 0XFB,
        PA1 = 0XFD,
        ANY_COUNTRY_CLEAR = 0XFE

    };

    void SleepFor(int64_t milliseconds)
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(milliseconds));
    }

    void GetScreenSize(int &w, int &h)
    {
        w = GetSystemMetrics(SM_CXSCREEN);
        h = GetSystemMetrics(SM_CYSCREEN);
    }
    void GetMousePosition(int &x, int &y)
    {
        POINT p;
        if (GetCursorPos(&p))
        {
            x = p.x;
            y = p.y;
        }
        else
        {
            x = 0;
            y = 0;
        }
    }
    void SetMousePosition(int x, int y)
    {
        SetCursorPos(x, y);
    }

    void MouseDown(MOUSE_BUTTON button)
    {

        INPUT in = {0};
        // ZeroMemory(&in, sizeof(INPUT));
        in.type = INPUT_MOUSE;
        switch (button)
        {
        case LEFT:
            in.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            break;
        case RIGHT:
            in.mi.dwFlags = MOUSEEVENTF_RIGHTDOWN;
            break;
        case MIDDLE:
            in.mi.dwFlags = MOUSEEVENTF_MIDDLEDOWN;
            break;
        default:
            in.mi.dwFlags = MOUSEEVENTF_LEFTDOWN;
            break;
        }
        SendInput(1, &in, sizeof(INPUT));
        ZeroMemory(&in, sizeof(INPUT));
    }
    void MouseUp(MOUSE_BUTTON button)
    {
        INPUT in = {0};
        // ZeroMemory(&in, sizeof(INPUT));
        in.type = INPUT_MOUSE;
        switch (button)
        {
        case LEFT:
            in.mi.dwFlags = MOUSEEVENTF_LEFTUP;
            break;
        case RIGHT:
            in.mi.dwFlags = MOUSEEVENTF_RIGHTUP;
            break;
        case MIDDLE:
            in.mi.dwFlags = MOUSEEVENTF_MIDDLEUP;
            break;
        default:
            in.mi.dwFlags = MOUSEEVENTF_LEFTUP;
            break;
        }
        SendInput(1, &in, sizeof(INPUT));
        ZeroMemory(&in, sizeof(INPUT));
    }
    void MouseClick(MOUSE_BUTTON button)
    {
        MouseDown(button);
        SleepFor(156); // 6.4 cps
        MouseUp(button);
    }

    void MouseScrollX(int length)
    {
        int scrollDirection = 1 * 50; // 1 left -1 right

        if (length < 0)
        {
            length *= -1;
            scrollDirection *= -1;
        }

        for (int cnt = 0; cnt < length; cnt++)
        {
            INPUT in;
            in.type = INPUT_MOUSE;
            in.mi.dx = 0;
            in.mi.dy = 0;
            in.mi.dwFlags = MOUSEEVENTF_HWHEEL;
            in.mi.time = 0;
            in.mi.dwExtraInfo = 0;
            in.mi.mouseData = scrollDirection; // WHEEL_DELTA;
            SendInput(1, &in, sizeof(in));
        }
    }
    void MouseScrollY(int length)
    {
        int scrollDirection = -1 * 50; // 1 up -1 down

        if (length < 0)
        {
            length *= -1;
            scrollDirection *= -1;
        }

        for (int cnt = 0; cnt < length; cnt++)
        {
            INPUT in;
            in.type = INPUT_MOUSE;
            in.mi.dx = 0;
            in.mi.dy = 0;
            in.mi.dwFlags = MOUSEEVENTF_WHEEL;
            in.mi.time = 0;
            in.mi.dwExtraInfo = 0;
            in.mi.mouseData = scrollDirection; // WHEEL_DELTA;
            SendInput(1, &in, sizeof(in));
        }
    }

    void KeyDown(KEYCODES key)
    {
        INPUT in = {0};
        // ZeroMemory(&in, sizeof(INPUT));
        in.type = INPUT_KEYBOARD;
        in.ki.wVk = key;
        SendInput(1, &in, sizeof(INPUT));
        ZeroMemory(&in, sizeof(INPUT));
    }
    void KeyUp(KEYCODES key)
    {
        INPUT in = {0};
        // ZeroMemory(&in, sizeof(INPUT));
        in.type = INPUT_KEYBOARD;
        in.ki.wVk = key;
        in.ki.dwFlags = KEYEVENTF_KEYUP;
        SendInput(1, &in, sizeof(INPUT));
        ZeroMemory(&in, sizeof(INPUT));
    }
    void KeyClick(KEYCODES key)
    {
        KeyDown(key);
        SleepFor(74); // 6.4 cps
        KeyUp(key);
    }

    /**
     * @param speed [px/s]
     */
    void InterpolateMouseBetween(int a_x, int a_y, int b_x, int b_y, double speed)
    {
        double distance = std::sqrt((b_x - a_x) * (b_x - a_x) + (b_y - a_y) * (b_y - a_y));

        int steps = static_cast<int>(distance / speed);
        if (steps == 0)
            steps = 1;

        std::cout << distance << std::endl;
        std::cout << speed << std::endl;
        std::cout << steps << std::endl;

        double stepX = (b_x - a_x) / static_cast<double>(steps);
        double stepY = (b_y - a_y) / static_cast<double>(steps);

        for (int i = 0; i <= steps; ++i)
        {
            int currentX = static_cast<int>(a_x + stepX * i);
            int currentY = static_cast<int>(a_y + stepY * i);

            SetCursorPos(currentX, currentY);

            SleepFor(10);
        }
    }
    void InterpolateMouseTo(int x, int y, double speed)
    {
        int s_x, s_y;
        GetMousePosition(s_x, s_y);
        InterpolateMouseBetween(s_x, s_y, x, y, speed);
    }
} // namespace HInputSim

#endif