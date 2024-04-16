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

January 5, 2024
- Set up Docker with EC2
- Worked on some matrix transformation problems

January 7, 2024
- Solved convoluted bug involving the API returning strings which contain quotation marks themselves, implemented some string cleaning in the JSON parsing process.
- Implemented some asynchronous API calls using mutex and async which allowed me to match the rate limit for the API. Shaved a considerable amount of time off the data collection process (demo uploaded here as generate_base_assets.cpp)
- Considering different methods of measuring risk and liquidity, possibly creating an index score involving order book depth, volatility, and volume to be considered in risk analysis for each currency.

January 8, 2024
- Continued cloud set up, learned about interactions betwewen CMake and Docker
- Tracked down many bugs and linker errors in the build process
- Settled on a EC2 linux set up but will continue local development on macOS
- Set up ssh connection with EC2 instance
- Discovered that Japan and Singapore AWS servers both have superior connection stability and throughput with the exchange

January 9, 2024
- Made some efficiency gains by finding some calculations and analyses which could be outsourced to compile time. Capacity to execute on detected opportunities should in theory be improved.

January 10, 2024
- Started learning CUDA. At the moment it seems like it's best application would be for the expensive matrix operations that I was initially doing with multiple threads. Will need to ensure I'm using an EC2 instance which has access to NVIDIA GPUs.
- Eigen doesn't have support for CUDA, and Eigen matrices are designed for CPU based computation, noteworthy because CPUs are optimized for sequential operations whereas GPUs are optimized for concurrent computation.
- I could develop a data transfer process to convert my Eigen matrices into 2D arrays to then be used in a CUDA program, but it's possible that the latency of that process would drag me down significantly so I may just scrap using Eigen altogether and edit the entire code base to use 2D matrices instead of Eigen matrices.

January 20, 2024
- I've put the CUDA-Eigen integration on hold in favour of working on the traversal algorithm. At this point I have a very heavily modified version of a known graph traversal algorithm but I'm still experimenting with improvements that can be made in terms of moving run-time problems to compile time.
- My most likely approach moving forward will be to use the traversal algorithm as an exploratory pre-amble to the execution phase, i.e., rather than use it to discover opportunities and then execute upon them, use it to discover and document all opportunities, then use some multi-threading/websocket magic to constantly monitor and execute upon the discovered possibilities.

January 28, 2024
- Completed system for retrieval and parsing of order books
- Implemented a baseline liquidity analysis process for each cryptocurrency

April 16, 2024
- After lots of research, I've decided I'm not going to risk attempting to access MEXC through a Singaporean VPN.
- Coinbase is available in Canada and offers FIX Order Entry API for higher-frequency trading. I will be moving forward with Coinbase.
