#include "mac_p_pic.hpp"

VLC_Entry Macroblock_PPic::table[] =
{
    {0x1, 0xA, 1},
    {0x1, 0x2, 2},
    {0x1, 0x8, 3},
    {0x3, 0x1, 5},
    {0x2, 0x1A, 5},
    {0x1, 0x12, 5},
    {0x1, 0x11, 6}
};

Macroblock_PPic::Macroblock_PPic() :
    VLC_Table(table, SIZE, 6)
{

}
