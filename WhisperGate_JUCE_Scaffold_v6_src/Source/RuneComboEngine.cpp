#include "RuneComboEngine.h"
RuneComboEngine::ComboFlags RuneComboEngine::evaluate (RuneManager& runes) const
{
    runes.clearComboFlags();
    ComboFlags flags;
    const bool whisper=runes.isActive(RuneId::whisper), breath=runes.isActive(RuneId::breath),
               drift=runes.isActive(RuneId::drift), echo=runes.isActive(RuneId::echo),
               temple=runes.isActive(RuneId::temple), choir=runes.isActive(RuneId::choir),
               seed=runes.isActive(RuneId::seed), autoMode=runes.isActive(RuneId::autoMode),
               presence=runes.isActive(RuneId::presence);
    flags.mouthSmear = whisper && drift;
    flags.friction = breath && presence;
    flags.spaceMorph = echo && temple;
    flags.cluster = choir;
    flags.sequenceEvolution = seed && autoMode;
    flags.hauntMode = whisper && temple && echo;
    flags.possessedChoir = drift && choir && presence;
    if (flags.mouthSmear){ runes.getState(RuneId::whisper).comboLinked=true; runes.getState(RuneId::drift).comboLinked=true; }
    if (flags.friction){ runes.getState(RuneId::breath).comboLinked=true; runes.getState(RuneId::presence).comboLinked=true; }
    if (flags.spaceMorph){ runes.getState(RuneId::echo).comboLinked=true; runes.getState(RuneId::temple).comboLinked=true; }
    if (flags.cluster){ runes.getState(RuneId::choir).comboLinked=true; }
    if (flags.sequenceEvolution){ runes.getState(RuneId::seed).comboLinked=true; runes.getState(RuneId::autoMode).comboLinked=true; }
    return flags;
}
float RuneComboEngine::computeComboBonus (const ComboFlags& f) const
{
    return (f.mouthSmear?0.08f:0.0f)+(f.friction?0.06f:0.0f)+(f.spaceMorph?0.10f:0.0f)+
           (f.cluster?0.10f:0.0f)+(f.sequenceEvolution?0.05f:0.0f)+(f.hauntMode?0.15f:0.0f)+
           (f.possessedChoir?0.14f:0.0f);
}
