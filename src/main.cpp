#include <Geode/Geode.hpp>

#include <Geode/modify/CCEGLView.hpp>
#include <Geode/modify/AppDelegate.hpp>


using namespace geode::prelude;

namespace {
    float music = 0;
    float sfx = 0;
    bool savedVolume = false;
}

#ifdef GEODE_IS_WINDOWS
class $modify(CCEGLView) {
    
    void pollEvents() {
        CCEGLView::pollEvents();


        
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
            savedVolume = true;
            sound->setBackgroundMusicVolume(0);
            sound->setEffectsVolume(0);
            
            focused = false;
        }
        
    }


};

class $modify(AppDelegate) {
    void platformShutdown() {
        AppDelegate::platformShutdown();

        FMODAudioEngine* sound = FMODAudioEngine::sharedEngine();

        if (savedVolume) {
            sound->setBackgroundMusicVolume(music);
            sound->setEffectsVolume(sfx);
            //fixes a bug where the volume would be muted on reopen and focus, if gd is closed while unfocused
        }
    }
};

#endif


