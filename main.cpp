#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <string>
#include <iomanip> // for std::setprecision
#include <cstdlib> // for std::exit

// Function to read VAT rates from a CSV file and store them in a map
std::map<std::string, double> readVATRatesFromFile(const std::string& filename) {
    std::map<std::string, double> countryTax;

    std::ifstream file(filename);
    if (!file.is_open()) {
        std::cerr << "Failed to open the file: " << filename << std::endl;
        std::exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string country;
        double taxRate;
        if (iss >> country >> taxRate) {
            countryTax[country] = taxRate;
        }
    }

    file.close();
    return countryTax;
}

// Function to print the list of countries from the CSV file
void printCountryList(const std::map<std::string, double>& taxMap) {
    std::cout << "List of Countries in the CSV file:" << std::endl;
    for (const auto& entry : taxMap) {
        const std::string& country = entry.first;
        std::cout << country << std::endl;
    }
}

// Function to calculate the final price after subtracting VAT
double calculateFinalPrice(const std::string& country, const std::map<std::string, double>& taxMap, double price) {
    auto it = taxMap.find(country);
    if (it != taxMap.end()) {
        double vatRate = it->second;
        double finalPrice = price * (1.0 - vatRate);
        return finalPrice;
    } else {
        std::cerr << "Country " << country << " not found in the tax map." << std::endl;
        return price; // Return the original price if the country is not found
    }
}

int main() {
    // Read VAT rates from the CSV file (assuming the file is named "vat_rates.csv")
    std::map<std::string, double> countryTax = readVATRatesFromFile("/home/georgia/CLionProjects/CPP_tutorial/vat_rates.csv");

    // Print the list of countries from the CSV file
    printCountryList(countryTax);

    // Input parameters: country and initial price
    std::string selectedCountry = "Germany";
    double initialPrice = 32;

    // Calculate the final price using the function
    double finalPrice = calculateFinalPrice(selectedCountry, countryTax, initialPrice);

    // Print the final price with 2 decimal places
    std::cout << "Final price in " << selectedCountry << ": " << std::fixed << std::setprecision(2) << finalPrice << std::endl;

    return 0;
}
