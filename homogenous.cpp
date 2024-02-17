#include <iostream>
#include <thread>
#include <fstream>
#include <chrono>

using namespace std;

void homogenous_work_load(string output_file) {
    ofstream file(output_file);
    if (file.is_open()) {
        for (int i = 0; i < 3000; ++i) {
            file << "Line " << i + 1 << ": Junk\n";
         }

         file.close();
    } else {
        std::cerr << "Unable to create the file: " << output_file << std::endl;
        return;
    }

    std::ifstream inputFile(output_file);
    std::vector<std::string> lines;

    if (inputFile.is_open()) {
        std::string line;

        // Read all lines from the file
        while (std::getline(inputFile, line)) {
            lines.push_back(line);
        }

        inputFile.close();
    } else {
        std::cerr << "Unable to reopen the file: " << output_file << std::endl;
        return;
    }

    // Step 3: Remove the first 2 lines
    lines.erase(lines.begin(), lines.begin() + 2);

    // Step 4: Close the file
    std::ofstream outputFile(output_file);

    if (outputFile.is_open()) {
        // Write the modified lines back to the file
        for (const auto& line : lines) {
            outputFile << line << "\n";
        }

        outputFile.close();
    } else {
        std::cerr << "Unable to update the file: " << output_file << std::endl;
        return;
    }
/*
    // Step 5: Delete the file
    if (std::remove(file.c_str()) != 0) {
        std::cerr << "Unable to delete the file: " << output_file << std::endl;
    } else {
        std::cout << "File operations completed successfully." << std::endl;
    }
*/
}


int main() {
    // Allocate 2 threads
    // Work of thread 1:
      // Produce a large file (homogenous)
      // Read and modify the first 2 lines
      // Delete the file
      
    // Work of thread 2:
      // Produce a large file (homogenous)
      // Read and modify the first 2 lines
      // Delete the file
    
    std::thread t1(homogenous_work_load, "inp");
    std::thread t2(homogenous_work_load, "inp2");

    // Join threads to wait for them to finish
    t1.join();
    t2.join();

    return 0;
}
