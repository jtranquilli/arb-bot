# arb-bot

January 1, 2024
- Developed JSON parsing process
- Created reading/writing utils for storing and reading large volumes of data
- Created several flags for main function to help with debugging

January 2, 2024
- Considering using Eigen's sparse matrix, may need to find a way to transform the data to make it work but the matrix in question is structurally analogous to a sparse matrix, and finding a way to use Eigen's sparse matrix would provide some storage efficiency gains

January 4, 2024
- Implemented some unit testing to ensure data is being read and stored properly
- Set up CMake as the project was getting large enough that the compile statements were prone to error

January 7, 2024
- Solved very convoluted bug involving the API returning strings which contain quotation marks themselves, implemented some string cleaning in the JSON parsing process.
- Implemented some asynchronous API calls using <mutex> and <async> which allowed me to match the rate limit for the API. Shaved a considerable amount of time off the data collection process.
- Considering different methods of measuring risk and liquidity. Depth of order book is potentially the best option for my purposes. I'm also considering cutting the asset pool by about 80% on the basis of low volume currencies posing too high of a risk to latency. 
