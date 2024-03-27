/* File : CS112_A3_Part1_S25_20230631_20231132_20231108.cpp
 * Purpose: this program is designed to embrace these filters :
 filter one : convert image to grayscale
 filter two : rotate image clockwise to a selected rotation angle (90,180,270)
 filter three : invert image's color
 filter four : darken or lighten the image by 50%
 filter five : convert image to black and white
*/
// Authors :
// Author 1 : Omar Fawzy Abdulhamid Mahmoud ID: 20230631 Section:26
// (Solved Filter 1,Filter 7)
// Email: orf6905@gmail.com
// Author 2 : Mohamed Ahmed Khalaf Mohamed  ID: 20231132 Section:25
// (Solved Filter 3,Filter 6)
// Email: akph2005mk@gmail.com
// Author 3 : Ali Osama Ali Ebrahim         ID: 20231108 Section:25
// (Solved Filter 2)
// Email: ali155osama@gmail.com
// Version: 1.0
// Date: 27/3/2024

#include "Image_Class.h"
#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

// Prototype for the saving_image function
void saving_image(Image &image, string &filename);
// Prototype for the saving_condition function
void saving_condition(Image &image, string &filename);

// Define an enumeration for menu options
enum enmenu_image { load_image = 1, Exit = 2 };

// Define an enumeration for filter options
enum enfilters {
  GrayScale = 1,
  RotateImage = 2,
  InvertImage = 3,
  DarkenAndLighten = 4,
  BlackAndWhite = 5,
  saving = 6
};

// Function to display the main menu
void menu() {
  cout << "\nwelcome to baby photoshop" << endl;
  cout << "1) Load image " << endl;
  cout << "2) Exit " << endl;
}

// Function to handle user input for the main menu
enmenu_image menu_user_input() {

  int choice;
  string input;
  bool valid_input = false;

  // Loop until a valid choice is entered
  do {
    cout << "Enter your choice: ";
    cin >> input;

    // Check if the input consists of digits only
    if (all_of(input.begin(), input.end(), [](char c) { return isdigit(c); })) {
      choice = stoi(input);

      // Validate the input choice
      if (choice >= 1 && choice <= 2) {
        valid_input = true;
      } else {
        cout << "Invalid input. Please enter a valid choice." << endl;
      }
    } else {
      cout << "Invalid input. Please enter a valid choice." << endl;
    }

  } while (!valid_input);

  return enmenu_image(choice);
}

// Function to display the sub menu for filter options
void sub_menu() {
  cout << "\nchoose a filter " << endl;
  cout << "1) Gray scale " << endl;
  cout << "2) Rotate image " << endl;
  cout << "3) Invert image colors " << endl;
  cout << "4) Darken and lighten " << endl;
  cout << "5) Black and white " << endl;
  cout << "6) save " << endl;
}

// Function to handle user input for selecting a filter
enfilters menu_user_filter() {
  int choice;
  string input;
  bool valid_input = false;

  // Loop until a valid filter choice is entered
  do {
    cout << "Enter your filter choice: ";
    cin >> input;

    // Check if the input consists of digits only
    if (all_of(input.begin(), input.end(), [](char c) { return isdigit(c); })) {
      choice = stoi(input);

      // Validate the input choice against the filter options
      if (choice >= 1 && choice <= 6) {
        valid_input = true;
      } else {
        cout << "Invalid input. Please enter a valid filter choice." << endl;
      }
    } else {
      cout << "Invalid input. Please enter a valid filter choice." << endl;
    }

  } while (!valid_input);

  return enfilters(choice);
}

// Function to create a new grayscale image from the input image
Image gray_scale(Image &image) {
  Image gray(image.width, image.height);

  // Calculate the average pixel value for each pixel in the input image
  for (int y = 0; y < gray.height; y++) {
    for (int x = 0; x < gray.width; x++) {
      unsigned char average =
          (image(x, y, 0) + image(x, y, 1) + image(x, y, 2)) / 3;

      // Set the average pixel value for each channel in the grayscale image
      gray(x, y, 0) = average;
      gray(x, y, 1) = average;
      gray(x, y, 2) = average;
    }
  }
  return gray;
}

void rotate_image_clockwise(Image &image, int degrees) {
  if (degrees == 90 || degrees == 180 || degrees == 270) {

    int num_rotations = degrees / 90;
    int new_width, new_height;
    // in the case of 180 rotation the dimensions are the same
    if (num_rotations % 2 == 0) {

      new_width = image.width;
      new_height = image.height;
    }
    // other rotation cases flip the dimensions
    else {
      new_width = image.height;
      new_height = image.width;
    }
    // a dynamic allocated array of every value in it takes maximum of 255
    unsigned char *newImageData =
        new unsigned char[new_width * new_height * image.channels];

    for (int x = 0; x < image.width; x++) {
      for (int y = 0; y < image.height; y++) {
        for (int c = 0; c < image.channels; c++) {

          int new_x, new_y;
          if (degrees == 90) {
            // getting every pixel dimensions from the original image
            // starting from the top right
            new_x = image.height - y - 1;
            new_y = x;
          } else if (degrees == 180) {
            // getting every pixel dimensions from the original image
            // starting from the bottom right
            new_x = image.width - x - 1;
            new_y = image.height - y - 1;
          } else {
            // getting every pixel dimensions from the original image
            // starting from the bottom left
            new_x = y;
            new_y = image.width - x - 1;
          }
          // loading the data in the allocated array
          newImageData[(new_y * new_width + new_x) * image.channels + c] =
              image.getPixel(x, y, c);
        }
      }
    }

    delete[] image.imageData; // Free the old memory using delete[]
    // putting the data of pixels of the array into the object
    image.imageData = newImageData;
    // setting the new width and the new height
    image.width = new_width;
    image.height = new_height;
  }
}

Image invert_colors(Image &image) {
  // making a new object with the same dimensions as the image
  Image invert(image.width, image.height);

  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      /*
       getting every pixel channel of the image and subtract 255 from it to
      invert it and then assign it to the corresponding channel in the invert
      object
       */
      invert(i, j, 0) = 255 - image(i, j, 0);
      invert(i, j, 1) = 255 - image(i, j, 1);
      invert(i, j, 2) = 255 - image(i, j, 2);
    }
  }
  return invert;
}

// Function to create a new image by darkening the input image by 50%
Image image_darken(Image &image) {
  Image darken(image.width, image.height);
  for (int y = 0; y < image.height; y++) {
    for (int x = 0; x < image.width; x++) {
      for (int c = 0; c < image.channels; c++) {

        // Get the current pixel value from the input image
        int current_pixel_value = image.getPixel(x, y, c);

        // Darken the pixel value by 50%
        int new_pixel_value = current_pixel_value * 0.5;

        // Set the new pixel value in the darkened image
        darken.setPixel(x, y, c, new_pixel_value);
      }
    }
  }
  return darken;
}

// Function to create a new image by lightening the input image by 50%
Image image_lighten(Image &image) {
  Image lighten(image.width, image.height);
  for (int y = 0; y < image.height; y++) {
    for (int x = 0; x < image.width; x++) {
      for (int c = 0; c < image.channels; c++) {
        int current_pixel_value = image.getPixel(x, y, c);

        // Lighten the pixel value by 50%
        int new_pixel_value = current_pixel_value * 1.5;

        // Clamp the new pixel value to the maximum value of 255
        if (new_pixel_value > 255) {
          new_pixel_value = 255;
        }

        // Set the new pixel value in the lightened image
        lighten.setPixel(x, y, c, new_pixel_value);
      }
    }
  }
  return lighten;
}

Image black_white(Image &image) {
  Image black_white(image.width, image.height);
  for (int y = 0; y < image.height; y++) {
    for (int x = 0; x < image.width; x++) {
      unsigned char average =
          (image(x, y, 0) + image(x, y, 1) + image(x, y, 2)) / 3;
      unsigned char pixel_color = (average < 127) ? 0 : 255;
      black_white(x, y, 0) = pixel_color;
      black_white(x, y, 1) = pixel_color;
      black_white(x, y, 2) = pixel_color;
    }
  }
  return black_white;
}

void filters(Image &image, string &filename) {
  // sub menu to choose the filter to apply
  sub_menu();
  // the choice of the user
  enfilters filter = menu_user_filter();
  // the resulting object to save the edited image from the filters
  Image result_image;

  if (filter == ::RotateImage) {
    string choice;
    do {
      cout << "\nchoose a rotation angle " << endl;
      cout << "1) 90  degree " << endl;
      cout << "2) 180 degree " << endl;
      cout << "3) 270 degree " << endl;
      // choice to rotate the image by a certain degree
      cin >> choice;
    } while (choice != "1" && choice != "2" && choice != "3");

    if (choice == "1") {
      rotate_image_clockwise(image, 90);
    } else if (choice == "2") {
      rotate_image_clockwise(image, 180);
    } else {
      rotate_image_clockwise(image, 270);
    }

    result_image = image;
  } else if (filter == ::GrayScale) {
    result_image = gray_scale(image);
  } else if (filter == ::InvertImage) {
    result_image = invert_colors(image);
  } else if (filter == ::BlackAndWhite) {
    result_image = black_white(image);
  } else if (filter == ::DarkenAndLighten) {
    string choice;
    do {
      cout << "Lighten or darken (l/d): ";
      cin >> choice;
    } while (choice != "d" && choice != "D" && choice != "l" && choice != "L");

    if (choice == "d" || choice == "D") {
      result_image = image_darken(image);
    } else {
      result_image = image_lighten(image);
    }
  } else if (filter == ::saving) {
    // to save in the filter menu
    result_image = image;
    saving_condition(result_image, filename);
    return;
  }
  // after applying the desired filters save the result_image
  saving_image(result_image, filename);
}

void saving_image(Image &image, string &filename) {
  string saving;
  do {
    cout << "Do you want to save the image or apply another filter? (s/a): ";
    cin >> saving;
    // if the user wants to apply another filter on the resulted image
    if (saving == "a" || saving == "A") {
      filters(image, filename);
      return;
    }
    // if the user wants to save after applying the desired filters
    if (saving == "s" || saving == "S") {
      saving_condition(image, filename);
      return;
    }
  } while (saving != "a" || saving != "A" || saving != "s" || saving != "S");
}

void saving_condition(Image &image, string &filename) {
  string save_choice;
  do {

    cout << "Do you want to save with the same name? (y/n): ";
    cin >> save_choice;
    if (save_choice == "y" || save_choice == "Y") {
      if (!image.saveImage(filename)) {
        cout << "Error: Unable to save the image " << filename << endl;
        return; // Return an error code
      }
      cout << "Image saved successfully as " << filename << endl;
      return;
    } else if (save_choice == "n" || save_choice == "N") {
      cout << "Please enter the name or the full path of the new image to "
              "save (with "
              "extension .jpg, .bmp, .png, .tga): ";
      // ignoring the enter key press
      cin.ignore(1, '\n');
      // getting the new filename to save in
      getline(cin, filename);
      if (!image.saveImage(filename)) {
        cout << "Error: Unable to save the image " << filename << endl;
        return; // Return an error code
      }
      cout << "Image saved successfully as " << filename << endl;
      return;
    }
  } while (save_choice != "y" || save_choice != "Y" || save_choice != "n" ||
           save_choice != "N");
}

void baby_photoshop() {
  string filename;

  while (true) {
    // main menu to load a new or exit
    menu();
    // getting the user input to load or exit
    enmenu_image image_choice = menu_user_input();

    if (image_choice == ::Exit) {
      return;
    }

    if (image_choice == ::load_image) {
      cout << "Please enter the name or the full path of the image that you "
              "want to edit: ";
      // getting filepath or file name with extention
      cin.ignore(1, '\n');
      getline(cin, filename);
      // declare the object with constructor with the filepath with extension
      Image image(filename);
      //  function all filters
      filters(image, filename);
    }
  }
}

int main() {

  baby_photoshop();
  return 0;
}
