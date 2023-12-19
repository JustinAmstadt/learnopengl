#ifndef RAYTRACER_H
#define RAYTRACER_H

#include <iostream>
#include <fstream>

#include <color.h>

class Raytracer{
public:
    std::string outputFileName;
    std::string ppmString;
    std::string outputFileContents;

    int image_width = 256;
    int image_height = 256;

    Raytracer(const std::string& outputFile) : outputFileName(outputFile) {
        makeImage();
        convertPPMtoPNG();
    }

    void makeImage() {
        ppmString = outputFileName;
        ppmString.replace(outputFileName.length() - 3, 3, "ppm");

        std::ofstream output(ppmString);
        if(!output.is_open()) {
            std::cerr << "Error opening the file for writing." << std::endl;
            return;
        }

        output << "P3\n" << image_width << ' ' << image_height << "\n255\n";

        for (int j = 0; j < image_height; ++j) {
            std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
            for (int i = 0; i < image_width; ++i) {
                auto pixel_color = color(double(i)/(image_width - 1), double(j)/(image_height - 1), 0.0f);
                write_color(output, pixel_color);
            }
        }

        std::clog << "\rDone.                 \n";

        output.close();
    }

    void convertPPMtoPNG() {
        std::string command = "convert ";
        command.append(ppmString + " ");
        command.append(outputFileName);

        int result = system(command.c_str());

        if (!result == 0) {
            std::cerr << "Could not convert ppm to png";
        }
    }
};

#endif