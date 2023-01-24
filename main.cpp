#include <iostream>
#include <sys/stat.h>
#include <random>

std::mt19937 random_seed(time(0));
std::string random_huge_number(int length){ // random number of length n (may contain leading zeros)
    std::uniform_int_distribution<int> dist(0, 9);
    std::string str(length, ' ');
    for (int i = 0; i < length; ++i)
        str[i] = '0' + dist(random_seed);
    return str;
}

// Structure which would store the metadata
struct stat sb;
bool isExistInPath(std::string path){
    return !stat(path.c_str(), &sb);
}

const std::string testsDir = "Tests";
void init(){
    if(!isExistInPath(testsDir)){
        std::string createTestsDir = "mkdir " + testsDir;
        if(system(createTestsDir.c_str())){
            throw std::invalid_argument("Couldn't create tests directory");
        }
    }
}

void interact(int& numberOfTestCases, std::string& generatorPath){
    std::cout << "Enter executable generator path:\n";
    std::cin >> generatorPath;
    while(!isExistInPath(generatorPath)){
        std::cout << "generator doesn't exist in the given path. Please enter the correct path:\n";
        std::cin >> generatorPath;
    }

    std::cout << "Enter number of tests you want to be generated:\n";
    std::string input;
    std::cin >> input;
    try{
        numberOfTestCases = stoi(input);
        numberOfTestCases = std::max(numberOfTestCases, 0);
    }catch(...){
        numberOfTestCases = 0;
    }
}

void generates(int numberOfTestCases, std::string generatorPath){
    for(int i = 1; i <= numberOfTestCases; ++i){
        // create random file name which wasn't exist before
        std::string filePath = testsDir + "/" + random_huge_number(6) + ".txt";
        while(isExistInPath(filePath))
            filePath = testsDir + "/" + random_huge_number(6) + ".txt";

        // run generator
        std::string runCommand = generatorPath + " > " + filePath;
        if(system(runCommand.c_str())){
            throw std::invalid_argument("Couldn't run generator");
        }else{
            std::cout << "Test " << i << " is generated.\n";
        }
    }
}

int main(){
    std::string generatorPath;
    int numberOfTestCases;

    init();
    interact(numberOfTestCases, generatorPath);
    generates(numberOfTestCases, generatorPath);

    return 0;
}