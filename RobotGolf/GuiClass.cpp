#include <GuiClass.h>
#include <setup.h>
#include <SerialPortClass.h>

Gui::Gui(){

    cout<<"Welcome to PuttPuttPal, Press the number of your option."<<endl;
    cout<<"1: Test"<<endl;
    cout<<"2: Old Reliable"<<endl;
    cout<<"3: NeverMiss"<<endl;
    cout<<"4: Exit"<<endl;

}

int Gui::getUserInput(){

    while(true){

        int choice = 0;
        // error checking, only moves forward if a viable option is chosen
        cin>> choice;
        if(choice !=1 && choice != 2 && choice!= 3 && choice != 4 && choice != 200){
            cout<<"You must enter the number of an option."<<endl;
            continue;
        }

        cout<<"You chose option: "<<choice<<endl;
        // write the option number to the serial


        return choice;
    }
}
