#pragma once
#include <stdlib.h>
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

template<typename T>
struct RingBuffer
{
    private:
        std::vector<T> buffer;
        size_t current_pos = 0;
        const size_t MAX_SIZE = 100;

    public:
        RingBuffer() {}
        RingBuffer(size_t size) : MAX_SIZE(size) {
            buffer.reserve(size);
        }

        void push(T value) {
            // add value or rewrite existing block
            if (buffer.size() <= MAX_SIZE) {
                buffer.push_back(value);
            } else {
                buffer[current_pos] = value;
            }
            // move pos
            current_pos++;
            if (current_pos >= MAX_SIZE - 1) {
                current_pos = 0;
            }
        }

        size_t size() {
            return buffer.size();
        }

        bool empty() {
            return buffer.empty();
        }

        T& operator[](size_t index) {
            return buffer[index];
        }
};

using time_point = std::chrono::steady_clock::time_point;

class TickRateControl
{
    private:
        uint maxTickRate = 0;  // 0 = disable
        time_point tickStarted = std::chrono::steady_clock::now();
        const time_point objectCreated = std::chrono::steady_clock::now();

        RingBuffer<float> framesLogs;

    private:
        float calcFrameDuration() {
            if (framesLogs.empty())
                return 0.0f;
            
            // recorded frames runtime
            float runtime = 0.0f;
            for (size_t i = 0; i < framesLogs.size(); i++) {
                runtime += framesLogs[i];
            }
            // average duration
            return runtime / framesLogs.size();
        }

        time_point getTimeNow() { // useful method to get the actual time 
            return std::chrono::steady_clock::now();
        }
        
    public:
        TickRateControl() : framesLogs(100) {}
        TickRateControl(uint tickRate) : TickRateControl() {
            maxTickRate = tickRate;
        }

        void setTickRate(uint maxRate) {
            maxTickRate = maxRate;
        }

        void frameStarted() {
            tickStarted = getTimeNow();
        }

        void frameFinished() {
            if (maxTickRate > 0) {
                auto expectedDur = std::chrono::duration<float>(1.0f / (float) maxTickRate);  // got expected frame duration
                std::this_thread::sleep_until(tickStarted + expectedDur);
            }

            // save frame duration for logs
            auto now = getTimeNow();
            float delta = std::chrono::duration<float>(now - tickStarted).count();
            framesLogs.push(delta);
        }

        void printLogs() {
            auto now = getTimeNow();
            auto runtime = std::chrono::duration<float>(now - objectCreated);
            float frame = calcFrameDuration();
            std::clog << "Continued: " << runtime.count() << " sec\n";
            std::clog << "Average frame duration: " << frame << " sec\n";
            std::clog << "Fps: " << 1.0f / frame << "\n";
        }
};