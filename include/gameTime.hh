#ifndef CDXG_GAME_TIME
#define CDXG_GAME_TIME

namespace cdxg {
    class GameTime {
        public:
        inline static float msDeltaTimeSec;
        inline static float msTotalTimeSec;
        GameTime() = delete;
        ~GameTime(){};
    }; //class GameTime
} //namespace cdxg

#endif