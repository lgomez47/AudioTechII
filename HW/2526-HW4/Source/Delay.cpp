/*
  ==============================================================================

    Delay.cpp
 
    This code contains the implementation needed for a simple feedback delay.

  ==============================================================================
*/

#include "Delay.h"


void Delay::prepare(double samplingRate, int maxDelay, int numChannels)
{
    sampleRate = samplingRate;
    delayBufferSize = maxDelay;
    delayBuffer.setSize(numChannels,delayBufferSize);
    delayBuffer.clear();
    
    // sets smoothing changes to linear smoothing in 10ms
    smoothedDelay.reset(sampleRate, 0.01);
    
    writeHeads.resize(numChannels);
    for (int c = 0; c < numChannels; ++c)
    {
        writeHeads[c] = 0;
    }

}

void Delay::setMaxDelayInSamples(int maxDelay)
{
    maxDelayInSamples = maxDelay;
}

int Delay::getMaxDelayInSamples()
{
    return maxDelayInSamples;
}

void Delay::setDelayTime(float delaySeconds)
{
    smoothedDelay.setTargetValue(delaySeconds);
    
}

void Delay::setWetMix(float wetAmount)
{
    mix = wetAmount;
}





void Delay::setDelayLength(float delayInSamples)
{
    delaySamples = (int)delayInSamples;
}

void Delay::setFeedbackAmt(float feedbackAmt)
{
    feedback = feedbackAmt;
}


// this is called in the ProcessBlock as we iterate over each channel's buffer
float Delay::processSample(float inputSample, int channel)
{
    float* delayData = delayBuffer.getWritePointer(channel);
    int writeHead = writeHeads[channel];
//    if (channel == 0)
//    {
//        nextLfoVal();
//        currDelay = smoothedDelay.getNextValue();
//    }
    
//    float modDelay = currDelay + lfo;
//    modDelay = std::clamp<float>(modDelay, 0.001f, (delayBufferSize / sampleRate));
//    float delaySamples = modDelay * sampleRate;
//    float delayed = interpRead(delayData, writeHead, delaySamples);
    
    //delayData[writeHead] = inputSample;
//    DBG(delayed);
    
    int readTail = (writeHead - delaySamples + delayBufferSize) % delayBufferSize;
    float delayed = delayData[readTail];
    //with feedback
    delayData[writeHead] = inputSample + (feedback * delayed);
    delayed = ((1.0 - mix) * inputSample) + (mix * delayed);
    
    writeHead = (writeHead + 1) % delayBufferSize;
    writeHeads[channel] = writeHead;
    return delayed;
}
