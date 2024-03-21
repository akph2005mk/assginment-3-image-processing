#include <iostream>
#include "Image_Class.h"
# include <algorithm>
using namespace std;
enum enmenu_image{load_image=1,save_image=2,Exit=3};

void menu(){
    cout<<"\nwelcome to baby photoshop"<<endl;
    cout<<"1) load image "<<endl;
    cout<<"2) save image "<<endl;
    cout<<"3) exit "<<endl;
}

enmenu_image menu_user_input(){
    int choice;
    string input;
    do {
        cin>>input;
        if(all_of(input.begin(),input.end(),[](char c){return isdigit(c);})) {
            choice =stoi(input);
        }

    }while(choice<1 || choice >3);

    return enmenu_image(choice);
}

void gray_scale( Image image){

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned  int avg = 0; // Initialize average value

            for (int k = 0; k < 3; ++k) {
                avg += image(i, j, k); // Accumulate pixel values
            }

            avg /= 3; // Calculate average

            // Set all channels to the average value
            image(i, j, 0) = avg;
            image(i, j, 1) = avg;
            image(i, j, 2) = avg;
        }
    }
}
Image image;
int main() {

    while(true){
        menu();
        enmenu_image image_choice = menu_user_input();
        if (image_choice == ::load_image) {
            string file_name;
            Image loaded(file_name);
            image =loaded;
            gray_scale(image);

        }
         if (image_choice == ::save_image) {
            string file_name;
            cin>>file_name;
            image.saveImage(file_name);
        }
         if (image_choice == ::Exit) {

            break;
        }


    }
    return 0;
}
