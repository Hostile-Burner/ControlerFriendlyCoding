#include <SDL3/SDL.h>
#include "CInputToCBC.cpp" 
#include <iostream>

int main() {
    //initalize SDL
    if (!SDL_Init(SDL_INIT_GAMEPAD)) {
        std::cerr << "SDL init failed: " << SDL_GetError() << "\n";
        exit(1);
    }

    CBC cbcProcessor;
    CInputToCBC inputHandler;
    inputHandler.loadSettings("settings.yaml"); // Loads YAML mappings

    SDL_Event e;
    while (true) {
        while (SDL_PollEvent(&e)) {
            //Check for Exit
            if (e.type == SDL_EVENT_QUIT) {
                SDL_Quit();
                return 0;
            }

            // Logic for CInputToCBC.cpp
            void handleController(SDL_Event& e, CBC& cbc, CInputToCBC& handler) {
                if (e.type == SDL_EVENT_GAMEPAD_AXIS_MOTION) {
                     // Update the internal degree tracker based on right joystick
                     if (e.gaxis.axis == SDL_GAMEPAD_AXIS_RIGHT_X || e.gaxis.axis == SDL_GAMEPAD_AXIS_RIGHT_Y) {
                        handler.updateJoystick(e.gaxis.value, e.gaxis.value);[cite: 10]
        }
    }

    if (e.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN) {
        // Button 1 Circle/B is the confirm button in our layout
        if (e.gbutton.button == SDL_GAMEPAD_BUTTON_EAST) {
            std::string token = handler.getConfirmedToken();[cite: 10]
            cbc.runLive(token); // Triggers the keyboard output
        }
        
        // Button 2 Square/X for Backspace
        if (e.gbutton.button == SDL_GAMEPAD_BUTTON_WEST) {
            sendKeyboardOutput("\b"); // Backspace escape character
        }
    }
}
            // It processes axes (joysticks) and button presses[cite: 4, 10]
            
            if (e.type == SDL_EVENT_GAMEPAD_AXIS_MOTION) {
                // Update joystick angle for the selection wheel
                if (e.gaxis.axis == SDL_GAMEPAD_AXIS_RIGHT_X || e.gaxis.axis == SDL_GAMEPAD_AXIS_RIGHT_Y) {
                    inputHandler.updateJoystick(e.gaxis.value, e.gaxis.value);[cite: 10]
                }
                
                // Handle cursor navigation with Left Joystick[cite: 3, 10]
                if (e.gaxis.axis == SDL_GAMEPAD_AXIS_LEFT_X || e.gaxis.axis == SDL_GAMEPAD_AXIS_LEFT_Y) {
                    inputHandler.handleMovement(e.gaxis.value, e.gaxis.value);[cite: 10]
                }
            }

            if (e.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN) {
                // Confirm selection or trigger special keys (Backspace/Space)
                inputHandler.handleButtonPress(e.gbutton.button, cbcProcessor);[cite: 10]
            }
        }
    }
}
    
    // count of controllers visable
    int count = 0; 
    SDL_JoystickID* gamepads = SDL_GetGamepads(&count);
    // if any controllers exist
    if (!gamepads || count == 0) {
        std::cout << "No controller found\n";
        SDL_free(gamepads);
        SDL_Quit();
        exit(1);
    }

    //use first controller
    SDL_Gamepad* controller = SDL_OpenGamepad(gamepads[0]);
    SDL_free(gamepads);

    //check if controlle = usable
    if (!controller) {
        std::cerr << "Could not open controller: " << SDL_GetError() << "\n";
        SDL_Quit();
        exit(1);
    }

    SDL_Event e;
    while (true) {
        //process each input from controller live
        while (SDL_PollEvent(&e)) {
            //buttons
            if (e.type == SDL_EVENT_GAMEPAD_BUTTON_DOWN) {
                std::cout << "Button: " << (int)e.gbutton.button << "\n";
            }
            //thumbsticks/joysticks
            if (e.type == SDL_EVENT_GAMEPAD_AXIS_MOTION) {
                std::cout << "Axis: " << (int)e.gaxis.axis
                          << " value: " << e.gaxis.value << "\n";
            }
            //when window is closed
            if (e.type == SDL_EVENT_QUIT) {
                SDL_CloseGamepad(controller);
                SDL_Quit();
                exit(0);
            }
        }
    }
}