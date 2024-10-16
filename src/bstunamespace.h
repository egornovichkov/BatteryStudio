#ifndef BSTUNAMESPACE_H
#define BSTUNAMESPACE_H

#include "qnamespace.h"
namespace BSTU
{

    /// Enumeration for cells model type.
    enum CellsModel
    {
        VoltageType = 0,
        TemperatureType = 1
    };

    /// Enumeration for cell parameters names.
    enum CellParams
    {
        // Params must be equal to int numbers from 0 to parameters count in order
        Number = 0,
        Voltage = 1,
        Temperature = 2,
        CELLPARAMSCOUNT // Do not insert any params after this
    };

    /// Enumeration for roles used by models.
    enum CellRoles
    {
        NumRole = Qt::UserRole,
        VoltRole,
        TempRole,
        MinVoltRole,
        MaxVoltRole,
        MinTempRole,
        MaxTempRole,
        VoltRangeRole,
        TempRangeRole,
        ModelTypeRole
    };

    enum CellsTableRoles
    {
        RelativeBarHeightRole = 2 * Qt::UserRole
    };
}

#endif // BSTUNAMESPACE_H
