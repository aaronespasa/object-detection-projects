// You can try to call the binary file as:
// $ ./build/webcam one two three four five

// Note: The binary file `webcam` is configured to be called
// from the `Image-Collection` folder, not from the `Image-Collection/build` folder

#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include <iostream>
#include <string>
#include <filesystem>
#include <random>
#include <sstream>

namespace fs = std::__fs::filesystem;

const int FPS = 60;
const int KEY_A_ASCII_CODE = 97;
const int KEY_D_ASCII_CODE = 100;
const int KEY_Q_ASCII_CODE = 113;
const int KEY_R_ASCII_CODE = 114;
const int KEY_ENTER_ASCII_CODE = 13;

const std::string IMAGES_FOLDER = "images";
const std::string COLLECTED_IMAGES_FOLDER = "collectedimages";
// IMPORTANT:
// We don't apply .parent_path() to fs::current_path() as we
// call the binary file `webcam` from OUTSIDE the `build` folder
const fs::path IMAGES_PATH = fs::current_path()         // get current path
                            / IMAGES_FOLDER            // go inside the 'images' folder
                            / COLLECTED_IMAGES_FOLDER; // go inside the 'collectedimages' folder

// Source of the following uuid namespace code:
// https://stackoverflow.com/questions/24365331/how-can-i-generate-uuid-in-c-without-using-boost-library/58467162
namespace uuid
{
    static std::random_device rd;
    static std::mt19937 gen(rd());
    static std::uniform_int_distribution<> dis(0, 15);
    static std::uniform_int_distribution<> dis2(8, 11);

    std::string generate_uuid_v4()
    {
        std::stringstream ss;
        int i;
        ss << std::hex;
        for (i = 0; i < 8; i++)
        {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 4; i++)
        {
            ss << dis(gen);
        }
        ss << "-4";
        for (i = 0; i < 3; i++)
        {
            ss << dis(gen);
        }
        ss << "-";
        ss << dis2(gen);
        for (i = 0; i < 3; i++)
        {
            ss << dis(gen);
        }
        ss << "-";
        for (i = 0; i < 12; i++)
        {
            ss << dis(gen);
        };
        return ss.str();
    }
}

// argc (ARGument Count): Integer corresponding to the number of teminal arguments
// argv (ARGument Vector): Vector containing the arguments
int main(int argc, const char *argv[])
{
    int cameraID = 0;
    cv::VideoCapture cap(cameraID);

    if (!cap.isOpened()) return -1;

    // Index of the current (the first argument 0 is the command ./webcam)
    int labelIndex = 1;

    cv::Mat frame;
    while (cap.read(frame))
    {
        // Mirror the webcam
        cv::flip(frame, frame, 1);

        char c = (char)cv::waitKey(1000 / FPS);
        // Obtain the ASCII code of any key:
        // if ((int)c >= 0) std::cout << (int)c << std::endl;

        if (c == KEY_A_ASCII_CODE && labelIndex > 1)
        { // Key A
            // GO TO THE PREVIOUS LABEL
            labelIndex -= 1;
        }
        else if (c == KEY_D_ASCII_CODE && labelIndex < argc - 1)
        { // Key D
            // GO TO THE NEXT LABEL
            labelIndex += 1;
        }
        else if (c == KEY_R_ASCII_CODE)
        { // Key R
            // REMOVE ALL IMAGES
            for (int i = 1; i < argc; i++) {
                // Path to the label folder
                // Example: images/collectedimages/one
                fs::path labelPath = IMAGES_PATH / argv[i];

                // Iterate through all the files (entry.path()) in labelPath
                if (!fs::is_empty(labelPath)) {
                    for (const auto &entry : fs::directory_iterator(labelPath))
                    {
                        fs::remove_all(entry.path());
                    }
                }
            }
            std::cout << "All images have been deleted!" << std::endl;
        }
        else if (c == KEY_ENTER_ASCII_CODE)
        { // Key ENTER
            // TAKE A SCREENSHOT AND SAVE IT
            
            // Path to the label folder
            fs::path labelPath = IMAGES_PATH / argv[labelIndex];

            // Example of filename:
            // 38c6a8d4-ac1c-44fb-a1c9-f471c689e997-two.jpg
            std::string filename = uuid::generate_uuid_v4()
                                       .append("-")
                                       .append(argv[labelIndex])
                                       .append(".jpg");
            fs::path pathFilename = labelPath / filename;
            // Example of pathFilenameString:
            // object-detection-projects/Image-Collection/images/
            // collectedimages/38c6a8d4-ac1c-44fb-a1c9-f471c689e997-two.jpg
            std::string pathFilenameString = pathFilename.string();

            cv::imwrite(pathFilenameString, frame); // save screenshot

            std::cout << "Screenshot guardado en: " << std::endl;
            std::cout << pathFilenameString << std::endl << std::endl;
        }
        else if (c == KEY_Q_ASCII_CODE)
        { // Key Q
            // EXIT THE PROGRAM
            break;
        }

        // Display the current label
        std::string textToDisplayLabel("Categoria: ");
        textToDisplayLabel.append(argv[labelIndex]);

        cv::putText(frame,
                    textToDisplayLabel,
                    cv::Point(50, 50),
                    cv::FONT_HERSHEY_DUPLEX,
                    1,
                    cv::Scalar(35, 161, 198),
                    2,
                    false);

        // If you want to add new instructions, make sure
        // you change the 6 in textToDisplayInstructions
        // and the 6 in the for loop for the number of instructions
        // that you want
        std::string textToDisplayInstructions[6] = {
            "Instrucciones:",
            "a: Categoria anterior",
            "d: Categoria siguiente",
            "r: Borrar imagenes",
            "ENTER: Screenshot",
            "q: Salir"
        };

        for (int i = 0; i < 6; i++)
        {
            cv::putText(frame, textToDisplayInstructions[i], cv::Point(frame.cols - 400, (i+1)*50),
                        cv::FONT_HERSHEY_DUPLEX, 1, cv::Scalar(255, 211, 117), 2, false);
        }

        // Show the webcam
        cv::imshow("Webcam", frame);
    }
    return 0;
}