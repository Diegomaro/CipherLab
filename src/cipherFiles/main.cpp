#include "menu.hpp"

int main(){
    Menu menu;
    menu.menuInitialization();
    if(!menu.centralMenu()){
        return 1;
    }
    return 0;
}
