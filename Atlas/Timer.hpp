#pragma once

#include <SDL.h>

//The application time based timer
class Timer {
    private:
        // The clock time when the timer started
        Uint32 m_startTicks;

        // The ticks stored when the timer was paused
        Uint32 m_pausedTicks;

        //The timer status
        bool m_paused;
        bool m_started;

    public:
        //Initializes variables
        Timer();

        //The various clock actions
        void start();
        void stop();
        void pause();
        void unpause();

        //Gets the timer's time
        Uint32 getTicks();

        //Checks the status of the timer
        bool isStarted();
        bool isPaused();
};