#include "SequenceEngine.h"
void SequenceEngine::addStep (const Step& s){ steps.push_back(s); if(playIndex<0) playIndex=0; }
void SequenceEngine::removeStep (int i){ if(i>=0 && i<(int)steps.size()) steps.erase(steps.begin()+i); if(steps.empty()) playIndex=-1; }
void SequenceEngine::clear(){ steps.clear(); playIndex=-1; playing=false; }
void SequenceEngine::setPlaying (bool s){ playing=s && !steps.empty(); if(playing && playIndex<0) playIndex=0; }
void SequenceEngine::tick(){ if(playing && !steps.empty()) playIndex=(playIndex+1)%(int)steps.size(); }
