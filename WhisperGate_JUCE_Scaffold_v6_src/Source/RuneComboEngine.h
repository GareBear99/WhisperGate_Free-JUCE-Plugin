#pragma once
#include "RuneManager.h"
class RuneComboEngine
{
public:
    struct ComboFlags
    {
        bool mouthSmear=false, friction=false, spaceMorph=false, cluster=false,
             sequenceEvolution=false, hauntMode=false, possessedChoir=false;
    };
    ComboFlags evaluate (RuneManager& runes) const;
    float computeComboBonus (const ComboFlags& flags) const;
};
