#pragma once

#include <chrono>
#include <thread>

class FrameLimiter {
public:
    FrameLimiter(int targetFps)
        : frameDuration(1000.0 / targetFps), deltaTime(0.0)
    {
        lastFrame = std::chrono::high_resolution_clock::now();
    }

    void wait() {
        using namespace std::chrono;
        auto now = high_resolution_clock::now();
        auto elapsed = duration<double, std::milli>(now - lastFrame);  

        auto sleepTime = duration<double, std::milli>(frameDuration - elapsed.count());  

        if (sleepTime.count() > 2.0) {
            std::this_thread::sleep_for(sleepTime - milliseconds(1));
        }

        while (high_resolution_clock::now() - lastFrame < milliseconds(static_cast<long long>(frameDuration))) {}

        auto frameEnd = high_resolution_clock::now();
        deltaTime = duration<double>(frameEnd - lastFrame).count();  // в секундах
        lastFrame = frameEnd;
    }

    double getDeltaTime() const {
        return deltaTime; 
    }

private:
    std::chrono::high_resolution_clock::time_point lastFrame;
    double frameDuration;  
    double deltaTime;      
};
