#include <iostream>
#include <map>
#include <string>

// Function to calculate the final price after subtracting VAT
double calculateFinalPrice(const std::string& country, const std::map<std::string, double>& taxMap, double price) {
    // Check if the country exists in the map
    auto it = taxMap.find(country);
    if (it != taxMap.end()) {
        // Calculate the final price by subtracting VAT
        double vatRate = it->second;
        double finalPrice = price * (1.0 - vatRate);
        return finalPrice;
    } else {
        std::cout << "Country " << country << " not found in the tax map." << std::endl;
        return price; // Return the original price if the country is not found
    }
}

int main() {
    // Create a map to store countries and their tax rates
    std::map<std::string, double> countryTax;

    // Add countries and their tax rates to the map
    countryTax["Germany"] = 0.19; // 19% tax rate
    countryTax["Italy"] = 0.22;   // 22% tax rate
    countryTax["France"] = 0.20;  // 20% tax rate

    // Calculate final prices for different countries
    double initialPrice = 100.0; // Initial price before VAT
    double finalPriceGermany = calculateFinalPrice(countryTax, "Germany", initialPrice);
    double finalPriceItaly = calculateFinalPrice(countryTax, "Italy", initialPrice);
    double finalPriceSpain = calculateFinalPrice(countryTax, "Spain", initialPrice); // Spain is not in the map

    // Print the final prices
    std::cout << "Final price in Germany: " << finalPriceGermany << std::endl;
    std::cout << "Final price in Italy: " << finalPriceItaly << std::endl;
    std::cout << "Final price in Spain: " << finalPriceSpain << std::endl;
    std::string message = std::format("The {} VAT of {} has been remitted, and will be reimbursed via OSS", countryTax. country);

    return 0;
}
