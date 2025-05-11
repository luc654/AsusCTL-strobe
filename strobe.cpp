#include <cstdlib>
#include <chrono>
#include <string>
#include <iostream>
#include <thread>

using namespace std;



int strobeUp(int delay){
    using namespace std::this_thread;
    using namespace std::chrono;
    for(int index = 0; index < 3;index++){
        sleep_for(milliseconds(delay));
        system("asusctl -n");
    };

    return 0;
}

int strobeDown(int delay){
    using namespace std::this_thread;
    using namespace std::chrono;
    for(int index = 0; index < 3;index++){
        sleep_for(milliseconds(delay));
        system("asusctl -p");
    };
    return 0;
}

int reset(){
    system("asusctl -k off");
    return 0;
};

int main(int argc, char* argv[]){
    int cycle = 3;
    int delay = 150;
    for(int i = 0; i < argc; i++){
        std::string arg = argv[i];

        if(arg == "--cycle" && i + 1 < argc){
            cycle = std::atoi(argv[i + 1]);
            i++;
        } else if (arg == "--delay" && i + 1 < argc){
            delay = std::atoi(argv[i + 1]);
            i++;
        } else if (i > 1) {
            std::cerr << "Unknown argument: " << arg << std::endl;
            std::cerr << "Correct arguments: --delay || --cycle." << std::endl;
        }
    }

    reset();

    for (int i = 0; i < cycle; i++){
        strobeUp(delay);
        strobeDown(delay);
    }
    
    system("asusctl -n");


    return 0;
}


