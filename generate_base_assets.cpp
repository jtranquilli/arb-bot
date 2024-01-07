#include <fstream>
#include <set>
#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <future>
#include <mutex>
#include <iomanip>
#include <chrono>



#include "include/markets_API.hpp"
#include "include/JSON_parser.hpp"

std::mutex currencyListMutex; // for thread-safe access to the shared resource
std::string responseFile = "response.json";

void processProduct(const std::string& product, std::set<std::string>& currency_list) {
	std::string requestLink = "https://api.mexc.com/api/v3/exchangeInfo?symbol=" + product;
    	std::string curr_product_data = makeGetRequestString(requestLink);
	std::string currency = extractValueForKey(curr_product_data, "baseAsset");
    	currency.erase(std::remove(currency.begin(), currency.end(), '\"'), currency.end());
    	currency.erase(std::remove(currency.begin(), currency.end(), '\''), currency.end());

    	std::lock_guard<std::mutex> guard(currencyListMutex);
    	currency_list.insert(currency);

    	currency = extractValueForKey(curr_product_data, "quoteAsset");
    	currency.erase(std::remove(currency.begin(), currency.end(), '\"'), currency.end());
    	currency.erase(std::remove(currency.begin(), currency.end(), '\''), currency.end());
    	currency_list.insert(currency);
}

void regenerate_currency_list() {
    	std::set<std::string> currency_list;
    	std::ofstream outFile("baseAssets.csv");
    	std::string address1 = "https://api.mexc.com/api/v3/defaultSymbols";
    	makeGetRequest(address1, responseFile);
    	std::vector<std::string> products = parseProductsFromFile("response.json");
    	std::cout << "generate_baseAssets.cpp: Response data read from 'response.json'\n";
    	std::cout << "Writing baseAsset items to baseAssets.csv.\n";

    	std::vector<std::future<void>> futures;
    	int total = products.size();
    	int progressCounter = 0;

    	for (int i = 0; i < total; ++i) {
        	futures.push_back(std::async(std::launch::async, processProduct, products[i], std::ref(currency_list)));

       		// rate limit: 2 calls per second
        	if (i % 2 == 1) {
            		std::this_thread::sleep_for(std::chrono::seconds(1));
        	}

       		// progress bar update
        	++progressCounter;
        	int progress = (progressCounter * 100) / total;
        	std::cout << "\r[" << std::setw(3) << progress << "%] Processing... " << std::flush;
    	}

    	// wait for all asynchronous tasks to complete
    	for (auto& future : futures) {
        	future.get();
   	 }

    	std::cout << "\n"; // Move to the next line after the progress bar completes

    	// write the unique currencies to the CSV file
    	for (const auto& currency : currency_list) {
        	outFile << currency << std::endl;
    	}

    	outFile.close();
}
