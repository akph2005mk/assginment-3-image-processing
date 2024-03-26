#include <iostream>
#include <string>
#include "Image_Class.h" // Include your Image class header here

void gray_scale( Image &image){

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
void fliphorizontally(Image &image){

     for (int i = 0; i < image.width / 2; ++i) {
            for (int j = 0; j < image.height; ++j) {
                // Swap pixels horizontally
                for (int k = 0; k < 3; ++k) {
                    std::swap(image(i, j, k), image(image.width - 1 - i, j, k));
                }
            }
        }
    }
void flipvertically(Image &image){
    for (int i = 0; i < image.width; ++i) {
            for (int j = 0; j < image.height / 2; ++j) {
                // Swap pixels vertically
                for (int k = 0; k < 3; ++k) {
                    std::swap(image(i, j, k), image(i, image.height - 1 - j, k));
                }
            }
        }
}

 // Convert the image to black and white
 void blackWhite(Image &image){
    const int threshold = 128; // Threshold value

    for (int i = 0; i < image.width; ++i) {
        for (int j = 0; j < image.height; ++j) {
            unsigned int average = 0; // Initialize average value

            // Calculate the average of RGB channels
            for (int k = 0; k < 3; ++k) {
                average += image(i, j, k); // Accumulate pixel values
            }

            average /= 3; // Calculate average

            // Set pixel to black or white based on threshold
            if (average >= threshold) {
                image(i, j, 0) = 255; // Set red channel to maximum (white)
                image(i, j, 1) = 255; // Set green channel to maximum (white)
                image(i, j, 2) = 255; // Set blue channel to maximum (white)
            } else {
                image(i, j, 0) = 0; // Set red channel to minimum (black)
                image(i, j, 1) = 0; // Set green channel to minimum (black)
                image(i, j, 2) = 0; // Set blue channel to minimum (black)
            }
        }
    }
}


int main() {
    std::string filename;
    std::cout << "Please enter the name of the colored image to edit: ";
    std::cin >> filename;

    // Load the image
    Image image(filename);
    std::cout<<"1) Black and White filter\n";
    std::cout<<"2)Gray filter\n";
    std::cout<<"3)Fliping the image\n";

    int user_choice;
    std::cin>>user_choice;
    if(user_choice == 1){

    blackWhite(image);
    }
    else if(user_choice == 2){
        gray_scale(image);
    }
    else if(user_choice == 3){

    int flipDirection;
    std::cout << "Enter 1 for 'horizontal' or 2 for 'vertical' to flip the image: ";
    std::cin >> flipDirection;
    // Flip the image horizontally
       if (flipDirection == 1) {
        fliphorizontally(image);
       }
       else if(flipDirection == 2)
       flipvertically(image);

    }
    else{
        std::cout<<"invalid input exiting.......";
        return 1;
    }
   
    // Save the black and white image
    std::cout << "Please enter the name of the new image to save (with extension .jpg, .bmp, .png, .tga): ";
    std::cin >> filename;

    if (!image.saveImage(filename)) {
        std::cerr << "Error: Unable to save the image " << filename << std::endl;
        return 1; // Return an error code
    }

    std::cout << "Image saved successfully as " << filename << std::endl;

    return 0;
}

