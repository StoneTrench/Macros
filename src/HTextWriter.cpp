#include <map>
#include "HInputSim.cpp"

#ifndef HTextWriter_IMPLEMENTATION
#define HTextWriter_IMPLEMENTATION

using namespace HInputSim;

namespace HTextWriter
{
    KEYCODES *GetCodes(char c, uint8_t &count)
    {
        static std::map<char, KEYCODES> keyMap = {
            {'A', KEYCODES::A},
            {'B', KEYCODES::B},
            {'C', KEYCODES::C},
            {'D', KEYCODES::D},
            {'E', KEYCODES::E},
            {'F', KEYCODES::F},
            {'G', KEYCODES::G},
            {'H', KEYCODES::H},
            {'I', KEYCODES::I},
            {'J', KEYCODES::J},
            {'K', KEYCODES::K},
            {'L', KEYCODES::L},
            {'M', KEYCODES::M},
            {'N', KEYCODES::N},
            {'O', KEYCODES::O},
            {'P', KEYCODES::P},
            {'Q', KEYCODES::Q},
            {'R', KEYCODES::R},
            {'S', KEYCODES::S},
            {'T', KEYCODES::T},
            {'U', KEYCODES::U},
            {'V', KEYCODES::V},
            {'W', KEYCODES::W},
            {'X', KEYCODES::X},
            {'Y', KEYCODES::Y},
            {'Z', KEYCODES::Z},
            {'0', KEYCODES::NUM_0},
            {'1', KEYCODES::NUM_1},
            {'2', KEYCODES::NUM_2},
            {'3', KEYCODES::NUM_3},
            {'4', KEYCODES::NUM_4},
            {'5', KEYCODES::NUM_5},
            {'6', KEYCODES::NUM_6},
            {'7', KEYCODES::NUM_7},
            {'8', KEYCODES::NUM_8},
            {'9', KEYCODES::NUM_9}};

        if (isalpha(c))
        {
            if (isupper(c))
            {
                // Uppercase letters require Shift
                count = 2;
                return new KEYCODES[2]{KEYCODES::LEFT_SHIFT, keyMap[c]};
            }
            else
            {
                // Lowercase letters
                count = 1;
                return new KEYCODES[1]{keyMap[toupper(c)]};
            }
        }
        else if (isdigit(c))
        {
            // Numbers
            count = 1;
            return new KEYCODES[1]{keyMap[c]};
        }
        else
        {
            // Add support for other characters (punctuation, etc.) as needed
            switch (c)
            {
            case ' ':
                count = 1;
                return new KEYCODES[1]{KEYCODES::SPACEBAR};
            case '.':
                count = 1;
                return new KEYCODES[1]{KEYCODES::ANY_COUNTRY_PERIOD};
            case ',':
                count = 1;
                return new KEYCODES[1]{KEYCODES::ANY_COUNTRY_COMMA};
            case '!':
                count = 2;
                return new KEYCODES[2]{KEYCODES::LEFT_SHIFT, KEYCODES::NUM_1};
            case ':':
                count = 2;
                return new KEYCODES[2]{KEYCODES::LEFT_SHIFT, KEYCODES::MISC_US_SEMICOLON_OR_COLON};
            case '/':
                count = 1;
                return new KEYCODES[1]{KEYCODES::MISC_US_SLASH_OR_QUESTIONMARK};
            case '?':
                count = 2;
                return new KEYCODES[2]{KEYCODES::LEFT_SHIFT, KEYCODES::MISC_US_SLASH_OR_QUESTIONMARK};
            // Add additional cases as needed
            default:
                break;
            }
        }

        count = 0;
        return new KEYCODES[0]{};
    }

    void WriteText(std::string text)
    {
        uint8_t count = 0;
        for (char c : text)
        {
            KEYCODES *codes = GetCodes(c, count);

            if (codes == nullptr || count == 0)
            {
                delete[] codes;
                continue;
            }
            for (int8_t i = 0; i < count; ++i)
            {
                HInputSim::KeyDown(codes[i]);
                HInputSim::SleepFor(75);
            }
            for (int8_t i = count - 1; i >= 0; --i)
            {
                HInputSim::KeyUp(codes[i]);
            }
            delete[] codes;
        }
    }
} // namespace HTextWriter

#endif