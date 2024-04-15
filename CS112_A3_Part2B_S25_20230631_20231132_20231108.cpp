/* File : CS112_A3_Part2B_S25_20230631_20231132_20231108.cpp
 * Purpose: this program is designed to embrace these filters :
 filter one : convert image to grayscale
 filter two : rotate image clockwise to a selected rotation angle (90,180,270)
 filter three : invert image's color
 filter four : darken or lighten the image by 50%
 filter five : convert image to black and white
 filter six : Applying a basic frame or fancy frame to an image
 filter seven : resize an image to user defined width and height
 filter eight : crop an image to user defined width and height
 filter nine : detect edges to an image
 filter ten : blur an image
filter eleven : merge two images
filter twelve : flip an image horizonatal or vertical
filter thirteen : oil paint an image
filter fourteen : infrared an image
filter fifteen : apply purple effect
filter sixteen : apply sunlight effect
filter seventeen : skew an image
filter eighteen : apply old tv effect
*/
// Authors :
// Author 1 : Omar Fawzy Abdulhamid Mahmoud ID: 20230631 Section:26
// (Solved Filter 1,Filter4,Filter 7,Filter 10,Filter 14,Filter 18)
// Email: orf6905@gmail.com
// Author 2 : Mohamed Ahmed Khalaf Mohamed  ID: 20231132 Section:25
// (Solved Filter 3,Filter 6,Filter 9,Filter12,Filter 13,Filter 15,Filter 17)
// Email: akph2005mk@gmail.com
// Author 3 : Ali Osama Ali Ebrahim         ID: 20231108 Section:25
// (Solved Filter 2,Filter 5,Filter 8,Filter 11,Filter 16)
// Email: ali155osama@gmail.com
// Version: 1.0
// Date: 15/4/2024

#include "Image_Class.h"
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
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
  Frame = 6,
  Resize = 7,
  Crop = 8,
  EdgeDetect = 9,
  Blur = 10,
  merge = 11,
  flip = 12,
  oil = 13,
  Infrared = 14,
  Purple = 15,
  Sunlight = 16,
  Skew = 17,
  oldTv = 18,
  saving = 19,
};

int random_(int from, int to) {
  int random = rand() % (to - from + 1) + from;
  return random;
}
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
  cout << "6) Applying frame " << endl;
  cout << "7) Resize image " << endl;
  cout << "8) Crop image " << endl;
  cout << "9) Edge detection " << endl;
  cout << "10) Blur image" << endl;
  cout << "11) merge" << endl;
  cout << "12) flip" << endl;
  cout << "13) oil painted" << endl;
  cout << "14) infrared" << endl;
  cout << "15) purple" << endl;
  cout << "16) sunlight effect" << endl;
  cout << "17) skew" << endl;
  cout << "18) old tv effect" << endl;
  cout << "19) save " << endl;
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
      if (choice >= 1 && choice <= 19) {
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
Image image_gray_scale(Image &image) {
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

Image image_invert_colors(Image &image) {
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

// Function to convert an image to black and white
Image image_black_white(Image &image) {
  Image black_white(image.width, image.height);

  // Loop through each pixel in the image
  for (int y = 0; y < image.height; y++) {
    for (int x = 0; x < image.width; x++) {
      // Calculate the average of RGB values
      unsigned char average =
          (image(x, y, 0) + image(x, y, 1) + image(x, y, 2)) / 3;

      // Set pixel color based on average intensity
      unsigned char pixel_color = (average < 98) ? 0 : 255;
      black_white(x, y, 0) = pixel_color;
      black_white(x, y, 1) = pixel_color;
      black_white(x, y, 2) = pixel_color;
    }
  }
  return black_white;
}

void image_adding_frame(Image &image, char color_outer) {
  int frame_thickness =
      min(image.width, image.height) / 60; // Thickness of the frame

  // Process outer frame
  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      if (i < frame_thickness || i >= image.width - frame_thickness ||
          j < frame_thickness || j >= image.height - frame_thickness) {
        // Outer frame
        if (color_outer == 'b' || color_outer == 'B') {
          // Blue outer frame
          image.setPixel(i, j, 0, 0);
          image.setPixel(i, j, 1, 0);
          image.setPixel(i, j, 2, 255);
        } else if (color_outer == 'r' || color_outer == 'R') {
          // Red outer frame
          image.setPixel(i, j, 0, 255);
          image.setPixel(i, j, 1, 0);
          image.setPixel(i, j, 2, 0);
        } else if (color_outer == 'g' || color_outer == 'G') {
          // Green outer frame
          image.setPixel(i, j, 0, 0);
          image.setPixel(i, j, 1, 255);
          image.setPixel(i, j, 2, 0);
        }
      }
    }
  }
}

void image_adding_fancyframe(Image &image, char color_outer) {
  int frame_thickness =
      min(image.width, image.height) / 60; // Thickness of the frame
  int inner_frame_thickness =
      frame_thickness + 15; // Thickness of the inner frame
  // Process outer frame
  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      if (i < frame_thickness || i >= image.width - frame_thickness ||
          j < frame_thickness || j >= image.height - frame_thickness) {
        // Outer frame
        if (color_outer == 'b' || color_outer == 'B') {
          // Blue outer frame
          image.setPixel(i, j, 0, 0);
          image.setPixel(i, j, 1, 0);
          image.setPixel(i, j, 2, 255);
        } else if (color_outer == 'r' || color_outer == 'R') {
          // Red outer frame
          image.setPixel(i, j, 0, 255);
          image.setPixel(i, j, 1, 0);
          image.setPixel(i, j, 2, 0);
        } else if (color_outer == 'g' || color_outer == 'G') {
          // Green outer frame
          image.setPixel(i, j, 0, 0);
          image.setPixel(i, j, 1, 255);
          image.setPixel(i, j, 2, 0);
        }
      }
    }
  }

  // Process inner frame
  for (int i = frame_thickness; i < image.width - frame_thickness; ++i) {
    for (int j = frame_thickness; j < image.height - frame_thickness; ++j) {
      if (i < inner_frame_thickness ||
          i >= image.width - inner_frame_thickness ||
          j < inner_frame_thickness ||
          j >= image.height - inner_frame_thickness) {
        // Inner frame (white)
        image.setPixel(i, j, 0, 255);
        image.setPixel(i, j, 1, 255);
        image.setPixel(i, j, 2, 255);
      }
    }
  }
}

// Function to resize an image
Image image_resize(Image &image) {
  // Ask user for new dimensions
  int new_width;
  int new_height;
  cout << "Enter the new width of the resized image: ";
  cin >> new_width;
  cout << "Enter the new height of the resized image: ";
  cin >> new_height;

  // Create a new image with the new dimensions
  Image resized_image(new_width, new_height);

  // Calculate scale factors
  float scale_x = static_cast<float>(image.width) / new_width;
  float scale_y = static_cast<float>(image.height) / new_height;

  // Loop through each pixel in the resized image
  for (int x = 0; x < new_width; ++x) {
    for (int y = 0; y < new_height; ++y) {
      // Calculate corresponding block in original image
      int start_x = static_cast<int>(x * scale_x);
      int end_x = static_cast<int>((x + 1) * scale_x);
      int start_y = static_cast<int>(y * scale_y);
      int end_y = static_cast<int>((y + 1) * scale_y);

      // Calculate average color value of the block
      int total_red = 0, total_green = 0, total_blue = 0;
      for (int i = start_x; i < end_x; ++i) {
        for (int j = start_y; j < end_y; ++j) {
          total_red += image.getPixel(i, j, 0);
          total_green += image.getPixel(i, j, 1);
          total_blue += image.getPixel(i, j, 2);
        }
      }
      int average_red = total_red / ((end_x - start_x) * (end_y - start_y));
      int average_green = total_green / ((end_x - start_x) * (end_y - start_y));
      int average_blue = total_blue / ((end_x - start_x) * (end_y - start_y));

      // Set the pixel in the resized image with the average color value
      resized_image.setPixel(x, y, 0, average_red);
      resized_image.setPixel(x, y, 1, average_green);
      resized_image.setPixel(x, y, 2, average_blue);
    }
  }
  return resized_image;
}

// Function to crop an image
Image image_crop(Image &image) {
  // Get cropping parameters from user
  int x, y, width, height;
  cout << "Enter the x-coordinate of the upper left corner: ";
  cin >> x;
  cout << "Enter the y-coordinate of the upper left corner: ";
  cin >> y;
  cout << "Enter the width of the cropped area: ";
  cin >> width;
  cout << "Enter the height of the cropped area: ";
  cin >> height;

  // Check if cropping dimensions exceed original image dimensions
  if (x + width > image.width || y + height > image.height) {
    cerr << "Error: Cropping dimensions exceed original image dimensions."
         << endl;
    exit(1);
  }

  // Create a new image for cropped portion
  Image cropped_image(width, height);

  // Copy pixels from original image to new image
  for (int i = 0; i < width; ++i) {
    for (int j = 0; j < height; ++j) {
      // Copy pixel from original image to cropped image
      for (int k = 0; k < 3; ++k) {
        cropped_image.setPixel(i, j, k, image.getPixel(x + i, y + j, k));
      }
    }
  }
  return cropped_image;
}

// Function to detect edges in an image
Image image_detect_edges(Image &image) {
  Image image_with_detected_edges(image.width, image.height);

  // Convert image to black and white
  image = image_black_white(image);

  // Apply the Sobel operator for edge detection
  int sobel_kernel_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
  int sobel_kernel_y[3][3] = {{1, 2, 1}, {0, 0, 0}, {-1, -2, -1}};

  // Loop through each pixel in the image
  for (int y = 1; y < image.height - 1; y++) {
    for (int x = 1; x < image.width - 1; x++) {
      int gradient_x = 0;
      int gradient_y = 0;

      // Apply the Sobel operator
      for (int j = -1; j <= 1; j++) {
        for (int i = -1; i <= 1; i++) {
          gradient_x += image(x + i, y + j, 0) * sobel_kernel_x[j + 1][i + 1];
          gradient_y += image(x + i, y + j, 0) * sobel_kernel_y[j + 1][i + 1];
        }
      }

      // Calculate the gradient magnitude
      int magnitude = sqrt(gradient_x * gradient_x + gradient_y * gradient_y);

      // Apply thresholding to obtain binary edges
      image_with_detected_edges(x, y, 0) = magnitude > 128 ? 0 : 255;
      image_with_detected_edges(x, y, 1) = image_with_detected_edges(x, y, 0);
      image_with_detected_edges(x, y, 2) = image_with_detected_edges(x, y, 0);
    }
  }
  return image_with_detected_edges;
}

// Function to calculate cumulative sums of pixel values for each color channel
vector<vector<vector<int>>> calculate_cummulative_sums(Image &image) {
  vector<vector<vector<int>>> table(
      image.width, vector<vector<int>>(image.height, vector<int>(3, 0)));

  // Loop through each pixel in the image
  for (int x = 0; x < image.width; x++) {
    for (int y = 0; y < image.height; y++) {
      for (int c = 0; c < 3; c++) {
        // Calculate cumulative sums
        table[x][y][c] = image.getPixel(x, y, c);
        if (x > 0)
          table[x][y][c] += table[x - 1][y][c];
        if (y > 0)
          table[x][y][c] += table[x][y - 1][c];
        if (x > 0 && y > 0)
          table[x][y][c] -= table[x - 1][y - 1][c];
      }
    }
  }
  return table;
}

// Function to blur an image
Image image_blur(Image &image) {
  // Calculate cumulative sums of pixel values for each color channel
  vector<vector<vector<int>>> cumulative_sums =
      calculate_cummulative_sums(image);
  int window_size = 15;
  int window_area = (2 * window_size + 1) * (2 * window_size + 1);
  Image blurred(image.width, image.height);

  // Loop through each pixel in the image
  for (int i = window_size; i < image.width - window_size; ++i) {
    for (int j = window_size; j < image.height - window_size; ++j) {
      int start_x = max(0, i - window_size);
      int start_y = max(0, j - window_size);
      int end_x = min(image.width - 1, i + window_size);
      int end_y = min(image.height - 1, j + window_size);

      // Calculate sum of pixel values within the window
      for (int c = 0; c < 3; c++) {
        int sum = cumulative_sums[end_x][end_y][c];
        if (start_x > 0)
          sum -= cumulative_sums[start_x - 1][end_y][c];
        if (start_y > 0)
          sum -= cumulative_sums[end_x][start_y - 1][c];
        if (start_x > 0 && start_y > 0)
          sum += cumulative_sums[start_x - 1][start_y - 1][c];

        // Calculate average pixel value and set it in the blurred image
        blurred.setPixel(i, j, c, sum / window_area);
      }
    }
  }
  return blurred;
}

// Function to apply a Sobel filter for edge detection
void apply_sobel(const Image &image, Image &image_with_edge) {
  // Sobel operator kernels for horizontal and vertical edge detection
  int sobel_x[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};

  int sobel_y[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};

  // Loop through each pixel in the image, excluding borders
  for (int y = 1; y < image.height - 1; y++) {
    for (int x = 1; x < image.width - 1; x++) {
      int gradient_x = 0;
      int gradient_y = 0;

      // Apply the Sobel operator to calculate gradients in X and Y directions
      for (int j = -1; j <= 1; j++) {
        for (int i = -1; i <= 1; i++) {
          int pixel_x = x + i;
          int pixel_y = y + j;
          int value = image.getPixel(pixel_x, pixel_y, 0);
          gradient_x += value * sobel_x[j + 1][i + 1];
          gradient_y += value * sobel_y[j + 1][i + 1];
        }
      }

      // Calculate the gradient magnitude and set it as the pixel value in the
      // edge image
      int magnitude = sqrt(gradient_x * gradient_x + gradient_y * gradient_y);
      image_with_edge.setPixel(x, y, 0, static_cast<unsigned char>(magnitude));
      image_with_edge.setPixel(x, y, 1, static_cast<unsigned char>(magnitude));
      image_with_edge.setPixel(x, y, 2, static_cast<unsigned char>(magnitude));
    }
  }
}

// Function to calculate the average color of neighboring pixels within a radius
vector<int> calculate_average_color(const Image &image, int x, int y,
                                    int radius) {
  vector<int> average_color(3, 0);
  int count = 0;

  for (int j = -radius; j <= radius; j++) {
    for (int i = -radius; i <= radius; i++) {
      int neighbor_x = x + i;
      int neighbor_y = y + j;

      // Ensure the neighbor is within the image bounds
      if (neighbor_x >= 0 && neighbor_x < image.width && neighbor_y >= 0 &&
          neighbor_y < image.height) {
        average_color[0] += image.getPixel(neighbor_x, neighbor_y, 0);
        average_color[1] += image.getPixel(neighbor_x, neighbor_y, 1);
        average_color[2] += image.getPixel(neighbor_x, neighbor_y, 2);
        count++;
      }
    }
  }

  if (count > 0) {
    average_color[0] /= count;
    average_color[1] /= count;
    average_color[2] /= count;
  }

  return average_color;
}

// Function to apply an oil painting effect with color mixing, detail
// preservation, and realistic color blending
void image_oil_paint(const Image &image, Image &oil_painted_image,
                     int radius = 8, int intensity_levels = 20,
                     float color_mixing_factor = 1.0) {
  // Create an edge image for edge detection
  Image image_with_edge(image.width, image.height);
  // Apply Sobel filter for edge detection
  apply_sobel(image, image_with_edge);

  // Loop through each pixel in the image
  for (int y = 0; y < image.height; y++) {
    for (int x = 0; x < image.width; x++) {
      // Check if the pixel is an edge pixel
      bool is_an_edge = image_with_edge.getPixel(x, y, 0) > 30;

      // If the pixel is an edge pixel, skip the oil painting effect and keep
      // the original pixel
      if (is_an_edge) {
        for (int c = 0; c < 3; c++) {
          oil_painted_image.setPixel(x, y, c, image.getPixel(x, y, c));
        }
        continue;
      }

      // Calculate the average color of neighboring pixels within the radius
      vector<int> average_color = calculate_average_color(image, x, y, radius);

      // Set the pixel value to the average color
      oil_painted_image.setPixel(x, y, 0,
                                 static_cast<unsigned char>(average_color[0]));
      oil_painted_image.setPixel(x, y, 1,
                                 static_cast<unsigned char>(average_color[1]));
      oil_painted_image.setPixel(x, y, 2,
                                 static_cast<unsigned char>(average_color[2]));

      // Mix the average color with the original color using the color mixing
      // factor
      for (int c = 0; c < 3; c++) {
        int original_color = image.getPixel(x, y, c);
        oil_painted_image.setPixel(
            x, y, c,
            static_cast<unsigned char>((1 - color_mixing_factor) *
                                           original_color +
                                       color_mixing_factor * average_color[c]));
      }
    }
  }
}

// Function to create an infrared effect on an image
Image infrared(Image &image) {
  Image infrared(image.width, image.height);

  // Set red, green, and blue channels to their inverses
  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      infrared(i, j, 0) = 255 - image(i, j, 0);
      infrared(i, j, 1) = 255 - image(i, j, 1);
      infrared(i, j, 2) = 255 - image(i, j, 2);
    }
  }

  return infrared;
}

// Function to apply a purple tint effect to an image
void purple_effect(Image &image) {
  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      // Increase red and blue channels to enhance purple tint, decrease green
      // channel
      image(i, j, 0) = min(255, image(i, j, 0) + 20); // Red
      image(i, j, 1) = max(0, image(i, j, 1) - 60);   // Green
      image(i, j, 2) = min(255, image(i, j, 2) + 20); // Blue
    }
  }
}

// Function to apply a sunlight effect to an image
Image sunlight_effect(Image &image) {
  Image sunlight(image.width, image.height);

  // Increase red and decrease blue channels to simulate sunlight
  for (int i = 0; i < image.width; ++i) {
    for (int j = 0; j < image.height; ++j) {
      int pixels_r = image.getPixel(i, j, 0) + 30;
      int pixels_b = image.getPixel(i, j, 2) - 30;

      // Clamp values to the valid range [0, 255]
      pixels_r = max(0, min(pixels_r, 255));
      pixels_b = max(0, min(pixels_b, 255));

      // Set pixel values in the sunlight image
      sunlight.setPixel(i, j, 0, pixels_r);                // Red channel
      sunlight.setPixel(i, j, 1, image.getPixel(i, j, 1)); // Green channel
      sunlight.setPixel(i, j, 2, pixels_b);                // Blue channel
    }
  }
  return sunlight;
}

// Function to merge two images by resizing and averaging pixel values
Image merge_resize(const Image &image1, const Image &image2) {
  // Determine the maximum width and height between the two images
  int maximum_width = max(image1.width, image2.width);
  int maximum_height = max(image1.height, image2.height);

  // Resize the first image to match the maximum dimensions
  Image resized_image1(maximum_width, maximum_height);
  for (int y = 0; y < maximum_height; ++y) {
    for (int x = 0; x < maximum_width; ++x) {
      for (int c = 0; c < 3; ++c) {
        // Calculate the corresponding pixel coordinates in the original image
        int original_x = x * image1.width / maximum_width;
        int original_y = y * image1.height / maximum_height;
        // Set the pixel value in the resized image
        resized_image1.setPixel(x, y, c,
                                image1.getPixel(original_x, original_y, c));
      }
    }
  }

  // Resize the second image to match the maximum dimensions
  Image resized_image2(maximum_width, maximum_height);
  for (int y = 0; y < maximum_height; ++y) {
    for (int x = 0; x < maximum_width; ++x) {
      for (int c = 0; c < 3; ++c) {
        // Calculate the corresponding pixel coordinates in the original image
        int original_x = x * image2.width / maximum_width;
        int original_y = y * image2.height / maximum_height;
        // Set the pixel value in the resized image
        resized_image2.setPixel(x, y, c,
                                image2.getPixel(original_x, original_y, c));
      }
    }
  }

  // Merge the two resized images by averaging pixel values
  Image merged(maximum_width, maximum_height);
  for (int y = 0; y < maximum_height; ++y) {
    for (int x = 0; x < maximum_width; ++x) {
      for (int c = 0; c < 3; ++c) {
        // Calculate the average pixel value between the two images
        int pixel_value = (resized_image1.getPixel(x, y, c) +
                           resized_image2.getPixel(x, y, c)) /
                          2;
        // Set the pixel value in the merged image
        merged.setPixel(x, y, c, pixel_value);
      }
    }
  }

  // Return the merged image
  return merged;
}

// Function to merge the common area of two images by averaging pixel values
Image merge_common_area(const Image &image1, const Image &image2) {
  // Determine the minimum width and height between the two images
  int minimum_width = min(image1.width, image2.width);
  int minimum_height = min(image1.height, image2.height);

  // Create a new image to store the merged common area
  Image merged(minimum_width, minimum_height);

  // Iterate over each pixel in the common area
  for (int y = 0; y < minimum_height; ++y) {
    for (int x = 0; x < minimum_width; ++x) {
      for (int c = 0; c < 3; ++c) {
        // Calculate the average pixel value from the corresponding pixels in
        // the two images
        int pixel_value =
            (image1.getPixel(x, y, c) + image2.getPixel(x, y, c)) / 2;
        // Set the pixel value in the merged image
        merged.setPixel(x, y, c, pixel_value);
      }
    }
  }

  // Return the merged image
  return merged;
}

// Function to apply an old TV effect to an image
Image old_tv_effect(Image &image) {
  // Create a new image to store the modified image
  Image old_tv(image.width, image.height);

  // Iterate over each pixel in the image
  for (int i = 0; i < image.width; i++) {
    for (int j = 0; j < image.height; j++) {
      // Check if the pixel row number is a multiple of 10
      if (j % 10 == 0) {
        // Calculate the average intensity of the pixel
        unsigned char avg = (image.getPixel(i, j, 0) + image.getPixel(i, j, 1) +
                             image.getPixel(i, j, 2)) /
                            3;
        // Set the RGB values of the pixel to the average intensity
        old_tv.setPixel(i, j, 0, avg);
        old_tv.setPixel(i, j, 1, avg);
        old_tv.setPixel(i, j, 2, avg);
      } else {
        // Copy the RGB values of the pixel from the original image
        old_tv.setPixel(i, j, 0, image.getPixel(i, j, 0));
        old_tv.setPixel(i, j, 1, image.getPixel(i, j, 1));
        old_tv.setPixel(i, j, 2, image.getPixel(i, j, 2));
      }
    }
  }

  // Introduce random noise by setting pixels to a gray color
  for (int k = 0; k < image.width / 5; k++) {
    for (int l = 0; l < image.height / 5; l++) {
      // Generate random coordinates within the image
      int row = random_(0, image.width - 1);
      int col = random_(0, image.height - 1);
      // Set the RGB values of the pixel to a gray color (120, 120, 120)
      old_tv.setPixel(row, col, 0, 120);
      old_tv.setPixel(row, col, 1, 120);
      old_tv.setPixel(row, col, 2, 120);
    }
  }

  // Return the modified image with the old TV effect
  return old_tv;
}

// Function to skew an image by a given angle
void image_skew(const Image &image, Image &skewed_image, float skew_angle) {
  // Convert skew angle from degrees to radians
  float skew_radians = skew_angle * M_PI / 180.0;

  // Calculate maximum height of the skewed image
  int new_height = image.height;

  // Calculate the maximum width of the skewed image
  int new_width = image.width + tan(skew_radians) * image.height;

  // Create the skewed image with the calculated dimensions
  skewed_image = Image(new_width, new_height);

  // Calculate the horizontal offset for the skewed image to align it properly
  float offset_x = abs(tan(skew_radians)) * image.height;

  // Loop through each pixel in the skewed image
  for (int y = 0; y < new_height; y++) {
    for (int x = 0; x < new_width; x++) {
      // Calculate the corresponding original x-coordinate for the skewed pixel
      float original_x = x - offset_x + tan(skew_radians) * y;

      // Perform bilinear interpolation to get the pixel value
      int x0 = floor(original_x);
      int x1 = ceil(original_x);

      // Check if the interpolated pixel falls within the bounds of the original
      // image
      if (x0 >= 0 && x1 < image.width) {
        // Calculate the interpolation weight for each neighboring pixel
        float delta_x = original_x - x0;

        // Interpolate pixel values for each color channel
        for (int c = 0; c < 3; c++) {
          float interpolation_value = image.getPixel(x0, y, c) * (1 - delta_x) +
                                      image.getPixel(x1, y, c) * delta_x;
          // Set the interpolated pixel value in the skewed image
          skewed_image.setPixel(
              x, y, c, static_cast<unsigned char>(interpolation_value));
        }
      } else {
        // Set pixels outside the original image bounds to black
        for (int c = 0; c < 3; c++) {
          skewed_image.setPixel(x, y, c, 0);
        }
      }
    }
  }
}

// Function to flip an image horizontally
void image_flip_horizontally(Image &image) {
  // Iterate through the left half of the image width
  for (int i = 0; i < image.width / 2; ++i) {
    // Iterate through all rows of pixels
    for (int j = 0; j < image.height; ++j) {
      // Swap pixels horizontally for each color channel
      for (int k = 0; k < 3; ++k) {
        swap(image(i, j, k), image(image.width - 1 - i, j, k));
      }
    }
  }
}

// Function to flip an image vertically
void image_flip_vertically(Image &image) {
  // Iterate through all columns of pixels
  for (int i = 0; i < image.width; ++i) {
    // Iterate through the top half of the image height
    for (int j = 0; j < image.height / 2; ++j) {
      // Swap pixels vertically for each color channel
      for (int k = 0; k < 3; ++k) {
        swap(image(i, j, k), image(i, image.height - 1 - j, k));
      }
    }
  }
}

// Function to load an image from file
Image loading_image(string filename) {
  // Prompt the user to enter the name or full path of the image
  cout << "Please enter the name or the full path of the image that you want "
          "to edit: ";
  // Ignore any characters left in the input buffer up to the next newline
  // character
  cin.ignore(1, '\n');
  // Read the input line containing the file name or full path
  getline(cin, filename);
  // Declare an Image object using the provided file name or path
  Image image(filename);
  // Return the loaded image
  return image;
}

// Function to apply various filters to an image based on user input
void filters(Image &image, string &filename) {
  // Display sub-menu to choose the filter to apply
  sub_menu();
  // Get the user's choice of filter
  enfilters filter = menu_user_filter();
  // Initialize the resulting object to save the edited image from the filters
  Image result_image;

  // Apply the selected filter
  if (filter == ::RotateImage) {
    // Rotate the image
    string choice;
    do {
      cout << "\nchoose a rotation angle " << endl;
      cout << "1) 90  degree " << endl;
      cout << "2) 180 degree " << endl;
      cout << "3) 270 degree " << endl;
      // Choice to rotate the image by a certain degree
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
    // Convert image to grayscale
    result_image = image_gray_scale(image);
  } else if (filter == ::InvertImage) {
    // Invert colors of the image
    result_image = image_invert_colors(image);
  } else if (filter == ::BlackAndWhite) {
    // Convert image to black and white
    result_image = image_black_white(image);
  } else if (filter == ::DarkenAndLighten) {
    // Darken or lighten the image
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
  } else if (filter == ::Frame) {
    // Add a frame to the image
    char choice;
    char choice_color;
    do {
      cout << "Choose fancy or normal (f/n): ";
      cin >> choice;
    } while (choice != 'f' && choice != 'F' && choice != 'N' && choice != 'n');

    do {
      cout << "Choose the color red, green, or blue (r/g/b): ";
      cin >> choice_color;
    } while (choice_color != 'r' && choice_color != 'R' &&
             choice_color != 'g' && choice_color != 'G' &&
             choice_color != 'b' && choice_color != 'B');

    if (choice == 'f' || choice == 'F') {
      image_adding_fancyframe(image, choice_color);
      result_image = image;
    } else {
      image_adding_frame(image, choice_color);
      result_image = image;
    }
  } else if (filter == ::Resize) {
    // Resize the image
    result_image = image_resize(image);
  } else if (filter == ::Crop) {
    // Crop the image
    result_image = image_crop(image);
  } else if (filter == ::EdgeDetect) {
    // Detect edges in the image
    result_image = image_detect_edges(image);
  } else if (filter == ::Blur) {
    // Blur the image
    result_image = image_blur(image);
  } else if (filter == ::merge) {
    // Merge the image with another image
    Image image2 = loading_image(filename);
    if (image.width == image2.width && image.height == image2.height) {
      // Merge the images directly
      result_image = merge_common_area(image, image2);
    } else {
      int mergeChoice;
      do {
        cout << "Images have different dimensions. Choose merging option:"
             << endl;
        cout << "1. Resize both images to the biggest height and width and "
                "then merge."
             << endl;
        cout << "2. Merge the common area of the smaller width and the smaller "
                "height."
             << endl;
        cout << "Enter your choice (1 or 2): ";
        cin >> mergeChoice;
      } while (mergeChoice != 1 && mergeChoice != 2);

      if (mergeChoice == 1) {
        // Merge the images after resizing both to the biggest height and width
        result_image = merge_resize(image, image2);
      } else if (mergeChoice == 2) {
        // Merge the images by their common area
        result_image = merge_common_area(image, image2);
      }
    }
  } else if (filter == ::flip) {
    // Flip the image horizontally or vertically
    int flipDirection;
    do {
      cout
          << "Enter 1 for 'horizontal' or 2 for 'vertical' to flip the image: ";
      cin >> flipDirection;
    } while (flipDirection != 1 && flipDirection != 2);

    if (flipDirection == 1) {
      image_flip_horizontally(image);
    } else if (flipDirection == 2) {
      image_flip_vertically(image);
    }

    result_image = image;
  } else if (filter == ::oil) {
    // Apply an oil paint effect to the image
    Image oil_painted_image(image.width, image.height);
    image_oil_paint(image, oil_painted_image);
    result_image = oil_painted_image;
  } else if (filter == ::Infrared) {
    // Apply an infrared effect to the image
    result_image = infrared(image);
  } else if (filter == ::Purple) {
    // Apply a purple effect to the image
    purple_effect(image);
    result_image = image;
  } else if (filter == ::Sunlight) {
    // Apply a sunlight effect to the image
    result_image = sunlight_effect(image);
  } else if (filter == ::Skew) {
    // Skew the image
    image_skew(image, result_image, 30.0f);
  } else if (filter == ::oldTv) {
    // Apply an old TV effect to the image
    result_image = old_tv_effect(image);
  } else if (filter == ::saving) {
    // Save the image in the filter menu
    result_image = image;
    saving_condition(result_image, filename);
    return;
  }
  // Save the edited image after applying the desired filters
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
    if (image_choice == ::load_image) {
      Image image = loading_image(filename);
      filters(image, filename);
    }
    if (image_choice == ::Exit) {
      return;
    }
  }
}
int main() {
  baby_photoshop();
  return 0;
}
