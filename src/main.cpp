#include <Geode/Geode.hpp>

#include <Geode/modify/CCEGLView.hpp>


using namespace geode::prelude;


#ifdef GEODE_IS_WINDOWS
class $modify(CCEGLView) {
    
    void pollEvents() {
        CCEGLView::pollEvents();


        static float music = 0;
        static float sfx = 0;
        static bool focused = false;
        FMODAudioEngine* sound = FMODAudioEngine::sharedEngine();

        if (GetActiveWindow() == WindowFromDC(wglGetCurrentDC())) { //checks if Geometry Dash is focused
            

            if (!focused) {
                //detected focused. Bring back sound
                

                sound->setBackgroundMusicVolume(music);
                sound->setEffectsVolume(sfx);

                focused = true;
            }
        }
        else if (focused) {
            //detected unfocused. Mute game volume
             
            music = sound->m_musicVolume;
            sfx = sound->m_sfxVolume;
            sound->setBackgroundMusicVolume(0);
            sound->setEffectsVolume(0);
            
            focused = false;
        }
        
    }
};
#endif
