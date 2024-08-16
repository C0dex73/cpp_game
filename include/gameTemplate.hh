#ifndef CDXG_GAME
#define CDXG_GAME

#include <string>
namespace cdxg {
    class GameTemplate {
        protected:
        const int mInitialWidth;
        const int mInitialHeight;
        const std::string mInitialTitle;

        virtual void Initialize(){};
        virtual void LoadComponents(){};
        virtual void Update(){};
        virtual void Render(){};
        public:
        GameTemplate(int initialWidth, int initialHeight, std::string initialTitle);
        ~GameTemplate(){};
        void Run();
    }; // class GameTemplate
} // namespace cdxg

#endif