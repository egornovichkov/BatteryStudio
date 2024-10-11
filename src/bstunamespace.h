#ifndef BSTUNAMESPACE_H
#define BSTUNAMESPACE_H

namespace BSTU
{
    /// Enumeration for cell parameters names.
    enum CellParams
    {
        // Params must be equal to int numbers from 0 to parameters count in order
        Number = 0,
        Voltage = 1,
        Minimum = 2,
        Maximum = 3,
        Color = 4,
        CELLPARAMSCOUNT // Do not insert any params after this
    };
}

#endif // BSTUNAMESPACE_H
